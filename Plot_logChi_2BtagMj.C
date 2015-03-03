//#include <iostream>
//#include <math.h>
//#include "TROOT.h"
//#include "TFile.h"
//#include "TTree.h"
//#include "TH1F.h"
//#include "TCanvas.h"

using namespace std;

double deltaR(double eta1, double phi1, double eta2, double phi2){
  double dEta = eta1 - eta2;

  double dPhi = phi1 - phi2;
  while (dPhi > TMath::Pi()) dPhi -= 2*TMath::Pi();
  while (dPhi <= -TMath::Pi()) dPhi += 2*TMath::Pi();

  double dR = sqrt(dEta*dEta + dPhi*dPhi);
  return dR;
}


TH1F* makeHisto(std::string fname){
  //{
  bool display = 0;

  //TFile *f = new TFile("RadionHH_M800_R12_r15_correctIVFmatch_mc_subjets.root");
  TFile *f = new TFile((fname).c_str());
  TDirectoryFile *df = f->GetDirectory("btaganaSubJets");
  TTree *tf = df->Get("ttree");

  //TCanvas *c = new TCanvas("c","SD fatjet higgs matching",800,600);
  TH1F *h = new TH1F(fname.c_str(),fname.c_str(),50,-18,-2);

  const int nEvent = tf->GetEntries();

  int nFj;
  const int nFjMax=8;
  float Fj_chi[nFjMax];
  int Fj_nbMj[nFjMax];

  tf->SetBranchAddress("FatJetInfo.nJet",&nFj);
  tf->SetBranchAddress("FatJetInfo.Jet_SD_chi",&Fj_chi);
  tf->SetBranchAddress("FatJetInfo.Jet_SD_nBtagMicrojets",&Fj_nbMj);

  //loop over events
  if(display)cout << endl;
  for (int i =0 ; i<nEvent;i++){
    //for (int i =0 ; i<2;i++){
    tf->GetEntry(i);
    //loop over fatjets
    for(int j=0; j < nFj; j++){
      if(display)cout<< "           "<<     "    Fatjet_chi = " << Fj_chi[j] << endl;
      if(Fj_chi[j]>0 && Fj_nbMj[j]>1) h->Fill(log(Fj_chi[j])); //fill 2D histo (chi, dR)
    }//end fatjet loop

  }//end event loop

  gStyle->SetOptStat("nemrou");
  h->SetLineColor(kBlue);
  h->SetLineWidth(2);
  h->GetXaxis()->SetTitle("log(#chi)");
  h->GetXaxis()->SetTitleOffset(1.3);
  h->GetYaxis()->SetTitle("Entries");
  h->GetYaxis()->SetTitleOffset(1.2);
  h->SetTitle("");

  return h;
}

void Plot_logChi_1leadbtagcondition_2BtagMj(){
  TH1F *h = (TH1F*) makeHisto("1leadbtagmjcondition/RadionToHH_4b_M-800_TuneZ2star_8TeV-Madgraph_pythia6_R12_r15_minPt200_1leadbtagmjcondition_mc_subjets.root");
  TH1F *h2 = (TH1F*) makeHisto("1leadbtagmjcondition/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_R12_r15_minPt200_1leadbtagmjcondition_mc_subjets.root");

  TCanvas *c = new TCanvas("SD - log chi", "SD - log chi",800, 600);
  TCanvas *c2 = new TCanvas("SD - log chi - sig", "SD - log chi - sig",800, 600);
  TCanvas *c3 = new TCanvas("SD - log chi - bkg", "SD - log chi - bkg",800, 600);

  gStyle->SetOptStat("nemrou");

  h->SetStats(1);
  h2->SetStats(1);

  c2->cd();
  h->SetLineColor(kBlue);
  h->Draw();
  c2->SaveAs("1leadbtagmjcondition/Plot_logChi_1leadbtagmjcondition_2BtagMj_sig.eps");


  c3->cd();
  h2->SetLineColor(kRed);
  h2->Draw();
  c3->SaveAs("1leadbtagmjcondition/Plot_logChi_1leadbtagmjcondition_2BtagMj_bkg.eps");

  //c->SetGrid();
  c->cd();

  Double_t norm1 = h->GetEntries();
  h->Scale(1/norm1);
  Double_t norm2 = h2->GetEntries();
  h2->Scale(1/norm2);

  h->SetStats(0);
  h2->SetStats(0);

  h->SetTitle("");

  h->Draw();
  h2->Draw("SAME");

  leg = new TLegend(0.65,0.65,0.85,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h,"Radion M800","L");
  leg->AddEntry(h2,"TTJets","L");

  leg->Draw("SAME");

  c->SaveAs("1leadbtagmjcondition/Plot_logChi_1leadbtagmjcondition_2BtagMj_All.eps");
  c->SetLogy();
  c->SaveAs("1leadbtagmjcondition/Plot_logChi_1leadbtagmjcondition_2BtagMj_All_logyscale.eps");

}

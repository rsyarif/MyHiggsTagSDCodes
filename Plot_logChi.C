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

  tf->SetBranchAddress("FatJetInfo.nJet",&nFj);
  tf->SetBranchAddress("FatJetInfo.Jet_SD_chi",&Fj_chi);

  //loop over events
  if(display)cout << endl;
  for (int i =0 ; i<nEvent;i++){
    //for (int i =0 ; i<2;i++){
    tf->GetEntry(i);
    //loop over fatjets
    for(int j=0; j < nFj; j++){
      if(display)cout<< "           "<<     "    Fatjet_chi = " << Fj_chi[j] << endl;
      if(Fj_chi[j]>0) h->Fill(log(Fj_chi[j])); //fill 2D histo (chi, dR)
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

void Plot_logChi(){
  TH1F *h = (TH1F*) makeHisto("RadionHH_M800_R12_r15_correctIVFmatch_mc_subjets.root");
  TH1F *h2 = (TH1F*) makeHisto("TTJets_R12_r15_correctIVFmatch_mc_subjets.root");
  TH1F *h3 = (TH1F*) makeHisto("QCD_Pt-470to600_TuneZ2star_8TeV_pythia6_R12_r15_correctIVFmatch_mc_subjets.root");

  TCanvas *c = new TCanvas("SD - log chi", "SD - log chi",800, 600);
  //c->SetGrid();

  Double_t norm1 = h->GetEntries();
  h->Scale(1/norm1);
  Double_t norm2 = h2->GetEntries();
  h2->Scale(1/norm2);
  Double_t norm3 = h3->GetEntries();
  h3->Scale(1/norm3);

  gStyle->SetOptStat(0);

  h->SetTitle("");
  h->SetLineColor(kBlue);
  h->Draw();

  h2->SetLineColor(kRed);
  h2->Draw("SAME");

  h3->SetLineColor(kGreen+3);
  h3->SetLineStyle(2);
  h3->Draw("SAME");

  leg = new TLegend(0.65,0.65,0.85,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h,"Radion M800","L");
  leg->AddEntry(h2,"TTJets","L");
  leg->AddEntry(h3,"QCD p_{T}470-600","L");

  leg->Draw("SAME");

  c->SaveAs("Plot_logChi_All.eps");
  c->SetLogy();
  c->SaveAs("Plot_logChi_All_logyscale.eps");

}


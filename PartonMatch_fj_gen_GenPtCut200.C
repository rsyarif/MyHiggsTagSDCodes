
using namespace std;

TH2D* PartonMatch(std::string fdir, std::string fname, std::string var = "dR", int gen_pdgid, double dRmax = 1.2, int xbin =50, double xmin = -18, double xmax = -2, int ybin = 50, double ymin =0, double ymax =0.6,bool display=false, bool save=false, std::string postfix = ""){

  TFile *f = new TFile((fdir+"/"+fname+".root").c_str());

  TDirectoryFile *d = f->GetDirectory("btagana");
  TTree *t = d->Get("ttree");
  TDirectoryFile *df = f->GetDirectory("btaganaSubJets");
  TTree *tf = df->Get("ttree");

  TCanvas *c = new TCanvas("c","SD fatjet genparticle matching",800,600);
  TCanvas *c2 = new TCanvas("c2","SD fatjet genparticle matching",800,600);
  TH2D *h = new TH2D("h","h",xbin,xmin,xmax,ybin,ymin,ymax);

  const int nEvent = t->GetEntries();
  int nMatchMax = 0;
  vector<int> iEventOverMatch;

  int nGenPruned;
  const int nGenPrunedMax = 25;
  int GenPruned_pdgID[nGenPrunedMax];
  float GenPruned_eta[nGenPrunedMax]; //simple hack to avoid making different size arrays every event loop. Run calcMax.C
  float GenPruned_phi[nGenPrunedMax];
  float GenPruned_pT[nGenPrunedMax];

  int FatJetInfo_nJet;
  const int nFjMax=5;
  float FatJetInfo_Jet_eta[nFjMax];
  float FatJetInfo_Jet_phi[nFjMax];
  float FatJetInfo_Jet_SD_chi[nFjMax];
  float FatJetInfo_Jet_pt[nFjMax];
  int FatJetInfo_Jet_SD_nBtagMicrojets[nFjMax];
  //int Fj_isleadMjbtag[nFjMax];

  t->SetBranchAddress("nGenPruned",&nGenPruned);
  t->SetBranchAddress("GenPruned_pdgID",&GenPruned_pdgID);
  t->SetBranchAddress("GenPruned_eta",&GenPruned_eta);
  t->SetBranchAddress("GenPruned_phi",&GenPruned_phi);
  t->SetBranchAddress("GenPruned_pT",&GenPruned_pT);

  tf->SetBranchAddress("FatJetInfo.nJet",&FatJetInfo_nJet);
  tf->SetBranchAddress("FatJetInfo.Jet_eta",&FatJetInfo_Jet_eta);
  tf->SetBranchAddress("FatJetInfo.Jet_phi",&FatJetInfo_Jet_phi);
  tf->SetBranchAddress("FatJetInfo.Jet_SD_chi",&FatJetInfo_Jet_SD_chi);
  tf->SetBranchAddress("FatJetInfo.Jet_pt",&FatJetInfo_Jet_pt);
  tf->SetBranchAddress("FatJetInfo.Jet_SD_nBtagMicrojets",&FatJetInfo_Jet_SD_nBtagMicrojets);
  //tf->SetBranchAddress("FatJetInfo.Jet_SD_isLeadMicrojetBtag",&Fj_isleadMjbtag);
  cout << endl;
  cout << "Matching fatjets in "<< fname << ", with pdgid = " << gen_pdgid << endl;
  cout << endl;

  //loop over events
  if(display)cout << endl;
  for (int i =0 ; i<nEvent;i++){
    t->GetEntry(i);
    tf->GetEntry(i);
    if(display)cout << endl;
    if(display)cout << "============  entry : "<< i << ", nGenPruned = "<< nGenPruned << ", nFatJet = "<< FatJetInfo_nJet <<"=============="<< endl;
    if(display)cout << endl;

    //loop over fatjets
    int nMatch=0;
    for(int j=0; j < FatJetInfo_nJet; j++){
      if(display)cout<< "Fatjet no. "<< j << " : Fatjet_eta = " << FatJetInfo_Jet_eta[j] << endl;
      if(display)cout<< "           "<<     "    Fatjet_phi = " << FatJetInfo_Jet_phi[j] << endl;
      if(display)cout<< "           "<<     "    Fatjet_chi = " << FatJetInfo_Jet_SD_chi[j] << endl;
      if(display)cout<<endl;

      //loop over GenPruned
      for(int k=2; k < nGenPruned; k++){
	if(GenPruned_pdgID[k]==gen_pdgid){
	  if(display)cout<< "        GenPruned no. "<< k << " : GenPruned_pdgID = " << GenPruned_pdgID[k] << endl;
	  if(display)cout<< "                      "<<     "    GenPruned_eta = " << GenPruned_eta[k] << endl;
	  if(display)cout<< "                      "<<     "    GenPruned_phi = " << GenPruned_phi[k] << endl;

	  double dR = deltaR(GenPruned_eta[k], GenPruned_phi[k], FatJetInfo_Jet_eta[j], FatJetInfo_Jet_phi[j]);
	  if(display)cout<< "        " << j<< "-"<<k<<", -------------------------------->  delta R = "<< dR ;// << endl;
	  if(dR<dRmax){
	    if(display)cout<<"----> MATCH!! " << endl;
	    nMatch++;
	    //Determine Cuts conditions - CONTINUE HERE. HOW TO PASS OVER CUT??
	    if(GenPruned_pT[k]<=200)continue;
	    if(FatJetInfo_Jet_SD_chi[j]>0 && FatJetInfo_Jet_pt[j]>200){
	      if(var == "dR") h->Fill(log(FatJetInfo_Jet_SD_chi[j]),dR); //fill 2D histo (chi, dR)
	      else if(var == "FatJetInfo_Jet_pt") h->Fill(log(FatJetInfo_Jet_SD_chi[j]),FatJetInfo_Jet_pt[j]); //fill 2D histo (chi, dR)
	      else if(var == "GenPruned_pT") h->Fill(log(FatJetInfo_Jet_SD_chi[j]),GenPruned_pT[k]); //fill 2D histo (chi, dR)
	      else if(var == "FatJetInfo_Jet_SD_nBtagMicrojets") h->Fill(log(FatJetInfo_Jet_SD_chi[j]),FatJetInfo_Jet_SD_nBtagMicrojets[j]); //fill 2D histo (chi, dR)
	      else{
		cout << "var not properly defined" << endl;
		return 0;
	      }
	    }
	  }

	  if(display)cout << endl;
	}
      }//end GenPruned loop
      if(nMatch>nMatchMax) nMatchMax = nMatch;
    }//end fatjet loop

    if (nMatch>2) iEventOverMatch.push_back(i);

  }//end event loop

  if(display)cout << "nMatchMax =" << nMatchMax << endl;
  if(display)cout << "nEventOverMatch = " << iEventOverMatch.size() << " (events more than 2 matches)" <<endl;
  if(iEventOverMatch.size()>2){
    if(display)cout << "EventsOverMatch = " ;
    for(int l =0 ; l<iEventOverMatch.size(); l++) if(display)cout << iEventOverMatch[l] <<", " ;
    endl;
  }

  gStyle->SetOptStat("nemrou");
  h->GetXaxis()->SetTitle("Log(#chi)");
  h->GetXaxis()->SetTitleOffset(1.3);
  h->GetYaxis()->SetTitle(var.c_str());
  h->GetYaxis()->SetTitleOffset(1.2);
  h->SetTitle("");
  c->cd();
  //c->SetLogx();
  c->SetBottomMargin(0.12);
  c->SetRightMargin(0.3);
  h->Draw("COLZ");
  c2->cd();
  //c2->SetLogx();
  c2->SetBottomMargin(0.12);
  c2->SetRightMargin(0.3);
  h->Draw("LEGO2Z");

  if(save)c->SaveAs((fdir+"/"+fname+"_"+postfix+"_fjGenParticleMatch_COLZ.eps").c_str());
  if(save)c2->SaveAs((fdir+"/"+fname+"_"+postfix+"_fjGenParticleMatch_LEGO2Z.eps").c_str());

  return h;
}

TH1D* PartonMatch_ProjectX(TH2D* h2, std::string fdir, std::string fname, const string var="log(#chi)", bool save=false, std::string postfix = ""){
  TCanvas *c = new TCanvas("c","c",800,600);
  TH1D *h = h2->ProjectionX();
  c->cd();

  gStyle->SetOptStat("nemrou");
  h->GetXaxis()->SetTitle(var.c_str());
  h->SetLineWidth(2);
  h->SetLineColor(kBlue);
  h->GetXaxis()->SetTitleOffset(1.3);
  h->GetYaxis()->SetTitle("Entries");
  h->SetTitle("");
  h->Draw();

  if(save)c->SaveAs((fdir+"/"+fname+"_"+postfix+"_fjGenParticleMatch_ProjectX.eps").c_str());

  return h;
}

TH1D* PartonMatch_ProjectY(TH2D* h2, std::string fdir, std::string fname, std::string var, bool save=false, std::string postfix = ""){
  TCanvas *c = new TCanvas("c","c",800,600);
  TH1D *h = h2->ProjectionY();
  c->cd();

  gStyle->SetOptStat("nemrou");
  h->GetXaxis()->SetTitle(var.c_str());
  h->SetLineWidth(2);
  h->SetLineColor(kBlue);
  h->GetXaxis()->SetTitleOffset(1.3);
  h->GetYaxis()->SetTitle("Entries");
  h->SetTitle("");
  h->Draw();

  if(save)c->SaveAs((fdir+"/"+fname+"_"+postfix+"_fjGenParticleMatch_ProjectY.eps").c_str());

  return h;
}


double deltaR(double eta1, double phi1, double eta2, double phi2){
  double dEta = eta1 - eta2;

  double dPhi = phi1 - phi2;
  while (dPhi > TMath::Pi()) dPhi -= 2*TMath::Pi();
  while (dPhi <= -TMath::Pi()) dPhi += 2*TMath::Pi();

  double dR = sqrt(dEta*dEta + dPhi*dPhi);
  return dR;
}

void PartonMatch_loose(){

  string dir = "1leadbtagmjcondition";
  string fsig = "RadionToHH_4b_M-800_TuneZ2star_8TeV-Madgraph_pythia6_R12_r15_minPt200_1leadbtagmjcondition_mc_subjets";
  string fbkg = "TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_R12_r15_minPt200_1leadbtagmjcondition_mc_subjets";
  string var;
  //string var = "FatJetInfo_Jet_SD_nBtagMicrojets";

  double dR_tight = 0.05;double dR_med = 0.2;  double dR_loose = 1.2;

  double xbin = 50; double xmin = -22; double xmax = -2;
  double ybin = 50; double ymin = 0; double ymax = 800;

  bool display = true ;
  bool save = false;

  string postfix;

  //loose match
  postfix = "loose_FjPt_GenPtCut200";
  var = "FatJetInfo_Jet_pt";
  //TH2D* h2D_fj_bkg = PartonMatch(dir.c_str(),fbkg.c_str(),var.c_str(),6,dR_loose,xbin,xmin,xmax,ybin,ymin,ymax,display,save,postfix);
  //TH1D* h_fj_bkg = PartonMatch_ProjectY(h2D_fj_bkg,dir.c_str(),fbkg.c_str(),var.c_str(),save,postfix);

  TH2D* h2D_fj_sig = PartonMatch(dir.c_str(),fsig.c_str(),var.c_str(),25,dR_loose,xbin,xmin,xmax,ybin,ymin,ymax,display,save,postfix);
  TH1D* h_fj_sig = PartonMatch_ProjectY(h2D_fj_sig,dir.c_str(),fsig.c_str(),var.c_str(),save,postfix);

  postfix = "loose_GenPt_GenPtCut200";
  var = "GenPruned_pT";
  //TH2D* h2D_gen_bkg = PartonMatch(dir.c_str(),fbkg.c_str(),var.c_str(),6,dR_loose,xbin,xmin,xmax,ybin,ymin,ymax,display,save,postfix);
  //TH1D* h_gen_bkg = PartonMatch_ProjectY(h2D_gen_bkg,dir.c_str(),fbkg.c_str(),var.c_str(),save,postfix);

  TH2D* h2D_gen_sig = PartonMatch(dir.c_str(),fsig.c_str(),var.c_str(),25,dR_loose,xbin,xmin,xmax,ybin,ymin,ymax,display,save,postfix);
  TH1D* h_gen_sig = PartonMatch_ProjectY(h2D_gen_sig,dir.c_str(),fsig.c_str(),var.c_str(),save,postfix);

  TCanvas* canvas = new TCanvas("Matching","Matching",800,600);
  //TCanvas* canvas2 = new TCanvas("After matching","After matching",800,600);

  canvas->cd();

  h_fj_sig->SetLineColor(kBlue);
  h_fj_sig->GetXaxis()->SetTitle("p_{T}");
  h_gen_sig->SetLineColor(kGreen+2);
  h_gen_sig->SetLineStyle(2);

  Double_t norm1;
  Double_t norm2;

  norm1 = h_fj_sig->GetEntries();
  h_fj_sig->Scale(1/norm1);
  norm2 = h_gen_sig->GetEntries();
  h_gen_sig->Scale(1/norm2);

  h_fj_sig->Draw();
  h_gen_sig->Draw("SAMES");

  leg = new TLegend(0.55,0.65,0.75,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h_fj_sig,"Reco Fatjet","L");
  leg->AddEntry(h_gen_sig,"Gen Higgs","L");

  leg->Draw("SAME");

  gPad->Update();

  TPaveStats *tps1 = (TPaveStats*) h_fj_sig->FindObject("stats");
  tps1->SetTextColor(kBlue);
  double X1 = tps1->GetX1NDC();
  double Y1 = tps1->GetY1NDC();
  double X2 = tps1->GetX2NDC();
  double Y2 = tps1->GetY2NDC();

  TPaveStats *tps2 = (TPaveStats*) h_gen_sig->FindObject("stats");
  tps2->SetTextColor(kGreen+2);
  tps2->SetX1NDC(X1);
  tps2->SetX2NDC(X2);
  tps2->SetY1NDC(Y1-(Y2-Y1));
  tps2->SetY2NDC(Y1);

  X1 = tps2->GetX1NDC();
  Y1 = tps2->GetY1NDC();
  X2 = tps2->GetX2NDC();
  Y2 = tps2->GetY2NDC();

  gPad->Update();

  canvas->SaveAs((dir+"/"+fsig+"loose_match_fj_genH_GenPtCut200.eps").c_str());

}

void PartonMatch_med(){

  string dir = "1leadbtagmjcondition";
  string fsig = "RadionToHH_4b_M-800_TuneZ2star_8TeV-Madgraph_pythia6_R12_r15_minPt200_1leadbtagmjcondition_mc_subjets";
  string fbkg = "TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_R12_r15_minPt200_1leadbtagmjcondition_mc_subjets";
  string var;
  //string var = "FatJetInfo_Jet_SD_nBtagMicrojets";

  double dR_tight = 0.05;double dR_med = 0.2;  double dR_loose = 1.2;

  double xbin = 50; double xmin = -22; double xmax = -2;
  double ybin = 50; double ymin = 0; double ymax = 800;

  bool display = true ;
  bool save = false;

  string postfix;

  //med match
  postfix = "med_FjPt_GenPtCut200";
  var = "FatJetInfo_Jet_pt";
  //TH2D* h2D_fj_bkg = PartonMatch(dir.c_str(),fbkg.c_str(),var.c_str(),6,dR_med,xbin,xmin,xmax,ybin,ymin,ymax,display,save,postfix);
  //TH1D* h_fj_bkg = PartonMatch_ProjectY(h2D_fj_bkg,dir.c_str(),fbkg.c_str(),var.c_str(),save,postfix);

  TH2D* h2D_fj_sig = PartonMatch(dir.c_str(),fsig.c_str(),var.c_str(),25,dR_med,xbin,xmin,xmax,ybin,ymin,ymax,display,save,postfix);
  TH1D* h_fj_sig = PartonMatch_ProjectY(h2D_fj_sig,dir.c_str(),fsig.c_str(),var.c_str(),save,postfix);

  postfix = "med_GenPt_GenPtCut200";
  var = "GenPruned_pT";
  //TH2D* h2D_gen_bkg = PartonMatch(dir.c_str(),fbkg.c_str(),var.c_str(),6,dR_med,xbin,xmin,xmax,ybin,ymin,ymax,display,save,postfix);
  //TH1D* h_gen_bkg = PartonMatch_ProjectY(h2D_gen_bkg,dir.c_str(),fbkg.c_str(),var.c_str(),save,postfix);

  TH2D* h2D_gen_sig = PartonMatch(dir.c_str(),fsig.c_str(),var.c_str(),25,dR_med,xbin,xmin,xmax,ybin,ymin,ymax,display,save,postfix);
  TH1D* h_gen_sig = PartonMatch_ProjectY(h2D_gen_sig,dir.c_str(),fsig.c_str(),var.c_str(),save,postfix);

  TCanvas* canvas = new TCanvas("Matching","Matching",800,600);
  //TCanvas* canvas2 = new TCanvas("After matching","After matching",800,600);

  canvas->cd();

  h_fj_sig->SetLineColor(kBlue);
  h_fj_sig->GetXaxis()->SetTitle("p_{T}");
  h_gen_sig->SetLineColor(kGreen+2);
  h_gen_sig->SetLineStyle(2);

  Double_t norm1;
  Double_t norm2;

  norm1 = h_fj_sig->GetEntries();
  h_fj_sig->Scale(1/norm1);
  norm2 = h_gen_sig->GetEntries();
  h_gen_sig->Scale(1/norm2);

  h_fj_sig->Draw();
  h_gen_sig->Draw("SAMES");

  leg = new TLegend(0.55,0.65,0.75,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h_fj_sig,"Reco Fatjet","L");
  leg->AddEntry(h_gen_sig,"Gen Higgs","L");

  leg->Draw("SAME");

  gPad->Update();

  TPaveStats *tps1 = (TPaveStats*) h_fj_sig->FindObject("stats");
  tps1->SetTextColor(kBlue);
  double X1 = tps1->GetX1NDC();
  double Y1 = tps1->GetY1NDC();
  double X2 = tps1->GetX2NDC();
  double Y2 = tps1->GetY2NDC();

  TPaveStats *tps2 = (TPaveStats*) h_gen_sig->FindObject("stats");
  tps2->SetTextColor(kGreen+2);
  tps2->SetX1NDC(X1);
  tps2->SetX2NDC(X2);
  tps2->SetY1NDC(Y1-(Y2-Y1));
  tps2->SetY2NDC(Y1);

  X1 = tps2->GetX1NDC();
  Y1 = tps2->GetY1NDC();
  X2 = tps2->GetX2NDC();
  Y2 = tps2->GetY2NDC();

  gPad->Update();

  canvas->SaveAs((dir+"/"+fsig+"med_match_fj_genH_GenPtCut200.eps").c_str());

}

void PartonMatch_tight(){

  string dir = "1leadbtagmjcondition";
  string fsig = "RadionToHH_4b_M-800_TuneZ2star_8TeV-Madgraph_pythia6_R12_r15_minPt200_1leadbtagmjcondition_mc_subjets";
  string fbkg = "TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_R12_r15_minPt200_1leadbtagmjcondition_mc_subjets";
  string var;
  //string var = "FatJetInfo_Jet_SD_nBtagMicrojets";

  double dR_tight = 0.05;double dR_med = 0.2;  double dR_loose = 1.2;

  double xbin = 50; double xmin = -22; double xmax = -2;
  double ybin = 50; double ymin = 0; double ymax = 800;

  bool display = true ;
  bool save = false;

  string postfix;

  //tight match
  postfix = "tight_FjPt_GenPtCut200";
  var = "FatJetInfo_Jet_pt";
  //TH2D* h2D_fj_bkg = PartonMatch(dir.c_str(),fbkg.c_str(),var.c_str(),6,dR_tight,xbin,xmin,xmax,ybin,ymin,ymax,display,save,postfix);
  //TH1D* h_fj_bkg = PartonMatch_ProjectY(h2D_fj_bkg,dir.c_str(),fbkg.c_str(),var.c_str(),save,postfix);

  TH2D* h2D_fj_sig = PartonMatch(dir.c_str(),fsig.c_str(),var.c_str(),25,dR_tight,xbin,xmin,xmax,ybin,ymin,ymax,display,save,postfix);
  TH1D* h_fj_sig = PartonMatch_ProjectY(h2D_fj_sig,dir.c_str(),fsig.c_str(),var.c_str(),save,postfix);

  postfix = "tight_GenPt_GenPtCut200";
  var = "GenPruned_pT";
  //TH2D* h2D_gen_bkg = PartonMatch(dir.c_str(),fbkg.c_str(),var.c_str(),6,dR_tight,xbin,xmin,xmax,ybin,ymin,ymax,display,save,postfix);
  //TH1D* h_gen_bkg = PartonMatch_ProjectY(h2D_gen_bkg,dir.c_str(),fbkg.c_str(),var.c_str(),save,postfix);

  TH2D* h2D_gen_sig = PartonMatch(dir.c_str(),fsig.c_str(),var.c_str(),25,dR_tight,xbin,xmin,xmax,ybin,ymin,ymax,display,save,postfix);
  TH1D* h_gen_sig = PartonMatch_ProjectY(h2D_gen_sig,dir.c_str(),fsig.c_str(),var.c_str(),save,postfix);

  TCanvas* canvas = new TCanvas("Matching","Matching",800,600);
  //TCanvas* canvas2 = new TCanvas("After matching","After matching",800,600);

  canvas->cd();

  h_fj_sig->SetLineColor(kBlue);
  h_fj_sig->GetXaxis()->SetTitle("p_{T}");
  h_gen_sig->SetLineColor(kGreen+2);
  h_gen_sig->SetLineStyle(2);

  Double_t norm1;
  Double_t norm2;

  norm1 = h_fj_sig->GetEntries();
  h_fj_sig->Scale(1/norm1);
  norm2 = h_gen_sig->GetEntries();
  h_gen_sig->Scale(1/norm2);

  h_fj_sig->Draw();
  h_gen_sig->Draw("SAMES");

  leg = new TLegend(0.55,0.65,0.75,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h_fj_sig,"Reco Fatjet","L");
  leg->AddEntry(h_gen_sig,"Gen Higgs","L");

  leg->Draw("SAME");

  gPad->Update();

  TPaveStats *tps1 = (TPaveStats*) h_fj_sig->FindObject("stats");
  tps1->SetTextColor(kBlue);
  double X1 = tps1->GetX1NDC();
  double Y1 = tps1->GetY1NDC();
  double X2 = tps1->GetX2NDC();
  double Y2 = tps1->GetY2NDC();

  TPaveStats *tps2 = (TPaveStats*) h_gen_sig->FindObject("stats");
  tps2->SetTextColor(kGreen+2);
  tps2->SetX1NDC(X1);
  tps2->SetX2NDC(X2);
  tps2->SetY1NDC(Y1-(Y2-Y1));
  tps2->SetY2NDC(Y1);

  X1 = tps2->GetX1NDC();
  Y1 = tps2->GetY1NDC();
  X2 = tps2->GetX2NDC();
  Y2 = tps2->GetY2NDC();

  gPad->Update();

  canvas->SaveAs((dir+"/"+fsig+"_tight_match_fj_genH_GenPtCut200.eps").c_str());

}

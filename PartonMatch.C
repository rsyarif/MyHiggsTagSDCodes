
using namespace std;

TH2D* PartonMatch(std::string fdir, std::string fname, std::string var = "dR", int gen_pdgid,double dRmax = 1.2, int xbin =50, double xmin = -18, double xmax = -2, int ybin = 50, double ymin =0, double ymax =0.6,bool display=false, bool save=false, std::string postfix = ""){

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
	    //Determine Cuts conditions
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

  if(save)c->SaveAs((fdir+"/"+fname+"_"+postfix+"_fjGenPartilcleMatch_COLZ.eps").c_str());
  if(save)c2->SaveAs((fdir+"/"+fname+"_"+postfix+"_fjGenParticleMatch_LEGO2Z.eps").c_str());

  return h;
}

TH1D* PartonMatch_ProjectX(TH2D* h2, std::string fdir, std::string fname, bool save=false, std::string postfix = ""){
  TCanvas *c3 = new TCanvas("c3","c3",800,600);
  TH1D *h = h2->ProjectionX();
  c3->cd();

  gStyle->SetOptStat("nemrou");
  h->GetXaxis()->SetTitle("Log(#chi)");
  h->SetLineWidth(2);
  h->SetLineColor(kBlue);
  h->GetXaxis()->SetTitleOffset(1.3);
  h->GetYaxis()->SetTitle("Entries");
  h->SetTitle("");
  h->Draw();

  if(save)c3->SaveAs((fdir+"/"+fname+"_"+postfix+"_fjGenParticleMatch_ProjectX.eps").c_str());

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

void PartonMatch(){
  string dir = "1leadbtagmjcondition";
  string fsig = "RadionToHH_4b_M-800_TuneZ2star_8TeV-Madgraph_pythia6_R12_r15_minPt200_1leadbtagmjcondition_mc_subjets";
  string fbkg = "TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_R12_r15_minPt200_1leadbtagmjcondition_mc_subjets";
  string var = "dR";

  double dR_tight = 0.05;double dR_med = 0.2;  double dR_loose = 1.2;

  double xbin = 40; double xmin = -18; double xmax = -2;
  double ybin = 40; double ymin = 0; double ymax = 800;

  bool display = false ;
  bool save = false;

  string postfix;

  //loose match
  TH2D* h2_bkg_l = PartonMatch(dir,fbkg,var,6,dR_loose,xbin,xmin,xmax,ybin,ymin,ymax,display,save,"dRmax12");
  TH1D* h_bkg_l = PartonMatch_ProjectX(h2_bkg_l,dir,fbkg,save,"dRmax12");

  TH2D* h2_sig_l = PartonMatch(dir,fsig,var,25,dR_loose,xbin,xmin,xmax,ybin,ymin,ymax,display,save,"dRmax12");
  TH1D* h_sig_l = PartonMatch_ProjectX(h2_sig_l,dir,fsig,save,"dRmax12");

  //med match
  TH2D* h2_bkg_m = PartonMatch(dir,fbkg,var,6,dR_med,xbin,xmin,xmax,ybin,ymin,ymax,display,save,"dRmax02");
  TH1D* h_bkg_m = PartonMatch_ProjectX(h2_bkg_m,dir,fbkg,save,"dRmax02");

  TH2D* h2_sig_m = PartonMatch(dir,fsig,var,25,dR_med,xbin,xmin,xmax,ybin,ymin,ymax,display,save,"dRmax02");
  TH1D* h_sig_m = PartonMatch_ProjectX(h2_sig_m,dir,fsig,save,"dRmax02");

  //tight match
  TH2D* h2_bkg_t = PartonMatch(dir,fbkg,var,6,dR_tight,xbin,xmin,xmax,ybin,ymin,ymax,display,save,"dRmax005");
  TH1D* h_bkg_t = PartonMatch_ProjectX(h2_bkg_t,dir,fbkg,save,"dRmax005");

  TH2D* h2_sig_t = PartonMatch(dir,fsig,var,25,dR_tight,xbin,xmin,xmax,ybin,ymin,ymax,display,save,"dRmax005");
  TH1D* h_sig_t = PartonMatch_ProjectX(h2_sig_t,dir,fsig,save,"dRmax005");

  TCanvas* canvas = new TCanvas("loose matching","loose matching",800,600);
  TCanvas* canvas2 = new TCanvas("med matching","med matching",800,600);
  TCanvas* canvas3 = new TCanvas("tight matching","tight matching",800,600);
  TCanvas* canvas4 = new TCanvas("sig matching","sig matching",800,600);
  TCanvas* canvas5 = new TCanvas("bkg matching","bkg matching",800,600);

  canvas->cd();

  h_sig_l->SetStats(0);
  h_bkg_l->SetStats(0);
  h_sig_l->SetLineColor(kBlue);
  h_bkg_l->SetLineColor(kRed);
  //h->GetXaxis()->SetTitleOffset(1.3);
  //h->GetYaxis()->SetTitle("Entries");
  //h->SetTitle("");
  Double_t norm1;
  Double_t norm2;

  norm1 = h_sig_l->GetEntries();
  h_sig_l->Scale(1/norm1);
  norm2 = h_bkg_l->GetEntries();
  h_bkg_l->Scale(1/norm2);

  h_sig_l->Draw();
  h_bkg_l->Draw("SAME");

  gPad->Update();

  canvas->SaveAs("1leadbtagmjcondition/loose_match.eps");

  canvas2->cd();

  h_sig_m->SetStats(0);
  h_bkg_m->SetStats(0);
  h_sig_m->SetLineColor(kBlue);
  h_bkg_m->SetLineColor(kRed);

  norm1 = h_sig_m->GetEntries();
  h_sig_m->Scale(1/norm1);
  norm2 = h_bkg_m->GetEntries();
  h_bkg_m->Scale(1/norm2);

  h_sig_m->Draw();
  h_bkg_m->Draw("SAME");

  gPad->Update();

  canvas2->SaveAs("1leadbtagmjcondition/medium_match.eps");

  canvas3->cd();

  h_sig_t->SetStats(0);
  h_bkg_t->SetStats(0);
  h_sig_t->SetLineColor(kBlue);
  h_bkg_t->SetLineColor(kRed);

  norm1 = h_sig_t->GetEntries();
  h_sig_t->Scale(1/norm1);
  norm2 = h_bkg_t->GetEntries();
  h_bkg_t->Scale(1/norm2);

  h_sig_t->Draw();
  h_bkg_t->Draw("SAME");

  gPad->Update();

  canvas3->SaveAs("1leadbtagmjcondition/tight_match.eps");

  canvas4->cd();

  h_sig_l->SetLineStyle(9);
  h_sig_m->SetLineStyle(2);
  h_sig_t->SetLineStyle(1);

  h_sig_l->SetLineWidth(3);

  h_sig_l->SetLineColor(kRed);
  h_sig_m->SetLineColor(kYellow+2);
  h_sig_t->SetLineColor(kGreen+2);

  h_sig_t->Draw();
  h_sig_m->Draw("SAME");
  h_sig_l->Draw("SAME");

  gPad->Update();

  canvas4->SaveAs("1leadbtagmjcondition/sig_match.eps");

  canvas5->cd();

  h_bkg_l->SetLineStyle(9);
  h_bkg_m->SetLineStyle(2);
  h_bkg_t->SetLineStyle(1);

  h_bkg_l->SetLineWidth(3);

  h_bkg_l->SetLineColor(kRed);
  h_bkg_m->SetLineColor(kYellow+2);
  h_bkg_t->SetLineColor(kGreen+2);

  h_bkg_l->Draw();
  h_bkg_m->Draw("SAME");
  h_bkg_t->Draw("SAME");

  gPad->Update();

  canvas5->SaveAs("1leadbtagmjcondition/bkg_match.eps");

}


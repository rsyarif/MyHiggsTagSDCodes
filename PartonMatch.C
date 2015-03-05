
using namespace std;

TH2D* PartonMatch(std::string fdir, std::string fname, int gen_pdgid,double dRmax = 1.2, int xbin =50, double xmin = -18, double xmax = -2, int ybin = 50, double ymin =0, double ymax =0.6,bool display=false, bool save=false, std::string postfix = ""){

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

  int nFj;
  const int nFjMax=5;
  float Fj_eta[nFjMax];
  float Fj_phi[nFjMax];
  float Fj_chi[nFjMax];
  float Fj_pt[nFjMax];
  int Fj_nbMj[nFjMax];
  //int Fj_isleadMjbtag[nFjMax];

  t->SetBranchAddress("nGenPruned",&nGenPruned);
  t->SetBranchAddress("GenPruned_pdgID",&GenPruned_pdgID);
  t->SetBranchAddress("GenPruned_eta",&GenPruned_eta);
  t->SetBranchAddress("GenPruned_phi",&GenPruned_phi);
  t->SetBranchAddress("GenPruned_pT",&GenPruned_pT);

  tf->SetBranchAddress("FatJetInfo.nJet",&nFj);
  tf->SetBranchAddress("FatJetInfo.Jet_eta",&Fj_eta);
  tf->SetBranchAddress("FatJetInfo.Jet_phi",&Fj_phi);
  tf->SetBranchAddress("FatJetInfo.Jet_SD_chi",&Fj_chi);
  tf->SetBranchAddress("FatJetInfo.Jet_pt",&Fj_pt);
  tf->SetBranchAddress("FatJetInfo.Jet_SD_nBtagMicrojets",&Fj_nbMj);
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
    if(display)cout << "============  entry : "<< i << ", nGenPruned = "<< nGenPruned << ", nFatJet = "<< nFj <<"=============="<< endl;
    if(display)cout << endl;

    //loop over fatjets
    int nMatch=0;
    for(int j=0; j < nFj; j++){
      if(display)cout<< "Fatjet no. "<< j << " : Fatjet_eta = " << Fj_eta[j] << endl;
      if(display)cout<< "           "<<     "    Fatjet_phi = " << Fj_phi[j] << endl;
      if(display)cout<< "           "<<     "    Fatjet_chi = " << Fj_chi[j] << endl;
      if(display)cout<<endl;

      //loop over GenPruned
      for(int k=2; k < nGenPruned; k++){
	if(GenPruned_pdgID[k]==gen_pdgid){
	  if(display)cout<< "        GenPruned no. "<< k << " : GenPruned_pdgID = " << GenPruned_pdgID[k] << endl;
	  if(display)cout<< "                      "<<     "    GenPruned_eta = " << GenPruned_eta[k] << endl;
	  if(display)cout<< "                      "<<     "    GenPruned_phi = " << GenPruned_phi[k] << endl;

	  double dR = deltaR(GenPruned_eta[k], GenPruned_phi[k], Fj_eta[j], Fj_phi[j]);
	  if(display)cout<< "        " << j<< "-"<<k<<", -------------------------------->  delta R = "<< dR ;// << endl;
	  if(dR<dRmax){
	    if(display)cout<<"----> MATCH!! " << endl;
	    nMatch++;
	    //Determine Cuts conditions
	    if(Fj_chi[j]>0 && GenPruned_pT[k]>200) h->Fill(log(Fj_chi[j]),dR); //fill 2D histo (chi, dR)

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
  h->GetYaxis()->SetTitle("#DeltaR");
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
  //loose match
  TH2D* h2_bkg = PartonMatch("1leadbtagmjcondition","TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_R12_r15_minPt200_1leadbtagmjcondition_mc_subjets",6,1.2,50,-18,-2,50,0,1.2,false,true,"dRmax12");
  TH1D* h_bkg = PartonMatch_ProjectX(h2_bkg,"1leadbtagmjcondition","TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_R12_r15_minPt200_1leadbtagmjcondition_mc_subjets",true,"dRmax12");

TH2D* h2_sig = PartonMatch("1leadbtagmjcondition","RadionToHH_4b_M-800_TuneZ2star_8TeV-Madgraph_pythia6_R12_r15_minPt200_1leadbtagmjcondition_mc_subjets",25,1.2,50,-18,-2,50,0,1.2,false,true,"dRmax12");
  TH1D* h_sig = PartonMatch_ProjectX(h2_sig,"1leadbtagmjcondition","RadionToHH_4b_M-800_TuneZ2star_8TeV-Madgraph_pythia6_R12_r15_minPt200_1leadbtagmjcondition_mc_subjets",true,"dRmax12");

  //tight match
  TH2D* h2_bkg2 = PartonMatch("1leadbtagmjcondition","TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_R12_r15_minPt200_1leadbtagmjcondition_mc_subjets",6,0.2,40,-18,-2,40,0,0.2,false,true,"dRmax02");
  TH1D* h_bkg2 = PartonMatch_ProjectX(h2_bkg2,"1leadbtagmjcondition","TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_R12_r15_minPt200_1leadbtagmjcondition_mc_subjets",true,"dRmax02");

TH2D* h2_sig2 = PartonMatch("1leadbtagmjcondition","RadionToHH_4b_M-800_TuneZ2star_8TeV-Madgraph_pythia6_R12_r15_minPt200_1leadbtagmjcondition_mc_subjets",25,0.05,40,-18,-2,40,0,0.1,false,true,"dRmax005");
  TH1D* h_sig2 = PartonMatch_ProjectX(h2_sig2,"1leadbtagmjcondition","RadionToHH_4b_M-800_TuneZ2star_8TeV-Madgraph_pythia6_R12_r15_minPt200_1leadbtagmjcondition_mc_subjets",true,"dRmax005");

  TCanvas* canvas = new TCanvas("B4 matching","B4 matching",800,600);
  TCanvas* canvas2 = new TCanvas("After matching","After matching",800,600);

  canvas->cd();

  h_sig->SetStats(0);
  h_bkg->SetStats(0);
  h_sig->SetLineColor(kBlue);
  h_bkg->SetLineColor(kRed);
  //h->GetXaxis()->SetTitleOffset(1.3);
  //h->GetYaxis()->SetTitle("Entries");
  //h->SetTitle("");
  Double_t norm1;
  Double_t norm2;

  norm1 = h_sig->GetEntries();
  h_sig->Scale(1/norm1);
  norm2 = h_bkg2->GetEntries();
  h_bkg->Scale(1/norm2);

  h_bkg->Draw();
  h_sig->Draw("SAME");

  gPad->Update();

  canvas->SaveAs("1leadbtagmjcondition/loose_match.eps");

  canvas2->cd();

  h_sig2->SetStats(0);
  h_bkg2->SetStats(0);
  h_sig2->SetLineColor(kBlue);
  h_bkg2->SetLineColor(kRed);

  norm1 = h_sig2->GetEntries();
  h_sig2->Scale(1/norm1);
  norm2 = h_bkg2->GetEntries();
  h_bkg2->Scale(1/norm2);

  h_sig2->Draw();
  h_bkg2->Draw("SAME");

  gPad->Update();

  canvas2->SaveAs("1leadbtagmjcondition/tight_match.eps");

}


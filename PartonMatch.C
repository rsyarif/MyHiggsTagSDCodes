
using namespace std;

int PartonMatch(std::string fdir, std::string fname, int gen_pdgid,double dRmax = 1.2,bool display=false, std::string postfix = ""){

  TFile *f = new TFile((fdir+"/"+fname+".root").c_str());

  TDirectoryFile *d = f->GetDirectory("btagana");
  TTree *t = d->Get("ttree");
  TDirectoryFile *df = f->GetDirectory("btaganaSubJets");
  TTree *tf = df->Get("ttree");

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

  float dR_match;
  float Fj_chi;
  float Fj_pt;
  float gen_pt;
  int Fj_nBtagMj;
  cout<<"Creating new root file containing Fatjet based tree: "<< fdir+"/"+"fMatch_"+fname+"_"+postfix+".root" << endl;
  TFile *fMatch = new TFile((fdir+"/"+"fMatch_"+fname+"_"+postfix+".root").c_str(),"RECREATE"); //DIFFERENCE BETWEEN USING POINTER???
  TTree *tr_new = new TTree("tree","tree");
  tr_new->Branch("dR_match",&dR_match,"dR_match/F");
  tr_new->Branch("Fj_chi",&Fj_chi,"Fj_chi/F");
  tr_new->Branch("Fj_pt",&Fj_pt,"Fj_pt/F");
  tr_new->Branch("gen_pt",&gen_pt,"gen_pt/F");
  tr_new->Branch("Fj_nBtagMj",&Fj_nBtagMj,"Fj_nBtagMj/I");

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
	    //----Determine Cuts conditions---- sync with postfix !!!
	    //if(GenPruned_pT[k]<=200)continue;
	    //if(FatJetInfo_Jet_SD_chi[j]<=0){
	    //if(FatJetInfo_Jet_SD_chi[j]>0){
	    //if(FatJetInfo_Jet_SD_chi[j]>0 && FatJetInfo_Jet_pt[j]>200){

	      dR_match = dR;
	      Fj_chi = FatJetInfo_Jet_SD_chi[j];
	      gen_pt = GenPruned_pT[k];
	      Fj_pt = FatJetInfo_Jet_pt[j];
	      Fj_nBtagMj = FatJetInfo_Jet_SD_nBtagMicrojets[j];
	      tr_new->Fill();

	    //}
	  }//end if dR requirement
	}//end if pdgid

	if(display)cout << endl;

      }//end GenPruned loop
      if(nMatch>nMatchMax) nMatchMax = nMatch;
    }//end fatjet loop
    if (nMatch>2) iEventOverMatch.push_back(i); //max 2 matches because there are 2 Higgs from RadionHH (so this is sample dependent!)

  }//end event loop
  tr_new->Print();
  fMatch->cd();
  tr_new->Write();


  if(display)cout << "nMatchMax =" << nMatchMax << endl;
  if(display)cout << "nEventOverMatch = " << iEventOverMatch.size() << " (events more than 2 matches)" <<endl;
  if(iEventOverMatch.size()>2){
    if(display)cout << "EventsOverMatch = " ;
    for(int l =0 ; l<iEventOverMatch.size(); l++) if(display)cout << iEventOverMatch[l] <<", " ;
    endl;
  }

  int tsize = tr_new->GetEntries();
  cout<<tsize<<endl;

  fMatch->Close();
  f->Close();

  return tsize;

}
TH2D* PartonMatch_2D(TFile* f, std::string yvar, double xbin, double xmin, double xmax, double ybin, double ymin, double ymax,std::string postfix){

  //TFile *f = new TFile((dir+"/"+"fMatch_"+fname+"_"+postfix+".root").c_str()); //must match fMatch name
  TTree *t = f->Get("tree");

  float dR_match;
  float Fj_chi;
  float Fj_pt;
  float gen_pt;
  int Fj_nBtagMj;

  t->SetBranchAddress("dR_match",&dR_match);
  t->SetBranchAddress("Fj_chi",&Fj_chi);
  t->SetBranchAddress("Fj_pt",&Fj_pt);
  t->SetBranchAddress("gen_pt",&gen_pt);
  t->SetBranchAddress("Fj_nBtagMj",&Fj_nBtagMj);

  TH2D* h2 = new TH2D("h2","h2",xbin,xmin,xmax,ybin,ymin,ymax);
  for(int i=0;i<t->GetEntries();i++){
    t->GetEntry(i);
    if(yvar=="dR_match")h2->Fill(log(Fj_chi),dR_match);
    else if(yvar=="Fj_pt")h2->Fill(log(Fj_chi),Fj_pt);
    else if(yvar=="gen_pt")h2->Fill(log(Fj_chi),gen_pt);
    else if(yvar=="Fj_nBtagMj")h2->Fill(log(Fj_chi),Fj_nBtagMj);
    else{
      cout<<"Invalid yvar value!"<<endl;
      return 0;
    }
  }
  h2->GetXaxis()->SetTitle("log(#chi)");

  //f->Close();
  delete t;
  return h2;
}


TH1D* PartonMatch_1D(std::string dir, TFile* f, std::string fname,  std::string var, std::string cut,  double xbin, double xmin, double xmax, std::string postfix, Color_t color = kBlue, int linestyle = 1,bool save = false){

  TCanvas* cvs = new TCanvas((var+cut+postfix).c_str(),(var+cut+postfix).c_str(),800,600);

  TTree *t = f->Get("tree");
  TH1D* h = new TH1D ((var+cut+postfix).c_str(),(var+cut+postfix).c_str(),xbin,xmin,xmax);
  t->Draw((var+">>"+var+cut+postfix).c_str(),cut.c_str());

  gStyle->SetOptStat("nemrou");

  h->SetLineWidth(2);
  h->SetLineColor(color);
  h->SetLineStyle(linestyle);
  h->GetXaxis()->SetTitle(var.c_str());
  h->SetTitle("");

  delete t;

  if(var=="log(Fj_chi)")var = "logChi";
  if(save)cvs->SaveAs((dir+"/"+fname+"_"+var+"_"+cut+".eps").c_str());

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

void PartonMatch(bool display = false){
  string dir = "allChi_noMinFatjetPt_noMjBtagCondition";
  string fsig = "RadionToHH_4b_M-800_TuneZ2star_8TeV-Madgraph_pythia6_R12_r15_minPt0_Nobtagmjcondition_AllChi_mc_subjets";
  string fbkg = "ZPrimeToTTJets_M1000GeV_W10GeV_TuneZ2star_8TeV-madgraph-tauola_R12_r15_minPt0_Nobtagmjcondition_AllChi_mc_subjets";
  double dRmax = 1.2;
  string postfix= "dRmax12_NoGenPtCut_NoFjPtCut_AllChi";
  int sig_l = PartonMatch(dir,fsig,25,dRmax,display,postfix);
  int bkg_l = PartonMatch(dir,fbkg,6,dRmax,display,postfix);
}


void makeHistos(bool save = false, bool display = false){
  //string dir = "1leadbtagmjcondition";
  //string fsig = "RadionToHH_4b_M-800_TuneZ2star_8TeV-Madgraph_pythia6_R12_r15_minPt200_1leadbtagmjcondition_mc_subjets";
  //string fbkg = "TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_R12_r15_minPt200_1leadbtagmjcondition_mc_subjets";

  string dir = "allChi_noMinFatjetPt_noMjBtagCondition";
  string fsig = "RadionToHH_4b_M-800_TuneZ2star_8TeV-Madgraph_pythia6_R12_r15_minPt0_Nobtagmjcondition_AllChi_mc_subjets";
  string fbkg = "ZPrimeToTTJets_M1000GeV_W10GeV_TuneZ2star_8TeV-madgraph-tauola_R12_r15_minPt0_Nobtagmjcondition_AllChi_mc_subjets";

  string var = "dR_match";

  double dR_tight = 0.05;double dR_med = 0.2;  double dR_loose = 1.2;

  double xbin = 40; double xmin = -18; double xmax = -2;
  double ybin = 40; double ymin = 0; double ymax = 1.2;

  //bool display = false ;
  //bool save = false;

  string postfix;

  //loose match
  postfix = "dRmax12";
  TFile *f_sig_l = new TFile((dir+"/"+"fMatch_"+fsig+"_"+postfix+".root").c_str());
  TH2D* h2_sig_l = PartonMatch_2D(dir,f_sig_l,var,xbin,xmin,xmax,ybin,ymin,1.2,"dRmax12");
  TH1D* h_sig_l = PartonMatch_1D(dir,f_sig_l,fsig,"log(Fj_chi)",xbin,xmin,xmax,"dRmax12");

  TFile *f_bkg_l = new TFile((dir+"/"+"fMatch_"+fbkg+"_"+postfix+".root").c_str());
  TH2D* h2_bkg_l = PartonMatch_2D(dir,f_bkg_l,var,xbin,xmin,xmax,ybin,ymin,1.2,"dRmax12");
  TH1D* h_bkg_l = PartonMatch_1D(dir,f_bkg_l,fbkg,"log(Fj_chi)",xbin,xmin,xmax,"dRmax12");

  //med match
  postfix = "dRmax02";
  TFile *f_sig_m = new TFile((dir+"/"+"fMatch_"+fsig+"_"+postfix+".root").c_str());
  TH2D* h2_sig_m = PartonMatch_2D(dir,f_sig_m,var,xbin,xmin,xmax,ybin,ymin,0.2,"dRmax02");
  TH1D* h_sig_m = PartonMatch_1D(dir,f_sig_m,fsig,"log(Fj_chi)",xbin,xmin,xmax,"dRmax02");

  TFile *f_bkg_m = new TFile((dir+"/"+"fMatch_"+fbkg+"_"+postfix+".root").c_str());
  TH2D* h2_bkg_m = PartonMatch_2D(dir,f_bkg_m,var,xbin,xmin,xmax,ybin,ymin,0.2,"dRmax02");
  TH1D* h_bkg_m = PartonMatch_1D(dir,f_bkg_m,fbkg,"log(Fj_chi)",xbin,xmin,xmax,"dRmax02");

  //tight match
  postfix = "dRmax005";
  TFile *f_sig_t = new TFile((dir+"/"+"fMatch_"+fsig+"_"+postfix+".root").c_str());
  TH2D* h2_sig_t = PartonMatch_2D(dir,f_sig_t,var,xbin,xmin,xmax,ybin,ymin,0.05,"dRmax005");
  TH1D* h_sig_t = PartonMatch_1D(dir,f_sig_t,fsig,"log(Fj_chi)",xbin,xmin,xmax,"dRmax005");

  TFile *f_bkg_t = new TFile((dir+"/"+"fMatch_"+fbkg+"_"+postfix+".root").c_str());
  TH2D* h2_bkg_t = PartonMatch_2D(dir,f_bkg_t,var,xbin,xmin,xmax,ybin,ymin,0.05,"dRmax005");
  TH1D* h_bkg_t = PartonMatch_1D(dir,f_bkg_t,fbkg,"log(Fj_chi)",xbin,xmin,xmax,"dRmax005");


  TCanvas* canvas = new TCanvas("loose matching","loose matching",800,600);
  TCanvas* canvas2 = new TCanvas("med matching","med matching",800,600);
  TCanvas* canvas3 = new TCanvas("tight matching","tight matching",800,600);
  TCanvas* canvas4 = new TCanvas("sig matching","sig matching",800,600);
  TCanvas* canvas5 = new TCanvas("bkg matching","bkg matching",800,600);

  cout<<"Creating "<< dir+"/"+"PartonMatch_histos.root"<< endl;
  TFile *fhistos = new TFile((dir+"/"+"PartonMatch_histos.root").c_str(),"RECREATE");
  //TFile *fhistos = new TFile("TEMP_PartonMatch_histos.root","RECREATE");

  h_sig_l->SetStats(1);
  h_sig_m->SetStats(1);
  h_sig_t->SetStats(1);

  h_bkg_l->SetStats(1);
  h_bkg_m->SetStats(1);
  h_bkg_t->SetStats(1);

  gStyle->SetOptStat("nemrou");
  gPad->Update();

  fhistos->cd();
  h2_sig_l->Write("h2_sig_l");
  h2_sig_m->Write("h2_sig_m");
  h2_sig_t->Write("h2_sig_t");

  h_sig_l->Write("h_sig_l");
  h_sig_m->Write("h_sig_m");
  h_sig_t->Write("h_sig_t");

  h2_bkg_l->Write("h2_bkg_l");
  h2_bkg_m->Write("h2_bkg_m");
  h2_bkg_t->Write("h2_bkg_t");

  h_bkg_l->Write("h_bkg_l");
  h_bkg_m->Write("h_bkg_m");
  h_bkg_t->Write("h_bkg_t");

  canvas->cd();

  h_sig_l->SetStats(0);
  h_bkg_l->SetStats(0);
  h_sig_l->SetLineColor(kBlue);
  h_bkg_l->SetLineColor(kRed);

  h_sig_l->DrawNormalized();
  h_bkg_l->DrawNormalized("SAME");

  leg = new TLegend(0.75,0.65,0.95,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h_sig_l,"Radion","L");
  leg->AddEntry(h_bkg_l,"ttjets","L");
  leg->Draw("SAME");

  gPad->Update();

  canvas->SaveAs((dir+"/loose_match.eps").c_str());
  canvas->Write();

  canvas2->cd();

  h_sig_m->SetStats(0);
  h_bkg_m->SetStats(0);
  h_sig_m->SetLineColor(kBlue);
  h_bkg_m->SetLineColor(kRed);

  h_sig_m->DrawNormalized();
  h_bkg_m->DrawNormalized("SAME");

  leg2 = new TLegend(0.75,0.65,0.95,0.85);
  leg2->SetFillStyle(0);
  leg2->SetBorderSize(0);
  leg2->AddEntry(h_sig_m,"Radion","L");
  leg2->AddEntry(h_bkg_m,"ttjets","L");
  leg2->Draw("SAME");

  gPad->Update();

  canvas2->SaveAs((dir+"/medium_match.eps").c_str());
  canvas2->Write();

  canvas3->cd();

  h_sig_t->SetStats(0);
  h_bkg_t->SetStats(0);
  h_sig_t->SetLineColor(kBlue);
  h_bkg_t->SetLineColor(kRed);

  h_sig_t->DrawNormalized();
  h_bkg_t->DrawNormalized("SAME");

  gPad->Update();

  leg3 = new TLegend(0.75,0.65,0.95,0.85);
  leg3->SetFillStyle(0);
  leg3->SetBorderSize(0);
  leg3->AddEntry(h_sig_t,"Radion","L");
  leg3->AddEntry(h_bkg_t,"ttjets","L");
  leg3->Draw("SAME");

  canvas3->SaveAs((dir+"/tight_match.eps").c_str());
  canvas3->Write();

  canvas4->cd();

  h_sig_l->SetLineStyle(9);
  h_sig_m->SetLineStyle(2);
  h_sig_t->SetLineStyle(1);

  h_sig_l->SetLineWidth(3);

  h_sig_l->SetLineColor(kRed);
  h_sig_m->SetLineColor(kYellow+2);
  h_sig_t->SetLineColor(kGreen+2);

  h_sig_t->DrawNormalized();
  h_sig_m->DrawNormalized("SAME");
  h_sig_l->DrawNormalized("SAME");

  leg4 = new TLegend(0.75,0.65,0.95,0.85);
  leg4->SetFillStyle(0);
  leg4->SetBorderSize(0);
  leg4->AddEntry(h_sig_l,"loose","L");
  leg4->AddEntry(h_sig_m,"medium","L");
  leg4->AddEntry(h_sig_t,"tight","L");
  leg4->Draw("SAME");

  gPad->Update();

  canvas4->SaveAs((dir+"/sig_match.eps").c_str());
  canvas4->Write();

  canvas5->cd();

  h_bkg_l->SetLineStyle(9);
  h_bkg_m->SetLineStyle(2);
  h_bkg_t->SetLineStyle(1);

  h_bkg_l->SetLineWidth(3);

  h_bkg_l->SetLineColor(kRed);
  h_bkg_m->SetLineColor(kYellow+2);
  h_bkg_t->SetLineColor(kGreen+2);

  h_bkg_l->DrawNormalized();
  h_bkg_m->DrawNormalized("SAME");
  h_bkg_t->DrawNormalized("SAME");

  leg5 = new TLegend(0.75,0.65,0.95,0.85);
  leg5->SetFillStyle(0);
  leg5->SetBorderSize(0);
  leg5->AddEntry(h_bkg_l,"loose","L");
  leg5->AddEntry(h_bkg_m,"medium","L");
  leg5->AddEntry(h_bkg_t,"tight","L");
  leg5->Draw("SAME");

  gPad->Update();

  canvas5->SaveAs((dir+"/bkg_match.eps").c_str());
  canvas5->Write();

  fhistos->Close();

}

void makeHistos_Fj_gen_pt_4plots(bool save = false, bool display = false){
  string dir = "allChi_noMinFatjetPt_noMjBtagCondition";
  string fsig = "RadionToHH_4b_M-800_TuneZ2star_8TeV-Madgraph_pythia6_R12_r15_minPt0_Nobtagmjcondition_AllChi_mc_subjets";
  string fbkg = "ZPrimeToTTJets_M1000GeV_W10GeV_TuneZ2star_8TeV-madgraph-tauola_R12_r15_minPt0_Nobtagmjcondition_AllChi_mc_subjets";
  string postfix = "dRmax12_NoGenPtCut_NoFjPtCut_AllChi";

  string var = "Fj_pt";
  string var_gen = "gen_pt";
  double xbin = 50; double xmin = 0; double xmax = 1000;

  string cut1 = "";
  string cut2 = "Fj_chi>0";
  string loose_cut1 = cut1;  string loose_cut2 = cut2;
  string medium_cut1;string medium_cut2;
  if(cut1==""){medium_cut1 = "dR_match<0.2";} else {medium_cut1 = ("dR_match<0.2&&"+cut1).c_str();}  ;
  if(cut2==""){medium_cut2 = "dR_match<0.2";} else {medium_cut2 = ("dR_match<0.2&&"+cut2).c_str();}  ;
  string tight_cut1;string tight_cut2;
  if(cut1==""){tight_cut1 = "dR_match<0.05";} else {tight_cut1 = ("dR_match<0.05&&"+cut1).c_str();}  ;
  if(cut2==""){tight_cut2 = "dR_match<0.05";} else {tight_cut2 = ("dR_match<0.05&&"+cut2).c_str();}  ;

  Color_t color1= kBlue;
  Color_t color2 = kGreen+1;

  TFile *f_l = new TFile((dir+"/"+"fMatch_"+fsig+"_"+postfix+".root").c_str());

  //loose match
  TH1D* h_fj_l = PartonMatch_1D(dir,f_l,fsig,var,loose_cut1,xbin,xmin,xmax,postfix,color1,1,save);
  TH1D* h_gen_l = PartonMatch_1D(dir,f_l,fsig,var_gen,loose_cut1,xbin,xmin,xmax,postfix,color2,1,save);
  TH1D* h_fj_l_2 = PartonMatch_1D(dir,f_l,fsig,var,loose_cut2,xbin,xmin,xmax,postfix,color1,2,save);
  TH1D* h_gen_l_2 = PartonMatch_1D(dir,f_l,fsig,var_gen,loose_cut2,xbin,xmin,xmax,postfix,color2,2,save);

  //medium match
  TH1D* h_fj_m = PartonMatch_1D(dir,f_l,fsig,var,medium_cut1,xbin,xmin,xmax,postfix,color1,1,save);
  TH1D* h_gen_m = PartonMatch_1D(dir,f_l,fsig,var_gen,medium_cut1,xbin,xmin,xmax,postfix,color2,1,save);
  TH1D* h_fj_m_2 = PartonMatch_1D(dir,f_l,fsig,var,medium_cut2,xbin,xmin,xmax,postfix,color1,2,save);
  TH1D* h_gen_m_2 = PartonMatch_1D(dir,f_l,fsig,var_gen,medium_cut2,xbin,xmin,xmax,postfix,color2,2,save);

  //tight match
  TH1D* h_fj_t = PartonMatch_1D(dir,f_l,fsig,var,tight_cut1,xbin,xmin,xmax,postfix,color1,1,save);
  TH1D* h_gen_t = PartonMatch_1D(dir,f_l,fsig,var_gen,tight_cut1,xbin,xmin,xmax,postfix,color2,1,save);
  TH1D* h_fj_t_2 = PartonMatch_1D(dir,f_l,fsig,var,tight_cut2,xbin,xmin,xmax,postfix,color1,2,save);
  TH1D* h_gen_t_2 = PartonMatch_1D(dir,f_l,fsig,var_gen,tight_cut2,xbin,xmin,xmax,postfix,color2,2,save);

  //---create canvas---

  TCanvas* canvas_l = new TCanvas("loose matching","loose matching",800,600);
  TCanvas* canvas_m = new TCanvas("medium matching","medium matching",800,600);
  TCanvas* canvas_t = new TCanvas("tight matching","tight matching",800,600);

  //cout<<"Creating "<< dir+"/"+"PartonMatch_makeHistos_Fj_gen_pt.root"<< endl;
  //TFile *fhistos = new TFile((dir+"/"+"PartonMatch_makeHistos_Fj_gen_pt.root").c_str(),"RECREATE");

  gStyle->SetOptStat("nemrou");

 //--------loose-------
  canvas_l->cd();
  h_fj_l->SetStats(0);
  h_gen_l->SetStats(0);
  h_fj_l_2->SetStats(0);
  h_gen_l_2->SetStats(0);
  h_gen_l->DrawNormalized();
  h_fj_l->DrawNormalized("SAME");
  h_gen_l_2->DrawNormalized("SAME");
  h_fj_l_2->DrawNormalized("SAME");
  leg = new TLegend(0.6,0.65,0.9,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h_fj_l,("fj "+cut1).c_str(),"L");
  leg->AddEntry(h_gen_l,("gen "+cut1).c_str(),"L");
  leg->AddEntry(h_fj_l_2,("fj "+cut2).c_str(),"L");
  leg->AddEntry(h_gen_l_2,("gen "+cut2).c_str(),"L");
  leg->Draw("SAME");
  gPad->Update();
  if(save)canvas_l->SaveAs((dir+"/loose_match"+"_"+var+".eps").c_str());

  //--------medium-------
  canvas_m->cd();
  h_fj_m->SetStats(0);
  h_gen_m->SetStats(0);
  h_fj_m_2->SetStats(0);
  h_gen_m_2->SetStats(0);
  h_gen_m->DrawNormalized();
  h_fj_m->DrawNormalized("SAME");
  h_gen_m_2->DrawNormalized("SAME");
  h_fj_m_2->DrawNormalized("SAME");
  leg = new TLegend(0.6,0.65,0.9,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h_fj_m,("fj "+cut1).c_str(),"L");
  leg->AddEntry(h_gen_m,("gen "+cut1).c_str(),"L");
  leg->AddEntry(h_fj_m_2,("fj "+cut2).c_str(),"L");
  leg->AddEntry(h_gen_m_2,("gen "+cut2).c_str(),"L");
  leg->Draw("SAME");
  gPad->Update();
  if(save)canvas_m->SaveAs((dir+"/medium_match"+"_"+var+".eps").c_str());

  //--------tight-------
  canvas_t->cd();
  h_fj_t->SetStats(0);
  h_gen_t->SetStats(0);
  h_fj_t_2->SetStats(0);
  h_gen_t_2->SetStats(0);
  h_gen_t->DrawNormalized();
  h_fj_t->DrawNormalized("SAME");
  h_gen_t_2->DrawNormalized("SAME");
  h_fj_t_2->DrawNormalized("SAME");
  leg = new TLegend(0.6,0.65,0.9,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h_fj_t,("fj "+cut1).c_str(),"L");
  leg->AddEntry(h_gen_t,("gen "+cut1).c_str(),"L");
  leg->AddEntry(h_fj_t_2,("fj "+cut2).c_str(),"L");
  leg->AddEntry(h_gen_t_2,("gen "+cut2).c_str(),"L");
  leg->Draw("SAME");
  gPad->Update();
  if(save)canvas_t->SaveAs((dir+"/tight_match"+"_"+var+".eps").c_str());

}

void makeHistos_Fj_gen_chi(bool save = false, bool display = false){
  string dir = "allChi_noMinFatjetPt_noMjBtagCondition";
  string fsig = "RadionToHH_4b_M-800_TuneZ2star_8TeV-Madgraph_pythia6_R12_r15_minPt0_Nobtagmjcondition_AllChi_mc_subjets";
  string fbkg = "ZPrimeToTTJets_M1000GeV_W10GeV_TuneZ2star_8TeV-madgraph-tauola_R12_r15_minPt0_Nobtagmjcondition_AllChi_mc_subjets";
  string var = "log(Fj_chi)";
  double dR_tight = 0.05; double dR_med = 0.2;  double dR_loose = 1.2;
  double xbin = 40; double xmin = -18; double xmax = -2;
  string postfix;
  string postfix1 = "NoGenPtCut_NoFjPtCut"; Color_t color1= kBlue;
  string postfix2 = "NoGenPtCut_NoFjPtCut_InvalidChiCut"; Color_t color2 = kGreen+1;

  //loose match
  postfix = "dRmax12_"+postfix1;
  TFile *f_l = new TFile((dir+"/"+"fMatch_"+fsig+"_"+postfix+".root").c_str());
  TH1D* h_fj_l = PartonMatch_1D(dir,f_l,fsig,var,xbin,xmin,xmax,postfix,color1,1,save);
  postfix = "dRmax12_"+postfix2;
  TFile *f_l_2 = new TFile((dir+"/"+"fMatch_"+fsig+"_"+postfix+".root").c_str());
  TH1D* h_fj_l_2 = PartonMatch_1D(dir,f_l_2,fsig,var,xbin,xmin,xmax,postfix,color1,2,save);

  //medium match
  postfix = "dRmax02_"+postfix1;
  TFile *f_m = new TFile((dir+"/"+"fMatch_"+fsig+"_"+postfix+".root").c_str());
  TH1D* h_fj_m = PartonMatch_1D(dir,f_m,fsig,var,xbin,xmin,xmax,postfix,color1,1,save);
  postfix = "dRmax02_"+postfix2;
  TFile *f_m_2 = new TFile((dir+"/"+"fMatch_"+fsig+"_"+postfix+".root").c_str());
  TH1D* h_fj_m_2 = PartonMatch_1D(dir,f_m_2,fsig,var,xbin,xmin,xmax,postfix,color1,2,save);

  //tight match
  postfix = "dRmax005_"+postfix1;
  TFile *f_t = new TFile((dir+"/"+"fMatch_"+fsig+"_"+postfix+".root").c_str());
  TH1D* h_fj_t = PartonMatch_1D(dir,f_t,fsig,var,xbin,xmin,xmax,postfix,color1,1,save);
  postfix = "dRmax005_"+postfix2;
  TFile *f_t_2 = new TFile((dir+"/"+"fMatch_"+fsig+"_"+postfix+".root").c_str());
  TH1D* h_fj_t_2 = PartonMatch_1D(dir,f_t_2,fsig,var,xbin,xmin,xmax,postfix,color1,2,save);


  TCanvas* canvas_l = new TCanvas("loose matching","loose matching",800,600);
  TCanvas* canvas_m = new TCanvas("medium matching","medium matching",800,600);
  TCanvas* canvas_t = new TCanvas("tight matching","tight matching",800,600);

  //cout<<"Creating "<< dir+"/"+"PartonMatch_makeHistos_Fj_gen_chi.root"<< endl;
  //TFile *fhistos = new TFile((dir+"/"+"PartonMatch_makeHistos_Fj_gen_chi.root").c_str(),"RECREATE");

  gStyle->SetOptStat("nemrou");

  //--------loose-----------
  canvas_l->cd();
  h_fj_l->SetStats(0);
  h_fj_l_2->SetStats(0);
  h_fj_l->DrawNormalized();
  h_fj_l_2->DrawNormalized("SAME");
  leg = new TLegend(0.6,0.65,0.9,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h_fj_l,("fj - "+postfix1).c_str(),"L");
  leg->AddEntry(h_fj_l_2,("fj - "+postfix2).c_str(),"L");
  leg->Draw("SAME");
  gPad->Update();
  if(save)canvas_l->SaveAs((dir+"/loose_match"+"_logChi"+".eps").c_str());

  //--------medium-----------
  canvas_m->cd();
  h_fj_m->SetStats(0);
  h_fj_m_2->SetStats(0);
  h_fj_m->DrawNormalized();
  h_fj_m_2->DrawNormalized("SAME");
  leg = new TLegend(0.6,0.65,0.9,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h_fj_m,("fj - "+postfix1).c_str(),"L");
  leg->AddEntry(h_fj_m_2,("fj - "+postfix2).c_str(),"L");
  leg->Draw("SAME");
  gPad->Update();
  if(save)canvas_m->SaveAs((dir+"/medium_match"+"_logChi"+".eps").c_str());

  //--------tight-----------
  canvas_t->cd();
  h_fj_t->SetStats(0);
  h_fj_t_2->SetStats(0);
  h_fj_t->DrawNormalized();
  h_fj_t_2->DrawNormalized("SAME");
  leg = new TLegend(0.6,0.65,0.9,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h_fj_t,("fj - "+postfix).c_str(),"L");
  leg->AddEntry(h_fj_t_2,("fj - "+postfix).c_str(),"L");
  leg->Draw("SAME");
  gPad->Update();
  if(save)canvas_t->SaveAs((dir+"/tight_match"+"_logChi"+".eps").c_str());

}



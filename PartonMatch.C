
using namespace std;

int PartonMatch(std::string fdir, std::string fname, int gen_pdgid,double dRmax = 1.2, double MjCone = 0.15, bool display=false, std::string postfix = ""){

  TFile *f = new TFile((fdir+"/"+fname+".root").c_str());

  TDirectoryFile *d = f->GetDirectory("btagana");
  //TDirectoryFile *d = f->GetDirectory("btaganaSubjets");
  TTree *t = d->Get("ttree");
  TDirectoryFile *df = f->GetDirectory("btaganaSubJets");
  TTree *tf = df->Get("ttree");

  const int nEvent = t->GetEntries();
  int nMatchMax = 0;
  vector<int> iEventOverMatch;

  const int nGenPrunedMax = 25;

  int nGenPruned;
  int GenPruned_pdgID[nGenPrunedMax];
  float GenPruned_eta[nGenPrunedMax];
  float GenPruned_phi[nGenPrunedMax];
  float GenPruned_pT[nGenPrunedMax];

  const int nFjMax=5;
  const int nMjMax=50;
  const int nSVMax=50;

  int FatJetInfo_nJet;
  float FatJetInfo_Jet_eta[nFjMax];
  float FatJetInfo_Jet_phi[nFjMax];
  float FatJetInfo_Jet_SD_chi[nFjMax];
  float FatJetInfo_Jet_pt[nFjMax];
  int FatJetInfo_Jet_SD_nBtagMicrojets[nFjMax];

  int   FatJetInfo_Jet_SD_nMicrojets[nFjMax];
  int FatJetInfo_Jet_SD_nFirstMicrojet[nFjMax];
  int FatJetInfo_Jet_SD_nLastMicrojet[nFjMax];
  float FatJetInfo_Jet_SD_Microjet_pt[nMjMax];
  float FatJetInfo_Jet_SD_Microjet_eta[nMjMax];
  float FatJetInfo_Jet_SD_Microjet_phi[nMjMax];
  int   FatJetInfo_Jet_SD_Microjet_isBtag[nMjMax];

  int FatJetInfo_Jet_SV_multi[nFjMax];
  int FatJetInfo_Jet_nFirstSV[nFjMax];
  int FatJetInfo_Jet_nLastSV[nFjMax];
  float FatJetInfo_SV_vtx_pt[nSVMax];
  float FatJetInfo_SV_vtx_eta[nSVMax];
  float FatJetInfo_SV_vtx_phi[nSVMax];

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

  tf->SetBranchAddress("FatJetInfo.Jet_SD_nMicrojets",&FatJetInfo_Jet_SD_nMicrojets);
  tf->SetBranchAddress("FatJetInfo.Jet_SD_nFirstMicrojet",&FatJetInfo_Jet_SD_nFirstMicrojet);
  tf->SetBranchAddress("FatJetInfo.Jet_SD_nLastMicrojet",&FatJetInfo_Jet_SD_nLastMicrojet);
  tf->SetBranchAddress("FatJetInfo.Jet_SD_Microjet_pt",&FatJetInfo_Jet_SD_Microjet_pt);
  tf->SetBranchAddress("FatJetInfo.Jet_SD_Microjet_eta",&FatJetInfo_Jet_SD_Microjet_eta);
  tf->SetBranchAddress("FatJetInfo.Jet_SD_Microjet_phi",&FatJetInfo_Jet_SD_Microjet_phi);
  tf->SetBranchAddress("FatJetInfo.Jet_SD_Microjet_isBtag",&FatJetInfo_Jet_SD_Microjet_isBtag);

  tf->SetBranchAddress("FatJetInfo.Jet_SV_multi",&FatJetInfo_Jet_SV_multi);
  tf->SetBranchAddress("FatJetInfo.Jet_nFirstSV",&FatJetInfo_Jet_nFirstSV);
  tf->SetBranchAddress("FatJetInfo.Jet_nLastSV",&FatJetInfo_Jet_nLastSV);
  tf->SetBranchAddress("FatJetInfo.SV_vtx_pt",&FatJetInfo_SV_vtx_pt);
  tf->SetBranchAddress("FatJetInfo.SV_vtx_eta",&FatJetInfo_SV_vtx_eta);
  tf->SetBranchAddress("FatJetInfo.SV_vtx_phi",&FatJetInfo_SV_vtx_phi);

  float dR_match;
  float gen_pt;
  int gen_pdgID;

  int Fj_event_idx;
  float Fj_chi;
  float Fj_pt;

  int Fj_nBtagMj;
  int Fj_nMj;
  const int MjPerFjMax = 10;
  float Mj_pt[MjPerFjMax];
  float Mj_eta[MjPerFjMax];
  float Mj_phi[MjPerFjMax];
  int Mj_isBtag[MjPerFjMax];
  float Mj_dR[MjPerFjMax];
  int Mj_dR_genIdx[MjPerFjMax];
  int Mj_gen_matched_pdgID[MjPerFjMax];
  float Mj_gen_matched_pt[MjPerFjMax];


  int nMj_gen = 30; //4 b's
  const int nMjGenMax = 30;
  float Mj_gen_pt[nMjGenMax];
  int Mj_gen_pdgID[nMjGenMax];
  int Mj_gen_isMatch[nMjGenMax];

  const int nMatchMjPerFjMax = 50;
  int Mj_nMatch;
  float Mj_match_pt[nMatchMjPerFjMax];

  int Fj_nSV;
  const int SVPerFjMax = 20;
  float SV_pt[SVPerFjMax];
  float SV_eta[SVPerFjMax];
  float SV_phi[SVPerFjMax];

  cout<<endl;
  cout<<"Creating new root file containing Fatjet based tree: "<< fdir+"/"+"fMatch_"+fname+"_"+postfix+".root" << endl;
  TFile *fMatch = new TFile((fdir+"/"+"fMatch_"+fname+"_"+postfix+".root").c_str(),"RECREATE"); //DIFFERENCE BETWEEN USING POINTER???
  TTree *tr_new = new TTree("tree","tree");
  tr_new->Branch("Fj_event_idx",&Fj_event_idx,"Fj_event_idx/I");
  tr_new->Branch("dR_match",&dR_match,"dR_match/F");
  tr_new->Branch("Fj_chi",&Fj_chi,"Fj_chi/F");
  tr_new->Branch("Fj_pt",&Fj_pt,"Fj_pt/F");
  tr_new->Branch("gen_pt",&gen_pt,"gen_pt/F");
  tr_new->Branch("gen_pdgID",&gen_pdgID,"gen_pdgID/I");
  tr_new->Branch("Fj_nMj",&Fj_nMj,"Fj_nMj/I");
  tr_new->Branch("Fj_nBtagMj",&Fj_nBtagMj,"Fj_nBtagMj/I");
  tr_new->Branch("Mj_pt",&Mj_pt,"Mj_pt[Fj_nMj]/F");
  tr_new->Branch("Mj_eta",&Mj_eta,"Mj_eta[Fj_nMj]/F");
  tr_new->Branch("Mj_phi",&Mj_phi,"Mj_phi[Fj_nMj]/F");
  tr_new->Branch("Mj_isBtag",&Mj_isBtag,"Mj_isBtag[Fj_nMj]/I");
  tr_new->Branch("Mj_dR",&Mj_dR,"Mj_dR[Fj_nMj]/F");
  tr_new->Branch("Mj_dR_genIdx",&Mj_dR_genIdx,"Mj_dR_genIdx[Fj_nMj]/I");
  tr_new->Branch("Mj_gen_matched_pdgID",&Mj_gen_matched_pdgID,"Mj_gen_matched_pdgID[Fj_nMj]/I");
  tr_new->Branch("Mj_gen_matched_pt",&Mj_gen_matched_pt,"Mj_gen_matched_pt[Fj_nMj]/F");

  tr_new->Branch("Mj_gen_pt",&Mj_gen_pt,"Mj_gen_pt[30]/F");
  tr_new->Branch("Mj_gen_pdgID",&Mj_gen_pdgID,"Mj_gen_pdgID[30]/I");
  tr_new->Branch("Mj_gen_isMatch",&Mj_gen_isMatch,"Mj_gen_isMatch[30]/I");

  tr_new->Branch("Mj_nMatch",&Mj_nMatch,"Mj_nMatch/I");

  tr_new->Branch("Fj_nSV",&Fj_nSV,"Fj_nSV/I");
  tr_new->Branch("SV_pt",&SV_pt,"SV_pt[Fj_nSV]/F");
  tr_new->Branch("SV_eta",&SV_eta,"SV_eta[Fj_nSV]/F");
  tr_new->Branch("SV_phi",&SV_phi,"SV_phi[Fj_nSV]/F");

  cout << endl;
  cout << "Matching fatjets in "<< fname << ", with pdgid = " << gen_pdgid << endl;
  cout << endl;

  //loop over events
  if(display)cout << endl;
  for (int i =0 ; i<nEvent;i++){
  //for (int i =0 ; i<3;i++){
    t->GetEntry(i);
    tf->GetEntry(i);
    if(display)cout << endl;
    if(display)cout << "============  entry : "<< i << ", nGenPruned = "<< nGenPruned << ", nFatJet = "<< FatJetInfo_nJet <<"  =============="<< endl;
    //    if(display)cout << endl;

    //loop over fatjets
    int nMatch=0;
    for(int j=0; j < FatJetInfo_nJet; j++){
      if(display)cout<<endl;
      if(display)cout<< "Fatjet no. "<< j << " : Fatjet_pt = " << FatJetInfo_Jet_pt[j] << endl;
      //if(display)cout<< "Fatjet no. "<< j << " : Fatjet_eta = " << FatJetInfo_Jet_eta[j] << endl;
      //if(display)cout<< "           "<<     "    Fatjet_phi = " << FatJetInfo_Jet_phi[j] << endl;
      if(display)cout<< "           "<<     "    Fatjet_chi = " << FatJetInfo_Jet_SD_chi[j] << endl;
      if(display)cout<<endl;

      //loop over GenPruned
      for(int k=2; k < nGenPruned; k++){
	if(GenPruned_pdgID[k]!=gen_pdgid) continue;
	if(display)cout<< "        GenPruned no. "<< k << " : GenPruned_pdgID = " << GenPruned_pdgID[k] << endl;
	if(display)cout<< "                      "<<     "    GenPruned_pT = " << GenPruned_pT[k] << endl;
	//if(display)cout<< "                      "<<     "    GenPruned_eta = " << GenPruned_eta[k] << endl;
	//if(display)cout<< "                      "<<     "    GenPruned_phi = " << GenPruned_phi[k] << endl;

	double dR = deltaR(GenPruned_eta[k], GenPruned_phi[k], FatJetInfo_Jet_eta[j], FatJetInfo_Jet_phi[j]);
	if(display)cout<< "        " << j<< "-"<<k<<", -------------------------------->  delta R = "<< dR ;// << endl;
	if(dR<dRmax){
	  if(display)cout<<"----> Fj-parton MATCH!! " << endl;
	  nMatch++;

	  dR_match = dR;
	  Fj_event_idx = i;
	  Fj_chi = FatJetInfo_Jet_SD_chi[j];
	  gen_pt = GenPruned_pT[k];
	  gen_pdgID = GenPruned_pdgID[k];
	  Fj_pt = FatJetInfo_Jet_pt[j];
	  Fj_nMj = FatJetInfo_Jet_SD_nMicrojets[j];
	  Fj_nBtagMj = FatJetInfo_Jet_SD_nBtagMicrojets[j];
	  Fj_nSV = FatJetInfo_Jet_SV_multi[j];

	  for(int ib_ =0; ib_<nMjGenMax;ib_++)Mj_gen_isMatch[ib_]=0; //initialize recon status of b quarks
	  for(int ib_ =0; ib_<nMjGenMax;ib_++)Mj_gen_pt[ib_]=-9999; //initialize pt of b quarks
	  for(int ib_ =0; ib_<nMjGenMax;ib_++)Mj_gen_pdgID[ib_]=-9999; //initialize pt of b quarks

	  //loop over SV
	  int iSV = 0; int first; int last;
	  first = FatJetInfo_Jet_nFirstSV[j];
	  last = FatJetInfo_Jet_nLastSV[j];
	  for(int jSV = first; jSV < last ; jSV++){
	    //cout << "FatJetInfo_SV_vtx_pt["<<jSV<<"] = "<<FatJetInfo_SV_vtx_pt[jSV]<<endl;
	    //cout << "FatJetInfo_SV_vtx_eta["<<jSV<<"] = "<<FatJetInfo_SV_vtx_eta[jSV]<<endl;
	    //cout << "FatJetInfo_SV_vtx_phi["<<jSV<<"] = "<<FatJetInfo_SV_vtx_phi[jSV]<<endl;
	    SV_pt[iSV] = FatJetInfo_SV_vtx_pt[jSV];
	    SV_eta[iSV] = FatJetInfo_SV_vtx_eta[jSV];
	    SV_phi[iSV] = FatJetInfo_SV_vtx_phi[jSV];
	    iSV++;
	  }

	  if(display)cout << endl;
	  if(display)cout << "                ---------------"<< " nMJet = "<< FatJetInfo_Jet_SD_nMicrojets[j] <<"  -----------"<< endl;
	  if(display)cout << endl;
	  //loop over Microjets
	  int iMj = 0;
	  int iMatchMj = 0;
	  for(int l = FatJetInfo_Jet_SD_nFirstMicrojet[j] ; l < FatJetInfo_Jet_SD_nLastMicrojet[j] ;l++){
	    if(display)cout<<endl;
	    if(display)cout<< "                Microjet no. "<< l  << " : Mjet_pt    = " << FatJetInfo_Jet_SD_Microjet_pt[l] << endl;
	    //if(display)cout<< "                           "<<     "      Mjet_eta    = " << FatJetInfo_Jet_SD_Microjet_eta[l] << endl;
	    //if(display)cout<< "                           "<<     "      Mjet_phi    = " << FatJetInfo_Jet_SD_Microjet_phi[l]  << endl;
	    if(display)cout<< "                           "<<     "      Mjet_isBtag = " << FatJetInfo_Jet_SD_Microjet_isBtag[l]  << endl;
	    if(display)cout<<endl;

	    Mj_pt[iMj] = FatJetInfo_Jet_SD_Microjet_pt[l];
	    Mj_eta[iMj] = FatJetInfo_Jet_SD_Microjet_eta[l];
	    Mj_phi[iMj] = FatJetInfo_Jet_SD_Microjet_phi[l];
	    Mj_isBtag[iMj] = FatJetInfo_Jet_SD_Microjet_isBtag[l];
	    Mj_dR[iMj] = -99999;
	    Mj_dR_genIdx[iMj] = -99999;
	    Mj_gen_matched_pdgID[iMj] = -99999;
	    Mj_gen_matched_pt[iMj] = -99999;

	    //Gen Mj matching loop
	    int ib = 0;
	    for(int iGenMj=2; iGenMj < nGenPruned; iGenMj++){
	      //if(abs(GenPruned_pdgID[iGenMj])!=5) continue;//b quark
	      if(abs(GenPruned_pdgID[iGenMj])==gen_pdgid) continue; // dont match with fatjet gen
	      //if(GenPruned_pdgID[iGenMj]==35) continue;
	      Mj_gen_pt[ib] = GenPruned_pT[iGenMj];
	      Mj_gen_pdgID[ib] = GenPruned_pdgID[iGenMj];

	      if(display)cout<< "                             GenPruned no. "<< iGenMj << " : GenPruned_pdgID = " << GenPruned_pdgID[iGenMj] << endl;
	      if(display)cout<< "                                           "<< iGenMj << " : GenPruned_pT = " << GenPruned_pT[iGenMj] << endl;
	      double dR_Mj = deltaR(GenPruned_eta[iGenMj], GenPruned_phi[iGenMj], FatJetInfo_Jet_SD_Microjet_eta[l], FatJetInfo_Jet_SD_Microjet_phi[l]);
	      if(display)cout<< "                             " << l<< "-"<<iGenMj<<", -------------------------------->  delta R = "<< dR_Mj ;// << endl;

	      //matching dR requirement
	      if(dR_Mj<MjCone){
		if(display)cout<<"----> Mj-Parton MATCH!! ";
		if(abs(Mj_dR[iMj])<dR_Mj) continue; //TO MAKE SURE THIS RECORDS THE SMALLEST deltaR!!
		Mj_dR[iMj] = dR_Mj;
		Mj_dR_genIdx[iMj] = ib;
		Mj_gen_matched_pdgID[iMj] = GenPruned_pdgID[iGenMj];
		Mj_gen_matched_pt[iMj] = GenPruned_pT[iGenMj];
		Mj_gen_isMatch[ib] = 1;
		iMatchMj++;
	      }// end if dR_Mj
	      if(display)cout << endl;

	    ib++;
	    }//end Gen Mj match loop

	    iMj++;
	  }//Mj loop
	  Mj_nMatch = iMatchMj;

	  tr_new->Fill();

	}//end if dR requirement
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

void PartonMatch(bool display = false){
  string dir = "allChi_noMinFatjetPt_noMjBtagCondition";
  string deltaHiggsMass;
  string fsig;
  string fbkg;
  double dRmax = 1.2;
  double MjCone = 0.15;
  string postfix= "dRmax12_NoGenPtCut_NoFjPtCut_AllChi";

  deltaHiggsMass = "HiggsWin10";
  fsig = "RadionToHH_4b_M-800_TuneZ2star_8TeV-Madgraph_pythia6_R12_r15_minPt0_Nobtagmjcondition_AllChi_"+deltaHiggsMass+"_mc_subjets";
  fbkg = "ZPrimeToTTJets_M1000GeV_W10GeV_TuneZ2star_8TeV-madgraph-tauola_R12_r15_minPt0_Nobtagmjcondition_AllChi_"+deltaHiggsMass+"_mc_subjets";
  int sig_l = PartonMatch(dir,fsig,25,dRmax,MjCone,display,postfix);
  int bkg_l = PartonMatch(dir,fbkg,6,dRmax,MjCone,display,postfix);

  deltaHiggsMass = "HiggsWin20";
  fsig = "RadionToHH_4b_M-800_TuneZ2star_8TeV-Madgraph_pythia6_R12_r15_minPt0_Nobtagmjcondition_AllChi_"+deltaHiggsMass+"_mc_subjets";
  fbkg = "ZPrimeToTTJets_M1000GeV_W10GeV_TuneZ2star_8TeV-madgraph-tauola_R12_r15_minPt0_Nobtagmjcondition_AllChi_"+deltaHiggsMass+"_mc_subjets";
  int sig_l = PartonMatch(dir,fsig,25,dRmax,MjCone,display,postfix);
  int bkg_l = PartonMatch(dir,fbkg,6,dRmax,MjCone,display,postfix);
}

double deltaR(double eta1, double phi1, double eta2, double phi2){
  double dEta = eta1 - eta2;

  double dPhi = phi1 - phi2;
  while (dPhi > TMath::Pi()) dPhi -= 2*TMath::Pi();
  while (dPhi <= -TMath::Pi()) dPhi += 2*TMath::Pi();

  double dR = sqrt(dEta*dEta + dPhi*dPhi);
  return dR;
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


TH1D* PartonMatch_1D(std::string dir, TFile* f, std::string fname,  std::string var, std::string cut,  double xbin, double xmin, double xmax, std::string xlabel, std::string postfix, Color_t color = kBlue, int linestyle = 1,bool save = false){

  string var_ = var;
  if(var_=="log(Fj_chi)") var_ = "logChi"; //log(Fj_chi) become log( for some reason???

  TCanvas* cvs = new TCanvas((var_+cut+postfix).c_str(),(var_+cut+postfix).c_str(),800,600);

  TTree *t = f->Get("tree");
  TH1D* h = new TH1D ((var_+cut+postfix).c_str(),(var_+cut+postfix).c_str(),xbin,xmin,xmax);

  t->Draw((var+">>"+var_+cut+postfix).c_str(),cut.c_str());

  gStyle->SetOptStat("emrou");

  h->SetLineWidth(2);
  h->SetLineColor(color);
  h->SetLineStyle(linestyle);
  h->GetXaxis()->SetTitle(xlabel.c_str());
  h->GetYaxis()->SetTitle("");
  h->SetTitle("");

  delete t;
  if(save)cvs->SaveAs((dir+"/"+fname+"_"+var_+"_"+cut+".eps").c_str());

  return h;
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

  gStyle->SetOptStat("emrou");
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

  gStyle->SetOptStat("emrou");

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

void makeHistos_Fj_gen_pt_2plots(bool save = false, std::string dir, std::string fsig, std::string cut, double xbin, double xmin, double xmax, std::string postfix){

  string var = "Fj_pt";
  string var_gen = "gen_pt";
  string xlabel = "p_{T}";

  string loose_cut = cut;
  string medium_cut; if(cut==""){medium_cut = "dR_match<0.2";} else {medium_cut = ("dR_match<0.2&&"+cut).c_str();}  ;
  string tight_cut; if(cut==""){tight_cut = "dR_match<0.05";} else {tight_cut = ("dR_match<0.05&&"+cut).c_str();}  ;

  Color_t color1= kBlue;  Color_t color2 = kGreen+1;
  int linestyle1 = 1 ;int linestyle2 = 1;

  TFile *f_l = new TFile((dir+"/"+"fMatch_"+fsig+"_"+postfix+".root").c_str());

  //loose match
  TH1D* h_fj_l = PartonMatch_1D(dir,f_l,fsig,var,loose_cut,xbin,xmin,xmax,xlabel,postfix,color1,linestyle1,save);
  TH1D* h_gen_l = PartonMatch_1D(dir,f_l,fsig,var_gen,loose_cut,xbin,xmin,xmax,xlabel,postfix,color2,linestyle2,save);

  //medium match
  TH1D* h_fj_m = PartonMatch_1D(dir,f_l,fsig,var,medium_cut,xbin,xmin,xmax,xlabel,postfix,color1,linestyle1,save);
  TH1D* h_gen_m = PartonMatch_1D(dir,f_l,fsig,var_gen,medium_cut,xbin,xmin,xmax,xlabel,postfix,color2,linestyle2,save);

  //tight match
  TH1D* h_fj_t = PartonMatch_1D(dir,f_l,fsig,var,tight_cut,xbin,xmin,xmax,xlabel,postfix,color1,linestyle1,save);
  TH1D* h_gen_t = PartonMatch_1D(dir,f_l,fsig,var_gen,tight_cut,xbin,xmin,xmax,xlabel,postfix,color2,linestyle2,save);

  //---create canvas---

  TCanvas* canvas_l = new TCanvas("loose matching","loose matching",800,600);
  TCanvas* canvas_m = new TCanvas("medium matching","medium matching",800,600);
  TCanvas* canvas_t = new TCanvas("tight matching","tight matching",800,600);

  gStyle->SetOptStat("emrou");

  Double_t norm1;
  Double_t norm2;

 //--------loose-------
  canvas_l->cd();

  norm1 = h_fj_l->GetEntries();
  h_fj_l->Scale(1/norm1);
  norm2 = h_gen_l->GetEntries();
  h_gen_l->Scale(1/norm2);

  h_gen_l->Draw();
  h_fj_l->Draw("SAME");
  leg = new TLegend(0.55,0.65,0.65,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h_fj_l,"fatjet","L");
  leg->AddEntry(h_gen_l,"gen","L");
  leg->Draw("SAME");

  TPaveStats *tps1 = (TPaveStats*) h_fj_l->FindObject("stats");
  tps1->SetTextColor(color1);
  double X1 = tps1->GetX1NDC();
  double Y1 = tps1->GetY1NDC();
  double X2 = tps1->GetX2NDC();
  double Y2 = tps1->GetY2NDC();

  TPaveStats *tps2 = (TPaveStats*) h_gen_l->FindObject("stats");
  tps2->SetTextColor(color2);
  tps2->SetX1NDC(X1);
  tps2->SetX2NDC(X2);
  tps2->SetY1NDC(Y1-(Y2-Y1));
  tps2->SetY2NDC(Y1);

  gPad->Update();
  if(save)canvas_l->SaveAs((dir+"/fj_gen_2plots_loose_match"+"_"+var+"_"+cut+".eps").c_str());

  //--------medium-------
  canvas_m->cd();

  norm1 = h_fj_m->GetEntries();
  h_fj_m->Scale(1/norm1);
  norm2 = h_gen_m->GetEntries();
  h_gen_m->Scale(1/norm2);

  h_gen_m->Draw();
  h_fj_m->Draw("SAME");
  leg = new TLegend(0.55,0.65,0.65,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h_fj_m,"fatjet","L");
  leg->AddEntry(h_gen_m,"gen","L");
  leg->Draw("SAME");

  TPaveStats *tps1_m = (TPaveStats*) h_fj_m->FindObject("stats");
  tps1_m->SetTextColor(color1);
  X1 = tps1_m->GetX1NDC();
  Y1 = tps1_m->GetY1NDC();
  X2 = tps1_m->GetX2NDC();
  Y2 = tps1_m->GetY2NDC();

  TPaveStats *tps2_m = (TPaveStats*) h_gen_m->FindObject("stats");
  tps2_m->SetTextColor(color2);
  tps2_m->SetX1NDC(X1);
  tps2_m->SetX2NDC(X2);
  tps2_m->SetY1NDC(Y1-(Y2-Y1));
  tps2_m->SetY2NDC(Y1);

  gPad->Update();
  if(save)canvas_m->SaveAs((dir+"/fj_gen_2plots_medium_match"+"_"+var+"_"+cut+".eps").c_str());

  //--------tight-------
  canvas_t->cd();

  norm1 = h_fj_t->GetEntries();
  h_fj_t->Scale(1/norm1);
  norm2 = h_gen_t->GetEntries();
  h_gen_t->Scale(1/norm2);

  h_gen_t->Draw();
  h_fj_t->Draw("SAME");
  leg = new TLegend(0.55,0.65,0.65,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h_fj_t,"fatjet","L");
  leg->AddEntry(h_gen_t,"gen","L");
  leg->Draw("SAME");

  TPaveStats *tps1_t = (TPaveStats*) h_fj_t->FindObject("stats");
  tps1_t->SetTextColor(color1);
  X1 = tps1_t->GetX1NDC();
  Y1 = tps1_t->GetY1NDC();
  X2 = tps1_t->GetX2NDC();
  Y2 = tps1_t->GetY2NDC();

  TPaveStats *tps2_t = (TPaveStats*) h_gen_t->FindObject("stats");
  tps2_t->SetTextColor(color2);
  tps2_t->SetX1NDC(X1);
  tps2_t->SetX2NDC(X2);
  tps2_t->SetY1NDC(Y1-(Y2-Y1));
  tps2_t->SetY2NDC(Y1);

  gPad->Update();
  if(save)canvas_t->SaveAs((dir+"/fj_gen_2plots_tight_match"+"_"+var+"_"+cut+".eps").c_str());

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

  gStyle->SetOptStat("emrou");

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

void makeHistos_sig_bkg_2plots(std::string dir, std::string fsig, std::string fbkg, std::string var, std::string cut, double xbin, double xmin, double xmax, std::string xlabel, bool save = false){

  string postfix = "dRmax12_NoGenPtCut_NoFjPtCut_AllChi";

  string loose_cut = cut;
  string medium_cut; if(cut==""){medium_cut = "dR_match<0.2";} else {medium_cut = ("dR_match<0.2&&"+cut).c_str();}  ;
  string tight_cut; if(cut==""){tight_cut = "dR_match<0.05";} else {tight_cut = ("dR_match<0.05&&"+cut).c_str();}  ;

  Color_t color1= kBlue;
  Color_t color2 = kRed;

  TFile *fs = new TFile((dir+"/"+"fMatch_"+fsig+"_"+postfix+".root").c_str());
  TFile *fb = new TFile((dir+"/"+"fMatch_"+fbkg+"_"+postfix+".root").c_str());

  //tight match
  TH1D* h_s = PartonMatch_1D(dir,fs,fsig,var,tight_cut,xbin,xmin,xmax,xlabel,postfix,color1,1,save);
  TH1D* h_b = PartonMatch_1D(dir,fb,fbkg,var,tight_cut,xbin,xmin,xmax,xlabel,postfix,color2,1,save);

  TCanvas* canvas_t = new TCanvas("tight matching","tight matching",800,600);

  gStyle->SetOptStat("emrou");

  Double_t norm1;
  Double_t norm2;

  //--------tight-------
  canvas_t->cd();

  norm1 = h_s->GetEntries();
  h_s->Scale(1/norm1);
  norm2 = h_b->GetEntries();
  h_b->Scale(1/norm2);

  if(h_s->GetMaximum() > h_b->GetMaximum()){
    h_s->Draw();
    h_b->Draw("SAME");
  }
  else {
    h_b->Draw();
    h_s->Draw("SAME");
  }

  leg = new TLegend(0.55,0.65,0.85,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h_s,"RadionHH","L");
  leg->AddEntry(h_b,"Z'->ttbar","L");
  leg->Draw("SAME");

  double X1,Y1,X2,Y2;

  TPaveStats *tps1_t = (TPaveStats*) h_s->FindObject("stats");
  tps1_t->SetTextColor(color1);
  X1 = tps1_t->GetX1NDC();
  Y1 = tps1_t->GetY1NDC();
  X2 = tps1_t->GetX2NDC();
  Y2 = tps1_t->GetY2NDC();

  TPaveStats *tps2_t = (TPaveStats*) h_b->FindObject("stats");
  tps2_t->SetTextColor(color2);
  tps2_t->SetX1NDC(X1);
  tps2_t->SetX2NDC(X2);
  tps2_t->SetY1NDC(Y1-(Y2-Y1));
  tps2_t->SetY2NDC(Y1);

  gPad->Update();
  if(var=="log(Fj_chi)")var = "logChi";
  if(save)canvas_t->SaveAs((dir+"/sig_bkg_2plots_tight_match"+"_"+var+"_"+cut+".eps").c_str());

}

void Alakazam(){
  string dir = "allChi_noMinFatjetPt_noMjBtagCondition";
  //string deltaHiggsMass = "HiggsWin20";
  string deltaHiggsMass = "HiggsWin10";
  string fsig = "RadionToHH_4b_M-800_TuneZ2star_8TeV-Madgraph_pythia6_R12_r15_minPt0_Nobtagmjcondition_AllChi_"+deltaHiggsMass+"_mc_subjets";
  string fbkg = "ZPrimeToTTJets_M1000GeV_W10GeV_TuneZ2star_8TeV-madgraph-tauola_R12_r15_minPt0_Nobtagmjcondition_AllChi_"+deltaHiggsMass+"_mc_subjets";

  string postfix = "dRmax12_NoGenPtCut_NoFjPtCut_AllChi";

  double xbin = 50; double xmin = 0; double xmax = 1000;
  bool save = true;
  //makeHistos_Fj_gen_pt_2plots(save, dir, fsig, "", xbin, xmin, xmax, postfix);
  //makeHistos_Fj_gen_pt_2plots(save, dir, fsig, "Fj_chi>0", xbin, xmin, xmax, postfix);
  //makeHistos_Fj_gen_pt_2plots(save, dir, fsig, "Fj_chi<=0", xbin, xmin, xmax, postfix);

  //makeHistos_Fj_gen_pt_2plots(save, dir, fbkg, "", xbin, xmin, xmax, postfix);
  //makeHistos_Fj_gen_pt_2plots(save, dir, fbkg, "Fj_chi>0", xbin, xmin, xmax, postfix);
  //makeHistos_Fj_gen_pt_2plots(save, dir, fbkg, "Fj_chi<=0", xbin, xmin, xmax, postfix);

  string var = "log(Fj_chi)" ; string xlabel = "Log(#chi)";
  double xbin = 50; double xmin = -22; double xmax = -2;
  bool save = true;
  //makeHistos_sig_bkg_2plots(dir,fsig,fbkg,var,"Fj_chi>0",xbin,xmin,xmax,xlabel,save);



  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var="Fj_nMj", cut="",10,-0.5,9.5,"# of Microjets", true);
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var="Fj_nMj", cut="Fj_chi>0",10,-0.5,9.5,"# of Microjets", true);
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var="Fj_nMj", cut="Fj_chi<=0",10,-0.5,9.5,"# of Microjets", true);
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var="Fj_nBtagMj", cut="",10,-0.5,9.5,"# of (IVF) btagged Microjets", true);
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var="Fj_nBtagMj", cut="Fj_chi>0",10,-0.5,9.5,"# of (IVF) btagged Microjets", true);
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var="Fj_nBtagMj", cut="Fj_chi<=0",10,-0.5,9.5,"# of (IVF) btagged Microjets", true);


  /*
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var="Mj_pt", cut="",50,0,400, true);
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var="Mj_pt", cut="Fj_chi>0",50,0,400, true);
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var="Mj_pt", cut="Fj_chi<=0",50,0,400, true);
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var="Mj_pt", cut="Mj_isBtag==1",50,0,400, true);
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var="Mj_pt", cut="Fj_chi>0&&Mj_isBtag==1",50,0,400, true);
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var="Mj_pt", cut="Fj_chi<=0&Mj_isBtag==1",50,0,400, true);
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var="Mj_isBtag", cut="",5,-2.5,2.5, true);
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var="Mj_isBtag", cut="Fj_chi>0",5,-2.5,2.5, true);
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var="Mj_isBtag", cut="Fj_chi<=0",5,-2.5,2.5, true);
  */

}

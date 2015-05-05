
using namespace std;

double deltaR(double eta1, double phi1, double eta2, double phi2){
  double dEta = eta1 - eta2;

  double dPhi = phi1 - phi2;
  while (dPhi > TMath::Pi()) dPhi -= 2*TMath::Pi();
  while (dPhi <= -TMath::Pi()) dPhi += 2*TMath::Pi();

  double dR = sqrt(dEta*dEta + dPhi*dPhi);
  return dR;
}


int SVMatch(std::string fdir, std::string fname,double dRmax = 1.2, double MjCone = 0.15, bool display=false, std::string prefix = ""){

  TFile *f = new TFile((fdir+"/"+fname+".root").c_str());

  TDirectory *df = f->GetDirectory("btaganaSubJets");
  TTree *tf = (TTree*) df->Get("ttree");

  const int nEvent = tf->GetEntries();

  const int nGenPrunedMax = 50;

  int nGenPruned;
  int GenPruned_pdgID[nGenPrunedMax];
  float GenPruned_eta[nGenPrunedMax];
  float GenPruned_phi[nGenPrunedMax];
  float GenPruned_pT[nGenPrunedMax];
  int GenPruned_mother[nGenPrunedMax];
  int GenPruned_status[nGenPrunedMax];

  const int nFjMax=10;
  const int nMjMax=50;
  const int nSVMax=50;

  int FatJetInfo_nJet;
  int FatJetInfo_Jet_flavour[nFjMax];
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

  tf->SetBranchAddress("nGenPruned",&nGenPruned);
  tf->SetBranchAddress("GenPruned_pdgID",&GenPruned_pdgID);
  tf->SetBranchAddress("GenPruned_eta",&GenPruned_eta);
  tf->SetBranchAddress("GenPruned_phi",&GenPruned_phi);
  tf->SetBranchAddress("GenPruned_pT",&GenPruned_pT);
  tf->SetBranchAddress("GenPruned_mother",&GenPruned_mother);
  tf->SetBranchAddress("GenPruned_status",&GenPruned_status);

  tf->SetBranchAddress("FatJetInfo.nJet",&FatJetInfo_nJet);
  tf->SetBranchAddress("FatJetInfo.Jet_flavour",&FatJetInfo_Jet_flavour);
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
  float gen_eta;
  float gen_phi;
  int gen_pdgID;
  int gen_motherID;
  int gen_status;

  int Fj_event_idx;
  float Fj_chi;
  float Fj_pt;
  int Fj_flavour;

  int Fj_nBtagMj;
  int Fj_nMj;
  int Fj_nMj_SVMatch;

  const int MjPerFjMax = 10;
  float Mj_pt[MjPerFjMax];
  float Mj_eta[MjPerFjMax];
  float Mj_phi[MjPerFjMax];
  int Mj_isBtag[MjPerFjMax];
  float Mj_dR_SV[MjPerFjMax];

  float Mj_dR_SV_1t1[MjPerFjMax];

  float Mj_dR_gen[MjPerFjMax];
  int Mj_dR_genIdx[MjPerFjMax];
  int Mj_gen_matched_pdgID[MjPerFjMax];
  int Mj_gen_matched_status[MjPerFjMax];
  int Mj_gen_matched_motherID[MjPerFjMax];
  float Mj_gen_matched_pt[MjPerFjMax];
  float Mj_gen_matched_eta[MjPerFjMax];
  float Mj_gen_matched_phi[MjPerFjMax];

  const int GenPerEventMax = 50;

  int Mj_nGen;
  int Mj_gen_pdgID[GenPerEventMax];
  int Mj_gen_motherID[GenPerEventMax];
  int Mj_gen_status[GenPerEventMax];

  int Fj_nSV;
  int Fj_nSV_MjMatch;
  const int SVPerFjMax = 20;
  float SV_pt[SVPerFjMax];
  float SV_eta[SVPerFjMax];
  float SV_phi[SVPerFjMax];
  float SV_dR_Mj[SVPerFjMax];

  cout<<endl;
  cout<<"Creating new root file containing Fatjet based tree: "<< fdir+"/"+prefix+"_"+fname+".root" << endl;
  TFile *fMatch = new TFile((fdir+"/"+prefix+"_"+fname+".root").c_str(),"RECREATE"); //DIFFERENCE BETWEEN USING POINTER???
  TTree *tr_new = new TTree("tree","tree");
  tr_new->Branch("Fj_event_idx",&Fj_event_idx,"Fj_event_idx/I");
  tr_new->Branch("Fj_chi",&Fj_chi,"Fj_chi/F");
  tr_new->Branch("Fj_pt",&Fj_pt,"Fj_pt/F");
  tr_new->Branch("Fj_flavour",&Fj_flavour,"Fj_flavour/I");
  tr_new->Branch("Fj_nMj",&Fj_nMj,"Fj_nMj/I");
  tr_new->Branch("Fj_nBtagMj",&Fj_nBtagMj,"Fj_nBtagMj/I");
  tr_new->Branch("Fj_nMj_SVMatch",&Fj_nMj_SVMatch,"Fj_nMj_SVMatch/I");

  tr_new->Branch("Mj_pt",&Mj_pt,"Mj_pt[Fj_nMj]/F");
  tr_new->Branch("Mj_eta",&Mj_eta,"Mj_eta[Fj_nMj]/F");
  tr_new->Branch("Mj_phi",&Mj_phi,"Mj_phi[Fj_nMj]/F");
  tr_new->Branch("Mj_isBtag",&Mj_isBtag,"Mj_isBtag[Fj_nMj]/I");
  tr_new->Branch("Mj_dR_SV",&Mj_dR_SV,"Mj_dR_SV[Fj_nMj]/F");
  tr_new->Branch("Mj_dR_SV_1t1",&Mj_dR_SV_1t1,"Mj_dR_SV_1t1[Fj_nMj]/F");
  tr_new->Branch("Mj_dR_gen",&Mj_dR_gen,"Mj_dR_gen[Fj_nMj]/F");
  tr_new->Branch("Mj_dR_genIdx",&Mj_dR_genIdx,"Mj_dR_genIdx[Fj_nMj]/I");
  tr_new->Branch("Mj_gen_matched_pdgID",&Mj_gen_matched_pdgID,"Mj_gen_matched_pdgID[Fj_nMj]/I");
  tr_new->Branch("Mj_gen_matched_status",&Mj_gen_matched_status,"Mj_gen_matched_status[Fj_nMj]/I");
  tr_new->Branch("Mj_gen_matched_motherID",&Mj_gen_matched_motherID,"Mj_gen_matched_motherID[Fj_nMj]/I");
  tr_new->Branch("Mj_gen_matched_pt",&Mj_gen_matched_pt,"Mj_gen_matched_pt[Fj_nMj]/F");
  tr_new->Branch("Mj_gen_matched_eta",&Mj_gen_matched_eta,"Mj_gen_matched_eta[Fj_nMj]/F");
  tr_new->Branch("Mj_gen_matched_phi",&Mj_gen_matched_phi,"Mj_gen_matched_phi[Fj_nMj]/F");

  tr_new->Branch("Mj_nGen",&Mj_nGen,"Mj_nGen/I");
  tr_new->Branch("Mj_gen_pdgID",&Mj_gen_pdgID,"Mj_gen_pdgID[Mj_nGen]/I");
  tr_new->Branch("Mj_gen_status",&Mj_gen_status,"Mj_gen_status[Mj_nGen]/I");
  tr_new->Branch("Mj_gen_motherID",&Mj_gen_motherID,"Mj_gen_motherID[Mj_nGen]/I");

  tr_new->Branch("Fj_nSV",&Fj_nSV,"Fj_nSV/I");
  tr_new->Branch("Fj_nSV_MjMatch",&Fj_nSV_MjMatch,"Fj_nSV_MjMatch/I");
  tr_new->Branch("SV_pt",&SV_pt,"SV_pt[Fj_nSV]/F");
  tr_new->Branch("SV_eta",&SV_eta,"SV_eta[Fj_nSV]/F");
  tr_new->Branch("SV_phi",&SV_phi,"SV_phi[Fj_nSV]/F");
  tr_new->Branch("SV_dR_Mj",&SV_dR_Mj,"SV_dR_Mj[Fj_nSV]/F");

  cout << endl;
  cout << "Processing fatjets in "<< fname << endl;
  cout << endl;

  //loop over events
  if(display)cout << endl;
  for (int i =0 ; i<nEvent;i++){
  //for (int i =0 ; i<2;i++){
    if(i%50==0)cout<<"Processing Event "<<i<<endl;
    tf->GetEntry(i);
    if(display)cout << endl;
    if(display)cout << "============  entry : "<< i << ", nFatJet = "<< FatJetInfo_nJet <<"  =============="<< endl;
    //    if(display)cout << endl;

    //loop over fatjets
    for(int j=0; j < FatJetInfo_nJet; j++){
      if(display)cout<<endl;
      if(display)cout<< "Fatjet no. "<< j << " : Fatjet_flavour = " << FatJetInfo_Jet_flavour[j] <<", nSV = " << FatJetInfo_Jet_SV_multi[j] <<endl;
      if(display)cout<<endl;

      Fj_event_idx = i;
      Fj_chi = FatJetInfo_Jet_SD_chi[j];
      Fj_pt = FatJetInfo_Jet_pt[j];
      Fj_flavour = FatJetInfo_Jet_flavour[j];
      Fj_nMj = FatJetInfo_Jet_SD_nMicrojets[j];
      Fj_nBtagMj = FatJetInfo_Jet_SD_nBtagMicrojets[j];
      Fj_nSV = FatJetInfo_Jet_SV_multi[j];

      Fj_nMj_SVMatch = 0;
      Fj_nSV_MjMatch = 0;

      //loop over SV
      int iSV = 0; int first; int last;
      first = FatJetInfo_Jet_nFirstSV[j];
      last = FatJetInfo_Jet_nLastSV[j];
      for(int jSV = first; jSV < last ; jSV++){

	if(display)cout<<endl;
	if(display)cout<< "                 SV no. "<< iSV << endl;

	SV_pt[iSV] = FatJetInfo_SV_vtx_pt[jSV];
	SV_eta[iSV] = FatJetInfo_SV_vtx_eta[jSV];
	SV_phi[iSV] = FatJetInfo_SV_vtx_phi[jSV];
	SV_dR_Mj[iSV] = -9999;

	//Microjet Matching loop (SV_dR_Mj calculation)
	int iMj_=0;
	for(int l = FatJetInfo_Jet_SD_nFirstMicrojet[j] ; l < FatJetInfo_Jet_SD_nLastMicrojet[j] ;l++){

	  double dR_SV_Mj = deltaR(FatJetInfo_SV_vtx_eta[jSV], FatJetInfo_SV_vtx_phi[jSV], FatJetInfo_Jet_SD_Microjet_eta[l], FatJetInfo_Jet_SD_Microjet_phi[l]);

	  if(display)cout<<endl;
	  if(display)cout <<"                             "<< iSV << "-" << iMj_ << ", " << "dR_SV_Mj: "<<dR_SV_Mj<<endl;

	  if(fabs(SV_dR_Mj[iSV]) > dR_SV_Mj && dR_SV_Mj < MjCone){
	    SV_dR_Mj[iSV] = dR_SV_Mj;
	  }

	  if(display)cout<<endl;
	  if(display&&l==FatJetInfo_Jet_SD_nLastMicrojet[j]-1)cout << "                                      -----> SV_dR_Mj["<<iSV<<"]"<<": "<<SV_dR_Mj[iSV]<<" (recorded)" <<endl;

	  iMj_++;
	}//end Mj loop

	if(SV_dR_Mj[iSV]>0) Fj_nSV_MjMatch++;

	iSV++;
      }//end SV loop

      if(display)cout << endl;
      if(display)cout << "                ---------------"<< " nMJet = "<< FatJetInfo_Jet_SD_nMicrojets[j] <<"  -----------"<< endl;
      if(display)cout << endl;

      //loop over Microjets
      int iMj = 0;
      for(int l = FatJetInfo_Jet_SD_nFirstMicrojet[j] ; l < FatJetInfo_Jet_SD_nLastMicrojet[j] ;l++){
	if(display)cout<<endl;
	if(display)cout<< "                Microjet no. "<< l  << " : Mjet_pt    = " << FatJetInfo_Jet_SD_Microjet_pt[l] << endl;
	if(display)cout<< "                           "<<     "      Mjet_isBtag = " << FatJetInfo_Jet_SD_Microjet_isBtag[l]  << endl;

	Mj_pt[iMj] = FatJetInfo_Jet_SD_Microjet_pt[l];
	Mj_eta[iMj] = FatJetInfo_Jet_SD_Microjet_eta[l];
	Mj_phi[iMj] = FatJetInfo_Jet_SD_Microjet_phi[l];
	Mj_isBtag[iMj] = FatJetInfo_Jet_SD_Microjet_isBtag[l];
	Mj_dR_SV[iMj] = -99999;

	Mj_dR_gen[iMj] = -99999;
	Mj_dR_genIdx[iMj] = -99999;
	Mj_gen_matched_pdgID[iMj] = -99999;
	Mj_gen_matched_motherID[iMj] = -99999;
	Mj_gen_matched_status[iMj] = -99999;
	Mj_gen_matched_pt[iMj] = -99999;
	Mj_gen_matched_eta[iMj] = -99999;
	Mj_gen_matched_phi[iMj] = -99999;

	//Gen Mj matching loop
	int ib = 0;
	int mother_idx;
	for(int iGenMj=0; iGenMj < nGenPruned; iGenMj++){

	  if(display)cout<<endl;
	  if(display)cout<< "                             GenPruned no. "<< iGenMj << " : GenPruned_pdgID = " << GenPruned_pdgID[iGenMj] <<endl;
	  if(display)cout<< "                                           "<< iGenMj << " : GenPruned_pT = " << GenPruned_pT[iGenMj] << endl;
	  if(display&&GenPruned_mother[iGenMj]>0)cout<< "                                           "<< iGenMj << " : GenPruned_mother = " << GenPruned_pdgID[GenPruned_mother[iGenMj]] << endl;
	  double dR_Mj = deltaR(GenPruned_eta[iGenMj], GenPruned_phi[iGenMj], FatJetInfo_Jet_SD_Microjet_eta[l], FatJetInfo_Jet_SD_Microjet_phi[l]);
	  if(display)cout<< "                             " << l<< "-"<<iGenMj<<", -------------------------------->  delta R = "<< dR_Mj;// << endl;

	  if(iMj==0){ // loop only once
	    Mj_nGen = nGenPruned;
	    Mj_gen_pdgID[iGenMj] = GenPruned_pdgID[iGenMj];
	    Mj_gen_motherID[iGenMj] = GenPruned_mother[iGenMj];
	    Mj_gen_status[iGenMj] = GenPruned_status[iGenMj];
	  }

	  //matching dR requirement
	  if(dR_Mj<MjCone){

	    if(display)cout<<"----> Mj-Parton MATCH!! ";

	    if(fabs(Mj_dR_gen[iMj])>dR_Mj){ //TO MAKE SURE THIS RECORDS THE SMALLEST deltaR!!

	      if(GenPruned_status[iGenMj]>=21&&GenPruned_status[iGenMj]<=29){ //only consider particles of the hardest subprocess http://home.thep.lu.se/~torbjorn/pythia81html/ParticleProperties.html
		Mj_dR_gen[iMj] = dR_Mj;
		Mj_dR_genIdx[iMj] = ib;
		Mj_gen_matched_pdgID[iMj] = GenPruned_pdgID[iGenMj];
		if(GenPruned_mother[iGenMj]>0)Mj_gen_matched_motherID[iMj] = GenPruned_pdgID[GenPruned_mother[iGenMj]];
		Mj_gen_matched_status[iMj] = GenPruned_status[iGenMj];
		Mj_gen_matched_pt[iMj] = GenPruned_pT[iGenMj];
		Mj_gen_matched_eta[iMj] = GenPruned_eta[iGenMj];
		Mj_gen_matched_phi[iMj] = GenPruned_phi[iGenMj];

		if(display)cout<<"Mj_dR_gen["<<iMj<<"]: "<<Mj_dR_gen[iMj]<<"(recorded)";

	      }//end if check status

	    }//end if record minimum

	  }//end if dR<cone

	  ib++;
	}//end Gen Mj match loop


	//SV Matching loop (Mj_dR_SV calculation)
	if(display)cout<<endl;if(display)cout<<endl;if(display&&Fj_nSV>0)cout<<"                             ---- nSV :"<<Fj_nSV<< "  ----"<<endl;
	int iSV_ = 0;
	for(int jSV = FatJetInfo_Jet_nFirstSV[j]; jSV < FatJetInfo_Jet_nLastSV[j] ; jSV++){

	  double dR_Mj_SV = deltaR(FatJetInfo_SV_vtx_eta[jSV], FatJetInfo_SV_vtx_phi[jSV], FatJetInfo_Jet_SD_Microjet_eta[l], FatJetInfo_Jet_SD_Microjet_phi[l]);

	  if(display)cout<<endl;
	  if(display)cout <<"                             "<< l << "-" << jSV << ", " << "dR_Mj_SV: "<<dR_Mj_SV<<endl;

	  if(fabs(Mj_dR_SV[iMj])>dR_Mj_SV && dR_Mj_SV<MjCone){
	      Mj_dR_SV[iMj] = dR_Mj_SV;
	  }

	  if(display)cout<<endl;
	  if(display&&jSV==FatJetInfo_Jet_nLastSV[j]-1)cout << "                                      -----> Mj_dR_SV["<<iMj<<"]"<<": "<<Mj_dR_SV[iMj]<<" (recorded)" <<endl;

	  iSV_++;
	}//end SV dR loop

	if(Mj_dR_SV[iMj]>0) Fj_nMj_SVMatch++;

	iMj++;
      }//end Mj loop

      //Final correction for one-to-one Mj-SV mat
      //Mj Loop
      int _iMj = 0;
      for(int l = FatJetInfo_Jet_SD_nFirstMicrojet[j] ; l < FatJetInfo_Jet_SD_nLastMicrojet[j] ;l++){

	Mj_dR_SV_1t1[_iMj] = -99999;

	//SV loop
	  int _iSV = 0;
	  for(int jSV = FatJetInfo_Jet_nFirstSV[j]; jSV < FatJetInfo_Jet_nLastSV[j] ; jSV++){

	    if(Mj_dR_SV[_iMj]==SV_dR_Mj[_iSV]) Mj_dR_SV_1t1[_iMj] = Mj_dR_SV[_iMj];

	    _iSV++;
	  }//end SV loop

	  _iMj++;
      }//end Mj Loop


    tr_new->Fill();

    }//end fatjet loop

  }//end event loop
  tr_new->Print();
  fMatch->cd();
  tr_new->Write();

  int tsize = tr_new->GetEntries();
  cout<<tsize<<endl;

  fMatch->Close();
  f->Close();

  return tsize;

}

void SVMatch(bool display = false){
  string dir ="rootfiles";
  string deltaHiggsMass;
  string fsig;
  string fbkg;
  double dRmax = 0.8;
  double MjCone = 0.15;
  string prefix= "FakeMjIVFbtagCalculation";
  //string prefix= "FakeMjAVRbtagCalculation";

  deltaHiggsMass = "HiggsWin20";
  //fbkg = "QCD_Pt-300to470_Tune4C_13TeV_pythia8_R08_r015_"+deltaHiggsMass+"_mc_subjets";
  //fbkg = "QCD_Pt-470to600_Tune4C_13TeV_pythia8_R08_r015_"+deltaHiggsMass+"_mc_subjets";
  //fbkg = "QCD_Pt-470to600_Tune4C_13TeV_pythia8_R08_r015_"+deltaHiggsMass+"_FULL_mc_subjets";
  //fbkg = "QCD_Pt-470to600_Tune4C_13TeV_pythia8_R08_r015_HiggsWin20_fakerate01_MjSVdR015_BTagAllMj_mc_subjets";

  //fbkg = "RelValProdTTbar_13_AOD_R08_r015_HiggsWin20_tagr07_fake02_BtagALLMj_MjIVF015_mc_subjets";
  //int bkg = SVMatch(dir,fbkg,dRmax,MjCone,display,prefix);

  //fbkg = "QCD_Pt-300to470_Tune4C_13TeV_pythia8_R08_r015_HiggsWin20_tagr07_fake02_BtagALLMj_MjIVF015_mc_subjets";
  //bkg = SVMatch(dir,fbkg,dRmax,MjCone,display,prefix);

  //fbkg = "QCD_Pt-470to600_Tune4C_13TeV_pythia8_R08_r015_HiggsWin20_tagr07_fake02_BtagALLMj_MjIVF015_mc_subjets";
  //bkg = SVMatch(dir,fbkg,dRmax,MjCone,display,prefix);

  //fbkg = "QCD_Pt-470to600_Tune4C_13TeV_pythia8_R08_r015_AkMj_HiggsWin30_tagr07_fake02_BtagALLMj_MjIVF015_mc_subjets";
  //int bkg = SVMatch(dir,fbkg,dRmax,MjCone,display,prefix);

  fbkg = "QCD_Pt-470to600_Tune4C_13TeV_pythia8_R08_r015_CAMj_HiggsWin30_tagr07_fake02_BtagALLMj_MjIVF015_mc_subjets";
  int bkg = SVMatch(dir,fbkg,dRmax,MjCone,display,prefix);
}




using namespace std;

double deltaR(double eta1, double phi1, double eta2, double phi2){
  double dEta = eta1 - eta2;

  double dPhi = phi1 - phi2;
  while (dPhi > TMath::Pi()) dPhi -= 2*TMath::Pi();
  while (dPhi <= -TMath::Pi()) dPhi += 2*TMath::Pi();

  double dR = sqrt(dEta*dEta + dPhi*dPhi);
  return dR;
}


int PartonMatch(std::string fdir, std::string fname, int gen_pdgid,double dRmax = 1.2, double MjCone = 0.15, bool display=false, std::string postfix = ""){

  TFile *f = new TFile((fdir+"/"+fname+".root").c_str());

  //TDirectory *d = f->GetDirectory("btagana");
  TDirectory *d = f->GetDirectory("btaganaSubJets");
  TTree *t = (TTree*)d->Get("ttree");
  TDirectory *df = f->GetDirectory("btaganaSubJets");
  TTree *tf = (TTree*)df->Get("ttree");

  const int nEvent = t->GetEntries();
  int nMatchMax = 0;
  vector<int> iEventOverMatch;

  const int nGenPrunedMax = 50;

  int nGenPruned;
  int GenPruned_pdgID[nGenPrunedMax];
  float GenPruned_eta[nGenPrunedMax];
  float GenPruned_phi[nGenPrunedMax];
  float GenPruned_pT[nGenPrunedMax];
  int GenPruned_mother[nGenPrunedMax];
  int GenPruned_status[nGenPrunedMax];

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
  t->SetBranchAddress("GenPruned_mother",&GenPruned_mother);
  t->SetBranchAddress("GenPruned_status",&GenPruned_status);

  tf->SetBranchAddress("FatJetInfo.nJet",&FatJetInfo_nJet);
  tf->SetBranchAddress("FatJetInfo.Jet_eta",&FatJetInfo_Jet_eta);
  tf->SetBranchAddress("FatJetInfo.Jet_phi",&FatJetInfo_Jet_phi);
  tf->SetBranchAddress("FatJetInfo.Jet_SD_chi",&FatJetInfo_Jet_SD_chi);
  tf->SetBranchAddress("FatJetInfo.Jet_pt",&FatJetInfo_Jet_pt);
  tf->SetBranchAddress("FatJetInfo.Jet_SD_nBtagMicrojets",&FatJetInfo_Jet_SD_nBtagMicrojets);

  tf->SetBranchAddress("FatJetInfo.Jet_SD_nMicrojets",&FatJetInfo_Jet_SD_nMicrojets);
  tf->SetBranchAddress("FatJetInfo.Jet_SD_nFirstMicrojet",&FatJetInfo_Jet_SD_nFirstMicrojet);
  tf->SetBranchAddress("FatJetInfo.Jet_SD_nLasttMicrojet",&FatJetInfo_Jet_SD_nLastMicrojet);
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
  float Mj_dR_SV[MjPerFjMax];
  float Mj_dR_SV_gen[MjPerFjMax];
  float Mj_dR[MjPerFjMax];
  int Mj_dR_genIdx[MjPerFjMax];
  int Mj_gen_matched_pdgID[MjPerFjMax];
  int Mj_gen_matched_status[MjPerFjMax];
  int Mj_gen_matched_motherID[MjPerFjMax];
  float Mj_gen_matched_pt[MjPerFjMax];
  float Mj_gen_matched_eta[MjPerFjMax];
  float Mj_gen_matched_phi[MjPerFjMax];

  int nMj_gen = 30; //4 b's
  const int nMjGenMax = 30;
  float Mj_gen_pt[nMjGenMax];
  int Mj_gen_pdgID[nMjGenMax];
  int Mj_gen_motherID[nMjGenMax];
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
  tr_new->Branch("gen_eta",&gen_eta,"gen_eta/F");
  tr_new->Branch("gen_phi",&gen_phi,"gen_phi/F");
  tr_new->Branch("gen_pdgID",&gen_pdgID,"gen_pdgID/I");
  tr_new->Branch("Fj_nMj",&Fj_nMj,"Fj_nMj/I");
  tr_new->Branch("Fj_nBtagMj",&Fj_nBtagMj,"Fj_nBtagMj/I");
  tr_new->Branch("Mj_pt",&Mj_pt,"Mj_pt[Fj_nMj]/F");
  tr_new->Branch("Mj_eta",&Mj_eta,"Mj_eta[Fj_nMj]/F");
  tr_new->Branch("Mj_phi",&Mj_phi,"Mj_phi[Fj_nMj]/F");
  tr_new->Branch("Mj_isBtag",&Mj_isBtag,"Mj_isBtag[Fj_nMj]/I");
  tr_new->Branch("Mj_dR_SV",&Mj_dR_SV,"Mj_dR_SV[Fj_nMj]/F");
  tr_new->Branch("Mj_dR",&Mj_dR,"Mj_dR[Fj_nMj]/F");
  tr_new->Branch("Mj_dR_genIdx",&Mj_dR_genIdx,"Mj_dR_genIdx[Fj_nMj]/I");
  tr_new->Branch("Mj_gen_matched_pdgID",&Mj_gen_matched_pdgID,"Mj_gen_matched_pdgID[Fj_nMj]/I");
  tr_new->Branch("Mj_gen_matched_status",&Mj_gen_matched_status,"Mj_gen_matched_status[Fj_nMj]/I");
  tr_new->Branch("Mj_gen_matched_motherID",&Mj_gen_matched_motherID,"Mj_gen_matched_motherID[Fj_nMj]/I");
  tr_new->Branch("Mj_gen_matched_pt",&Mj_gen_matched_pt,"Mj_gen_matched_pt[Fj_nMj]/F");
  tr_new->Branch("Mj_gen_matched_eta",&Mj_gen_matched_eta,"Mj_gen_matched_eta[Fj_nMj]/F");
  tr_new->Branch("Mj_gen_matched_phi",&Mj_gen_matched_phi,"Mj_gen_matched_phi[Fj_nMj]/F");
  tr_new->Branch("Mj_dR_SV_gen",&Mj_dR_SV_gen,"Mj_dR_SV_gen[Fj_nMj]/F");

  tr_new->Branch("Mj_gen_pt",&Mj_gen_pt,"Mj_gen_pt[30]/F");
  tr_new->Branch("Mj_gen_pdgID",&Mj_gen_pdgID,"Mj_gen_pdgID[30]/I");
  tr_new->Branch("Mj_gen_motherID",&Mj_gen_motherID,"Mj_gen_motherID[30]/I");
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
  //for (int i =0 ; i<4;i++){
    if(i%50==0)cout<<"Processing Event "<<i<<endl;
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
	if(abs(GenPruned_pdgID[k])!=gen_pdgid) continue;
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
	  gen_eta = GenPruned_eta[k];
	  gen_phi = GenPruned_phi[k];
	  gen_pdgID = GenPruned_pdgID[k];
	  Fj_pt = FatJetInfo_Jet_pt[j];
	  Fj_nMj = FatJetInfo_Jet_SD_nMicrojets[j];
	  Fj_nBtagMj = FatJetInfo_Jet_SD_nBtagMicrojets[j];
	  Fj_nSV = FatJetInfo_Jet_SV_multi[j];

	  for(int ib_ =0; ib_<nMjGenMax;ib_++)Mj_gen_isMatch[ib_]=0; //initialize recon status of b quarks
	  for(int ib_ =0; ib_<nMjGenMax;ib_++)Mj_gen_pt[ib_]=-9999; //initialize pt of b quarks
	  for(int ib_ =0; ib_<nMjGenMax;ib_++)Mj_gen_pdgID[ib_]=-9999; //initialize pt of b quarks
	  for(int ib_ =0; ib_<nMjGenMax;ib_++)Mj_gen_motherID[ib_]=-9999; //initialize pt of b quarks

	  //loop over SV
	  int iSV = 0; int first; int last;
	  first = FatJetInfo_Jet_nFirstSV[j];
	  last = FatJetInfo_Jet_nLastSV[j];
	  for(int jSV = first; jSV < last ; jSV++){
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
	    Mj_gen_matched_motherID[iMj] = -99999;
	    Mj_gen_matched_pt[iMj] = -99999;
	    Mj_gen_matched_eta[iMj] = -99999;
	    Mj_gen_matched_phi[iMj] = -99999;

	    Mj_dR_SV[iMj] = -99999;
	    Mj_dR_SV_gen[iMj] = -99999;

	    //Gen Mj matching loop
	    int ib = 0;
	    int mother_idx;
	    for(int iGenMj=0; iGenMj < nGenPruned; iGenMj++){


	      if(abs(GenPruned_pdgID[iGenMj])==gen_pdgid) continue; // dont match with fatjet gen

	      Mj_gen_pt[ib] = GenPruned_pT[iGenMj];
	      Mj_gen_pdgID[ib] = GenPruned_pdgID[iGenMj];
	      if(GenPruned_mother[iGenMj]>0)Mj_gen_motherID[ib] = GenPruned_pdgID[GenPruned_mother[iGenMj]];


	      if(display)cout<<endl;
	      if(display)cout<< "                             GenPruned no. "<< iGenMj << " : GenPruned_pdgID = " << GenPruned_pdgID[iGenMj] <<endl;
	      if(display)cout<< "                                           "<< iGenMj << " : GenPruned_pT = " << GenPruned_pT[iGenMj] << endl;
	      if(display&&GenPruned_mother[iGenMj]>0)cout<< "                                           "<< iGenMj << " : GenPruned_mother = " << GenPruned_pdgID[GenPruned_mother[iGenMj]] << endl;
	      double dR_Mj = deltaR(GenPruned_eta[iGenMj], GenPruned_phi[iGenMj], FatJetInfo_Jet_SD_Microjet_eta[l], FatJetInfo_Jet_SD_Microjet_phi[l]);
	      if(display)cout<< "                             " << l<< "-"<<iGenMj<<", -------------------------------->  delta R = "<< dR_Mj;// << endl;

	      //matching dR requirement
	      if(dR_Mj<MjCone){

		if(display)cout<<"----> Mj-Parton MATCH!! ";

		if(fabs(Mj_dR[iMj])>dR_Mj){ //TO MAKE SURE THIS RECORDS THE SMALLEST deltaR!!

		  if(GenPruned_status[iGenMj]>=21&&GenPruned_status[iGenMj]<=29){ //only consider particles of the hardest subprocess http://home.thep.lu.se/~torbjorn/pythia81html/ParticleProperties.html
		    Mj_dR[iMj] = dR_Mj;
		    Mj_dR_genIdx[iMj] = ib;
		    Mj_gen_matched_pdgID[iMj] = GenPruned_pdgID[iGenMj];
		    if(GenPruned_mother[iGenMj]>0)Mj_gen_matched_motherID[iMj] = GenPruned_pdgID[GenPruned_mother[iGenMj]];
		    Mj_gen_matched_pt[iMj] = GenPruned_pT[iGenMj];
		    Mj_gen_matched_eta[iMj] = GenPruned_eta[iGenMj];
		    Mj_gen_matched_phi[iMj] = GenPruned_phi[iGenMj];
		    Mj_gen_isMatch[ib] = 1;
		    iMatchMj++;

		    if(display)cout<<"Mj_dR["<<iMj<<"]: "<<Mj_dR[iMj]<<"(recorded)";

		  }//end if check status

		}//end if record minimum

	      }//end if dR<cone

	      ib++;
	    }//end Gen Mj match loop

	    //SV Matching loop (Mj_dR_SV calculation)
	    if(display)cout<<endl;if(display)cout<<endl;if(display&&Fj_nSV>0)cout<<"                             ----SV matching info----"<<endl;
	    for(int jSV = FatJetInfo_Jet_nFirstSV[j]; jSV < FatJetInfo_Jet_nLastSV[j] ; jSV++){
	      double dR_Mj_SV = deltaR(FatJetInfo_SV_vtx_eta[jSV], FatJetInfo_SV_vtx_phi[jSV], FatJetInfo_Jet_SD_Microjet_eta[l], FatJetInfo_Jet_SD_Microjet_phi[l]);
	      if(display)cout<<endl;
	      if(display)cout <<"                             "<< l << "-" << jSV << ", " << "dR_Mj_SV: "<<dR_Mj_SV<<endl;
	      if(fabs(Mj_dR_SV[iMj])<dR_Mj_SV) continue; //TO MAKE SURE THIS RECORDS THE SMALLEST deltaR!!
	      Mj_dR_SV[iMj] = dR_Mj_SV;
	      if(display)cout << "                                      -----> Mj_dR_SV["<<iMj<<"]"<<": "<<Mj_dR_SV[iMj]<<" (recorded)" <<endl;

	      if(Mj_gen_matched_pt[iMj]<0) continue;
	      Mj_dR_SV_gen[iMj] = deltaR(Mj_gen_matched_eta[iMj], Mj_gen_matched_phi[iMj], FatJetInfo_SV_vtx_eta[jSV], FatJetInfo_SV_vtx_phi[jSV]);
	      if(display)cout << "                                      -----> Mj_dR_SV_gen["<<iMj<<"]"<<": "<<Mj_dR_SV_gen[iMj] <<endl;
	      if(display)cout << "                                      gen: "<<Mj_gen_matched_eta[iMj]<<", "<< Mj_gen_matched_phi[iMj]<<", SV: "<<FatJetInfo_SV_vtx_eta[jSV]<<", "<<FatJetInfo_SV_vtx_phi[jSV]<< endl;


	    }//end SV dR loop

	    iMj++;
	  }//end Mj loop
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
    for(int l =0 ; l<iEventOverMatch.size(); l++) if(display)cout << iEventOverMatch[l] <<", " << endl;
  }

  int tsize = tr_new->GetEntries();
  cout<<tsize<<endl;

  fMatch->Close();
  f->Close();

  return tsize;

}

void PartonMatch(bool display = false){
  string dir ="rootfiles";
  string deltaHiggsMass;
  string fsig;
  string fbkg;
  double dRmax = 0.8;
  double MjCone = 0.15;
  string postfix= "dRmax08_NoGenPtCut_NoFjPtCut_AllChi";

  int sig_l; int bkg_l;

  deltaHiggsMass = "HiggsWin10";
  fsig = "Rad_HHto4b_M800_13TeV_AOD_R08_r015_"+deltaHiggsMass+"_mc_subjets";
  fbkg = "ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola_R08_r015_"+deltaHiggsMass+"_mc_subjets";
  sig_l = PartonMatch(dir,fsig,25,dRmax,MjCone,display,postfix);
  bkg_l = PartonMatch(dir,fbkg,6,dRmax,MjCone,display,postfix);

  deltaHiggsMass = "HiggsWin20";
  //deltaHiggsMass = "HiggsWin20_WRONGtagrate35";
  fsig = "Rad_HHto4b_M800_13TeV_AOD_R08_r015_"+deltaHiggsMass+"_mc_subjets";
  fbkg = "ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola_R08_r015_"+deltaHiggsMass+"_mc_subjets";
  sig_l = PartonMatch(dir,fsig,25,dRmax,MjCone,display,postfix);
  bkg_l = PartonMatch(dir,fbkg,6,dRmax,MjCone,display,postfix);

  deltaHiggsMass = "HiggsWin30";
  fsig = "Rad_HHto4b_M800_13TeV_AOD_R08_r015_"+deltaHiggsMass+"_mc_subjets";
  fbkg = "ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola_R08_r015_"+deltaHiggsMass+"_mc_subjets";
  sig_l = PartonMatch(dir,fsig,25,dRmax,MjCone,display,postfix);
  bkg_l = PartonMatch(dir,fbkg,6,dRmax,MjCone,display,postfix);


}

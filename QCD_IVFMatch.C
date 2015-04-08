
using namespace std;

int IVFMatch(std::string fdir, std::string fname,double dRmax = 1.2, double MjCone = 0.15, bool display=false, std::string prefix = ""){

  TFile *f = new TFile((fdir+"/"+fname+".root").c_str());

  TDirectoryFile *d = f->GetDirectory("btaganaSubJets");
  TTree *t = d->Get("ttree");
  TDirectoryFile *df = f->GetDirectory("btaganaSubJets");
  TTree *tf = df->Get("ttree");

  const int nEvent = t->GetEntries();

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

  tf->SetBranchAddress("FatJetInfo.nJet",&FatJetInfo_nJet);
  tf->SetBranchAddress("FatJetInfo.Jet_flavour",&FatJetInfo_Jet_flavour);
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
  //for (int i =0 ; i<20;i++){
    if(i%50==0)cout<<"Processing Event "<<i<<endl;
    t->GetEntry(i);
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
	  if(display&jSV==FatJetInfo_Jet_nLastSV[j]-1)cout << "                                      -----> Mj_dR_SV["<<iMj<<"]"<<": "<<Mj_dR_SV[iMj]<<" (recorded)" <<endl;

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

void IVFMatch(bool display = false){
  string dir ="rootfiles";
  string deltaHiggsMass;
  string fsig;
  string fbkg;
  double dRmax = 0.8;
  double MjCone = 0.15;
  string prefix= "FakeMjIVFbtagCalculation";

  deltaHiggsMass = "HiggsWin20";
  fbkg = "QCD_Pt-470to600_Tune4C_13TeV_pythia8_R08_r015_"+deltaHiggsMass+"_mc_subjets";

  int bkg = IVFMatch(dir,fbkg,dRmax,MjCone,display,prefix);
}

double deltaR(double eta1, double phi1, double eta2, double phi2){
  double dEta = eta1 - eta2;

  double dPhi = phi1 - phi2;
  while (dPhi > TMath::Pi()) dPhi -= 2*TMath::Pi();
  while (dPhi <= -TMath::Pi()) dPhi += 2*TMath::Pi();

  double dR = sqrt(dEta*dEta + dPhi*dPhi);
  return dR;
}

TH1D* makeHisto_1plot(std::string dir,  std::string fname,  std::string var, std::string cut,  double xbin, double xmin, double xmax, std::string xlabel, std::string prefix, Color_t color = kBlue, int linestyle = 1,bool save = false, bool saveroot = false){

  TFile *f = new TFile((dir+"/"+prefix+"_"+fname+".root").c_str());

  string var_ = var;
  if(var_=="log(Fj_chi)") var_ = "logChi"; //log(Fj_chi) become log( for some reason??

  TCanvas* cvs = new TCanvas((var_+prefix).c_str(),(var_+prefix).c_str(),800,600);

  TTree *t = f->Get("tree");

  TH1D* h = new TH1D ((var_+prefix).c_str(),(var_+prefix).c_str(),xbin,xmin,xmax);

  t->Draw((var+">>"+var_+prefix).c_str(),cut.c_str());

  gStyle->SetOptStat("nemrou");

  h->SetLineWidth(2);
  h->SetLineColor(color);
  h->SetLineStyle(linestyle);
  h->GetXaxis()->SetTitle(xlabel.c_str());
  h->GetYaxis()->SetTitle("");
  h->SetTitle("");

  delete t;
  if(save)cvs->SaveAs((dir+"/"+fname+"_"+var_+"_"+cut+".eps").c_str());

  if(saveroot)TFile *fout = new TFile((dir+"/"+"PLOTS_"+fname+"_"+var_+"_"+cut+".root").c_str(),"RECREATE");
  if(saveroot)fout->cd();
  if(saveroot)h->Write("h");
  if(saveroot)fout->Close();

  return h;
}


void Alakazam(){
  string dir ="rootfiles";
  string deltaHiggsMass;
  string fsig;
  string fbkg;
  double dRmax = 0.8;
  double MjCone = 0.15;
  string prefix= "FakeMjIVFbtagCalculation";

  double xbin; double xmin; double xmax; string xlabel;
  double ybin; double ymin; double ymax; string ylabel;
  string var; string var_gen; string var1; string var2;
  string cut;
  bool save; bool saveroot;

  deltaHiggsMass = "HiggsWin20";
  fsig = "Rad_HHto4b_M800_13TeV_AOD_R08_r015_"+deltaHiggsMass+"_mc_subjets";
  fbkg2 = "ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola_R08_r015_"+deltaHiggsMass+"_mc_subjets";
  fbkg = "QCD_Pt-470to600_Tune4C_13TeV_pythia8_R08_r015_HiggsWin20_mc_subjets"+deltaHiggsMass+"_mc_subjets";

  var = "Mj_dR_SV";
  xbin = 45; xmin = 0; xmax = 0.15; xlabel = "Microjet-IVF SV #Delta R matching";
  save = true; saveroot = true;
  makeHistos_1plot(dir,fsig,var,"",xbin,xmin,xmax,xlabel,prefix,kBlue,1,save,saveroot);
  makeHistos_1plot(dir,fbkg,var,"",xbin,xmin,xmax,xlabel,prefix,kRed,1,save);

  //Mj study  sequence

  var = "Mj_pt";
  xbin = 50; xmin = 0; xmax = 500; xlabel = "Microjet p_{T}";
  save = false;
  makeHistos_1plot(dir,fsig,var,"",xbin,xmin,xmax,xlabel,prefix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"",xbin,xmin,xmax,xlabel,prefix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"Mj_dR>0",xbin,xmin,xmax,xlabel,prefix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0",xbin,xmin,xmax,xlabel,prefix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"Mj_dR>0&&Mj_isBtag==1",xbin,xmin,xmax,xlabel,prefix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_isBtag==1",xbin,xmin,xmax,xlabel,prefix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"Mj_dR>0&&Mj_isBtag==-1",xbin,xmin,xmax,xlabel,prefix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_isBtag==-1",xbin,xmin,xmax,xlabel,prefix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"Mj_dR>0&&Mj_isBtag==1&&abs(Mj_gen_matched_pdgID)==5",xbin,xmin,xmax,xlabel,prefix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_isBtag==1&&abs(Mj_gen_matched_pdgID)==5",xbin,xmin,xmax,xlabel,prefix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"Mj_dR>0&&Mj_isBtag==-1&&abs(Mj_gen_matched_pdgID)==5",xbin,xmin,xmax,xlabel,prefix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_isBtag==-1&&abs(Mj_gen_matched_pdgID)==5",xbin,xmin,xmax,xlabel,prefix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"Mj_dR>0&&Mj_isBtag==1&&abs(Mj_gen_matched_pdgID)!=5",xbin,xmin,xmax,xlabel,prefix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_isBtag==1&&abs(Mj_gen_matched_pdgID)!=5",xbin,xmin,xmax,xlabel,prefix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"Mj_dR>0&&Mj_isBtag==-1&&abs(Mj_gen_matched_pdgID)!=5",xbin,xmin,xmax,xlabel,prefix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_isBtag==-1&&abs(Mj_gen_matched_pdgID)!=5",xbin,xmin,xmax,xlabel,prefix,kRed,1,save);
  //
  makeHistos_1plot(dir,fsig,var,"Mj_dR>0&&Mj_dR<0.04",xbin,xmin,xmax,xlabel,prefix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_dR<0.04",xbin,xmin,xmax,xlabel,prefix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==1",xbin,xmin,xmax,xlabel,prefix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==1",xbin,xmin,xmax,xlabel,prefix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==-1",xbin,xmin,xmax,xlabel,prefix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==-1",xbin,xmin,xmax,xlabel,prefix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==1&&abs(Mj_gen_matched_pdgID)==5",xbin,xmin,xmax,xlabel,prefix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==1&&abs(Mj_gen_matched_pdgID)==5",xbin,xmin,xmax,xlabel,prefix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==-1&&abs(Mj_gen_matched_pdgID)==5",xbin,xmin,xmax,xlabel,prefix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==-1&&abs(Mj_gen_matched_pdgID)==5",xbin,xmin,xmax,xlabel,prefix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==1&&abs(Mj_gen_matched_pdgID)!=5",xbin,xmin,xmax,xlabel,prefix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==1&&abs(Mj_gen_matched_pdgID)!=5",xbin,xmin,xmax,xlabel,prefix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==-1&&abs(Mj_gen_matched_pdgID)!=5",xbin,xmin,xmax,xlabel,prefix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==-1&&abs(Mj_gen_matched_pdgID)!=5",xbin,xmin,xmax,xlabel,prefix,kRed,1,save);

}

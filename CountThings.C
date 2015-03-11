TTree* CountThings(std::string fname, std::string dir = "btagana"){
  TFile *f = new TFile(fname.c_str());
  TDirectoryFile *d = f->GetDirectory(dir.c_str());
  TTree *t = d->Get("ttree");
  return t;
}

void CountFatJets(std::string fname, std::string dir = "btaganaSubJets"){
  TTree *t = CountThings(fname,dir);
  int fj = t->Draw("FatJetInfo.Jet_pt","");
  cout<<"Number of Fatjets = "<< fj <<endl;

  int nChi = t->Draw("FatJetInfo.Jet_SD_chi","");
  int nChi_valid = t->Draw("FatJetInfo.Jet_SD_chi","FatJetInfo.Jet_SD_chi>0");
  int nChi_invalid = t->Draw("FatJetInfo.Jet_SD_chi","FatJetInfo.Jet_SD_chi<=0");

  cout<< "Number of calculated chi's = "<< nChi << "(valid = "<<nChi_valid<<", invalid = "<< nChi_invalid <<" )"<<endl;
  delete t;
}


void CountGen(std::string fname,std::string pdgid){
  TTree *t = CountThings(fname,"btagana");
  int fj = t->Draw("GenPruned_pT",("GenPruned_pdgID=="+pdgid).c_str());
  cout<<"Number of Gen Particles = "<<fj<<endl;
  delete t;
}



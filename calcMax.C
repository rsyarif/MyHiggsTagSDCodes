void calcMax(std::string fname){

  //TFile *f = new TFile("RadionHH_M800_R12_r15_correctIVFmatch_mc_subjets.root");
  TFile *f = new TFile(fname.c_str());
  TDirectoryFile *d = f->GetDirectory("btagana");
  TTree *t = d->Get("ttree");

  TDirectoryFile *df = f->GetDirectory("btaganaSubJets");
  TTree *tf = df->Get("ttree");

  int nGenPruned;
  int nGenPrunedMax;
  int nFj;
  int nFjMax;

  t->SetBranchAddress("nGenPruned",&nGenPruned);
  tf->SetBranchAddress("FatJetInfo.nJet",&nFj);

  //loop over events
  for (int i =0 ; i<t->GetEntries();i++){
    t->GetEntry(i);
    tf->GetEntry(i);
    if (nGenPruned>nGenPrunedMax) nGenPrunedMax = nGenPruned;
    if (nFj>nFjMax) nFjMax = nFj;
  }

  std::cout<<"nEvent = "<< t->GetEntries() << endl;
  std::cout<<"nGenPrunedMax = "<<nGenPrunedMax<< ", nFjMax = "<< nFjMax<<std::endl;
}



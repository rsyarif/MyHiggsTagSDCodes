
TTree* AccessTree(std::string fname, std::string dir = "btagana"){
  TFile *f = new TFile(fname.c_str());
  TDirectoryFile *d = f->GetDirectory(dir.c_str());
  TTree *t = d->Get("ttree");
  return t;
}

void AccessTreePrint(std::string fname, std::string dir = "btagana"){
  TTree *t = AccessTree(fname,dir);
  t->Print();
}

void AccessTreeDraw(std::string fname, std::string dir = "btagana", std::string var, std::string cut){
  TTree *t = AccessTree(fname,dir);
  t->Draw(var.c_str(),cut.c_str());
}



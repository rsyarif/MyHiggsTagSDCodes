
{
  TFile *f = new TFile("RadionHH_M800_R12_r15_correctIVFmatch_mc_subjets.root");
  TDirectoryFile *d = f->GetDirectory("btagana");
  TTree *t = d->Get("ttree");
}

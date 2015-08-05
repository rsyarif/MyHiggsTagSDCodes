#include "Plot_LogChi_ROC_TChain.h"

void makeHistos_3bkg_optimization_Hwin_300470(){
  vector<TString> chains; cout<< "Chaining files ..."<<endl;
  vector<string> postfix;
  vector<string> labels;
  TString info;

  info = "signal: Rad->HH M1200";
  //1st set
  postfix.push_back("RadM1200_KtHW20tag07fake02_pt300470"); labels.push_back("#DeltaM_{H}=20, tag70%, fake 20%");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M1200_13TeV_PHYS14_25_V1/Rad_M1200_kT015_Hwin20_tag07_fake02/150703_004008/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola/Zpr_M1000_kT015_Hwin20_tag07_fake02/150703_215830/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-300to470_Tune4C_13TeV_pythia8/QCDpt300_kT015_Hwin20_tag07_fake02/150706_204430/0000/*.root");
  //2nd set
  postfix.push_back("RadM1200_KtHW30tag07fake02_pt300470"); labels.push_back("#DeltaM_{H}=30, tag 70% fake 20%");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M1200_13TeV_PHYS14_25_V1/Rad_M1200_kT015_Hwin30_tag07_fake02/150703_003908/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola/Zpr_M1000_kT015_Hwin30_tag07_fake02/150703_215645/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-300to470_Tune4C_13TeV_pythia8/QCDpt300_kT015_Hwin30_tag07_fake02/150706_204303/0000/*.root");

  makeHistos_3bkg_optimization(chains,postfix,labels,"300","470", info);
}

void makeHistos_3bkg_optimization_fake_300470(){
  vector<TString> chains; cout<< "Chaining files ..."<<endl;
  vector<string> postfix;
  vector<string> labels;
  TString info;

  info = "signal: Rad->HH M1200";
  //1st set
  postfix.push_back("RadM1200_KtHW30tag07fake001_pt300470"); labels.push_back("#DeltaM_{H}=30, tag70%, fake 1%");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M1200_13TeV_PHYS14_25_V1/Rad_M1200_kT015_Hwin30_tag07_fake001/150703_003759/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola/Zpr_M1000_kT015_Hwin30_tag07_fake001/150703_215615/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-300to470_Tune4C_13TeV_pythia8/QCDpt300_kT015_Hwin30_tag07_fake001/150708_022817/0000/*.root");
  //2nd set
  postfix.push_back("RadM1200_KtHW30tag07fake02_pt300470"); labels.push_back("#DeltaM_{H}=30, tag 70% fake 20%");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M1200_13TeV_PHYS14_25_V1/Rad_M1200_kT015_Hwin30_tag07_fake02/150703_003908/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola/Zpr_M1000_kT015_Hwin30_tag07_fake02/150703_215645/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-300to470_Tune4C_13TeV_pythia8/QCDpt300_kT015_Hwin30_tag07_fake02/150706_204303/0000/*.root"); 

  makeHistos_3bkg_optimization(chains,postfix,labels,"300","470", info);
}

void makeHistos_3bkg_optimization_MjCone10_300470(){
  vector<TString> chains; cout<< "Chaining files ..."<<endl;
  vector<string> postfix;
  vector<string> labels;
  TString info;

  info = "signal: Rad->HH M1200";
  //1st set
  postfix.push_back("RadM1200_KtR010HW30tag07fake02_pt300470"); labels.push_back("Kt R=0.10");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M1200_13TeV_PHYS14_25_V1/Rad_M1200_kT010_Hwin30_tag07_fake02/150703_004111/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola/Zpr_M1000_kT010_Hwin30_tag07_fake02/150703_215908/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-300to470_Tune4C_13TeV_pythia8/QCDpt300_kT010_Hwin30_tag07_fake02/150706_204619/0000/*.root");
  //2nd set
  postfix.push_back("RadM1200_KtR015HW30tag07fake02_pt300470"); labels.push_back("Kt R=0.15");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M1200_13TeV_PHYS14_25_V1/Rad_M1200_kT015_Hwin30_tag07_fake02/150703_003908/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola/Zpr_M1000_kT015_Hwin30_tag07_fake02/150703_215645/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-300to470_Tune4C_13TeV_pythia8/QCDpt300_kT015_Hwin30_tag07_fake02/150706_204303/0000/*.root"); 

  makeHistos_3bkg_optimization(chains,postfix,labels,"300","470", info);
}

void makeHistos_3bkg_optimization_MjCone20_300470(){
  vector<TString> chains; cout<< "Chaining files ..."<<endl;
  vector<string> postfix;
  vector<string> labels;
  TString info;

  info = "signal: Rad->HH M1200";
  //1st set
  postfix.push_back("RadM1200_KtR020HW30tag07fake02_pt300470"); labels.push_back("Kt R=0.20");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M1200_13TeV_PHYS14_25_V1/Rad_M1200_kT020_Hwin30_tag07_fake02/150703_004216/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola/Zpr_M1000_kT020_Hwin30_tag07_fake02/150703_215948/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-300to470_Tune4C_13TeV_pythia8/QCDpt300_kT020_Hwin30_tag07_fake02/150706_204757/0000/*.root");
  //2nd set
  postfix.push_back("RadM1200_KtR015HW30tag07fake02_pt300470"); labels.push_back("Kt R=0.15");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M1200_13TeV_PHYS14_25_V1/Rad_M1200_kT015_Hwin30_tag07_fake02/150703_003908/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola/Zpr_M1000_kT015_Hwin30_tag07_fake02/150703_215645/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-300to470_Tune4C_13TeV_pythia8/QCDpt300_kT015_Hwin30_tag07_fake02/150706_204303/0000/*.root"); 

  makeHistos_3bkg_optimization(chains,postfix,labels,"300","470", info);
}

void makeHistos_3bkg_optimization_tag_300470(){
  vector<TString> chains; cout<< "Chaining files ..."<<endl;
  vector<string> postfix;
  vector<string> labels;
  TString info;

  info = "signal: Rad->HH M1200";
  //1st set
  postfix.push_back("RadM1200_KtHW30tag06fake02_pt300470"); labels.push_back("#DeltaM_{H}=30, tag 60%, fake 20%");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M1200_13TeV_PHYS14_25_V1/Rad_M1200_kT015_Hwin30_tag06_fake02/150703_004312/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola/Zpr_M1000_kT015_Hwin30_tag06_fake02/150703_220034/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-300to470_Tune4C_13TeV_pythia8/QCDpt300_kT015_Hwin30_tag06_fake02/150706_204955/0000/*.root");
  //2nd set
  postfix.push_back("RadM1200_KtHW30tag07fake02_pt300470"); labels.push_back("#DeltaM_{H}=30, tag 70% fake 20%");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M1200_13TeV_PHYS14_25_V1/Rad_M1200_kT015_Hwin30_tag07_fake02/150703_003908/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola/Zpr_M1000_kT015_Hwin30_tag07_fake02/150703_215645/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-300to470_Tune4C_13TeV_pythia8/QCDpt300_kT015_Hwin30_tag07_fake02/150706_204303/0000/*.root"); 

  makeHistos_3bkg_optimization(chains,postfix,labels,"300","470", info);
}

void makeHistos_3bkg_optimization_Hwin_470600(){
  vector<TString> chains; cout<< "Chaining files ..."<<endl;
  vector<string> postfix;
  vector<string> labels;
  TString info;

  info = "signal: Rad->HH M1200";
  //1st set
  postfix.push_back("RadM1200_KtHW20tag07fake02_pt470600"); labels.push_back("#DeltaM_{H}=20, tag70%, fake 20%");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M1200_13TeV_PHYS14_25_V1/Rad_M1200_kT015_Hwin20_tag07_fake02/150703_004008/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola/Zpr_M1000_kT015_Hwin20_tag07_fake02/150703_215830/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-470to600_Tune4C_13TeV_pythia8/QCDpt470_kT015_Hwin20_tag07_fake02/150706_204511/0000/*.root");
  //2nd set
  postfix.push_back("RadM1200_KtHW30tag07fake02_pt470600"); labels.push_back("#DeltaM_{H}=30, tag 70% fake 20%");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M1200_13TeV_PHYS14_25_V1/Rad_M1200_kT015_Hwin30_tag07_fake02/150703_003908/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola/Zpr_M1000_kT015_Hwin30_tag07_fake02/150703_215645/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-470to600_Tune4C_13TeV_pythia8/QCDpt470_kT015_Hwin30_tag07_fake02/150706_204344/0000/*.root");

  makeHistos_3bkg_optimization(chains,postfix,labels,"470","600", info);
}

void makeHistos_3bkg_optimization_fake_470600(){
  vector<TString> chains; cout<< "Chaining files ..."<<endl;
  vector<string> postfix;
  vector<string> labels;
  TString info;

  info = "signal: Rad->HH M1200";
  //1st set
  postfix.push_back("RadM1200_KtHW30tag07fake001_pt470600"); labels.push_back("#DeltaM_{H}=30, tag70%, fake 1%");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M1200_13TeV_PHYS14_25_V1/Rad_M1200_kT015_Hwin30_tag07_fake001/150703_003759/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola/Zpr_M1000_kT015_Hwin30_tag07_fake001/150703_215615/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-470to600_Tune4C_13TeV_pythia8/QCDpt470_kT015_Hwin30_tag07_fake001/150706_204212/0000/*.root");
  //2nd set
  postfix.push_back("RadM1200_KtHW30tag07fake02_pt470600"); labels.push_back("#DeltaM_{H}=30, tag 70% fake 20%");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M1200_13TeV_PHYS14_25_V1/Rad_M1200_kT015_Hwin30_tag07_fake02/150703_003908/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola/Zpr_M1000_kT015_Hwin30_tag07_fake02/150703_215645/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-470to600_Tune4C_13TeV_pythia8/QCDpt470_kT015_Hwin30_tag07_fake02/150706_204344/0000/*.root");

  makeHistos_3bkg_optimization(chains,postfix,labels,"470","600", info);
}

void makeHistos_3bkg_optimization_MjCone10_470600(){
  vector<TString> chains; cout<< "Chaining files ..."<<endl;
  vector<string> postfix;
  vector<string> labels;
  TString info;

  info = "signal: Rad->HH M1200";
  //1st set
  postfix.push_back("RadM1200_KtR010HW30tag07fake02_pt470600"); labels.push_back("Kt R=0.10");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M1200_13TeV_PHYS14_25_V1/Rad_M1200_kT010_Hwin30_tag07_fake02/150703_004111/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola/Zpr_M1000_kT010_Hwin30_tag07_fake02/150703_215908/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-470to600_Tune4C_13TeV_pythia8/QCDpt470_kT010_Hwin30_tag07_fake02/150706_204703/0000/*.root");
  //2nd set
  postfix.push_back("RadM1200_KtR015HW30tag07fake02_pt470600"); labels.push_back("Kt R=0.15");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M1200_13TeV_PHYS14_25_V1/Rad_M1200_kT015_Hwin30_tag07_fake02/150703_003908/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola/Zpr_M1000_kT015_Hwin30_tag07_fake02/150703_215645/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-470to600_Tune4C_13TeV_pythia8/QCDpt470_kT015_Hwin30_tag07_fake02/150706_204344/0000/*.root"); 

  makeHistos_3bkg_optimization(chains,postfix,labels,"470","600", info);
}

void makeHistos_3bkg_optimization_MjCone20_470600(){
  vector<TString> chains; cout<< "Chaining files ..."<<endl;
  vector<string> postfix;
  vector<string> labels;
  TString info;

  info = "signal: Rad->HH M1200";
  //1st set
  postfix.push_back("RadM1200_KtR020HW30tag07fake02_pt470600"); labels.push_back("Kt R=0.20");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M1200_13TeV_PHYS14_25_V1/Rad_M1200_kT020_Hwin30_tag07_fake02/150703_004216/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola/Zpr_M1000_kT020_Hwin30_tag07_fake02/150703_215948/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-470to600_Tune4C_13TeV_pythia8/QCDpt470_kT020_Hwin30_tag07_fake02/150706_204846/0000/*.root");
  //2nd set
  postfix.push_back("RadM1200_KtR015HW30tag07fake02_pt470600"); labels.push_back("Kt R=0.15");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M1200_13TeV_PHYS14_25_V1/Rad_M1200_kT015_Hwin30_tag07_fake02/150703_003908/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola/Zpr_M1000_kT015_Hwin30_tag07_fake02/150703_215645/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-470to600_Tune4C_13TeV_pythia8/QCDpt470_kT015_Hwin30_tag07_fake02/150706_204344/0000/*.root"); 

  makeHistos_3bkg_optimization(chains,postfix,labels,"470","600", info);
}

void makeHistos_3bkg_optimization_tag_470600(){
  vector<TString> chains; cout<< "Chaining files ..."<<endl;
  vector<string> postfix;
  vector<string> labels;
  TString info;

  info = "signal: Rad->HH M1200";
  //1st set
  postfix.push_back("RadM1200_KtHW30tag06fake02_pt470600"); labels.push_back("#DeltaM_{H}=30, tag 60%, fake 20%");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M1200_13TeV_PHYS14_25_V1/Rad_M1200_kT015_Hwin30_tag06_fake02/150703_004312/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola/Zpr_M1000_kT015_Hwin30_tag06_fake02/150703_220034/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-470to600_Tune4C_13TeV_pythia8/QCDpt470_kT015_Hwin30_tag06_fake02/150706_205037/0000/*.root");
  //2nd set
  postfix.push_back("RadM1200_KtHW30tag07fake02_pt470600"); labels.push_back("#DeltaM_{H}=30, tag 70% fake 20%");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M1200_13TeV_PHYS14_25_V1/Rad_M1200_kT015_Hwin30_tag07_fake02/150703_003908/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola/Zpr_M1000_kT015_Hwin30_tag07_fake02/150703_215645/0000/*.root");
  chains.push_back("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-470to600_Tune4C_13TeV_pythia8/QCDpt470_kT015_Hwin30_tag07_fake02/150706_204344/0000/*.root"); 

  makeHistos_3bkg_optimization(chains,postfix,labels,"470","600", info);
}

void makeHistos_3bkg_compareSubstructure_300470(){

  TChain *fs  = new TChain("btaganaSubJets/ttree");
  TChain *fb1  = new TChain("btaganaSubJets/ttree");
  TChain *fb2  = new TChain("btaganaSubJets/ttree");

  string massCut; string ptCut;
  string postfix;
  vector<string> fsave;
  vector<string> labels;
  vector<TString> infos;

  string minMass = "95", maxMass = "155", minPt = "300", maxPt = "470";
  //string massType = "SoftDrop";
  string massType = "Groomed";
  massCut = "FatJetInfo.Jet_mass"+massType+">"+minMass+"&&FatJetInfo.Jet_mass"+massType+"<"+maxMass;
  ptCut = "FatJetInfo.Jet_pt>"+minPt+"&&FatJetInfo.Jet_pt<"+maxPt;
  infos.push_back(minMass+"<M_{"+massType+"}<"+maxMass+" GeV, "+minPt+"<p_{T}<"+maxPt+" GeV");
  infos.push_back("signal: Rad->HH M1200");

  ////QCD300470 Kt r=015 Hmasswin=30 tag70% fake20%
  fs->Add("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M1200_13TeV_PHYS14_25_V1/Rad_M1200_kT015_Hwin30_tag07_fake02/150703_003908/0000/*.root");
  fb1->Add("/eos/uscms/store/user/rsyarif/SDstudies/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola/Zpr_M1000_kT015_Hwin30_tag07_fake02/150703_215645/0000/*.root");
  fb2->Add("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-300to470_Tune4C_13TeV_pythia8/QCDpt300_kT015_Hwin30_tag07_fake02/150706_204303/0000/*.root");
  postfix = "RadM1200_KtHW30tag07fake02_3bkg_pt300470";labels.push_back("#DeltaM_{H}=30, tag 70% fake 20%");

  fsave.push_back("logchi_"+postfix);
  fsave.push_back("pt_"+postfix);
  fsave.push_back("mass_"+postfix);
  fsave.push_back("tau21_"+postfix);
  fsave.push_back("qvol_"+postfix);
  Plot_3bkg(fs,fb1,fb2,"log(FatJetInfo.Jet_SD_chi)",massCut+"&&"+ptCut+"&&FatJetInfo.Jet_SD_chi>0",fsave[0],"Log(#chi)",100,-26,-6);
  Plot_3bkg(fs,fb1,fb2,"FatJetInfo.Jet_pt",massCut+"&&"+ptCut,fsave[1],"p_{T}",50,150,700);
  Plot_3bkg(fs,fb1,fb2,"FatJetInfo.Jet_massGroomed",massCut+"&&"+ptCut,fsave[2],"M_{groomed}",100,50,200);
  Plot_3bkg(fs,fb1,fb2,"FatJetInfo.Jet_tau2/FatJetInfo.Jet_tau1",massCut+"&&"+ptCut,fsave[3],"#tau_{2} /#tau_{1}",100,0,1);
  Plot_3bkg(fs,fb1,fb2,"FatJetInfo.Jet_qvol",massCut+"&&"+ptCut,fsave[4],"qvol",100,0,0.5);
  ROC_3bkg(fsave[0],fsave[1],fsave[0],100,-26,-6,1);
  ROC_3bkg(fsave[3],fsave[1],fsave[3],100,0,1,0);
  ROC_3bkg(fsave[4],fsave[1],fsave[4],100,0,0.5,0);

  vector<string> labels_; labels_.push_back("log#chi");labels_.push_back("qvol");labels_.push_back("#tau_{2} /#tau_{1}");
  ROC_combined3_3bkg(("temp/TEMP_fhistos_ROC_logchi_"+postfix+".root").c_str(),("temp/TEMP_fhistos_ROC_qvol_"+postfix+".root").c_str(),("temp/TEMP_fhistos_ROC_tau21_"+postfix+".root").c_str(),("logchi_"+postfix+"_qvol_tau21").c_str(),labels_, infos);
}

void makeHistos_3bkg_compareSubstructure_470600(){

  TChain *fs  = new TChain("btaganaSubJets/ttree");
  TChain *fb1  = new TChain("btaganaSubJets/ttree");
  TChain *fb2  = new TChain("btaganaSubJets/ttree");

  string massCut; string ptCut;
  string postfix;
  vector<string> fsave;
  vector<string> labels;
  vector<TString> infos;

  string minMass = "95", maxMass = "155", minPt = "470", maxPt = "600";
  //string massType = "SoftDrop";
  string massType = "Groomed";
  massCut = "FatJetInfo.Jet_mass"+massType+">"+minMass+"&&FatJetInfo.Jet_mass"+massType+"<"+maxMass;
  ptCut = "FatJetInfo.Jet_pt>"+minPt+"&&FatJetInfo.Jet_pt<"+maxPt;
  infos.push_back(minMass+"<M_{"+massType+"}<"+maxMass+" GeV, "+minPt+"<p_{T}<"+maxPt+" GeV");
  infos.push_back("signal: Rad->HH M1200");

  ////QCD300470 Kt r=015 Hmasswin=30 tag70% fake20%
  fs->Add("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M1200_13TeV_PHYS14_25_V1/Rad_M1200_kT015_Hwin30_tag07_fake02/150703_003908/0000/*.root");
  fb1->Add("/eos/uscms/store/user/rsyarif/SDstudies/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola/Zpr_M1000_kT015_Hwin30_tag07_fake02/150703_215645/0000/*.root");
  fb2->Add("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-470to600_Tune4C_13TeV_pythia8/QCDpt470_kT015_Hwin30_tag07_fake02/150706_204344/0000/*.root");
  postfix = "RadM1200_KtHW30tag07fake02_3bkg_pt470600";labels.push_back("#DeltaM_{H}=30, tag 70% fake 20%");

  fsave.push_back("logchi_"+postfix);
  fsave.push_back("pt_"+postfix);
  fsave.push_back("mass_"+postfix);
  fsave.push_back("tau21_"+postfix);
  fsave.push_back("qvol_"+postfix);
  Plot_3bkg(fs,fb1,fb2,"log(FatJetInfo.Jet_SD_chi)",massCut+"&&"+ptCut+"&&FatJetInfo.Jet_SD_chi>0",fsave[0],"Log(#chi)",100,-26,-6);
  Plot_3bkg(fs,fb1,fb2,"FatJetInfo.Jet_pt",massCut+"&&"+ptCut,fsave[1],"p_{T}",50,150,700);
  Plot_3bkg(fs,fb1,fb2,"FatJetInfo.Jet_massGroomed",massCut+"&&"+ptCut,fsave[2],"M_{groomed}",100,50,200);
  Plot_3bkg(fs,fb1,fb2,"FatJetInfo.Jet_tau2/FatJetInfo.Jet_tau1",massCut+"&&"+ptCut,fsave[3],"#tau_{2} /#tau_{1}",100,0,1);
  Plot_3bkg(fs,fb1,fb2,"FatJetInfo.Jet_qvol",massCut+"&&"+ptCut,fsave[4],"qvol",100,0,0.5);
  ROC_3bkg(fsave[0],fsave[1],fsave[0],100,-26,-6,1);
  ROC_3bkg(fsave[3],fsave[1],fsave[3],100,0,1,0);
  ROC_3bkg(fsave[4],fsave[1],fsave[4],100,0,0.5,0);

  vector<string> labels_; labels_.push_back("log#chi");labels_.push_back("qvol");labels_.push_back("#tau_{2} /#tau_{1}");
  ROC_combined3_3bkg(("temp/TEMP_fhistos_ROC_logchi_"+postfix+".root").c_str(),("temp/TEMP_fhistos_ROC_qvol_"+postfix+".root").c_str(),("temp/TEMP_fhistos_ROC_tau21_"+postfix+".root").c_str(),("logchi_"+postfix+"_qvol_tau21").c_str(),labels_, infos);
}

void makeHistos_3bkg_compareSubstructure_opt_300470(){

  TChain *fs  = new TChain("btaganaSubJets/ttree");
  TChain *fb1  = new TChain("btaganaSubJets/ttree");
  TChain *fb2  = new TChain("btaganaSubJets/ttree");

  string massCut; string ptCut;
  string postfix;
  vector<string> fsave;
  vector<string> labels;
  vector<TString> infos;

  string minMass = "95", maxMass = "155", minPt = "300", maxPt = "470";
  //string massType = "SoftDrop";
  string massType = "Groomed";
  massCut = "FatJetInfo.Jet_mass"+massType+">"+minMass+"&&FatJetInfo.Jet_mass"+massType+"<"+maxMass;
  ptCut = "FatJetInfo.Jet_pt>"+minPt+"&&FatJetInfo.Jet_pt<"+maxPt;
  infos.push_back(minMass+"<M_{"+massType+"}<"+maxMass+" GeV, "+minPt+"<p_{T}<"+maxPt+" GeV");
  infos.push_back("signal: Rad->HH M1200");

  ////QCD300470 Kt r=020 Hmasswin=30 tag70% fake20%
  fs->Add("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M1200_13TeV_PHYS14_25_V1/Rad_M1200_kT020_Hwin30_tag07_fake02/150703_004216/0000/*.root");
  fb1->Add("/eos/uscms/store/user/rsyarif/SDstudies/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola/Zpr_M1000_kT020_Hwin30_tag07_fake02/150703_215948/0000/*.root");
  fb2->Add("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-300to470_Tune4C_13TeV_pythia8/QCDpt300_kT020_Hwin30_tag07_fake02/150706_204757/0000/*.root");
  postfix = "RadM1200_Kt020HW30tag07fake02_3bkg_pt300470";labels.push_back("#DeltaM_{H}=30 tag=70% fake=20% r=0.2");

  fsave.push_back("logchi_"+postfix);
  fsave.push_back("pt_"+postfix);
  fsave.push_back("mass_"+postfix);
  fsave.push_back("tau21_"+postfix);
  fsave.push_back("qvol_"+postfix);
  Plot_3bkg(fs,fb1,fb2,"log(FatJetInfo.Jet_SD_chi)",massCut+"&&"+ptCut+"&&FatJetInfo.Jet_SD_chi>0",fsave[0],"Log(#chi)",100,-26,-6);
  Plot_3bkg(fs,fb1,fb2,"FatJetInfo.Jet_pt",massCut+"&&"+ptCut,fsave[1],"p_{T}",50,150,700);
  Plot_3bkg(fs,fb1,fb2,"FatJetInfo.Jet_massGroomed",massCut+"&&"+ptCut,fsave[2],"M_{groomed}",100,50,200);
  Plot_3bkg(fs,fb1,fb2,"FatJetInfo.Jet_tau2/FatJetInfo.Jet_tau1",massCut+"&&"+ptCut,fsave[3],"#tau_{2} /#tau_{1}",100,0,1);
  Plot_3bkg(fs,fb1,fb2,"FatJetInfo.Jet_qvol",massCut+"&&"+ptCut,fsave[4],"qvol",100,0,0.5);
  ROC_3bkg(fsave[0],fsave[1],fsave[0],100,-26,-6,1);
  ROC_3bkg(fsave[3],fsave[1],fsave[3],100,0,1,0);
  ROC_3bkg(fsave[4],fsave[1],fsave[4],100,0,0.5,0);

  vector<string> labels_; labels_.push_back("log#chi");labels_.push_back("qvol");labels_.push_back("#tau_{2} /#tau_{1}");
  ROC_combined3_3bkg(("temp/TEMP_fhistos_ROC_logchi_"+postfix+".root").c_str(),("temp/TEMP_fhistos_ROC_qvol_"+postfix+".root").c_str(),("temp/TEMP_fhistos_ROC_tau21_"+postfix+".root").c_str(),("logchi_"+postfix+"_qvol_tau21").c_str(),labels_, infos);
}

void makeHistos_3bkg_compareSubstructure_opt_470600(){

  TChain *fs  = new TChain("btaganaSubJets/ttree");
  TChain *fb1  = new TChain("btaganaSubJets/ttree");
  TChain *fb2  = new TChain("btaganaSubJets/ttree");

  string massCut; string ptCut;
  string postfix;
  vector<string> fsave;
  vector<string> labels;
  vector<TString> infos;

  string minMass = "95", maxMass = "155", minPt = "470", maxPt = "600";
  //string massType = "SoftDrop";
  string massType = "Groomed";
  massCut = "FatJetInfo.Jet_mass"+massType+">"+minMass+"&&FatJetInfo.Jet_mass"+massType+"<"+maxMass;
  ptCut = "FatJetInfo.Jet_pt>"+minPt+"&&FatJetInfo.Jet_pt<"+maxPt;
  infos.push_back(minMass+"<M_{"+massType+"}<"+maxMass+" GeV, "+minPt+"<p_{T}<"+maxPt+" GeV");
  infos.push_back("signal: Rad->HH M1200");

  ////QCD300470 Kt r=020 Hmasswin=30 tag70% fake20%
  fs->Add("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M1200_13TeV_PHYS14_25_V1/Rad_M1200_kT020_Hwin30_tag07_fake02/150703_004216/0000/*.root");
  fb1->Add("/eos/uscms/store/user/rsyarif/SDstudies/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola/Zpr_M1000_kT020_Hwin30_tag07_fake02/150703_215948/0000/*.root");
  fb2->Add("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-470to600_Tune4C_13TeV_pythia8/QCDpt470_kT020_Hwin30_tag07_fake02/150706_204846/0000/*.root");
  postfix = "RadM1200_Kt020HW30tag07fake02_3bkg_pt470600";labels.push_back("#DeltaM_{H}=30 tag=70% fake=20% r=0.2");

  fsave.push_back("logchi_"+postfix);
  fsave.push_back("pt_"+postfix);
  fsave.push_back("mass_"+postfix);
  fsave.push_back("tau21_"+postfix);
  fsave.push_back("qvol_"+postfix);
  Plot_3bkg(fs,fb1,fb2,"log(FatJetInfo.Jet_SD_chi)",massCut+"&&"+ptCut+"&&FatJetInfo.Jet_SD_chi>0",fsave[0],"Log(#chi)",100,-26,-6);
  Plot_3bkg(fs,fb1,fb2,"FatJetInfo.Jet_pt",massCut+"&&"+ptCut,fsave[1],"p_{T}",50,150,700);
  Plot_3bkg(fs,fb1,fb2,"FatJetInfo.Jet_massGroomed",massCut+"&&"+ptCut,fsave[2],"M_{groomed}",100,50,200);
  Plot_3bkg(fs,fb1,fb2,"FatJetInfo.Jet_tau2/FatJetInfo.Jet_tau1",massCut+"&&"+ptCut,fsave[3],"#tau_{2} /#tau_{1}",100,0,1);
  Plot_3bkg(fs,fb1,fb2,"FatJetInfo.Jet_qvol",massCut+"&&"+ptCut,fsave[4],"qvol",100,0,0.5);
  ROC_3bkg(fsave[0],fsave[1],fsave[0],100,-26,-6,1);
  ROC_3bkg(fsave[3],fsave[1],fsave[3],100,0,1,0);
  ROC_3bkg(fsave[4],fsave[1],fsave[4],100,0,0.5,0);

  vector<string> labels_; labels_.push_back("log#chi");labels_.push_back("qvol");labels_.push_back("#tau_{2} /#tau_{1}");
  ROC_combined3_3bkg(("temp/TEMP_fhistos_ROC_logchi_"+postfix+".root").c_str(),("temp/TEMP_fhistos_ROC_qvol_"+postfix+".root").c_str(),("temp/TEMP_fhistos_ROC_tau21_"+postfix+".root").c_str(),("logchi_"+postfix+"_qvol_tau21").c_str(),labels_, infos);
}

void Alakazam(){
//    makeHistos_3bkg_optimization_Hwin_300470();
//   makeHistos_3bkg_optimization_fake_300470();
//   makeHistos_3bkg_optimization_MjCone10_300470();
//   makeHistos_3bkg_optimization_MjCone20_300470();
//   makeHistos_3bkg_optimization_tag_300470();
//   
//   makeHistos_3bkg_optimization_Hwin_470600();
//   makeHistos_3bkg_optimization_fake_470600();
//   makeHistos_3bkg_optimization_MjCone10_470600();
//   makeHistos_3bkg_optimization_MjCone20_470600();
//   makeHistos_3bkg_optimization_tag_470600();
//   
//   makeHistos_3bkg_compareSubstructure_300470();
//   makeHistos_3bkg_compareSubstructure_470600();
//   
//   makeHistos_3bkg_compareSubstructure_opt_300470();
  makeHistos_3bkg_compareSubstructure_opt_470600();

}
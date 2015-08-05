#include "Plot_LogChi_ROC_TChain.h"

void makeHistos_1bkg(){

  TChain *fs  = new TChain("btaganaSubJets/ttree");
  TChain *fb1  = new TChain("btaganaSubJets/ttree");

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
  postfix = "RadM1200_KtHW30tag07fake02_3bkg_pt300470";labels.push_back("#DeltaM_{H}=30, tag 70% fake 20%");

  fsave.push_back("logchi_"+postfix);
  fsave.push_back("pt_"+postfix);
  fsave.push_back("mass_"+postfix);
  Plot_3bkg(fs,fb1,fb2,"log(FatJetInfo.Jet_SD_chi)",massCut+"&&"+ptCut+"&&FatJetInfo.Jet_SD_chi>0",fsave[0],"Log(#chi)",100,-26,-6);
  Plot_3bkg(fs,fb1,fb2,"FatJetInfo.Jet_pt",massCut+"&&"+ptCut,fsave[1],"p_{T}",50,150,700);
  Plot_3bkg(fs,fb1,fb2,"FatJetInfo.Jet_massGroomed",massCut+"&&"+ptCut,fsave[2],"M_{groomed}",100,50,200);
  ROC_3bkg(fsave[0],fsave[1],fsave[0],100,-26,-6,1);

  vector<string> labels_; labels_.push_back("log#chi");labels_.push_back("qvol");labels_.push_back("#tau_{2} /#tau_{1}");
  ROC_combined3_1bkg(("temp/TEMP_fhistos_ROC_logchi_"+postfix+"_1bkg.root").c_str(),("temp/TEMP_fhistos_ROC_qvol_"+postfix+"_1bkg.root").c_str(),("temp/TEMP_fhistos_ROC_tau21_"+postfix+"_1bkg.root").c_str(),("logchi_"+postfix+"_qvol_tau21").c_str(),labels_, infos);
}

void Alakazam(){
  makeHistos_3bkg_optimization_Hwin_300470();
  makeHistos_3bkg_optimization_fake_300470();
  makeHistos_3bkg_optimization_MjCone10_300470();
  makeHistos_3bkg_optimization_MjCone20_300470();
  makeHistos_3bkg_optimization_tag_300470();
  
  makeHistos_3bkg_optimization_Hwin_470600();
  makeHistos_3bkg_optimization_fake_470600();
  makeHistos_3bkg_optimization_MjCone10_470600();
  makeHistos_3bkg_optimization_MjCone20_470600();
  makeHistos_3bkg_optimization_tag_470600();
  
  makeHistos_3bkg_compareSubstructure_300470();
  makeHistos_3bkg_compareSubstructure_470600();

}







{
  TFile * f = new TFile("../QCD_Pt-470to600_Tune4C_13TeV_pythia8_R08_r015_AkMj_HiggsWin30_tagr07_fake02_BtagALLMj_MjIVF015_mc_subjets.root");
  //TFile * f = new TFile("../ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola_R08_r015_AkMj_HiggsWin30_tagr07_fake02_BtagALLMj_MjIVF015_mc_subjets.root");
  //TFile * f = new TFile("rootfiles/FakeMjIVFbtagCalculation_RelValProdTTbar_13_AOD_R08_r015_HiggsWin20_tagr07_fake02_BtagALLMj_MjIVF015_mc_subjets.root");
  //TFile * f = new TFile("rootfiles/FakeMjIVFbtagCalculation_QCD_Pt-470to600_Tune4C_13TeV_pythia8_R08_r015_HiggsWin20_tagr07_fake02_BtagALLMj_MjIVF015_mc_subjets.root");
  TDirectory *d = f->GetDirectory("btaganaSubJets");
  TTree *t = (TTree*) d->Get("ttree");
  //TTree *t = (TTree*) f->Get("tree");

  TH1D *h = new TH1D("h","h",50,0,1000);
  TH1D *h2 = new TH1D("h2","h2",50,0,1000);
  TH1D *h3 = new TH1D("h3","h3",50,0,1000);

  TCanvas* c1 = new TCanvas();

  gStyle->SetOptStat("nemrou");

  h3->GetXaxis()->SetTitle("Microjet p_{T}");

  //t->Draw("FatJetInfo.Jet_SD_Microjet_pt>>h","FatJetInfo.Jet_SD_Microjet_isBtag!=1");
  //t->Draw("FatJetInfo.Jet_SD_Microjet_pt>>h2","FatJetInfo.Jet_SD_Microjet_isBtag==1");

  t->Draw("log(FatJetInfo.Jet_SD_chi)","FatJetInfo.Jet_SD_chi>0");

  //t->Draw("Mj_pt>>h","Mj_dR_gen>0");

  //c1->SaveAs("rootfiles/QCD_Pt-470to600_Mj_pt_Mj_dR_gen.eps");

  //t->Draw("Fj_pt>>h3","abs(Fj_flavour)!=5&&abs(Fj_flavour)!=4");

  //c1->SaveAs("rootfiles/QCD_Pt-470to600_Fj_pt_abs(Flavour)!=5&abs(Flavour)!=4.eps");

  // t->Draw("Mj_pt>>h","Mj_isBtag!=1");
  // t->Draw("Mj_pt>>h2","Mj_isBtag==1");
  // int Fj_flavour; float Fj_pt;int Fj_nMj; int Fj_nSV; float Mj_pt[10]; int Mj_isBtag[10]; float Mj_dR_SV[10];
  // t->SetBranchAddress("Fj_flavour",&Fj_flavour);
  // t->SetBranchAddress("Fj_pt",&Fj_pt);
  // t->SetBranchAddress("Fj_nMj",&Fj_nMj);
  // t->SetBranchAddress("Fj_nSV",&Fj_nSV);
  // t->SetBranchAddress("Mj_pt",&Mj_pt);
  // t->SetBranchAddress("Mj_isBtag",&Mj_isBtag);
  // t->SetBranchAddress("Mj_dR_SV",&Mj_dR_SV);
  // for(int i = 0; i<t->GetEntries();i++){
  //   t->GetEntry(i);
  //   if(abs(Fj_flavour)==5 || abs(Fj_flavour) ==4)continue;

  //   if(Fj_nSV>0)h3->Fill(Fj_pt);
  //   for(int j=0; j < Fj_nMj ;j++)
  //   {
  //     //if(Mj_dR_SV[j]>0)
  //     //h3->Fill(Mj_dR_SV[j]);
  //     //if(Mj_isBtag[j]==1)h3->Fill(Mj_pt[j]);
  //   }
  // }

  // h->Scale(1/h->GetEntries());
  // h2->Scale(1/h2->GetEntries());
  // h->SetLineColor(kBlue);
  // h2->SetLineColor(kRed);
  // h->Draw();
  // h2->Draw("sames");

  //h3->Draw();

  //c1->SaveAs("rootfiles/RelValProdTTbar_Fj_pt_Flavour!=5&Flavour!=4&Fj_nSV>0.eps");

}


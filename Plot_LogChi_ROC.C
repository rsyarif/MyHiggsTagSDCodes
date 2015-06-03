namespace using std;

Color_t c_h1 = kBlue;
Color_t c_h2 = kRed;
Color_t c_h3 = kGreen+2;
Color_t c_h4 = kYellow+2;

//3 bkg

void Plot_3bkg(TFile *fs, TFile *fb1, TFile*fb2, string var, string cut, string fsave, string xlabel, int bin, int min, int max){

  TDirectory *ds = fs->GetDirectory("btaganaSubJets");
  TDirectory *db1 = fb1->GetDirectory("btaganaSubJets");
  TDirectory *db2 = fb2->GetDirectory("btaganaSubJets");

  TTree *ts = (TTree*) ds->Get("ttree");
  TTree *tb1 = (TTree*) db1->Get("ttree");
  TTree *tb2 = (TTree*) db2->Get("ttree");


  const int xbin=bin; double xmin=min; double xmax=max;

  TCanvas *c1 =  new TCanvas("c1","c1",600,600);

  TH1D *h1 = new TH1D("h1","h1",xbin,xmin,xmax);
  TH1D *h2 = new TH1D("h2","h2",xbin,xmin,xmax);
  TH1D *h3 = new TH1D("h3","h3",xbin,xmin,xmax);
  TH1D *h4 = new TH1D("h4","h4",xbin,xmin,xmax);

  //string cutCommon = "FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_massGroomed>80&&FatJetInfo.Jet_massGroomed<150&&FatJetInfo.Jet_SD_nBtagMicrojets>1";
  //string cutCommon = "FatJetInfo.Jet_pt>300&&FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_massGroomed>80&&FatJetInfo.Jet_massGroomed<150";
  //string cutCommon = "FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_massGroomed>80&&FatJetInfo.Jet_massGroomed<150";

  string cutCommon = cut;

  string cutSig = ""+cutCommon;
  string cutTT = ""+cutCommon;
  string cutQCDb = "abs(int(FatJetInfo.Jet_flavour))==5&&FatJetInfo.Jet_nbHadrons<2&&"+cutCommon;
  string cutQCDgsp = "abs(FatJetInfo.Jet_flavour)==5&&FatJetInfo.Jet_nbHadrons>1&&"+cutCommon;

  //string var = "log(FatJetInfo.Jet_SD_chi)";

  ts->Draw((var+">>h1").c_str(),cutSig.c_str());
  tb1->Draw((var+">>h2").c_str(),cutTT.c_str());
  tb2->Draw((var+">>h3").c_str(),cutQCDb.c_str());
  tb2->Draw((var+">>h4").c_str(),cutQCDgsp.c_str());

  //string xlabel = "Log(#chi)";

  h1->SetTitle("");
  h1->GetXaxis()->SetTitle(xlabel.c_str());
  h1->SetLineColor(c_h1);
  h1->SetLineWidth(3);
  h2->SetTitle("");
  h2->GetXaxis()->SetTitle(xlabel.c_str());
  h2->SetLineColor(c_h2);
  h2->SetLineWidth(2);
  h3->SetTitle("");
  h3->GetXaxis()->SetTitle(xlabel.c_str());
  h3->SetLineColor(c_h3);
  h3->SetLineWidth(2);
  h4->SetTitle("");
  h4->GetXaxis()->SetTitle(xlabel.c_str());
  h4->SetLineColor(c_h4);
  h4->SetLineWidth(2);

  TFile *fTEMP = new TFile(("TEMP_fhistos_"+fsave+".root").c_str(),"RECREATE");
  h1->Write();
  h2->Write();
  h3->Write();
  h4->Write();

  h1->Scale(1/h1->GetEntries());
  h2->Scale(1/h2->GetEntries());
  h3->Scale(1/h3->GetEntries());
  h4->Scale(1/h4->GetEntries());

  THStack *h = new THStack("h","");
  h->Add(h1,"sames");
  h->Add(h2,"sames");
  h->Add(h3,"sames");
  h->Add(h4,"sames");
  h->Draw("nostack");
  h->GetXaxis()->SetTitle(xlabel.c_str());

  TLegend *leg = new TLegend(0.2,0.65,0.4,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h1,"RadHH800","L");
  leg->AddEntry(h2,"Z'ttbar","L");
  leg->AddEntry(h3,"QCDb","L");
  leg->AddEntry(h4,"QCDgsp","L");
  leg->Draw("SAME");

  gPad->Update();

  TPaveStats *tps1 = (TPaveStats*) h1->FindObject("stats");
  tps1->SetTextColor(c_h1);
  double X1 = tps1->GetX1NDC();
  double Y1 = tps1->GetY1NDC();
  double X2 = tps1->GetX2NDC();
  double Y2 = tps1->GetY2NDC();
  TPaveStats *tps2 = (TPaveStats*) h2->FindObject("stats");
  tps2->SetTextColor(c_h2);
  tps2->SetX1NDC(X1);
  tps2->SetX2NDC(X2);
  tps2->SetY1NDC(Y1-(Y2-Y1));
  tps2->SetY2NDC(Y1);
  X1 = tps2->GetX1NDC();
  Y1 = tps2->GetY1NDC();
  X2 = tps2->GetX2NDC();
  Y2 = tps2->GetY2NDC();
  TPaveStats *tps3 = (TPaveStats*) h3->FindObject("stats");
  tps3->SetTextColor(c_h3);
  tps3->SetX1NDC(X1);
  tps3->SetX2NDC(X2);
  tps3->SetY1NDC(Y1-(Y2-Y1));
  tps3->SetY2NDC(Y1);
  X1 = tps3->GetX1NDC();
  Y1 = tps3->GetY1NDC();
  X2 = tps3->GetX2NDC();
  Y2 = tps3->GetY2NDC();
  TPaveStats *tps4 = (TPaveStats*) h4->FindObject("stats");
  tps4->SetTextColor(c_h4);
  tps4->SetX1NDC(X1);
  tps4->SetX2NDC(X2);
  tps4->SetY1NDC(Y1-(Y2-Y1));
  tps4->SetY2NDC(Y1);

  gPad->Update();

  c1->SaveAs(("plots/"+fsave+".eps").c_str());

  fTEMP->Close();
}

void ROC_3bkg(string fname,string fdenom,string fsave, const int xbin, double xmin, double xmax){

  TFile *f = new TFile(("TEMP_fhistos_"+fname+".root").c_str());
  TFile *fd = new TFile(("TEMP_fhistos_"+fdenom+".root").c_str());

  TH1D* h1 = (TH1D*)f->Get("h1");
  TH1D* h2 = (TH1D*)f->Get("h2");
  TH1D* h3 = (TH1D*)f->Get("h3");
  TH1D* h4 = (TH1D*)f->Get("h4");

  TH1D* d1 = (TH1D*)fd->Get("h1");
  TH1D* d2 = (TH1D*)fd->Get("h2");
  TH1D* d3 = (TH1D*)fd->Get("h3");
  TH1D* d4 = (TH1D*)fd->Get("h4");

  //double denom1 = h1->Integral(0,xbin+1);
  //double denom2 = h2->Integral(0,xbin+1);
  //double denom3 = h3->Integral(0,xbin+1);
  //double denom4 = h4->Integral(0,xbin+1);

  double denom1 = d1->GetEntries();
  double denom2 = d2->GetEntries();
  double denom3 = d3->GetEntries();
  double denom4 = d4->GetEntries();

  //const int xbin = h1->GetSize()-2;

  double num1[xbin];
  double num2[xbin];
  double num3[xbin];
  double num4[xbin];
  double eff1[xbin];
  double eff2[xbin];
  double eff3[xbin];
  double eff4[xbin];

  double x[xbin];
  double inc = (xmax-xmin)/xbin;

  for(int i=0; i<xbin;i++){
    num1[i]=h1->Integral(i+1,xbin+1);
    num2[i]=h2->Integral(i+1,xbin+1);
    num3[i]=h3->Integral(i+1,xbin+1);
    num4[i]=h4->Integral(i+1,xbin+1);
    eff1[i]=num1[i]/denom1;
    eff2[i]=num2[i]/denom2;
    eff3[i]=num3[i]/denom3;
    eff4[i]=num4[i]/denom4;
    x[i] = xmin + inc*i;
    cout<<i+1<<". x = "<<x[i]<< ", h1 =  "<< num1[i]/denom1<< ", h3 = "<< num3[i]/denom3 << endl;
  }

  double rej2[xbin];for(int i =0;i<xbin;i++)rej2[i]=1-eff2[i];
  double rej3[xbin];for(int i =0;i<xbin;i++)rej3[i]=1-eff3[i];
  double rej4[xbin];for(int i =0;i<xbin;i++)rej4[i]=1-eff4[i];

  TGraph *gr2 = new TGraph(xbin,eff1,rej2);
  gr2->SetName("gr2");
  gr2->SetTitle("Z'ttbar");
  gr2->SetLineColor(c_h2);
  gr2->SetLineWidth(2);
  gr2->GetXaxis()->SetTitle("Eff_{sig}");
  gr2->GetYaxis()->SetTitle("1-Eff_{bkg}");
  gr2->GetXaxis()->SetRangeUser(0,1);
  gr2->GetYaxis()->SetRangeUser(0,1);
  gr2->SetFillStyle(0);

  TGraph *gr3 = new TGraph(xbin,eff1,rej3);
  gr3->SetName("gr3");
  gr3->SetTitle("QCDb");
  gr3->SetLineColor(c_h3);
  gr3->SetLineWidth(2);
  gr3->GetXaxis()->SetTitle("Eff_{sig}");
  gr3->GetYaxis()->SetTitle("1-Eff_{bkg}");
  gr3->GetXaxis()->SetRangeUser(0,1);
  gr3->GetYaxis()->SetRangeUser(0,1);
  gr3->SetFillStyle(0);

  TGraph *gr4 = new TGraph(xbin,eff1,rej4);
  gr4->SetName("gr4");
  gr4->SetTitle("QCDgsp");
  gr4->SetLineColor(c_h4);
  gr4->SetLineWidth(2);
  gr4->GetXaxis()->SetTitle("Eff_{sig}");
  gr4->GetYaxis()->SetTitle("1-Eff_{bkg}");
  gr4->GetXaxis()->SetRangeUser(0,1);
  gr4->GetYaxis()->SetRangeUser(0,1);
  gr4->SetFillStyle(0);

  TFile *fTEMP = new TFile(("TEMP_fhistos_ROC_"+fsave+".root").c_str(),"RECREATE");
  gr2->Write();
  gr3->Write();
  gr4->Write();

  TCanvas *c = new TCanvas("c","c",600,600);

  TMultiGraph *ROC = new TMultiGraph("ROC","ROC");
  ROC->Add(gr2);
  ROC->Add(gr3);
  ROC->Add(gr4);

  ROC->Draw("APL");
  ROC->GetXaxis()->SetTitle("Eff_{sig}");
  ROC->GetYaxis()->SetTitle("1-Eff_{bkg}");
  ROC->GetXaxis()->SetLimits(0.,1.);
  //ROC->GetYaxis()->SetLimits(0.,1.);
  ROC->SetMaximum(1.);ROC->SetMinimum(0.);
  ROC->SetTitle("ROC Curves");

  c->BuildLegend(0.2,0.2,0.2+0.2,0.2+0.15);

  gPad->Update();

  c->SaveAs(("plots/ROC_"+fsave+".eps").c_str());

  fTEMP->Close();
}

void ROC_combined_3bkg(string fname1, string fname2, string fsave,vector<string> labels) {

  TFile *f1 = new TFile(fname1.c_str());
  TFile *f2 = new TFile(fname2.c_str());

  TGraph* gr2 = (TGraph*)f1->Get("gr2");
  gr2->SetLineStyle(2);
  gr2->SetTitle(labels[0].c_str());
  TGraph* gr3 = (TGraph*)f1->Get("gr3");
  gr3->SetLineStyle(2);
  gr3->SetTitle(labels[0].c_str());
  TGraph* gr4 = (TGraph*)f1->Get("gr4");
  gr4->SetLineStyle(2);
  gr4->SetTitle(labels[0].c_str());

  TGraph* gr2_ = (TGraph*)f2->Get("gr2");
  gr2_->SetTitle(labels[1].c_str());
  TGraph* gr3_ = (TGraph*)f2->Get("gr3");
  gr3_->SetTitle(labels[1].c_str());
  TGraph* gr4_ = (TGraph*)f2->Get("gr4");
  gr4_->SetTitle(labels[1].c_str());

  TCanvas *c = new TCanvas("c","c",600,600);

  TMultiGraph *ROC = new TMultiGraph("ROC","ROC");
  ROC->Add(gr2);
  ROC->Add(gr3);
  ROC->Add(gr4);
  ROC->Add(gr2_);
  ROC->Add(gr3_);
  ROC->Add(gr4_);

  ROC->Draw("APL");
  ROC->GetXaxis()->SetTitle("Eff_{sig}");
  ROC->GetYaxis()->SetTitle("1-Eff_{bkg}");
  ROC->GetXaxis()->SetLimits(0.,1.);
  //ROC->GetYaxis()->SetLimits(0.,1.);
  ROC->SetMaximum(1.);ROC->SetMinimum(0.);
  ROC->SetTitle("ROC Curves");

  c->BuildLegend(0.2,0.2,0.2+0.3,0.2+0.25);

  gPad->Update();

  c->SaveAs(("plots/ROC_Combined_"+fsave+".eps").c_str());
}

void makeHistos_3bkg(){

  string fsave1; string fsave2;
  string postfix1; string postfix2;
  vector<string> labels;

  // TFile *fs = new TFile("rootfiles/Rad_HHto4b_M800_13TeV_AOD_R08_r015_HiggsWin20_mc_subjets.root");
  // TFile *fb1 = new TFile("rootfiles/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola_R08_r015_HiggsWin20_mc_subjets.root");
  // TFile *fb2 = new TFile("rootfiles/QCD_Pt-470to600_Tune4C_13TeV_pythia8_R08_r015_HiggsWin20_FULL_mc_subjets.root");
  // postfix1="KtHW20fake001_3bkg";labels.push_back("#DeltaM_{H}=20, fake 1%");

  // TFile *fs = new TFile("rootfiles/Rad_HHto4b_M800_13TeV_AOD_R08_r015_KtMj_HiggsWin30_tagr06_fake02_BtagALLMj_MjIVF015_mc_subjets.root");
  // TFile *fb1 = new TFile("rootfiles/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola_R08_r015_KtMj_HiggsWin30_tagr06_fake02_BtagALLMj_MjIVF015_mc_subjets.root");
  // TFile *fb2 = new TFile("rootfiles/QCD_Pt-470to600_Tune4C_13TeV_pythia8_R08_r015_KtMj_HiggsWin30_tagr06_fake02_BtagALLMj_MjIVF015_MORE_mc_subjets.root");
  // postfix1 = "KtHW30tag06fake02_3bkg";labels.push_back("#DeltaM_{H}=30, tag 60% fake 20%");
  fsave1 = "logchi_"+postfix1;
  fsave2 = "pt_"+postfix1;
  Plot_3bkg(fs,fb1,fb2,"log(FatJetInfo.Jet_SD_chi)","FatJetInfo.Jet_pt>300&&FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_massGroomed>80&&FatJetInfo.Jet_massGroomed<150",fsave1,"Log(#chi)",40,-26,-6);
  Plot_3bkg(fs,fb1,fb2,"FatJetInfo.Jet_pt","FatJetInfo.Jet_pt>300&&FatJetInfo.Jet_massGroomed>80&&FatJetInfo.Jet_massGroomed<150",fsave2,"p_{T}",50,0,800);
  ROC_3bkg(fsave1,fsave2,postfix1,40,-26,-6);

  //TFile *fs_ = new TFile("rootfiles/Rad_HHto4b_M800_13TeV_AOD_R08_r015_AkMj_HiggsWin30_tagr07_fake02_BtagALLMj_MjIVF015_mc_subjets.root");
  //TFile *fb1_ = new TFile("rootfiles/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola_R08_r015_AkMj_HiggsWin30_tagr07_fake02_BtagALLMj_MjIVF015_mc_subjets.root");
  //TFile *fb2_ = new TFile("rootfiles/QCD_Pt-470to600_Tune4C_13TeV_pythia8_R08_r015_AkMj_HiggsWin30_tagr07_fake02_BtagALLMj_MjIVF015_mc_subjets.root");
  //postfix2 = "AkHW30fake02_3bkg";labels.push_back("#DeltaM_{H}=30, fake 20% AK");
  TFile *fs_ = new TFile("rootfiles/Rad_HHto4b_M800_13TeV_AOD_R08_r015_KtMj_HiggsWin30_tagr07_fake02_BtagALLMj_MjIVF015_mc_subjets.root");
  TFile *fb1_ = new TFile("rootfiles/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola_R08_r015_KtMj_HiggsWin30_tagr07_fake02_BtagALLMj_MjIVF015_mc_subjets.root");
  TFile *fb2_ = new TFile("rootfiles/QCD_Pt-470to600_Tune4C_13TeV_pythia8_R08_r015_KtMj_HiggsWin30_tagr07_fake02_BtagALLMj_MjIVF015_MORE_mc_subjets.root");
  postfix2 = "KtHW30tag07fake02_3bkg";labels.push_back("#DeltaM_{H}=30, tag 70% fake 20%");
  fsave1 = "logchi_"+postfix2;
  fsave2 = "pt_"+postfix2;
  Plot_3bkg(fs_,fb1_,fb2_,"log(FatJetInfo.Jet_SD_chi)","FatJetInfo.Jet_pt>300&&FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_massGroomed>80&&FatJetInfo.Jet_massGroomed<150",fsave1,"Log(#chi)",40,-26,-6);
  Plot_3bkg(fs_,fb1_,fb2_,"FatJetInfo.Jet_pt","FatJetInfo.Jet_pt>300&&FatJetInfo.Jet_massGroomed>80&&FatJetInfo.Jet_massGroomed<150",fsave2,"p_{T}",50,0,800);
  ROC_3bkg(fsave1,fsave2,postfix2,40,-26,-6);

  ROC_combined_3bkg(("TEMP_fhistos_ROC_"+postfix1+".root").c_str(),("TEMP_fhistos_ROC_"+postfix2+".root").c_str(),(postfix1+"_"+postfix2).c_str(),labels);

}

//1 bkg

void Plot_1bkg(TFile *fs, TFile *fb1,  string var, string cut, string fsave, string xlabel, int bin, int min, int max){

  TDirectory *ds = fs->GetDirectory("btaganaSubJets");
  TDirectory *db1 = fb1->GetDirectory("btaganaSubJets");

  TTree *ts = (TTree*) ds->Get("ttree");
  TTree *tb1 = (TTree*) db1->Get("ttree");

  const int xbin=bin; double xmin=min; double xmax=max;

  TCanvas *c1 =  new TCanvas("c1","c1",600,600);

  TH1D *h1 = new TH1D("h1","h1",xbin,xmin,xmax);
  TH1D *h2 = new TH1D("h2","h2",xbin,xmin,xmax);

  string cutCommon = cut;
  string cutSig = ""+cutCommon;
  string cutTT = ""+cutCommon;
  //string cutQCDb = "abs(int(FatJetInfo.Jet_flavour))==5&&FatJetInfo.Jet_nbHadrons<2&&"+cutCommon;
  //string cutQCDgsp = "abs(FatJetInfo.Jet_flavour)==5&&FatJetInfo.Jet_nbHadrons>1&&"+cutCommon;

  ts->Draw((var+">>h1").c_str(),cutSig.c_str());
  tb1->Draw((var+">>h2").c_str(),cutTT.c_str());

  h1->SetTitle("");
  h1->GetXaxis()->SetTitle(xlabel.c_str());
  h1->SetLineColor(c_h1);
  h1->SetLineWidth(3);
  h2->SetTitle("");
  h2->GetXaxis()->SetTitle(xlabel.c_str());
  h2->SetLineColor(c_h2);
  h2->SetLineWidth(2);

  TFile *fTEMP = new TFile(("TEMP_fhistos_"+fsave+".root").c_str(),"RECREATE");
  h1->Write();
  h2->Write();

  h1->Scale(1/h1->GetEntries());
  h2->Scale(1/h2->GetEntries());

  THStack *h = new THStack("h","");
  h->Add(h1,"sames");
  h->Add(h2,"sames");
  h->Draw("nostack");
  h->GetXaxis()->SetTitle(xlabel.c_str());

  TLegend *leg = new TLegend(0.2,0.65,0.4,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h1,"RadHH800","L");
  leg->AddEntry(h2,"Z'ttbar","L");
  leg->Draw("SAME");

  gPad->Update();

  TPaveStats *tps1 = (TPaveStats*) h1->FindObject("stats");
  tps1->SetTextColor(c_h1);
  double X1 = tps1->GetX1NDC();
  double Y1 = tps1->GetY1NDC();
  double X2 = tps1->GetX2NDC();
  double Y2 = tps1->GetY2NDC();
  TPaveStats *tps2 = (TPaveStats*) h2->FindObject("stats");
  tps2->SetTextColor(c_h2);
  tps2->SetX1NDC(X1);
  tps2->SetX2NDC(X2);
  tps2->SetY1NDC(Y1-(Y2-Y1));
  tps2->SetY2NDC(Y1);
  X1 = tps2->GetX1NDC();
  Y1 = tps2->GetY1NDC();
  X2 = tps2->GetX2NDC();
  Y2 = tps2->GetY2NDC();

  gPad->Update();

  c1->SaveAs(("rootfiles/TEMP_"+fsave+".eps").c_str());

  fTEMP->Close();
}

void ROC_1bkg(string fname,string fdenom,string fsave, const int xbin, double xmin, double xmax){

  TFile *f = new TFile(("TEMP_fhistos_"+fname+".root").c_str());
  TFile *fd = new TFile(("TEMP_fhistos_"+fdenom+".root").c_str());

  TH1D* h1 = (TH1D*)f->Get("h1");
  TH1D* h2 = (TH1D*)f->Get("h2");

  TH1D* d1 = (TH1D*)fd->Get("h1");
  TH1D* d2 = (TH1D*)fd->Get("h2");

  double denom1 = d1->GetEntries();
  double denom2 = d2->GetEntries();

  double num1[xbin];
  double num2[xbin];
  double eff1[xbin];
  double eff2[xbin];

  double x[xbin];
  double inc = (xmax-xmin)/xbin;

  for(int i=0; i<xbin;i++){
    num1[i]=h1->Integral(i+1,xbin+1);
    num2[i]=h2->Integral(i+1,xbin+1);
    eff1[i]=num1[i]/denom1;
    eff2[i]=num2[i]/denom2;
    x[i] = xmin + inc*i;
    cout<<i+1<<". x = "<<x[i]<< ", h1 =  "<< num1[i]/denom1<< ", h2 = "<< num2[i]/denom2 << endl;
  }

  double rej2[xbin];for(int i =0;i<xbin;i++)rej2[i]=1-eff2[i];

  TGraph *gr2 = new TGraph(xbin,eff1,rej2);
  gr2->SetName("gr2");
  gr2->SetTitle("Z'ttbar");
  gr2->SetLineColor(c_h2);
  gr2->SetLineWidth(2);
  gr2->GetXaxis()->SetTitle("Eff_{sig}");
  gr2->GetYaxis()->SetTitle("1-Eff_{bkg}");
  gr2->GetXaxis()->SetRangeUser(0,1);
  gr2->GetYaxis()->SetRangeUser(0,1);
  gr2->SetFillStyle(0);

  TFile *fTEMP = new TFile(("TEMP_fhistos_ROC_"+fsave+".root").c_str(),"RECREATE");
  gr2->Write();

  TCanvas *c = new TCanvas("c","c",600,600);

  TMultiGraph *ROC = new TMultiGraph("ROC","ROC");
  ROC->Add(gr2);

  ROC->Draw("APL");
  ROC->GetXaxis()->SetTitle("Eff_{sig}");
  ROC->GetYaxis()->SetTitle("1-Eff_{bkg}");
  ROC->GetXaxis()->SetLimits(0.,1.);
  //ROC->GetYaxis()->SetLimits(0.,1.);
  ROC->SetMaximum(1.);ROC->SetMinimum(0.);
  ROC->SetTitle("ROC Curves");

  c->BuildLegend(0.2,0.2,0.2+0.2,0.2+0.15);

  gPad->Update();

  c->SaveAs(("rootfiles/TEMP_ROC_"+fsave+".eps").c_str());

  fTEMP->Close();
}

void ROC_combined_1bkg(string fname1, string fname2,string fsave, string label1, string label2){

  TFile *f1 = new TFile(fname1.c_str());
  TFile *f2 = new TFile(fname2.c_str());

  TGraph* gr2 = (TGraph*)f1->Get("gr2");
  gr2->SetLineStyle(2);
  gr2->SetTitle(label1.c_str());
  TGraph* gr2_ = (TGraph*)f2->Get("gr2");
  gr2_->SetTitle(label2.c_str());
  TCanvas *c = new TCanvas("c","c",600,600);

  TMultiGraph *ROC = new TMultiGraph("ROC","ROC");
  ROC->Add(gr2);
  ROC->Add(gr2_);

  ROC->Draw("APL");
  ROC->GetXaxis()->SetTitle("Eff_{sig}");
  ROC->GetYaxis()->SetTitle("1-Eff_{bkg}");
  ROC->GetXaxis()->SetLimits(0.,1.);
  //ROC->GetYaxis()->SetLimits(0.,1.);
  ROC->SetMaximum(1.);ROC->SetMinimum(0.);
  ROC->SetTitle("ROC Curves");

  c->BuildLegend(0.2,0.2,0.2+0.3,0.2+0.25);

  gPad->Update();

  c->SaveAs(("rootfiles/TEMP_ROC_Combined_"+fsave+".eps").c_str());
}

void makeHistos_1bkg(){

  string fsave1; string fsave2;
  string postfix1; string postfix2;
  string label1; string label2;

  //TFile *fs = new TFile("rootfiles/Rad_HHto4b_M800_13TeV_AOD_R08_r015_HiggsWin20_mc_subjets.root");
  //TFile *fb1 = new TFile("rootfiles/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola_R08_r015_HiggsWin20_mc_subjets.root");
  //postfix1="KtHW20fake001_1bkg";label1="#DeltaM_{H}=20, fake 1%";
  //TFile *fs = new TFile("rootfiles/Rad_HHto4b_M800_13TeV_AOD_R08_r015_HiggsWin30_mc_subjets.root");
  //TFile *fb1 = new TFile("rootfiles/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola_R08_r015_HiggsWin30_mc_subjets.root");
  //postfix1="KtHW30fake001_1bkg";label1="#DeltaM_{H}=30, fake 1%";
  //TFile *fs = new TFile("rootfiles/Rad_HHto4b_M800_13TeV_AOD_R08_r015_AkMj_HiggsWin30_tagr07_fake02_BtagALLMj_MjIVF015_mc_subjets.root");
  //TFile *fb1 = new TFile("rootfiles/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola_R08_r015_AkMj_HiggsWin30_tagr07_fake02_BtagALLMj_MjIVF015_mc_subjets.root");
  //postfix1 = "AkHW30fake02_1bkg";label1="#DeltaM_{H}=30, fake 20% Ak";
  //TFile *fs = new TFile("rootfiles/Rad_HHto4b_M800_13TeV_AOD_R08_r015_CAMj_HiggsWin30_tagr07_fake02_BtagALLMj_MjIVF015_mc_subjets.root");
  //TFile *fb1 = new TFile("rootfiles/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola_R08_r015_CAMj_HiggsWin30_tagr07_fake02_BtagALLMj_MjIVF015_mc_subjets.root");
  //postfix1 = "CAHW30fake02_1bkg";label1="#DeltaM_{H}=30, fake 20% CA";
  TFile *fs = new TFile("rootfiles/Rad_HHto4b_M800_13TeV_AOD_R08_r015_KtMj_HiggsWin30_tagr06_fake02_BtagALLMj_MjIVF015_mc_subjets.root");
  TFile *fb1 = new TFile("rootfiles/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola_R08_r015_KtMj_HiggsWin30_tagr06_fake02_BtagALLMj_MjIVF015_mc_subjets.root");
  postfix1 = "KtHW30tag06fake02_1bkg";label1="#DeltaM_{H}=30, tag 60% fake 20%";
  fsave1 = "logchi_"+postfix1;
  fsave2 = "pt_"+postfix1;
  Plot_1bkg(fs,fb1,"log(FatJetInfo.Jet_SD_chi)","FatJetInfo.Jet_pt>300&&FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_massGroomed>80&&FatJetInfo.Jet_massGroomed<150",fsave1,"Log(#chi)",40,-26,-6);
  Plot_1bkg(fs,fb1,"FatJetInfo.Jet_pt","FatJetInfo.Jet_pt>300&&FatJetInfo.Jet_massGroomed>80&&FatJetInfo.Jet_massGroomed<150",fsave2,"p_{T}",50,0,800);
  ROC_1bkg(fsave1,fsave2,postfix1,40,-26,-6);


  //TFile *fs_ = new TFile("rootfiles/Rad_HHto4b_M800_13TeV_AOD_R08_r015_HiggsWin30_mc_subjets.root");
  //TFile *fb1_ = new TFile("rootfiles/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola_R08_r015_HiggsWin30_mc_subjets.root");
  //postfix2="KtHW30fake001_1bkg"; label2="#DeltaM_{H}=30, fake 1%"
  TFile *fs_ = new TFile("rootfiles/Rad_HHto4b_M800_13TeV_AOD_R08_r015_KtMj_HiggsWin30_tagr07_fake02_BtagALLMj_MjIVF015_mc_subjets.root");
  TFile *fb1_ = new TFile("rootfiles/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola_R08_r015_KtMj_HiggsWin30_tagr07_fake02_BtagALLMj_MjIVF015_mc_subjets.root");
  postfix2 = "KtHW30tag07fake02_1bkg";label2="#DeltaM_{H}=30, tag 70% fake 20%";
  fsave1 = "logchi_"+postfix2;
  fsave2 = "pt_"+postfix2;
  Plot_1bkg(fs_,fb1_,"log(FatJetInfo.Jet_SD_chi)","FatJetInfo.Jet_pt>300&&FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_massGroomed>80&&FatJetInfo.Jet_massGroomed<150",fsave1,"Log(#chi)",40,-26,-6);
  Plot_1bkg(fs_,fb1_,"FatJetInfo.Jet_pt","FatJetInfo.Jet_pt>300&&FatJetInfo.Jet_massGroomed>80&&FatJetInfo.Jet_massGroomed<150",fsave2,"p_{T}",50,0,800);
  ROC_1bkg(fsave1,fsave2,postfix2,40,-26,-6);

  ROC_combined_1bkg(("TEMP_fhistos_ROC_"+postfix1+".root").c_str(),("TEMP_fhistos_ROC_"+postfix2+".root").c_str(),(postfix1+"_"+postfix2).c_str(),label1,label2);

}

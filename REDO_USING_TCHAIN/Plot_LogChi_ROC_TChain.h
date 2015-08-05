using namespace std;

Color_t c_h1 = kBlue;
Color_t c_h2 = kRed;
Color_t c_h3 = kGreen+2;
Color_t c_h4 = kYellow+2;


//1 bkg

void Plot_1bkg(TChain *ts, TChain *tb1, string var, string cut, string fsave, string xlabel, int bin, float min, float max){

  const int xbin=bin; double xmin=min; double xmax=max;

  TCanvas *c1 =  new TCanvas("c1","c1",600,600);

  TH1D *h1 = new TH1D("h1","h1",xbin,xmin,xmax);
  TH1D *h2 = new TH1D("h2","h2",xbin,xmin,xmax);

  string cutCommon = cut;

  string cutSig = ""+cutCommon;
  string cutTT = ""+cutCommon;

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

  TFile *fTEMP = new TFile(("temp/TEMP_fhistos_"+fsave+"_1bkg.root").c_str(),"RECREATE");
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
  leg->AddEntry(h1,"RadHH","L");
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

  c1->SaveAs(("plots/"+fsave+"_1bkg.pdf").c_str());

  fTEMP->Close();
}

void ROC_1bkg(string fname,string fdenom,string fsave, const int xbin, double xmin, double xmax, bool direction = 1){

  TFile *f = new TFile(("temp/TEMP_fhistos_"+fname+"_1bkg.root").c_str());
  TFile *fd = new TFile(("temp/TEMP_fhistos_"+fdenom+"_1bkg.root").c_str());

  TH1D* h1 = (TH1D*)f->Get("h1");
  TH1D* h2 = (TH1D*)f->Get("h2");

  TH1D* d1 = (TH1D*)fd->Get("h1");
  TH1D* d2 = (TH1D*)fd->Get("h2");

  //selfDenom
  //double denom1 = h1->Integral(0,xbin+1); cout<<"denom1 = "<<denom1 << endl;
  //double denom2 = h2->Integral(0,xbin+1); cout<<"denom2 = "<<denom2 << endl;
 
  //commonDenom
  double denom1 = d1->GetEntries(); //cout<<"denom1 = "<<denom1 << endl;
  double denom2 = d2->GetEntries(); //cout<<"denom2 = "<<denom2 << endl;

  //const int xbin = h1->GetSize()-2;

  double num1[xbin];
  double num2[xbin];
  double eff1[xbin];
  double eff2[xbin];

  double x[xbin];
  double inc = (xmax-xmin)/xbin;

  for(int i=0; i<xbin;i++){
    num1[i]=h1->Integral(i+1,xbin+1);
    num2[i]=h2->Integral(i+1,xbin+1);
    eff1[i]=(direction==1? num1[i]/denom1 : 1. -  (num1[i]/denom1));
    eff2[i]=(direction==1? num2[i]/denom2 : 1. -  (num2[i]/denom2));
    x[i] = xmin + inc*i;
    //cout<<i+1<<". x = "<<x[i]<< ", h1 =  "<< num1[i]/denom1<< ", h3 = "<< num3[i]/denom3 << endl;
  }

  double rej2[xbin];for(int i =0;i<xbin;i++)rej2[i]=1-eff2[i];

  TGraph *gr2 = new TGraph(xbin,eff1,rej2);
  gr2->SetName("gr2");
  gr2->SetTitle("Z'ttbar");
  gr2->SetLineColor(c_h2);
  gr2->SetLineWidth(2);
  gr2->GetXaxis()->SetTitle("Eff_{sig}");
  gr2->GetYaxis()->SetTitle("Rej_{bkg} (1-Eff_{bkg})"); 
  gr2->GetXaxis()->SetRangeUser(0,1);
  gr2->GetYaxis()->SetRangeUser(0,1);
  gr2->SetFillStyle(0);


  TFile *fTEMP = new TFile(("temp/TEMP_fhistos_ROC_"+fsave+"_1bkg.root").c_str(),"RECREATE");
  gr2->Write();

  TCanvas *c = new TCanvas("c","c",600,600);

  TMultiGraph *ROC = new TMultiGraph("ROC","");
  ROC->Add(gr2);

  ROC->Draw("APL");
  ROC->GetXaxis()->SetTitle("Eff_{sig}");
  ROC->GetYaxis()->SetTitle("Rej_{bkg} (1-Eff_{bkg})");
  ROC->GetXaxis()->SetLimits(0.,1.);
  //ROC->GetYaxis()->SetLimits(0.,1.);
  ROC->SetMaximum(1.);ROC->SetMinimum(0.);
  ROC->SetTitle("ROC Curves");

  c->BuildLegend(0.2,0.2,0.2+0.2,0.2+0.15);

  gPad->Update();

  c->SaveAs(("plots/ROC_"+fsave+"_1bkg.pdf").c_str());

  fTEMP->Close();
}

void ROC_combined_1bkg(string fname1, string fname2, string fsave,vector<string> labels, vector<TString> infos){

  TFile *f1 = new TFile(fname1.c_str());
  TFile *f2 = new TFile(fname2.c_str());

  TGraph* gr2 = (TGraph*)f1->Get("gr2");
  gr2->SetLineStyle(2);
  gr2->SetTitle(("ttbar, "+labels[0]).c_str());

  TGraph* gr2_ = (TGraph*)f2->Get("gr2");
  gr2_->SetTitle(("ttbar, "+labels[1]).c_str());

  TCanvas *c = new TCanvas("c","c",600,600);

  TMultiGraph *ROC = new TMultiGraph("ROC","");
  ROC->Add(gr2);
  ROC->Add(gr2_);

  ROC->Draw("APL");
  ROC->GetXaxis()->SetTitle("Eff_{sig}");
  ROC->GetYaxis()->SetTitle("Rej_{bkg} (1-Eff_{bkg})");
  ROC->GetXaxis()->SetLimits(0.,1.);
  //ROC->GetYaxis()->SetLimits(0.,1.);
  ROC->SetMaximum(1.);ROC->SetMinimum(0.);
  ROC->SetTitle("ROC Curves");

  c->BuildLegend(0.15,0.15,0.15+0.4,0.15+0.25);

  TLatex *latex = new TLatex();
  latex->SetNDC();
  latex->SetTextSize(0.025);
  latex->SetTextFont(82);
  latex->SetTextAlign(22);
  latex->DrawLatex(0.65, 0.85,infos[0]);

  TLatex *latex2 = new TLatex();
  latex2->SetNDC();
  latex2->SetTextSize(0.025);
  latex2->SetTextFont(82);
  latex2->SetTextAlign(22);
  latex2->DrawLatex(0.65, 0.88,infos[1]);

  gPad->Update();

  c->SaveAs(("plots/ROC_Combined_"+fsave+"_1bkg.pdf").c_str());
}

void ROC_combined3_1bkg(string fname1, string fname2, string fname3, string fsave,vector<string> labels, vector<TString> infos){

  TFile *f1 = new TFile(fname1.c_str());
  TFile *f2 = new TFile(fname2.c_str());
  TFile *f3 = new TFile(fname3.c_str());

  TGraph* gr2 = (TGraph*)f1->Get("gr2");
  gr2->SetLineWidth(2);
  gr2->SetLineStyle(3);
  gr2->SetTitle(("ttbar, "+labels[0]).c_str());

  TGraph* gr2_ = (TGraph*)f2->Get("gr2");
  gr2_->SetTitle(("ttbar, "+labels[1]).c_str());

  TGraph* gr2_3 = (TGraph*)f3->Get("gr2");
  gr2_3->SetLineStyle(7);
  gr2_3->SetTitle(("ttbar, "+labels[2]).c_str());

  TCanvas *c = new TCanvas("c","c",600,600);

  TMultiGraph *ROC = new TMultiGraph("ROC","");
  ROC->Add(gr2);
  ROC->Add(gr2_);
  ROC->Add(gr2_3);

  ROC->Draw("APL");
  ROC->GetXaxis()->SetTitle("Eff_{sig}");
  ROC->GetYaxis()->SetTitle("Rej_{bkg} (1-Eff_{bkg})");
  ROC->GetXaxis()->SetLimits(0.,1.);
  //ROC->GetYaxis()->SetLimits(0.,1.);
  ROC->SetMaximum(1.);ROC->SetMinimum(0.);
  ROC->SetTitle("ROC Curves");

  c->BuildLegend(0.2,0.2,0.2+0.3,0.2+0.25);

  TLatex *latex = new TLatex();
  latex->SetNDC();
  latex->SetTextSize(0.025);
  latex->SetTextFont(82);
  latex->SetTextAlign(22);
  latex->DrawLatex(0.65, 0.85,infos[0]);

  TLatex *latex2 = new TLatex();
  latex2->SetNDC();
  latex2->SetTextSize(0.025);
  latex2->SetTextFont(82);
  latex2->SetTextAlign(22);
  latex2->DrawLatex(0.65, 0.88,infos[1]);

  gPad->Update();

  c->SaveAs(("plots/ROC_Combined3_"+fsave+"_1bkg.pdf").c_str());
}

void makeHistos_1bkg_selectedFj(vector<TString> chains, vector<string> postfix, vector<string> labels, string minPt, string maxPt, TString info_){

  TChain *fs  = new TChain("btaganaSubJets/ttree");
  TChain *fb1  = new TChain("btaganaSubJets/ttree");

  TChain *fs_  = new TChain("btaganaSubJets/ttree");
  TChain *fb1_  = new TChain("btaganaSubJets/ttree");

  string massCut; string ptCut;
  vector<string> fsave; vector<string> fsave2;

  string minMass = "80", maxMass = "150";//, minPt = "300", maxPt = "470";
  string massType = "Groomed";
  massCut = "FatJetInfo.Jet_mass"+massType+">"+minMass+"&&FatJetInfo.Jet_mass"+massType+"<"+maxMass;
  ptCut = "FatJetInfo.Jet_pt>"+minPt+"&&FatJetInfo.Jet_pt<"+maxPt;

  vector<TString> infos;
  infos.push_back(minMass+"<M_{"+massType+"}<"+maxMass+" GeV, "+minPt+"<p_{T}<"+maxPt+" GeV");
  infos.push_back(info_);

  ////1st Set
  fs->Add(chains[0]);
  fb1->Add(chains[1]);

  fsave.push_back("logchi_"+postfix[0]);
  fsave.push_back("pt_"+postfix[0]);
  fsave.push_back("mass_"+postfix[0]);
  Plot_1bkg(fs,fb1,"log(FatJetInfo.Jet_SD_chi)",massCut+"&&"+ptCut+"&&FatJetInfo.Jet_SD_chi>0",fsave[0],"Log(#chi)",100,-26,-6);
  Plot_1bkg(fs,fb1,"FatJetInfo.Jet_pt",massCut+"&&"+ptCut,fsave[1],"p_{T}",100,150,600);
  Plot_1bkg(fs,fb1,"FatJetInfo.Jet_massGroomed",massCut+"&&"+ptCut,fsave[2],"M_{groomed}",100,50,200);
  ROC_1bkg(fsave[0],fsave[1],fsave[0],100,-26,-6);

  ////2nd Set
  fs_->Add(chains[3]);
  fb1_->Add(chains[4]);
 
  fsave2.push_back("logchi_"+postfix[1]);
  fsave2.push_back("pt_"+postfix[1]);
  fsave2.push_back("mass_"+postfix[1]);
  Plot_1bkg(fs_,fb1_,"log(FatJetInfo.Jet_SD_chi)",massCut+"&&"+ptCut+"&&FatJetInfo.Jet_SD_chi>0",fsave2[0],"Log(#chi)",100,-26,-6);
  Plot_1bkg(fs_,fb1_,"FatJetInfo.Jet_pt",massCut+"&&"+ptCut,fsave2[1],"p_{T}",100,150,600);
  Plot_1bkg(fs_,fb1_,"FatJetInfo.Jet_massGroomed",massCut+"&&"+ptCut,fsave2[2],"M_{groomed}",100,50,200);
  ROC_1bkg(fsave2[0],fsave2[1],fsave2[0],100,-26,-6);

  ROC_combined_1bkg(("temp/TEMP_fhistos_ROC_logchi_"+postfix[0]+"_1bkg.root").c_str(),("temp/TEMP_fhistos_ROC_logchi_"+postfix[1]+"_1bkg.root").c_str(),("logchi_"+postfix[0]+"_"+postfix[1]).c_str(),labels, infos);
}


//3 bkg

void Plot_3bkg(TChain *ts, TChain *tb1, TChain* tb2, string var, string cut, string fsave, string xlabel, int bin, float min, float max){

  const int xbin=bin; double xmin=min; double xmax=max;

  TCanvas *c1 =  new TCanvas("c1","c1",600,600);

  TH1D *h1 = new TH1D("h1","h1",xbin,xmin,xmax);
  TH1D *h2 = new TH1D("h2","h2",xbin,xmin,xmax);
  TH1D *h3 = new TH1D("h3","h3",xbin,xmin,xmax);
  TH1D *h4 = new TH1D("h4","h4",xbin,xmin,xmax);

  string cutCommon = cut;

  string cutSig = ""+cutCommon;
  string cutTT = ""+cutCommon;
  string cutQCDb = "abs(int(FatJetInfo.Jet_flavour))==5&&FatJetInfo.Jet_nbHadrons<2&&"+cutCommon;
  string cutQCDgsp = "abs(FatJetInfo.Jet_flavour)==5&&FatJetInfo.Jet_nbHadrons>1&&"+cutCommon;

  ts->Draw((var+">>h1").c_str(),cutSig.c_str());
  tb1->Draw((var+">>h2").c_str(),cutTT.c_str());
  tb2->Draw((var+">>h3").c_str(),cutQCDb.c_str());
  tb2->Draw((var+">>h4").c_str(),cutQCDgsp.c_str());

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

  TFile *fTEMP = new TFile(("temp/TEMP_fhistos_"+fsave+".root").c_str(),"RECREATE");
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
  leg->AddEntry(h1,"RadHH","L");
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

  c1->SaveAs(("plots/"+fsave+".pdf").c_str());

  fTEMP->Close();
}

void ROC_3bkg(string fname,string fdenom,string fsave, const int xbin, double xmin, double xmax, bool direction = 1){

  TFile *f = new TFile(("temp/TEMP_fhistos_"+fname+".root").c_str());
  TFile *fd = new TFile(("temp/TEMP_fhistos_"+fdenom+".root").c_str());

  TH1D* h1 = (TH1D*)f->Get("h1");
  TH1D* h2 = (TH1D*)f->Get("h2");
  TH1D* h3 = (TH1D*)f->Get("h3");
  TH1D* h4 = (TH1D*)f->Get("h4");

  TH1D* d1 = (TH1D*)fd->Get("h1");
  TH1D* d2 = (TH1D*)fd->Get("h2");
  TH1D* d3 = (TH1D*)fd->Get("h3");
  TH1D* d4 = (TH1D*)fd->Get("h4");

  //selfDenom
  //double denom1 = h1->Integral(0,xbin+1); cout<<"denom1 = "<<denom1 << endl;
  //double denom2 = h2->Integral(0,xbin+1); cout<<"denom2 = "<<denom2 << endl;
  //double denom3 = h3->Integral(0,xbin+1); cout<<"denom3 = "<<denom3 << endl;
  //double denom4 = h4->Integral(0,xbin+1); cout<<"denom4 = "<<denom4 << endl;

  //commonDenom
  double denom1 = d1->GetEntries(); //cout<<"denom1 = "<<denom1 << endl;
  double denom2 = d2->GetEntries(); //cout<<"denom2 = "<<denom2 << endl;
  double denom3 = d3->GetEntries(); //cout<<"denom3 = "<<denom3 << endl;
  double denom4 = d4->GetEntries(); //cout<<"denom4 = "<<denom4 << endl;

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
    eff1[i]=(direction==1? num1[i]/denom1 : 1. -  (num1[i]/denom1));
    eff2[i]=(direction==1? num2[i]/denom2 : 1. -  (num2[i]/denom2));
    eff3[i]=(direction==1? num3[i]/denom3 : 1. -  (num3[i]/denom3));
    eff4[i]=(direction==1? num4[i]/denom4 : 1. -  (num4[i]/denom4));
    x[i] = xmin + inc*i;
    //cout<<i+1<<". x = "<<x[i]<< ", h1 =  "<< num1[i]/denom1<< ", h3 = "<< num3[i]/denom3 << endl;
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
  gr2->GetYaxis()->SetTitle("Rej_{bkg} (1-Eff_{bkg})");
  gr2->GetXaxis()->SetRangeUser(0,1);
  gr2->GetYaxis()->SetRangeUser(0,1);
  gr2->SetFillStyle(0);

  TGraph *gr3 = new TGraph(xbin,eff1,rej3);
  gr3->SetName("gr3");
  gr3->SetTitle("QCDb");
  gr3->SetLineColor(c_h3);
  gr3->SetLineWidth(2);
  gr3->GetXaxis()->SetTitle("Eff_{sig}");
  gr3->GetYaxis()->SetTitle("Rej_{bkg} (1-Eff_{bkg})");
  gr3->GetXaxis()->SetRangeUser(0,1);
  gr3->GetYaxis()->SetRangeUser(0,1);
  gr3->SetFillStyle(0);

  TGraph *gr4 = new TGraph(xbin,eff1,rej4);
  gr4->SetName("gr4");
  gr4->SetTitle("QCDgsp");
  gr4->SetLineColor(c_h4);
  gr4->SetLineWidth(2);
  gr4->GetXaxis()->SetTitle("Eff_{sig}");
  gr4->GetYaxis()->SetTitle("Rej_{bkg} (1-Eff_{bkg})");
  gr4->GetXaxis()->SetRangeUser(0,1);
  gr4->GetYaxis()->SetRangeUser(0,1);
  gr4->SetFillStyle(0);

  TFile *fTEMP = new TFile(("temp/TEMP_fhistos_ROC_"+fsave+".root").c_str(),"RECREATE");
  gr2->Write();
  gr3->Write();
  gr4->Write();

  TCanvas *c = new TCanvas("c","c",600,600);

  TMultiGraph *ROC = new TMultiGraph("ROC","");
  ROC->Add(gr2);
  ROC->Add(gr3);
  ROC->Add(gr4);

  ROC->Draw("APL");
  ROC->GetXaxis()->SetTitle("Eff_{sig}");
  ROC->GetYaxis()->SetTitle("Rej_{bkg} (1-Eff_{bkg})");

  ROC->GetXaxis()->SetTitleFont(42);
  ROC->GetYaxis()->SetTitleFont(42);    	
  ROC->GetXaxis()->SetTitleSize(0.035);
  ROC->GetYaxis()->SetTitleSize(0.035);    	
  ROC->GetYaxis()->SetTitleOffset(1.2);	    	
  ROC->GetXaxis()->SetLabelFont(42);
  ROC->GetYaxis()->SetLabelFont(42);    	
  ROC->GetXaxis()->SetLabelSize(0.03);
  ROC->GetYaxis()->SetLabelSize(0.03);    	

  ROC->GetXaxis()->SetLimits(0.,1.);
  //ROC->GetYaxis()->SetLimits(0.,1.);
  ROC->SetMaximum(1.);ROC->SetMinimum(0.);
  ROC->SetTitle("ROC Curves");

  c->BuildLegend(0.2,0.2,0.2+0.2,0.2+0.15);
  
  TLatex *   tex0 = new TLatex(0.42,0.96,"CMS Simulation, #sqrt{s} = 13 TeV");
  tex0->SetNDC();
  tex0->SetTextAlign(13);
  tex0->SetTextFont(42);
  tex0->SetTextFont(62);
  tex0->SetTextSize(0.035); //added by rizki
  tex0->SetLineWidth(2);
  tex0->Draw();
  
  c->SetGridx();
  c->SetGridy();
 

  gPad->Update();

  c->SaveAs(("plots/ROC_"+fsave+".pdf").c_str());

  fTEMP->Close();
}

void ROC_combined_3bkg(string fname1, string fname2, string fsave,vector<string> labels, vector<TString> infos){

  TFile *f1 = new TFile(fname1.c_str());
  TFile *f2 = new TFile(fname2.c_str());

  TGraph* gr2 = (TGraph*)f1->Get("gr2");
  gr2->SetLineStyle(2);
  gr2->SetTitle(("ttbar, "+labels[0]).c_str());
  TGraph* gr3 = (TGraph*)f1->Get("gr3");
  gr3->SetLineStyle(2);
  gr3->SetTitle(("QCDb, "+labels[0]).c_str());
  TGraph* gr4 = (TGraph*)f1->Get("gr4");
  gr4->SetLineStyle(2);
  gr4->SetTitle(("QCDgsp, "+labels[0]).c_str());

  TGraph* gr2_ = (TGraph*)f2->Get("gr2");
  gr2_->SetTitle(("ttbar, "+labels[1]).c_str());
  TGraph* gr3_ = (TGraph*)f2->Get("gr3");
  gr3_->SetTitle(("QCDb, "+labels[1]).c_str());
  TGraph* gr4_ = (TGraph*)f2->Get("gr4");
  gr4_->SetTitle(("QCDgsp, "+labels[1]).c_str());

  TCanvas *c = new TCanvas("c","c",600,600);

  TMultiGraph *ROC = new TMultiGraph("ROC","");
  ROC->Add(gr2);
  ROC->Add(gr3);
  ROC->Add(gr4);
  ROC->Add(gr2_);
  ROC->Add(gr3_);
  ROC->Add(gr4_);

  ROC->Draw("APL");
  ROC->GetXaxis()->SetTitle("Eff_{sig}");
  ROC->GetYaxis()->SetTitle("Rej_{bkg} (1-Eff_{bkg})");
 
  ROC->GetXaxis()->SetTitleFont(42);
  ROC->GetYaxis()->SetTitleFont(42);    	
  ROC->GetXaxis()->SetTitleSize(0.035);
  ROC->GetYaxis()->SetTitleSize(0.035);    	
  ROC->GetYaxis()->SetTitleOffset(1.2);	    	
  ROC->GetXaxis()->SetLabelFont(42);
  ROC->GetYaxis()->SetLabelFont(42);    	
  ROC->GetXaxis()->SetLabelSize(0.03);
  ROC->GetYaxis()->SetLabelSize(0.03);    	
 
  ROC->GetXaxis()->SetLimits(0.,1.);
  //ROC->GetYaxis()->SetLimits(0.,1.);
  ROC->SetMaximum(1.);ROC->SetMinimum(0.);
  ROC->SetTitle("ROC Curves");

  c->BuildLegend(0.15,0.15,0.15+0.4,0.15+0.25);

  TLatex *latex = new TLatex();
  latex->SetNDC();
  latex->SetTextSize(0.025);
  latex->SetTextFont(82);
  latex->SetTextAlign(22);
  latex->DrawLatex(0.65, 0.85,infos[0]);

  TLatex *latex2 = new TLatex();
  latex2->SetNDC();
  latex2->SetTextSize(0.025);
  latex2->SetTextFont(82);
  latex2->SetTextAlign(22);
  latex2->DrawLatex(0.65, 0.88,infos[1]);
  
  TLatex *   tex0 = new TLatex(0.42,0.96,"CMS Simulation, #sqrt{s} = 13 TeV");
  tex0->SetNDC();
  tex0->SetTextAlign(13);
  tex0->SetTextFont(42);
  tex0->SetTextFont(62);
  tex0->SetTextSize(0.035); //added by rizki
  tex0->SetLineWidth(2);
  tex0->Draw();
  
  c->SetGridx();
  c->SetGridy();
  
  gPad->Update();
   
  c->SaveAs(("plots/ROC_Combined_"+fsave+".pdf").c_str());
}

void ROC_combined3_3bkg(string fname1, string fname2, string fname3, string fsave,vector<string> labels, vector<TString> infos){

  TFile *f1 = new TFile(fname1.c_str());
  TFile *f2 = new TFile(fname2.c_str());
  TFile *f3 = new TFile(fname3.c_str());

  TGraph* gr2 = (TGraph*)f1->Get("gr2");
  gr2->SetLineWidth(2);
  gr2->SetLineStyle(3);
  gr2->SetTitle(("ttbar, "+labels[0]).c_str());
  TGraph* gr3 = (TGraph*)f1->Get("gr3");
  gr3->SetLineWidth(2);
  gr3->SetLineStyle(3);
  gr3->SetTitle(("QCDb, "+labels[0]).c_str());
  TGraph* gr4 = (TGraph*)f1->Get("gr4");
  gr4->SetLineWidth(2);
  gr4->SetLineStyle(3);
  gr4->SetTitle(("QCDgsp, "+labels[0]).c_str());

  TGraph* gr2_ = (TGraph*)f2->Get("gr2");
  gr2_->SetTitle(("ttbar, "+labels[1]).c_str());
  TGraph* gr3_ = (TGraph*)f2->Get("gr3");
  gr3_->SetTitle(("QCDb, "+labels[1]).c_str());
  TGraph* gr4_ = (TGraph*)f2->Get("gr4");
  gr4_->SetTitle(("QCDgsp, "+labels[1]).c_str());

  TGraph* gr2_3 = (TGraph*)f3->Get("gr2");
  gr2_3->SetLineStyle(7);
  gr2_3->SetTitle(("ttbar, "+labels[2]).c_str());
  TGraph* gr3_3 = (TGraph*)f3->Get("gr3");
  gr3_3->SetLineStyle(7);
  gr3_3->SetTitle(("QCDb, "+labels[2]).c_str());
  TGraph* gr4_3 = (TGraph*)f3->Get("gr4");
  gr4_3->SetLineStyle(7);
  gr4_3->SetTitle(("QCDgsp, "+labels[2]).c_str());

  TCanvas *c = new TCanvas("c","c",600,600);

  TMultiGraph *ROC = new TMultiGraph("ROC","");
  ROC->Add(gr2);
  ROC->Add(gr3);
  ROC->Add(gr4);
  ROC->Add(gr2_);
  ROC->Add(gr3_);
  ROC->Add(gr4_);
  ROC->Add(gr2_3);
  ROC->Add(gr3_3);
  ROC->Add(gr4_3);

  ROC->Draw("APL");
  ROC->GetXaxis()->SetTitle("Eff_{sig}");
  ROC->GetYaxis()->SetTitle("Rej_{bkg} (1-Eff_{bkg})");
  ROC->GetXaxis()->SetLimits(0.,1.);

  ROC->GetXaxis()->SetTitleFont(42);
  ROC->GetYaxis()->SetTitleFont(42);    	
  ROC->GetXaxis()->SetTitleSize(0.035);
  ROC->GetYaxis()->SetTitleSize(0.035);
  ROC->GetYaxis()->SetTitleOffset(1.2);	    	
  ROC->GetXaxis()->SetLabelFont(42);
  ROC->GetYaxis()->SetLabelFont(42);    	
  ROC->GetXaxis()->SetLabelSize(0.03);
  ROC->GetYaxis()->SetLabelSize(0.03);    	

  //ROC->GetYaxis()->SetLimits(0.,1.);
  ROC->SetMaximum(1.);ROC->SetMinimum(0.);
  ROC->SetTitle("ROC Curves");

  c->BuildLegend(0.2,0.2,0.2+0.3,0.2+0.25);

  TLatex *latex = new TLatex();
  latex->SetNDC();
  latex->SetTextSize(0.025);
  latex->SetTextFont(82);
  latex->SetTextAlign(22);
  latex->DrawLatex(0.65, 0.85,infos[0]);

  TLatex *latex2 = new TLatex();
  latex2->SetNDC();
  latex2->SetTextSize(0.025);
  latex2->SetTextFont(82);
  latex2->SetTextAlign(22);
  latex2->DrawLatex(0.65, 0.88,infos[1]);

  TLatex *   tex0 = new TLatex(0.42,0.96,"CMS Simulation, #sqrt{s} = 13 TeV");
  tex0->SetNDC();
  tex0->SetTextAlign(13);
  tex0->SetTextFont(42);
  tex0->SetTextFont(62);
  tex0->SetTextSize(0.035); //added by rizki
  tex0->SetLineWidth(2);
  tex0->Draw();
  gPad->Update();
  
  c->SetGridx();
  c->SetGridy();

  gPad->Update();

  c->SaveAs(("plots/ROC_Combined3_"+fsave+".pdf").c_str());
}

void makeHistos_3bkg_optimization(vector<TString> chains, vector<string> postfix, vector<string> labels, string minPt, string maxPt, TString info_){

  TChain *fs  = new TChain("btaganaSubJets/ttree");
  TChain *fb1  = new TChain("btaganaSubJets/ttree");
  TChain *fb2  = new TChain("btaganaSubJets/ttree");

  TChain *fs_  = new TChain("btaganaSubJets/ttree");
  TChain *fb1_  = new TChain("btaganaSubJets/ttree");
  TChain *fb2_  = new TChain("btaganaSubJets/ttree");

  string massCut; string ptCut;
  vector<string> fsave; vector<string> fsave2;

  string minMass = "80", maxMass = "150";//, minPt = "300", maxPt = "470";
  string massType = "Groomed";
  massCut = "FatJetInfo.Jet_mass"+massType+">"+minMass+"&&FatJetInfo.Jet_mass"+massType+"<"+maxMass;
  ptCut = "FatJetInfo.Jet_pt>"+minPt+"&&FatJetInfo.Jet_pt<"+maxPt;

  vector<TString> infos;
  infos.push_back(minMass+"<M_{"+massType+"}<"+maxMass+" GeV, "+minPt+"<p_{T}<"+maxPt+" GeV");
  infos.push_back(info_);

  ////1st Set
  fs->Add(chains[0]);
  fb1->Add(chains[1]);
  fb2->Add(chains[2]);

  fsave.push_back("logchi_"+postfix[0]);
  fsave.push_back("pt_"+postfix[0]);
  fsave.push_back("mass_"+postfix[0]);
  Plot_3bkg(fs,fb1,fb2,"log(FatJetInfo.Jet_SD_chi)",massCut+"&&"+ptCut+"&&FatJetInfo.Jet_SD_chi>0",fsave[0],"Log(#chi)",100,-26,-6);
  Plot_3bkg(fs,fb1,fb2,"FatJetInfo.Jet_pt",massCut+"&&"+ptCut,fsave[1],"p_{T}",100,150,600);
  Plot_3bkg(fs,fb1,fb2,"FatJetInfo.Jet_massGroomed",massCut+"&&"+ptCut,fsave[2],"M_{groomed}",100,50,200);
  ROC_3bkg(fsave[0],fsave[1],fsave[0],100,-26,-6);

  ////2nd Set
  fs_->Add(chains[3]);
  fb1_->Add(chains[4]);
  fb2_->Add(chains[5]);

  fsave2.push_back("logchi_"+postfix[1]);
  fsave2.push_back("pt_"+postfix[1]);
  fsave2.push_back("mass_"+postfix[1]);
  Plot_3bkg(fs_,fb1_,fb2_,"log(FatJetInfo.Jet_SD_chi)",massCut+"&&"+ptCut+"&&FatJetInfo.Jet_SD_chi>0",fsave2[0],"Log(#chi)",100,-26,-6);
  Plot_3bkg(fs_,fb1_,fb2_,"FatJetInfo.Jet_pt",massCut+"&&"+ptCut,fsave2[1],"p_{T}",100,150,600);
  Plot_3bkg(fs_,fb1_,fb2_,"FatJetInfo.Jet_massGroomed",massCut+"&&"+ptCut,fsave2[2],"M_{groomed}",100,50,200);
  ROC_3bkg(fsave2[0],fsave2[1],fsave2[0],100,-26,-6);

  ROC_combined_3bkg(("temp/TEMP_fhistos_ROC_logchi_"+postfix[0]+".root").c_str(),("temp/TEMP_fhistos_ROC_logchi_"+postfix[1]+".root").c_str(),("logchi_"+postfix[0]+"_"+postfix[1]).c_str(),labels, infos);
}


//2 bkg - QCD inclusive

void Plot_2bkg(TChain *ts, TChain *tb1, TChain* tb2, string var, string cut, string fsave, string xlabel, int bin, float min, float max){

  const int xbin=bin; double xmin=min; double xmax=max;

  TCanvas *c1 =  new TCanvas("c1","c1",600,600);

  TH1D *h1 = new TH1D("h1","h1",xbin,xmin,xmax);
  TH1D *h2 = new TH1D("h2","h2",xbin,xmin,xmax);
  TH1D *h3 = new TH1D("h3","h3",xbin,xmin,xmax);

  string cutCommon = cut;

  string cutSig = ""+cutCommon;
  string cutTT = ""+cutCommon;
  string cutQCD = ""+cutCommon;

  ts->Draw((var+">>h1").c_str(),cutSig.c_str());
  tb1->Draw((var+">>h2").c_str(),cutTT.c_str());
  tb2->Draw((var+">>h3").c_str(),cutQCD.c_str());

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

  TFile *fTEMP = new TFile(("temp/TEMP_fhistos_"+fsave+".root").c_str(),"RECREATE");
  h1->Write();
  h2->Write();
  h3->Write();

  h1->Scale(1/h1->GetEntries());
  h2->Scale(1/h2->GetEntries());
  h3->Scale(1/h3->GetEntries());

  THStack *h = new THStack("h","");
  h->Add(h1,"sames");
  h->Add(h2,"sames");
  h->Add(h3,"sames");
  h->Draw("nostack");
  h->GetXaxis()->SetTitle(xlabel.c_str());

  TLegend *leg = new TLegend(0.2,0.65,0.4,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h1,"RadHH","L");
  leg->AddEntry(h2,"Z'ttbar","L");
  leg->AddEntry(h3,"QCD","L");
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

  gPad->Update();

  c1->SaveAs(("plots/"+fsave+".pdf").c_str());

  fTEMP->Close();
}

void ROC_2bkg(string fname,string fdenom,string fsave, const int xbin, double xmin, double xmax, bool direction = 1){

  TFile *f = new TFile(("temp/TEMP_fhistos_"+fname+".root").c_str());
  TFile *fd = new TFile(("temp/TEMP_fhistos_"+fdenom+".root").c_str());

  TH1D* h1 = (TH1D*)f->Get("h1");
  TH1D* h2 = (TH1D*)f->Get("h2");
  TH1D* h3 = (TH1D*)f->Get("h3");

  TH1D* d1 = (TH1D*)fd->Get("h1");
  TH1D* d2 = (TH1D*)fd->Get("h2");
  TH1D* d3 = (TH1D*)fd->Get("h3");

  //selfDenom
  //double denom1 = h1->Integral(0,xbin+1); cout<<"denom1 = "<<denom1 << endl;
  //double denom2 = h2->Integral(0,xbin+1); cout<<"denom2 = "<<denom2 << endl;
  //double denom3 = h3->Integral(0,xbin+1); cout<<"denom3 = "<<denom3 << endl;
  //double denom4 = h4->Integral(0,xbin+1); cout<<"denom4 = "<<denom4 << endl;

  //commonDenom
  double denom1 = d1->GetEntries(); //cout<<"denom1 = "<<denom1 << endl;
  double denom2 = d2->GetEntries(); //cout<<"denom2 = "<<denom2 << endl;
  double denom3 = d3->GetEntries(); //cout<<"denom3 = "<<denom3 << endl;

  //const int xbin = h1->GetSize()-2;

  double num1[xbin];
  double num2[xbin];
  double num3[xbin];
  double eff1[xbin];
  double eff2[xbin];
  double eff3[xbin];

  double x[xbin];
  double inc = (xmax-xmin)/xbin;

  for(int i=0; i<xbin;i++){
    num1[i]=h1->Integral(i+1,xbin+1);
    num2[i]=h2->Integral(i+1,xbin+1);
    num3[i]=h3->Integral(i+1,xbin+1);
    eff1[i]=(direction==1? num1[i]/denom1 : 1. -  (num1[i]/denom1));
    eff2[i]=(direction==1? num2[i]/denom2 : 1. -  (num2[i]/denom2));
    eff3[i]=(direction==1? num3[i]/denom3 : 1. -  (num3[i]/denom3));
    x[i] = xmin + inc*i;
    //cout<<i+1<<". x = "<<x[i]<< ", h1 =  "<< num1[i]/denom1<< ", h3 = "<< num3[i]/denom3 << endl;
  }

  double rej2[xbin];for(int i =0;i<xbin;i++)rej2[i]=1-eff2[i];
  double rej3[xbin];for(int i =0;i<xbin;i++)rej3[i]=1-eff3[i];

  TGraph *gr2 = new TGraph(xbin,eff1,rej2);
  gr2->SetName("gr2");
  gr2->SetTitle("Z'ttbar");
  gr2->SetLineColor(c_h2);
  gr2->SetLineWidth(2);
  gr2->GetXaxis()->SetTitle("Eff_{sig}");
  gr2->GetYaxis()->SetTitle("Rej_{bkg} (1-Eff_{bkg})");
  gr2->GetXaxis()->SetRangeUser(0,1);
  gr2->GetYaxis()->SetRangeUser(0,1);
  gr2->SetFillStyle(0);

  TGraph *gr3 = new TGraph(xbin,eff1,rej3);
  gr3->SetName("gr3");
  gr3->SetTitle("QCD");
  gr3->SetLineColor(c_h3);
  gr3->SetLineWidth(2);
  gr3->GetXaxis()->SetTitle("Eff_{sig}");
  gr3->GetYaxis()->SetTitle("Rej_{bkg} (1-Eff_{bkg})");
  gr3->GetXaxis()->SetRangeUser(0,1);
  gr3->GetYaxis()->SetRangeUser(0,1);
  gr3->SetFillStyle(0);

  TFile *fTEMP = new TFile(("temp/TEMP_fhistos_ROC_"+fsave+".root").c_str(),"RECREATE");
  gr2->Write();
  gr3->Write();

  TCanvas *c = new TCanvas("c","c",600,600);

  TMultiGraph *ROC = new TMultiGraph("ROC","");
  ROC->Add(gr2);
  ROC->Add(gr3);

  ROC->Draw("APL");
  ROC->GetXaxis()->SetTitle("Eff_{sig}");
  ROC->GetYaxis()->SetTitle("Rej_{bkg} (1-Eff_{bkg})");

  ROC->GetXaxis()->SetTitleFont(42);
  ROC->GetYaxis()->SetTitleFont(42);    	
  ROC->GetXaxis()->SetTitleSize(0.035);
  ROC->GetYaxis()->SetTitleSize(0.035);    	
  ROC->GetYaxis()->SetTitleOffset(1.2);	    	
  ROC->GetXaxis()->SetLabelFont(42);
  ROC->GetYaxis()->SetLabelFont(42);    	
  ROC->GetXaxis()->SetLabelSize(0.03);
  ROC->GetYaxis()->SetLabelSize(0.03);    	

  ROC->GetXaxis()->SetLimits(0.,1.);
  //ROC->GetYaxis()->SetLimits(0.,1.);
  ROC->SetMaximum(1.);ROC->SetMinimum(0.);
  ROC->SetTitle("ROC Curves");

  c->BuildLegend(0.2,0.2,0.2+0.2,0.2+0.15);
  
  TLatex *   tex0 = new TLatex(0.42,0.96,"CMS Simulation, #sqrt{s} = 13 TeV");
  tex0->SetNDC();
  tex0->SetTextAlign(13);
  tex0->SetTextFont(42);
  tex0->SetTextFont(62);
  tex0->SetTextSize(0.035); //added by rizki
  tex0->SetLineWidth(2);
  tex0->Draw();
  
//   c->SetGridx();
//   c->SetGridy();
 

  gPad->Update();

  c->SaveAs(("plots/ROC_"+fsave+".pdf").c_str());

  fTEMP->Close();
}

void ROC_combined_2bkg(string fname1, string fname2, string fsave,vector<string> labels, vector<TString> infos){

  TFile *f1 = new TFile(fname1.c_str());
  TFile *f2 = new TFile(fname2.c_str());

  TGraph* gr2 = (TGraph*)f1->Get("gr2");
  gr2->SetLineStyle(2);
  gr2->SetTitle(("ttbar, "+labels[0]).c_str());
  TGraph* gr3 = (TGraph*)f1->Get("gr3");
  gr3->SetLineStyle(2);
  gr3->SetTitle(("QCD, "+labels[0]).c_str());

  TGraph* gr2_ = (TGraph*)f2->Get("gr2");
  gr2_->SetTitle(("ttbar, "+labels[1]).c_str());
  TGraph* gr3_ = (TGraph*)f2->Get("gr3");
  gr3_->SetTitle(("QCD, "+labels[1]).c_str());
 
  TCanvas *c = new TCanvas("c","c",600,600);

  TMultiGraph *ROC = new TMultiGraph("ROC","");
  ROC->Add(gr2);
  ROC->Add(gr3);
  ROC->Add(gr2_);
  ROC->Add(gr3_);

  ROC->Draw("APL");
  ROC->GetXaxis()->SetTitle("Eff_{sig}");
  ROC->GetYaxis()->SetTitle("Rej_{bkg} (1-Eff_{bkg})");
 
  ROC->GetXaxis()->SetTitleFont(42);
  ROC->GetYaxis()->SetTitleFont(42);    	
  ROC->GetXaxis()->SetTitleSize(0.035);
  ROC->GetYaxis()->SetTitleSize(0.035);    	
  ROC->GetYaxis()->SetTitleOffset(1.2);	    	
  ROC->GetXaxis()->SetLabelFont(42);
  ROC->GetYaxis()->SetLabelFont(42);    	
  ROC->GetXaxis()->SetLabelSize(0.03);
  ROC->GetYaxis()->SetLabelSize(0.03);    	
 
  ROC->GetXaxis()->SetLimits(0.,1.);
  //ROC->GetYaxis()->SetLimits(0.,1.);
  ROC->SetMaximum(1.);ROC->SetMinimum(0.);
  ROC->SetTitle("ROC Curves");

  c->BuildLegend(0.15,0.15,0.15+0.4,0.15+0.25);

  TLatex *latex = new TLatex();
  latex->SetNDC();
  latex->SetTextSize(0.025);
  latex->SetTextFont(82);
  latex->SetTextAlign(22);
  latex->DrawLatex(0.65, 0.85,infos[0]);

  TLatex *latex2 = new TLatex();
  latex2->SetNDC();
  latex2->SetTextSize(0.025);
  latex2->SetTextFont(82);
  latex2->SetTextAlign(22);
  latex2->DrawLatex(0.65, 0.88,infos[1]);
  
  TLatex *   tex0 = new TLatex(0.42,0.96,"CMS Simulation, #sqrt{s} = 13 TeV");
  tex0->SetNDC();
  tex0->SetTextAlign(13);
  tex0->SetTextFont(42);
  tex0->SetTextFont(62);
  tex0->SetTextSize(0.035); //added by rizki
  tex0->SetLineWidth(2);
  tex0->Draw();
  
//   c->SetGridx();
//   c->SetGridy();
  
  gPad->Update();
   
  c->SaveAs(("plots/ROC_Combined_"+fsave+".pdf").c_str());
}

void ROC_combined3_2bkg(string fname1, string fname2, string fname3, string fsave,vector<string> labels, vector<TString> infos){

  TFile *f1 = new TFile(fname1.c_str());
  TFile *f2 = new TFile(fname2.c_str());
  TFile *f3 = new TFile(fname3.c_str());

  TGraph* gr2 = (TGraph*)f1->Get("gr2");
  gr2->SetLineWidth(2);
  gr2->SetLineStyle(3);
  gr2->SetTitle(("ttbar, "+labels[0]).c_str());
  TGraph* gr3 = (TGraph*)f1->Get("gr3");
  gr3->SetLineWidth(2);
  gr3->SetLineStyle(3);
  gr3->SetTitle(("QCD, "+labels[0]).c_str());

  TGraph* gr2_ = (TGraph*)f2->Get("gr2");
  gr2_->SetTitle(("ttbar, "+labels[1]).c_str());
  TGraph* gr3_ = (TGraph*)f2->Get("gr3");
  gr3_->SetTitle(("QCDb, "+labels[1]).c_str());

  TGraph* gr2_3 = (TGraph*)f3->Get("gr2");
  gr2_3->SetLineStyle(7);
  gr2_3->SetTitle(("ttbar, "+labels[2]).c_str());
  TGraph* gr3_3 = (TGraph*)f3->Get("gr3");
  gr3_3->SetLineStyle(7);
  gr3_3->SetTitle(("QCD, "+labels[2]).c_str());

  TCanvas *c = new TCanvas("c","c",600,600);

  TMultiGraph *ROC = new TMultiGraph("ROC","");
  ROC->Add(gr2);
  ROC->Add(gr3);
  ROC->Add(gr2_);
  ROC->Add(gr3_);
  ROC->Add(gr2_3);
  ROC->Add(gr3_3);

  ROC->Draw("APL");
  ROC->GetXaxis()->SetTitle("Eff_{sig}");
  ROC->GetYaxis()->SetTitle("Rej_{bkg} (1-Eff_{bkg})");
  ROC->GetXaxis()->SetLimits(0.,1.);

  ROC->GetXaxis()->SetTitleFont(42);
  ROC->GetYaxis()->SetTitleFont(42);    	
  ROC->GetXaxis()->SetTitleSize(0.035);
  ROC->GetYaxis()->SetTitleSize(0.035);
  ROC->GetYaxis()->SetTitleOffset(1.2);	    	
  ROC->GetXaxis()->SetLabelFont(42);
  ROC->GetYaxis()->SetLabelFont(42);    	
  ROC->GetXaxis()->SetLabelSize(0.03);
  ROC->GetYaxis()->SetLabelSize(0.03);    	

  //ROC->GetYaxis()->SetLimits(0.,1.);
  ROC->SetMaximum(1.);ROC->SetMinimum(0.);
  ROC->SetTitle("ROC Curves");

  c->BuildLegend(0.2,0.2,0.2+0.3,0.2+0.25);

  TLatex *latex = new TLatex();
  latex->SetNDC();
  latex->SetTextSize(0.025);
  latex->SetTextFont(82);
  latex->SetTextAlign(22);
  latex->DrawLatex(0.65, 0.85,infos[0]);

  TLatex *latex2 = new TLatex();
  latex2->SetNDC();
  latex2->SetTextSize(0.025);
  latex2->SetTextFont(82);
  latex2->SetTextAlign(22);
  latex2->DrawLatex(0.65, 0.88,infos[1]);

  TLatex *   tex0 = new TLatex(0.42,0.96,"CMS Simulation, #sqrt{s} = 13 TeV");
  tex0->SetNDC();
  tex0->SetTextAlign(13);
  tex0->SetTextFont(42);
  tex0->SetTextFont(62);
  tex0->SetTextSize(0.035); //added by rizki
  tex0->SetLineWidth(2);
  tex0->Draw();
  gPad->Update();
  
//   c->SetGridx();
//   c->SetGridy();

  gPad->Update();

  c->SaveAs(("plots/ROC_Combined3_"+fsave+".pdf").c_str());
}

void makeHistos_2bkg_optimization(vector<TString> chains, vector<string> postfix, vector<string> labels, string minPt, string maxPt, TString info_){

  TChain *fs  = new TChain("btaganaSubJets/ttree");
  TChain *fb1  = new TChain("btaganaSubJets/ttree");
  TChain *fb2  = new TChain("btaganaSubJets/ttree");

  TChain *fs_  = new TChain("btaganaSubJets/ttree");
  TChain *fb1_  = new TChain("btaganaSubJets/ttree");
  TChain *fb2_  = new TChain("btaganaSubJets/ttree");

  string massCut; string ptCut;
  vector<string> fsave; vector<string> fsave2;

  string minMass = "80", maxMass = "150";//, minPt = "300", maxPt = "470";
  string massType = "Groomed";
  massCut = "FatJetInfo.Jet_mass"+massType+">"+minMass+"&&FatJetInfo.Jet_mass"+massType+"<"+maxMass;
  ptCut = "FatJetInfo.Jet_pt>"+minPt+"&&FatJetInfo.Jet_pt<"+maxPt;

  vector<TString> infos;
  infos.push_back(minMass+"<M_{"+massType+"}<"+maxMass+" GeV, "+minPt+"<p_{T}<"+maxPt+" GeV");
  infos.push_back(info_);

  ////1st Set
  fs->Add(chains[0]);
  fb1->Add(chains[1]);
  fb2->Add(chains[2]);

  fsave.push_back("logchi_"+postfix[0]);
  fsave.push_back("pt_"+postfix[0]);
  fsave.push_back("mass_"+postfix[0]);
  Plot_2bkg(fs,fb1,fb2,"log(FatJetInfo.Jet_SD_chi)",massCut+"&&"+ptCut+"&&FatJetInfo.Jet_SD_chi>0",fsave[0],"Log(#chi)",100,-26,-6);
  Plot_2bkg(fs,fb1,fb2,"FatJetInfo.Jet_pt",massCut+"&&"+ptCut,fsave[1],"p_{T}",100,150,600);
  Plot_2bkg(fs,fb1,fb2,"FatJetInfo.Jet_massGroomed",massCut+"&&"+ptCut,fsave[2],"M_{groomed}",100,50,200);
  ROC_2bkg(fsave[0],fsave[1],fsave[0],100,-26,-6);

  ////2nd Set
  fs_->Add(chains[3]);
  fb1_->Add(chains[4]);
  fb2_->Add(chains[5]);

  fsave2.push_back("logchi_"+postfix[1]);
  fsave2.push_back("pt_"+postfix[1]);
  fsave2.push_back("mass_"+postfix[1]);
  Plot_2bkg(fs_,fb1_,fb2_,"log(FatJetInfo.Jet_SD_chi)",massCut+"&&"+ptCut+"&&FatJetInfo.Jet_SD_chi>0",fsave2[0],"Log(#chi)",100,-26,-6);
  Plot_2bkg(fs_,fb1_,fb2_,"FatJetInfo.Jet_pt",massCut+"&&"+ptCut,fsave2[1],"p_{T}",100,150,600);
  Plot_2bkg(fs_,fb1_,fb2_,"FatJetInfo.Jet_massGroomed",massCut+"&&"+ptCut,fsave2[2],"M_{groomed}",100,50,200);
  ROC_2bkg(fsave2[0],fsave2[1],fsave2[0],100,-26,-6);

  ROC_combined_2bkg(("temp/TEMP_fhistos_ROC_logchi_"+postfix[0]+".root").c_str(),("temp/TEMP_fhistos_ROC_logchi_"+postfix[1]+".root").c_str(),("logchi_"+postfix[0]+"_"+postfix[1]).c_str(),labels, infos);
}


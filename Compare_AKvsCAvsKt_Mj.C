using namespace std;

void Compare_3plots(TFile *f1, TFile *f2, TFile *f3, string fsavename, string name1, string name2,string name3, string var,string commoncut, string cut1, string cut2,string cut3, string xlabel, float xbin, float xmin, float xmax){

  TTree *t1 = (TTree*) f1->Get("tree");
  TTree *t2 = (TTree*) f2->Get("tree");
  TTree *t3 = (TTree*) f3->Get("tree");

  Color_t c_h1 = kBlue;
  Color_t c_h2 = kGreen+2;
  Color_t c_h3 = kRed;

  gStyle->SetOptStat("nemrou");

  TH1D *h1 = new TH1D("h1","h1",xbin,xmin,xmax);
  TH1D *h2 = new TH1D("h2","h2",xbin,xmin,xmax);
  TH1D *h3 = new TH1D("h3","h3",xbin,xmin,xmax);

  TCanvas *c1 = new TCanvas("c1","c1",600,600);

  t1->Draw((var+">>h1").c_str(),(commoncut+cut1).c_str());
  t2->Draw((var+">>h2").c_str(),(commoncut+cut2).c_str());
  t3->Draw((var+">>h3").c_str(),(commoncut+cut3).c_str());

  h1->SetTitle("");
  h1->GetXaxis()->SetTitle(xlabel.c_str());
  h1->SetLineColor(c_h1);
  h1->SetLineWidth(2);
  h2->SetTitle("");
  h2->GetXaxis()->SetTitle(xlabel.c_str());
  h2->SetLineColor(c_h2);
  h2->SetLineWidth(2);
  h3->SetTitle("");
  h3->GetXaxis()->SetTitle(xlabel.c_str());
  h3->SetLineColor(c_h3);
  h3->SetLineWidth(2);

  THStack *hs = new THStack("hs","");
  hs->Add(h1,"sames");
  hs->Add(h2,"sames");
  hs->Add(h3,"sames");
  hs->Draw("nostack");
  hs->GetXaxis()->SetTitle(xlabel.c_str());


  TLegend *leg = new TLegend(0.6,0.65,0.8,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h1,name1.c_str(),"L");
  leg->AddEntry(h2,name2.c_str(),"L");
  leg->AddEntry(h3,name3.c_str(),"L");
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

  c1->SaveAs(("rootfiles/"+fsavename+"_"+var+"_"+commoncut+".eps").c_str());
}

void Alakazam(){
  string prefix = "FakeMjIVFbtagCalculation_";
  string fname = "QCD_Pt-470to600_Tune4C_13TeV_pythia8";
  string type1 = "_R08_r015_HiggsWin20_tagr07_fake02_BtagALLMj_MjIVF015_mc_subjets"; //string postfix ="";
  string type2 = "_R08_r015_AkMj_HiggsWin30_tagr07_fake02_BtagALLMj_MjIVF015_mc_subjets"; //string postfix = "_AkMj"; //DOUBLE CHECK postfix! for saving name purposes.
  string type3 = "_R08_r015_CAMj_HiggsWin30_tagr07_fake02_BtagALLMj_MjIVF015_mc_subjets"; //string postfix = "_AkMj"; //DOUBLE CHECK postfix! for saving name purposes.
  string cut;

  TCanvas *c1 = new TCanvas();

  gStyle->SetOptStat("nemrou");

  TFile *f1 = new TFile(("rootfiles/"+prefix+fname+type1+".root").c_str());
  TFile *f2 = new TFile(("rootfiles/"+prefix+fname+type2+".root").c_str());
  TFile *f3 = new TFile(("rootfiles/"+prefix+fname+type3+".root").c_str());

  Compare_3plots(f1,f2,f3,"QCD470_AKvsCAvsKT_Fj_nMj","Kt","AK","CA","Fj_nMj","","","","","No. Microjets",10,-0.5,9.5);

  Compare_3plots(f1,f2,f3,"QCD470_AKvsCAvsKT_Fj_nMj","Kt","AK","CA","Fj_nMj","abs(Fj_flavour)!=5&&abs(Fj_flavour)!=4","","","","No. Microjets",10,-0.5,9.5);

  Compare_3plots(f1,f2,f3,"QCD470_AKvsCAvsKT_Fj_nBtagMj","Kt","AK","CA","Fj_nBtagMj","abs(Fj_flavour)!=5&&abs(Fj_flavour)!=4","","","","No. Btagged Microjets",10,-0.5,9.5);

  Compare_3plots(f1,f2,f3,"QCD470_AKvsCAvsKT_Mj_pt","Kt","AK","CA","Mj_pt","abs(Fj_flavour)!=5&&abs(Fj_flavour)!=4","","","","Microjet p_{T}",40,0,800);

  Compare_3plots(f1,f2,f3,"QCD470_AKvsCAvsKT_Mj_pt","Kt","AK","CA","Mj_pt","abs(Fj_flavour)!=5&&abs(Fj_flavour)!=4&&Mj_isBtag==1","","","","Microjet p_{T}",40,0,800);

}

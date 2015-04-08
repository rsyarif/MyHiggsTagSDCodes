#include <iostream>
#include <sstream>
#include <string>
#include <TFile.h>
#include <TTree.h>
#include <TLegend.h>
#include <TPaveStats.h>
#include <TH1D.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TMultiGraph.h>
#include <TLatex.h>
#include <TMarker.h>

using namespace std;

void Alakazam(){

  std::string dir = "rootfiles";

  std::string fn1 = "PLOTS_Rad_HHto4b_M800_13TeV_AOD_R08_r015_HiggsWin20_mc_subjets_Mj_dR_";
  std::string fn2 = "PLOTS_Rad_HHto4b_M800_13TeV_AOD_R08_r015_HiggsWin20_mc_subjets_Mj_dR_SV_";
  std::string fn3 = "PLOTS_Rad_HHto4b_M800_13TeV_AOD_R08_r015_HiggsWin20_mc_subjets_Mj_dR_SV_gen_";

  TFile *f1 = new TFile((dir+"/"+fn1+".root").c_str());
  TFile *f2 = new TFile((dir+"/"+fn2+".root").c_str());
  TFile *f3 = new TFile((dir+"/"+fn3+".root").c_str());

  TH1D *h1 = (TH1D*)f1->Get("h");
  TH1D *h2 = (TH1D*)f2->Get("h");
  TH1D *h3 = (TH1D*)f3->Get("h");

  int h1_nbins = h1->GetSize()-2;
  int h2_nbins = h2->GetSize()-2;
  int h3_nbins = h3->GetSize()-2;

  cout<<"h1_nbins = "<< h1_nbins<<", h2_nbins = "<< h2_nbins<<", h3_nbins = "<< h3_nbins<<endl;

  double Sh1 = h1->Integral(1,h1_nbins);
  double Sh2 = h2->Integral(1,h2_nbins);
  double Sh3 = h3->Integral(1,h3_nbins);

  double h1_integral[h1_nbins];
  double h2_integral[h2_nbins];
  double h1_eff[h1_nbins];
  double h2_eff[h2_nbins];

  double x[h1_nbins]; double xmin = 0; double xmax = 0.15;
  double increment = (xmax-xmin)/h1_nbins;

  for(int i=0;i<h1_nbins;i++){
    h1_integral[i]= Sh1 - h1->Integral(i+1,h1_nbins);
    h2_integral[i]= Sh2 - h2->Integral(i+1,h2_nbins);
    h1_eff[i] = h1_integral[i]/Sh1;
    h2_eff[i] = h2_integral[i]/Sh2;
    x[i] = xmin + increment*i;

    cout<<i+1<<". x = "<<x[i]<< ", h1 =  "<< h1_integral[i]/Sh1<< ", h2 = "<< h2_integral[i]/Sh2 << endl;
  }
  cout << endl;
  cout<<"Sh1 = "<<Sh1<<", Sh2 = "<<Sh2<<", Sh3 = "<<Sh3<<endl;
  //------

  TCanvas *c1 = new TCanvas("c1","c1",800, 600);

  TMultiGraph *mg = new TMultiGraph("mg","mg");

  TGraph *gr1 = new TGraph(h1_nbins,x,h1_eff);
  gr1->SetName("gr1");
  gr1->SetTitle("Microjet-Gen");
  gr1->SetMarkerStyle(7);
  gr1->SetMarkerColor(kGreen);
  gr1->SetDrawOption("AP");
  gr1->SetLineColor(kBlue);
  gr1->SetLineWidth(2);
  gr1->SetFillStyle(0);

  TGraph *gr2 = new TGraph(h2_nbins,x,h2_eff);
  gr2->SetName("gr2");
  gr2->SetTitle("Microjet-IVF SV");
  gr2->SetMarkerStyle(7);
  gr2->SetMarkerColor(kRed+4);
  gr2->SetDrawOption("P");
  gr2->SetLineColor(kRed);
  gr2->SetLineWidth(2);
  gr2->SetFillStyle(0);

  mg->Add( gr1 );
  mg->Add( gr2 );

  mg->Draw("APL");
  mg->SetTitle("");
  mg->GetXaxis()->SetTitle("#DeltaR");
  mg->GetYaxis()->SetTitle("Fraction");
  mg->SetTitle("dR");
  c1->BuildLegend(0.7,.65,.9,.8);

  c1->SaveAs((dir+"/"+"Plot_MjdR_MjdRSV_Fraction.eps").c_str());

  //-------

  TCanvas *c2 = new TCanvas("c2","c2",800, 600);

  double ratio[h1_nbins];
  for(int i=0;i<h1_nbins;i++){
    if(h2_eff[i]!=0)ratio[i] = h1_eff[i]/h2_eff[i];
    if(h1_eff[i]==0&&h2_eff[i]==0)ratio[i]=1;
  }

  TGraph *gr3 = new TGraph(h1_nbins,x,ratio);
  //gr3->SetTitle("#frac{Microjet-Gen}{Microjet-IVF}");
  gr3->SetLineWidth(2);
  gr3->SetLineColor(kBlue);
  gr3->SetFillStyle(0);
  gr3->SetMarkerStyle(7);
  gr3->SetMarkerColor(kRed);
  c2->cd();
  gr3->Draw("APL");
  gr3->GetXaxis()->SetTitle("#DeltaR");
  gr3->GetYaxis()->SetTitle("Ratio of Fraction");
  //c2->BuildLegend(0.7,.75,.9,.9);

  TLegend *leg2 = new TLegend(0.5,0.65,0.8,0.85);
  leg2->SetFillStyle(0);
  leg2->SetBorderSize(0);
  leg2->AddEntry(gr3,"#frac{% Mj-Gen}{% Mj-IVF}","L");
  leg2->Draw("SAME");

  c2->SetGridy();

  c2->SaveAs((dir+"/"+"Plot_MjdR_MjdRSV_Ratio.eps").c_str());

  //------

  TCanvas *c3 = new TCanvas("c3","c3",800,600);

  c3->cd();

  h1->Scale(1/Sh1);
  h2->Scale(1/Sh2);
  h3->Scale(1/Sh3);

  h1->Draw();
  h2->Draw("SAMES");
  h3->Draw("SAMES");

  h2->SetLineColor(kGreen+2);
  h3->SetLineColor(kYellow+2);

  h1->SetTitle("");
  h2->SetTitle("");
  h2->SetTitle("");

  TPaveStats *tps1 = (TPaveStats*) h1->FindObject("stats");
  tps1->SetTextColor(kBlue);
  double X1 = tps1->GetX1NDC();
  double Y1 = tps1->GetY1NDC();
  double X2 = tps1->GetX2NDC();
  double Y2 = tps1->GetY2NDC();

  TPaveStats *tps2 = (TPaveStats*) h2->FindObject("stats");
  tps2->SetTextColor(kGreen+2);
  tps2->SetX1NDC(X1);
  tps2->SetX2NDC(X2);
  tps2->SetY1NDC(Y1-(Y2-Y1));
  tps2->SetY2NDC(Y1);

  h1->SetStats(0);
  h2->SetStats(0);
  h3->SetStats(0);

  TLegend *leg = new TLegend(0.5,0.65,0.8,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h1,"Mj-Gen","L");
  leg->AddEntry(h2,"Mj-IVF","L");
  leg->AddEntry(h3,"Gen-IVF","L");
  leg->Draw("SAME");

  h1->GetXaxis()->SetTitle("#Delta R");

  c3->SaveAs((dir+"/"+"Plot_MjdR_MjdRSV_SuperImpose.eps").c_str());


}

#include <iostream>
#include <TFile.h>
#include <TH1D.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TMultiGraph.h>

using namespace std;

string dir = "1leadbtagmjcondition";

void Plot_efficiency(){
  TFile *f = new TFile((dir+"/"+"PartonMatch_histos.root").c_str());

  TH1D *h_sig_l = (TH1D*)f->Get("h_sig_l");
  TH1D *h_bkg_l = (TH1D*)f->Get("h_bkg_l");

  TH1D *h_sig_m = (TH1D*)f->Get("h_sig_m");
  TH1D *h_bkg_m = (TH1D*)f->Get("h_bkg_m");

  TH1D *h_sig_t = (TH1D*)f->Get("h_sig_t");
  TH1D *h_bkg_t = (TH1D*)f->Get("h_bkg_t");

  double x_l[sig_l_nbins]; double xmin = -18.; double xmax = -2.;
  double increment = (xmax-xmin)/sig_l_nbins;

  int sig_l_nbins = h_sig_l->GetSize()-2;
  int bkg_l_nbins = h_bkg_l->GetSize()-2;
  double Ssig_l = h_sig_l->Integral(0,sig_l_nbins+1);
  double Sbkg_l = h_bkg_l->Integral(0,bkg_l_nbins+1);
  double sig_l_integral[sig_l_nbins];
  double bkg_l_integral[bkg_l_nbins];
  double sig_l_eff[sig_l_nbins];
  double bkg_l_eff[bkg_l_nbins];
  for(int i=0;i<sig_l_nbins;i++){
    sig_l_integral[i]=h_sig_l->Integral(i+1,sig_l_nbins+1);
    bkg_l_integral[i]=h_bkg_l->Integral(i+1,bkg_l_nbins+1);
    sig_l_eff[i] = sig_l_integral[i]/Ssig_l;
    bkg_l_eff[i] = bkg_l_integral[i]/Sbkg_l;
    x_l[i] = xmin + increment*i;
    //cout<<i+1<<". x = "<<x_l[i]<< ", sig_l =  "<< sig_l_integral[i]/Ssig_l<< ", bkg_l = "<< bkg_l_integral[i]/Sbkg_l << endl;
  }

  int sig_m_nbins = h_sig_m->GetSize()-2;
  int bkg_m_nbins = h_bkg_m->GetSize()-2;
  double Ssig_m = h_sig_m->Integral(0,sig_m_nbins+1);
  double Sbkg_m = h_bkg_m->Integral(0,bkg_m_nbins+1);
  double sig_m_integral[sig_m_nbins];
  double bkg_m_integral[bkg_m_nbins];
  double sig_m_eff[sig_m_nbins];
  double bkg_m_eff[bkg_m_nbins];
  double x_m[sig_m_nbins]; //double xmin = -18.; double xmax = -2.;
  increment = (xmax-xmin)/sig_m_nbins;
  for(int i=0;i<sig_m_nbins;i++){
    sig_m_integral[i]=h_sig_m->Integral(i+1,sig_m_nbins+1);
    bkg_m_integral[i]=h_bkg_m->Integral(i+1,bkg_m_nbins+1);
    sig_m_eff[i] = sig_m_integral[i]/Ssig_m;
    bkg_m_eff[i] = bkg_m_integral[i]/Sbkg_m;
    x_m[i] = xmin + increment*i;
    //cout<<i+1<<". x = "<<x_m[i]<< ", sig_m =  "<< sig_m_integral[i]/Ssig_m<< ", bkg_m = "<< bkg_m_integral[i]/Sbkg_m << endl;
  }

  int sig_t_nbins = h_sig_t->GetSize()-2;
  int bkg_t_nbins = h_bkg_t->GetSize()-2;
  double Ssig_t = h_sig_t->Integral(0,sig_t_nbins+1);
  double Sbkg_t = h_bkg_t->Integral(0,bkg_t_nbins+1);
  double sig_t_integral[sig_t_nbins];
  double bkg_t_integral[bkg_t_nbins];
  double sig_t_eff[sig_t_nbins];
  double bkg_t_eff[bkg_t_nbins];
  double x_t[sig_t_nbins]; //double xmin = -18.; double xmax = -2.;
  increment = (xmax-xmin)/sig_t_nbins;
  for(int i=0;i<sig_t_nbins;i++){
    sig_t_integral[i]=h_sig_t->Integral(i+1,sig_t_nbins+1);
    bkg_t_integral[i]=h_bkg_t->Integral(i+1,bkg_t_nbins+1);
    sig_t_eff[i] = sig_t_integral[i]/Ssig_t;
    bkg_t_eff[i] = bkg_t_integral[i]/Sbkg_t;
    x_t[i] = xmin + increment*i;
    //cout<<i+1<<". x = "<<x_t[i]<< ", sig_t =  "<< sig_t_integral[i]/Ssig_t<< ", bkg_t = "<< bkg_t_integral[i]/Sbkg_t << endl;
  }

  TCanvas *c3 = new TCanvas("c3","c3",800, 600);

  TMultiGraph *mg = new TMultiGraph("mg","mg");

  TGraph *gr1 = new TGraph(sig_l_nbins,x_l,sig_l_eff);
  gr1->SetName("gr1");
  gr1->SetTitle("RadionHH");
  gr1->SetMarkerStyle(21);
  gr1->SetMarkerColor(kGreen);
  gr1->SetDrawOption("AP");
  gr1->SetLineColor(kBlue);
  gr1->SetLineWidth(2);
  gr1->SetFillStyle(0);

  TGraph *gr2 = new TGraph(sig_l_nbins,x_l,bkg_l_eff);
  gr2->SetName("gr2");
  gr2->SetTitle("ttjets");
  gr2->SetMarkerStyle(22);
  gr2->SetMarkerColor(kRed+4);
  gr2->SetDrawOption("P");
  gr2->SetLineColor(kRed);
  gr2->SetLineWidth(2);
  gr2->SetFillStyle(0);

  mg->Add( gr1 );
  mg->Add( gr2 );

  mg->Draw("APL");
  mg->GetXaxis()->SetTitle("log(#chi) >");
  mg->SetTitle("after loose matching");
  c3->BuildLegend();

  c3->SaveAs((dir+"/"+"efficiency_loose.eps").c_str());

  TCanvas *c3_m = new TCanvas("c3_m","c3_m",800, 600);

  TMultiGraph *mg_m = new TMultiGraph("mg_m","mg_m");

  TGraph *gr1_m = new TGraph(sig_m_nbins,x_m,sig_m_eff);
  gr1_m->SetName("gr1_m");
  gr1_m->SetTitle("RadionHH");
  gr1_m->SetMarkerStyle(21);
  gr1_m->SetMarkerColor(kGreen);
  gr1_m->SetDrawOption("AP");
  gr1_m->SetLineColor(kBlue);
  gr1_m->SetLineWidth(2);
  gr1_m->SetFillStyle(0);

  TGraph *gr2_m = new TGraph(sig_m_nbins,x_m,bkg_m_eff);
  gr2_m->SetName("gr2_m");
  gr2_m->SetTitle("ttjets");
  gr2_m->SetMarkerStyle(22);
  gr2_m->SetMarkerColor(kRed+4);
  gr2_m->SetDrawOption("P");
  gr2_m->SetLineColor(kRed);
  gr2_m->SetLineWidth(2);
  gr2_m->SetFillStyle(0);

  mg_m->Add( gr1_m );
  mg_m->Add( gr2_m );

  mg_m->Draw("APL");
  mg_m->GetXaxis()->SetTitle("log(#chi) >");
  mg_m->SetTitle("after loose matching");
  c3_m->BuildLegend();

  c3_m->SaveAs((dir+"/"+"efficiency_med.eps").c_str());

  TCanvas *c3_t = new TCanvas("c3_t","c3_t",800, 600);

  TMultiGraph *mg_t = new TMultiGraph("mg_t","mg_t");

  TGraph *gr1_t = new TGraph(sig_t_nbins,x_t,sig_t_eff);
  gr1_t->SetName("gr1_t");
  gr1_t->SetTitle("RadionHH");
  gr1_t->SetMarkerStyle(21);
  gr1_t->SetMarkerColor(kGreen);
  gr1_t->SetDrawOption("AP");
  gr1_t->SetLineColor(kBlue);
  gr1_t->SetLineWidth(2);
  gr1_t->SetFillStyle(0);

  TGraph *gr2_t = new TGraph(sig_t_nbins,x_t,bkg_t_eff);
  gr2_t->SetName("gr2_t");
  gr2_t->SetTitle("ttjets");
  gr2_t->SetMarkerStyle(22);
  gr2_t->SetMarkerColor(kRed+4);
  gr2_t->SetDrawOption("P");
  gr2_t->SetLineColor(kRed);
  gr2_t->SetLineWidth(2);
  gr2_t->SetFillStyle(0);

  mg_t->Add( gr1_t );
  mg_t->Add( gr2_t );

  mg_t->Draw("APL");
  mg_t->GetXaxis()->SetTitle("log(#chi) >");
  mg_t->SetTitle("after loose matching");
  c3_t->BuildLegend();

  c3_t->SaveAs((dir+"/"+"efficiency_tight.eps").c_str());

  TCanvas *c = new TCanvas("c","c",800,600);
  c->cd();

  TMultiGraph *mg_ROC = new TMultiGraph("mg_ROC","mg_ROC");

  double bkg_l_rej[bkg_l_nbins];
  for(int i =0;i<bkg_l_nbins;i++)bkg_l_rej[i]=1-bkg_l_eff[i];

  TGraph *gr3 = new TGraph(sig_l_nbins,sig_l_eff,bkg_l_rej);
  gr3->SetLineColor(kRed);
  gr3->SetLineWidth(2);
  gr3->GetXaxis()->SetTitle("Eff_{sig}");
  gr3->GetYaxis()->SetTitle("1-Eff_{bkg}");
  gr3->GetXaxis()->SetRangeUser(0,1);
  gr3->GetYaxis()->SetRangeUser(0,1);

  double bkg_m_rej[bkg_m_nbins];
  for(int i =0;i<bkg_m_nbins;i++)bkg_m_rej[i]=1-bkg_m_eff[i];

  TGraph *gr3_m = new TGraph(sig_m_nbins,sig_m_eff,bkg_m_rej);
  gr3_m->SetLineColor(kGreen+2);
  gr3_m->SetLineWidth(2);
  gr3_m->GetXaxis()->SetTitle("Eff_{sig}");
  gr3_m->GetYaxis()->SetTitle("1-Eff_{bkg}");
  gr3_m->GetXaxis()->SetRangeUser(0,1);
  gr3_m->GetYaxis()->SetRangeUser(0,1);

  double bkg_t_rej[bkg_t_nbins];
  for(int i =0;i<bkg_t_nbins;i++)bkg_t_rej[i]=1-bkg_t_eff[i];

  TGraph *gr3_t = new TGraph(sig_t_nbins,sig_t_eff,bkg_t_rej);
  gr3_t->SetLineColor(kBlue);
  gr3_t->SetLineWidth(2);
  gr3_t->GetXaxis()->SetTitle("Eff_{sig}");
  gr3_t->GetYaxis()->SetTitle("1-Eff_{bkg}");
  gr3_t->GetXaxis()->SetRangeUser(0,1);
  gr3_t->GetYaxis()->SetRangeUser(0,1);

  mg_ROC->Add(gr3);
  mg_ROC->Add(gr3_m);
  mg_ROC->Add(gr3_t);

  mg_ROC->Draw("APL");
  mg_ROC->GetXaxis()->SetTitle("Eff_{sig}");
  mg_ROC->GetYaxis()->SetTitle("1-Eff_{bkg}");
  mg_ROC->GetXaxis()->SetRangeUser(0,1);
  mg_ROC->GetYaxis()->SetRangeUser(0,1);
  mg_ROC->SetTitle("ROC Curves");
  //c3_ROC->BuildLegend();

  leg = new TLegend(0.7,0.65,0.9,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(gr3,"dR<1.2","L");
  leg->AddEntry(gr3_m,"dR<0.2","L");
  leg->AddEntry(gr3_t,"dR<0.05","L");
  leg->Draw("SAME");

  c->SaveAs((dir+"/"+"ROC.eps").c_str());

}

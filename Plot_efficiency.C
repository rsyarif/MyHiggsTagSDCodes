#include <iostream>
#include <sstream>
#include <string>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TMultiGraph.h>
#include <TLatex.h>
#include <TMarker.h>

using namespace std;

//string dir = "1leadbtagmjcondition";
//string dir = "allChi_noMinFatjetPt_noMjBtagCondition";

TH1D* PartonMatch_1D(std::string dir, TFile* f, std::string fname,  std::string var, std::string cut,  double xbin, double xmin, double xmax, std::string xlabel, std::string postfix, Color_t color = kBlue, int linestyle = 1,bool save = false){

  string var_ = var;
  if(var_=="log(Fj_chi)") var_ = "logChi"; //log(Fj_chi) become log( for some reason???

  TCanvas* cvs = new TCanvas((var_+cut+postfix).c_str(),(var_+cut+postfix).c_str(),800,600);

  TTree *t = (TTree*)f->Get("tree");
  TH1D* h = new TH1D ((var_+cut+postfix).c_str(),(var_+cut+postfix).c_str(),xbin,xmin,xmax);

  t->Draw((var+">>"+var_+cut+postfix).c_str(),cut.c_str());

  //gStyle->SetOptStat("nemrou");

  h->SetLineWidth(2);
  h->SetLineColor(color);
  h->SetLineStyle(linestyle);
  h->GetXaxis()->SetTitle(xlabel.c_str());
  h->GetYaxis()->SetTitle("");
  h->SetTitle("");

  delete t;
  if(save)cvs->SaveAs((dir+"/"+fname+"_"+var_+"_"+cut+".eps").c_str());

  return h;
}

void Plot_efficiency(){
  string dir = "allChi_noMinFatjetPt_noMjBtagCondition";
  string deltaHiggsMass = "HiggsWin10";
  string fsig = "RadionToHH_4b_M-800_TuneZ2star_8TeV-Madgraph_pythia6_R12_r15_minPt0_Nobtagmjcondition_AllChi_"+deltaHiggsMass+"_mc_subjets";
  string fbkg = "ZPrimeToTTJets_M1000GeV_W10GeV_TuneZ2star_8TeV-madgraph-tauola_R12_r15_minPt0_Nobtagmjcondition_AllChi_"+deltaHiggsMass+"_mc_subjets";
  string postfix = "dRmax12_NoGenPtCut_NoFjPtCut_AllChi";
  double xbin = 40; double xmin = -18; double xmax = -2;
  bool save = false;
  string var = "log(Fj_chi)" ; string xlabel = "Log(#chi)";
  string cut = "Fj_chi>0";
  string loose_cut = cut;
  string medium_cut; if(cut==""){medium_cut = "dR_match<0.2";} else {medium_cut = ("dR_match<0.2&&"+cut).c_str();}  ;
  string tight_cut; if(cut==""){tight_cut = "dR_match<0.05";} else {tight_cut = ("dR_match<0.05&&"+cut).c_str();}  ;
  Color_t color1= kBlue;
  Color_t color2 = kRed;

  //if(dir==""){
  //  std::cout<< "Choose Directory!"<< endl;
  //  return;
  //}

  //TFile *f = new TFile((dir+"/"+"PartonMatch_histos.root").c_str());

  TFile *fs = new TFile((dir+"/"+"fMatch_"+fsig+"_"+postfix+".root").c_str());
  TFile *fb = new TFile((dir+"/"+"fMatch_"+fbkg+"_"+postfix+".root").c_str());

  TH1D* h_sig_l = PartonMatch_1D(dir,fs,fsig,var,loose_cut,xbin,xmin,xmax,xlabel,postfix,color1,1,save);
  TH1D* h_bkg_l = PartonMatch_1D(dir,fb,fbkg,var,loose_cut,xbin,xmin,xmax,xlabel,postfix,color2,1,save);

  TH1D* h_sig_m = PartonMatch_1D(dir,fs,fsig,var,medium_cut,xbin,xmin,xmax,xlabel,postfix,color1,1,save);
  TH1D* h_bkg_m = PartonMatch_1D(dir,fb,fbkg,var,medium_cut,xbin,xmin,xmax,xlabel,postfix,color2,1,save);

  TH1D* h_sig_t = PartonMatch_1D(dir,fs,fsig,var,tight_cut,xbin,xmin,xmax,xlabel,postfix,color1,1,save);
  TH1D* h_bkg_t = PartonMatch_1D(dir,fb,fbkg,var,tight_cut,xbin,xmin,xmax,xlabel,postfix,color2,1,save);


  //TH1D *h_sig_l = (TH1D*)f->Get("h_sig_l");
  //TH1D *h_bkg_l = (TH1D*)f->Get("h_bkg_l");

  //TH1D *h_sig_m = (TH1D*)f->Get("h_sig_m");
  //TH1D *h_bkg_m = (TH1D*)f->Get("h_bkg_m");

  //TH1D *h_sig_t = (TH1D*)f->Get("h_sig_t");
  //TH1D *h_bkg_t = (TH1D*)f->Get("h_bkg_t");


  //float Ssig = 4688;
  //float Sbkg = 1337;
  //float Ssig_l = Ssig;
  //float Sbkg_l = Sbkg;
  //float Ssig_m = Ssig;
  //float Sbkg_m = Sbkg;
  //float Ssig_t = Ssig;
  //float Sbkg_t = Sbkg;

  //---------Calculating efficiciencies----------

  int sig_l_nbins = h_sig_l->GetSize()-2;
  int bkg_l_nbins = h_bkg_l->GetSize()-2;
  double Ssig_l = h_sig_l->Integral(0,sig_l_nbins+1);
  double Sbkg_l = h_bkg_l->Integral(0,bkg_l_nbins+1);
  double sig_l_integral[sig_l_nbins];
  double bkg_l_integral[bkg_l_nbins];
  double sig_l_eff[sig_l_nbins];
  double bkg_l_eff[bkg_l_nbins];
  double x_l[sig_l_nbins]; //double xmin = -18.; double xmax = -2.;
  double increment = (xmax-xmin)/sig_l_nbins;
  cout <<"---loose---"<<endl;
  for(int i=0;i<sig_l_nbins;i++){
    sig_l_integral[i]=h_sig_l->Integral(i+1,sig_l_nbins+1);
    bkg_l_integral[i]=h_bkg_l->Integral(i+1,bkg_l_nbins+1);
    sig_l_eff[i] = sig_l_integral[i]/Ssig_l;
    bkg_l_eff[i] = bkg_l_integral[i]/Sbkg_l;
    x_l[i] = xmin + increment*i;
    cout<<i+1<<". x = "<<x_l[i]<< ", sig_l =  "<< sig_l_integral[i]/Ssig_l<< ", bkg_l = "<< bkg_l_integral[i]/Sbkg_l << endl;
  }
  cout << endl;

  int sig_m_nbins = h_sig_m->GetSize()-2;
  int bkg_m_nbins = h_bkg_m->GetSize()-2;
  double Ssig_m = h_sig_m->Integral(0,sig_m_nbins+1);
  double Sbkg_m = h_bkg_m->Integral(0,bkg_m_nbins+1);
  double sig_m_integral[sig_m_nbins];
  double bkg_m_integral[bkg_m_nbins];
  double sig_m_eff[sig_m_nbins];
  double bkg_m_eff[bkg_m_nbins];
  double x_m[sig_m_nbins]; //double xmin = -18.; double xmax = -2.;
  double increment_m = (xmax-xmin)/sig_m_nbins;
  cout << "---medium---"<<endl;
  for(int i=0;i<sig_m_nbins;i++){
    sig_m_integral[i]=h_sig_m->Integral(i+1,sig_m_nbins+1);
    bkg_m_integral[i]=h_bkg_m->Integral(i+1,bkg_m_nbins+1);
    sig_m_eff[i] = sig_m_integral[i]/Ssig_m;
    bkg_m_eff[i] = bkg_m_integral[i]/Sbkg_m;
    x_m[i] = xmin + increment_m*i;
    cout<<i+1<<". x = "<<x_m[i]<< ", sig_m =  "<< sig_m_integral[i]/Ssig_m<< ", bkg_m = "<< bkg_m_integral[i]/Sbkg_m << endl;
  }
  cout << endl;

  int sig_t_nbins = h_sig_t->GetSize()-2;
  int bkg_t_nbins = h_bkg_t->GetSize()-2;
  double Ssig_t = h_sig_t->Integral(0,sig_t_nbins+1);
  double Sbkg_t = h_bkg_t->Integral(0,bkg_t_nbins+1);
  double sig_t_integral[sig_t_nbins];
  double bkg_t_integral[bkg_t_nbins];
  double sig_t_eff[sig_t_nbins];
  double bkg_t_eff[bkg_t_nbins];
  double x_t[sig_t_nbins]; //double xmin = -18.; double xmax = -2.;
  double increment_t = (xmax-xmin)/sig_t_nbins;
  cout<<"---tight---"<<endl;
  for(int i=0;i<sig_t_nbins;i++){
    sig_t_integral[i]=h_sig_t->Integral(i+1,sig_t_nbins+1);
    bkg_t_integral[i]=h_bkg_t->Integral(i+1,bkg_t_nbins+1);
    sig_t_eff[i] = sig_t_integral[i]/Ssig_t;
    bkg_t_eff[i] = bkg_t_integral[i]/Sbkg_t;
    x_t[i] = xmin + increment_t*i;
    cout<<i+1<<". x = "<<x_t[i]<< ", sig_t =  "<< sig_t_integral[i]/Ssig_t<< ", bkg_t = "<< bkg_t_integral[i]/Sbkg_t << endl;
  }
  cout << endl;

  //------------loose-------------------------

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
  mg->GetYaxis()->SetTitle("Efficiency");
  mg->SetTitle("after loose matching");
  c3->BuildLegend(0.7,.75,.9,.9);

  c3->SaveAs((dir+"/"+"efficiency_loose.eps").c_str());

  //----------------medium----------------------

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
  mg_m->GetYaxis()->SetTitle("Efficiency");
  mg_m->SetTitle("after loose matching");
  c3_m->BuildLegend(0.7,.75,.9,.9);

  c3_m->SaveAs((dir+"/"+"efficiency_med.eps").c_str());

  //---------------tight------------------------

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
  mg_t->GetYaxis()->SetTitle("Efficiency");
  mg_t->SetTitle("after loose matching");
  c3_t->BuildLegend(0.7,.75,.9,.9);

  c3_t->SaveAs((dir+"/"+"efficiency_tight.eps").c_str());

  //---------superimpose signal efficiency graph------

  TCanvas *c_sig = new TCanvas("c_sig","c_sig",800,600);
  c_sig->cd();

  TMultiGraph *mg_sig = new TMultiGraph("sig","sig");

  mg_sig->Add(gr1);
  mg_sig->Add(gr1_m);
  mg_sig->Add(gr1_t);

  gr1->SetLineStyle(4);
  gr1_m->SetLineStyle(9);
  gr1->SetMarkerStyle(7);
  gr1_m->SetMarkerStyle(7);
  gr1_t->SetMarkerStyle(7);

  mg_sig->Draw("APL");
  mg_sig->GetXaxis()->SetTitle("log(#chi) >");
  mg_sig->GetYaxis()->SetTitle("Efficiency");
  mg_sig->SetTitle("after loose matching");
  //c_sig->BuildLegend(0.7,.75,.9,.9);

  c_sig->SaveAs((dir+"/"+"efficiency_sig.eps").c_str());

  //---------superimpose bkg efficiency graph------

  TCanvas *c_bkg = new TCanvas("c_bkg","c_bkg",800,600);
  c_bkg->cd();

  TMultiGraph *mg_bkg = new TMultiGraph("bkg","bkg");

  mg_bkg->Add(gr2);
  mg_bkg->Add(gr2_m);
  mg_bkg->Add(gr2_t);

  gr2->SetLineStyle(4);
  gr2_m->SetLineStyle(9);
  gr2->SetMarkerStyle(7);
  gr2_m->SetMarkerStyle(7);
  gr2_t->SetMarkerStyle(7);

  mg_bkg->Draw("APL");
  mg_bkg->GetXaxis()->SetTitle("log(#chi) >");
  mg_bkg->GetYaxis()->SetTitle("Efficiency");
  mg_bkg->SetTitle("after loose matching");
  //c_bkg->BuildLegend(0.7,.75,.9,.9);

  c_bkg->SaveAs((dir+"/"+"efficiency_bkg.eps").c_str());

  //---------superimpose sig&bkg efficiency graph------

  TCanvas *c_sb = new TCanvas("c_sb","c_sb",800,600);
  c_sb->cd();

  TMultiGraph *mg_sb = new TMultiGraph("sb","sb");


  gr1->SetTitle("HH - dR<1.2");
  gr1_m->SetTitle("HH - dR<0.2");
  gr1_t->SetTitle("HH - dR<0.05");
  gr2->SetTitle("tt - dR<1.2");
  gr2_m->SetTitle("tt - dR<0.2");
  gr2_t->SetTitle("tt - dR<0.05");

  mg_sb->Add(gr1);
  mg_sb->Add(gr1_m);
  mg_sb->Add(gr1_t);
  mg_sb->Add(gr2);
  mg_sb->Add(gr2_m);
  mg_sb->Add(gr2_t);

  mg_sb->Draw("APL");
  mg_sb->GetXaxis()->SetTitle("log(#chi) >");
  mg_sb->GetYaxis()->SetTitle("Efficiency");
  mg_sb->SetTitle("after loose matching");
  c_sb->BuildLegend(0.7,.65,.9,.9);

  c_sb->SaveAs((dir+"/"+"efficiency_sb.eps").c_str());

  //------------ROC-------------------------

  TCanvas *c = new TCanvas("c","c",800,600);
  c->cd();

  TMultiGraph *mg_ROC = new TMultiGraph("ROC","ROC");

  double bkg_l_rej[bkg_l_nbins];
  for(int i =0;i<bkg_l_nbins;i++)bkg_l_rej[i]=1-bkg_l_eff[i];

  TGraph *gr3 = new TGraph(sig_l_nbins,sig_l_eff,bkg_l_rej);
  gr3->SetTitle("loose");
  gr3->SetLineColor(kRed);
  gr3->SetLineWidth(2);
  gr3->GetXaxis()->SetTitle("Eff_{sig}");
  gr3->GetYaxis()->SetTitle("1-Eff_{bkg}");
  gr3->GetXaxis()->SetRangeUser(0,1);
  gr3->GetYaxis()->SetRangeUser(0,1);
  gr3->SetFillStyle(0);

  double bkg_m_rej[bkg_m_nbins];
  for(int i =0;i<bkg_m_nbins;i++)bkg_m_rej[i]=1-bkg_m_eff[i];

  TGraph *gr3_m = new TGraph(sig_m_nbins,sig_m_eff,bkg_m_rej);
  gr3_m->SetTitle("medium");
  gr3_m->SetLineColor(kGreen+2);
  gr3_m->SetLineWidth(2);
  gr3_m->GetXaxis()->SetTitle("Eff_{sig}");
  gr3_m->GetYaxis()->SetTitle("1-Eff_{bkg}");
  gr3_m->GetXaxis()->SetRangeUser(0,1);
  gr3_m->GetYaxis()->SetRangeUser(0,1);
  gr3_m->SetFillStyle(0);

  double bkg_t_rej[bkg_t_nbins];
  for(int i =0;i<bkg_t_nbins;i++)bkg_t_rej[i]=1-bkg_t_eff[i];

  TGraph *gr3_t = new TGraph(sig_t_nbins,sig_t_eff,bkg_t_rej);
  gr3_t->SetTitle("tight");
  gr3_t->SetLineColor(kBlue);
  gr3_t->SetLineWidth(2);
  gr3_t->GetXaxis()->SetTitle("Eff_{sig}");
  gr3_t->GetYaxis()->SetTitle("1-Eff_{bkg}");
  gr3_t->GetXaxis()->SetRangeUser(0,1);
  gr3_t->GetYaxis()->SetRangeUser(0,1);
  gr3_t->SetFillStyle(0);

  mg_ROC->Add(gr3);
  mg_ROC->Add(gr3_m);
  mg_ROC->Add(gr3_t);

  mg_ROC->Draw("APL");
  mg_ROC->GetXaxis()->SetTitle("Eff_{sig}");
  mg_ROC->GetYaxis()->SetTitle("1-Eff_{bkg}");
  mg_ROC->GetXaxis()->SetRangeUser(0,1);
  mg_ROC->GetYaxis()->SetRangeUser(0,1);
  mg_ROC->SetTitle("ROC Curves");


  c->BuildLegend(0.2,0.2,0.2+0.2,0.2+0.15);

  //-----putting marker on graph-----

  int pt_i = 18; //(10,17,25)
  double pt = xmin+increment*pt_i;
  ostringstream ostr;
  ostr << pt;
  string pt_s = ostr.str();

  TLatex *latex = new TLatex(gr3->GetX()[pt_i], gr3->GetY()[pt_i],pt_s.c_str());
  gr3->GetListOfFunctions()->Add(latex);
  latex->SetTextSize(0.02);
  TMarker* marker = new TMarker;
  marker->SetMarkerStyle(24);
  marker->SetMarkerSize(0.5);
  marker->DrawMarker(gr3->GetX()[pt_i], gr3->GetY()[pt_i]);
  marker->Draw("SAME");

  TLatex *latex_m = new TLatex(gr3_m->GetX()[pt_i], gr3_m->GetY()[pt_i],pt_s.c_str());
  gr3_m->GetListOfFunctions()->Add(latex_m);
  latex_m->SetTextSize(0.02);
  TMarker* marker_m = new TMarker;
  marker_m->SetMarkerStyle(25);
  marker_m->SetMarkerSize(0.5);
  marker_m->DrawMarker(gr3_m->GetX()[pt_i], gr3_m->GetY()[pt_i]);
  marker_m->Draw("SAME");

  TLatex *latex_t = new TLatex(gr3_t->GetX()[pt_i], gr3_t->GetY()[pt_i],pt_s.c_str());
  gr3_t->GetListOfFunctions()->Add(latex_t);
  latex_t->SetTextSize(0.02);
  TMarker* marker_t = new TMarker;
  marker_t->SetMarkerStyle(26);
  marker_t->SetMarkerSize(0.5);
  marker_t->DrawMarker(gr3_t->GetX()[pt_i], gr3_t->GetY()[pt_i]);
  marker_t->Draw("SAME");

  c->SaveAs((dir+"/"+"ROC.eps").c_str());

}

void Plot_efficiency_dMHigs10_dMHigs20(){
  string dir = "allChi_noMinFatjetPt_noMjBtagCondition";
  string deltaHiggsMass;
  string fsig;  string fsig2;
  string fbkg;  string fbkg2;
  string postfix = "dRmax12_NoGenPtCut_NoFjPtCut_AllChi";
  double xbin = 40; double xmin = -18; double xmax = -2;
  bool save = false;
  string var = "log(Fj_chi)" ; string xlabel = "Log(#chi)";
  string cut = "Fj_chi>0";
  string loose_cut = cut;
  string medium_cut; if(cut==""){medium_cut = "dR_match<0.2";} else {medium_cut = ("dR_match<0.2&&"+cut).c_str();}  ;
  string tight_cut; if(cut==""){tight_cut = "dR_match<0.05";} else {tight_cut = ("dR_match<0.05&&"+cut).c_str();}  ;
  Color_t color1= kBlue;
  Color_t color2 = kRed;

  deltaHiggsMass = "HiggsWin10";
  fsig = "RadionToHH_4b_M-800_TuneZ2star_8TeV-Madgraph_pythia6_R12_r15_minPt0_Nobtagmjcondition_AllChi_"+deltaHiggsMass+"_mc_subjets";
  fbkg = "ZPrimeToTTJets_M1000GeV_W10GeV_TuneZ2star_8TeV-madgraph-tauola_R12_r15_minPt0_Nobtagmjcondition_AllChi_"+deltaHiggsMass+"_mc_subjets";
  TFile *fs = new TFile((dir+"/"+"fMatch_"+fsig+"_"+postfix+".root").c_str());
  TFile *fb = new TFile((dir+"/"+"fMatch_"+fbkg+"_"+postfix+".root").c_str());

  TH1D* h_sig_t = PartonMatch_1D(dir,fs,fsig,var,tight_cut,xbin,xmin,xmax,xlabel,postfix,color1,1,save);
  TH1D* h_bkg_t = PartonMatch_1D(dir,fb,fbkg,var,tight_cut,xbin,xmin,xmax,xlabel,postfix,color2,1,save);

  deltaHiggsMass = "HiggsWin20";
  fsig2 = "RadionToHH_4b_M-800_TuneZ2star_8TeV-Madgraph_pythia6_R12_r15_minPt0_Nobtagmjcondition_AllChi_"+deltaHiggsMass+"_mc_subjets";
  fbkg2 = "ZPrimeToTTJets_M1000GeV_W10GeV_TuneZ2star_8TeV-madgraph-tauola_R12_r15_minPt0_Nobtagmjcondition_AllChi_"+deltaHiggsMass+"_mc_subjets";
  TFile *fs2 = new TFile((dir+"/"+"fMatch_"+fsig2+"_"+postfix+".root").c_str());
  TFile *fb2 = new TFile((dir+"/"+"fMatch_"+fbkg2+"_"+postfix+".root").c_str());

  TH1D* h_sig_t2 = PartonMatch_1D(dir,fs2,fsig2,var,tight_cut,xbin,xmin,xmax,xlabel,postfix,color1,2,save);
  TH1D* h_bkg_t2 = PartonMatch_1D(dir,fb2,fbkg2,var,tight_cut,xbin,xmin,xmax,xlabel,postfix,color2,2,save);


  //---------Calculating efficiciencies----------

  int sig_t_nbins = h_sig_t->GetSize()-2;
  int bkg_t_nbins = h_bkg_t->GetSize()-2;
  double Ssig_t = h_sig_t->Integral(0,sig_t_nbins+1);
  double Sbkg_t = h_bkg_t->Integral(0,bkg_t_nbins+1);
  double sig_t_integral[sig_t_nbins];
  double bkg_t_integral[bkg_t_nbins];
  double sig_t_eff[sig_t_nbins];
  double bkg_t_eff[bkg_t_nbins];
  double x_t[sig_t_nbins]; //double xmin = -18.; double xmax = -2.;
  double increment_t = (xmax-xmin)/sig_t_nbins;
  cout<<"---tight---"<<endl;
  for(int i=0;i<sig_t_nbins;i++){
    sig_t_integral[i]=h_sig_t->Integral(i+1,sig_t_nbins+1);
    bkg_t_integral[i]=h_bkg_t->Integral(i+1,bkg_t_nbins+1);
    sig_t_eff[i] = sig_t_integral[i]/Ssig_t;
    bkg_t_eff[i] = bkg_t_integral[i]/Sbkg_t;
    x_t[i] = xmin + increment_t*i;
    cout<<i+1<<". x = "<<x_t[i]<< ", sig_t =  "<< sig_t_integral[i]/Ssig_t<< ", bkg_t = "<< bkg_t_integral[i]/Sbkg_t << endl;
  }
  cout << endl;

  int sig_t2_nbins = h_sig_t2->GetSize()-2;
  int bkg_t2_nbins = h_bkg_t2->GetSize()-2;
  double Ssig_t2 = h_sig_t2->Integral(0,sig_t2_nbins+1);
  double Sbkg_t2 = h_bkg_t2->Integral(0,bkg_t2_nbins+1);
  double sig_t2_integral[sig_t2_nbins];
  double bkg_t2_integral[bkg_t2_nbins];
  double sig_t2_eff[sig_t2_nbins];
  double bkg_t2_eff[bkg_t2_nbins];
  double x_t2[sig_t2_nbins]; //double xmin = -18.; double xmax = -2.;
  double increment_t2 = (xmax-xmin)/sig_t2_nbins;
  cout<<"---tight--- dMHigs 20"<<endl;
  for(int i=0;i<sig_t2_nbins;i++){
    sig_t2_integral[i]=h_sig_t2->Integral(i+1,sig_t2_nbins+1);
    bkg_t2_integral[i]=h_bkg_t2->Integral(i+1,bkg_t2_nbins+1);
    sig_t2_eff[i] = sig_t2_integral[i]/Ssig_t2;
    bkg_t2_eff[i] = bkg_t2_integral[i]/Sbkg_t2;
    x_t2[i] = xmin + increment_t2*i;
    cout<<i+1<<". x = "<<x_t2[i]<< ", sig_t2 =  "<< sig_t2_integral[i]/Ssig_t2<< ", bkg_t2 = "<< bkg_t2_integral[i]/Sbkg_t2 << endl;
  }
  cout << endl;

  //---------------tight------------------------

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

  TGraph *gr1_t2 = new TGraph(sig_t2_nbins,x_t2,sig_t2_eff);
  gr1_t2->SetName("gr1_t2");
  gr1_t2->SetTitle("RadionHH");
  gr1_t2->SetMarkerStyle(21);
  gr1_t2->SetMarkerColor(kGreen);
  gr1_t2->SetDrawOption("AP");
  gr1_t2->SetLineColor(kBlue);
  gr1_t2->SetLineWidth(2);
  gr1_t2->SetFillStyle(0);

  TGraph *gr2_t2 = new TGraph(sig_t2_nbins,x_t2,bkg_t2_eff);
  gr2_t2->SetName("gr2_t2");
  gr2_t2->SetTitle("ttjets");
  gr2_t2->SetMarkerStyle(22);
  gr2_t2->SetMarkerColor(kRed+4);
  gr2_t2->SetDrawOption("P");
  gr2_t2->SetLineColor(kRed);
  gr2_t2->SetLineWidth(2);
  gr2_t2->SetFillStyle(0);

  mg_t->Add( gr1_t );
  mg_t->Add( gr2_t );
  mg_t->Add( gr1_t2 );
  mg_t->Add( gr2_t2 );

  mg_t->Draw("APL");
  mg_t->GetXaxis()->SetTitle("log(#chi) >");
  mg_t->GetYaxis()->SetTitle("Efficiency");
  mg_t->SetTitle("after loose matching");
  c3_t->BuildLegend(0.7,.75,.9,.9);

  c3_t->SaveAs((dir+"/"+"efficiency_tight_deltaHiggsMass.eps").c_str());

  //---------superimpose signal efficiency graph------

  TCanvas *c_sig = new TCanvas("c_sig","c_sig",800,600);
  c_sig->cd();

  TMultiGraph *mg_sig = new TMultiGraph("sig","sig");

  mg_sig->Add(gr1_t);
  mg_sig->Add(gr1_t2);

  gr1_t->SetMarkerStyle(7);
  gr1_t2->SetMarkerStyle(4);

  mg_sig->Draw("APL");
  mg_sig->GetXaxis()->SetTitle("log(#chi) >");
  mg_sig->GetYaxis()->SetTitle("Efficiency");
  mg_sig->SetTitle("after loose matching");
  //c_sig->BuildLegend(0.7,.75,.9,.9);

  c_sig->SaveAs((dir+"/"+"efficiency_sig_deltaHiggsMass.eps").c_str());

  //---------superimpose bkg efficiency graph------

  TCanvas *c_bkg = new TCanvas("c_bkg","c_bkg",800,600);
  c_bkg->cd();

  TMultiGraph *mg_bkg = new TMultiGraph("bkg","bkg");

  mg_bkg->Add(gr2_t);
  mg_bkg->Add(gr2_t2);

  gr2_t->SetMarkerStyle(7);
  gr2_t2->SetMarkerStyle(4);

  mg_bkg->Draw("APL");
  mg_bkg->GetXaxis()->SetTitle("log(#chi) >");
  mg_bkg->GetYaxis()->SetTitle("Efficiency");
  mg_bkg->SetTitle("after loose matching");
  //c_bkg->BuildLegend(0.7,.75,.9,.9);

  c_bkg->SaveAs((dir+"/"+"efficiency_bkg_deltaHigssMass.eps").c_str());

  //---------superimpose sig&bkg efficiency graph------

  TCanvas *c_sb = new TCanvas("c_sb","c_sb",800,600);
  c_sb->cd();

  TMultiGraph *mg_sb = new TMultiGraph("sb","sb");

  gr1_t->SetTitle("HH - dR<0.05");
  gr2_t->SetTitle("tt - dR<0.05");
  gr1_t2->SetTitle("HH - dR<0.05");
  gr2_t2->SetTitle("tt - dR<0.05");

  mg_sb->Add(gr1_t);
  mg_sb->Add(gr2_t);
  mg_sb->Add(gr1_t2);
  mg_sb->Add(gr2_t2);

  mg_sb->Draw("APL");
  mg_sb->GetXaxis()->SetTitle("log(#chi) >");
  mg_sb->GetYaxis()->SetTitle("Efficiency");
  mg_sb->SetTitle("after loose matching");
  c_sb->BuildLegend(0.7,.65,.9,.9);

  c_sb->SaveAs((dir+"/"+"efficiency_sb_deltaHiggsMass.eps").c_str());

  //------------ROC-------------------------

  TCanvas *c = new TCanvas("c","c",800,600);
  c->cd();

  TMultiGraph *mg_ROC = new TMultiGraph("ROC","ROC");


  double bkg_t_rej[bkg_t_nbins];
  for(int i =0;i<bkg_t_nbins;i++)bkg_t_rej[i]=1-bkg_t_eff[i];

  TGraph *gr3_t = new TGraph(sig_t_nbins,sig_t_eff,bkg_t_rej);
  gr3_t->SetTitle("tight");
  gr3_t->SetLineColor(kBlue);
  gr3_t->SetLineWidth(2);
  gr3_t->GetXaxis()->SetTitle("Eff_{sig}");
  gr3_t->GetYaxis()->SetTitle("1-Eff_{bkg}");
  gr3_t->GetXaxis()->SetRangeUser(0,1);
  gr3_t->GetYaxis()->SetRangeUser(0,1);
  gr3_t->SetFillStyle(0);

  double bkg_t2_rej[bkg_t2_nbins];
  for(int i =0;i<bkg_t2_nbins;i++)bkg_t2_rej[i]=1-bkg_t2_eff[i];

  TGraph *gr3_t2 = new TGraph(sig_t2_nbins,sig_t2_eff,bkg_t2_rej);
  gr3_t2->SetTitle("tight");
  gr3_t2->SetLineColor(kBlue);
  gr3_t2->SetLineWidth(2);
  gr3_t2->GetXaxis()->SetTitle("Eff_{sig}");
  gr3_t2->GetYaxis()->SetTitle("1-Eff_{bkg}");
  gr3_t2->GetXaxis()->SetRangeUser(0,1);
  gr3_t2->GetYaxis()->SetRangeUser(0,1);
  gr3_t2->SetFillStyle(0);

  mg_ROC->Add(gr3_t);
  mg_ROC->Add(gr3_t2);

  mg_ROC->Draw("APL");
  mg_ROC->GetXaxis()->SetTitle("Eff_{sig}");
  mg_ROC->GetYaxis()->SetTitle("1-Eff_{bkg}");
  mg_ROC->GetXaxis()->SetRangeUser(0,1);
  mg_ROC->GetYaxis()->SetRangeUser(0,1);
  mg_ROC->SetTitle("ROC Curves");


  c->BuildLegend(0.2,0.2,0.2+0.2,0.2+0.15);

  //-----putting marker on graph-----

  /*
  int pt_i = 18; //(10,17,25)
  double pt = xmin+increment*pt_i;
  ostringstream ostr;
  ostr << pt;
  string pt_s = ostr.str();

  TLatex *latex_t = new TLatex(gr3_t->GetX()[pt_i], gr3_t->GetY()[pt_i],pt_s.c_str());
  gr3_t->GetListOfFunctions()->Add(latex_t);
  latex_t->SetTextSize(0.02);
  TMarker* marker_t = new TMarker;
  marker_t->SetMarkerStyle(26);
  marker_t->SetMarkerSize(0.5);
  marker_t->DrawMarker(gr3_t->GetX()[pt_i], gr3_t->GetY()[pt_i]);
  marker_t->Draw("SAME");
  */

  c->SaveAs((dir+"/"+"ROC_deltaHiggsMass.eps").c_str());

}

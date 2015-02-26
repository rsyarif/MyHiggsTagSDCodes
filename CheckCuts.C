#include <iostream>
#include <math.h>
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TCanvas.h"

/* Define Cuts */
std::string cut1 = "FatJetInfo.nJet>0&&FatJetInfo.Jet_pt>0";
std::string cut2 = "FatJetInfo.nJet>0&&FatJetInfo.Jet_pt>200";
std::string cut3 = "FatJetInfo.nJet>0&&FatJetInfo.Jet_pt>200&&FatJetInfo.Jet_SD_nBtagMicrojets>1";
std::string cut4 = "FatJetInfo.nJet>0&&FatJetInfo.Jet_pt>200&&FatJetInfo.Jet_SD_nBtagMicrojets>1&&FatJetInfo.Jet_SD_chi>0";

/* Define samples */

std::string Radsig = "RadionHH_M800_R12_r15_correctIVFmatch_mc_subjets";
//std::string TTbkg = "TTJets_R12_r15_correctIVFmatch_mc_subjets";
//std::string QCDbkg = "QCD_Pt-470to600_TuneZ2star_8TeV_pythia6_R12_r15_correctIVFmatch_mc_subjets";

void Graph(std::string & dir, std::string & name, std::string & var){

  TFile *f1 = new TFile((dir + name + ".root").c_str()); //note: include forward slash when writing directory

  TDirectoryFile *df1 = f1->GetDirectory("btaganaSubJets");
  TTree *t1 = (TTree*) df1->Get("ttree");

  const int nCuts = 4;

  int nEvents = t1->Draw(var.c_str(),"");
  int nFj = t1->Draw(var.c_str(),cut1.c_str());
  int nCut2 = t1->Draw(var.c_str(),cut2.c_str());
  int nCut3 = t1->Draw(var.c_str(),cut3.c_str());
  int nCut4 = t1->Draw(var.c_str(),cut4.c_str());

  Double_t rat1 = nCut2*1.0/nFj*1.0 ;
  Double_t rat2 = nCut3*1.0/nFj*1.0 ;
  Double_t rat3 = nCut4*1.0/nFj*1.0 ;

  std::cout << "nEvents                                       = " << nEvents << std::endl;
  std::cout << "nFj					      = " << nFj << std::endl;
  std::cout << "cut2 : nFj + pt>200 			      = " << nCut2 << std::endl;
  std::cout << "cut3 : nFj + pt>200 + nBtagMicrojet>1 	      = " << nCut3 << std::endl;
  std::cout << "cut4 : nFj + pt>200 + nBtagMicrojet>1 + Chi>0 = " << nCut4 << std::endl;
  std::cout<<std::endl;
  std::cout << "cut2/nFj                                      = " << rat1 << std::endl;
  std::cout << "cut3/nFj 				      = " << rat2 << std::endl;
  std::cout << "cut4/nFj 				      = " << rat3 << std::endl;

  TCanvas *canvas = new TCanvas("Cut Flow","Cut Flow",800,600);
  TCanvas *canvas2 = new TCanvas("Cut Flow Ratio","Cut Flow Ratio",800,600);

  TH1F *h1 = new TH1F(name.c_str(),name.c_str(),nCuts,0.5,nCuts+.5);

  TH1F *h2 = new TH1F(name.c_str(),(name).c_str(),nCuts,0.5,nCuts+.5);
  //TH1F *h3 = new TH1F((name3).c_str(),(name3).c_str(),bins,min,max);

  h1->GetXaxis()->SetTitle("Cuts");
  h1->GetYaxis()->SetTitle("Entries");
  h1->GetYaxis()->SetTitleOffset(1.5);
  h1->SetLineWidth(2);
  h1->SetLineColor(kBlue);
  h1->SetMarkerStyle(22);
  h1->SetMarkerColor(kRed);

  h1->SetBinContent(1,nFj);
  h1->SetBinContent(2,nCut2);
  h1->SetBinContent(3,nCut3);
  h1->SetBinContent(4,nCut4);
  h1->SetStats(0);

  char *label[4]={"nFj","+ pt>200","+ nBtagMj>1","+ #chi>0"};
  h1->GetXaxis()->SetBinLabel(1,label[0]);
  h1->GetXaxis()->SetBinLabel(2,label[1]);
  h1->GetXaxis()->SetBinLabel(3,label[2]);
  h1->GetXaxis()->SetBinLabel(4,label[3]);

  h2->GetXaxis()->SetTitle("Ratio");
  h2->GetYaxis()->SetTitle("Entries");
  h2->SetLineWidth(2);
  h2->SetLineColor(kBlue);
  h2->SetMarkerStyle(22);
  h2->SetMarkerColor(kRed);

  h2->SetBinContent(1,nFj/nFj);
  h2->SetBinContent(2,rat1);
  h2->SetBinContent(3,rat2);
  h2->SetBinContent(4,rat3);
  h2->SetStats(0);

  char *label[4]={"#frac{nFj}{nFj}","#frac{+pt>200}{nFj}","#frac{+nBtagMj>1}{nFj}","#frac{+#chi>0}{nFj}"};
  h2->GetXaxis()->SetBinLabel(1,label[0]);
  h2->GetXaxis()->SetBinLabel(2,label[1]);
  h2->GetXaxis()->SetBinLabel(3,label[2]);
  h2->GetXaxis()->SetBinLabel(4,label[3]);

  canvas->cd();
  canvas->SetLeftMargin(0.15);
  canvas->SetGrid();
  h1->Draw("PL");
  canvas2->cd();
  canvas2->SetGrid();
  h2->Draw("PL");

  //canvas->SaveAs(("CutFlow"+name+".eps").c_str());
  //canvas2->SaveAs(("RatioCutFlow"+name+".eps").c_str());

}

void GraphAll(std::string & dir, std::string & name, std::string & name2, std::string & name3, std::string & var){

  TFile *f1 = new TFile((dir + name + ".root").c_str()); //note: include forward slash when writing directory
  TFile *f2 = new TFile((dir + name2 + ".root").c_str()); //note: include forward slash when writing directory
  TFile *f3 = new TFile((dir + name3 + ".root").c_str()); //note: include forward slash when writing directory

  TDirectoryFile *df1 = f1->GetDirectory("btaganaSubJets");
  TTree *t1 = (TTree*) df1->Get("ttree");
  TDirectoryFile *df2 = f2->GetDirectory("btaganaSubJets");
  TTree *t2 = (TTree*) df2->Get("ttree");
  TDirectoryFile *df3 = f3->GetDirectory("btaganaSubJets");
  TTree *t3 = (TTree*) df3->Get("ttree");

  const int nCuts = 4;

  int nEvents = t1->Draw(var.c_str(),"");
  int nFj = t1->Draw(var.c_str(),cut1.c_str());
  int nCut2 = t1->Draw(var.c_str(),cut2.c_str());
  int nCut3 = t1->Draw(var.c_str(),cut3.c_str());
  int nCut4 = t1->Draw(var.c_str(),cut4.c_str());

  int nEvents_2 = t2->Draw(var.c_str(),"");
  int nFj_2 = t2->Draw(var.c_str(),cut1.c_str());
  int nCut2_2 = t2->Draw(var.c_str(),cut2.c_str());
  int nCut3_2 = t2->Draw(var.c_str(),cut3.c_str());
  int nCut4_2 = t2->Draw(var.c_str(),cut4.c_str());

  int nEvents_3 = t3->Draw(var.c_str(),"");
  int nFj_3 = t3->Draw(var.c_str(),cut1.c_str());
  int nCut2_3 = t3->Draw(var.c_str(),cut2.c_str());
  int nCut3_3 = t3->Draw(var.c_str(),cut3.c_str());
  int nCut4_3 = t3->Draw(var.c_str(),cut4.c_str());

  Double_t rat1 = nCut2*1.0/nFj*1.0 ;
  Double_t rat2 = nCut3*1.0/nFj*1.0 ;
  Double_t rat3 = nCut4*1.0/nFj*1.0 ;

  Double_t rat1_2 = nCut2_2*1.0/nFj_2*1.0 ;
  Double_t rat2_2 = nCut3_2*1.0/nFj_2*1.0 ;
  Double_t rat3_2 = nCut4_2*1.0/nFj_2*1.0 ;

  Double_t rat1_3 = nCut2_3*1.0/nFj_3*1.0 ;
  Double_t rat2_3 = nCut3_3*1.0/nFj_3*1.0 ;
  Double_t rat3_3 = nCut4_3*1.0/nFj_3*1.0 ;


  TCanvas *canvas = new TCanvas("Cut Flow","Cut Flow",800,600);
  TCanvas *canvas2 = new TCanvas("Cut Flow Ratio","Cut Flow Ratio",800,600);

  TH1F *h1 = new TH1F(name.c_str(),name.c_str(),nCuts,0.5,nCuts+.5);
  TH1F *h1_2 = new TH1F(name2.c_str(),name3.c_str(),nCuts,0.5,nCuts+.5);
  TH1F *h1_3 = new TH1F(name3.c_str(),name3.c_str(),nCuts,0.5,nCuts+.5);

  TH1F *h2 = new TH1F(name.c_str(),(name).c_str(),nCuts,0.5,nCuts+.5);
  TH1F *h2_2 = new TH1F(name2.c_str(),(name2).c_str(),nCuts,0.5,nCuts+.5);
  TH1F *h2_3 = new TH1F(name3.c_str(),(name3).c_str(),nCuts,0.5,nCuts+.5);

  h1->SetTitle("");
  h1->GetXaxis()->SetTitle("Cuts");
  h1->GetYaxis()->SetTitle("Entries");
  h1->GetYaxis()->SetTitleOffset(1.5);
  h1->SetLineWidth(2);
  h1->SetLineColor(kBlue);
  h1->SetMarkerStyle(22);
  h1->SetMarkerColor(kRed);

  h1->SetBinContent(1,nFj);
  h1->SetBinContent(2,nCut2);
  h1->SetBinContent(3,nCut3);
  h1->SetBinContent(4,nCut4);
  h1->SetStats(0);

  char *label[4]={"nFj","+ pt>200","+ nBtagMj>1","+ #chi>0"};
  h1->GetXaxis()->SetBinLabel(1,label[0]);
  h1->GetXaxis()->SetBinLabel(2,label[1]);
  h1->GetXaxis()->SetBinLabel(3,label[2]);
  h1->GetXaxis()->SetBinLabel(4,label[3]);

  h1_2->SetTitle("");
  h1_2->GetXaxis()->SetTitle("Cuts");
  h1_2->GetYaxis()->SetTitle("Entries");
  h1_2->GetYaxis()->SetTitleOffset(1.5);
  h1_2->SetLineWidth(2);
  h1_2->SetLineColor(kBlue+3);
  h1_2->SetMarkerStyle(22);
  h1_2->SetMarkerColor(kRed+3);

  h1_2->SetBinContent(1,nFj_2);
  h1_2->SetBinContent(2,nCut2_2);
  h1_2->SetBinContent(3,nCut3_2);
  h1_2->SetBinContent(4,nCut4_2);
  h1_2->SetStats(0);

  h1_2->GetXaxis()->SetBinLabel(1,label[0]);
  h1_2->GetXaxis()->SetBinLabel(2,label[1]);
  h1_2->GetXaxis()->SetBinLabel(3,label[2]);
  h1_2->GetXaxis()->SetBinLabel(4,label[3]);

  h1_3->SetTitle("");
  h1_3->GetXaxis()->SetTitle("Cuts");
  h1_3->GetYaxis()->SetTitle("Entries");
  h1_3->GetYaxis()->SetTitleOffset(1.5);
  h1_3->SetLineWidth(2);
  h1_3->SetLineColor(kGreen);
  h1_3->SetMarkerStyle(22);
  h1_3->SetMarkerColor(kRed+2);

  h1_3->SetBinContent(1,nFj_3);
  h1_3->SetBinContent(2,nCut2_3);
  h1_3->SetBinContent(3,nCut3_3);
  h1_3->SetBinContent(4,nCut4_3);
  h1_3->SetStats(0);

  h1_3->GetXaxis()->SetBinLabel(1,label[0]);
  h1_3->GetXaxis()->SetBinLabel(2,label[1]);
  h1_3->GetXaxis()->SetBinLabel(3,label[2]);
  h1_3->GetXaxis()->SetBinLabel(4,label[3]);

  h2->SetTitle("");
  h2->GetXaxis()->SetTitle("Ratio");
  h2->GetYaxis()->SetTitle("Entries");
  h2->SetLineWidth(2);
  h2->SetLineColor(kBlue);
  h2->SetMarkerStyle(22);
  h2->SetMarkerColor(kRed);

  h2->SetBinContent(1,nFj/nFj);
  h2->SetBinContent(2,rat1);
  h2->SetBinContent(3,rat2);
  h2->SetBinContent(4,rat3);
  h2->SetStats(0);

  char *label[4]={"#frac{nFj}{nFj}","#frac{+pt>200}{nFj}","#frac{+nBtagMj>1}{nFj}","#frac{+#chi>0}{nFj}"};
  h2->GetXaxis()->SetBinLabel(1,label[0]);
  h2->GetXaxis()->SetBinLabel(2,label[1]);
  h2->GetXaxis()->SetBinLabel(3,label[2]);
  h2->GetXaxis()->SetBinLabel(4,label[3]);

  h2_2->SetTitle("");
  h2_2->GetXaxis()->SetTitle("Ratio");
  h2_2->GetYaxis()->SetTitle("Entries");
  h2_2->SetLineWidth(2);
  h2_2->SetLineColor(kBlue+3);
  h2_2->SetMarkerStyle(22);
  h2_2->SetMarkerColor(kRed+3);

  h2_2->SetBinContent(1,nFj_2/nFj_2);
  h2_2->SetBinContent(2,rat1_2);
  h2_2->SetBinContent(3,rat2_2);
  h2_2->SetBinContent(4,rat3_2);
  h2_2->SetStats(0);

  h2_2->GetXaxis()->SetBinLabel(1,label[0]);
  h2_2->GetXaxis()->SetBinLabel(2,label[1]);
  h2_2->GetXaxis()->SetBinLabel(3,label[2]);
  h2_2->GetXaxis()->SetBinLabel(4,label[3]);

  h2_3->SetTitle("");
  h2_3->GetXaxis()->SetTitle("Ratio");
  h2_3->GetYaxis()->SetTitle("Entries");
  h2_3->SetLineWidth(2);
  h2_3->SetLineColor(kGreen);
  h2_3->SetMarkerStyle(22);
  h2_3->SetMarkerColor(kRed+2);

  h2_3->SetBinContent(1,nFj_3/nFj_3);
  h2_3->SetBinContent(2,rat1_3);
  h2_3->SetBinContent(3,rat2_3);
  h2_3->SetBinContent(4,rat3_3);
  h2_3->SetStats(0);

  h2_3->GetXaxis()->SetBinLabel(1,label[0]);
  h2_3->GetXaxis()->SetBinLabel(2,label[1]);
  h2_3->GetXaxis()->SetBinLabel(3,label[2]);
  h2_3->GetXaxis()->SetBinLabel(4,label[3]);

  leg = new TLegend(0.65,0.65,0.85,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h1,"Radion M800","LP");
  leg->AddEntry(h1_2,"TTJets","LP");
  leg->AddEntry(h1_3,"QCD p_{T}470-600","LP");

  leg2 = new TLegend(0.65,0.65,0.85,0.85);
  leg2->SetFillStyle(0);
  leg2->SetBorderSize(0);
  leg2->AddEntry(h2,"Radion M800","LP");
  leg2->AddEntry(h2_2,"TTJets","LP");
  leg2->AddEntry(h2_3,"QCD p_{T}470-600","LP");


  canvas->cd();
  canvas->SetLeftMargin(0.15);
  canvas->SetGrid();
  h1_3->Draw("PL");
  h1_2->Draw("PLSAME");
  h1->Draw("PLSAME");
  leg->Draw("SAME");
  canvas2->cd();
  canvas2->SetGrid();
  h2_3->Draw("PL");
  h2_2->Draw("PLSAME");
  h2->Draw("PLSAME");
  leg2->Draw("SAME");

  //canvas->SaveAs("CutFlow_ALLSuperimposed.eps");
  //canvas2->SaveAs("RatioCutFlow_ALLSuperimposed.eps");

}

TH1F*  makeHisto1(std::string & dir, std::string & name, std::string & var){

  TFile *f1 = new TFile((dir + name + ".root").c_str()); //note: include forward slash when writing directory

  TDirectoryFile *df1 = f1->GetDirectory("btaganaSubJets");
  TTree *t1 = (TTree*) df1->Get("ttree");

  const int nCuts = 4;

  int nEvents = t1->Draw(var.c_str(),"");
  int nFj = t1->Draw(var.c_str(),cut1.c_str());
  int nCut2 = t1->Draw(var.c_str(),cut2.c_str());
  int nCut3 = t1->Draw(var.c_str(),cut3.c_str());
  int nCut4 = t1->Draw(var.c_str(),cut4.c_str());

  Double_t rat1 = nCut2*1.0/nFj*1.0 ;
  Double_t rat2 = nCut3*1.0/nFj*1.0 ;
  Double_t rat3 = nCut4*1.0/nFj*1.0 ;

  bool display = 1;
  if(display){
    std::cout << "SAMPLE: "<< name << endl;;
    std::cout << "nEvents                                       = " << nEvents << std::endl;
    std::cout << "nFj					      = " << nFj << std::endl;
    std::cout << "cut2 : nFj + pt>200 			      = " << nCut2 << std::endl;
    std::cout << "cut3 : nFj + pt>200 + nBtagMicrojet>1 	      = " << nCut3 << std::endl;
    std::cout << "cut4 : nFj + pt>200 + nBtagMicrojet>1 + Chi>0 = " << nCut4 << std::endl;
    std::cout<<std::endl;
  }

  TH1F *h1 = new TH1F(name.c_str(),name.c_str(),nCuts,0.5,nCuts+.5);

  h1->GetXaxis()->SetTitle("Cuts");
  h1->GetYaxis()->SetTitle("Entries");
  h1->GetYaxis()->SetTitleOffset(1.5);
  h1->SetLineWidth(2);
  h1->SetLineColor(kBlue);
  h1->SetMarkerStyle(22);
  h1->SetMarkerColor(kRed);

  h1->SetBinContent(1,nFj);
  h1->SetBinContent(2,nCut2);
  h1->SetBinContent(3,nCut3);
  h1->SetBinContent(4,nCut4);
  h1->SetStats(0);

  char *label[4]={"nFj","+ pt>200","+ nBtagMj>1","+ #chi>0"};
  h1->GetXaxis()->SetBinLabel(1,label[0]);
  h1->GetXaxis()->SetBinLabel(2,label[1]);
  h1->GetXaxis()->SetBinLabel(3,label[2]);
  h1->GetXaxis()->SetBinLabel(4,label[3]);

  return h1;

}

TH1F*  makeHisto2(std::string & dir, std::string & name, std::string & var){

  TFile *f1 = new TFile((dir + name + ".root").c_str()); //note: include forward slash when writing directory

  TDirectoryFile *df1 = f1->GetDirectory("btaganaSubJets");
  TTree *t1 = (TTree*) df1->Get("ttree");

  const int nCuts = 4;

  int nEvents = t1->Draw(var.c_str(),"");
  int nFj = t1->Draw(var.c_str(),cut1.c_str());
  int nCut2 = t1->Draw(var.c_str(),cut2.c_str());
  int nCut3 = t1->Draw(var.c_str(),cut3.c_str());
  int nCut4 = t1->Draw(var.c_str(),cut4.c_str());

  Double_t rat1 = nCut2*1.0/nFj*1.0 ;
  Double_t rat2 = nCut3*1.0/nFj*1.0 ;
  Double_t rat3 = nCut4*1.0/nFj*1.0 ;

  bool display = 1;
  if(display){
    std::cout << "SAMPLE: "<< name << endl;;
    std::cout << "cut2/nFj                                      = " << rat1 << std::endl;
    std::cout << "cut3/nFj 				      = " << rat2 << std::endl;
    std::cout << "cut4/nFj 				      = " << rat3 << std::endl;
    std::cout << std::endl;
  }

  TH1F *h2 = new TH1F(name.c_str(),(name).c_str(),nCuts,0.5,nCuts+.5);

  h2->GetXaxis()->SetTitle("Ratio");
  h2->GetYaxis()->SetTitle("Entries");
  h2->SetLineWidth(2);
  h2->SetLineColor(kBlue);
  h2->SetMarkerStyle(22);
  h2->SetMarkerColor(kRed);

  h2->SetBinContent(1,nFj/nFj);
  h2->SetBinContent(2,rat1);
  h2->SetBinContent(3,rat2);
  h2->SetBinContent(4,rat3);
  h2->SetStats(0);

  char *label[4]={"#frac{nFj}{nFj}","#frac{+pt>200}{nFj}","#frac{+nBtagMj>1}{nFj}","#frac{+#chi>0}{nFj}"};
  h2->GetXaxis()->SetBinLabel(1,label[0]);
  h2->GetXaxis()->SetBinLabel(2,label[1]);
  h2->GetXaxis()->SetBinLabel(3,label[2]);
  h2->GetXaxis()->SetBinLabel(4,label[3]);

  return h2;

}

void makeALLhisto1(){

  TCanvas *c = new TCanvas("SD studies","SD studies",800,600);
  c->SetGrid();
  c->SetLeftMargin(0.12);
  TH1F *h = (TH1F*)  makeHisto1("","RadionHH_M800_R12_r15_correctIVFmatch_mc_subjets","FatJetInfo.nJet");
  TH1F *h2 = (TH1F*)  makeHisto1("","TTJets_R12_r15_correctIVFmatch_mc_subjets","FatJetInfo.nJet");
  TH1F *h3 = (TH1F*)  makeHisto1("","QCD_Pt-470to600_TuneZ2star_8TeV_pythia6_R12_r15_correctIVFmatch_mc_subjets","FatJetInfo.nJet");
  h->SetTitle("");
  h->SetLineColor(kBlue);
  h->SetMarkerColor(kRed);
  h3->SetTitle("");
  h2->SetLineColor(kBlue+3);
  h2->SetMarkerColor(kRed+3);
  h3->SetTitle("");
  h3->SetLineColor(kGreen);
  h3->SetMarkerColor(kRed+2);

  h3->Draw("PL");
  h2->Draw("PLSAME");
  h->Draw("PLSAME");

  leg = new TLegend(0.65,0.65,0.85,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h,"Radion M800","LP");
  leg->AddEntry(h2,"TTJets","LP");
  leg->AddEntry(h3,"QCD p_{T}470-600","LP");

  leg->Draw();

  c->SaveAs("CutFlow_ALLSuperimposed.eps");

}

void makeALLhisto2(){

  TCanvas *c = new TCanvas("SD studies - ratio","SD studies - ratio",800,600);
  c->SetGrid();
  c->SetLeftMargin(0.12);
  TH1F *h = (TH1F*)  makeHisto2("","RadionHH_M800_R12_r15_correctIVFmatch_mc_subjets","FatJetInfo.nJet");
  TH1F *h2 = (TH1F*)  makeHisto2("","TTJets_R12_r15_correctIVFmatch_mc_subjets","FatJetInfo.nJet");
  TH1F *h3 = (TH1F*)  makeHisto2("","QCD_Pt-470to600_TuneZ2star_8TeV_pythia6_R12_r15_correctIVFmatch_mc_subjets","FatJetInfo.nJet");
  h->SetTitle("");
  h->SetLineColor(kBlue);
  h->SetMarkerColor(kRed);
  h3->SetTitle("");
  h2->SetLineColor(kBlue+3);
  h2->SetMarkerColor(kRed+3);
  h3->SetTitle("");
  h3->SetLineColor(kGreen);
  h3->SetMarkerColor(kRed+2);

  h3->Draw("PL");
  h2->Draw("PLSAME");
  h->Draw("PLSAME");

  leg = new TLegend(0.65,0.65,0.85,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h,"Radion M800","LP");
  leg->AddEntry(h2,"TTJets","LP");
  leg->AddEntry(h3,"QCD p_{T}470-600","LP");

  leg->Draw();

  c->SaveAs("RatioCutFlow_ALLSuperimposed.eps");

}

void LetThereBeHisto(){

  /*
  std::cout<< std::endl;
  std::cout<<"Radion"<<std::endl;
  Graph("","RadionHH_M800_R12_r15_correctIVFmatch_mc_subjets","FatJetInfo.nJet");
  std::cout<< std::endl;
  std::cout<<"TTjets"<<std::endl;
  Graph("","TTJets_R12_r15_correctIVFmatch_mc_subjets","FatJetInfo.nJet");
  std::cout<< std::endl;
  std::cout<<"QCD"<<std::endl;
  Graph("","QCD_Pt-470to600_TuneZ2star_8TeV_pythia6_R12_r15_correctIVFmatch_mc_subjets","FatJetInfo.nJet");
  std::cout<<std::endl;
  */

  /*
  GraphAll("","RadionHH_M800_R12_r15_correctIVFmatch_mc_subjets",
	   "TTJets_R12_r15_correctIVFmatch_mc_subjets",
 	   "QCD_Pt-470to600_TuneZ2star_8TeV_pythia6_R12_r15_correctIVFmatch_mc_subjets",
	   "FatJetInfo.nJet");
  */

  makeALLhisto1();
  makeALLhisto2();

}

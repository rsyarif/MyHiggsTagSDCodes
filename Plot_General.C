
TH1F* makeHisto(std::string dir, TFile *f, std::string fname, std::string rdir ,std::string var, std::string var_, std::string cut="", double bin, double min, double max, std::string xlabel, std::string ylabel, Color_t color = kBlue, int linestyle = 1, bool save = false, bool statbox = false){

  TDirectoryFile *df = f->GetDirectory(rdir.c_str());
  TTree *tf = df->Get("ttree");

  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  TH1F *h = new TH1F(fname.c_str(),fname.c_str(),bin,min,max);

  tf->Draw((var+">>"+fname).c_str(),cut.c_str());

  gStyle->SetOptStat("nemrou");
  h->SetLineColor(color);
  h->SetLineWidth(2);
  h->SetLineStyle(linestyle);
  h->GetXaxis()->SetTitle(xlabel.c_str());
  h->GetXaxis()->SetTitleOffset(1.2);
  h->GetYaxis()->SetTitle(ylabel.c_str());
  h->GetYaxis()->SetTitleOffset(1.2);
  h->SetTitle("");

  if(save) c1->SaveAs((dir+"/"+fname+"_"+cut+"_"+var_+"_"+".eps").c_str());

  h->SetStats(statbox);

  return h;
}

void Plot_General_1plot(bool save = false, std::string dir, std::string fname,std::string flabel, std::string rdir, std::string var, std::string var_, std::string cut, double bin, double min, double max, std::string xlabel, std::string ylabel){

  TFile *f = new TFile((dir+"/"+fname+".root").c_str());
  Color_t c_h1 = kBlue;
  TH1F *h1 = (TH1F*) makeHisto(dir,f,fname,rdir,var,var_,cut,bin,min,max,xlabel,ylabel,c_h1,1,save,true);
  TCanvas *c = new TCanvas("SD", "SD",800, 600);
  h1->SetStats(1);
  gStyle->SetOptStat("nemrou");
  h1->SetTitle("");
  h1->Draw();
  leg = new TLegend(0.6,0.65,0.8,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h1,flabel.c_str(),"L");
  leg->Draw("SAME");
  gPad->Update();
  if(save) c->SaveAs((dir+"/Plot_"+var_+"_"+cut+"_All.eps").c_str());
}

void Plot_General_sig_bkg(bool save = false, std::string dir, std::string fsig, std::string fbkg, std::string rdir, std::string var, std::string var_, std::string cut, double bin, double min, double max, std::string xlabel, std::string ylabel){

  TFile *fs = new TFile((dir+"/"+fsig+".root").c_str());
  TFile *fb = new TFile((dir+"/"+fbkg+".root").c_str());
  Color_t c_h1 = kBlue;
  Color_t c_h2 = kRed;
  TH1F *h1 = (TH1F*) makeHisto(dir,fs,fsig,rdir,var,var_,cut,bin,min,max,xlabel,ylabel,c_h1,1,save,true);
  TH1F *h2 = (TH1F*) makeHisto(dir,fb,fbkg,rdir,var,var_,cut,bin,min,max,xlabel,ylabel,c_h2,1,save,true);
  TCanvas *c = new TCanvas("SD", "SD",800, 600);
  //TCanvas *c2 = new TCanvas("SD - sig", "SD - sig",800, 600);
  //TCanvas *c3 = new TCanvas("SD - bkg", "SD - bkg",800, 600);

  h1->SetStats(1);
  h2->SetStats(1);

  gStyle->SetOptStat("nemrou");

  //c2->cd();
  //h1->Draw();
  //if(save) c2->SaveAs((dir+"/Plot_"+var_+"_"+dir+"_"+cut+"_sig.eps").c_str());
  //c3->cd();
  //h2->Draw();
  //if(save) c3->SaveAs((dir+"/Plot_"+var_+"_"+dir+"_"+cut+"_bkg.eps").c_str());

  c->cd();
  Double_t norm1 = h1->GetEntries();
  h1->Scale(1/norm1);
  Double_t norm2 = h2->GetEntries();
  h2->Scale(1/norm2);

  h1->SetTitle("");

  if(h1->GetMaximum()>h2->GetMaximum()){
    h1->Draw();
    h2->Draw("SAMES");
  }
  else{
    h2->Draw();
    h1->Draw("SAMES");
  }

  leg = new TLegend(0.6,0.65,0.8,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h1,"RadionHH","L");
  leg->AddEntry(h2,"Z'->ttbar","L");

  leg->Draw("SAME");

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

  gPad->Update();

  if(save) c->SaveAs((dir+"/Plot_"+var_+"_"+dir+"_"+cut+"_All.eps").c_str());

}

void Plot_General_sig_bkg_many(bool save = false, std::string dir, std::string fsig, std::string fbkg1, std::string fbkg2, std::string rdir, std::string var, std::string var_, std::string cut, double bin, double min, double max, std::string xlabel, std::string ylabel){

  TFile *fs = new TFile((dir+"/"+fsig+".root").c_str());
  TFile *fb1 = new TFile((dir+"/"+fbkg1+".root").c_str());
  TFile *fb2 = new TFile((dir+"/"+fbkg2+".root").c_str());
  Color_t c_h1 = kBlue;
  Color_t c_h2 = kRed;
  Color_t c_h3 = kGreen+2;
  Color_t c_h4 = kYellow+2;
  TH1F *h1 = (TH1F*) makeHisto(dir,fs,fsig,rdir,var,var_,cut,bin,min,max,xlabel,ylabel,c_h1,1,save,true);
  TH1F *h2 = (TH1F*) makeHisto(dir,fb1,fbkg1,rdir,var,var_,cut,bin,min,max,xlabel,ylabel,c_h2,1,save,true);

  std::string cutQCDb = "abs(int(FatJetInfo.Jet_flavour))==5&&FatJetInfo.Jet_nbHadrons<2&&"+cut;
  TH1F *h3 = (TH1F*) makeHisto(dir,fb2,fbkg2,rdir,var,var_,cutQCDb,bin,min,max,xlabel,ylabel,c_h3,2,save,true);

  std::string cutQCDgsp = "abs(FatJetInfo.Jet_flavour)==5&&FatJetInfo.Jet_nbHadrons>1&&"+cut;
  TH1F *h4 = (TH1F*) makeHisto(dir,fb2,fbkg2,rdir,var,var_,cutQCDgsp,bin,min,max,xlabel,ylabel,c_h4,2,save,true);

  TCanvas *c1_ = new TCanvas("c1_","c1_",800,600);
  c1_->cd();
  h3->Draw();
  c1_->SaveAs("rootfiles/SingleB_QCD_Pt-470to600_R08_r015_HiggsWin20_FULL_mc_subjets_FatJetInfo.nJet>0&&FatJetInfo.Jet_pt>300&&FatJetInfo.Jet_massGroomed>80&&FatJetInfo.Jet_massGroomed<150&&FatJetInfo.Jet_SD_chi>0_LogChi_.eps");

  TCanvas *c2_ = new TCanvas("c2_","c2_",800,600);
  c2_->cd();
  h4->Draw();
  c2_->SaveAs("rootfiles/GSP_QCD_Pt-470to600_R08_r015_HiggsWin20_FULL_mc_subjets_FatJetInfo.nJet>0&&FatJetInfo.Jet_pt>300&&FatJetInfo.Jet_massGroomed>80&&FatJetInfo.Jet_massGroomed<150&&FatJetInfo.Jet_SD_chi>0_LogChi_.eps");

  TCanvas *c = new TCanvas("SD", "SD",800, 600);

  h1->SetStats(0);
  h2->SetStats(0);
  h3->SetStats(0);
  h4->SetStats(0);

  gStyle->SetOptStat("nemrou");

  h1->SetTitle("RadionHH(800)");
  h2->SetTitle("Z'ttbartt - All Fj");
  h3->SetTitle("QCD single b");
  h4->SetTitle("QCD gsp");

  /*
  int n = 4;
  int top = 2;
  TH1F** h = new TH1F*[n];
  h[0] = (TH1F*) h1;
  h[1] = (TH1F*) h2;
  h[2] = (TH1F*) h3;
  h[3] = (TH1F*) h4;
  TCanvas *c  = SuperimposeHistos(n,h,top);
  */

  //c->BuildLegend();
  c->cd();
  Double_t norm1 = h1->GetEntries();
  h1->Scale(1/norm1);
  Double_t norm2 = h2->GetEntries();
  h2->Scale(1/norm2);
  Double_t norm3 = h3->GetEntries();
  h3->Scale(1/norm3);
  Double_t norm4 = h4->GetEntries();
  h4->Scale(1/norm4);

  h1->SetTitle("");

  // if(h1->GetMaximum()>h2->GetMaximum()&&h1->GetMaximum()>h3->GetMaximum()&&h1->GetMaximum()>h4->GetMaximum()){
  h1->Draw();
  h2->Draw("SAMES");
  h3->Draw("SAMES");
  h4->Draw("SAMES");
    // }
    //else if(h2->GetMaximum()>h2->GetMaximum()&&h2->GetMaximum()>h3->GetMaximum()&&h2->GetMaximum()>h4->GetMaximum(){
    //h2->Draw();
    //h1->Draw("SAMES");
    //h3->Draw("SAMES");
    //h4->Draw("SAMES");
    //}

  leg = new TLegend(0.6,0.65,0.8,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h1,"RadionHH","L");
  leg->AddEntry(h2,"Z'->ttbar","L");
  leg->AddEntry(h3,"QCD single b","L");
  leg->AddEntry(h4,"QCD gsp","L");

  leg->Draw("SAME");

  gPad->Update();

  if(save) c->SaveAs((dir+"/Plot_"+var_+"_"+dir+"_"+cut+"_All.eps").c_str());

}

TCanvas*  SuperimposeHistos(int n, TH1F** h, int top = 0){
  TCanvas* c = new TCanvas("superimpose","superimpose",800,600);
  c->cd();
  h[top]->DrawNormalized();
  for(int i =0;i<n;i++){
    if(i==top)continue;
    h[i]->DrawNormalized("SAMES");
  }
  gPad->Update();

  return c;
}

void Plot_General_many(bool save=false){
  std::string dir = "allChi_noMinFatjetPt_noMjBtagCondition";
  std::string fsig ="RadionToHH_4b_M-800_TuneZ2star_8TeV-Madgraph_pythia6_R12_r15_minPt0_Nobtagmjcondition_AllChi_mc_subjets";
  std::string fbkg ="ZPrimeToTTJets_M1000GeV_W10GeV_TuneZ2star_8TeV-madgraph-tauola_R12_r15_minPt0_Nobtagmjcondition_AllChi_mc_subjets";
  std::string rdir = "btaganaSubJets";
  std::string var = "FatJetInfo.Jet_SD_nBtagMicrojets";
  std::string cut;

  double bin  = 8;  double min = -0.5;  double max = 7.5;
  TFile *fs = new TFile((dir+"/"+fsig+".root").c_str());
  TFile *fb = new TFile((dir+"/"+fbkg+".root").c_str());
  Color_t c_h1 = kBlue;
  Color_t c_h2 = kRed;

  cut = "FatJetInfo.nJet>0";
  TH1F *h1 = (TH1F*) makeHisto(dir,fs,fsig,rdir,var,cut,bin,min,max,c_h1,2,save);
  TH1F *h2 = (TH1F*) makeHisto(dir,fb,fbkg,rdir,var,cut,bin,min,max,c_h2,2,save);

  cut = "FatJetInfo.nJet>0&&FatJetInfo.Jet_SD_chi>0";
  TH1F *h3 = (TH1F*) makeHisto(dir,fs,fsig,rdir,var,cut,bin,min,max,c_h1,1,save);
  TH1F *h4 = (TH1F*) makeHisto(dir,fb,fbkg,rdir,var,cut,bin,min,max,c_h2,1,save);

  h1->SetTitle("RadionHH - All Fj");
  h2->SetTitle("tt - All Fj");
  h3->SetTitle("RadionHH - Fj w/ valid #chi");
  h4->SetTitle("tt - Fj w/ valid #chi");

  int n = 4;
  int top = 3;
  TH1F** h = new TH1F*[n];
  h[0] = (TH1F*) h1;
  h[1] = (TH1F*) h2;
  h[2] = (TH1F*) h3;
  h[3] = (TH1F*) h4;
  TCanvas *c  = SuperimposeHistos(n,h,top);

  c->BuildLegend();
  if(save)c->SaveAs((dir+"/"+var+"_ALL.eps").c_str());
}

void Plot_General_fj_gen(bool save = false,std::string dir, std::string fsig, std::string rdir, std::string rdir_gen, std::string var, std::string var_gen, std::string var_label, std::string cut, std::string cut_gen, double bin, double min, double max, std::string xlabel, std::string ylabel){

  TFile *fs = new TFile((dir+"/"+fsig+".root").c_str());

  Color_t c_h1 = kBlue;
  Color_t c_h2 = kGreen+2;
  int lineStyle_h1 = 1 ;  int lineStyle_h2 = 1 ;

  TH1F *h1 = (TH1F*) makeHisto(dir,fs,fsig,rdir,var,var_label,cut,bin,min,max,xlabel,ylabel,c_h1,lineStyle_h1,save,true);
  TH1F *h2 = (TH1F*) makeHisto(dir,fs,fsig,rdir_gen,var_gen,var_label,cut_gen,bin,min,max,xlabel,ylabel,c_h2,lineStyle_h2,save,true);

  TCanvas *c = new TCanvas("SD", "SD",800, 600);

  gStyle->SetOptStat("nemrou");

  c->cd();

  Double_t norm1 = h1->GetEntries();
  h1->Scale(1/norm1);
  Double_t norm2 = h2->GetEntries();
  h2->Scale(1/norm2);

  h1->SetTitle("");

  if(h1->GetMaximum()>h2->GetMaximum()){
    h1->Draw();
    h2->Draw("SAME");
  }
  else{
    h2->Draw();
    h1->Draw("SAME");
  }

  leg = new TLegend(0.6,0.65,0.8,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h1,"Fatjet","L");
  leg->AddEntry(h2,"Gen Particle","L");

  leg->Draw("SAME");

  TPaveStats *tps1 = (TPaveStats*) h1->FindObject("stats");
  //tps1->SetName("Radion M800");
  tps1->SetTextColor(c_h1);
  double X1 = tps1->GetX1NDC();
  double Y1 = tps1->GetY1NDC();
  double X2 = tps1->GetX2NDC();
  double Y2 = tps1->GetY2NDC();

  TPaveStats *tps2 = (TPaveStats*) h2->FindObject("stats");
  //tps2->SetName("TTJets");
  tps2->SetTextColor(c_h2);
  tps2->SetX1NDC(X1);
  tps2->SetX2NDC(X2);
  tps2->SetY1NDC(Y1-(Y2-Y1));
  tps2->SetY2NDC(Y1);

  gPad->Update();

  if(save) c->SaveAs((dir+"/Plot_Fj_gen_"+var_label+"_"+cut_gen+".eps").c_str());

  if(save)TFile *fout = new TFile((dir+"/PLOTSGeneral_Plot_Fj_gen_"+var_label+"_"+cut_gen+".root").c_str(),"RECREATE");
  if(save)fout->cd();
  if(save)h1->Write("h_fj");
  if(save)h2->Write("h_gen");
  if(save)fout->Close();


}

void Alakazam(){
  string dir ="rootfiles";
  string deltaHiggsMass;
  string fsig;
  string fbkg;
  double dRmax = 0.8;
  double MjCone = 0.15;
  string postfix= "dRmax08_NoGenPtCut_NoFjPtCut_AllChi";

  std::string var; std::string var_; std:string var_gen; std::string var_label;

  std::string rdir = "btaganaSubJets";
  std::string rdir_gen = "btaganaSubJets";
  //std::string cut = "FatJetInfo.nJet>0";
  std::string cut = "FatJetInfo.nJet>0&&FatJetInfo.Jet_pt>300&&FatJetInfo.Jet_massGroomed>80&&FatJetInfo.Jet_massGroomed<150";
  std::string SDcut = "&&FatJetInfo.Jet_SD_chi>0";

  bool save;

  deltaHiggsMass = "HiggsWin10";
  fsig = "Rad_HHto4b_M800_13TeV_AOD_R08_r015_"+deltaHiggsMass+"_mc_subjets";
  fbkg = "ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola_R08_r015_"+deltaHiggsMass+"_mc_subjets";

  var = "log(FatJetInfo.Jet_SD_chi)"; var_ = "LogChi";
  Plot_General_sig_bkg(false, dir, fsig, fbkg, rdir, var, var_, cut+SDcut, 50,-22,-2,"Log(#chi)","");
  var = "FatJetInfo.Jet_pt"; var_ = "pt";
  Plot_General_sig_bkg(false, dir, fsig, fbkg, rdir, var, var_, cut, 50,0,1000,"p_{T}","");

  var = "FatJetInfo.Jet_pt";
  var_gen = "GenPruned_pT";
  var_label = "pt";
  std::string cut_gen = "GenPruned_pdgID==25";
  Plot_General_fj_gen(false, dir, fsig, rdir, rdir_gen, var, var_gen, var_label, cut, cut_gen, 50,0,1000,"p_{T}","");
  std::string cut_gen = "GenPruned_pdgID==6";
  Plot_General_fj_gen(false, dir, fbkg, rdir, rdir_gen, var, var_gen, var_label, cut, cut_gen, 50,0,1000,"p_{T}","");

  //

  deltaHiggsMass = "HiggsWin20";
  fsig = "Rad_HHto4b_M800_13TeV_AOD_R08_r015_"+deltaHiggsMass+"_mc_subjets";
  fbkg = "ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola_R08_r015_"+deltaHiggsMass+"_mc_subjets";
  fbkg2 = "QCD_Pt-470to600_Tune4C_13TeV_pythia8_R08_r015_"+deltaHiggsMass+"_FULL_mc_subjets";

  var = "log(FatJetInfo.Jet_SD_chi)"; var_ = "LogChi";
  Plot_General_sig_bkg(false, dir, fsig, fbkg, rdir, var, var_, cut+SDcut, 50,-22,-2,"Log(#chi)","");
  Plot_General_sig_bkg_many(true, dir, fsig, fbkg,fbkg2, rdir, var, var_, cut+SDcut, 50,-22,-2,"Log(#chi)","");

  var = "FatJetInfo.Jet_pt"; var_ = "pt";
  Plot_General_sig_bkg(false, dir, fsig, fbkg, rdir, var, var_, cut, 50,0,1000,"p_{T}","");

  var = "FatJetInfo.Jet_pt";
  var_gen = "GenPruned_pT";
  var_label = "pt";
  std::string cut_gen = "GenPruned_pdgID==25";
  Plot_General_fj_gen(false, dir, fsig, rdir, rdir_gen, var, var_gen, var_label, cut, cut_gen, 50,0,1000,"p_{T}","");
  std::string cut_gen = "GenPruned_pdgID==6";
  Plot_General_fj_gen(false, dir, fbkg, rdir, rdir_gen, var, var_gen, var_label, cut, cut_gen, 50,0,1000,"p_{T}","");

  var = "FatJetInfo.Jet_SD_Microjet_pt";
  var_ = "Microjet_pT";
  cut = "abs(FatJetInfo.Jet_flavour)!=5&&abs(FatJetInfo.Jet_flavour)!=4&&FatJetInfo.Jet_SD_Microjet_isBtag==1";
  Plot_General_1plot(false, dir, fbkg2,"QCD470-600", rdir, var, var_, cut, 50,0,1000,"Microjet p_{T}","");
  cut = "abs(FatJetInfo.Jet_flavour)!=5&&abs(FatJetInfo.Jet_flavour)!=4";
  Plot_General_1plot(false, dir, fbkg2,"QCD470-600", rdir, var, var_, cut, 50,0,1000,"Microjet p_{T}","");

  //

  deltaHiggsMass = "HiggsWin30";
  fsig = "Rad_HHto4b_M800_13TeV_AOD_R08_r015_"+deltaHiggsMass+"_mc_subjets";
  fbkg = "ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola_R08_r015_"+deltaHiggsMass+"_mc_subjets";

  var = "log(FatJetInfo.Jet_SD_chi)"; var_ = "LogChi";
  Plot_General_sig_bkg(false, dir, fsig, fbkg, rdir, var, var_, cut+SDcut, 50,-22,-2,"Log(#chi)","");
  var = "FatJetInfo.Jet_pt"; var_ = "pt";
  Plot_General_sig_bkg(false, dir, fsig, fbkg, rdir, var, var_, cut, 50,0,1000,"p_{T}","");

  var = "FatJetInfo.Jet_pt";
  var_gen = "GenPruned_pT";
  var_label = "pt";
  std::string cut_gen = "GenPruned_pdgID==25";
  Plot_General_fj_gen(false, dir, fsig, rdir, rdir_gen, var, var_gen, var_label, cut, cut_gen, 50,0,1000,"p_{T}","");
  std::string cut_gen = "GenPruned_pdgID==6";
  Plot_General_fj_gen(false, dir, fbkg, rdir, rdir_gen, var, var_gen, var_label, cut, cut_gen, 50,0,1000,"p_{T}","");

}



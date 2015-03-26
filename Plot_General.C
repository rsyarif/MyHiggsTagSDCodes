
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

  h1->Draw();
  h2->Draw("SAMES");

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

void Plot_General_Fj_gen(bool save = false){
  std::string dir = "allChi_noMinFatjetPt_noMjBtagCondition";
  std::string fsig ="RadionToHH_4b_M-800_TuneZ2star_8TeV-Madgraph_pythia6_R12_r15_minPt0_Nobtagmjcondition_AllChi_mc_subjets";
  std::string fbkg ="ZPrimeToTTJets_M1000GeV_W10GeV_TuneZ2star_8TeV-madgraph-tauola_R12_r15_minPt0_Nobtagmjcondition_AllChi_mc_subjets";

  //std::string dir = "noMinFatjetPt_noMjBtagCondition";
  //std::string fsig = "RadionToHH_4b_M-800_TuneZ2star_8TeV-Madgraph_pythia6_R12_r15_minPt0_Nobtagmjcondition_mc_subjets" ;
  //std::string fbkg = "TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_R12_r15_minPt0_Nobtagmjcondition_mc_subjets" ;

  //std::string dir = "1leadbtagmjcondition";
  //std::string fsig ="RadionToHH_4b_M-800_TuneZ2star_8TeV-Madgraph_pythia6_R12_r15_minPt200_1leadbtagmjcondition_mc_subjets";
  //std::string fbkg ="TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_R12_r15_minPt200_1leadbtagmjcondition_mc_subjets";

  std::string rdir = "btaganaSubJets";
  std::string rdir_gen = "btagana";

  std::string var = "FatJetInfo.Jet_pt";
  std::string var_gen = "GenPruned_pT";

  std::string cut_gen = "GenPruned_pdgID==25";
  //std::string cut_gen = "GenPruned_pdgID==6";
  std::string cut = "FatJetInfo.nJet>0";
  //std::string cut = "FatJetInfo.nJet>0&&FatJetInfo.Jet_SD_chi>0";
  //std::string cut = "FatJetInfo.nJet>0&&FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_SD_isLeadMicrojetBtag>0";
  //std::string cut = "FatJetInfo.nJet>0&&FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_SD_isLeadMicrojetBtag>0&&FatJetInfo.Jet_pt>200";
  //std::string cut = "FatJetInfo.nJet>0&&FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_SD_isLeadMicrojetBtag>0&&FatJetInfo.Jet_pt>200&&FatJetInfo.Jet_SD_nBtagMicrojets>1";

  double bin  = 50;  double min = 0;  double max = 1000;

  TFile *fs = new TFile((dir+"/"+fsig+".root").c_str());

  TH1F *h1 = (TH1F*) makeHisto(dir,fs,fsig,rdir,var,cut,bin,min,max,kBlue,1,save,true);
  TH1F *h2 = (TH1F*) makeHisto(dir,fs,fsig,rdir_gen,var_gen,cut_gen,bin,min,max,kGreen+1,1,save,true);

  Color_t c_h1 = kBlue;
  Color_t c_h2 = kGreen+2;

  TCanvas *c = new TCanvas("SD", "SD",800, 600);

  gStyle->SetOptStat("nemrou");

  c->cd();

  Double_t norm1 = h1->GetEntries();
  h1->Scale(1/norm1);
  Double_t norm2 = h2->GetEntries();
  h2->Scale(1/norm2);

  h1->SetTitle("");

  h2->Draw();
  h1->Draw("SAME");

  leg = new TLegend(0.6,0.65,0.8,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h1,"Reco Fatjet","L");
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

  if(save) c->SaveAs((dir+"/Plot_"+var+"_"+var_gen+"_"+dir+"_Fj_gen_"+cut_gen+"_.eps").c_str());

}

void Alakazam(){

  std::string dir = "allChi_noMinFatjetPt_noMjBtagCondition";
  std::string fsig ="RadionToHH_4b_M-800_TuneZ2star_8TeV-Madgraph_pythia6_R12_r15_minPt0_Nobtagmjcondition_AllChi_HiggsWin20_mc_subjets";
  std::string fbkg ="ZPrimeToTTJets_M1000GeV_W10GeV_TuneZ2star_8TeV-madgraph-tauola_R12_r15_minPt0_Nobtagmjcondition_AllChi_HiggsWin20_mc_subjets";
  std::string rdir = "btaganaSubJets";

  std::string cut = "FatJetInfo.nJet>0";
  //std::string cut = "FatJetInfo.nJet>0&&FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_pt>200";

  std::string var = "log(FatJetInfo.Jet_SD_chi)"; std::string var_ = "LogChi";
  Plot_General_sig_bkg(true, dir, fsig, fbkg, rdir, var, var_, cut, 50,-22,-2,"Log(#chi)","");
  std::string var = "FatJetInfo.Jet_pt"; std::string var_ = "pt";
  Plot_General_sig_bkg(true, dir, fsig, fbkg, rdir, var, var_, cut, 50,0,1000,"p_{T}","");

}



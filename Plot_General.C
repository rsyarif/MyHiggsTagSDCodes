
TH1F* makeHisto(std::string dir, std::string fname, std::string rdir ,std::string var, std::string cut="", double bin, double min, double max){
  bool display = 0;
  TFile *f = new TFile((dir+"/"+fname+".root").c_str());
  TDirectoryFile *df = f->GetDirectory(rdir.c_str());
  TTree *tf = df->Get("ttree");

  TH1F *h = new TH1F(fname.c_str(),fname.c_str(),bin,min,max);

  tf->Draw((var+">>"+fname).c_str(),cut.c_str());

  gStyle->SetOptStat("nemrou");
  h->SetLineColor(kBlue);
  h->SetLineWidth(2);
  h->GetXaxis()->SetTitle(var.c_str());
  h->GetXaxis()->SetTitleOffset(1.2);
  h->GetYaxis()->SetTitle("Entries");
  h->GetYaxis()->SetTitleOffset(1.2);
  h->SetTitle("");

  return h;
}

void Plot_General_sig_bkg(bool save = false){
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

  //std::string var = "log(FatJetInfo.Jet_SD_chi)";
  std::string var = "FatJetInfo.Jet_pt";

  //std::string cut = "FatJetInfo.nJet>0";
  //std::string cut = "FatJetInfo.nJet>0&&FatJetInfo.Jet_pt>200";
  std::string cut = "FatJetInfo.nJet>0&&FatJetInfo.Jet_SD_chi>0";
  //std::string cut = "FatJetInfo.nJet>0&&FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_pt>200";
  //std::string cut = "FatJetInfo.nJet>0&&FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_pt>200&&FatJetInfo.Jet_SD_nBtagMicrojets>1";
  //std::string cut = "FatJetInfo.nJet>0&&FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_SD_isLeadMicrojetBtag>0&&FatJetInfo.Jet_pt>200&&FatJetInfo.Jet_SD_nBtagMicrojets>1";

  double bin  = 50;  double min = 0;  double max = 1000;
  //double bin  = 50;  double min = -18;  double max = -2;

  TH1F *h1 = (TH1F*) makeHisto(dir.c_str(),fsig.c_str(),rdir.c_str(),var.c_str(),cut.c_str(),bin,min,max);
  TH1F *h2 = (TH1F*) makeHisto(dir.c_str(),fbkg.c_str(),rdir.c_str(),var.c_str(),cut.c_str(),bin,min,max);

  Color_t c_h1 = kBlue;
  Color_t c_h2 = kRed;

  TCanvas *c = new TCanvas("SD", "SD",800, 600);
  TCanvas *c2 = new TCanvas("SD - sig", "SD - sig",800, 600);
  TCanvas *c3 = new TCanvas("SD - bkg", "SD - bkg",800, 600);

  gStyle->SetOptStat("nemrou");

  h1->SetStats(1);
  h2->SetStats(1);

  c2->cd();
  h1->SetLineColor(c_h1);
  h1->Draw();
  if(save) c2->SaveAs((dir+"/Plot_"+var+"_"+dir+"_sig.eps").c_str());
  //if(save) c2->SaveAs((dir+"/Plot_LogChi_"+dir+"_sig.eps").c_str());

  c3->cd();
  h2->SetLineColor(c_h2);
  h2->SetLineStyle(2);
  h2->Draw();
  if(save) c3->SaveAs((dir+"/Plot_"+var+"_"+dir+"_bkg.eps").c_str());
  //if(save) c3->SaveAs((dir+"/Plot_LogChi_"+dir+"_bkg.eps").c_str());

  //c->SetGrid();
  c->cd();

  //h1->SetStats(0);
  //h2->SetStats(0);

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

  if(save) c->SaveAs((dir+"/Plot_"+var+"_"+dir+"_All.eps").c_str());
  //if(save) c->SaveAs((dir+"/Plot_LogChi_"+dir+"_All.eps").c_str());
  //c->SetLogy();
  //if(save)c->SaveAs((dir+"/Plot_"+var+"_"+dir+"_logyscale.eps").c_str());

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

  TH1F *h1 = (TH1F*) makeHisto(dir.c_str(),fsig.c_str(),rdir.c_str(),var.c_str(),cut.c_str(),bin,min,max);
  TH1F *h2 = (TH1F*) makeHisto(dir.c_str(),fsig.c_str(),rdir_gen.c_str(),var_gen.c_str(),cut_gen.c_str(),bin,min,max);

  Color_t c_h1 = kBlue;
  Color_t c_h2 = kGreen+2;

  TCanvas *c = new TCanvas("SD", "SD",800, 600);
  TCanvas *c2 = new TCanvas("SD - sig", "SD - sig",800, 600);
  TCanvas *c3 = new TCanvas("SD - bkg", "SD - bkg",800, 600);

  gStyle->SetOptStat("nemrou");

  h1->SetStats(1);
  h2->SetStats(1);

  c2->cd();
  h1->SetLineColor(c_h1);
  h1->Draw();
  if(save) c2->SaveAs((dir+"/Plot_"+var+"_"+dir+"_sig_noFjPtCut.eps").c_str());

  c3->cd();
  h2->SetLineColor(c_h2);
  h2->SetLineStyle(2);
  h2->Draw();
  if(save) c3->SaveAs((dir+"/Plot_"+var_gen+"_"+dir+"_sig_"+cut_gen+"_.eps").c_str());

  //c->SetGrid();
  c->cd();

  Double_t norm1 = h1->GetEntries();
  h1->Scale(1/norm1);
  Double_t norm2 = h2->GetEntries();
  h2->Scale(1/norm2);

  //h1->SetStats(0);
  //h2->SetStats(0);

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



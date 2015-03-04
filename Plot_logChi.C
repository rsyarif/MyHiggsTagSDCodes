
TH1F* makeHisto(std::string dir, std::string fname, std::string var, std::string cut, double bin, double min, double max){
  bool display = 0;
  TFile *f = new TFile((dir+"/"+fname+".root").c_str());
  TDirectoryFile *df = f->GetDirectory("btaganaSubJets");
  TTree *tf = df->Get("ttree");

  TH1F *h = new TH1F(fname.c_str(),fname.c_str(),bin,min,max);

  tf->Draw((var+">>"+fname).c_str(),cut.c_str());

  gStyle->SetOptStat("nemrou");
  h->SetLineColor(kBlue);
  h->SetLineWidth(2);
  h->GetXaxis()->SetTitle("log(#chi)");
  h->GetXaxis()->SetTitleOffset(1.2);
  h->GetYaxis()->SetTitle("Entries");
  h->GetYaxis()->SetTitleOffset(1.2);
  h->SetTitle("");

  return h;
}

void Plot_logChi_old(){

  TH1F *h = (TH1F*) makeHisto("RadionToHH_4b_M-800_TuneZ2star_8TeV-Madgraph_pythia6_mc_subjets.root");
  TH1F *h2 = (TH1F*) makeHisto("TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_mc_subjets.root");
  TH1F *h3 = (TH1F*) makeHisto("QCD_Pt-300to600_TuneZ2star_8TeV_pythia6_mc_subjets.root");

  TCanvas *c = new TCanvas("SD - log chi", "SD - log chi",800, 600);
  //c->SetGrid();

  Double_t norm1 = h->GetEntries();
  h->Scale(1/norm1);
  Double_t norm2 = h2->GetEntries();
  h2->Scale(1/norm2);
  Double_t norm3 = h3->GetEntries();
  h3->Scale(1/norm3);

  gStyle->SetOptStat(0);

  h->SetTitle("");
  h->SetLineColor(kBlue);
  h->Draw();

  h2->SetLineColor(kRed);
  h2->Draw("SAME");

  h3->SetLineColor(kGreen+3);
  h3->SetLineStyle(2);
  h3->Draw("SAME");

  leg = new TLegend(0.65,0.65,0.85,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h,"Radion M800","L");
  leg->AddEntry(h2,"TTJets","L");
  leg->AddEntry(h3,"QCD p_{T}300-600","L");

  leg->Draw("SAME");

  c->SaveAs("Plot_logChi_All.eps");
  c->SetLogy();
  c->SaveAs("Plot_logChi_All_logyscale.eps");

}

void Plot_logChi_1leadbtagcondition(){
  std::string fsig = "RadionToHH_4b_M-800_TuneZ2star_8TeV-Madgraph_pythia6_R12_r15_minPt200_1leadbtagmjcondition_mc_subjets" ;
  std::string fbkg = "TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_R12_r15_minPt200_1leadbtagmjcondition_mc_subjets" ;
  std::string dir = "1leadbtagmjcondition";
  std::string cut = "FatJetInfo.nJet>0&&FatJetInfo.Jet_SD_chi>0";
  std::string var = "log(FatJetInfo.Jet_SD_chi)";

  TH1F *h = (TH1F*) makeHisto(dir.c_str(),fsig.c_str(),var.c_str(),cut.c_str(),50,-18,2);
  TH1F *h2 = (TH1F*) makeHisto(dir.c_str(),fbkg.c_str(),var.c_str(),cut.c_str(),50,-18,2);

  TCanvas *c = new TCanvas("SD - log chi", "SD - log chi",800, 600);
  TCanvas *c2 = new TCanvas("SD - log chi - sig", "SD - log chi - sig",800, 600);
  TCanvas *c3 = new TCanvas("SD - log chi - bkg", "SD - log chi - bkg",800, 600);

  gStyle->SetOptStat("nemrou");

  h->SetStats(1);
  h2->SetStats(1);

  c2->cd();
  h->SetLineColor(kBlue);
  h->Draw();
  c2->SaveAs((dir+"/Plot_logChi_1leadbtagmjcondition_sig.eps").c_str());


  c3->cd();
  h2->SetLineColor(kRed);
  h2->Draw();
  c3->SaveAs((dir+"/Plot_logChi_1leadbtagmjcondition_bkg.eps").c_str());

  c->SetGrid();
  c->cd();

  Double_t norm1 = h->GetEntries();
  h->Scale(1/norm1);
  Double_t norm2 = h2->GetEntries();
  h2->Scale(1/norm2);

  h->SetStats(0);
  h2->SetStats(0);

  h->SetTitle("");

  h->Draw();
  h2->Draw("SAME");

  leg = new TLegend(0.65,0.65,0.85,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h,"Radion M800","L");
  leg->AddEntry(h2,"TTJets","L");

  leg->Draw("SAME");

  c->SaveAs((dir+"Plot_logChi_1leadbtagmjcondition_All.eps").c_str());
  c->SetLogy();
  c->SaveAs((dir+"/Plot_logChi_1leadbtagmjcondition_All_logyscale.eps").c_str());

}

void Plot_logChi_noMinFatjetPt_noMjBtagCondition(){
  std::string fsig = "RadionToHH_4b_M-800_TuneZ2star_8TeV-Madgraph_pythia6_R12_r15_minPt0_Nobtagmjcondition_mc_subjets" ;
  std::string fbkg = "TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_R12_r15_minPt0_Nobtagmjcondition_mc_subjets" ;
  std::string dir = "noMinFatjetPt_noMjBtagCondition";
  //std::string cut = "FatJetInfo.nJet>0&&FatJetInfo.Jet_SD_chi>0";
  //std::string cut = "FatJetInfo.nJet>0&&FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_SD_isLeadMicrojetBtag>0";
  //std::string cut = "FatJetInfo.nJet>0&&FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_SD_isLeadMicrojetBtag>0&&FatJetInfo.Jet_pt>200";
  std::string cut = "FatJetInfo.nJet>0&&FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_SD_isLeadMicrojetBtag>0&&FatJetInfo.Jet_pt>200&&FatJetInfo.Jet_SD_nBtagMicrojets>1";
  std::string var = "log(FatJetInfo.Jet_SD_chi)";

  TH1F *h = (TH1F*) makeHisto(dir.c_str(),fsig.c_str(),var.c_str(),cut.c_str(),50,-18,-2);
  TH1F *h2 = (TH1F*) makeHisto(dir.c_str(),fbkg.c_str(),var.c_str(),cut.c_str(),50,-18,-2);

  TCanvas *c = new TCanvas("SD - log chi", "SD - log chi",800, 600);
  TCanvas *c2 = new TCanvas("SD - log chi - sig", "SD - log chi - sig",800, 600);
  TCanvas *c3 = new TCanvas("SD - log chi - bkg", "SD - log chi - bkg",800, 600);

  gStyle->SetOptStat("nemrou");

  h->SetStats(1);
  h2->SetStats(1);

  c2->cd();
  h->SetLineColor(kBlue);
  h->Draw();
  c2->SaveAs((dir+"/Plot_logChi_noMinFatjetPt_noMjBtagCondition_sig.eps").c_str());


  c3->cd();
  h2->SetLineColor(kRed);
  h2->Draw();
  c3->SaveAs((dir+"/Plot_logChi_noMinFatjetPt_noMjBtagCondition_bkg.eps").c_str());

  //c->SetGrid();
  c->cd();

  Double_t norm1 = h->GetEntries();
  h->Scale(1/norm1);
  Double_t norm2 = h2->GetEntries();
  h2->Scale(1/norm2);

  h->SetStats(0);
  h2->SetStats(0);

  h->SetTitle("");

  h->Draw();
  h2->Draw("SAME");

  leg = new TLegend(0.65,0.65,0.85,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h,"Radion M800","L");
  leg->AddEntry(h2,"TTJets","L");

  leg->Draw("SAME");

  c->SaveAs((dir+"/Plot_logChi_noMinFatjetPt_noMjBtagCondition_All.eps").c_str());
  c->SetLogy();
  c->SaveAs((dir+"/Plot_logChi_noMinFatjetPt_noMjBtagCondition_All_logyscale.eps").c_str());

}



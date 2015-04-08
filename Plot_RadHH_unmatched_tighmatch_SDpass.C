{
  TFile *f = new TFile("rootfiles/PLOTSGeneral_Plot_Fj_gen_pt_GenPruned_pdgID==25.root");
  TH1D* h1 = f->Get("h_fj");
  TFile *f2 = new TFile("rootfiles/PLOTS_fj_gen_2plots_tight_match_Rad_HHto4b_M800_13TeV_AOD_R08_r015_HiggsWin20_mc_subjets_Fj_pt_.root");
  TH1D* h2 = f2->Get("h_fj_t");
  TFile *f3 = new TFile("rootfiles/PLOTS_fj_gen_2plots_tight_match_Rad_HHto4b_M800_13TeV_AOD_R08_r015_HiggsWin20_mc_subjets_Fj_pt_Fj_chi>0.root");
  TH1D* h3 = f3->Get("h_fj_t");

  h1->SetLineColor(kGreen+2);
  h2->SetLineColor(kBlue);
  h3->SetLineColor(kBlack);

  h3->Draw();
  h2->Draw("SAMES");
  h1->Draw("SAMES");

  TPaveStats *tps1 = (TPaveStats*) h1->FindObject("stats");
  tps1->SetTextColor(kGreen+2);
  double X1 = tps1->GetX1NDC();
  double Y1 = tps1->GetY1NDC();
  double X2 = tps1->GetX2NDC();
  double Y2 = tps1->GetY2NDC();

  TPaveStats *tps2 = (TPaveStats*) h2->FindObject("stats");
  tps2->SetTextColor(kBlue);
  tps2->SetX1NDC(X1);
  tps2->SetX2NDC(X2);
  tps2->SetY1NDC(Y1-(Y2-Y1));
  tps2->SetY2NDC(Y1);

  X1 = tps2->GetX1NDC();
  Y1 = tps2->GetY1NDC();
  X2 = tps2->GetX2NDC();
  Y2 = tps2->GetY2NDC();

  TPaveStats *tps3 = (TPaveStats*) h3->FindObject("stats");
  tps3->SetTextColor(kBlack);
  tps3->SetX1NDC(X1);
  tps3->SetX2NDC(X2);
  tps3->SetY1NDC(Y1-(Y2-Y1));
  tps3->SetY2NDC(Y1);

  leg = new TLegend(0.45,0.6,0.775,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h1,"Unmatched","L");
  leg->AddEntry(h2,"Matched to genHiggs (#DeltaR<0.05)","L");
  leg->AddEntry(h3,"Matched to genHiggs (#DeltaR<0.05), pass SD","L");
  leg->Draw("SAME");

  gPad->Update();

  c1->SaveAs("rootfiles/Rad_unmatched_tightmatch_SDpass.eps");

}

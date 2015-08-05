{
  
  
  TFile *f = new TFile("plots/PLOTSGeneral_Plot_Fj_gen_pt_GenPruned_pdgID==25.root");
  TH1D* h1 = (TH1D*)f->Get("h_fj");
  TFile *f2 = new TFile("plots/PLOTS_fj_gen_2plots_tight_match_Rad_HHto4b_HW20_Fj_pt_.root");
  TH1D* h2 = (TH1D*)f2->Get("h_fj_t");
  TFile *f3 = new TFile("plots/PLOTS_fj_gen_2plots_tight_match_Rad_HHto4b_HW20_Fj_pt_Fj_chi>0.root");
  TH1D* h3 = (TH1D*)f3->Get("h_fj_t");

TCanvas *c1 = new TCanvas("c1","c1",800,600);

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

  leg = new TLegend(0.425,0.6,0.65,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->AddEntry(h1,"Unmatched","L");
  leg->AddEntry(h2,"#DeltaR (Fj, gen H) < 0.05","L");
  leg->AddEntry(h3,"#DeltaR (Fj, gen H) < 0.05), pass SD","L");
  leg->Draw("SAME");

  gPad->Update();

  c1->SaveAs("plots/Rad_unmatched_tightmatch_SDpass.pdf");

}

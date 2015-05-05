{

  TFile *f = new TFile("rootfiles/fPartonMatch_useBhadron_Rad_HHto4b_M800_13TeV_AOD_R08_r015_HiggsWin30_tagr07_fake01bHadron_NoBtagOnLowPtMj_MjIVF004_mc_subjets.root");
  TTree*t = (TTree*) f->Get("tree");

  TCanvas *c1 = new TCanvas();

  TH1D *h1 = new TH1D("h1","h1",45,0,0.15);
  TH1D *h2 = new TH1D("h2","h2",45,0,0.15);
  TH1D *h3 = new TH1D("h3","h3",40,0,0.04);
  TH1D *h4 = new TH1D("h4","h4",40,0,0.04);

  gStyle->SetOptStat("nemrou");

  t->Draw("Mj_dR>>h1","Mj_dR>0");

  // c1->SaveAs("rootfiles/Rad_HHto4b_M800_useBhadron_Mj_dR_Mj_dR>0.eps");

  t->Draw("Mj_dR>>h3","Mj_dR>0&&Mj_dR<0.04");

  // c1->SaveAs("rootfiles/Rad_HHto4b_M800_useBhadron_Mj_dR_Mj_dR>0&&Mj_dR<0.04.eps");

  // t->Draw("Mj_dR","Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==1");

  // c1->SaveAs("rootfiles/Rad_HHto4b_M800_useBhadron_Mj_dR_Mj_dR>0&&Mj_dR<0.04.eps&&Mj_isBtag==1.eps");

  // //

  // t->Draw("Mj_pt","Mj_dR>0");

  // c1->SaveAs("rootfiles/Rad_HHto4b_M800_useBhadron_Mj_pt_Mj_dR>0.eps");

  // t->Draw("Mj_pt","Mj_dR>0&&Mj_dR<0.04");

  // c1->SaveAs("rootfiles/Rad_HHto4b_M800_useBhadron_Mj_pt_Mj_dR>0&&Mj_dR<0.04.eps");

  // t->Draw("Mj_pt","Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==1");

  // c1->SaveAs("rootfiles/Rad_HHto4b_M800_useBhadron_Mj_pt_Mj_dR>0&&Mj_dR<0.04.eps&&Mj_isBtag==1.eps");

  // //

  // t->Draw("Mj_gen_matched_pdgID","Mj_dR>0");

  // c1->SaveAs("rootfiles/Rad_HHto4b_M800_useBhadron_Mj_gen_matched_pdgID_Mj_dR>0.eps");

  // t->Draw("Mj_gen_matched_pdgID","Mj_dR>0&&Mj_dR<0.04");

  // c1->SaveAs("rootfiles/Rad_HHto4b_M800_useBhadron_Mj_gen_matched_pdgID_Mj_dR>0&&Mj_dR<0.04.eps");

  // t->Draw("Mj_gen_matched_pdgID","Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==1");

  // c1->SaveAs("rootfiles/Rad_HHto4b_M800_useBhadron_Mj_gen_matched_pdgID_Mj_dR>0&&Mj_dR<0.04.eps&&Mj_isBtag==1.eps");

  // //

  t->Draw("Mj_dR_SV>>h2","Mj_dR_SV>0&&Mj_dR_SV<0.15");

  c1->SaveAs("rootfiles/Rad_HHto4b_M800_useBhadron_Mj_dR_SV_Mj_dR_SV>0.eps");

  t->Draw("Mj_dR_SV>>h4","Mj_dR_SV>0&&Mj_dR_SV<0.04");

  c1->SaveAs("rootfiles/Rad_HHto4b_M800_useBhadron_Mj_dR_SV_Mj_dR_SV>0&&Mj_dR_SV<0.04.eps");

  t->Draw("Mj_dR_SV","Mj_dR_SV>0&&Mj_dR_SV<0.04&&Mj_isBtag==1");

  c1->SaveAs("rootfiles/Rad_HHto4b_M800_useBhadron_Mj_dR_SV_Mj_dR_SV>0&&Mj_dR_SV<0.04.eps&&Mj_isBtag==1.eps");

  //

  h1->SetStats(0);
  h2->SetStats(0);
  h3->SetStats(0);
  h4->SetStats(0);

  h1->GetXaxis()->SetTitle("#DeltaR");
  h2->GetXaxis()->SetTitle("#DeltaR");
  h3->GetXaxis()->SetTitle("#DeltaR");
  h4->GetXaxis()->SetTitle("#DeltaR");

  h1->SetLineColor(kGreen+2);
  h2->SetLineColor(kBlue);

  h1->Scale(1/h1->GetEntries());
  h2->Scale(1/h2->GetEntries());
  h1->Draw();
  h2->Draw("same");

  TLegend * l = new TLegend(0.75,0.65,0.95,0.8);
  l->AddEntry(h1,"Mj-bHadron");
  l->AddEntry(h2,"Mj-IVF");
  l->Draw("same");

  c1->SaveAs("rootfiles/Rad_HHto4b_M800_useBhadron_Mj_dR_SV_Mj_dR_superimpose.eps");

  h3->SetLineColor(kGreen+2);
  h4->SetLineColor(kBlue);

  h3->Scale(1/h3->GetEntries());
  h4->Scale(1/h4->GetEntries());
  h3->Draw();
  h4->Draw("same");

  TLegend * l2 = new TLegend(0.75,0.65,0.95,0.8);
  l2->AddEntry(h3,"Mj-bHadron");
  l2->AddEntry(h4,"Mj-IVF");
  l2->Draw("same");

  c1->SaveAs("rootfiles/Rad_HHto4b_M800_useBhadron_Mj_dR_SV_Mj_dR_<0.04_superimpose.eps");

}

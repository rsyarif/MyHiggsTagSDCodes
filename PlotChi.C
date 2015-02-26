{
  TCanvas *c = new TCanvas("c","c",1600,400);
  c->Divide(3,1);

  TFile *f1 = new TFile("RadionHH_M800_R12_r15_correctIVFmatch_mc_subjets.root");
  TDirectoryFile *df1 = f1->GetDirectory("btaganaSubJets");
  TTree *t1 = (TTree*) df1->Get("ttree");

  TFile *f2 = new TFile("TTJets_R12_r15_correctIVFmatch_mc_subjets.root");
  TDirectoryFile *df2 = f2->GetDirectory("btaganaSubJets");
  TTree *t2 = (TTree*) df2->Get("ttree");

  TFile *f3 = new TFile("QCD_Pt-470to600_TuneZ2star_8TeV_pythia6_R12_r15_correctIVFmatch_mc_subjets.root");
  TDirectoryFile *df3 = f3->GetDirectory("btaganaSubJets");
  TTree *t3 = (TTree*) df3->Get("ttree");


  TH1F *h1 = new TH1F("Radion","Radion M800",50,0,1e-3);
  TH1F *h2 = new TH1F("TTJets","TTJets",50,0,1e-3);
  TH1F *h3 = new TH1F("QCD","QCD p_{T} 470to600",50,0,1e-3);


  h1->SetLineColor(kBlue);
  h1->SetLineWidth(2);
  h1->GetXaxis()->SetTitle("#chi");
  h1->GetXaxis()->SetTitleOffset(1.2);
  h1->GetYaxis()->SetTitle("Entries");

  h2->SetLineColor(kRed);
  h2->SetLineWidth(2);
  h2->GetXaxis()->SetTitle("#chi");
  h2->GetXaxis()->SetTitleOffset(1.2);
  h2->GetYaxis()->SetTitle("Entries");

  h3->SetLineColor(kRed+3);
  h3->SetLineWidth(2);
  h3->GetXaxis()->SetTitle("#chi");
  h3->GetXaxis()->SetTitleOffset(1.2);
  h3->GetYaxis()->SetTitle("Entries");

  gStyle->SetOptStat("nemrou");

  c->cd(1);
  c->cd(1)->SetLogx();
  c->cd(1)->SetLogy();
  t1->Draw("FatJetInfo.Jet_SD_chi>>Radion","FatJetInfo.Jet_SD_chi>0");

  c->cd(2);
  c->cd(2)->SetLogx();
  c->cd(2)->SetLogy();
  t2->Draw("FatJetInfo.Jet_SD_chi>>TTJets","FatJetInfo.Jet_SD_chi>0");

  c->cd(3);
  c->cd(3)->SetLogy();
  c->cd(3)->SetLogx();
  t3->Draw("FatJetInfo.Jet_SD_chi>>QCD","FatJetInfo.Jet_SD_chi>0");

  c->SaveAs("Separate.eps");

  gPad->Update();

  TCanvas *c2 = new TCanvas("c2","c2",800,600);
  c2->SetLogx();
  c2->SetLogy();
  c2->cd();
  h2->Draw();
  h1->SetTitle("");
  h2->SetTitle("");
  h3->SetTitle("");
  h1->Draw("SAME");
  h3->Draw("SAME");

  Double_t norm1 = h1->GetEntries();
  h1->Scale(1/norm1);
  Double_t norm2 = h2->GetEntries();
  h2->Scale(1/norm2);
  Double_t norm3 = h3->GetEntries();
  h3->Scale(1/norm3);

  TPaveStats *tps1 = (TPaveStats*) h1->FindObject("stats");
  tps1->SetName("Radion M800");
  tps1->SetTextColor(kBlue);
  double X1 = tps1->GetX1NDC();
  double Y1 = tps1->GetY1NDC();
  double X2 = tps1->GetX2NDC();
  double Y2 = tps1->GetY2NDC();

  TPaveStats *tps2 = (TPaveStats*) h2->FindObject("stats");
  tps2->SetName("TTJets");
  tps2->SetTextColor(kRed);
  tps2->SetX1NDC(X1);
  tps2->SetX2NDC(X2);
  tps2->SetY1NDC(Y1-(Y2-Y1));
  tps2->SetY2NDC(Y1);

  X1 = tps2->GetX1NDC();
  Y1 = tps2->GetY1NDC();
  X2 = tps2->GetX2NDC();
  Y2 = tps2->GetY2NDC();

  TPaveStats *tps3 = (TPaveStats*) h3->FindObject("stats");
  tps2->SetName("QCD p_{T} 470to800");
  tps3->SetTextColor(kRed+3);
  tps3->SetX1NDC(X1);
  tps3->SetX2NDC(X2);
  tps3->SetY1NDC(Y1-(Y2-Y1));
  tps3->SetY2NDC(Y1);

  gPad->Update();

  c2->SaveAs("Superimposed_normalized.eps");

}

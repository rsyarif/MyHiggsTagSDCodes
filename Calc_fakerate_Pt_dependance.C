{

  //TFile *f = new TFile("rootfiles/FakeMjIVFbtagCalculation_QCD_Pt-470to600_Tune4C_13TeV_pythia8_R08_r015_HiggsWin20_mc_subjets.root");
  TFile *f = new TFile("rootfiles/FakeMjIVFbtagCalculation_noMjConeCut4genMatch_useHadron_QCD_Pt-470to600_Tune4C_13TeV_pythia8_R08_r015_KtMj_HiggsWin30_tagr07_fake02_BtagALLMj_MjIVF015_MORE_mc_subjets.root");

  TTree * t= (TTree*)f->Get("tree");

  TCanvas *c1 = new TCanvas();

  const int nbins = 40; float xmin = 0; float xmax = 800;

  TH1D *h1 = new TH1D("h1","h1",nbins,xmin,xmax);
  TH1D *h2 = new TH1D("h2","h2",nbins,xmin,xmax);

  gStyle->SetOptStat("nemrou");

  h1->SetLineColor(kBlue);
  h1->SetLineWidth(2);
  h1->SetTitle("abs(Mj_gen_matched_pdgID)<99999&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4");
  h1->GetXaxis()->SetTitle("Microjet p_{T}");

  h2->SetLineColor(kBlue);
  h2->SetLineWidth(2);
  h2->SetTitle("abs(Mj_gen_matched_pdgID)<99999.eps&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4&&Mj_isBtag==1_.eps");
  h2->GetXaxis()->SetTitle("Microjet p_{T}");

  t->Draw("Mj_pt>>h1","abs(Fj_flavour)!=5&&abs(Fj_flavour)!=4");

  c1->SaveAs("plots/QCD470-600_Mj_pt_abs(Fj_flavour)!=5&&abs(Fj_flavour)!=4_.eps");

  t->Draw("Mj_pt>>h2","Mj_isBtag==1&&abs(Fj_flavour)!=5&&abs(Fj_flavour)!=4");

  c1->SaveAs("plots/QCD470-600_Mj_pt_Mj_isBtag==1&&abs(Fj_flavour)!=5&&abs(Fj_flavour)!=4_.eps");


  //t->Draw("Mj_pt>>h1","abs(Mj_gen_matched_pdgID)<99999&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4");

  //c1->SaveAs("plots/QCD470-600_Mj_pt_abs(Mj_gen_matched_pdgID)<99999&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4_.eps");

  //t->Draw("Mj_pt>>h2","abs(Mj_gen_matched_pdgID)<99999&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4&&Mj_isBtag==1");

  //c1->SaveAs("plots/QCD470-600_Mj_pt_abs(Mj_gen_matched_pdgID)<99999&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4&&Mj_isBtag==1_.eps");

  //t->Draw("Mj_pt>>h1","Mj_dR_gen<0.05&&abs(Mj_gen_matched_pdgID)<99999&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4");

  //c1->SaveAs("plots/QCD470-600_Mj_pt_Mj_dR_gen<0.05&&abs(Mj_gen_matched_pdgID)<99999&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4_.eps");

  //t->Draw("Mj_pt>>h2","Mj_dR_gen<0.05&&abs(Mj_gen_matched_pdgID)<99999&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4&&Mj_isBtag==1");

  //c1->SaveAs("plots/QCD470-600_Mj_pt_Mj_dR_gen<0.05&&abs(Mj_gen_matched_pdgID)<99999&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4&&Mj_isBtag==1_.eps");


  //int nbins  = h1->GetSize()-2;

  float v1[nbins];
  float v1_std[nbins];
  float v2[nbins];
  float v2_std[nbins];
  float x[nbins];
  float ratio_[nbins];
  float ratio_err_x[nbins];
  float ratio_err_y[nbins];

  for (int i =0 ; i<nbins;i++){
    v1[i] = h1->GetBinContent(i+1);
    v1_std[i] = sqrt(v1[i]);
    v2[i] = h2->GetBinContent(i+1);
    v2_std[i] = sqrt(v2[i]);
    ratio_[i] = (v2[i]==0? 0 : v2[i]/v1[i]);
    ratio_err_x[i] = (xmax - xmin)/nbins *0.5;
    ratio_err_y[i] = ratio_[i] * sqrt( (v1_std[i] / v1[i])*(v1_std[i] / v1[i])  + (v2_std[i] / v2[i])*(v2_std[i] / v2[i]) ) ;
    x[i] = xmin + i * (xmax-xmin)/nbins ;
  }

  TGraphErrors *gr = new TGraphErrors(nbins,x,ratio_,ratio_err_x,ratio_err_y);
  gr->Draw("AP");
  gr->SetTitle("ratio of #frac{IVF matched non-b/c Mj}{non-b/c Mj}");
  gr->GetXaxis()->SetTitle("p_{T}");

  c1->SetGridy();
  c1->SaveAs("plots/QCD_Pt-470to600_IVFfakerate_PtDependance.eps");
}

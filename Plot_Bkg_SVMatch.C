{
  string prefix = "FakeMjIVFbtagCalculation_";
  //string fname = "RelValProdTTbar_13_AOD";
  //string fname = "QCD_Pt-470to600_Tune4C_13TeV_pythia8";
  string fname = "QCD_Pt-300to470_Tune4C_13TeV_pythia8";

  TCanvas *c1 = new TCanvas();

  gStyle->SetOptStat("nemrou");

  TFile *f = new TFile(("rootfiles/"+prefix+fname+"_R08_r015_HiggsWin20_tagr07_fake02_BtagALLMj_MjIVF015_mc_subjets.root").c_str());
  TTree *t = (TTree*) f->Get("tree");

  t->Draw("Mj_pt","abs(Fj_flavour)!=5&&abs(Fj_flavour)!=4");

  c1->SaveAs(("rootfiles/"+fname+"_Mj_pt_abs(Fj_flavour)!=5&&abs(Fj_flavour)!=4.eps").c_str());

  t->Draw("Mj_pt","abs(Fj_flavour)!=5&&abs(Fj_flavour)!=4&&Mj_isBtag==1");

  c1->SaveAs(("rootfiles/"+fname+"_Mj_pt_abs(Fj_flavour)!=5&&abs(Fj_flavour)!=4&&Mj_isBtag==1.eps").c_str());
  //
  t->Draw("Mj_eta","abs(Fj_flavour)!=5&&abs(Fj_flavour)!=4");

  c1->SaveAs(("rootfiles/"+fname+"_Mj_eta_abs(Fj_flavour)!=5&&abs(Fj_flavour)!=4.eps").c_str());

  t->Draw("Mj_eta","abs(Fj_flavour)!=5&&abs(Fj_flavour)!=4&&Mj_isBtag==1");

  c1->SaveAs(("rootfiles/"+fname+"_Mj_eta_abs(Fj_flavour)!=5&&abs(Fj_flavour)!=4&&Mj_isBtag==1.eps").c_str());
  //
  t->Draw("Mj_gen_matched_pdgID","abs(Mj_dR_gen)<99999&&abs(Fj_flavour)!=5&&abs(Fj_flavour)!=4");

  c1->SaveAs(("rootfiles/"+fname+"_Mj_gen_matched_pdgID_abs(Mj_dR_gen)<99999&&abs(Fj_flavour)!=5&&abs(Fj_flavour)!=4.eps").c_str());

  t->Draw("Mj_gen_matched_pdgID","abs(Mj_dR_gen)<99999&&abs(Fj_flavour)!=5&&abs(Fj_flavour)!=4&&Mj_isBtag==1");

  c1->SaveAs(("rootfiles/"+fname+"_Mj_gen_matched_pdgID_abs(Mj_dR_gen)<99999&&abs(Fj_flavour)!=5&&abs(Fj_flavour)!=4&&Mj_isBtag==1.eps").c_str());
  //
  t->Draw("Fj_flavour","abs(Fj_flavour)!=5&&abs(Fj_flavour)!=4");

  c1->SaveAs(("rootfiles/"+fname+"_Fj_flavour_abs(Fj_flavour)!=5&&abs(Fj_flavour)!=4.eps").c_str());

  t->Draw("Fj_flavour","abs(Fj_flavour)!=5&&abs(Fj_flavour)!=4&&Mj_isBtag==1");

  c1->SaveAs(("rootfiles/"+fname+"_Fj_flavour_abs(Fj_flavour)!=5&&abs(Fj_flavour)!=4&&Mj_isBtag==1.eps").c_str());
  //
  t->Draw("Mj_dR_SV","Mj_dR_SV>=0&&Mj_isBtag==1&&abs(Fj_flavour)!=5&&abs(Fj_flavour)!=4");

  c1->SaveAs(("rootfiles/"+fname+"_Mj_dR_SV_Mj_dR_SV>=0&&Mj_isBtag==1&&abs(Fj_flavour)!=5&&abs(Fj_flavour)!=4_.eps").c_str());

  t->Draw("Mj_dR_SV","Mj_dR_SV>=0&&Mj_dR_SV<0.15&&abs(Fj_flavour)!=5&&abs(Fj_flavour)!=4");

  c1->SaveAs(("rootfiles/"+fname+"_Mj_dR_SV_Mj_dR_SV>=0&&Mj_dR_SV<0.15&&abs(Fj_flavour)!=5&&abs(Fj_flavour)!=4_.eps").c_str());
  //
  t->Draw("Mj_dR_SV_1t1","Mj_dR_SV_1t1>=0&&Mj_dR_SV_1t1<0.15&&abs(Fj_flavour)!=5&&abs(Fj_flavour)!=4");

  c1->SaveAs(("rootfiles/"+fname+"_Mj_dR_SV_1t1_Mj_dR_SV_1t1>=0&&Mj_dR_SV_1t1<0.15&&abs(Fj_flavour)!=5&&abs(Fj_flavour)!=4_.eps").c_str());

  t->Draw("Mj_dR_SV_1t1","Mj_dR_SV_1t1>=0&&Mj_dR_SV_1t1<0.015&&abs(Fj_flavour)!=5&&abs(Fj_flavour)!=4");

  c1->SaveAs(("rootfiles/"+fname+"_Mj_dR_SV_1t1_Mj_dR_SV_1t1>=0&&Mj_dR_SV_1t1<0.015&&abs(Fj_flavour)!=5&&abs(Fj_flavour)!=4_.eps").c_str());
  //
  t->Draw("Mj_dR_gen","abs(Mj_gen_matched_pdgID)<99999");

  c1->SaveAs(("rootfiles/"+fname+"_Mj_dR_gen_abs(Mj_gen_matched_pdgID)<99999.eps").c_str());
  //
  t->Draw("Mj_pt","abs(Mj_gen_matched_pdgID)<99999");

  c1->SaveAs(("rootfiles/"+fname+"_Mj_pt_abs(Mj_gen_matched_pdgID)<99999.eps").c_str());

  t->Draw("Mj_pt","abs(Mj_gen_matched_pdgID)<99999&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4");

  c1->SaveAs(("rootfiles/"+fname+"_Mj_pt_abs(Mj_gen_matched_pdgID)<99999&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4.eps").c_str());

  t->Draw("Mj_pt","abs(Mj_gen_matched_pdgID)<99999&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4&&Mj_isBtag==1");

  c1->SaveAs(("rootfiles/"+fname+"_Mj_pt_abs(Mj_gen_matched_pdgID)<99999&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4&&Mj_isBtag==1.eps").c_str());

  t->Draw("Mj_pt","Mj_dR_gen<0.05&&abs(Mj_gen_matched_pdgID)<99999");

  c1->SaveAs(("rootfiles/"+fname+"_Mj_pt_Mj_dR_gen<0.05&&abs(Mj_gen_matched_pdgID)<99999.eps").c_str());

  t->Draw("Mj_pt","Mj_dR_gen<0.05&&abs(Mj_gen_matched_pdgID)<99999&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4");

  c1->SaveAs(("rootfiles/"+fname+"_Mj_pt_Mj_dR_gen<0.05&&abs(Mj_gen_matched_pdgID)<99999&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4.eps").c_str());

  t->Draw("Mj_pt","Mj_dR_gen<0.05&&abs(Mj_gen_matched_pdgID)<99999&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4&&Mj_isBtag==1");

  c1->SaveAs(("rootfiles/"+fname+"_Mj_pt_Mj_dR_gen<0.05&&abs(Mj_gen_matched_pdgID)<99999&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4&&Mj_isBtag==1.eps").c_str());
  //
  t->Draw("Mj_gen_matched_pdgID","abs(Mj_gen_matched_pdgID)<99999");

  c1->SaveAs(("rootfiles/"+fname+"_Mj_gen_matched_pdgID_abs(Mj_gen_matched_pdgID)<99999.eps").c_str());

  t->Draw("Mj_gen_matched_pdgID","abs(Mj_gen_matched_pdgID)<99999&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4");

  c1->SaveAs(("rootfiles/"+fname+"_Mj_gen_matched_pdgID_abs(Mj_gen_matched_pdgID)<99999&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4.eps").c_str());

  t->Draw("Mj_gen_matched_pdgID","abs(Mj_gen_matched_pdgID)<99999&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4&&Mj_isBtag==1");

  c1->SaveAs(("rootfiles/"+fname+"_Mj_gen_matched_pdgID_abs(Mj_gen_matched_pdgID)<99999&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4&&Mj_isBtag==1.eps").c_str());

  t->Draw("Mj_gen_matched_pdgID","Mj_dR_gen<0.05&&abs(Mj_gen_matched_pdgID)<99999");

  c1->SaveAs(("rootfiles/"+fname+"_Mj_gen_matched_pdgID_Mj_dR_gen<0.05&&abs(Mj_gen_matched_pdgID)<99999.eps").c_str());

  t->Draw("Mj_gen_matched_pdgID","Mj_dR_gen<0.05&&abs(Mj_gen_matched_pdgID)<99999&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4");

  c1->SaveAs(("rootfiles/"+fname+"_Mj_gen_matched_pdgID_Mj_dR_gen<0.05&&abs(Mj_gen_matched_pdgID)<99999&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4.eps").c_str());

  t->Draw("Mj_gen_matched_pdgID","Mj_dR_gen<0.05&&abs(Mj_gen_matched_pdgID)<99999&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4&&Mj_isBtag==1");

  c1->SaveAs(("rootfiles/"+fname+"_Mj_gen_matched_pdgID_Mj_dR_gen<0.05&&abs(Mj_gen_matched_pdgID)<99999&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4&&Mj_isBtag==1.eps").c_str());
  //
  t->Draw("Mj_gen_matched_eta","abs(Mj_gen_matched_pdgID)<99999");

  c1->SaveAs(("rootfiles/"+fname+"_Mj_gen_matched_eta_abs(Mj_gen_matched_pdgID)<99999.eps").c_str());

  t->Draw("Mj_gen_matched_eta","abs(Mj_gen_matched_pdgID)<99999&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4");

  c1->SaveAs(("rootfiles/"+fname+"_Mj_gen_matched_eta_abs(Mj_gen_matched_pdgID)<99999&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4.eps").c_str());

  t->Draw("Mj_gen_matched_eta","abs(Mj_gen_matched_pdgID)<99999&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4&&Mj_isBtag==1");

  c1->SaveAs(("rootfiles/"+fname+"_Mj_gen_matched_eta_abs(Mj_gen_matched_pdgID)<99999&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4&&Mj_isBtag==1.eps").c_str());

  t->Draw("Mj_gen_matched_eta","Mj_dR_gen<0.05&&abs(Mj_gen_matched_pdgID)<99999");

  c1->SaveAs(("rootfiles/"+fname+"_Mj_gen_matched_eta_Mj_dR_gen<0.05&&abs(Mj_gen_matched_pdgID)<99999.eps").c_str());

  t->Draw("Mj_gen_matched_eta","Mj_dR_gen<0.05&&abs(Mj_gen_matched_pdgID)<99999&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4");

  c1->SaveAs(("rootfiles/"+fname+"_Mj_gen_matched_eta_Mj_dR_gen<0.05&&abs(Mj_gen_matched_pdgID)<99999&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4.eps").c_str());

  t->Draw("Mj_gen_matched_eta","Mj_dR_gen<0.05&&abs(Mj_gen_matched_pdgID)<99999&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4&&Mj_isBtag==1");

  c1->SaveAs(("rootfiles/"+fname+"_Mj_gen_matched_eta_Mj_dR_gen<0.05&&abs(Mj_gen_matched_pdgID)<99999&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4&&Mj_isBtag==1.eps").c_str());
  //
  TH2D *h_1 = new TH2D("h_1","h_1",50,0,1000,51,-25.5,25.5);
  TH2D *h_2 = new TH2D("h_2","h_2",50,0,1000,51,-25.5,25.5);
  t->Draw("Mj_gen_matched_pdgID:Mj_pt>>h_1","abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4");
  t->Draw("Mj_gen_matched_pdgID:Mj_pt>>h_2","Mj_isBtag==1&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4");

  h_1->Draw("LEGO2");
  c1->SaveAs(("rootfiles/"+fname+"_Mj_pt:Mj_gen_matched_pdgID_abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4.eps").c_str());

  h_2->Draw("LEGO2");
  c1->SaveAs(("rootfiles/"+fname+"_Mj_pt:Mj_gen_matched_pdgID_Mj_isBtag==1&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4.eps").c_str());

  //

  TFile *f_ = new TFile(("rootfiles/"+fname+"_R08_r015_HiggsWin20_tagr07_fake02_BtagALLMj_MjIVF015_mc_subjets.root").c_str());
  TDirectory *d_ = f_->GetDirectory("btaganaSubJets");
  TTree *t_ = (TTree*) d_->Get("ttree");

  const int nbins = 50;float xmin = 0;float xmax = 800;

  TH1D *h1 = new TH1D("h1","h1",nbins,xmin,xmax);
  TH1D *h2 = new TH1D("h2","h2",nbins,xmin,xmax);
  TH1D *h3 = new TH1D("h3","h3",5,-0.5,4.5);
  TH1D *h4 = new TH1D("h4","h4",5,-0.5,4.5);

  const int nEvent = t_->GetEntries();

  const int nGenPrunedMax = 50;

  int nGenPruned;
  int GenPruned_pdgID[nGenPrunedMax];
  float GenPruned_eta[nGenPrunedMax];
  float GenPruned_phi[nGenPrunedMax];
  float GenPruned_pT[nGenPrunedMax];
  int GenPruned_mother[nGenPrunedMax];
  int GenPruned_status[nGenPrunedMax];

  const int nFjMax=10;
  const int nMjMax=50;
  const int nSVMax=50;

  int nJet;
  int Jet_flavour[nFjMax];
  float Jet_eta[nFjMax];
  float Jet_phi[nFjMax];
  float Jet_SD_chi[nFjMax];
  float Jet_pt[nFjMax];
  int Jet_SD_nBtagMicrojets[nFjMax];

  int   Jet_SD_nMicrojets[nFjMax];
  int Jet_SD_nFirstMicrojet[nFjMax];
  int Jet_SD_nLastMicrojet[nFjMax];
  float Jet_SD_Microjet_pt[nMjMax];
  float Jet_SD_Microjet_eta[nMjMax];
  float Jet_SD_Microjet_phi[nMjMax];
  int   Jet_SD_Microjet_isBtag[nMjMax];

  int Jet_SV_multi[nFjMax];
  int Jet_nFirstSV[nFjMax];
  int Jet_nLastSV[nFjMax];
  float SV_vtx_pt[nSVMax];
  float SV_vtx_eta[nSVMax];
  float SV_vtx_phi[nSVMax];

  t_->SetBranchAddress("nGenPruned",&nGenPruned);
  t_->SetBranchAddress("GenPruned_pdgID",&GenPruned_pdgID);
  t_->SetBranchAddress("GenPruned_eta",&GenPruned_eta);
  t_->SetBranchAddress("GenPruned_phi",&GenPruned_phi);
  t_->SetBranchAddress("GenPruned_pT",&GenPruned_pT);
  t_->SetBranchAddress("GenPruned_mother",&GenPruned_mother);
  t_->SetBranchAddress("GenPruned_status",&GenPruned_status);

  t_->SetBranchAddress("FatJetInfo.nJet",&nJet);
  t_->SetBranchAddress("FatJetInfo.Jet_flavour",&Jet_flavour);
  t_->SetBranchAddress("FatJetInfo.Jet_eta",&Jet_eta);
  t_->SetBranchAddress("FatJetInfo.Jet_phi",&Jet_phi);
  t_->SetBranchAddress("FatJetInfo.Jet_SD_chi",&Jet_SD_chi);
  t_->SetBranchAddress("FatJetInfo.Jet_pt",&Jet_pt);
  t_->SetBranchAddress("FatJetInfo.Jet_SD_nBtagMicrojets",&Jet_SD_nBtagMicrojets);

  t_->SetBranchAddress("FatJetInfo.Jet_SD_nMicrojets",&Jet_SD_nMicrojets);
  t_->SetBranchAddress("FatJetInfo.Jet_SD_nFirstMicrojet",&Jet_SD_nFirstMicrojet);
  t_->SetBranchAddress("FatJetInfo.Jet_SD_nLastMicrojet",&Jet_SD_nLastMicrojet);
  t_->SetBranchAddress("FatJetInfo.Jet_SD_Microjet_pt",&Jet_SD_Microjet_pt);
  t_->SetBranchAddress("FatJetInfo.Jet_SD_Microjet_eta",&Jet_SD_Microjet_eta);
  t_->SetBranchAddress("FatJetInfo.Jet_SD_Microjet_phi",&Jet_SD_Microjet_phi);
  t_->SetBranchAddress("FatJetInfo.Jet_SD_Microjet_isBtag",&Jet_SD_Microjet_isBtag);

  t_->SetBranchAddress("FatJetInfo.Jet_SV_multi",&Jet_SV_multi);
  t_->SetBranchAddress("FatJetInfo.Jet_nFirstSV",&Jet_nFirstSV);
  t_->SetBranchAddress("FatJetInfo.Jet_nLastSV",&Jet_nLastSV);
  t_->SetBranchAddress("FatJetInfo.SV_vtx_pt",&SV_vtx_pt);
  t_->SetBranchAddress("FatJetInfo.SV_vtx_eta",&SV_vtx_eta);
  t_->SetBranchAddress("FatJetInfo.SV_vtx_phi",&SV_vtx_phi);

  //loop over events
  for (int i =0 ; i<nEvent;i++){
  //for (int i =0 ; i<2;i++){
    if(i%50==0)cout<<"Processing Event "<<i<<endl;
    t_->GetEntry(i);

    if(nJet==0)continue;

    //loop over fatjets
    for(int j=0; j < nJet; j++){

      if( abs(Jet_flavour[j])==5 || abs(Jet_flavour[j])==4)continue;

      h3->Fill(Jet_SV_multi[j]);

      if(Jet_SV_multi[j]>0) h4->Fill(Jet_SV_multi[j]);

      //loop over SV
      //int iSV = 0; int first = Jet_nFirstSV[j]; int last = Jet_nLastSV[j];
      //for(int jSV = first; jSV < last ; jSV++){
      //iSV++;
      //}

  	//Microjet loop
      int iMj_=0;
      for(int l = Jet_SD_nFirstMicrojet[j] ; l < Jet_SD_nLastMicrojet[j] ;l++){
	h1->Fill(Jet_SD_Microjet_pt[l]);

  	if(Jet_SD_Microjet_isBtag[l]!=1) continue;
	h2->Fill(Jet_SD_Microjet_pt[l]);


  	iMj_++;
      }//end Mj loop

    }//end Fj loop

  }//end event loop

  h1->Draw();
  h1->GetXaxis()->SetTitle("Mj p_{T}");

  c1->SaveAs(("rootfiles/"+fname+"_Mj_pt_FatJetInfo.nJet>0&&abs(FatJetInfo.Jet_flavour)!=5&&abs(FatJetInfo.Jet_flavour)!=4_LOOP.eps").c_str());

  h2->Draw();
  h2->GetXaxis()->SetTitle("Mj p_{T}");

  c1->SaveAs(("rootfiles/"+fname+"_Mj_pt_FatJetInfo.nJet>0&&abs(FatJetInfo.Jet_flavour)!=5&&abs(FatJetInfo.Jet_flavour)!=4&&Mj_isBtag==1_LOOP.eps").c_str());


  h3->Draw();
  h3->GetXaxis()->SetTitle("Jet_SV_multi");

  c1->SaveAs(("rootfiles/"+fname+"_Jet_SV_multi_FatJetInfo.nJet>0&&abs(FatJetInfo.Jet_flavour)!=5&&abs(FatJetInfo.Jet_flavour)!=4_LOOP.eps").c_str());

  h4->Draw();
  h4->GetXaxis()->SetTitle("Jet_SV_multi");

  c1->SaveAs(("rootfiles/"+fname+"_Jet_SV_multi_FatJetInfo.nJet>0&&abs(FatJetInfo.Jet_flavour)!=5&&abs(FatJetInfo.Jet_flavour)!=4&&Jet_SV_multi>0_LOOP.eps").c_str());

  //

  float v1[nbins];
  float v1_std[nbins];
  float v2[nbins];
  float v2_std[nbins];
  float x[nbins];
  float Y[nbins];

  for (int i =0 ; i<nbins;i++){
    v1[i] = h1->Integral(i+1,nbins+1);
    v1_std[i] = sqrt(v1[i]);
    v2[i] = h2->Integral(i+1,nbins+1);
    v2_std[i] = sqrt(v2[i]);
    Y[i] = (v2[i]==0? 0 : v2[i]/v1[i]);
    x[i] = xmin + i * (xmax-xmin)/nbins;
  }

  TGraph *gr = new TGraph(nbins,x,Y);
  gr->Draw("AP*L");
  gr->SetTitle("ratio of #frac{IVF matched, non-b/c Mj}{non-b/c Mj}");
  gr->GetXaxis()->SetTitle("p_{T}");

  c1->SetGridy();
  c1->SaveAs(("rootfiles/"+fname+"_IVFfakerate_PtDependance.eps").c_str());


}
//  LocalWords:  TFile

using namespace std;

string savedir = "plots";

TH2D* Plot_PartonMatch_2D(std::string dir, std::string fname,  std::string var1, std::string var2, std::string cut,  double xbin, double xmin, double xmax,double ybin, double ymin, double ymax, std::string xlabel,std::string ylabel, std::string DrawOption, std::string postfix,bool save = false){

  TFile *f = new TFile((dir+"/"+"fMatch_"+fname+"_"+postfix+".root").c_str());

  string var1_ = var1;
  if(var1_=="log(Fj_chi)") var1_ = "logChi"; //log(Fj_chi) become log( for some reason???
  string var2_ = var2;
  if(var2_=="log(Fj_chi)") var2_ = "logChi"; //log(Fj_chi) become log( for some reason???


  TCanvas* cvs = new TCanvas((var1_+var2_+postfix).c_str(),(var1_+var2_+postfix).c_str(),600,600);

  TTree *t = (TTree*)f->Get("tree");
  TH2D* h2 = new TH2D((var1_+var2_+postfix).c_str(),(var1_+var2_+postfix).c_str(),xbin,xmin,xmax,ybin,ymin,ymax);

  t->Draw((var2+":"+var1+">>"+var1_+var2_+postfix).c_str(),cut.c_str());

  h2->GetXaxis()->SetTitle(xlabel.c_str());
  h2->GetXaxis()->SetTitleOffset(1.5);
  h2->GetYaxis()->SetTitle(ylabel.c_str());
  h2->GetYaxis()->SetTitleOffset(1.75);
  h2->SetTitle("");

  cvs->cd();
  cvs->SetLeftMargin(.15);
  cvs->SetBottomMargin(.15);
  cvs->SetRightMargin(.2);
  gStyle->SetOptStat("nemrous");
  h2->Draw(DrawOption.c_str());

  delete t;
  if(save)cvs->SaveAs((savedir+"/2D_"+fname+"_"+var1_+"_"+var2_+"_"+cut+"_"+DrawOption+".eps").c_str());
  return h2;
}

TH1D* PartonMatch_1D(std::string dir, TFile* f, std::string fname,  std::string var, std::string cut,  double xbin, double xmin, double xmax, std::string xlabel, std::string postfix, Color_t color = kBlue, int linestyle = 1,bool save = false, bool saveroot = false){

  string var_ = var;
  if(var_=="log(Fj_chi)") var_ = "logChi"; //log(Fj_chi) become log( for some reason???

  TCanvas* cvs = new TCanvas((var_+postfix).c_str(),(var_+postfix).c_str(),600,600);

  TTree *t = (TTree*)f->Get("tree");

  TH1D* h = new TH1D ((var_+postfix).c_str(),(var_+postfix).c_str(),xbin,xmin,xmax);

  t->Draw((var+">>"+var_+postfix).c_str(),cut.c_str());

  gStyle->SetOptStat("nemrou");

  h->SetLineWidth(2);
  h->SetLineColor(color);
  h->SetLineStyle(linestyle);
  h->GetXaxis()->SetTitle(xlabel.c_str());
  h->GetYaxis()->SetTitle("");
  h->SetTitle("");

  delete t;
  if(save)cvs->SaveAs((savedir+"/"+fname+"_"+var_+"_"+cut+".eps").c_str());

  if(saveroot){
    TFile *fout = new TFile((savedir+"/"+"PLOTS_"+fname+"_"+var_+"_"+cut+".root").c_str(),"RECREATE");
    fout->cd();
    h->Write("h");
    fout->Close();
  }

  return h;
}

// void makeHistos(bool save = false, bool display = false){
//   //string dir = "1leadbtagmjcondition";
//   //string fsig = "RadionToHH_4b_M-800_TuneZ2star_8TeV-Madgraph_pythia6_R12_r15_minPt200_1leadbtagmjcondition_mc_subjets";
//   //string fbkg = "TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_R12_r15_minPt200_1leadbtagmjcondition_mc_subjets";

//   string dir = "allChi_noMinFatjetPt_noMjBtagCondition";
//   string fsig = "RadionToHH_4b_M-800_TuneZ2star_8TeV-Madgraph_pythia6_R12_r15_minPt0_Nobtagmjcondition_AllChi_mc_subjets";
//   string fbkg = "ZPrimeToTTJets_M1000GeV_W10GeV_TuneZ2star_8TeV-madgraph-tauola_R12_r15_minPt0_Nobtagmjcondition_AllChi_mc_subjets";

//   string var = "dR_match";

//   double dR_tight = 0.05;double dR_med = 0.2;  double dR_loose = 1.2;

//   double xbin = 40; double xmin = -18; double xmax = -2;
//   double ybin = 40; double ymin = 0; double ymax = 1.2;

//   //bool display = false ;
//   //bool save = false;

//   string postfix;

//   //loose match
//   postfix = "dRmax12";
//   TFile *f_sig_l = new TFile((dir+"/"+"fMatch_"+fsig+"_"+postfix+".root").c_str());
//   TH2D* h2_sig_l = PartonMatch_2D(dir,f_sig_l,var,xbin,xmin,xmax,ybin,ymin,1.2,"dRmax12");
//   TH1D* h_sig_l = PartonMatch_1D(dir,f_sig_l,fsig,"log(Fj_chi)",xbin,xmin,xmax,"dRmax12");

//   TFile *f_bkg_l = new TFile((dir+"/"+"fMatch_"+fbkg+"_"+postfix+".root").c_str());
//   TH2D* h2_bkg_l = PartonMatch_2D(dir,f_bkg_l,var,xbin,xmin,xmax,ybin,ymin,1.2,"dRmax12");
//   TH1D* h_bkg_l = PartonMatch_1D(dir,f_bkg_l,fbkg,"log(Fj_chi)",xbin,xmin,xmax,"dRmax12");

//   //med match
//   postfix = "dRmax02";
//   TFile *f_sig_m = new TFile((dir+"/"+"fMatch_"+fsig+"_"+postfix+".root").c_str());
//   TH2D* h2_sig_m = PartonMatch_2D(dir,f_sig_m,var,xbin,xmin,xmax,ybin,ymin,0.2,"dRmax02");
//   TH1D* h_sig_m = PartonMatch_1D(dir,f_sig_m,fsig,"log(Fj_chi)",xbin,xmin,xmax,"dRmax02");

//   TFile *f_bkg_m = new TFile((dir+"/"+"fMatch_"+fbkg+"_"+postfix+".root").c_str());
//   TH2D* h2_bkg_m = PartonMatch_2D(dir,f_bkg_m,var,xbin,xmin,xmax,ybin,ymin,0.2,"dRmax02");
//   TH1D* h_bkg_m = PartonMatch_1D(dir,f_bkg_m,fbkg,"log(Fj_chi)",xbin,xmin,xmax,"dRmax02");

//   //tight match
//   postfix = "dRmax005";
//   TFile *f_sig_t = new TFile((dir+"/"+"fMatch_"+fsig+"_"+postfix+".root").c_str());
//   TH2D* h2_sig_t = PartonMatch_2D(dir,f_sig_t,var,xbin,xmin,xmax,ybin,ymin,0.05,"dRmax005");
//   TH1D* h_sig_t = PartonMatch_1D(dir,f_sig_t,fsig,"log(Fj_chi)",xbin,xmin,xmax,"dRmax005");

//   TFile *f_bkg_t = new TFile((dir+"/"+"fMatch_"+fbkg+"_"+postfix+".root").c_str());
//   TH2D* h2_bkg_t = PartonMatch_2D(dir,f_bkg_t,var,xbin,xmin,xmax,ybin,ymin,0.05,"dRmax005");
//   TH1D* h_bkg_t = PartonMatch_1D(dir,f_bkg_t,fbkg,"log(Fj_chi)",xbin,xmin,xmax,"dRmax005");


//   TCanvas* canvas = new TCanvas("loose matching","loose matching",600,600);
//   TCanvas* canvas2 = new TCanvas("med matching","med matching",600,600);
//   TCanvas* canvas3 = new TCanvas("tight matching","tight matching",600,600);
//   TCanvas* canvas4 = new TCanvas("sig matching","sig matching",600,600);
//   TCanvas* canvas5 = new TCanvas("bkg matching","bkg matching",600,600);

//   cout<<"Creating "<< dir+"/"+"PartonMatch_histos.root"<< endl;
//   TFile *fhistos = new TFile((dir+"/"+"PartonMatch_histos.root").c_str(),"RECREATE");
//   //TFile *fhistos = new TFile("TEMP_PartonMatch_histos.root","RECREATE");

//   h_sig_l->SetStats(1);
//   h_sig_m->SetStats(1);
//   h_sig_t->SetStats(1);

//   h_bkg_l->SetStats(1);
//   h_bkg_m->SetStats(1);
//   h_bkg_t->SetStats(1);

//   gStyle->SetOptStat("nemrou");
//   gPad->Update();

//   fhistos->cd();
//   h2_sig_l->Write("h2_sig_l");
//   h2_sig_m->Write("h2_sig_m");
//   h2_sig_t->Write("h2_sig_t");

//   h_sig_l->Write("h_sig_l");
//   h_sig_m->Write("h_sig_m");
//   h_sig_t->Write("h_sig_t");

//   h2_bkg_l->Write("h2_bkg_l");
//   h2_bkg_m->Write("h2_bkg_m");
//   h2_bkg_t->Write("h2_bkg_t");

//   h_bkg_l->Write("h_bkg_l");
//   h_bkg_m->Write("h_bkg_m");
//   h_bkg_t->Write("h_bkg_t");

//   canvas->cd();

//   h_sig_l->SetStats(0);
//   h_bkg_l->SetStats(0);
//   h_sig_l->SetLineColor(kBlue);
//   h_bkg_l->SetLineColor(kRed);

//   h_sig_l->DrawNormalized();
//   h_bkg_l->DrawNormalized("SAME");

//   leg = new TLegend(0.75,0.65,0.95,0.85);
//   leg->SetFillStyle(0);
//   leg->SetBorderSize(0);
//   leg->AddEntry(h_sig_l,"Radion","L");
//   leg->AddEntry(h_bkg_l,"ttjets","L");
//   leg->Draw("SAME");

//   gPad->Update();

//   canvas->SaveAs((savedir+"/loose_match.eps").c_str());
//   canvas->Write();

//   canvas2->cd();

//   h_sig_m->SetStats(0);
//   h_bkg_m->SetStats(0);
//   h_sig_m->SetLineColor(kBlue);
//   h_bkg_m->SetLineColor(kRed);

//   h_sig_m->DrawNormalized();
//   h_bkg_m->DrawNormalized("SAME");

//   leg2 = new TLegend(0.75,0.65,0.95,0.85);
//   leg2->SetFillStyle(0);
//   leg2->SetBorderSize(0);
//   leg2->AddEntry(h_sig_m,"Radion","L");
//   leg2->AddEntry(h_bkg_m,"ttjets","L");
//   leg2->Draw("SAME");

//   gPad->Update();

//   canvas2->SaveAs((savedir+"/medium_match.eps").c_str());
//   canvas2->Write();

//   canvas3->cd();

//   h_sig_t->SetStats(0);
//   h_bkg_t->SetStats(0);
//   h_sig_t->SetLineColor(kBlue);
//   h_bkg_t->SetLineColor(kRed);

//   h_sig_t->DrawNormalized();
//   h_bkg_t->DrawNormalized("SAME");

//   gPad->Update();

//   leg3 = new TLegend(0.75,0.65,0.95,0.85);
//   leg3->SetFillStyle(0);
//   leg3->SetBorderSize(0);
//   leg3->AddEntry(h_sig_t,"Radion","L");
//   leg3->AddEntry(h_bkg_t,"ttjets","L");
//   leg3->Draw("SAME");

//   canvas3->SaveAs((savedir+"/tight_match.eps").c_str());
//   canvas3->Write();

//   canvas4->cd();

//   h_sig_l->SetLineStyle(9);
//   h_sig_m->SetLineStyle(2);
//   h_sig_t->SetLineStyle(1);

//   h_sig_l->SetLineWidth(3);

//   h_sig_l->SetLineColor(kRed);
//   h_sig_m->SetLineColor(kYellow+2);
//   h_sig_t->SetLineColor(kGreen+2);

//   h_sig_t->DrawNormalized();
//   h_sig_m->DrawNormalized("SAME");
//   h_sig_l->DrawNormalized("SAME");

//   leg4 = new TLegend(0.75,0.65,0.95,0.85);
//   leg4->SetFillStyle(0);
//   leg4->SetBorderSize(0);
//   leg4->AddEntry(h_sig_l,"loose","L");
//   leg4->AddEntry(h_sig_m,"medium","L");
//   leg4->AddEntry(h_sig_t,"tight","L");
//   leg4->Draw("SAME");

//   gPad->Update();

//   canvas4->SaveAs((savedir+"/sig_match.eps").c_str());
//   canvas4->Write();

//   canvas5->cd();

//   h_bkg_l->SetLineStyle(9);
//   h_bkg_m->SetLineStyle(2);
//   h_bkg_t->SetLineStyle(1);

//   h_bkg_l->SetLineWidth(3);

//   h_bkg_l->SetLineColor(kRed);
//   h_bkg_m->SetLineColor(kYellow+2);
//   h_bkg_t->SetLineColor(kGreen+2);

//   h_bkg_l->DrawNormalized();
//   h_bkg_m->DrawNormalized("SAME");
//   h_bkg_t->DrawNormalized("SAME");

//   leg5 = new TLegend(0.75,0.65,0.95,0.85);
//   leg5->SetFillStyle(0);
//   leg5->SetBorderSize(0);
//   leg5->AddEntry(h_bkg_l,"loose","L");
//   leg5->AddEntry(h_bkg_m,"medium","L");
//   leg5->AddEntry(h_bkg_t,"tight","L");
//   leg5->Draw("SAME");

//   gPad->Update();

//   canvas5->SaveAs((savedir+"/bkg_match.eps").c_str());
//   canvas5->Write();

//   fhistos->Close();

// }

// void makeHistos_Fj_gen_pt_4plots(bool save = false, bool display = false){
//   string dir = "allChi_noMinFatjetPt_noMjBtagCondition";
//   string fsig = "RadionToHH_4b_M-800_TuneZ2star_8TeV-Madgraph_pythia6_R12_r15_minPt0_Nobtagmjcondition_AllChi_mc_subjets";
//   string fbkg = "ZPrimeToTTJets_M1000GeV_W10GeV_TuneZ2star_8TeV-madgraph-tauola_R12_r15_minPt0_Nobtagmjcondition_AllChi_mc_subjets";
//   string postfix = "dRmax12_NoGenPtCut_NoFjPtCut_AllChi";

//   string var = "Fj_pt";
//   string var_gen = "gen_pt";
//   double xbin = 50; double xmin = 0; double xmax = 1000;

//   string cut1 = "";
//   string cut2 = "Fj_chi>0";
//   string loose_cut1 = cut1;  string loose_cut2 = cut2;
//   string medium_cut1;string medium_cut2;
//   if(cut1==""){medium_cut1 = "dR_match<0.2";} else {medium_cut1 = ("dR_match<0.2&&"+cut1).c_str();}  ;
//   if(cut2==""){medium_cut2 = "dR_match<0.2";} else {medium_cut2 = ("dR_match<0.2&&"+cut2).c_str();}  ;
//   string tight_cut1;string tight_cut2;
//   if(cut1==""){tight_cut1 = "dR_match<0.05";} else {tight_cut1 = ("dR_match<0.05&&"+cut1).c_str();}  ;
//   if(cut2==""){tight_cut2 = "dR_match<0.05";} else {tight_cut2 = ("dR_match<0.05&&"+cut2).c_str();}  ;

//   Color_t color1= kBlue;
//   Color_t color2 = kGreen+1;

//   TFile *f_l = new TFile((dir+"/"+"fMatch_"+fsig+"_"+postfix+".root").c_str());

//   //loose match
//   TH1D* h_fj_l = PartonMatch_1D(dir,f_l,fsig,var,loose_cut1,xbin,xmin,xmax,postfix,color1,1,save);
//   TH1D* h_gen_l = PartonMatch_1D(dir,f_l,fsig,var_gen,loose_cut1,xbin,xmin,xmax,postfix,color2,1,save);
//   TH1D* h_fj_l_2 = PartonMatch_1D(dir,f_l,fsig,var,loose_cut2,xbin,xmin,xmax,postfix,color1,2,save);
//   TH1D* h_gen_l_2 = PartonMatch_1D(dir,f_l,fsig,var_gen,loose_cut2,xbin,xmin,xmax,postfix,color2,2,save);

//   //medium match
//   TH1D* h_fj_m = PartonMatch_1D(dir,f_l,fsig,var,medium_cut1,xbin,xmin,xmax,postfix,color1,1,save);
//   TH1D* h_gen_m = PartonMatch_1D(dir,f_l,fsig,var_gen,medium_cut1,xbin,xmin,xmax,postfix,color2,1,save);
//   TH1D* h_fj_m_2 = PartonMatch_1D(dir,f_l,fsig,var,medium_cut2,xbin,xmin,xmax,postfix,color1,2,save);
//   TH1D* h_gen_m_2 = PartonMatch_1D(dir,f_l,fsig,var_gen,medium_cut2,xbin,xmin,xmax,postfix,color2,2,save);

//   //tight match
//   TH1D* h_fj_t = PartonMatch_1D(dir,f_l,fsig,var,tight_cut1,xbin,xmin,xmax,postfix,color1,1,save);
//   TH1D* h_gen_t = PartonMatch_1D(dir,f_l,fsig,var_gen,tight_cut1,xbin,xmin,xmax,postfix,color2,1,save);
//   TH1D* h_fj_t_2 = PartonMatch_1D(dir,f_l,fsig,var,tight_cut2,xbin,xmin,xmax,postfix,color1,2,save);
//   TH1D* h_gen_t_2 = PartonMatch_1D(dir,f_l,fsig,var_gen,tight_cut2,xbin,xmin,xmax,postfix,color2,2,save);

//   //---create canvas---

//   TCanvas* canvas_l = new TCanvas("loose matching","loose matching",600,600);
//   TCanvas* canvas_m = new TCanvas("medium matching","medium matching",600,600);
//   TCanvas* canvas_t = new TCanvas("tight matching","tight matching",600,600);

//   //cout<<"Creating "<< dir+"/"+"PartonMatch_makeHistos_Fj_gen_pt.root"<< endl;
//   //TFile *fhistos = new TFile((dir+"/"+"PartonMatch_makeHistos_Fj_gen_pt.root").c_str(),"RECREATE");

//   gStyle->SetOptStat("nemrou");

//  //--------loose-------
//   canvas_l->cd();
//   h_fj_l->SetStats(0);
//   h_gen_l->SetStats(0);
//   h_fj_l_2->SetStats(0);
//   h_gen_l_2->SetStats(0);
//   h_gen_l->DrawNormalized();
//   h_fj_l->DrawNormalized("SAME");
//   h_gen_l_2->DrawNormalized("SAME");
//   h_fj_l_2->DrawNormalized("SAME");
//   leg = new TLegend(0.6,0.65,0.9,0.85);
//   leg->SetFillStyle(0);
//   leg->SetBorderSize(0);
//   leg->AddEntry(h_fj_l,("fj "+cut1).c_str(),"L");
//   leg->AddEntry(h_gen_l,("gen "+cut1).c_str(),"L");
//   leg->AddEntry(h_fj_l_2,("fj "+cut2).c_str(),"L");
//   leg->AddEntry(h_gen_l_2,("gen "+cut2).c_str(),"L");
//   leg->Draw("SAME");
//   gPad->Update();
//   if(save)canvas_l->SaveAs((savedir+"/loose_match"+"_"+var+".eps").c_str());

//   //--------medium-------
//   canvas_m->cd();
//   h_fj_m->SetStats(0);
//   h_gen_m->SetStats(0);
//   h_fj_m_2->SetStats(0);
//   h_gen_m_2->SetStats(0);
//   h_gen_m->DrawNormalized();
//   h_fj_m->DrawNormalized("SAME");
//   h_gen_m_2->DrawNormalized("SAME");
//   h_fj_m_2->DrawNormalized("SAME");
//   leg = new TLegend(0.6,0.65,0.9,0.85);
//   leg->SetFillStyle(0);
//   leg->SetBorderSize(0);
//   leg->AddEntry(h_fj_m,("fj "+cut1).c_str(),"L");
//   leg->AddEntry(h_gen_m,("gen "+cut1).c_str(),"L");
//   leg->AddEntry(h_fj_m_2,("fj "+cut2).c_str(),"L");
//   leg->AddEntry(h_gen_m_2,("gen "+cut2).c_str(),"L");
//   leg->Draw("SAME");
//   gPad->Update();
//   if(save)canvas_m->SaveAs((savedir+"/medium_match"+"_"+var+".eps").c_str());

//   //--------tight-------
//   canvas_t->cd();
//   h_fj_t->SetStats(0);
//   h_gen_t->SetStats(0);
//   h_fj_t_2->SetStats(0);
//   h_gen_t_2->SetStats(0);
//   h_gen_t->DrawNormalized();
//   h_fj_t->DrawNormalized("SAME");
//   h_gen_t_2->DrawNormalized("SAME");
//   h_fj_t_2->DrawNormalized("SAME");
//   leg = new TLegend(0.6,0.65,0.9,0.85);
//   leg->SetFillStyle(0);
//   leg->SetBorderSize(0);
//   leg->AddEntry(h_fj_t,("fj "+cut1).c_str(),"L");
//   leg->AddEntry(h_gen_t,("gen "+cut1).c_str(),"L");
//   leg->AddEntry(h_fj_t_2,("fj "+cut2).c_str(),"L");
//   leg->AddEntry(h_gen_t_2,("gen "+cut2).c_str(),"L");
//   leg->Draw("SAME");
//   gPad->Update();
//   if(save)canvas_t->SaveAs((savedir+"/tight_match"+"_"+var+".eps").c_str());

// }

void makeHistos_Fj_gen_pt_2plots(bool save = false, std::string dir="", std::string fsig="", std::string cut="", double xbin=50, double xmin=0, double xmax=100, std::string postfix=""){

  string var = "Fj_pt";
  string var_gen = "gen_pt";
  string xlabel = "p_{T}";

  string loose_cut = cut;
  string medium_cut; if(cut==""){medium_cut = "dR_match<0.2";} else {medium_cut = ("dR_match<0.2&&"+cut).c_str();}  ;
  string tight_cut; if(cut==""){tight_cut = "dR_match<0.05";} else {tight_cut = ("dR_match<0.05&&"+cut).c_str();}  ;

  Color_t color1= kBlue;  Color_t color2 = kGreen+1;
  int linestyle1 = 1 ;int linestyle2 = 1;

  TFile *f_l = new TFile((dir+"/"+"fMatch_"+fsig+"_"+postfix+".root").c_str());

  //loose match
  TH1D* h_fj_l = PartonMatch_1D(dir,f_l,fsig,var,loose_cut,xbin,xmin,xmax,xlabel,postfix,color1,linestyle1,save);
  TH1D* h_gen_l = PartonMatch_1D(dir,f_l,fsig,var_gen,loose_cut,xbin,xmin,xmax,xlabel,postfix,color2,linestyle2,save);

  //medium match
  TH1D* h_fj_m = PartonMatch_1D(dir,f_l,fsig,var,medium_cut,xbin,xmin,xmax,xlabel,postfix,color1,linestyle1,save);
  TH1D* h_gen_m = PartonMatch_1D(dir,f_l,fsig,var_gen,medium_cut,xbin,xmin,xmax,xlabel,postfix,color2,linestyle2,save);

  //tight match
  TH1D* h_fj_t = PartonMatch_1D(dir,f_l,fsig,var,tight_cut,xbin,xmin,xmax,xlabel,postfix,color1,linestyle1,save);
  TH1D* h_gen_t = PartonMatch_1D(dir,f_l,fsig,var_gen,tight_cut,xbin,xmin,xmax,xlabel,postfix,color2,linestyle2,save);

  //---create canvas---

  TCanvas* canvas_l = new TCanvas("loose matching","loose matching",600,600);
  TCanvas* canvas_m = new TCanvas("medium matching","medium matching",600,600);
  TCanvas* canvas_t = new TCanvas("tight matching","tight matching",600,600);

  gStyle->SetOptStat("nemrou");

  Double_t norm1;
  Double_t norm2;

 //--------loose-------
  canvas_l->cd();

  norm1 = h_fj_l->GetEntries();
  h_fj_l->Scale(1/norm1);
  norm2 = h_gen_l->GetEntries();
  h_gen_l->Scale(1/norm2);

  if(h_fj_l->GetMaximum()>h_gen_l->GetMaximum()){
    h_fj_l->Draw();
    h_gen_l->Draw("SAME");
  }
  else{
    h_gen_l->Draw();
    h_fj_l->Draw("SAME");
  }
  leg = new TLegend(0.5,0.65,0.75,0.75);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h_fj_l,"fatjet","L");
  leg->AddEntry(h_gen_l,"gen","L");
  leg->Draw("SAME");

  TPaveStats *tps1 = (TPaveStats*) h_fj_l->FindObject("stats");
  tps1->SetTextColor(color1);
  double X1 = tps1->GetX1NDC();
  double Y1 = tps1->GetY1NDC();
  double X2 = tps1->GetX2NDC();
  double Y2 = tps1->GetY2NDC();

  TPaveStats *tps2 = (TPaveStats*) h_gen_l->FindObject("stats");
  tps2->SetTextColor(color2);
  tps2->SetX1NDC(X1);
  tps2->SetX2NDC(X2);
  tps2->SetY1NDC(Y1-(Y2-Y1));
  tps2->SetY2NDC(Y1);

  gPad->Update();
  if(save)canvas_l->SaveAs((savedir+"/fj_gen_2plots_loose_match"+"_"+fsig+"_"+var+"_"+cut+".eps").c_str());

  //--------medium-------
  canvas_m->cd();

  norm1 = h_fj_m->GetEntries();
  h_fj_m->Scale(1/norm1);
  norm2 = h_gen_m->GetEntries();
  h_gen_m->Scale(1/norm2);

  if(h_fj_m->GetMaximum()>h_gen_m->GetMaximum()){
    h_fj_m->Draw();
    h_gen_m->Draw("SAME");
  }
  else{
    h_gen_m->Draw();
    h_fj_m->Draw("SAME");
  }
  leg = new TLegend(0.5,0.65,0.75,0.75);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h_fj_m,"fatjet","L");
  leg->AddEntry(h_gen_m,"gen","L");
  leg->Draw("SAME");

  TPaveStats *tps1_m = (TPaveStats*) h_fj_m->FindObject("stats");
  tps1_m->SetTextColor(color1);
  X1 = tps1_m->GetX1NDC();
  Y1 = tps1_m->GetY1NDC();
  X2 = tps1_m->GetX2NDC();
  Y2 = tps1_m->GetY2NDC();

  TPaveStats *tps2_m = (TPaveStats*) h_gen_m->FindObject("stats");
  tps2_m->SetTextColor(color2);
  tps2_m->SetX1NDC(X1);
  tps2_m->SetX2NDC(X2);
  tps2_m->SetY1NDC(Y1-(Y2-Y1));
  tps2_m->SetY2NDC(Y1);

  gPad->Update();
  if(save)canvas_m->SaveAs((savedir+"/fj_gen_2plots_medium_match"+"_"+fsig+"_"+var+"_"+cut+".eps").c_str());

  //--------tight-------
  canvas_t->cd();

  norm1 = h_fj_t->GetEntries();
  h_fj_t->Scale(1/norm1);
  norm2 = h_gen_t->GetEntries();
  h_gen_t->Scale(1/norm2);

  if(h_fj_t->GetMaximum()>h_gen_t->GetMaximum()){
    h_fj_t->Draw();
    h_gen_t->Draw("SAME");
  }
  else{
    h_gen_t->Draw();
    h_fj_t->Draw("SAME");
  }
  leg = new TLegend(0.5,0.65,0.75,0.75);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h_fj_t,"fatjet","L");
  leg->AddEntry(h_gen_t,"gen","L");
  leg->Draw("SAME");

  TPaveStats *tps1_t = (TPaveStats*) h_fj_t->FindObject("stats");
  tps1_t->SetTextColor(color1);
  X1 = tps1_t->GetX1NDC();
  Y1 = tps1_t->GetY1NDC();
  X2 = tps1_t->GetX2NDC();
  Y2 = tps1_t->GetY2NDC();

  TPaveStats *tps2_t = (TPaveStats*) h_gen_t->FindObject("stats");
  tps2_t->SetTextColor(color2);
  tps2_t->SetX1NDC(X1);
  tps2_t->SetX2NDC(X2);
  tps2_t->SetY1NDC(Y1-(Y2-Y1));
  tps2_t->SetY2NDC(Y1);

  gPad->Update();
  if(save)canvas_t->SaveAs((savedir+"/fj_gen_2plots_tight_match"+"_"+fsig+"_"+var+"_"+cut+".eps").c_str());

  if(save){
    TFile *fout = new TFile((savedir+"/PLOTS_fj_gen_2plots_tight_match"+"_"+fsig+"_"+var+"_"+cut+".root").c_str(),"RECREATE");
    fout->cd();
    h_fj_t->Write("h_fj_t");
    h_gen_t->Write("h_gen_t");
    fout->Close();
  }

}

// void makeHistos_Fj_gen_chi(bool save = false, bool display = false){
//   string dir = "allChi_noMinFatjetPt_noMjBtagCondition";
//   string fsig = "RadionToHH_4b_M-800_TuneZ2star_8TeV-Madgraph_pythia6_R12_r15_minPt0_Nobtagmjcondition_AllChi_mc_subjets";
//   string fbkg = "ZPrimeToTTJets_M1000GeV_W10GeV_TuneZ2star_8TeV-madgraph-tauola_R12_r15_minPt0_Nobtagmjcondition_AllChi_mc_subjets";
//   string var = "log(Fj_chi)";
//   double dR_tight = 0.05; double dR_med = 0.2;  double dR_loose = 1.2;
//   double xbin = 40; double xmin = -18; double xmax = -2;
//   string postfix;
//   string postfix1 = "NoGenPtCut_NoFjPtCut"; Color_t color1= kBlue;
//   string postfix2 = "NoGenPtCut_NoFjPtCut_InvalidChiCut"; Color_t color2 = kGreen+1;

//   //loose match
//   postfix = "dRmax12_"+postfix1;
//   TFile *f_l = new TFile((dir+"/"+"fMatch_"+fsig+"_"+postfix+".root").c_str());
//   TH1D* h_fj_l = PartonMatch_1D(dir,f_l,fsig,var,xbin,xmin,xmax,postfix,color1,1,save);
//   postfix = "dRmax12_"+postfix2;
//   TFile *f_l_2 = new TFile((dir+"/"+"fMatch_"+fsig+"_"+postfix+".root").c_str());
//   TH1D* h_fj_l_2 = PartonMatch_1D(dir,f_l_2,fsig,var,xbin,xmin,xmax,postfix,color1,2,save);

//   //medium match
//   postfix = "dRmax02_"+postfix1;
//   TFile *f_m = new TFile((dir+"/"+"fMatch_"+fsig+"_"+postfix+".root").c_str());
//   TH1D* h_fj_m = PartonMatch_1D(dir,f_m,fsig,var,xbin,xmin,xmax,postfix,color1,1,save);
//   postfix = "dRmax02_"+postfix2;
//   TFile *f_m_2 = new TFile((dir+"/"+"fMatch_"+fsig+"_"+postfix+".root").c_str());
//   TH1D* h_fj_m_2 = PartonMatch_1D(dir,f_m_2,fsig,var,xbin,xmin,xmax,postfix,color1,2,save);

//   //tight match
//   postfix = "dRmax005_"+postfix1;
//   TFile *f_t = new TFile((dir+"/"+"fMatch_"+fsig+"_"+postfix+".root").c_str());
//   TH1D* h_fj_t = PartonMatch_1D(dir,f_t,fsig,var,xbin,xmin,xmax,postfix,color1,1,save);
//   postfix = "dRmax005_"+postfix2;
//   TFile *f_t_2 = new TFile((dir+"/"+"fMatch_"+fsig+"_"+postfix+".root").c_str());
//   TH1D* h_fj_t_2 = PartonMatch_1D(dir,f_t_2,fsig,var,xbin,xmin,xmax,postfix,color1,2,save);


//   TCanvas* canvas_l = new TCanvas("loose matching","loose matching",600,600);
//   TCanvas* canvas_m = new TCanvas("medium matching","medium matching",600,600);
//   TCanvas* canvas_t = new TCanvas("tight matching","tight matching",600,600);

//   //cout<<"Creating "<< dir+"/"+"PartonMatch_makeHistos_Fj_gen_chi.root"<< endl;
//   //TFile *fhistos = new TFile((dir+"/"+"PartonMatch_makeHistos_Fj_gen_chi.root").c_str(),"RECREATE");

//   gStyle->SetOptStat("nemrou");

//   //--------loose-----------
//   canvas_l->cd();
//   h_fj_l->SetStats(0);
//   h_fj_l_2->SetStats(0);
//   h_fj_l->DrawNormalized();
//   h_fj_l_2->DrawNormalized("SAME");
//   leg = new TLegend(0.6,0.65,0.9,0.85);
//   leg->SetFillStyle(0);
//   leg->SetBorderSize(0);
//   leg->AddEntry(h_fj_l,("fj - "+postfix1).c_str(),"L");
//   leg->AddEntry(h_fj_l_2,("fj - "+postfix2).c_str(),"L");
//   leg->Draw("SAME");
//   gPad->Update();
//   if(save)canvas_l->SaveAs((savedir+"/loose_match"+"_logChi"+".eps").c_str());

//   //--------medium-----------
//   canvas_m->cd();
//   h_fj_m->SetStats(0);
//   h_fj_m_2->SetStats(0);
//   h_fj_m->DrawNormalized();
//   h_fj_m_2->DrawNormalized("SAME");
//   leg = new TLegend(0.6,0.65,0.9,0.85);
//   leg->SetFillStyle(0);
//   leg->SetBorderSize(0);
//   leg->AddEntry(h_fj_m,("fj - "+postfix1).c_str(),"L");
//   leg->AddEntry(h_fj_m_2,("fj - "+postfix2).c_str(),"L");
//   leg->Draw("SAME");
//   gPad->Update();
//   if(save)canvas_m->SaveAs((savedir+"/medium_match"+"_logChi"+".eps").c_str());

//   //--------tight-----------
//   canvas_t->cd();
//   h_fj_t->SetStats(0);
//   h_fj_t_2->SetStats(0);
//   h_fj_t->DrawNormalized();
//   h_fj_t_2->DrawNormalized("SAME");
//   leg = new TLegend(0.6,0.65,0.9,0.85);
//   leg->SetFillStyle(0);
//   leg->SetBorderSize(0);
//   leg->AddEntry(h_fj_t,("fj - "+postfix).c_str(),"L");
//   leg->AddEntry(h_fj_t_2,("fj - "+postfix).c_str(),"L");
//   leg->Draw("SAME");
//   gPad->Update();
//   if(save)canvas_t->SaveAs((savedir+"/tight_match"+"_logChi"+".eps").c_str());

// }

void makeHistos_1plot(std::string dir, std::string fname, std::string var, std::string cut, double xbin, double xmin, double xmax,std::string xlabel, std::string postfix,Color_t color = kBlue, int linestyle = 1, bool save = false, bool saveroot = false ){
  TFile *f = new TFile((dir+"/"+"fMatch_"+fname+"_"+postfix+".root").c_str());
  TH1D* h_s = PartonMatch_1D(dir,f,fname,var,cut,xbin,xmin,xmax,xlabel,postfix,color,linestyle,save,saveroot);
}

void  makeHistos_sig_bkg_2plots(std::string dir, std::string fsig, std::string fbkg, std::string var, std::string cut, double xbin, double xmin, double xmax, std::string xlabel, bool save = false, bool isLeg = true){

  string postfix = "dRmax08_NoGenPtCut_NoFjPtCut_AllChi";

  string loose_cut = cut;
  string medium_cut; if(cut==""){medium_cut = "dR_match<0.2";} else {medium_cut = ("dR_match<0.2&&"+cut).c_str();}  ;
  string tight_cut; if(cut==""){tight_cut = "dR_match<0.05";} else {tight_cut = ("dR_match<0.05&&"+cut).c_str();}  ;

  Color_t color1= kBlue;
  Color_t color2 = kRed;

  TFile *fs = new TFile((dir+"/"+"fMatch_"+fsig+"_"+postfix+".root").c_str());
  TFile *fb = new TFile((dir+"/"+"fMatch_"+fbkg+"_"+postfix+".root").c_str());

  //tight match
  TH1D* h_s = PartonMatch_1D(dir,fs,fsig,var,tight_cut,xbin,xmin,xmax,xlabel,postfix,color1,1,save);
  TH1D* h_b = PartonMatch_1D(dir,fb,fbkg,var,tight_cut,xbin,xmin,xmax,xlabel,postfix,color2,1,save);

  TCanvas* canvas_t = new TCanvas("tight matching","tight matching",600,600);

  gStyle->SetOptStat("nemrou");

  Double_t norm1;
  Double_t norm2;

  //--------tight-------
  canvas_t->cd();

  norm1 = h_s->GetEntries();
  h_s->Scale(1/norm1);
  norm2 = h_b->GetEntries();
  h_b->Scale(1/norm2);

  if(h_s->GetMaximum() > h_b->GetMaximum()){
    h_s->Draw();
    h_b->Draw("SAME");
  }
  else {
    h_b->Draw();
    h_s->Draw("SAME");
  }

  leg = new TLegend(0.55,0.65,0.85,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h_s,"RadionHH","L");
  leg->AddEntry(h_b,"Z'->ttbar","L");
  leg->Draw("SAME");

  double X1,Y1,X2,Y2;

  TPaveStats *tps1_t = (TPaveStats*) h_s->FindObject("stats");
  tps1_t->SetTextColor(color1);
  X1 = tps1_t->GetX1NDC();
  Y1 = tps1_t->GetY1NDC();
  X2 = tps1_t->GetX2NDC();
  Y2 = tps1_t->GetY2NDC();

  TPaveStats *tps2_t = (TPaveStats*) h_b->FindObject("stats");
  tps2_t->SetTextColor(color2);
  tps2_t->SetX1NDC(X1);
  tps2_t->SetX2NDC(X2);
  tps2_t->SetY1NDC(Y1-(Y2-Y1));
  tps2_t->SetY2NDC(Y1);

  if(isLeg==false){
    h_s->SetStats(isLeg);
    h_b->SetStats(isLeg);
  }

  gPad->Update();
  if(var=="log(Fj_chi)")var = "logChi";
  if(save)canvas_t->SaveAs((savedir+"/sig_bkg_2plots_tight_match"+"_"+var+"_"+cut+".eps").c_str());

}

void makeHistos_gen_2plots(std::string dir, std::string fname, std::string var, std::string var_gen, std::string cut, double xbin, double xmin, double xmax, std::string xlabel,std::string leg1, std::string leg2, bool save = false){

  string postfix = "dRmax08_NoGenPtCut_NoFjPtCut_AllChi";

  string loose_cut = cut;
  string medium_cut; if(cut==""){medium_cut = "dR_match<0.2";} else {medium_cut = ("dR_match<0.2&&"+cut).c_str();}  ;
  string tight_cut; if(cut==""){tight_cut = "dR_match<0.05";} else {tight_cut = ("dR_match<0.05&&"+cut).c_str();}  ;

  Color_t color1= kBlue;
  Color_t color2 = kGreen+1;

  TFile *f = new TFile((dir+"/"+"fMatch_"+fname+"_"+postfix+".root").c_str());

  //tight match
  TH1D* h_s = PartonMatch_1D(dir,f,fname,var,tight_cut,xbin,xmin,xmax,xlabel,postfix,color1,1,save);
  TH1D* h_b = PartonMatch_1D(dir,f,fname,var_gen,tight_cut,xbin,xmin,xmax,xlabel,postfix,color2,2,save);

  TCanvas* canvas_t = new TCanvas("tight matching","tight matching",600,600);

  gStyle->SetOptStat("nemrou");

  Double_t norm1;
  Double_t norm2;

  //--------tight-------
  canvas_t->cd();

  norm1 = h_s->GetEntries();
  h_s->Scale(1/norm1);
  norm2 = h_b->GetEntries();
  h_b->Scale(1/norm2);

  if(h_s->GetMaximum() > h_b->GetMaximum()){
    h_s->Draw();
    h_b->Draw("SAME");
  }
  else {
    h_b->Draw();
    h_s->Draw("SAME");
  }

  leg = new TLegend(0.55,0.65,0.85,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h_s,leg1.c_str(),"L");
  leg->AddEntry(h_b,leg2.c_str(),"L");
  leg->Draw("SAME");

  double X1,Y1,X2,Y2;

  TPaveStats *tps1_t = (TPaveStats*) h_s->FindObject("stats");
  tps1_t->SetTextColor(color1);
  X1 = tps1_t->GetX1NDC();
  Y1 = tps1_t->GetY1NDC();
  X2 = tps1_t->GetX2NDC();
  Y2 = tps1_t->GetY2NDC();

  TPaveStats *tps2_t = (TPaveStats*) h_b->FindObject("stats");
  tps2_t->SetTextColor(color2);
  tps2_t->SetX1NDC(X1);
  tps2_t->SetX2NDC(X2);
  tps2_t->SetY1NDC(Y1-(Y2-Y1));
  tps2_t->SetY2NDC(Y1);

  gPad->Update();
  if(var=="log(Fj_chi)")var = "logChi";
  if(save)canvas_t->SaveAs((savedir+"/sig_bkg_2plots_tight_match"+"_"+var+"_"+cut+".eps").c_str());

}

void Alakazam(){
  string dir ="rootfiles";
  string deltaHiggsMass;
  string fsig;
  string fbkg;
  double dRmax = 0.8;
  double MjCone = 0.15;
  string postfix= "dRmax08_NoGenPtCut_NoFjPtCut_AllChi";

  double xbin; double xmin; double xmax; string xlabel;
  double ybin; double ymin; double ymax; string ylabel;
  string var; string var_gen; string var1; string var2;
  string cut;
  bool save; bool saveroot;

  //TFile *fout = new TFile("f_histo.root","RECREATE");

  deltaHiggsMass = "HiggsWin20";
  //deltaHiggsMass = "HiggsWin20_WRONGtagrate35";
  fsig = "Rad_HHto4b_M800_13TeV_AOD_R08_r015_"+deltaHiggsMass+"_mc_subjets";
  fbkg = "ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola_R08_r015_"+deltaHiggsMass+"_mc_subjets";

  var = "dR_match";
  cut = "";
  xbin = 40; xmin = 0; xmax = 0.8; xlabel = "#Delta R matching";
  save = true;
  makeHistos_1plot(dir,fsig,var,cut,xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,cut,xbin,xmin,xmax,xlabel,postfix,kRed,1,save);


  //Fj vs Gen pt distribution
  xbin = 50;  xmin = 0;  xmax = 1000;
  save = true;
  makeHistos_Fj_gen_pt_2plots(save, dir, fsig, "", xbin, xmin, xmax, postfix);
  makeHistos_Fj_gen_pt_2plots(save, dir, fsig, "Fj_chi>0", xbin, xmin, xmax, postfix);
  makeHistos_Fj_gen_pt_2plots(save, dir, fsig, "Fj_chi<=0", xbin, xmin, xmax, postfix);

  makeHistos_Fj_gen_pt_2plots(save, dir, fsig, "Fj_pt>300", xbin, xmin, xmax, postfix);
  makeHistos_Fj_gen_pt_2plots(save, dir, fsig, "Fj_pt>300&&Fj_chi>0", xbin, xmin, xmax, postfix);
  makeHistos_Fj_gen_pt_2plots(save, dir, fsig, "Fj_pt>300&&Fj_chi<=0", xbin, xmin, xmax, postfix);

  xbin = 50;  xmin = 0;  xmax = 1000;
  save = true;
  makeHistos_Fj_gen_pt_2plots(save, dir, fbkg, "", xbin, xmin, xmax, postfix);
  makeHistos_Fj_gen_pt_2plots(save, dir, fbkg, "Fj_chi>0", xbin, xmin, xmax, postfix);
  makeHistos_Fj_gen_pt_2plots(save, dir, fbkg, "Fj_chi<=0", xbin, xmin, xmax, postfix);

  makeHistos_Fj_gen_pt_2plots(save, dir, fbkg, "Fj_pt>300", xbin, xmin, xmax, postfix);
  makeHistos_Fj_gen_pt_2plots(save, dir, fbkg, "Fj_pt>300&&Fj_chi>0", xbin, xmin, xmax, postfix);
  makeHistos_Fj_gen_pt_2plots(save, dir, fbkg, "Fj_pt>300&&Fj_chi<=0", xbin, xmin, xmax, postfix);


  //Sig vs Bkg
  var = "log(Fj_chi)" ;  xlabel = "Log(#chi)";
  xbin = 50;  xmin = -22;  xmax = -2;
  save = true;
  makeHistos_sig_bkg_2plots(dir,fsig,fbkg,var,"Fj_chi>0",xbin,xmin,xmax,xlabel,save,1);
  makeHistos_sig_bkg_2plots(dir,fsig,fbkg,var,"Fj_nMj>=2&&Fj_chi>0",xbin,xmin,xmax,xlabel,save,1);
  makeHistos_sig_bkg_2plots(dir,fsig,fbkg,var,"Fj_nMj>=2&&Fj_nBtagMj>=2&&Fj_chi>0",xbin,xmin,xmax,xlabel,save,1);
  makeHistos_sig_bkg_2plots(dir,fsig,fbkg,var,"Fj_pt>300&&Fj_chi>0",xbin,xmin,xmax,xlabel,save,1);
  makeHistos_sig_bkg_2plots(dir,fsig,fbkg,var,"Fj_pt>300&&Fj_nMj>=2&&Fj_nBtagMj>=2&&Fj_chi>0",xbin,xmin,xmax,xlabel,save,1);

  var = "Fj_pt" ;  xlabel = "Fatjet p_{T}";
  xbin = 50;  xmin = 0;  xmax = 1000;
  save = true;
  makeHistos_sig_bkg_2plots(dir,fsig,fbkg,var,"",xbin,xmin,xmax,xlabel,save,1);
  makeHistos_sig_bkg_2plots(dir,fsig,fbkg,var,"Fj_nMj>=2",xbin,xmin,xmax,xlabel,save,1);
  makeHistos_sig_bkg_2plots(dir,fsig,fbkg,var,"Fj_nMj>=2&&Fj_nBtagMj>=2",xbin,xmin,xmax,xlabel,save,1);
  makeHistos_sig_bkg_2plots(dir,fsig,fbkg,var,"Fj_pt>300&&Fj_nMj>=2&&Fj_nBtagMj>=2",xbin,xmin,xmax,xlabel,save,1);

  var = "Fj_nMj" ;  xlabel = "# of Microjets";
  xbin = 10;  xmin = -0.5;  xmax = 9.5;
  save = true;
  makeHistos_sig_bkg_2plots(dir,fsig,fbkg, var, cut="",xbin,xmin,xmax,xlabel,save);
  makeHistos_sig_bkg_2plots(dir,fsig,fbkg, var, cut="Fj_chi>0",xbin,xmin,xmax,xlabel,save);
  makeHistos_sig_bkg_2plots(dir,fsig,fbkg, var, cut="Fj_chi<=0",xbin,xmin,xmax,xlabel,save);

  makeHistos_sig_bkg_2plots(dir,fsig,fbkg, var, cut="Fj_pt>300",xbin,xmin,xmax,xlabel,save);
  makeHistos_sig_bkg_2plots(dir,fsig,fbkg, var, cut="Fj_pt>300&&Fj_chi>0",xbin,xmin,xmax,xlabel,save);
  makeHistos_sig_bkg_2plots(dir,fsig,fbkg, var, cut="Fj_pt>300&&Fj_chi<=0",xbin,xmin,xmax,xlabel,save);

  var = "Fj_nBtagMj" ;  xlabel = "# of Btagged Microjets";
  xbin = 10;  xmin = -0.5;  xmax = 9.5;
  save = true;
  makeHistos_sig_bkg_2plots(dir,fsig,fbkg, var, cut="",xbin,xmin,xmax,xlabel,save);
  makeHistos_sig_bkg_2plots(dir,fsig,fbkg, var, cut="Fj_chi>0",xbin,xmin,xmax,xlabel,save);
  makeHistos_sig_bkg_2plots(dir,fsig,fbkg, var, cut="Fj_chi<=0",xbin,xmin,xmax,xlabel,save);

  makeHistos_sig_bkg_2plots(dir,fsig,fbkg, var, cut="Fj_pt>300",xbin,xmin,xmax,xlabel,save);
  makeHistos_sig_bkg_2plots(dir,fsig,fbkg, var, cut="Fj_pt>300&&Fj_chi>0",xbin,xmin,xmax,xlabel,save);
  makeHistos_sig_bkg_2plots(dir,fsig,fbkg, var, cut="Fj_pt>300&&Fj_chi<=0",xbin,xmin,xmax,xlabel,save);

  var = "Mj_pt" ;  xlabel = "p_{T}";
  xbin = 50;  xmin = 0;  xmax = 400;
  save = true;
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var, cut="",xbin,xmin,xmax,xlabel,save);
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var, cut="Fj_chi>0",xbin,xmin,xmax,xlabel,save);
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var, cut="Fj_chi<=0",xbin,xmin,xmax,xlabel,save);
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var, cut="Mj_isBtag==1",xbin,xmin,xmax,xlabel,save);
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var, cut="Fj_chi>0&&Mj_isBtag==1",xbin,xmin,xmax,xlabel,save);
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var, cut="Fj_chi<=0&Mj_isBtag==1",xbin,xmin,xmax,xlabel,save);

  var = "Mj_isBtag" ;  xlabel = "Microjet Btag status";
  xbin = 5;  xmin = -2.5;  xmax = 2.5;
  save = true;
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var, cut="",xbin,xmin,xmax,xlabel,save);
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var, cut="Fj_chi>0",xbin,xmin,xmax,xlabel,save);
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var, cut="Fj_chi<=0",xbin,xmin,xmax,xlabel,save);

  //Fj 2D

  var1 = "Fj_nMj"; var2 = "log(Fj_chi)";
  xbin  = 10; xmin =-0.5; xmax=9.5; xlabel = "# of Microjets";
  ybin  = 50; ymin =-22; ymax=-2; ylabel = "Log #chi";
  save  = true;
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"dR_match<0.05",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"dR_match<0.05",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&dR_match<0.05",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&dR_match<0.05",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);

  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2Z",postfix,save);
  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"dR_match<0.05",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"dR_match<0.05",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);
  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"Fj_pt>300&&dR_match<0.05",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"Fj_pt>300&&dR_match<0.05",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);


  var1 = "Fj_nBtagMj"; var2 = "log(Fj_chi)";
  xbin  = 10; xmin =-0.5; xmax=9.5; xlabel = "# of Btagged Microjets";
  ybin  = 50; ymin =-22; ymax=-2; ylabel = "Log #chi";
  save= true;
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"dR_match<0.05",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"dR_match<0.05",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&dR_match<0.05",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&dR_match<0.05",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);

  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);
  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"dR_match<0.05",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"dR_match<0.05",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);
  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"Fj_pt>300&&dR_match<0.05",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"Fj_pt>300&&dR_match<0.05",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);


  var1 = "Fj_nMj"; var2 = "Fj_pt";
  xbin  = 10; xmin =-0.5; xmax=9.5; xlabel = "# of Microjets";
  ybin  = 50; ymin = 0; ymax=1000; ylabel = "Fatjet p_{T}";
  save= true;
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);

  Plot_PartonMatch_2D(dir,fsig,var1,var2,"dR_match<0.05",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"dR_match<0.05",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"dR_match<0.05&&Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"dR_match<0.05&&Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"dR_match<0.05&&Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"dR_match<0.05&&Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);

  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);
  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);
  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);

  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"dR_match<0.05",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"dR_match<0.05",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);
  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"dR_match<0.05&&Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"dR_match<0.05&&Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);
  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"dR_match<0.05&&Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"dR_match<0.05&&Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);
  //
  ybin  = 50; ymin =200; ymax=800; ylabel = "Fatjet p_{T}";
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&dR_match<0.05",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&dR_match<0.05",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&dR_match<0.05&&Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&dR_match<0.05&&Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&dR_match<0.05&&Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&dR_match<0.05&&Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);

  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"Fj_pt>300&&dR_match<0.05",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"Fj_pt>300&&dR_match<0.05",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);
  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"Fj_pt>300&&dR_match<0.05&&Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"Fj_pt>300&&dR_match<0.05&&Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);
  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"Fj_pt>300&&dR_match<0.05&&Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"Fj_pt>300&&dR_match<0.05&&Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);

  var1 = "Fj_nBtagMj";  var2 = "Fj_pt";
  xbin  = 10; xmin =-0.5; xmax=9.5; xlabel = "# of Btagged Microjets";
  ybin  = 50; ymin =0; ymax=1000; ylabel = "Fatjet p_{T}";
  save=true;
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);

  Plot_PartonMatch_2D(dir,fsig,var1,var2,"dR_match<0.05",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"dR_match<0.05",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"dR_match<0.05&&Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"dR_match<0.05&&Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"dR_match<0.05&&Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"dR_match<0.05&&Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);

  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);
  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);
  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);

  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"dR_match<0.05",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"dR_match<0.05",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);
  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"dR_match<0.05&&Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"dR_match<0.05&&Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);
  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"dR_match<0.05&&Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fbkg,var1,var2,"dR_match<0.05&&Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);

  ybin  = 50; ymin =200; ymax=800; ylabel = "Fatjet p_{T}";
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&dR_match<0.05",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&dR_match<0.05",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&dR_match<0.05&&Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&dR_match<0.05&&Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&dR_match<0.05&&Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&dR_match<0.05&&Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);

  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&dR_match<0.05",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&dR_match<0.05",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&dR_match<0.05&&Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&dR_match<0.05&&Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&dR_match<0.05&&Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&dR_match<0.05&&Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2",postfix,save);


  //Matched Mj stuff

  var1 = "Mj_pt"; var2 = "Mj_isBtag";
  xbin  = 50; xmin =0; xmax=500; xlabel = "Microjet p_{T}";
  ybin  = 5; ymin =-2.5; ymax=2.5; ylabel = "Microjets Btag status";
  save = true;
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);

  Plot_PartonMatch_2D(dir,fsig,var1,var2,"",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2Z",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2Z",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2Z",postfix,save);

  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);

  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2Z",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2Z",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2Z",postfix,save);

  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&dR_match<0.05",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&dR_match<0.05&&Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&dR_match<0.05&&Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);

  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&dR_match<0.05",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2Z",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&dR_match<0.05&&Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2Z",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&dR_match<0.05&&Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2Z",postfix,save);

  var2 = "Mj_pt"; var1 = "Mj_isBtag";
  ybin  = 50; ymin =0; ymax=500; ylabel = "(Matched_{#DeltaR<0.04}) Microjet p_{T}";
  xbin  = 5; xmin =-2.5; xmax=2.5; xlabel = "(Matched) Microjets Btag status";
  save = true;
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Mj_dR>0&&Mj_dR<0.04",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Mj_dR>0&&Mj_dR<0.04&&Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Mj_dR>0&&Mj_dR<0.04&&Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);

  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Mj_dR>0&&Mj_dR<0.04",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2Z",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Mj_dR>0&&Mj_dR<0.04&&Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2Z",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Mj_dR>0&&Mj_dR<0.04&&Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2Z",postfix,save);

  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&Mj_dR>0&&Mj_dR<0.04",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&Mj_dR>0&&Mj_dR<0.04&&Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&Mj_dR>0&&Mj_dR<0.04&&Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);

  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&Mj_dR>0&&Mj_dR<0.04",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2Z",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&Mj_dR>0&&Mj_dR<0.04&&Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2Z",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&Mj_dR>0&&Mj_dR<0.04&&Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2Z",postfix,save);

  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04&&Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04&&Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);

  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2Z",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04&&Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2Z",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04&&Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2Z",postfix,save);

  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&Fj_nMj>=2&&Fj_nBtagMj>=2&&dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&Fj_nMj>=2&&Fj_nBtagMj>=2&&dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04&&Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&Fj_nMj>=2&&Fj_nBtagMj>=2&&dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04&&Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"COLZ",postfix,save);

  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&Fj_nMj>=2&&Fj_nBtagMj>=2&&dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2Z",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&Fj_nMj>=2&&Fj_nBtagMj>=2&&dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04&&Fj_chi>0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2Z",postfix,save);
  Plot_PartonMatch_2D(dir,fsig,var1,var2,"Fj_pt>300&&Fj_nMj>=2&&Fj_nBtagMj>=2&&dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04&&Fj_chi<=0",xbin,xmin,xmax,ybin,ymin,ymax,xlabel,ylabel,"LEGO2Z",postfix,save);

  var = "Mj_gen_matched_pdgID" ;
  xbin = 31;  xmin = -15.5;  xmax = 15.5;   xlabel = "(matched) gen pdgID";
  save = true;
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var, cut="",xbin,xmin,xmax,xlabel,save);
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var, cut="Mj_dR>0",xbin,xmin,xmax,xlabel,save);
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var, cut="Mj_dR>0&&Fj_chi>0",xbin,xmin,xmax,xlabel,save);
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var, cut="Mj_dR>0&&Fj_chi<=0",xbin,xmin,xmax,xlabel,save);
  xbin = 61;  xmin = -30.5;  xmax = 30.5;   xlabel = "(matched) gen pdgID";
  save = save;
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var, cut="",xbin,xmin,xmax,xlabel,save);
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var, cut="Mj_dR>0",xbin,xmin,xmax,xlabel,save);
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var, cut="Mj_dR>0&&Fj_chi>0",xbin,xmin,xmax,xlabel,save);
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var, cut="Mj_dR>0&&Fj_chi<=0",xbin,xmin,xmax,xlabel,save);

  var = "Mj_isBtag";
  xbin = 5; xmin = -2.5; xmax = 2.5; xlabel = "(Matching) Microjet Btag status";
  save = true;
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var, cut="",xbin,xmin,xmax,xlabel,save);
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var, cut="Mj_dR>0",xbin,xmin,xmax,xlabel,save);
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var, cut="Mj_dR>0&&Mj_isBtag==1",xbin,xmin,xmax,xlabel,save);
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var, cut="Mj_dR>0&&Mj_isBtag==-1",xbin,xmin,xmax,xlabel,save);
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var, cut="Mj_dR>0&&Mj_isBtag==1&&abs(Mj_gen_matched_pdgID)==5",xbin,xmin,xmax,xlabel,save); //NEED TO FIX THIS!!!!!!!!!!!
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var, cut="Mj_dR>0&&Mj_isBtag==-1&&abs(Mj_gen_matched_pdgID)==5",xbin,xmin,xmax,xlabel,save);
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var, cut="Mj_dR>0&&Mj_isBtag==1&&abs(Mj_gen_matched_pdgID)!=5",xbin,xmin,xmax,xlabel,save);
  makeHistos_sig_bkg_2plots(dir, fsig, fbkg, var, cut="Mj_dR>0&&Mj_isBtag==-1&&abs(Mj_gen_matched_pdgID)!=5",xbin,xmin,xmax,xlabel,save);

  var = "Mj_dR";
  xbin = 45; xmin = 0; xmax = 0.15; xlabel = "Microjet-parton #Delta R matching";
  save = true; saveroot = false;
  makeHistos_1plot(dir,fsig,var,"",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save,saveroot);
  makeHistos_1plot(dir,fbkg,var,"",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  var = "Mj_dR_SV";
  xbin = 45; xmin = 0; xmax = 0.15; xlabel = "Microjet-IVF SV #Delta R matching";
  save = true; saveroot = false;
  makeHistos_1plot(dir,fsig,var,"",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save,saveroot);
  makeHistos_1plot(dir,fbkg,var,"",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  var = "Mj_dR_SV_gen";
  xbin = 45; xmin = 0; xmax = 0.15; xlabel = "IVF SV-genParticle #Delta R";
  save = true; saveroot = false;
  makeHistos_1plot(dir,fsig,var,"",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save,saveroot);
  makeHistos_1plot(dir,fbkg,var,"",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  var = "Mj_pt"; var_gen = "Mj_gen_matched_pt";
  xbin = 50; xmin = 0; xmax = 500; xlabel = "p_{T}";
  save = true;
  makeHistos_gen_2plots(dir,fsig,var,var_gen,"Mj_dR>0",xbin,xmin,xmax,xlabel,"Microjet","Gen",save);
  makeHistos_gen_2plots(dir,fbkg,var,var_gen,"Mj_dR>0",xbin,xmin,xmax,xlabel,"Microjet","Gen",save);
  makeHistos_gen_2plots(dir,fsig,var,var_gen,"Mj_dR>0&&Mj_dR<0.04",xbin,xmin,xmax,xlabel,"Microjet","Gen",save);
  makeHistos_gen_2plots(dir,fbkg,var,var_gen,"Mj_dR>0&&Mj_dR<0.04",xbin,xmin,xmax,xlabel,"Microjet","Gen",save);

  //Mj study  sequence

  var = "Mj_pt";
  xbin = 50; xmin = 0; xmax = 500; xlabel = "Microjet p_{T}";
  save = true;
  makeHistos_1plot(dir,fsig,var,"",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"Mj_dR>0",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"Mj_dR>0&&Mj_isBtag==1",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_isBtag==1",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"Mj_dR>0&&Mj_isBtag==-1",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_isBtag==-1",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"Mj_dR>0&&Mj_isBtag==1&&abs(Mj_gen_matched_pdgID)==5",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_isBtag==1&&abs(Mj_gen_matched_pdgID)==5",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"Mj_dR>0&&Mj_isBtag==-1&&abs(Mj_gen_matched_pdgID)==5",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_isBtag==-1&&abs(Mj_gen_matched_pdgID)==5",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"Mj_dR>0&&Mj_isBtag==1&&abs(Mj_gen_matched_pdgID)!=5",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_isBtag==1&&abs(Mj_gen_matched_pdgID)!=5",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_isBtag==1&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"Mj_dR>0&&Mj_isBtag==-1&&abs(Mj_gen_matched_pdgID)!=5",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_isBtag==-1&&abs(Mj_gen_matched_pdgID)!=5",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);
  //
  makeHistos_1plot(dir,fsig,var,"Mj_dR>0&&Mj_dR<0.04",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_dR<0.04",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_dR<0.04&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==1",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==1",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==-1",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==-1",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==1&&abs(Mj_gen_matched_pdgID)==5",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==1&&abs(Mj_gen_matched_pdgID)==5",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==-1&&abs(Mj_gen_matched_pdgID)==5",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==-1&&abs(Mj_gen_matched_pdgID)==5",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==1&&abs(Mj_gen_matched_pdgID)!=5",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==1&&abs(Mj_gen_matched_pdgID)!=5",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==1&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==-1&&abs(Mj_gen_matched_pdgID)!=5",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==-1&&abs(Mj_gen_matched_pdgID)!=5",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);
  //
  makeHistos_1plot(dir,fsig,var,"dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==1",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==1",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==-1",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==-1",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==1&&abs(Mj_gen_matched_pdgID)==5",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==1&&abs(Mj_gen_matched_pdgID)==5",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==-1&&abs(Mj_gen_matched_pdgID)==5",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==-1&&abs(Mj_gen_matched_pdgID)==5",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==1&&abs(Mj_gen_matched_pdgID)!=5",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==1&&abs(Mj_gen_matched_pdgID)!=5",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);
  makeHistos_1plot(dir,fbkg,var,"dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==1&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==-1&&abs(Mj_gen_matched_pdgID)!=5",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==-1&&abs(Mj_gen_matched_pdgID)!=5",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);


  var = "Mj_gen_matched_pdgID";
  xbin = 51; xmin = -25.5; xmax = 25.5; xlabel = "(matched) gen pdgID";
  save = true;
  makeHistos_1plot(dir,fsig,var,"Mj_dR>0",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"Mj_dR>0&&Mj_isBtag==1",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_isBtag==1",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"Mj_dR>0&&Mj_isBtag==-1",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_isBtag==-1",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"Mj_dR>0&&Mj_dR<0.04",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_dR<0.04",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_dR<0.04&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==1",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==1",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==-1",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==-1",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==1&&abs(Mj_gen_matched_pdgID)!=5",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==1&&abs(Mj_gen_matched_pdgID)!=5",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==1&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==-1&&abs(Mj_gen_matched_pdgID)!=5",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==-1&&abs(Mj_gen_matched_pdgID)!=5",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);
  //
  makeHistos_1plot(dir,fsig,var,"dR_match<0.05&&Mj_dR>0",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"dR_match<0.05&&Mj_dR>0",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"dR_match<0.05&&Mj_dR>0&&Mj_isBtag==1",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"dR_match<0.05&&Mj_dR>0&&Mj_isBtag==1",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"dR_match<0.05&&Mj_dR>0&&Mj_isBtag==-1",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"dR_match<0.05&&Mj_dR>0&&Mj_isBtag==-1",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==1",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==1",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==-1",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==-1",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==1&&abs(Mj_gen_matched_pdgID)!=5",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==1&&abs(Mj_gen_matched_pdgID)!=5",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);
  makeHistos_1plot(dir,fbkg,var,"dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==1&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  makeHistos_1plot(dir,fsig,var,"dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==-1&&abs(Mj_gen_matched_pdgID)!=5",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"dR_match<0.05&&Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==-1&&abs(Mj_gen_matched_pdgID)!=5",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);

  var = "Mj_gen_matched_motherID";
  xbin = 51; xmin = -25.5; xmax = 25.5; xlabel = "MotherID of (matched) of gen pdgID";
  save = true;

  makeHistos_1plot(dir,fsig,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==1&&abs(Mj_gen_matched_pdgID)!=5",xbin,xmin,xmax,xlabel,postfix,kBlue,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==1&&abs(Mj_gen_matched_pdgID)!=5",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);
  makeHistos_1plot(dir,fbkg,var,"Mj_dR>0&&Mj_dR<0.04&&Mj_isBtag==1&&abs(Mj_gen_matched_pdgID)!=5&&abs(Mj_gen_matched_pdgID)!=4",xbin,xmin,xmax,xlabel,postfix,kRed,1,save);


}

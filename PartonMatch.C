
using namespace std;

void PartonMatch(){
  //{
  bool display = 0;

  TFile *f = new TFile("RadionHH_M800_R12_r15_correctIVFmatch_mc_subjets.root");

  TDirectoryFile *d = f->GetDirectory("btagana");
  TTree *t = d->Get("ttree");
  TDirectoryFile *df = f->GetDirectory("btaganaSubJets");
  TTree *tf = df->Get("ttree");

  TCanvas *c = new TCanvas("c","SD fatjet higgs matching",800,600);
  TCanvas *c2 = new TCanvas("c2","SD fatjet higgs matching",800,600);
  TH2D *h = new TH2D("h","h",50,-18,-2,50,0,0.6);

  const int nEvent = t->GetEntries();
  int nMatchMax = 0;
  vector<int> iEventOverMatch;

  int nGenPruned;
  const int nGenPrunedMax = 19;
  int GenPruned_pdgID[nGenPrunedMax];
  float GenPruned_eta[nGenPrunedMax]; //simple hack to avoid making different size arrays every event loop. Run calcMax.C
  float GenPruned_phi[nGenPrunedMax];

  int nFj;
  const int nFjMax=5;
  float Fj_eta[nFjMax];
  float Fj_phi[nFjMax];
  float Fj_chi[nFjMax];

  t->SetBranchAddress("nGenPruned",&nGenPruned);
  t->SetBranchAddress("GenPruned_pdgID",&GenPruned_pdgID);
  t->SetBranchAddress("GenPruned_eta",&GenPruned_eta);
  t->SetBranchAddress("GenPruned_phi",&GenPruned_phi);

  tf->SetBranchAddress("FatJetInfo.nJet",&nFj);
  tf->SetBranchAddress("FatJetInfo.Jet_eta",&Fj_eta);
  tf->SetBranchAddress("FatJetInfo.Jet_phi",&Fj_phi);
  tf->SetBranchAddress("FatJetInfo.Jet_SD_chi",&Fj_chi);

  //loop over events
  if(display)cout << endl;
  for (int i =0 ; i<nEvent;i++){
    //for (int i =0 ; i<2;i++){
    t->GetEntry(i);
    tf->GetEntry(i);
    if(display)cout << endl;
    if(display)cout << "============  entry : "<< i << ", nGenPruned = "<< nGenPruned << ", nFatJet = "<< nFj <<"=============="<< endl;
    if(display)cout << endl;

    //loop over fatjets
    int nMatch=0;
    for(int j=0; j < nFj; j++){
      if(display)cout<< "Fatjet no. "<< j << " : Fatjet_eta = " << Fj_eta[j] << endl;
      if(display)cout<< "           "<<     "    Fatjet_phi = " << Fj_phi[j] << endl;
      if(display)cout<< "           "<<     "    Fatjet_chi = " << Fj_chi[j] << endl;
      if(display)cout<<endl;

      //loop over GenPruned
      for(int k=2; k < nGenPruned; k++){
	if(GenPruned_pdgID[k]==25){
	  if(display)cout<< "        GenPruned no. "<< k << " : GenPruned_pdgID = " << GenPruned_pdgID[k] << endl;
	  if(display)cout<< "                      "<<     "    GenPruned_eta = " << GenPruned_eta[k] << endl;
	  if(display)cout<< "                      "<<     "    GenPruned_phi = " << GenPruned_phi[k] << endl;

	  double dR = deltaR(GenPruned_eta[k], GenPruned_phi[k], Fj_eta[j], Fj_phi[j]);
	  if(display)cout<< "        " << j<< "-"<<k<<", -------------------------------->  delta R = "<< dR ;// << endl;
	  if(dR<1.2){
	    if(display)cout<<"----> MATCH!! " << endl;
	    nMatch++;

	    if(Fj_chi[j]>0) h->Fill(log(Fj_chi[j]),dR); //fill 2D histo (chi, dR)

	  }

	  if(display)cout << endl;
	}
      }//end GenPruned loop
      if(nMatch>nMatchMax) nMatchMax = nMatch;
    }//end fatjet loop

    if (nMatch>2) iEventOverMatch.push_back(i);

  }//end event loop

  if(display)cout << "nMatchMax =" << nMatchMax << endl;
  if(display)cout << "nEventOverMatch =" << iEventOverMatch.size() << endl;
  if(display)cout << "EventOverMatch = " ;
  for(int l =0 ; l<iEventOverMatch.size(); l++) if(display)cout << iEventOverMatch[l] <<", " ;
  endl;


  gStyle->SetOptStat("nemrou");
  h->GetXaxis()->SetTitle("Log(#chi)");
  h->GetXaxis()->SetTitleOffset(1.3);
  h->GetYaxis()->SetTitle("#DeltaR");
  h->GetYaxis()->SetTitleOffset(1.2);
  h->SetTitle("");
  c->cd();
  //c->SetLogx();
  c->SetBottomMargin(0.12);
  c->SetRightMargin(0.3);
  h->Draw("COLZ");
  c2->cd();
  //c2->SetLogx();
  c2->SetBottomMargin(0.12);
  c2->SetRightMargin(0.3);
  h->Draw("LEGO2Z");

  c->SaveAs("Radion_fjHmatch_COLZ.eps");
  c2->SaveAs("Radion_fjHmatch_LEGO2Z.eps");
}


double deltaR(double eta1, double phi1, double eta2, double phi2){
  double dEta = eta1 - eta2;

  double dPhi = phi1 - phi2;
  while (dPhi > TMath::Pi()) dPhi -= 2*TMath::Pi();
  while (dPhi <= -TMath::Pi()) dPhi += 2*TMath::Pi();

  double dR = sqrt(dEta*dEta + dPhi*dPhi);
  return dR;
}


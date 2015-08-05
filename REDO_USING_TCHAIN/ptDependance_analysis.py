import os, sys, math
from ROOT import *


def efficiency1D(Tfpass, Tftotal, Tfpass_qcd, Tftotal_qcd, ptRange, var, fRebinX, ):

    h1_Pass = Tfpass.Get(var);
    h1_Total = Tftotal.Get(var);

    h_qcd_pass = Tfpass_qcd[0].Get(var)
    h_qcd_total = Tftotal_qcd[0].Get(var)

    for i in range(len(Tfpass_qcd)):
    	if (i==len(ptRange)-1): continue 
        h_qcd_pass.Add(Tfpass_qcd[i+1].Get(var))
        h_qcd_total.Add(Tftotal_qcd[i+1].Get(var))

    h1_Pass.Rebin(fRebinX);
    h1_Total.Rebin(fRebinX);

    h_qcd_pass.Rebin(fRebinX);
    h_qcd_total.Rebin(fRebinX);

    c = TCanvas("c", "",1000,800);
    c.cd();

    c.SetGridx();
    c.SetGridy();

    print h1_Pass.GetSize();
    print h1_Total.GetSize();

    g_sig = TGraphAsymmErrors();
    g_sig.Divide(h1_Pass, h1_Total,"cl=0.683 b(1,1) mode")
    # g_sig.Divide(h1_Pass, h1_Total,"cp")
    g_sig.SetLineWidth(2);
    g_sig.SetLineColor(kBlue+2);
    g_sig.SetMarkerSize(1.);
    g_sig.SetMarkerStyle(20);
    g_sig.SetMarkerColor(2);
    g_sig.GetXaxis().SetRangeUser(300,1200)
    g_sig.GetHistogram().SetMaximum(0.4)
    g_sig.GetHistogram().SetMinimum(0.)
    g_sig.SetTitle("")
    g_sig.GetXaxis().SetTitle("p_{T} [GeV]")
    g_sig.GetXaxis().SetTitleOffset(1.1)
    g_sig.GetYaxis().SetTitle("Efficiency")
    g_sig.GetYaxis().SetTitleOffset(1.2)


    g_bkg = TGraphAsymmErrors();
    g_bkg.Divide(h_qcd_pass, h_qcd_total,"cl=0.683 b(1,1) mode")
    # g_bkg.Divide(h_qcd_pass, h_qcd_total,"cp")
    g_bkg.SetLineWidth(2);
    g_bkg.SetLineColor(kRed);
    g_bkg.SetMarkerSize(1.);
    g_bkg.SetMarkerStyle(20);
    g_bkg.SetMarkerColor(kBlue+2);
    g_bkg.GetXaxis().SetRangeUser(300,1200)

    g_sig.Draw("AP");
    g_bkg.Draw("Psame");

    c.Update()
    c.Modified()
    # gPad.Update()

    c.SaveAs("temp.eps")


Tftotal = TFile("rootfiles/ROC_analyzer_ptDependanceCalc_total/ROC_analyzer_Rad_ptDependanceCalc_total.root")
Tfpass = TFile("rootfiles/ROC_analyzer_ptDependanceCalc/ROC_analyzer_Rad_ptDependanceCalc.root")

ptRange = []
ptRange.append("300")
ptRange.append("470")
ptRange.append("600")
ptRange.append("800")
ptRange.append("1000")
ptRange.append("1400")
ptRange.append("1800")
ptRange.append("2400")
ptRange.append("3200")

Tfpass_qcd =[]
Tftotal_qcd =[]
    
for i in xrange(len(ptRange)):
	Tfpass_qcd.append(TFile("rootfiles/ROC_analyzer_ptDependanceCalc/ROC_analyzer_QCD%s_ptDependanceCalc.root"%ptRange[i]))
	Tftotal_qcd.append(TFile("rootfiles/ROC_analyzer_ptDependanceCalc_total/ROC_analyzer_QCD%s_ptDependanceCalc_total.root" %ptRange[i]))

var = "pt"
fRebinX = 10

efficiency1D(Tfpass,Tftotal,Tfpass_qcd, Tftotal_qcd, ptRange, var,fRebinX)

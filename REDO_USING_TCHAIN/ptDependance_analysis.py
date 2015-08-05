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
    g_sig.SetMarkerStyle(24);
    g_sig.SetMarkerColor(2);
    g_sig.GetXaxis().SetRangeUser(300,1500)
    g_sig.GetHistogram().SetMaximum(1.1)
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
    g_bkg.SetMarkerStyle(24);
    g_bkg.SetMarkerColor(kBlue+2);
    g_bkg.GetXaxis().SetRangeUser(300,1500)

    g_sig.Draw("AP");
    g_bkg.Draw("Psame");


    legend = TLegend(.5,.8,.86,.85)
    # legend = TLegend(.16,.17,.3,.25)
    legend.SetBorderSize(0)
    legend.SetFillColor(0)
    legend.SetFillStyle(0)
    legend.SetTextFont(42)
    legend.SetTextSize(0.03)
    legend.AddEntry(g_sig,"log #chi - Rad->HH (M800-2000)",'lep')
    legend.AddEntry(g_bkg,"log #chi - QCD",'lep')
    legend.Draw()

    l1 = TLatex()
    l1.SetTextAlign(13)
    l1.SetTextFont(42)
    l1.SetNDC()
    l1.SetTextSize(0.04)

    #l1.DrawLatex(0.14+0.03,0.85, "R(0.8+1.0+1.6+2.0 TeV)")

    l1.SetTextAlign(12)
    l1.SetTextSize(0.045)
    l1.SetTextFont(42)
#     l1.DrawLatex(0.72,0.96, "CMS simulation (13 TeV)")
    l1.DrawLatex(0.55,0.96, "CMS simulation (13 TeV)")


    l1.SetTextFont(42)
    l1.SetTextSize(0.03)
    l1.SetTextAlign(22);
    l1.DrawLatex(0.25,0.85, "70 % signal efficiency")
    l1.DrawLatex(0.25,0.85-0.04, "95 GeV < M_{pruned} < 155 GeV")
    l1.DrawLatex(0.25,0.85-0.04-0.04, "300 < p_{T} < 10000 GeV")



    c.Update()
    c.Modified()
    # gPad.Update()

    c.SaveAs("plots/ptDependence_pt300-10000_chiCut15.eps")
    c.SaveAs("plots/ptDependence_pt300-10000_chiCut15.pdf")


Tftotal = TFile("rootfiles/ROC_analyzer_ptDependanceCalc_total/ROC_analyzer_Rad_ptDependanceCalc_pt300-10000_total.root")
Tfpass = TFile("rootfiles/ROC_analyzer_ptDependanceCalc/ROC_analyzer_Rad_ptDependanceCalc_pt300-10000_chiCut.root")

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
	Tfpass_qcd.append(TFile("rootfiles/ROC_analyzer_ptDependanceCalc/ROC_analyzer_QCD%s_ptDependanceCalc_pt300-10000_chiCut.root"%ptRange[i]))
	Tftotal_qcd.append(TFile("rootfiles/ROC_analyzer_ptDependanceCalc_total/ROC_analyzer_QCD%s_ptDependanceCalc_pt300-10000_total.root" %ptRange[i]))

var = "pt"
fRebinX = 20

efficiency1D(Tfpass,Tftotal,Tfpass_qcd, Tftotal_qcd, ptRange, var,fRebinX)

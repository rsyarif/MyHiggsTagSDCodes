import os, sys, math
from ROOT import *

dir = "rootfiles"
prefix = "ROC_analyzer"
#category = "_pt300-400"
postfix = "validChi"

def makeROC(var,xmin, xmax,direction,category):

	path = dir+"/"+prefix+category+"_"+postfix+"/"

	gStyle.SetOptStat("nemrou")

	fSave = TFile("temp/TEMP_ROC_"+var+".root","recreate")

	ch1 = TFile(path+"ROC_analyzer_Rad"+category+".root")
	ch2_1 = TFile(path+"ROC_analyzer_QCD300"+category+".root")
	ch2_2 = TFile(path+"ROC_analyzer_QCD470"+category+".root")
	ch2_3 = TFile(path+"ROC_analyzer_QCD600"+category+".root")
	ch2_4 = TFile(path+"ROC_analyzer_QCD800"+category+".root")
	ch2_5 = TFile(path+"ROC_analyzer_QCD1000"+category+".root")
	ch2_7 = TFile(path+"ROC_analyzer_QCD1400"+category+".root")		
	ch2_8 = TFile(path+"ROC_analyzer_QCD1800"+category+".root")
	ch2_9 = TFile(path+"ROC_analyzer_QCD2400"+category+".root")
	ch2_10 = TFile(path+"ROC_analyzer_QCD3200"+category+".root")
	ch3 = TFile(path+"ROC_analyzer_Zpr"+category+".root")	

	hs = ch1.Get(var)
	hb1 = ch2_1.Get(var)
	hb1.Add(ch2_2.Get(var))
	hb1.Add(ch2_3.Get(var))
	hb1.Add(ch2_4.Get(var))
	hb1.Add(ch2_5.Get(var))
	hb1.Add(ch2_7.Get(var))
	hb1.Add(ch2_8.Get(var))
	hb1.Add(ch2_9.Get(var))
	hb1.Add(ch2_10.Get(var))

	hb2 = ch3.Get(var)

	hs.GetXaxis().SetTitle(var+"_hs")
	hb1.GetXaxis().SetTitle(var+"_hb1")
	hb2.GetXaxis().SetTitle(var+"_hb2")

	if not os.path.exists("plots/"+prefix+category+"_"+postfix):os.makedirs("plots/"+prefix+category+"_"+postfix)

	c1 = TCanvas("c1","c1",600,600)
	hs.Draw()
	c1.SaveAs("plots/"+prefix+category+"_"+postfix+"/hs_"+var+category+".pdf")
	c1.SaveAs("plots/"+prefix+category+"_"+postfix+"/hs_"+var+category+".eps")

	c2 = TCanvas("c2","c2",600,600)
	hb1.Draw()
	c2.SaveAs("plots/"+prefix+category+"_"+postfix+"/hb1_"+var+category+".pdf")
	c2.SaveAs("plots/"+prefix+category+"_"+postfix+"/hb1_"+var+category+".eps")

	c3 = TCanvas("c3","c3",600,600)
	hb2.Draw()
	c3.SaveAs("plots/"+prefix+category+"_"+postfix+"/hb2_"+var+category+".pdf")	
	c3.SaveAs("plots/"+prefix+category+"_"+postfix+"/hb2_"+var+category+".eps")	

	hs.SetName("hs_Rad"+var)
	hb1.SetName("hb1_QCD"+var)
	hb2.SetName("hb2_Zpr"+var)


	fSave.cd()

	hs.Write()
	hb1.Write()
	hb2.Write()
	
	size_hs = hs.GetSize()
	size_hb1 = hb1.GetSize()
	size_hb2 = hb2.GetSize()

	if size_hs!=size_hb1 or size_hs!=size_hb2:
		print "bins - hs=%i, hb1=%i, hb2=%i"%(size_hs, size_hb1, size_hb2)
		print "number of bins don't match!"
		return

	denom_hs = hs.Integral(0,size_hs-1)
	denom_hb1 = hb1.Integral(0,size_hs-1)
	denom_hb2 = hb2.Integral(0,size_hs-1)
	#denom_hb2 = 1000.

	print "var = ",var,", denom = ", denom_hs, ", ",denom_hb1, ", ", denom_hb2

	#print "denom_hb2 = %f" %denom_hb2

	c4 = TCanvas("c4","c4",600,600)

	gr = TGraph(size_hs-2)

	gr.SetName("gr")
	#gr.SetTitle("QCD")
  	gr.SetLineColor(kBlue)
  	gr.SetLineWidth(2)
  	gr.GetXaxis().SetTitle("Eff_{sig}")
  	gr.GetYaxis().SetTitle("1-Eff_{bkg}")
  	gr.GetXaxis().SetRangeUser(0.,1.)
  	gr.SetFillStyle(0)
  	gr.SetMaximum(1.)
  	gr.SetMinimum(0.)
	gr.SetTitle("ROC Curves")

	c5 = TCanvas("c5","c5",600,600)

	gr2 = TGraph(size_hs-2)

	gr2.SetName("gr2")
	#gr2.SetTitle("Zpr")
  	gr2.SetLineColor(kBlue)
  	gr2.SetLineWidth(2)
  	gr2.GetXaxis().SetTitle("Eff_{sig}")
  	gr2.GetYaxis().SetTitle("1-Eff_{bkg}")
  	gr2.GetXaxis().SetRangeUser(0.,1.)
  	gr2.SetFillStyle(0)
  	gr2.SetMaximum(1.)
  	gr2.SetMinimum(0.)
	gr2.SetTitle("ROC Curves")

	gPad.Update()

	inc = (xmax-xmin) /  (size_hs - 2)
	for i in xrange(size_hs-1):
		#print "i = %i" %i
		num_hs = hs.Integral(i,size_hs-1)
		num_hb1 = hb1.Integral(i,size_hs-1)
		num_hb2 = hb2.Integral(i,size_hs-1)

		eff_hs = num_hs/denom_hs if direction==1 else (1. -  (num_hs/denom_hs))
# 		print "%f/%f = %f" %(num_hs,denom_hs, eff_hs)
		eff_hb1 = num_hb1/denom_hb1 if direction==1 else (1. -  (num_hb1/denom_hb1))
# 		print "1 - (%f/%f) = %f" %(num_hb1,denom_hb1, 1-eff_hb1)
		eff_hb2 = num_hb2/denom_hb2 if direction==1 else (1. -  (num_hb2/denom_hb2))

# 		if (eff_hs >0.85 and eff_hs<0.95): print "(%f, %f)" %(eff_hs, 1-eff_hb2)
# 		if (eff_hs >0.65 and eff_hs<0.85): print "(%f, %f)" %(eff_hs, 1-eff_hb2)
# 		if (eff_hs >0.45 and eff_hs<0.65): print "(%f, %f)" %(eff_hs, 1-eff_hb2)

		print "at i = ", i, "(", xmin+inc*i ,")", "eff_s = ", eff_hs, ", rej_b = ", 1-eff_hb1 

		gr.SetPoint(i,eff_hs,1-eff_hb1)
		gr2.SetPoint(i,eff_hs,1-eff_hb2)

	c4.cd()
	gr.Draw("APL")
	c5.cd()
	gr2.Draw("APL")
	
	gr.Write()
	gr2.Write()

	c4.SaveAs("plots/"+prefix+category+"_"+postfix+"/ROC_QCD_"+var+category+".pdf")
	c5.SaveAs("plots/"+prefix+category+"_"+postfix+"/ROC_Zpr_"+var+category+".pdf")
	c4.SaveAs("plots/"+prefix+category+"_"+postfix+"/ROC_QCD_"+var+category+".eps")
	c5.SaveAs("plots/"+prefix+category+"_"+postfix+"/ROC_Zpr_"+var+category+".eps")

	
	hs.Scale(1/hs.Integral(1,(hs.GetSize()-2)));
	hb1.Scale(1/hb1.Integral(1,(hb1.GetSize()-2)));
	hb2.Scale(1/hb2.Integral(1,(hb2.GetSize()-2)));

	c6 = TCanvas("c6","c6",600,600)
	
	c6.cd()
	
	hs.SetLineColor(kBlue)
	hs.SetLineWidth(2)
	hb1.SetLineColor(kGreen+2)
	hb1.SetLineStyle(9)
	hb1.SetLineWidth(2)
	hb2.SetLineColor(kRed)
	
	h = THStack("hStack","");
  	h.Add(hs,"sames");
  	h.Add(hb1,"sames");
  	h.Add(hb2,"sames");
  	h.Draw("nostack");
  	h.GetXaxis().SetTitle(var);

  	leg = TLegend(0.2,0.65,0.4,0.85);
  	leg.SetFillStyle(0);
  	leg.SetBorderSize(0);
  	leg.AddEntry(hs,"RadHH","L");
  	leg.AddEntry(hb2,"Z'ttbar","L");
  	leg.AddEntry(hb1,"incl. QCD","L");
  	leg.Draw("SAME");
  	
  	tps1 = hs.FindObject("stats");
  	tps1.SetTextColor(kBlue);
  	X1 = tps1.GetX1NDC();
  	Y1 = tps1.GetY1NDC();
  	X2 = tps1.GetX2NDC();
  	Y2 = tps1.GetY2NDC();
  	tps2 = hb1.FindObject("stats");
  	tps2.SetTextColor(kGreen+2);
  	tps2.SetX1NDC(X1);
  	tps2.SetX2NDC(X2);
  	tps2.SetY1NDC(Y1-(Y2-Y1));
  	tps2.SetY2NDC(Y1);
  	X1 = tps2.GetX1NDC();
  	Y1 = tps2.GetY1NDC();
  	X2 = tps2.GetX2NDC();
  	Y2 = tps2.GetY2NDC();
  	tps3 = hb2.FindObject("stats");
  	tps3.SetTextColor(kRed);
  	tps3.SetX1NDC(X1);
  	tps3.SetX2NDC(X2);
  	tps3.SetY1NDC(Y1-(Y2-Y1));
  	tps3.SetY2NDC(Y1);
  	
  	gPad.Update();
  	
  	c6.SaveAs("plots/"+prefix+category+"_"+postfix+"/superimpose_"+var+category+".pdf")
  	c6.SaveAs("plots/"+prefix+category+"_"+postfix+"/superimpose_"+var+category+".eps")

	h.Write()

	fSave.Write()
	fSave.Close()


def allROC(files, massCut, ptCut,category):
	c = TCanvas("c","c",600,600)
# 	c.SetLogy()
	c.SetGridy()
	c.SetGridx()


	f_logchi = TFile(files[0])
	f_tau21 = TFile(files[1])
	f_qvol = TFile(files[2])
		
	gr1 = f_logchi.Get("gr")
	gr3 = f_logchi.Get("gr2")

	gr2 = f_tau21.Get("gr")
	gr4 = f_tau21.Get("gr2")

	gr5 = f_qvol.Get("gr")
	gr6 = f_qvol.Get("gr2")

	gr1.SetTitle("log #chi - incl. QCD")
	gr3.SetTitle("log #chi - Zpr -> ttbar (M 1-2 TeV)")
	
	gr2.SetTitle("#tau_{2} / #tau_{1} - incl. QCD")
	gr4.SetTitle("#tau_{2} / #tau_{1} - Zpr -> ttbar (M 1-2 TeV)")
	
	gr5.SetTitle("qvol - incl. QCD")
	gr6.SetTitle("qvol - Zpr -> ttbar (M 1-2 TeV)")
	
	gr1.SetLineColor(kGreen+2)
	gr1.SetLineStyle(1)
	gr2.SetLineColor(kGreen+2)
	gr2.SetLineStyle(4)
	gr3.SetLineColor(kRed)
	gr3.SetLineStyle(1)
	gr4.SetLineColor(kRed)
	gr4.SetLineStyle(4)
# 	gr5.SetLineColor(kRed)
	gr5.SetLineColor(kGreen+2)
	gr5.SetLineStyle(9)
	gr6.SetLineColor(kRed)
	gr6.SetLineStyle(9)

	ROC = TMultiGraph("ROC","")
	ROC.Add(gr1)
	ROC.Add(gr2)
	ROC.Add(gr5)
	ROC.Add(gr3)
	ROC.Add(gr4)
	ROC.Add(gr6)

	ROC.Draw("APL")
	ROC.GetXaxis().SetTitle("Eff_{sig}")
	ROC.GetYaxis().SetTitle("1-Eff_{bkg}")
	ROC.GetXaxis().SetLimits(0.,1.)
	ROC.SetMaximum(1.)
	ROC.SetMinimum(0.)
# 	ROC.SetMinimum(1e-2)

	ROC.SetTitle("ROC Curves")

	c.BuildLegend(0.125,0.2,0.2+0.375,0.2+0.275)
# 	c.BuildLegend(0.125,0.2,0.2+0.2,0.2+0.15)

	
	infos =[]
	infos.append("signal: Rad->HH M800-2000")
	#info = "%i<M_{pruned}<%i GeV, %i<p_{T}<%i GeV" %(massCut[0],massCut[1],ptCut[0],ptCut[1])
	info = "%i<M_{pruned}<%i GeV, %i<p_{T}<%i GeV, #chi>0" %(massCut[0],massCut[1],ptCut[0],ptCut[1])
	infos.append(info) 
	
	latex = TLatex();
  	latex.SetNDC();
  	latex.SetTextSize(0.025);
  	latex.SetTextFont(82);
  	latex.SetTextAlign(22);
  	latex.DrawLatex(0.45, 0.15,infos[0]);

  	latex2 = TLatex();
  	latex2.SetNDC();
  	latex2.SetTextSize(0.025);
  	latex2.SetTextFont(82);
  	latex2.SetTextAlign(22);
  	latex2.DrawLatex(0.65, 0.88,infos[1]);
#   	latex2.DrawLatex(0.40, 0.65,infos[1]);

  	
  	title1 = "CMS Simulation, #sqrt{s} = 13 TeV";
  	cmslatex = TLatex();
  	latex.SetNDC();
  	latex.SetTextSize(0.035);
  	latex.SetTextFont(62);
  	latex.SetTextAlign(13);
  	latex.DrawLatex(0.42, 0.96, title1);

	gPad.Update()

	c.Update()
	c.Modified()
	c.SaveAs("plots/"+prefix+category+"_"+postfix+"/multiROC"+category+".pdf")
	c.SaveAs("plots/"+prefix+category+"_"+postfix+"/multiROC"+category+".eps")




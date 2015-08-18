from ROOT import *

def makeTGraph(fIn,varCut,color):
	f = TFile(fIn)
	tr = f.Get("ttree")

	grList = []

	htotal1 = TH1D("htotal1","htotal1",100,300,400)
	hpass1 = TH1D("hpass1","hpass1",100,300,400)
	tr.Draw("FatJetInfo.Jet_pt>>htotal1","FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_massGroomed>95&&FatJetInfo.Jet_massGroomed<155&&FatJetInfo.Jet_pt>300&&FatJetInfo.Jet_pt<400")
	tr.Draw("FatJetInfo.Jet_pt>>hpass1","FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_massGroomed>95&&FatJetInfo.Jet_massGroomed<155&&FatJetInfo.Jet_pt>300&&FatJetInfo.Jet_pt<400"+varCut[0])
	hpass1.Rebin(100)
	htotal1.Rebin(100)
	gr1 = TGraphAsymmErrors(hpass1,htotal1,"cl=0.683 b(1,1) mode")
	gr1.SetPointEXlow(0,50.)
	gr1.SetPointEXhigh(0,50.)
	gr1.SetLineColor(color)
	gr1.SetLineWidth(2)
	grList.append(gr1)

	htotal2 = TH1D("htotal2","htotal2",100,400,500)
	hpass2 = TH1D("hpass2","hpass2",100,400,500)
	tr.Draw("FatJetInfo.Jet_pt>>htotal2","FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_massGroomed>95&&FatJetInfo.Jet_massGroomed<155&&FatJetInfo.Jet_pt>400&&FatJetInfo.Jet_pt<500")
	tr.Draw("FatJetInfo.Jet_pt>>hpass2","FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_massGroomed>95&&FatJetInfo.Jet_massGroomed<155&&FatJetInfo.Jet_pt>400&&FatJetInfo.Jet_pt<500"+varCut[1])
	hpass2.Rebin(100)
	htotal2.Rebin(100)
	gr2 = TGraphAsymmErrors(hpass2,htotal2,"cl=0.683 b(1,1) mode")
	gr2.SetPointEXlow(0,50.)
	gr2.SetPointEXhigh(0,50.)
	gr2.SetLineColor(color)
	gr2.SetLineWidth(2)
	grList.append(gr2)

	htotal3 = TH1D("htotal3","htotal3",100,500,600)
	hpass3 = TH1D("hpass3","hpass3",100,500,600)
	tr.Draw("FatJetInfo.Jet_pt>>htotal3","FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_massGroomed>95&&FatJetInfo.Jet_massGroomed<155&&FatJetInfo.Jet_pt>500&&FatJetInfo.Jet_pt<600")
	tr.Draw("FatJetInfo.Jet_pt>>hpass3","FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_massGroomed>95&&FatJetInfo.Jet_massGroomed<155&&FatJetInfo.Jet_pt>500&&FatJetInfo.Jet_pt<600"+varCut[2])
	hpass3.Rebin(100)
	htotal3.Rebin(100)
	gr3 = TGraphAsymmErrors(hpass3,htotal3,"cl=0.683 b(1,1) mode")
	gr3.SetPointEXlow(0,50.)
	gr3.SetPointEXhigh(0,50.)
	gr3.SetLineColor(color)
	gr3.SetLineWidth(2)
	grList.append(gr3)

	htotal4 = TH1D("htotal4","htotal4",100,600,800)
	hpass4 = TH1D("hpass4","hpass4",100,600,800)
	tr.Draw("FatJetInfo.Jet_pt>>htotal4","FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_massGroomed>95&&FatJetInfo.Jet_massGroomed<155&&FatJetInfo.Jet_pt>600&&FatJetInfo.Jet_pt<800")
	tr.Draw("FatJetInfo.Jet_pt>>hpass4","FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_massGroomed>95&&FatJetInfo.Jet_massGroomed<155&&FatJetInfo.Jet_pt>600&&FatJetInfo.Jet_pt<800"+varCut[3])
	hpass4.Rebin(100)
	htotal4.Rebin(100)
	gr4 = TGraphAsymmErrors(hpass4,htotal4,"cl=0.683 b(1,1) mode")
	gr4.SetPointEXlow(0,100.)
	gr4.SetPointEXhigh(0,100.)
	gr4.SetLineColor(color)
	gr4.SetLineWidth(2)
	grList.append(gr4)

	htotal5 = TH1D("htotal5","htotal5",100,800,1000)
	hpass5 = TH1D("hpass5","hpass5",100,800,1000)
	tr.Draw("FatJetInfo.Jet_pt>>htotal5","FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_massGroomed>95&&FatJetInfo.Jet_massGroomed<155&&FatJetInfo.Jet_pt>800&&FatJetInfo.Jet_pt<1000")
	tr.Draw("FatJetInfo.Jet_pt>>hpass5","FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_massGroomed>95&&FatJetInfo.Jet_massGroomed<155&&FatJetInfo.Jet_pt>800&&FatJetInfo.Jet_pt<1000"+varCut[4])
	hpass5.Rebin(100)
	htotal5.Rebin(100)
	gr5 = TGraphAsymmErrors(hpass5,htotal5,"cl=0.683 b(1,1) mode")
	gr5.SetPointEXlow(0,100.)
	gr5.SetPointEXhigh(0,100.)
	gr5.SetLineColor(color)
	gr5.SetLineWidth(2)
	grList.append(gr5)

	htotal6 = TH1D("htotal6","htotal6",100,1000,1600)
	hpass6 = TH1D("hpass6","hpass6",100,1000,1600)
	tr.Draw("FatJetInfo.Jet_pt>>htotal6","FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_massGroomed>95&&FatJetInfo.Jet_massGroomed<155&&FatJetInfo.Jet_pt>1000&&FatJetInfo.Jet_pt<1600")
	tr.Draw("FatJetInfo.Jet_pt>>hpass6","FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_massGroomed>95&&FatJetInfo.Jet_massGroomed<155&&FatJetInfo.Jet_pt>1000&&FatJetInfo.Jet_pt<1600"+varCut[5])
	hpass6.Rebin(100)
	htotal6.Rebin(100)
	gr6 = TGraphAsymmErrors(hpass6,htotal6,"cl=0.683 b(1,1) mode")
	gr6.SetPointEXlow(0,300.)
	gr6.SetPointEXhigh(0,300.)
	gr6.SetLineColor(color)
	gr6.SetLineWidth(2)
	grList.append(gr6)


	return grList

def makeTGraphAll():

	grm = TMultiGraph()

	logchiCut = []
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-19.1")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-18.2")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-18.0")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-18.1")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-19.0")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-20.25")

	grList1 = makeTGraph("rootfiles/slimTree/slimTree_Rad.root",logchiCut,kBlue)

	for i in xrange(len(grList1)):
		grm.Add(grList1[i])


	logchiCut = []
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-17.05")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-16.2")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-15.9")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-15.85")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-16.23")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-17.25")

	grList2 = makeTGraph("rootfiles/slimTree/slimTree_Rad.root",logchiCut,kGreen)

	for i in xrange(len(grList2)):
		grm.Add(grList2[i])


	logchiCut = []
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-14.8")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-14.1")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-13.7")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-13.37")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-13.3")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-13.9")

	grList3 = makeTGraph("rootfiles/slimTree/slimTree_Rad.root",logchiCut,kRed)

	for i in xrange(len(grList3)):
		grm.Add(grList3[i])


	grm.SetMaximum(1.05)
	grm.SetMinimum(0.)
	grm.SetTitle("")


	c1 = TCanvas()
	c1.cd()
	c1.SetGridx()
	c1.SetGridy()
	grm.Draw("APL")

	grm.GetXaxis().SetLimits(200,1600)
	grm.GetXaxis().SetTitle("FatJet p_{T}")
	grm.GetYaxis().SetTitle("eff_{signal}")


	leg = TLegend(0.12,0.12,0.3,0.12+0.2)
	leg.AddEntry(grList1[0],"rej_{bkg} = 10%")
	leg.AddEntry(grList2[0],"rej_{bkg} = 50%")
	leg.AddEntry(grList3[0],"rej_{bkg} = 90%")
	leg.Draw()

	l1 = TLatex()
	l1.SetTextAlign(13)
	l1.SetTextFont(42)
	l1.SetNDC()
	l1.SetTextSize(0.04)

	l1.SetTextAlign(12)
	l1.SetTextSize(0.045)
	l1.SetTextFont(42)
	#     l1.DrawLatex(0.72,0.93, "CMS simulation (13 TeV)")
	l1.DrawLatex(0.75,0.94, "(13 TeV)")

	l1.SetTextAlign(11)
	l1.SetTextSize(0.045)
	l1.SetTextFont(61)
	l1.DrawLatex(0.1,0.93, "CMS")
	l1.SetTextFont(52)
	l1.DrawLatex(0.1+0.08,0.93, "simulation")


	l1.SetTextFont(42)
	l1.SetTextSize(0.035)
	l1.SetTextAlign(22);
	l1.DrawLatex(0.7,0.25, "95 GeV < M_{pruned} < 155 GeV")
	l1.DrawLatex(0.7,0.25-0.04, "#chi_{SD} > 0")

	c1.Update()
	c1.SaveAs("sigEff_vs_pt_slimTree_Rad_logChi.pdf")

makeTGraphAll()

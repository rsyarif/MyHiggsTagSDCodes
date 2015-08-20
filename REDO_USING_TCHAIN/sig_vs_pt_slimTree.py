from ROOT import *

def makeTGraph(fIn,varCut,color):
	f = TFile(fIn)
	tr = f.Get("ttree")

	debug = 0

	grList = []

	if (debug==1): print "-------------------------------------"
	if (debug==1): print ""

	if (debug==1): print "processing pt 300-400 GeV, ", varCut[0]
	htotal1 = TH1D("htotal1","htotal1",100,300,400)
	hpass1 = TH1D("hpass1","hpass1",100,300,400)
	ntotal = tr.Draw("FatJetInfo.Jet_pt>>htotal1","FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_massGroomed>95&&FatJetInfo.Jet_massGroomed<155&&FatJetInfo.Jet_pt>300&&FatJetInfo.Jet_pt<400")
	npass = tr.Draw("FatJetInfo.Jet_pt>>hpass1","FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_massGroomed>95&&FatJetInfo.Jet_massGroomed<155&&FatJetInfo.Jet_pt>300&&FatJetInfo.Jet_pt<400"+varCut[0])
	if (debug==1): print "ntotal = ", ntotal
	if (debug==1): print "npass = ", npass
	if (debug==1): print (npass*1.0) / (ntotal *1.0), "%" 
	hpass1.Rebin(100)
	htotal1.Rebin(100)
	gr1 = TGraphAsymmErrors(hpass1,htotal1,"cl=0.683 b(1,1) mode")
	gr1.SetPointEXlow(0,50.)
	gr1.SetPointEXhigh(0,50.)
	gr1.SetLineColor(color)
	gr1.SetLineWidth(2)
	grList.append(gr1)

	if (debug==1): print "processing pt 400-500 GeV, ", varCut[1]
	htotal2 = TH1D("htotal2","htotal2",100,400,500)
	hpass2 = TH1D("hpass2","hpass2",100,400,500)
	ntotal = tr.Draw("FatJetInfo.Jet_pt>>htotal2","FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_massGroomed>95&&FatJetInfo.Jet_massGroomed<155&&FatJetInfo.Jet_pt>400&&FatJetInfo.Jet_pt<500")
	npass = tr.Draw("FatJetInfo.Jet_pt>>hpass2","FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_massGroomed>95&&FatJetInfo.Jet_massGroomed<155&&FatJetInfo.Jet_pt>400&&FatJetInfo.Jet_pt<500"+varCut[1])
	if (debug==1): print "ntotal = ", ntotal
	if (debug==1): print "npass = ", npass
	if (debug==1): print (npass*1.0) / (ntotal *1.0), "%" 
	hpass2.Rebin(100)
	htotal2.Rebin(100)
	gr2 = TGraphAsymmErrors(hpass2,htotal2,"cl=0.683 b(1,1) mode")
	gr2.SetPointEXlow(0,50.)
	gr2.SetPointEXhigh(0,50.)
	gr2.SetLineColor(color)
	gr2.SetLineWidth(2)
	grList.append(gr2)

	if (debug==1): print "processing pt 500-600 GeV, ", varCut[2]
	htotal3 = TH1D("htotal3","htotal3",100,500,600)
	hpass3 = TH1D("hpass3","hpass3",100,500,600)
	ntotal = tr.Draw("FatJetInfo.Jet_pt>>htotal3","FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_massGroomed>95&&FatJetInfo.Jet_massGroomed<155&&FatJetInfo.Jet_pt>500&&FatJetInfo.Jet_pt<600")
	npass = tr.Draw("FatJetInfo.Jet_pt>>hpass3","FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_massGroomed>95&&FatJetInfo.Jet_massGroomed<155&&FatJetInfo.Jet_pt>500&&FatJetInfo.Jet_pt<600"+varCut[2])
	if (debug==1): print "ntotal = ", ntotal
	if (debug==1): print "npass = ", npass
	if (debug==1): print (npass*1.0) / (ntotal *1.0), "%" 
	hpass3.Rebin(100)
	htotal3.Rebin(100)
	gr3 = TGraphAsymmErrors(hpass3,htotal3,"cl=0.683 b(1,1) mode")
	gr3.SetPointEXlow(0,50.)
	gr3.SetPointEXhigh(0,50.)
	gr3.SetLineColor(color)
	gr3.SetLineWidth(2)
	grList.append(gr3)

	if (debug==1): print "processing pt 600-800 GeV, ", varCut[3]
	htotal4 = TH1D("htotal4","htotal4",100,600,800)
	hpass4 = TH1D("hpass4","hpass4",100,600,800)
	ntotal = tr.Draw("FatJetInfo.Jet_pt>>htotal4","FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_massGroomed>95&&FatJetInfo.Jet_massGroomed<155&&FatJetInfo.Jet_pt>600&&FatJetInfo.Jet_pt<800")
	npass = tr.Draw("FatJetInfo.Jet_pt>>hpass4","FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_massGroomed>95&&FatJetInfo.Jet_massGroomed<155&&FatJetInfo.Jet_pt>600&&FatJetInfo.Jet_pt<800"+varCut[3])
	if (debug==1): print "ntotal = ", ntotal
	if (debug==1): print "npass = ", npass
	if (debug==1): print (npass*1.0) / (ntotal *1.0), "%" 
	hpass4.Rebin(100)
	htotal4.Rebin(100)
	gr4 = TGraphAsymmErrors(hpass4,htotal4,"cl=0.683 b(1,1) mode")
	gr4.SetPointEXlow(0,100.)
	gr4.SetPointEXhigh(0,100.)
	gr4.SetLineColor(color)
	gr4.SetLineWidth(2)
	grList.append(gr4)

	if (debug==1): print "processing pt 800-1000 GeV, ", varCut[4]
	htotal5 = TH1D("htotal5","htotal5",100,800,1000)
	hpass5 = TH1D("hpass5","hpass5",100,800,1000)
	ntotal = tr.Draw("FatJetInfo.Jet_pt>>htotal5","FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_massGroomed>95&&FatJetInfo.Jet_massGroomed<155&&FatJetInfo.Jet_pt>800&&FatJetInfo.Jet_pt<1000")
	npass = tr.Draw("FatJetInfo.Jet_pt>>hpass5","FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_massGroomed>95&&FatJetInfo.Jet_massGroomed<155&&FatJetInfo.Jet_pt>800&&FatJetInfo.Jet_pt<1000"+varCut[4])
	if (debug==1): print "ntotal = ", ntotal
	if (debug==1): print "npass = ", npass
	if (debug==1): print (npass*1.0) / (ntotal *1.0), "%" 
	hpass5.Rebin(100)
	htotal5.Rebin(100)
	gr5 = TGraphAsymmErrors(hpass5,htotal5,"cl=0.683 b(1,1) mode")
	gr5.SetPointEXlow(0,100.)
	gr5.SetPointEXhigh(0,100.)
	gr5.SetLineColor(color)
	gr5.SetLineWidth(2)
	grList.append(gr5)

	if (debug==1): print "processing pt 1000-10000 GeV, ", varCut[5]
	htotal6 = TH1D("htotal6","htotal6",100,1000,1600)
	hpass6 = TH1D("hpass6","hpass6",100,1000,1600)
	ntotal = tr.Draw("FatJetInfo.Jet_pt>>htotal6","FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_massGroomed>95&&FatJetInfo.Jet_massGroomed<155&&FatJetInfo.Jet_pt>1000&&FatJetInfo.Jet_pt<1600")
	npass = tr.Draw("FatJetInfo.Jet_pt>>hpass6","FatJetInfo.Jet_SD_chi>0&&FatJetInfo.Jet_massGroomed>95&&FatJetInfo.Jet_massGroomed<155&&FatJetInfo.Jet_pt>1000&&FatJetInfo.Jet_pt<1600"+varCut[5])
	if (debug==1): print "ntotal = ", ntotal
	if (debug==1): print "npass = ", npass
	if (debug==1): print (npass*1.0) / (ntotal *1.0), "%" 
	hpass6.Rebin(100)
	htotal6.Rebin(100)
	gr6 = TGraphAsymmErrors(hpass6,htotal6,"cl=0.683 b(1,1) mode")
	gr6.SetPointEXlow(0,300.)
	gr6.SetPointEXhigh(0,300.)
	gr6.SetLineColor(color)
	gr6.SetLineWidth(2)
	grList.append(gr6)


	return grList

def makeTGraphAll_logchi_QCD():

	grm = TMultiGraph()

	logchiCut = []
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-19.3")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-18.4")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-18.2")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-18.3")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-19.2")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-20.45")

	grList1 = makeTGraph("rootfiles/slimTree/slimTree_Rad.root",logchiCut,kBlue)

	for i in xrange(len(grList1)):
		grm.Add(grList1[i])


	logchiCut = []
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-17.25")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-16.4")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-16.07")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-15.85")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-16.42")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-17.45")

	grList2 = makeTGraph("rootfiles/slimTree/slimTree_Rad.root",logchiCut,kGreen)

	for i in xrange(len(grList2)):
		grm.Add(grList2[i])


	logchiCut = []
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-15.07")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-14.39")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-13.95")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-13.6")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-13.5")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-14.2")

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

def makeTGraphAll_compare_rej10_QCD():

	grm = TMultiGraph()

	logchiCut = []
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-19.2")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-18.4")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-18.2")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-18.3")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-19.2")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-20.45")

	grList1 = makeTGraph("rootfiles/slimTree/slimTree_Rad.root",logchiCut,kBlue)

	for i in xrange(len(grList1)):
		grm.Add(grList1[i])


	tau21Cut = []
	tau21Cut.append("&&tau21<0.64")
	tau21Cut.append("&&tau21<0.65")
	tau21Cut.append("&&tau21<0.663")
	tau21Cut.append("&&tau21<0.67")
	tau21Cut.append("&&tau21<0.68")
	tau21Cut.append("&&tau21<0.675")

	grList2 = makeTGraph("rootfiles/slimTree/slimTree_Rad_wTau21.root",tau21Cut,kGreen)

	for i in xrange(len(grList2)):
		grm.Add(grList2[i])


	qvolCut = []
	qvolCut.append("&&FatJetInfo.Jet_qvol<0.127")
	qvolCut.append("&&FatJetInfo.Jet_qvol<0.225")
	qvolCut.append("&&FatJetInfo.Jet_qvol<0.315")
	qvolCut.append("&&FatJetInfo.Jet_qvol<0.340")
	qvolCut.append("&&FatJetInfo.Jet_qvol<0.280")
	qvolCut.append("&&FatJetInfo.Jet_qvol<0.225")

	grList3 = makeTGraph("rootfiles/slimTree/slimTree_Rad.root",qvolCut,kRed)

	for i in xrange(len(grList3)):
		grm.Add(grList3[i])


	grm.SetMaximum(1.05)
	grm.SetMinimum(0.85)
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
	leg.AddEntry(grList1[0],"log (#chi)")
	leg.AddEntry(grList2[0],"#tau_{2} / #tau_{1}")
	leg.AddEntry(grList3[0],"qvol")
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
	l1.SetTextSize(0.06)
	l1.DrawLatex(0.7,0.75, "rej_{bkg} = 10%")


	c1.Update()
	c1.SaveAs("sigEff_vs_pt_slimTree_Rad_compare_rej10.pdf")

def makeTGraphAll_compare_rej50_QCD():

	grm = TMultiGraph()

	logchiCut = []
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-17.25")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-16.4")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-16.1")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-16.07")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-16.42")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-17.45")

	grList1 = makeTGraph("rootfiles/slimTree/slimTree_Rad.root",logchiCut,kBlue)

	for i in xrange(len(grList1)):
		grm.Add(grList1[i])


	tau21Cut = []
	tau21Cut.append("&&tau21<0.452")
	tau21Cut.append("&&tau21<0.47")
	tau21Cut.append("&&tau21<0.493")
	tau21Cut.append("&&tau21<0.51")
	tau21Cut.append("&&tau21<0.52")
	tau21Cut.append("&&tau21<0.53")

	grList2 = makeTGraph("rootfiles/slimTree/slimTree_Rad_wTau21.root",tau21Cut,kGreen)

	for i in xrange(len(grList2)):
		grm.Add(grList2[i])


	qvolCut = []
	qvolCut.append("&&FatJetInfo.Jet_qvol<0.060")
	qvolCut.append("&&FatJetInfo.Jet_qvol<0.071")
	qvolCut.append("&&FatJetInfo.Jet_qvol<0.086")
	qvolCut.append("&&FatJetInfo.Jet_qvol<0.087")
	qvolCut.append("&&FatJetInfo.Jet_qvol<0.077")
	qvolCut.append("&&FatJetInfo.Jet_qvol<0.067")

	grList3 = makeTGraph("rootfiles/slimTree/slimTree_Rad.root",qvolCut,kRed)

	for i in xrange(len(grList3)):
		grm.Add(grList3[i])


	grm.SetMaximum(1.0)
	grm.SetMinimum(0.45)
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
	leg.AddEntry(grList1[0],"log (#chi)")
	leg.AddEntry(grList2[0],"#tau_{2} / #tau_{1}")
	leg.AddEntry(grList3[0],"qvol")
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
	l1.SetTextSize(0.06)
	l1.DrawLatex(0.7,0.75, "rej_{bkg} = 50%")


	c1.Update()
	c1.SaveAs("sigEff_vs_pt_slimTree_Rad_compare_rej50.pdf")

def makeTGraphAll_compare_rej90_QCD():

	grm = TMultiGraph()

	logchiCut = []
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-15.07")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-14.39")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-13.95")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-13.6")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-13.5")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-14.2")

	grList1 = makeTGraph("rootfiles/slimTree/slimTree_Rad.root",logchiCut,kBlue)

	for i in xrange(len(grList1)):
		grm.Add(grList1[i])


	tau21Cut = []
	tau21Cut.append("&&tau21<0.29")
	tau21Cut.append("&&tau21<0.29")
	tau21Cut.append("&&tau21<0.31")
	tau21Cut.append("&&tau21<0.325")
	tau21Cut.append("&&tau21<0.34")
	tau21Cut.append("&&tau21<0.355")

	grList2 = makeTGraph("rootfiles/slimTree/slimTree_Rad_wTau21.root",tau21Cut,kGreen)

	for i in xrange(len(grList2)):
		grm.Add(grList2[i])


	qvolCut = []
	qvolCut.append("&&FatJetInfo.Jet_qvol<0.035")
	qvolCut.append("&&FatJetInfo.Jet_qvol<0.037")
	qvolCut.append("&&FatJetInfo.Jet_qvol<0.040")
	qvolCut.append("&&FatJetInfo.Jet_qvol<0.040")
	qvolCut.append("&&FatJetInfo.Jet_qvol<0.035")
	qvolCut.append("&&FatJetInfo.Jet_qvol<0.025")

	grList3 = makeTGraph("rootfiles/slimTree/slimTree_Rad.root",qvolCut,kRed)

	for i in xrange(len(grList3)):
		grm.Add(grList3[i])


	grm.SetMaximum(0.65)
	grm.SetMinimum(-0.1)
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
	leg.AddEntry(grList1[0],"log (#chi)")
	leg.AddEntry(grList2[0],"#tau_{2} / #tau_{1}")
	leg.AddEntry(grList3[0],"qvol")
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
	l1.SetTextSize(0.06)
	l1.DrawLatex(0.7,0.75, "rej_{bkg} = 90%")


	c1.Update()
	c1.SaveAs("sigEff_vs_pt_slimTree_Rad_compare_rej90.pdf")


def makeTGraphAll_logchi_Zpr():

	grm = TMultiGraph()

	logchiCut = []
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-18.6")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-17.82")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-17.62")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-17.82")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-18.77")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-19.61")

	grList1 = makeTGraph("rootfiles/slimTree/slimTree_Rad.root",logchiCut,kBlue)

	for i in xrange(len(grList1)):
		grm.Add(grList1[i])


	logchiCut = []
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-16.22")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-15.61")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-15.41")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-15.41")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-15.8")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-16.8")

	grList2 = makeTGraph("rootfiles/slimTree/slimTree_Rad.root",logchiCut,kGreen)

	for i in xrange(len(grList2)):
		grm.Add(grList2[i])


	logchiCut = []
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-14.25")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-13.8")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-13.6")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-13.4")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-13.4")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-13.8")

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
	c1.SaveAs("sigEff_vs_pt_slimTree_Rad_logChi_Zpr.pdf")

def makeTGraphAll_compare_rej10_Zpr():

	grm = TMultiGraph()

	logchiCut = []
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-18.6")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-17.82")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-17.62")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-17.82")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-18.77")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-19.61")

	grList1 = makeTGraph("rootfiles/slimTree/slimTree_Rad.root",logchiCut,kBlue)

	for i in xrange(len(grList1)):
		grm.Add(grList1[i])


	tau21Cut = []
	tau21Cut.append("&&tau21<0.592")
	tau21Cut.append("&&tau21<0.61")
	tau21Cut.append("&&tau21<0.632")
	tau21Cut.append("&&tau21<0.64")
	tau21Cut.append("&&tau21<0.64")
	tau21Cut.append("&&tau21<0.64")

	grList2 = makeTGraph("rootfiles/slimTree/slimTree_Rad_wTau21.root",tau21Cut,kGreen)

	for i in xrange(len(grList2)):
		grm.Add(grList2[i])


	qvolCut = []
	qvolCut.append("&&FatJetInfo.Jet_qvol<0.105")
	qvolCut.append("&&FatJetInfo.Jet_qvol<0.140")
	qvolCut.append("&&FatJetInfo.Jet_qvol<0.200")
	qvolCut.append("&&FatJetInfo.Jet_qvol<0.200")
	qvolCut.append("&&FatJetInfo.Jet_qvol<0.200")
	qvolCut.append("&&FatJetInfo.Jet_qvol<0.210")

	grList3 = makeTGraph("rootfiles/slimTree/slimTree_Rad.root",qvolCut,kRed)

	for i in xrange(len(grList3)):
		grm.Add(grList3[i])


	grm.SetMaximum(1.0)
	grm.SetMinimum(0.85)
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
	leg.AddEntry(grList1[0],"log (#chi)")
	leg.AddEntry(grList2[0],"#tau_{2} / #tau_{1}")
	leg.AddEntry(grList3[0],"qvol")
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
	l1.SetTextSize(0.06)
	l1.DrawLatex(0.7,0.75, "rej_{bkg} = 10%")


	c1.Update()
	c1.SaveAs("sigEff_vs_pt_slimTree_Rad_compare_rej10_Zpr.pdf")

def makeTGraphAll_compare_rej50_Zpr():

	grm = TMultiGraph()

	logchiCut = []
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-16.22")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-15.61")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-15.41")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-15.41")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-15.8")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-16.8")

	grList1 = makeTGraph("rootfiles/slimTree/slimTree_Rad.root",logchiCut,kBlue)

	for i in xrange(len(grList1)):
		grm.Add(grList1[i])


	tau21Cut = []
	tau21Cut.append("&&tau21<0.40")
	tau21Cut.append("&&tau21<0.41")
	tau21Cut.append("&&tau21<0.46")
	tau21Cut.append("&&tau21<0.47")
	tau21Cut.append("&&tau21<0.471")
	tau21Cut.append("&&tau21<0.463")

	grList2 = makeTGraph("rootfiles/slimTree/slimTree_Rad_wTau21.root",tau21Cut,kGreen)

	for i in xrange(len(grList2)):
		grm.Add(grList2[i])


	qvolCut = []
	qvolCut.append("&&FatJetInfo.Jet_qvol<0.052") 
	qvolCut.append("&&FatJetInfo.Jet_qvol<0.06")
	qvolCut.append("&&FatJetInfo.Jet_qvol<0.072")
	qvolCut.append("&&FatJetInfo.Jet_qvol<0.075")
	qvolCut.append("&&FatJetInfo.Jet_qvol<0.0775")
	qvolCut.append("&&FatJetInfo.Jet_qvol<0.0725")

	grList3 = makeTGraph("rootfiles/slimTree/slimTree_Rad.root",qvolCut,kRed)

	for i in xrange(len(grList3)):
		grm.Add(grList3[i])


	grm.SetMaximum(0.9)
	grm.SetMinimum(0.45)
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
	leg.AddEntry(grList1[0],"log (#chi)")
	leg.AddEntry(grList2[0],"#tau_{2} / #tau_{1}")
	leg.AddEntry(grList3[0],"qvol")
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
	l1.SetTextSize(0.06)
	l1.DrawLatex(0.7,0.75, "rej_{bkg} = 50%")


	c1.Update()
	c1.SaveAs("sigEff_vs_pt_slimTree_Rad_compare_rej50_Zpr.pdf")

def makeTGraphAll_compare_rej90_Zpr():

	grm = TMultiGraph()

	logchiCut = []
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-14.25")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-13.8")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-13.6")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-13.4")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-13.4")
	logchiCut.append("&&log(FatJetInfo.Jet_SD_chi)>-13.8")

	grList1 = makeTGraph("rootfiles/slimTree/slimTree_Rad.root",logchiCut,kBlue)

	for i in xrange(len(grList1)):
		grm.Add(grList1[i])


	tau21Cut = []
	tau21Cut.append("&&tau21<0.232")
	tau21Cut.append("&&tau21<0.232")
	tau21Cut.append("&&tau21<0.26")
	tau21Cut.append("&&tau21<0.27")
	tau21Cut.append("&&tau21<0.29")
	tau21Cut.append("&&tau21<0.31")

	grList2 = makeTGraph("rootfiles/slimTree/slimTree_Rad_wTau21.root",tau21Cut,kGreen)

	for i in xrange(len(grList2)):
		grm.Add(grList2[i])


	qvolCut = []
	qvolCut.append("&&FatJetInfo.Jet_qvol<0.031")
	qvolCut.append("&&FatJetInfo.Jet_qvol<0.0325")
	qvolCut.append("&&FatJetInfo.Jet_qvol<0.035")
	qvolCut.append("&&FatJetInfo.Jet_qvol<0.035")
	qvolCut.append("&&FatJetInfo.Jet_qvol<0.030")
	qvolCut.append("&&FatJetInfo.Jet_qvol<0.025")

	grList3 = makeTGraph("rootfiles/slimTree/slimTree_Rad.root",qvolCut,kRed)

	for i in xrange(len(grList3)):
		grm.Add(grList3[i])


	grm.SetMaximum(0.5)
	grm.SetMinimum(-0.1)
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
	leg.AddEntry(grList1[0],"log (#chi)")
	leg.AddEntry(grList2[0],"#tau_{2} / #tau_{1}")
	leg.AddEntry(grList3[0],"qvol")
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
	l1.SetTextSize(0.06)
	l1.DrawLatex(0.7,0.75, "rej_{bkg} = 90%")


	c1.Update()
	c1.SaveAs("sigEff_vs_pt_slimTree_Rad_compare_rej90_Zpr.pdf")

# makeTGraphAll_logchi_QCD()
# makeTGraphAll_compare_rej10_QCD()
# makeTGraphAll_compare_rej50_QCD()
# makeTGraphAll_compare_rej90_QCD()

makeTGraphAll_logchi_Zpr()
makeTGraphAll_compare_rej10_Zpr()
makeTGraphAll_compare_rej50_Zpr()
makeTGraphAll_compare_rej90_Zpr()
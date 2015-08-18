#!/usr/bin/env python
from ROOT import *

def makeROC(ch_s, var, cuts, bin, min, max):

	h_s = TH1D("h_s","",bin, min,max)
	h_b = TH1D("h_b","",bin, min,max)

	nEntries = ch_s.GetEntries()

	for i in xrange(len(nEntries)):
		ch_s.GetEntry(i)
		ch_b.GetEntry(i)



		for j in

		if(var == "tau21"):
			tau2 = ch_s.Get("FatJetInfo.Jet_tau2")
			tau1 = ch_s.Get("FatJetInfo.Jet_tau1")
			tau21 = tau2/tau1
		else:
			var = ch_s.Get(var)

		pt = ch_s.Get("FatJetInfo.Jet_pt")
		mass = ch_s.Get("FatJetInfo.Jet_massGroomed")
		chi = ch_s.Get("FatJetInfo.Jet_SD_chi")

		ptmin  = cut[0]
		ptmax = cut[1]
		massmin = cut[2]
		massmax = cut[3]
		logchiMin = cut[4]
		logchiMax =cut[5]

		weight = ch_s.Get("weight")

		if(pt<ptmin or pt>ptmax or mass<massmin or mass>massmax or chi==0 or chi<logchiMin or chi>logchiMax):continue

		h_s.Fill(var,weight)

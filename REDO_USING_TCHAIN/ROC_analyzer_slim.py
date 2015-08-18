import os, sys, math
from ROOT import *


def runAnalysis(myChain, fOut, massCut, ptCut, chiCut):
  entries = myChain.GetEntries()

  print "Number of entries: " + str(entries)

  fOut.cd()

  h1 = TH1F("pt", "p_{T}", 400, 0,1600) 
  h2 = TH1F("tau21", "#tau_{2} / #tau_{1}", 100, 0,1)
  h3 = TH1F("logchi","log #chi",200,-26,-6)
  h4 = TH1F("qvol","qvol",100,0,0.5)

  for jEntry in xrange(entries):
    iEntry = myChain.LoadTree(jEntry)

    if iEntry < 0:
      break

    nb = myChain.GetEntry(jEntry)
    
    w = getattr(myChain, "evt_weight")
 
    if nb <= 0:
      continue

    if jEntry % 1000 == 0:
      print "Processing entry " + str(jEntry)
    if jEntry == 100 : break #debug
    br = getattr(myChain, "FatJetInfo.nJet")
    for i in range(br):

      mass = getattr(myChain, "FatJetInfo.Jet_massGroomed")
      flavour = getattr(myChain, "FatJetInfo.Jet_flavour")
      nbHad = getattr(myChain, "FatJetInfo.Jet_nbHadrons")
      pt = getattr(myChain, "FatJetInfo.Jet_pt")
      tau1 = getattr(myChain, "FatJetInfo.Jet_tau1")
      tau2 = getattr(myChain, "FatJetInfo.Jet_tau2")
      tau21 = tau2[i]/tau1[i] if tau1[i]!=0 else -1
      chi = getattr(myChain, "FatJetInfo.Jet_SD_chi")
      qvol = getattr(myChain, "FatJetInfo.Jet_qvol")	
      
      #if mass[i]>155 or mass[i]<95 or pt[i]<300 or pt[i]>600: continue
      #if mass[i]<massCut[0] or mass[i]>massCut[1] or pt[i]<ptCut[0] or pt[i]>ptCut[1]: continue
      if mass[i]<massCut[0] or mass[i]>massCut[1] or pt[i]<ptCut[0] or pt[i]>ptCut[1] or chi[i]==0 : continue
      if math.log(chi[i])<chiCut : continue

      if chi[i]>0:
      	logchi = math.log(chi[i])
#       	print w
#       	if iEntry<10: print w 
        h3.Fill(logchi,w )
      else :
      	print "chi = ",chi[i]
        h3.Fill(0)

      h1.Fill(pt[i],w)
      h2.Fill(tau21,w)
      h4.Fill(qvol[i],w)

  fOut.Write()
  fOut.Close()

import os, sys
from ROOT import *
from slimTree_BTagAnalyzerLite_v2_addTau21 import doMySkim


sw = TStopwatch()

sw.Start()

Tree = "btaganaSubJets/ttree"

print "Processing RadHH"
fOut = "slimTree_Rad_wTau21.root"
w = 1.
fIn = []
fIn.append("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M800_13TeV/Rad_M800_kT020_Hwin30_tag07_fake02/150702_233636/0000/*.root")
fIn.append("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M1000_13TeV_PHYS14_25_V1/Rad_M1000_kT020_Hwin30_tag07_fake02/150703_002549/0000/*.root")
fIn.append("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M1200_13TeV_PHYS14_25_V1/Rad_M1200_kT020_Hwin30_tag07_fake02/150703_004216/0000/*.root")
fIn.append("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M1400_13TeV_PHYS14_25_V1/Rad_M1400_kT020_Hwin30_tag07_fake02/150722_023215/0000/*.root")
fIn.append("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M1600_13TeV_PHYS14_25_V1/Rad_M1600_kT020_Hwin30_tag07_fake02/150717_211508/0000/*.root")
fIn.append("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M1800_13TeV_PHYS14_25_V1/Rad_M1800_kT020_Hwin30_tag07_fake02/150717_211547/0000/*.root")
fIn.append("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M2000_13TeV_PHYS14_25_V1/Rad_M2000_kT020_Hwin30_tag07_fake02/150717_211622/0000/*.root")
doMySkim(Tree,fOut,fIn,w)


print "Processing QCD300"
fOut = "slimTree_QCD300_wTau21.root"
w = 7475./1986177.
fIn = []
fIn.append("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-300to470_Tune4C_13TeV_pythia8/QCDpt300_kT020_Hwin30_tag07_fake02/150706_204757/0000/*.root")
doMySkim(Tree,fOut,fIn,w)

print "Processing QCD470"
fOut = "slimTree_QCD470_wTau21.root"
w = 587.1/2001071.
fIn =[]
fIn.append("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-470to600_Tune4C_13TeV_pythia8/QCDpt470_kT020_Hwin30_tag07_fake02/150706_204846/0000/*.root")
doMySkim(Tree,fOut,fIn,w)

print "Processing QCD600"
fOut = "slimTree_QCD600_wTau21.root"
# w = 167.0/2001071.
w = 167.0/1952057.0 #(1 unfinished jobs)
fIn =[]
fIn.append("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-600to800_Tune4C_13TeV_pythia8/QCDpt600_kT020_Hwin30_tag07_fake02/150717_210748/0000/*.root")
doMySkim(Tree,fOut,fIn,w)

print "Processing QCD800"
ch4  = TChain(Tree)
fOut = "slimTree_QCD800_wTau21.root"
w = 28.25/1000065.
fIn =[]
fIn.append("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-800to1000_Tune4C_13TeV_pythia8/QCDpt800_kT020_Hwin30_tag07_fake02/150717_210834/0000/*.root")
doMySkim(Tree,fOut,fIn,w)

print "Processing QCD1000"
ch5  = TChain(Tree)
fOut = "slimTree_QCD1000_wTau21.root"
w = 8.195/500550.
fIn =[]
fIn.append("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/QCDpt1000_kT020_Hwin30_tag07_fake02/150717_210939/0000/*.root")
doMySkim(Tree,fOut,fIn,w)

print "Processing QCD1400"
ch6  = TChain(Tree)
fOut = "slimTree_QCD1400_wTau21.root"
w = 0.7346/199627.0
w = 0.7346/149170.0 #(1 unfinished job)
fIn =[]
fIn.append("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-1400to1800_Tune4C_13TeV_pythia8/QCDpt1400_kT020_Hwin30_tag07_fake02/150717_211013/0000/*.root")
doMySkim(Tree,fOut,fIn,w)

print "Processing QCD1800"
ch7  = TChain(Tree)
fOut = "slimTree_QCD1800_wTau21.root"
w = 0.102/200079.
fIn =[]
fIn.append("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-1800to2400_Tune4C_13TeV_pythia8/QCDpt1800_kT020_Hwin30_tag07_fake02/150717_211111/0000/*.root")
doMySkim(Tree,fOut,fIn,w)

print "Processing QCD2400"
ch8  = TChain(Tree)
fOut = "slimTree_QCD2400_wTau21.root"
w = 0.00644/200453.
fIn =[]
fIn.append("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-2400to3200_Tune4C_13TeV_pythia8/QCDpt2400_kT020_Hwin30_tag07_fake02/150717_211201/0000/*.root")
doMySkim(Tree,fOut,fIn,w)

print "Processing QCD3200"
fOut = "slimTree_QCD3200_wTau21.root"
w = 0.000163/200200.
fIn =[]
fIn.append("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-3200_Tune4C_13TeV_pythia8/QCDpt3200_kT020_Hwin30_tag07_fake02/150717_211311/0000/*.root")
doMySkim(Tree,fOut,fIn,w)

print "Processing Zpr"
fOut = "slimTree_Zpr_wTau21.root"
w = 1.0
fIn =[]
fIn.append("/eos/uscms/store/user/rsyarif/SDstudies/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola/Zpr_M1000_kT020_Hwin30_tag07_fake02/150703_215948/0000/*.root")
fIn.append("/eos/uscms/store/user/rsyarif/SDstudies/ZPrimeToTTJets_M2000GeV_W20GeV_Tune4C_13TeV-madgraph-tauola/Zpr_M2000_kT020_Hwin30_tag07_fake02/150703_214411/0000/*.root")
doMySkim(Tree,fOut,fIn,w)

sw.Stop()

print "Real time: " + str(sw.RealTime() / 60.0) + " minutes"
print "CPU time:  " + str(sw.CpuTime()  / 60.0) + " minutes"
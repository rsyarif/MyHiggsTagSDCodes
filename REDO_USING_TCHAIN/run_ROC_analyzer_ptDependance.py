import os, sys
from ROOT import *
from ROC_analyzer import runAnalysis
from combine_ROC import *


sw = TStopwatch()

sw.Start()

minMass = 95
maxMass = 155

massCut = []
massCut.append(minMass)
massCut.append(maxMass)

minPt = 0
maxPt = 100000

ptCut = []
ptCut.append(minPt)
ptCut.append(maxPt)

chiCut = -12.5

# print "PROCESSING FOR PT DEPENDANCE ANALYSIS"
# print " "
# print "Processing signal - Rad"
# cIn  = TChain("btaganaSubJets/ttree")
# fOut = TFile ("ROC_analyzer_Rad_ptDependanceCalc.root", "recreate")
# w = 1.
# print "Chaining files ..."
# cIn.Add("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M800_13TeV/Rad_M800_kT020_Hwin30_tag07_fake02/150702_233636/0000/*.root")
# cIn.Add("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M1000_13TeV_PHYS14_25_V1/Rad_M1000_kT020_Hwin30_tag07_fake02/150703_002549/0000/*.root")
# cIn.Add("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M1200_13TeV_PHYS14_25_V1/Rad_M1200_kT020_Hwin30_tag07_fake02/150703_004216/0000/*.root")
# cIn.Add("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M1400_13TeV_PHYS14_25_V1/Rad_M1400_kT020_Hwin30_tag07_fake02/150722_023215/0000/*.root")
# cIn.Add("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M1600_13TeV_PHYS14_25_V1/Rad_M1600_kT020_Hwin30_tag07_fake02/150717_211508/0000/*.root")
# cIn.Add("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M1800_13TeV_PHYS14_25_V1/Rad_M1800_kT020_Hwin30_tag07_fake02/150717_211547/0000/*.root")
# cIn.Add("/eos/uscms/store/user/rsyarif/SDstudies/Rad_HHto4b_M2000_13TeV_PHYS14_25_V1/Rad_M2000_kT020_Hwin30_tag07_fake02/150717_211622/0000/*.root")
# runAnalysis(cIn, w, fOut, massCut, ptCut, chiCut)
# 
# print "Processing QCD300"
# ch1  = TChain("btaganaSubJets/ttree")
# fOut = TFile ("ROC_analyzer_QCD300_ptDependanceCalc.root", "recreate")
# w = 7475./1986177.
# print "Chaining files ..."
# ch1.Add("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-300to470_Tune4C_13TeV_pythia8/QCDpt300_kT020_Hwin30_tag07_fake02/150706_204757/0000/*.root")
# runAnalysis(ch1, w, fOut, massCut, ptCut, chiCut)
# 
# print "Processing QCD470"
# ch2  = TChain("btaganaSubJets/ttree")
# fOut = TFile ("ROC_analyzer_QCD470_ptDependanceCalc.root", "recreate")
# w = 587.1/2001071.
# print "Chaining files ..."
# ch2.Add("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-470to600_Tune4C_13TeV_pythia8/QCDpt470_kT020_Hwin30_tag07_fake02/150706_204846/0000/*.root")
# runAnalysis(ch2, w, fOut, massCut, ptCut, chiCut)
# 
print "Processing QCD600"
ch3  = TChain("btaganaSubJets/ttree")
fOut = TFile ("ROC_analyzer_QCD600_ptDependanceCalc.root", "recreate")
w = 167.0/2001071.
w = 167.0/1952057.0 #(1 unfinished jobs)
print "Chaining files ..."
ch3.Add("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-600to800_Tune4C_13TeV_pythia8/QCDpt600_kT020_Hwin30_tag07_fake02/150717_210748/0000/*.root")
runAnalysis(ch3, w, fOut, massCut, ptCut, chiCut)

print "Processing QCD800"
ch4  = TChain("btaganaSubJets/ttree")
fOut = TFile ("ROC_analyzer_QCD800_ptDependanceCalc.root", "recreate")
w = 28.25/1000065.
print "Chaining files ..."
ch4.Add("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-800to1000_Tune4C_13TeV_pythia8/QCDpt800_kT020_Hwin30_tag07_fake02/150717_210834/0000/*.root")
runAnalysis(ch4, w, fOut, massCut, ptCut, chiCut)

print "Processing QCD1000"
ch5  = TChain("btaganaSubJets/ttree")
fOut = TFile ("ROC_analyzer_QCD1000_ptDependanceCalc.root", "recreate")
w = 8.195/500550.
print "Chaining files ..."
ch5.Add("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/QCDpt1000_kT020_Hwin30_tag07_fake02/150717_210939/0000/*.root")
runAnalysis(ch5, w, fOut, massCut, ptCut, chiCut)

print "Processing QCD1400"
ch6  = TChain("btaganaSubJets/ttree")
fOut = TFile ("ROC_analyzer_QCD1400_ptDependanceCalc.root", "recreate")
w = 0.7346/199627.0
w = 0.7346/149170.0 #(1 unfinished job)
print "Chaining files ..."
ch6.Add("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-1400to1800_Tune4C_13TeV_pythia8/QCDpt1400_kT020_Hwin30_tag07_fake02/150717_211013/0000/*.root")
runAnalysis(ch6, w, fOut, massCut, ptCut, chiCut)

print "Processing QCD1800"
ch7  = TChain("btaganaSubJets/ttree")
fOut = TFile ("ROC_analyzer_QCD1800_ptDependanceCalc.root", "recreate")
w = 0.102/200079.
print "Chaining files ..."
ch7.Add("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-1800to2400_Tune4C_13TeV_pythia8/QCDpt1800_kT020_Hwin30_tag07_fake02/150717_211111/0000/*.root")
runAnalysis(ch7, w, fOut, massCut, ptCut, chiCut)

print "Processing QCD2400"
ch8  = TChain("btaganaSubJets/ttree")
fOut = TFile ("ROC_analyzer_QCD2400_ptDependanceCalc.root", "recreate")
w = 0.00644/200453.
print "Chaining files ..."
ch8.Add("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-2400to3200_Tune4C_13TeV_pythia8/QCDpt2400_kT020_Hwin30_tag07_fake02/150717_211201/0000/*.root")
runAnalysis(ch8, w, fOut, massCut, ptCut, chiCut)

print "Processing QCD3200"
ch9  = TChain("btaganaSubJets/ttree")
fOut = TFile ("ROC_analyzer_QCD3200_ptDependanceCalc.root", "recreate")
w = 0.000163/200200.
print "Chaining files ..."
ch9.Add("/eos/uscms/store/user/rsyarif/SDstudies/QCD_Pt-3200_Tune4C_13TeV_pythia8/QCDpt3200_kT020_Hwin30_tag07_fake02/150717_211311/0000/*.root")
runAnalysis(ch9, w, fOut, massCut, ptCut, chiCut)

print "Processing Zpr"
ch10  = TChain("btaganaSubJets/ttree")
fOut = TFile ("ROC_analyzer_Zpr_ptDependanceCalc.root", "recreate")
w = 1.0
print "Chaining files ..."
ch10.Add("/eos/uscms/store/user/rsyarif/SDstudies/ZPrimeToTTJets_M1000GeV_W10GeV_Tune4C_13TeV-madgraph-tauola/Zpr_M1000_kT020_Hwin30_tag07_fake02/150703_215948/0000/*.root")
ch10.Add("/eos/uscms/store/user/rsyarif/SDstudies/ZPrimeToTTJets_M2000GeV_W20GeV_Tune4C_13TeV-madgraph-tauola/Zpr_M2000_kT020_Hwin30_tag07_fake02/150703_214411/0000/*.root")
runAnalysis(ch10, w, fOut, massCut, ptCut, chiCut)



sw.Stop()

print "Real time: " + str(sw.RealTime() / 60.0) + " minutes"
print "CPU time:  " + str(sw.CpuTime()  / 60.0) + " minutes"

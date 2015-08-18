import os, sys
from ROOT import *
from ROC_analyzer_slim import runAnalysis

sw = TStopwatch()

sw.Start()

minMass = 95
maxMass = 155

massCut = []
massCut.append(minMass)
massCut.append(maxMass)

minPt = 300
maxPt = 400

ptCut = []
ptCut.append(minPt)
ptCut.append(maxPt)

chiCut = -1e6

print "Processing signal - Rad"
cIn  = TChain("ttree")
fOut = TFile ("ROC_analyzer_slim_Rad_pt300-400.root", "recreate")
w = 1.
print "Chaining files ..."
cIn.Add("/uscms_data/d3/rsyarif/HiggsTagging/CMSSW_7_4_0/src/RecoBTag/BTagAnalyzerLite/test/sandbox/REDO_USING_TCHAIN/rootfiles/slimTree/slimTree_Rad.root")
runAnalysis(cIn, fOut, massCut, ptCut, chiCut)

print "Processing QCD300"
ch1  = TChain("ttree")
fOut = TFile ("ROC_analyzer_slim_QCD_pt300-400.root", "recreate")
print "Chaining files ..."
ch1.Add("/uscms_data/d3/rsyarif/HiggsTagging/CMSSW_7_4_0/src/RecoBTag/BTagAnalyzerLite/test/sandbox/REDO_USING_TCHAIN/rootfiles/slimTree/slimTree_QCD300.root")
ch1.Add("/uscms_data/d3/rsyarif/HiggsTagging/CMSSW_7_4_0/src/RecoBTag/BTagAnalyzerLite/test/sandbox/REDO_USING_TCHAIN/rootfiles/slimTree/slimTree_QCD470.root")
ch1.Add("/uscms_data/d3/rsyarif/HiggsTagging/CMSSW_7_4_0/src/RecoBTag/BTagAnalyzerLite/test/sandbox/REDO_USING_TCHAIN/rootfiles/slimTree/slimTree_QCD600.root")
ch1.Add("/uscms_data/d3/rsyarif/HiggsTagging/CMSSW_7_4_0/src/RecoBTag/BTagAnalyzerLite/test/sandbox/REDO_USING_TCHAIN/rootfiles/slimTree/slimTree_QCD800.root")
ch1.Add("/uscms_data/d3/rsyarif/HiggsTagging/CMSSW_7_4_0/src/RecoBTag/BTagAnalyzerLite/test/sandbox/REDO_USING_TCHAIN/rootfiles/slimTree/slimTree_QCD1000.root")
ch1.Add("/uscms_data/d3/rsyarif/HiggsTagging/CMSSW_7_4_0/src/RecoBTag/BTagAnalyzerLite/test/sandbox/REDO_USING_TCHAIN/rootfiles/slimTree/slimTree_QCD1400.root")
ch1.Add("/uscms_data/d3/rsyarif/HiggsTagging/CMSSW_7_4_0/src/RecoBTag/BTagAnalyzerLite/test/sandbox/REDO_USING_TCHAIN/rootfiles/slimTree/slimTree_QCD1800.root")
ch1.Add("/uscms_data/d3/rsyarif/HiggsTagging/CMSSW_7_4_0/src/RecoBTag/BTagAnalyzerLite/test/sandbox/REDO_USING_TCHAIN/rootfiles/slimTree/slimTree_QCD2400.root")
ch1.Add("/uscms_data/d3/rsyarif/HiggsTagging/CMSSW_7_4_0/src/RecoBTag/BTagAnalyzerLite/test/sandbox/REDO_USING_TCHAIN/rootfiles/slimTree/slimTree_QCD3200.root")
runAnalysis(ch1, fOut, massCut, ptCut, chiCut)

print "Processing Zpr"
ch10  = TChain("ttree")
fOut = TFile ("ROC_analyzer_slim_Zpr_pt300-400.root", "recreate")
w = 1.0
print "Chaining files ..."
ch10.Add("/uscms_data/d3/rsyarif/HiggsTagging/CMSSW_7_4_0/src/RecoBTag/BTagAnalyzerLite/test/sandbox/REDO_USING_TCHAIN/rootfiles/slimTree/slimTree_Zpr.root")
runAnalysis(ch10, fOut, massCut, ptCut, chiCut)



sw.Stop()

print "Real time: " + str(sw.RealTime() / 60.0) + " minutes"
print "CPU time:  " + str(sw.CpuTime()  / 60.0) + " minutes"

#!/usr/bin/env python
from ROOT import *
import sys

def doMySkim(treeName,outputFile,inputFiles,wt):

# 	inputFiles = sys.argv[1].split(',')
# 	inputFiles = inputFiles

#     print "inputFiles = ", inputFiles

    print "Tree = ", treeName

    #get main tree
    ch = TChain(treeName)
    print "Chaining Files :"

    for file in inputFiles:
        ch.Add(file)
        print file

   #*****set branches*****

    #set branch status, at first, all off
    ch.SetBranchStatus("*", 0)

    #event information
    ch.SetBranchStatus("Evt",1)
    ch.SetBranchStatus("mcweight",1)
    ch.SetBranchStatus("FatJetInfo.nJet",1)
    ch.SetBranchStatus("FatJetInfo.Jet_pt",1)
    ch.SetBranchStatus("FatJetInfo.Jet_eta",1)
    ch.SetBranchStatus("FatJetInfo.Jet_phi",1)
    ch.SetBranchStatus("FatJetInfo.Jet_flavour",1)
    ch.SetBranchStatus("FatJetInfo.Jet_nbHadrons",1)
    ch.SetBranchStatus("FatJetInfo.Jet_massGroomed",1)
    ch.SetBranchStatus("FatJetInfo.Jet_tau1",1)
    ch.SetBranchStatus("FatJetInfo.Jet_tau2",1)
    ch.SetBranchStatus("FatJetInfo.Jet_qvol",1)
    ch.SetBranchStatus("FatJetInfo.Jet_SD_chi",1)
    ch.SetBranchStatus("FatJetInfo.Jet_SD_nMicrojets",1)
    ch.SetBranchStatus("FatJetInfo.Jet_SD_nBtagMicrojets",1)

    #*****set branches end*****

    # Write to new file
    outFile = outputFile
    newFile = TFile(outFile, "RECREATE")

    #new tree
    ch_new = ch.CloneTree(0)

     # Create a struct
    gROOT.ProcessLine(\
    "struct MyStruct{\
    	const UInt_t nMaxJets_ = 10000;\
    	Double_t tau21[10000];\
    	Double_t evt_weight;\
    };")

    s = MyStruct()
    ch_new.Branch("evt_weight", AddressOf(s,'evt_weight'),'evt_weight/D')
    ch_new.Branch("tau21", AddressOf(s,'tau21'),'tau21[FatJetInfo.nJet]/D')

    # event selection

    nEntries = ch.GetEntries()
    print "total events =", nEntries
    for i in xrange(nEntries):
        if i % 10000 == 0:
        	print "Processing entry " + str(i)

# 		if i == 1000 : break

        ch.GetEntry(i)

        nJet = getattr(ch,"FatJetInfo.nJet")
        if ( nJet == 0 ) : continue
        s.evt_weight = wt

        tau2 = getattr(ch,"FatJetInfo.Jet_tau2")
        tau1 = getattr(ch,"FatJetInfo.Jet_tau1")

        for j in range(nJet):
        	tau21 = tau2[j] / tau1[j]
        	s.tau21[j] = tau21

        ch_new.Fill()


    newFile.cd()
    ch_new.Write()

    print "s.evt_weight = ", s.evt_weight

    print ""
    print outputFile," has been created and saved."


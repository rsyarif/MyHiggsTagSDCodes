import os, sys
from ROOT import *
from combine_ROC_v2 import *

sw = TStopwatch()

sw.Start()

def run_combine_ROC(category,min,max):
	makeROC("tau21",0.,1.,0,category)
	makeROC("logchi",-26.,-6.,1,category)
	makeROC("pt",150,1600,1,category)
	makeROC("qvol",0,0.5,0,category)
	
	files=[]
	files.append("temp/TEMP_ROC_logchi.root")
	files.append("temp/TEMP_ROC_tau21.root")
	files.append("temp/TEMP_ROC_qvol.root")
	
	massCut = []
	massCut.append(95)
	massCut.append(155)
	
	ptCut = []
	ptCut.append(min)
	ptCut.append(max)
	
	allROC(files, massCut, ptCut,category)

run_combine_ROC("_pt300-400",300,400)
run_combine_ROC("_pt400-500",400,500)
run_combine_ROC("_pt500-600",500,600)
run_combine_ROC("_pt600-800",600,800)
run_combine_ROC("_pt800-1000",800,1000)
run_combine_ROC("_pt1000-10000",1000,10000)
# run_combine_ROC("_pt300-10000",300,10000)


sw.Stop()

print "Real time: " + str(sw.RealTime() / 60.0) + " minutes"
print "CPU time:  " + str(sw.CpuTime()  / 60.0) + " minutes"

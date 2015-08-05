#!/usr/bin/env python

from ROOT import *
import os, sys, optparse, subprocess, string, re, shutil

def make_filenamelist(inputDir):
    if not os.path.isdir(inputDir):
        print ('%s is not a directory'%(inputDir))
        sys.exit(1)

    filenamelist = []
    for filename in os.listdir(inputDir):
        if not os.path.isfile(os.path.join(inputDir,filename)):
            continue
        filenamelist.append(filename)
    #print filenamelist
    return filenamelist


def process_input_dir(inputDir, filelist):
    inputDir = inputDir.rstrip('/')+'/'
    filenamelist = make_filenamelist(inputDir)

    path = inputDir;
    name = ''
    jobdict = {}

    for filename in filenamelist:
        if( not re.search('.root$', filename) ):
            continue
        m1 = re.search('\w+.root', filename)
        if name=='':
            name = re.split('\w+.root', filename)[0]
        jobstring = filename[m1.start():].lstrip('_').replace('.root','').split('_')
        job = int(jobstring[3])
        jobdict[job] = []
        jobdict[job].append(jobstring[0])
        jobdict[job].append(jobstring[1])
        jobdict[job].append(jobstring[2])

    jobs = jobdict.keys()
    if( len(jobs)==0 ):
        print 'No matching .root files found'
        sys.exit()

    jobs.sort()
    for job in jobs:
        filename = (path+'%s_%s_%s_%i.root')%(jobdict[job][0],jobdict[job][1],jobdict[job][2],job)
        filelist.append(filename)

	#print filelist
    return

usage = """Usage: %prog -i INPUTDIR
Example: ./CalcTotalEvents.py -i /path/"""



def main():

    parser = optparse.OptionParser(usage=usage)

    parser.add_option('-i', '--inputdir', metavar='INPUTDIR', dest='inputdir', action='store', help='Input directory containing .root files')

    (options, args) = parser.parse_args(args=None)

    # process input directory
    filelist = []
    process_input_dir(options.inputdir, filelist)


    print "Processing ", len(filelist), " files:"
    count  = 0
    i = 0
    for f in filelist:
        i=i+1
        #print "f =",f
        root_file = TFile(f)
        htemp = root_file.Get("allEvents/hEventCount")
        count = count + htemp.GetBinContent(1)
        print i, ". ",root_file," has", htemp.GetBinContent(1) , " events."

    print "---------------"
    print options.inputdir," has", count , " events."

if __name__ == '__main__':
    main()

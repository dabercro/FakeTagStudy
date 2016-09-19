#!/usr/bin/env python

import sys,os
import ROOT

import CrombieTools

OutTreeName = 'OutTree'

os.system('crombie maketree ' + OutTreeName)
ROOT.gROOT.LoadMacro(OutTreeName + '.cc+')
ROOT.gROOT.LoadMacro('NeroTree.C+')
ROOT.gROOT.LoadMacro('slimmer.cc+')

# Load any other needed macros here

if len(sys.argv) < 2:
    exit()
elif sys.argv[1] == 'test' or len(sys.argv) < 3:
    ROOT.slimmer(
        'root://eoscms.cern.ch//store/user/dabercro/Nero/80X/SingleMuon/SingleMuon_0/160907_133042/0000/NeroNtuples_90.root',
        'test.root'
        )
else:
    if not os.path.isfile(sys.argv[2]):
        ROOT.slimmer(sys.argv[1],
                     sys.argv[2])
    else:
        print(sys.argv[2] + ' already exists!! Skipping...')

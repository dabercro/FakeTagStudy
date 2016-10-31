#!/usr/bin/env python

import sys,os
import ROOT

import CrombieTools

OutTreeName = 'OutTree'

os.system('crombie maketree ' + OutTreeName)
ROOT.gROOT.LoadMacro(OutTreeName + '.cc+')
ROOT.gROOT.LoadMacro('NeroMonoJet.C+')
ROOT.gROOT.LoadMacro('slimmer.cc+')

# Load any other needed macros here

if len(sys.argv) < 2:
    exit()
elif sys.argv[1] == 'test' or len(sys.argv) < 3:
    ROOT.slimmer(
        'root://eoscms.cern.ch//store/group/phys_exotica/monojet/zdemirag/setup80x/Nero/zey_base/GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/GJets_HT-400To600/160709_172352/0000/NeroNtuples_8.root',
        'test.root'
        )
else:
    if not os.path.isfile(sys.argv[2]):
        ROOT.slimmer(sys.argv[1],
                     sys.argv[2])
    else:
        print(sys.argv[2] + ' already exists!! Skipping...')

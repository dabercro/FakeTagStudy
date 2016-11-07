#!/usr/bin/env python

from CrombieTools.AnalysisTools.XSecAdder import RunXSecAdder as run
from CrombieTools.AnalysisTools.XSecAdder import xSecAdder as adder
from CrombieTools.LoadConfig import cuts
import sys

for branch in cuts.defaultMCWeight.split(' * '):
    print 'Adding merge branch:', branch
    adder.AddMergeBranch(branch)

run(*([sys.argv[1]]))

#!/usr/bin/env python

from CrombieTools.AnalysisTools.HistAnalysis import *
from CrombieTools.LoadConfig import cuts

SetupFromEnv()

histAnalysis.AddDataFile('fakescale_Data.root')
histAnalysis.SetBaseCut(cuts.cut('photon','nocut'))
histAnalysis.SetMCWeight('mcFactors/puWeight')

histAnalysis.MakeReweightHist('../slimmer/files/puWeight_28fb_2016.root', 'puWeight', 'npv', 35, 0, 35)

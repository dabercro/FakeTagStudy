#! /usr/bin/env python

from CrombieTools.AnalysisTools.FitTools import *
from CrombieTools.LoadConfig import cuts

fitTools.SetDebugLevel(fitTools.eDebug)

SetupFromEnv()

fitTools.SetCategoryBranch('fatjet1QGMatching')
fitTools.AddCategory('Quark')
fitTools.AddCategory('Gluon')

fitTools.SetBaseCut(cuts.cut('photon', 'nocut') + ' && fatjet1tau21 < 0.4')
fitTools.SetDefaultExpr('fatjet1PrunedM')
fitTools.SetMCWeight('xsec_v2')
fitTools.SetSignalName('Signal')
fitTools.AddDataFile('fakescale_Data.root')

fitTools.FitCategories(0.0, 150.0, 'Pruned Mass [GeV]')

#!/usr/bin/env python

from CrombieTools.AnalysisTools.HistAnalysis import *
from CrombieTools.LoadConfig import cuts
from CrombieTools import Nminus1Cut
import os, sys

SetupFromEnv()

histAnalysis.SetPrintingMethod(histAnalysis.kPresentation)

histAnalysis.AddDataFile('monojet_MET.root')
histAnalysis.SetSignalName('Signal')
histAnalysis.SetMCWeight(cuts.defaultMCWeight)

def theCuts(cat):
    return [
        ('$m_\\text{pruned}$', 'fatjet1PrunedML2L3 > 65 && fatjet1PrunedML2L3 < 105'),
        ('$\\tau_2/\\tau_1$', 'fatjet1tau21 < 0.6'),
        ('V-tag cut', cuts.cut(cat,'full'))
        ]
 

def printBig(printThis):
    chars = len(printThis)
    print('\n' + '#' * (chars + 4))
    print('# {0} #'.format(printThis))
    print('#' * (chars + 4) + '\n')


def getSmear(cat, whichDir):

    printBig('Smeared' + whichDir)

    histAnalysis.SetBaseCut(Nminus1Cut(cuts.cut(cat,'nocut'),'fatjet1Pt'))
    histAnalysis.ResetScaleFactorCuts()

    for name, cut in theCuts(cat):
        datacut = '(' + cut + ' && fatjet1Pt > 250)'
        mccut = '(' + cut.replace('L2L3','L2L3Smeared' + whichDir) + ' && fatjet1PtSmeared' + whichDir + '  > 250)'
        histAnalysis.AddScaleFactorCut(name, mccut, datacut)

    histAnalysis.DoScaleFactors('n_tightlep',1,0,2)


def main(cat):
    printBig(cat)
    histAnalysis.ResetScaleFactorCuts()
    histAnalysis.SetBaseCut(cuts.cut(cat,'nocut'))

    for name, cut in theCuts(cat):
        histAnalysis.AddScaleFactorCut(name, cut)

    histAnalysis.DoScaleFactors('n_tightlep',1,0,2)


if __name__ == "__main__":
    for cat in ['Zmm', 'gjets']:
        main(cat)
#        for smear in ['Up', 'Down', 'Central']:
#            getSmear(cat, smear)

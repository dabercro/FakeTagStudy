#!/usr/bin/env python

from CrombieTools.AnalysisTools.HistAnalysis import *
from CrombieTools.LoadConfig import cuts
from CrombieTools import Nminus1Cut
import os, sys

SetupFromEnv()

histAnalysis.SetPrintingMethod(histAnalysis.kPresentation)

histAnalysis.SetSignalName('Signal')
histAnalysis.SetMCWeight(cuts.defaultMCWeight)

def theCuts(cat):
    return [
        ('$m_\\text{pruned}$', 'fatjet1PrunedM > 65 && fatjet1PrunedM < 105'),
        ('$\\tau_2/\\tau_1$', 'fatjet1tau21 < 0.6'),
        ('V-tag cut', cuts.cut('full', cat))
        ]
 

def printBig(printThis):
    chars = len(printThis)
    print('\n' + '#' * (chars + 4))
    print('# {0} #'.format(printThis))
    print('#' * (chars + 4) + '\n')


def getSmear(cat, whichDir):

    printBig('Smeared' + whichDir)

    histAnalysis.SetBaseCut(Nminus1Cut(cuts.cut('nocut', cat),'fatjet1Pt'))
    histAnalysis.ResetScaleFactorCuts()

    for name, cut in theCuts(cat):
        datacut = '(' + cut + ' && fatjet1Pt > 250)'
        mccut = '(' + cut.replace('L2L3','L2L3Smeared' + whichDir) + ' && fatjet1PtSmeared' + whichDir + '  > 250)'
        histAnalysis.AddScaleFactorCut(name, mccut, datacut)

    histAnalysis.DoScaleFactors('n_tightlep',1,0,2)


def main(cat):
    printBig(cat)
    histAnalysis.ResetScaleFactorCuts()
    histAnalysis.SetBaseCut(cuts.cut('nocut', cat))

    for name, cut in theCuts(cat):
        histAnalysis.AddScaleFactorCut(name, cut)

    histAnalysis.DoScaleFactors('n_tightlep',1,0,4)


if __name__ == "__main__":
    histAnalysis.AddDataFile('monojet_MET.root')
    main('Zmm')
    histAnalysis.ResetConfig(histAnalysis.kData)
    histAnalysis.AddDataFile('monojet_SinglePhoton.root')
    main('gjets')

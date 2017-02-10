#!/usr/bin/env python

from CrombieTools.AnalysisTools.HistAnalysis import *
from CrombieTools.LoadConfig import cuts
from CrombieTools.PlotTools import AddOutDir
from CrombieTools import Nminus1Cut
import os, sys
from array import array

SetupFromEnv()

histAnalysis.SetPrintingMethod(histAnalysis.kPresentation)

histAnalysis.SetSignalName('Background')
histAnalysis.SetMCWeight(cuts.defaultMCWeight)

def theCuts(cat):
    return [
        ('$m_\\text{pruned}$', 'fatjet1PrunedML2L3 > 65 && fatjet1PrunedML2L3 < 105'),
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

    printBig(cat)

    histAnalysis.SetBaseCut(Nminus1Cut(cuts.cut('nocut', cat),'fatjet1Pt'))
    histAnalysis.ResetScaleFactorCuts()

    for name, cut in theCuts(cat):
        datacut = '(' + cut + ' && fatjet1Pt > 250)'
        mccut = '(' + cut.replace('L2L3','L2L3Smeared' + whichDir) + ' && fatjet1PtSmeared' + whichDir + '  > 250)'
        histAnalysis.AddScaleFactorCut(name, mccut, datacut)

    histAnalysis.DoScaleFactorsCutAndCount('n_tightlep', 0.0, 4.0)


def main(cat):
    printBig(cat)
    histAnalysis.ResetScaleFactorCuts()
    histAnalysis.SetBaseCut(cuts.cut('nocut', cat))

    for name, cut in theCuts(cat):
        histAnalysis.AddScaleFactorCut(name, cut)


    histAnalysis.DoScaleFactorsCutAndCount('n_tightlep', 0.0, 4.0)


if __name__ == "__main__":
    histAnalysis.AddDataFile('../Skim_170111/monojet_Data.root')

    histAnalysis.ReadMCConfig('MCPurity.txt', histAnalysis.kBackground)

    main('gjets')

    histAnalysis.PlotScaleFactors(AddOutDir('scale_npv'), 'npv', 4, 0, 40, 'NPV')
    histAnalysis.PlotScaleFactors(AddOutDir('scale_fatjet1Pt'), 'fatjet1Pt', 4,
                                  array('d', [250, 350, 500, 700, 1000]),
                                  'Fat Jet p_{T} [GeV]')

    exit(0)

    for direction in ['Up', 'Down', 'Central']:
        getSmear('gjets', direction)

    printBig('Scale Up')
    histAnalysis.ChangeBackground(1.0)
    main('gjets')

    printBig('Scale Down')
    histAnalysis.ChangeBackground(-0.5)
    main('gjets')

    printBig('QCD')
    histAnalysis.ChangeBackground(0.0)
    histAnalysis.ResetConfig(histAnalysis.kBackground)
    histAnalysis.ReadMCConfig('MCMonoJet.txt', histAnalysis.kBackground)
    for cat in ['gjets', 'Zee', 'Zmm']:
        main(cat)

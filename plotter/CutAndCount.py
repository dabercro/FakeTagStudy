#!/usr/bin/env python

from CrombieTools.AnalysisTools.HistAnalysis import *
from CrombieTools.LoadConfig import cuts
from CrombieTools import Nminus1Cut
import os, sys

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

    printBig('npv %s to %s' % (0, 10))
    histAnalysis.DoScaleFactorsCutAndCount('npv', 0.0, 10.0)
    printBig('npv %s to %s' % (10, 20))
    histAnalysis.DoScaleFactorsCutAndCount('npv', 10.0, 20.0)
    printBig('npv %s to %s' % (20, 30))
    histAnalysis.DoScaleFactorsCutAndCount('npv', 20.0, 30.0)
    printBig('npv %s to %s' % (30, 40))
    histAnalysis.DoScaleFactorsCutAndCount('npv', 30.0, 40.0)

    printBig('pT %s to %s' % (250, 350))
    histAnalysis.DoScaleFactorsCutAndCount('fatjet1Pt', 250.0, 350.0)
    printBig('pT %s to %s' % (350, 500))
    histAnalysis.DoScaleFactorsCutAndCount('fatjet1Pt', 350.0, 500.0)
    printBig('pT %s to %s' % (500, 700))
    histAnalysis.DoScaleFactorsCutAndCount('fatjet1Pt', 500.0, 700.0)
    printBig('pT %s to %s' % (700, 1000))
    histAnalysis.DoScaleFactorsCutAndCount('fatjet1Pt', 700.0, 1000.0)

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

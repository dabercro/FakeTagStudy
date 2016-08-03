#!/usr/bin/env python

from CrombieTools.AnalysisTools.HistAnalysis import *
from CrombieTools.LoadConfig import cuts
import os, sys

SetupFromEnv()

histAnalysis.SetPrintingMethod(histAnalysis.kPresentation)

histAnalysis.ResetConfig()
histAnalysis.ReadMCConfig('MCSignal.txt')
histAnalysis.AddDataFile('fakescale_Data.root')
histAnalysis.SetSignalName('Signal')
histAnalysis.SetMCWeight('(' + cuts.defaultMCWeight + ' * xsec_v1 * ' + os.environ.get('CrombieLuminosity') + ')')


def printBig(printThis):
    chars = len(printThis)
    print('\n' + '#' * (chars + 4))
    print('# {0} #'.format(printThis))
    print('#' * (chars + 4) + '\n')


def main(cat):
    printBig(cat)
    histAnalysis.ResetScaleFactorCuts()
    histAnalysis.SetBaseCut(cuts.cut(cat,'nocut'))

    histAnalysis.AddScaleFactorCut('m_\\text{pruned}', 'fatjet1PrunedML2L3 > 65 && fatjet1PrunedML2L3 < 105')
    histAnalysis.AddScaleFactorCut('\\tau_2/\\tau_1', 'fatjet1tau21 < 0.6')
    
    histAnalysis.AddScaleFactorCut('V-tag cut', cuts.cut(cat,'full'))
    histAnalysis.DoScaleFactors('n_tightlep',1,0,2)


if __name__ == "__main__":
    main('dilep')
    main('diele')
    main('dimu')
    main('photon')

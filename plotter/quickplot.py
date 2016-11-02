#! /usr/bin/env python

from CrombieTools.PlotTools.QuickPlot import *

SetupFromEnv()

if __name__ == '__main__':
    SetCuts('photon', 'nocut')

    plotter.AddBackground('#gamma + jets (Quark)', 800)
    plotter.AddBackground('#gamma + jets (Gluon)', 609)

    plotter.SetDefaultExpr('fatjet1PrunedML2L3')
    plotter.MakeCanvas('checkshape', 25, 0, 250, 'Fat Jet Pruned Mass [GeV]')

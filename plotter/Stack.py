#!/usr/bin/env python

from CrombieTools.PlotTools.PlotStack import *
from array import array

SetupFromEnv()

plotter.SetStackLineWidth(2)
plotter.SetCMSLabel('Preliminary')
plotter.SetTreeName('events')
plotter.SetAllHistName('htotal')
plotter.SetLegendLocation(plotter.kUpper,plotter.kRight,0.25,0.5)
plotter.SetEventsPer(1.0)
plotter.SetMinLegendFrac(0.0)
plotter.SetIgnoreInLinear(0.005)
plotter.SetOthersColor(922)
plotter.SetFontSize(0.03)
plotter.SetAxisTitleOffset(1.2)
plotter.SetRatioMinMax(0,2)
plotter.SetMakeRatio(True)
plotter.SetForceTop("#gamma + jets (Quark)")

def SetupArgs():
    return [
        ['npv', 50, 0, 50, 'NPV', 'Events/1.0'],
        ['fatjet1Pt', 25, 100, 600, 'p_{T} [GeV]', 'Events/1.0'],
        ['fatjet1Mass', 25, 0, 250, 'Fat Jet Mass [GeV]', 'Events/1.0'],
        ['fatjet1PrunedML2L3', 25, 0, 250, 'Fat Jet Pruned Mass [GeV]', 'Events/1.0'],
        ['fatjet1tau21', 25, 0, 1.5, '#tau_{2}/#tau_{1}', 'Events/1.0'],
        ['met', 6, array('d', [250, 300, 350, 400, 500, 600, 1000]), 'Recoil [GeV]', 'Events/1.0', True],
        ['dilep_m', 30, 0, 150, 'm_{ll} [GeV]', 'Events/1.0'],
        ['dilep_pt', 25, 100, 600, 'p_{T, ll} [GeV]', 'Events/1.0'],
        ]

    if len(sys.argv) > 2:
        return [member for member in return_list if member[0] in sys.argv[2:]]

    return return_list

if __name__ == '__main__':
    plotter.AddDataFile('../Skim_170111/monojet_Data.root')
    MakePlots(
        # Categories
        ['nocut',
         'full',
         'tight',
         ],
        # Regions
        ['signal',
         'Zmm',
         'Wmn',
         'Zee',
         'Wen'
         ],
        # Things to plot
        SetupArgs()
        )

    plotter.ReadMCConfig('MCPurity.txt')
    MakePlots(['nocut', 'full', 'tight'], ['gjets'], SetupArgs())

#!/usr/bin/env python

from CrombieTools.PlotTools.PlotStack import *

SetupFromEnv()

plotter.SetStackLineWidth(2)
plotter.SetCMSLabelType(plotter.kPreliminary)
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

def SetupArgs():
    return [
        ['npv', 50, 0, 50, 'NPV', 'Events/1.0'],
        ['fatjet1Pt', 25, 100, 600, 'p_{T} [GeV]', 'Events/1.0'],
        ['fatjet1Mass', 25, 0, 250, 'Fat Jet Mass [GeV]', 'Events/1.0'],
        ['fatjet1PrunedML2L3', 25, 0, 250, 'Fat Jet Pruned Mass [GeV]', 'Events/1.0'],
        ['fatjet1tau21', 25, 0, 1.5, '#tau_{2}/#tau_{1}', 'Events/1.0'],
        ['met', 20, 200, 1000, 'Recoil [GeV]', 'Events/1.0'],
        ['dilep_m', 30, 0, 150, 'm_{ll} [GeV]', 'Events/1.0'],
        ['dilep_pt', 25, 100, 600, 'p_{T, ll} [GeV]', 'Events/1.0'],
        ]

if __name__ == '__main__':
    plotter.AddDataFile('monojet_MET.root')
    plotter.AddDataFile('monojet_SinglePhoton.root')
    MakePlots(
        # Categories
        ['Zmm',
         ],
        # Regions
        ['nocut',
         'full',
         ],
        # Things to plot
        SetupArgs()
        )

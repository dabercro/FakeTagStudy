#! /usr/bin/python

from applyCorrectionsA import *

addCorr('purityWeight','pho1Pt','1','files/Purity.root','purity')

if __name__ == "__main__":
    RunOnDirectory(applicator)

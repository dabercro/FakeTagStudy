#!/usr/bin/env python

from applyCorrections import *

ewk_z = Corrector.MakeCorrector('ewk_z','genBosPt','abs(genBosPdgId) == 23','files/uncertainties_EWK_24bins.root',['EWKcorr/Z','ZJets_012j_NLO/nominal'])
zkfactor = Corrector.MakeCorrector('zkfactor','genBosPt','abs(genBosPdgId) == 23','files/uncertainties_EWK_24bins.root',['ZJets_012j_NLO/nominal','ZJets_LO/inv_pt'])
applicator.AddCorrector(ewk_z)
applicator.AddCorrector(zkfactor)

if __name__ == "__main__":
    RunOnDirectory(applicator)

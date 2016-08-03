#!/usr/bin/env python

from applyCorrections import *

ewk_a = Corrector.MakeCorrector('ewk_a','genBosPt','genBosPdgId == 22','files/uncertainties_EWK_24bins.root',['EWKcorr/photon','GJets_1j_NLO/nominal_G'])
kfactor  = Corrector.MakeCorrector('kfactor','genBosPt','genBosPdgId == 22','files/uncertainties_EWK_24bins.root',['GJets_1j_NLO/nominal_G','GJets_LO/inv_pt_G'])
applicator.AddCorrector(ewk_a)
applicator.AddCorrector(kfactor)

if __name__ == "__main__":
    RunOnDirectory(applicator)

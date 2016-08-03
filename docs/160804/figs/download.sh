#!/bin/bash

crombie downloadtar "http://dabercro.web.cern.ch/dabercro/plotviewer/viewplot/static/viewplot/returntar.php?only=pdf&files=160803/photon_full_fatjet1tau21,160803/dimu_full_fatjet1tau21,160803/photon_nocut_fatjet1tau21,160803/dimu_nocut_fatjet1tau21,160803/photon_full_fatjet1PrunedML2L3,160803/dimu_full_fatjet1PrunedML2L3,160803/photon_nocut_fatjet1PrunedML2L3,160803/dimu_nocut_fatjet1PrunedML2L3,160803/photon_full_recoil,160803/dimu_full_recoil,160803/photon_nocut_recoil,160803/dimu_nocut_recoil,160803/photon_full_fatjet1Pt,160803/dimu_full_fatjet1Pt,160803/photon_nocut_fatjet1Pt,160803/dimu_nocut_fatjet1Pt"
crombie downloadtar "http://dabercro.web.cern.ch/dabercro/plotviewer/viewplot/static/viewplot/returntar.php?only=pdf&files=160803/dimu_full_dilepMass,160803/dimu_nocut_dilepMass"
crombie downloadtar "http://dabercro.web.cern.ch/dabercro/plotviewer/viewplot/static/viewplot/returntar.php?only=pdf&files=160803/dimu_full_fatjet1DRGenW,160803/dimu_nocut_fatjet1DRGenW"

for f in */*.pdf
do
    pdfcrop $f $f
done

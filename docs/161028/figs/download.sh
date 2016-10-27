#!/bin/bash

crombie downloadtar "http://dabercro.web.cern.ch/dabercro/plotviewer/viewplot/static/viewplot/returntar.php?only=pdf&files=161026/photon_full_fatjet1tau21,161026/photon_nocut_fatjet1tau21,161026/photon_full_fatjet1PrunedML2L3,161026/photon_nocut_fatjet1PrunedML2L3,161026/photon_full_recoil,161026/photon_nocut_recoil"
crombie downloadtar "http://dabercro.web.cern.ch/dabercro/plotviewer/viewplot/static/viewplot/returntar.php?only=pdf&files=161026/photon_full_fatjet1Pt,161026/photon_nocut_fatjet1Pt"
crombie downloadtar "http://dabercro.web.cern.ch/dabercro/plotviewer/viewplot/static/viewplot/returntar.php?only=pdf&files=161027/photon_full_fatjet1tau21,161027/photon_nocut_fatjet1tau21,161027/photon_full_fatjet1PrunedML2L3,161027/photon_nocut_fatjet1PrunedML2L3,161027/photon_full_recoil,161027/photon_nocut_recoil,161027/photon_full_fatjet1Pt,161027/photon_nocut_fatjet1Pt"

for f in */*.pdf
do
    pdfcrop $f $f
done

#!/bin/bash

fresh=$1

source CrombieSlimmingConfig.sh

if [ "$fresh" = "fresh" ]
then
    rm $CrombieSkimDir/*.root 2> /dev/null
fi

crombie skim --cut '(n_loosepho == 0 || n_looselep == 0) && n_bjetsLoose == 0 && recoil > 200' --tree 'events' --copy 'htotal' --run 'runNum' --lumi 'lumiNum' --freq 100000 --numproc $CrombieNLocalProcs --indir $CrombieFullDir --outdir $CrombieSkimDir --json $CrombieGoodRuns

mkdir $CrombieSkimDir/A
mv $CrombieSkimDir/GJets_HT-*.root $CrombieSkimDir/A/.

mkdir $CrombieSkimDir/Z
mv $CrombieSkimDir/DYJetsToLL_M-50_HT-*.root $CrombieSkimDir/Z/.

./applyCorrections.py $CrombieSkimDir

./applyCorrectionsA.py $CrombieSkimDir/A
./applyCorrectionsZ.py $CrombieSkimDir/Z

mv $CrombieSkimDir/A/*.root $CrombieSkimDir/.
mv $CrombieSkimDir/Z/*.root $CrombieSkimDir/.

rmdir $CrombieSkimDir/A $CrombieSkimDir/Z

if [ ! -d ../../Data ]
then
    mkdir ../../Data
fi

hadd -f ../../Data/fakescale_Data.root $CrombieSkimDir/*MET* $CrombieSkimDir/*Single*

crombie skim --cut '(n_loosepho == 0 || n_looselep == 0) && n_bjetsLoose == 0 && recoil > 200' --tree 'events' --copy 'htotal' --run 'runNum' --lumi 'lumiNum' --freq 100000 --numproc 1 --indir ../../Data --outdir $CrombieSkimDir --json $CrombieGoodRuns -d

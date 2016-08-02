#!/bin/bash

fresh=$1

source CrombieSlimmingConfig.sh

if [ "$fresh" = "fresh" ]
then
    rm $CrombieSkimDir/*.root 2> /dev/null
fi

crombie skim --cut 'n_loosepho == 0 && n_bjetsLoose == 0 && recoil > 200' --tree 'events' --copy 'htotal' --run 'runNum' --lumi 'lumiNum' --freq 100000 --numproc $CrombieNLocalProcs --indir $CrombieFullDir --outdir $CrombieSkimDir --json $CrombieGoodRuns

./applyCorrections.py $CrombieSkimDir

if [ ! -d ../Data ]
then
    mkdir ../Data
fi

hadd -f ../Data/fakescale_Data.root $CrombieSkimDir/*MET* $CrombieSkimDir/*SingleElectron*

crombie skim --cut 'n_loosepho == 0 && n_bjetsLoose == 0 && recoil > 200' --tree 'events' --copy 'htotal' --run 'runNum' --lumi 'lumiNum' --freq 100000 --numproc 1 --indir ../Data --outdir $CrombieSkimDir --json $CrombieGoodRuns -d

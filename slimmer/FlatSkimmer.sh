#!/bin/bash

fresh=$1

source CrombieSlimmingConfig.sh

if [ "$fresh" = "fresh" ]
then
    rm $CrombieSkimDir/*.root 2> /dev/null
fi

crombie skim --cut 'leadingJet_outaccp==0 && abs(fatjet1Eta)<2.5 && n_tau==0 && n_bjetsMedium==0 && fatjet1Pt>250. && jet1isMonoJetIdNew==1 && abs(minJetMetDPhi_clean)>0.5' --tree 'events' --copy 'htotal' --run 'runNum' --lumi 'lumiNum' --freq 100000 --numproc $CrombieNLocalProcs --indir $CrombieFullDir --outdir $CrombieSkimDir

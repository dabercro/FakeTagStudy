#!/bin/bash

fresh=$1

source CrombieSlimmingConfig.sh

if [ "$fresh" = "fresh" ]
then
    rm $CrombieSkimDir/*.root 2> /dev/null
fi

crombie skim --cut '(n_loosepho == 0 || n_looselep == 0) && n_bjetsLoose == 0 && recoil > 200' --tree 'events' --copy 'htotal' --run 'runNum' --lumi 'lumiNum' --freq 100000 --numproc $CrombieNLocalProcs --indir $CrombieFullDir --outdir $CrombieSkimDir --json $CrombieGoodRuns

if [ ! -d $CrombieSkimDir/Purity ]
then
    mkdir $CrombieSkimDir/Purity
fi

cp $CrombieSkimDir/*GJets* $CrombieSkimDir/Purity/.

mkdir $CrombieSkimDir/A
mv $CrombieSkimDir/*GJets_HT-*.root $CrombieSkimDir/A/.

mkdir $CrombieSkimDir/Z
# mv $CrombieSkimDir/*DYJetsToLL_M-50_HT-*.root $CrombieSkimDir/Z/.

./applyCorrections.py $CrombieSkimDir

./applyCorrectionsA.py $CrombieSkimDir/A
# ./applyCorrectionsZ.py $CrombieSkimDir/Z

test -d $CrombieSkimDir/Quark || mkdir $CrombieSkimDir/Quark
test -d $CrombieSkimDir/Gluon || mkdir $CrombieSkimDir/Gluon

crombie skim --cut 'fatjet1QGMatching == 0' --tree 'events' --copy 'htotal' --run 'runNum' --lumi 'lumiNum' --freq 100000 --numproc $CrombieNLocalProcs --indir $CrombieSkimDir/A --outdir $CrombieSkimDir/Quark --json $CrombieGoodRuns

crombie skim --cut 'fatjet1QGMatching != 0' --tree 'events' --copy 'htotal' --run 'runNum' --lumi 'lumiNum' --freq 100000 --numproc $CrombieNLocalProcs --indir $CrombieSkimDir/A --outdir $CrombieSkimDir/Gluon --json $CrombieGoodRuns

mv $CrombieSkimDir/A/*.root $CrombieSkimDir/.
# mv $CrombieSkimDir/Z/*.root $CrombieSkimDir/.

./applyPurity.py $CrombieSkimDir/Purity

if [ ! -d ../../Data ]
then
    mkdir ../../Data
fi

# hadd -f ../../Data/fakescale_Data.root $CrombieSkimDir/*Single* $CrombieSkimDir/*MET*

# crombie skim --cut '(n_loosepho == 0 || n_looselep == 0) && n_bjetsLoose == 0 && recoil > 200' --tree 'events' --copy 'htotal' --run 'runNum' --lumi 'lumiNum' --freq 100000 --numproc 1 --indir ../../Data --outdir $CrombieSkimDir --json $CrombieGoodRuns -d

cd $CrombieSkimDir
test -f fakescale_Data.root || ln -s fakescale_SinglePhoton.root fakescale_Data.root
cd -

rmdir $CrombieSkimDir/A $CrombieSkimDir/Z

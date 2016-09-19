source ../slimmer/CrombieSlimmingConfig.sh

export CrombieMCConfig=MCMonoJet.txt
#export CrombieSignalConfig=SignalConfig.txt
#export CrombieExcept_example=MCAdjust.txt
export CrombieLuminosity=12900.0
export CrombieInFilesDir=../../SkimmedMonoJet_160912

if [ "$(hostname)" = "dabercro-MacBookAir" ]
then
    export CrombieOutPlotDir=plots/$CROMBIEDATE
else    
    export CrombieOutPlotDir=/afs/cern.ch/user/d/dabercro/www/plots/$CROMBIEDATE
fi

export CrombieOutLimitTreeDir=limits/$CROMBIEDATE

export CrombieCutsFile=cuts.py

source ../slimmer/CrombieSlimmingConfig.sh

export CrombieMCConfig=MCConfig.txt
#export CrombieMCConfig=MCSignal.txt
#export CrombieSignalConfig=SignalConfig.txt
#export CrombieExcept_example=MCAdjust.txt
export CrombieLuminosity=27600
export CrombieInFilesDir=../../Skim_161103

if [ "$(hostname)" = "dabercro-MacBookAir" ]
then
    export CrombieOutPlotDir=plots/$CROMBIEDATE
else
    export CrombieOutPlotDir=/afs/cern.ch/user/d/dabercro/www/plots/$CROMBIEDATE
fi

export CrombieOutLimitTreeDir=limits/$CROMBIEDATE

export CrombieCutsFile=cuts.py

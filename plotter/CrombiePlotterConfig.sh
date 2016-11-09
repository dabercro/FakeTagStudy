source ../slimmer/CrombieSlimmingConfig.sh

export CrombieMCConfig=MCMonoJet.txt
#export CrombieSignalConfig=SignalConfig.txt
#export CrombieExcept_example=MCAdjust.txt
export CrombieLuminosity=27600.0
export CrombieInFilesDir=/afs/cern.ch/work/z/zdemirag/public/ichep/setup80x/Skim_v12

if [ "$(hostname)" = "dabercro-MacBookAir" ]
then
    export CrombieOutPlotDir=plots/$CROMBIEDATE
else    
    export CrombieOutPlotDir=/afs/cern.ch/user/d/dabercro/www/plots/${CROMBIEDATE}_1
fi

export CrombieOutLimitTreeDir=limits/$CROMBIEDATE

export CrombieCutsFile=cuts.py

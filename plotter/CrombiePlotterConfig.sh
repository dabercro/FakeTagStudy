source ../slimmer/CrombieSlimmingConfig.sh

export CrombieMCConfig=MCMonoJet.txt
#export CrombieSignalConfig=SignalConfig.txt
#export CrombieExcept_example=MCAdjust.txt
export CrombieLuminosity=34100.0
export CrombieInFilesDir=/data/t3home000/dabercro/monojet/Skim_170206

export CrombieOutPlotDir=/home/dabercro/public_html/plots/$(date +%y%m%d)

export CrombieOutLimitTreeDir=limits/$CROMBIEDATE
export CrombieCutsFile=cuts.py

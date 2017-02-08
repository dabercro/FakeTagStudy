source ../slimmer/CrombieSlimmingConfig.sh

#export CrombieMCConfig=MCConfig.txt
export CrombieMCConfig=MCMonoJet.txt
#export CrombieMCConfig=MCSignal.txt
#export CrombieSignalConfig=SignalConfig.txt
export CrombieExcept_gjets=MCPurity.txt

export CrombieLuminosity=34100.0
export CrombieInFilesDir=/data/t3home000/dabercro/monojet/Skim_170208

export CrombieOutPlotDir=/home/dabercro/public_html/plots/$(date +%y%m%d)_FakeTagStudy

export CrombieOutLimitTreeDir=limits/$CROMBIEDATE
export CrombieCutsFile=cuts.py

export CrombieFilesPerJob=20
export CrombieNBatchProcs=4
export CrombieQueue=2nw4cores

if [ "$(hostname)" = "dabercro-MacBookAir" ]
then
    export CrombieNLocalProcs=1
else
    export CrombieNLocalProcs=6
fi

export CrombieFileBase=fakescale
export CrombieEosDir=WithVA.txt
#export CrombieEosDir=80X.txt
export CrombieRegDir=/afs/cern.ch/work/d/dabercro/eoscms/cms$CrombieEosDir
export CrombieTempDir=/afs/cern.ch/work/d/dabercro/public/Fall16/Temp
export CrombieFullDir=../../FullOut_$CROMBIEDATE
export CrombieSkimDir=../../Skim_$CROMBIEDATE
export CrombieDirList=VA.txt

export CrombieSlimmerScript=runSlimmer.py
export CrombieJobScriptList=JobScriptList.txt
export CrombieCheckerScript="$CROMBIEPATH/scripts/findtree.py"

export CrombieGoodRuns=/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/Cert_271036-276811_13TeV_PromptReco_Collisions16_JSON_NoL1T.txt

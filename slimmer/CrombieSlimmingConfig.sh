export CrombieFilesPerJob=20
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
export CrombieFullDir=../../Full_$CROMBIEDATE
export CrombieSkimDir=../../Skim_$CROMBIEDATE
export CrombieDirList=VA.txt

export CrombieSlimmerScript=runSlimmer.py
export CrombieJobScriptList=JobScriptList.txt
export CrombieCheckerScript="$CROMBIEPATH/scripts/findtree.py"

export CrombieGoodRuns=files/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt

export CrombieFilesPerJob=20
export CrombieNBatchProcs=1
export CrombieQueue=1nh

export CrombieNLocalProcs=6

export CrombieFileBase=fakescale
#export CrombieEosDir=/store/user/dabercro/Nero/80X
export CrombieEosDir=80X.txt
export CrombieRegDir=/afs/cern.ch/work/d/dabercro/eoscms/cms$CrombieEosDir
export CrombieTempDir=/afs/cern.ch/work/d/dabercro/public/Fall16/TempOut
export CrombieFullDir=../../Full_$CROMBIEDATE
export CrombieSkimDir=../../Skim_$CROMBIEDATE
#export CrombieDirList=FakeScale.txt

export CrombieSlimmerScript=runSlimmer.py
export CrombieJobScriptList=JobScriptList.txt
export CrombieCheckerScript="$CROMBIEPATH/scripts/findtree.py"

export CrombieGoodRuns=files/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt

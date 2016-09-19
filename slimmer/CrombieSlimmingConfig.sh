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

export CrombieGoodRuns=/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/Cert_271036-276811_13TeV_PromptReco_Collisions16_JSON_NoL1T.txt

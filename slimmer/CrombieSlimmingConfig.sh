export CrombieFilesPerJob=20
export CrombieNBatchProcs=4
export CrombieQueue=2nw4cores

export CrombieNLocalProcs=6

export CrombieFileBase=fakescale
export CrombieEosDir=80X.txt
export CrombieTempDir=/afs/cern.ch/work/d/dabercro/public/Fall16/TempOut
export CrombieFullDir=/afs/cern.ch/work/d/dabercro/public/Fall16/FullOut_$CROMBIEDATE
export CrombieSkimDir=/afs/cern.ch/work/d/dabercro/public/Fall16/SkimOut_$CROMBIEDATE
export CrombieDirList=FakeScale.txt

export CrombieSlimmerScript=runSlimmer.py
export CrombieJobScriptList=JobScriptList.txt
export CrombieCheckerScript="$CROMBIEPATH/scripts/findtree.py"

export CrombieGoodRuns=/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/Cert_271036-276811_13TeV_PromptReco_Collisions16_JSON_NoL1T.txt

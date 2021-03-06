//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Oct 31 14:47:43 2016 by ROOT version 6.02/13
// from TTree events/events
// found on file: root://eoscms.cern.ch//store/group/phys_exotica/monojet/zdemirag/setup80x/Nero/zey_base/GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/GJets_HT-400To600/160709_172352/0000/NeroNtuples_8.root
//////////////////////////////////////////////////////////

#ifndef NeroMonoJet_h
#define NeroMonoJet_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "TClonesArray.h"
#include "vector"
#include "vector"
#include "vector"
#include "TLorentzVector.h"
#include "vector"

class NeroMonoJet {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           isRealData;
   Int_t           runNum;
   Int_t           lumiNum;
   ULong64_t       eventNum;
   Float_t         rho;
   UInt_t          filterSelBits;
   Bool_t          filterbadChCandidate;
   Bool_t          filterbadPFMuon;
   Int_t           npv;
   TClonesArray    *jetP4;
   vector<int>     *jetMatch;
   vector<float>   *jetRawPt;
   vector<float>   *jetRefPt;
   vector<float>   *jetBdiscr;
   vector<float>   *jetBdiscrLegacy;
   vector<float>   *jetPuId;
   vector<float>   *jetUnc;
   vector<float>   *jetQGL;
   vector<int>     *jetQglMult;
   vector<float>   *jetQglPtD;
   vector<float>   *jetQglAxis2;
   vector<int>     *jetFlavour;
   vector<int>     *jetMatchedPartonPdgId;
   vector<int>     *jetMotherPdgId;
   vector<int>     *jetGrMotherPdgId;
   vector<unsigned int> *jetSelBits;
   vector<float>   *jetQ;
   vector<float>   *jetQnoPU;
   vector<float>   *jetPtResUncCentral;
   vector<float>   *jetPtResUncUp;
   vector<float>   *jetPtResUncDown;
   vector<float>   *jetchef;
   vector<float>   *jetnhef;
   TClonesArray    *jetpuppiP4;
   vector<float>   *jetpuppiRawPt;
   vector<float>   *jetpuppiBdiscr;
   vector<unsigned int> *jetpuppiSelBits;
   vector<float>   *jetpuppiQ;
   TClonesArray    *fatjetAK8CHSP4;
   vector<float>   *fatjetAK8CHSRawPt;
   vector<int>     *fatjetAK8CHSFlavour;
   vector<float>   *fatjetAK8CHSTau1;
   vector<float>   *fatjetAK8CHSTau2;
   vector<float>   *fatjetAK8CHSTau3;
   vector<float>   *fatjetAK8CHSTrimmedMass;
   vector<float>   *fatjetAK8CHSPrunedMass;
   vector<float>   *fatjetAK8CHSCorrectedPrunedMass;
   vector<float>   *fatjetAK8CHSSoftdropMass;
   TClonesArray    *fatjetAK8CHSsubjet;
   vector<int>     *fatjetAK8CHSnSubjets;
   vector<int>     *fatjetAK8CHSfirstSubjet;
   vector<float>   *fatjetAK8CHSsubjet_btag;
   vector<float>   *fatjetAK8CHSHbb;
   vector<float>   *fatjetAK8CHStopMVA;
   vector<float>   *fatjetAK8CHSPuppiTau1;
   vector<float>   *fatjetAK8CHSPuppiTau2;
   vector<float>   *fatjetAK8CHSPuppiSoftdropMass;
   TClonesArray    *tauP4;
   vector<int>     *tauMatch;
   vector<unsigned int> *tauSelBits;
   vector<int>     *tauQ;
   vector<float>   *tauM;
   vector<float>   *tauIso;
   vector<float>   *tauChargedIsoPtSum;
   vector<float>   *tauNeutralIsoPtSum;
   vector<float>   *tauIsoDeltaBetaCorr;
   vector<float>   *tauIsoPileupWeightedRaw;
   vector<float>   *tauIsoMva;
   TClonesArray    *lepP4;
   vector<int>     *lepMatch;
   vector<int>     *lepPdgId;
   vector<float>   *lepIso;
   vector<unsigned int> *lepSelBits;
   vector<float>   *lepPfPt;
   vector<float>   *lepMva;
   vector<float>   *lepChIso;
   vector<float>   *lepNhIso;
   vector<float>   *lepPhoIso;
   vector<float>   *lepPuIso;
   vector<float>   *lepEtaSC;
   TClonesArray    *eleP4_smear;
   TClonesArray    *metP4;
   Float_t         metSumEtRaw;
   vector<float>   *metPtJESUP;
   vector<float>   *metPtJESDOWN;
   TClonesArray    *metP4_GEN;
   TLorentzVector  *metPuppi;
   TClonesArray    *metPuppiSyst;
   TClonesArray    *metSyst;
   Float_t         metSumEtRawPuppi;
   TLorentzVector  *metNoMu;
   TLorentzVector  *metNoHF;
   Float_t         metSumEtRawNoHF;
   TLorentzVector  *pfMet_e3p0;
   TLorentzVector  *trackMet;
   TLorentzVector  *neutralMet;
   TLorentzVector  *photonMet;
   TLorentzVector  *HFMet;
   Float_t         caloMet_Pt;
   Float_t         caloMet_Phi;
   Float_t         caloMet_SumEt;
   Float_t         rawMet_Pt;
   Float_t         rawMet_Phi;
   TClonesArray    *photonP4;
   vector<float>   *photonIso;
   vector<float>   *photonSieie;
   vector<unsigned int> *photonSelBits;
   vector<float>   *photonChIso;
   vector<float>   *photonNhIso;
   vector<float>   *photonPhoIso;
   vector<float>   *photonPuIso;
   TClonesArray    *phoP4_smear;
   vector<float>   *photonRawPt;
   vector<float>   *photonE55;
   vector<float>   *photonHOverE;
   vector<float>   *photonChWorstIso;
   vector<float>   *photonChIsoMax;
   vector<float>   *photonSipip;
   vector<float>   *photonSieip;
   vector<float>   *photonR9;
   vector<float>   *photonEtaSC;
   vector<float>   *photonS4;
   vector<float>   *photonMipEnergy;
   vector<float>   *photonTime;
   vector<float>   *photonTimeSpan;
   vector<short>   *photonGenMatched;
   TClonesArray    *genP4;
   TClonesArray    *genjetP4;
   vector<int>     *genPdgId;
   vector<unsigned int> *genFlags;
   Int_t           puTrueInt;
   Float_t         mcWeight;
   Float_t         pdfQscale;
   Float_t         pdfAlphaQED;
   Float_t         pdfAlphaQCD;
   Float_t         pdfX1;
   Float_t         pdfX2;
   Int_t           pdfId1;
   Int_t           pdfId2;
   Float_t         pdfScalePdf;
   Float_t         r2f1;
   Float_t         r5f1;
   Float_t         r1f2;
   Float_t         r2f2;
   Float_t         r1f5;
   Float_t         r5f5;
   vector<float>   *pdfRwgt;
   vector<float>   *genIso;
   vector<float>   *genIsoFrixione;
   vector<int>     *genParent;
   vector<int>     *triggerFired;
   vector<float>   *triggerPrescale;
   vector<int>     *triggerLeps;
   vector<int>     *triggerJets;
   vector<int>     *triggerTaus;
   vector<int>     *triggerPhotons;
   vector<unsigned int> *triggerNoneTaus;

   // List of branches
   TBranch        *b_isRealData;   //!
   TBranch        *b_runNum;   //!
   TBranch        *b_lumiNum;   //!
   TBranch        *b_eventNum;   //!
   TBranch        *b_rho;   //!
   TBranch        *b_selBits;   //!
   TBranch        *b_filterbadChCandidate;   //!
   TBranch        *b_filterbadPFMuon;   //!
   TBranch        *b_npv;   //!
   TBranch        *b_jetP4;   //!
   TBranch        *b_jetMatch;   //!
   TBranch        *b_jetRawPt;   //!
   TBranch        *b_jetRefPt;   //!
   TBranch        *b_jetBdiscr;   //!
   TBranch        *b_jetBdiscrLegacy;   //!
   TBranch        *b_jetPuId;   //!
   TBranch        *b_jetUnc;   //!
   TBranch        *b_jetQGL;   //!
   TBranch        *b_jetQglMult;   //!
   TBranch        *b_jetQglPtD;   //!
   TBranch        *b_jetQglAxis2;   //!
   TBranch        *b_jetFlavour;   //!
   TBranch        *b_jetMatchedPartonPdgId;   //!
   TBranch        *b_jetMotherPdgId;   //!
   TBranch        *b_jetGrMotherPdgId;   //!
   TBranch        *b_jetSelBits;   //!
   TBranch        *b_jetQ;   //!
   TBranch        *b_jetQnoPU;   //!
   TBranch        *b_jetPtResUncCentral;   //!
   TBranch        *b_jetPtResUncUp;   //!
   TBranch        *b_jetPtResUncDown;   //!
   TBranch        *b_jetchef;   //!
   TBranch        *b_jetnhef;   //!
   TBranch        *b_jetpuppiP4;   //!
   TBranch        *b_jetpuppiRawPt;   //!
   TBranch        *b_jetpuppiBdiscr;   //!
   TBranch        *b_jetpuppiSelBits;   //!
   TBranch        *b_jetpuppiQ;   //!
   TBranch        *b_fatjetAK8CHSP4;   //!
   TBranch        *b_fatjetAK8CHSRawPt;   //!
   TBranch        *b_fatjetAK8CHSFlavour;   //!
   TBranch        *b_fatjetAK8CHSTau1;   //!
   TBranch        *b_fatjetAK8CHSTau2;   //!
   TBranch        *b_fatjetAK8CHSTau3;   //!
   TBranch        *b_fatjetAK8CHSTrimmedMass;   //!
   TBranch        *b_fatjetAK8CHSPrunedMass;   //!
   TBranch        *b_fatjetAK8CHSCorrectedPrunedMass;   //!
   TBranch        *b_fatjetAK8CHSSoftdropMass;   //!
   TBranch        *b_fatjetAK8CHSsubjet;   //!
   TBranch        *b_fatjetAK8CHSnSubjets;   //!
   TBranch        *b_fatjetAK8CHSfirstSubjet;   //!
   TBranch        *b_fatjetAK8CHSsubjet_btag;   //!
   TBranch        *b_fatjetAK8CHSHbb;   //!
   TBranch        *b_fatjetAK8CHStopMVA;   //!
   TBranch        *b_fatjetAK8CHSPuppiTau1;   //!
   TBranch        *b_fatjetAK8CHSPuppiTau2;   //!
   TBranch        *b_fatjetAK8CHSPuppiSoftdropMass;   //!
   TBranch        *b_tauP4;   //!
   TBranch        *b_tauMatch;   //!
   TBranch        *b_tauSelBits;   //!
   TBranch        *b_tauQ;   //!
   TBranch        *b_tauM;   //!
   TBranch        *b_tauIso;   //!
   TBranch        *b_tauChargedIsoPtSum;   //!
   TBranch        *b_tauNeutralIsoPtSum;   //!
   TBranch        *b_tauIsoDeltaBetaCorr;   //!
   TBranch        *b_tauIsoPileupWeightedRaw;   //!
   TBranch        *b_tauIsoMva;   //!
   TBranch        *b_lepP4;   //!
   TBranch        *b_lepMatch;   //!
   TBranch        *b_lepPdgId;   //!
   TBranch        *b_lepIso;   //!
   TBranch        *b_lepSelBits;   //!
   TBranch        *b_lepPfPt;   //!
   TBranch        *b_lepMva;   //!
   TBranch        *b_lepChIso;   //!
   TBranch        *b_lepNhIso;   //!
   TBranch        *b_lepPhoIso;   //!
   TBranch        *b_lepPuIso;   //!
   TBranch        *b_lepEtaSC;   //!
   TBranch        *b_eleP4_smear;   //!
   TBranch        *b_metP4;   //!
   TBranch        *b_metSumEtRaw;   //!
   TBranch        *b_metPtJESUP;   //!
   TBranch        *b_metPtJESDOWN;   //!
   TBranch        *b_metP4_GEN;   //!
   TBranch        *b_metPuppi;   //!
   TBranch        *b_metPuppiSyst;   //!
   TBranch        *b_metSyst;   //!
   TBranch        *b_metSumEtRawPuppi;   //!
   TBranch        *b_metNoMu;   //!
   TBranch        *b_metNoHF;   //!
   TBranch        *b_metSumEtRawNoHF;   //!
   TBranch        *b_pfMet_e3p0;   //!
   TBranch        *b_trackMet;   //!
   TBranch        *b_neutralMet;   //!
   TBranch        *b_photonMet;   //!
   TBranch        *b_HFMet;   //!
   TBranch        *b_caloMet_Pt;   //!
   TBranch        *b_caloMet_Phi;   //!
   TBranch        *b_caloMet_SumEt;   //!
   TBranch        *b_rawMet_Pt;   //!
   TBranch        *b_rawMet_Phi;   //!
   TBranch        *b_photonP4;   //!
   TBranch        *b_photonIso;   //!
   TBranch        *b_photonSieie;   //!
   TBranch        *b_photonSelBits;   //!
   TBranch        *b_photonChIso;   //!
   TBranch        *b_photonNhIso;   //!
   TBranch        *b_photonPhoIso;   //!
   TBranch        *b_photonPuIso;   //!
   TBranch        *b_phoP4_smear;   //!
   TBranch        *b_photonRawPt;   //!
   TBranch        *b_photonE55;   //!
   TBranch        *b_photonHOverE;   //!
   TBranch        *b_photonChWorstIso;   //!
   TBranch        *b_photonChIsoMax;   //!
   TBranch        *b_photonSipip;   //!
   TBranch        *b_photonSieip;   //!
   TBranch        *b_photonR9;   //!
   TBranch        *b_photonEtaSC;   //!
   TBranch        *b_photonS4;   //!
   TBranch        *b_photonMipEnergy;   //!
   TBranch        *b_photonTime;   //!
   TBranch        *b_photonTimeSpan;   //!
   TBranch        *b_photonGenMatched;   //!
   TBranch        *b_genP4;   //!
   TBranch        *b_genjetP4;   //!
   TBranch        *b_genPdgId;   //!
   TBranch        *b_genFlags;   //!
   TBranch        *b_puTrueInt;   //!
   TBranch        *b_mcWeight;   //!
   TBranch        *b_pdfQscale;   //!
   TBranch        *b_pdfAlphaQED;   //!
   TBranch        *b_pdfAlphaQCD;   //!
   TBranch        *b_pdfX1;   //!
   TBranch        *b_pdfX2;   //!
   TBranch        *b_pdfId1;   //!
   TBranch        *b_pdfId2;   //!
   TBranch        *b_pdfScalePdf;   //!
   TBranch        *b_r2f1;   //!
   TBranch        *b_r5f1;   //!
   TBranch        *b_r1f2;   //!
   TBranch        *b_r2f2;   //!
   TBranch        *b_r1f5;   //!
   TBranch        *b_r5f5;   //!
   TBranch        *b_pdfRwgt;   //!
   TBranch        *b_genIso;   //!
   TBranch        *b_genIsoFrixione;   //!
   TBranch        *b_genParent;   //!
   TBranch        *b_triggerFired;   //!
   TBranch        *b_triggerPrescale;   //!
   TBranch        *b_triggerLeps;   //!
   TBranch        *b_triggerJets;   //!
   TBranch        *b_triggerTaus;   //!
   TBranch        *b_triggerPhotons;   //!
   TBranch        *b_triggerNoneTaus;   //!

   NeroMonoJet(TTree *tree=0);
   virtual ~NeroMonoJet();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

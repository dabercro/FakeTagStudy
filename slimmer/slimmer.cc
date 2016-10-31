#include <algorithm>
#include <iostream>
#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TF1.h"
#include "TMath.h"

#include "KinematicFunctions.h"
#include "OutTree.h"
#include "NeroMonoJet.h"
#include "JetSmearer.h"

enum TauSelection{
  TauBaseline = 1UL << 0,
  TauDecayModeFindingNewDMs = 1UL << 1,
  TauDecayModeFinding = 1UL << 2,
  AgainstEleLoose = 1UL <<8,
  AgainstEleMedium = 1UL<<9,
  AgainstMuLoose = 1UL<<10,
  AgainstMuTight = 1UL<<11,
  byLooseIsolationMVArun2v1DBoldDMwLT = 1UL <<12,
  byMediumIsolationMVArun2v1DBoldDMwLT= 1UL <<13,
  byTightIsolationMVArun2v1DBoldDMwLT = 1UL <<14,
  byVTightIsolationMVArun2v1DBoldDMwLT= 1UL <<15,
  byLooseIsolationMVArun2v1DBnewDMwLT = 1UL <<16,
  byMediumIsolationMVArun2v1DBnewDMwLT= 1UL <<17,
  byTightIsolationMVArun2v1DBnewDMwLT = 1UL <<18,
  byVTightIsolationMVArun2v1DBnewDMwLT= 1UL <<19,
};

enum IsoType {
  kIsoVeto = 0,
  kIsoLoose,
  kIsoMedium,
  kIsoTight
};

Bool_t PassIso(Float_t lepPt, Float_t lepEta, Float_t lepIso, Int_t lepPdgId, IsoType isoType) {

  Float_t isoCut = 0.;

  if (abs(lepPdgId) == 13) {
    isoCut = (isoType == kIsoTight) ? 0.12 : 0.20;
  }
  else {
    switch (isoType) {
    case kIsoVeto:
      isoCut = (fabs(lepEta) <= 1.479) ? 0.126 : 0.144;
      break;
    case kIsoLoose:
      isoCut = (fabs(lepEta) <= 1.479) ? 0.0893 : 0.121;
      break;
    case kIsoMedium:
      isoCut = (fabs(lepEta) <= 1.479) ? 0.01603226 : 0.0678;
      break;
    case kIsoTight:
      isoCut = (fabs(lepEta) <= 1.479) ? 0.0354 : 0.0646;
      break;
    default:
      break;
    }
  }
  return (lepIso/lepPt) < isoCut;
}

float GetMaxBTag(Int_t iFatjet, NeroMonoJet *inTree) {
  Int_t nSubjets = (*(inTree->fatjetAK8CHSnSubjets))[iFatjet];
  Int_t firstSubjet = (*(inTree->fatjetAK8CHSfirstSubjet))[iFatjet];
  float maxsjbtag = -1.0;
  for (int iSJ=firstSubjet; iSJ!=nSubjets+firstSubjet; ++iSJ)
    maxsjbtag = TMath::Max(maxsjbtag,(*(inTree->fatjetAK8CHSsubjet_btag))[iSJ]);

  return maxsjbtag;
}

void slimmer(TString inFileName, TString outFileName, Bool_t isSig = false) {

  Float_t dROverlap  = 0.4;
  Float_t dRGenMatch = 0.2;
  Float_t bCutLoose  = 0.605;
  Float_t bCutMedium = 0.89;
  Float_t bCutTight  = 0.97;

  TFile *outFile = new TFile(outFileName,"RECREATE");
  OutTree *outTree = new OutTree("events", outFile);
  TH1F *allHist = new TH1F("htotal","htotal",1,-1,1);

  TFile *inFile           = TFile::Open(inFileName);
  TTree *inTreeFetch      = (TTree*) inFile->Get("nero/events");
  NeroMonoJet *inTree     = new NeroMonoJet(inTreeFetch);
  TTree *allTree          = (TTree*) inFile->Get("nero/all");
  Float_t mcWeight        = 0.;
  TBranch *mcWeightBranch = allTree->GetBranch("mcWeight");
  mcWeightBranch->SetAddress(&mcWeight);

  TLorentzVector vec1;
  TLorentzVector vec2;
  TLorentzVector vec3;

  TLorentzVector saveGenVec;
  TLorentzVector saveDMVec;

  JetSmearer *smearer = new JetSmearer(inTree);
  smearer->ReadSFConfig("files/Spring16_25nsV6_MC_SF_AK8PFchs.txt");
  smearer->ReadResConfig("files/Spring16_25nsV6_MC_PtResolution_AK8PFchs.txt");

  Int_t nentries = inTreeFetch->GetEntriesFast();

  std::vector<TLorentzVector*> leptonVecs;
  std::vector<TLorentzVector*> photonVecs;

  Float_t checkDR = 0.0;

  for (Int_t iEntry = 0; iEntry < allTree->GetEntriesFast(); iEntry++) {
    mcWeightBranch->GetEntry(iEntry);
    if (mcWeight > 0)
      allHist->Fill(0.0,1.0);
    else if (mcWeight < 0)
      allHist->Fill(0.0,-1.0);
  }

  outFile->WriteTObject(allHist,allHist->GetName());

  for (Int_t iEntry = 0; iEntry < nentries; iEntry++) {

    outTree->Reset();

    //// Clear out the saved vectors for cleaning ////

    leptonVecs.resize(0);
    photonVecs.resize(0);

    if (iEntry % 10000 == 0)
      std::cout << "Processing events: ... " << float(iEntry)/float(nentries)*100 << "%" << std::endl;

    inTree->GetEntry(iEntry);

    //// Fill some global event values ////

    outTree->runNum    = inTree->runNum;
    outTree->lumiNum   = inTree->lumiNum;
    outTree->eventNum  = inTree->eventNum;
    outTree->npv       = inTree->npv;

    if (isSig)
      outTree->mcWeight = inTree->mcWeight;
    else {
      if (inTree->mcWeight < 0)
        outTree->mcWeight = -1;
      else
        outTree->mcWeight = 1;
    }

    outTree->met    = ((TLorentzVector*)((*(inTree->metP4))[0]))->Pt();
    outTree->metPhi = ((TLorentzVector*)((*(inTree->metP4))[0]))->Phi();

    outTree->triggerFired = inTree->triggerFired;

    // std::cout << "//// Here is the lepton filling ////" << std::endl;

    for (Int_t iLepton = 0; iLepton < inTree->lepP4->GetEntries(); iLepton++) {
      TLorentzVector* tempLepton = (TLorentzVector*) inTree->lepP4->At(iLepton);

      //// Rejecting leptons with Eta cuts ////

      if ((fabs(tempLepton->Eta()) > 2.5) ||
          (fabs(tempLepton->Eta()) > 2.4 && fabs((*(inTree->lepPdgId))[iLepton]) == 13))
        continue;

      //// Filling lepton values based on loose cut for muons and veto cut for electrons ////

      if (tempLepton->Pt() > 10. && (
          ( fabs((*(inTree->lepPdgId))[iLepton]) == 13 && ((*(inTree->lepSelBits))[iLepton] & 16) == 16 &&
            PassIso(tempLepton->Pt(),tempLepton->Eta(),(*(inTree->lepIso))[iLepton],(*(inTree->lepPdgId))[iLepton],kIsoLoose)
          ) ||
          (fabs((*(inTree->lepPdgId))[iLepton]) == 11 && ((*(inTree->lepSelBits))[iLepton] & 2) == 2 &&
            PassIso(tempLepton->Pt(),tempLepton->Eta(),(*(inTree->lepIso))[iLepton],(*(inTree->lepPdgId))[iLepton],kIsoVeto)
          )
          )) {

        outTree->n_looselep++;
        if (outTree->n_looselep == 1) {
          outTree->lep1Pt    = tempLepton->Pt();
          outTree->lep1Eta   = tempLepton->Eta();
          outTree->lep1Phi   = tempLepton->Phi();
          outTree->lep1PdgId = (*(inTree->lepPdgId))[iLepton];
          outTree->lep1IsMedium = 0;
          outTree->lep1IsTight  = 0;
          outTree->lep1RelIso = (*(inTree->lepIso))[iLepton]/outTree->lep1Pt;
        }
        else if (outTree->n_looselep == 2) {
          outTree->lep2Pt    = tempLepton->Pt();
          outTree->lep2Eta   = tempLepton->Eta();
          outTree->lep2Phi   = tempLepton->Phi();
          outTree->lep2PdgId = (*(inTree->lepPdgId))[iLepton];
          outTree->lep2IsMedium = 0;
          outTree->lep2IsTight  = 0;
          outTree->lep2RelIso = (*(inTree->lepIso))[iLepton]/outTree->lep2Pt;
        }

        if (tempLepton->Pt() > 20. && ((*(inTree->lepSelBits))[iLepton] & 32) == 32 &&
            PassIso(tempLepton->Pt(),tempLepton->Eta(),(*(inTree->lepIso))[iLepton],(*(inTree->lepPdgId))[iLepton],kIsoMedium)) {

          outTree->n_mediumlep +=1;
          if (outTree->n_looselep == 1)
            outTree->lep1IsMedium = 1;
          else if (outTree->n_looselep == 2)
            outTree->lep2IsMedium = 1;
        }

        //// We are cleaning tight leptons from jets ////

        if (tempLepton->Pt() > 20. && ((*(inTree->lepSelBits))[iLepton] & 64) == 64 &&
            PassIso(tempLepton->Pt(),tempLepton->Eta(),(*(inTree->lepIso))[iLepton],(*(inTree->lepPdgId))[iLepton],kIsoTight) &&
            (abs((*(inTree->lepPdgId))[iLepton]) == 13 || tempLepton->Pt() > 40.)) {

          leptonVecs.push_back(tempLepton);
          outTree->n_tightlep +=1;
          if (outTree->n_looselep == 1)
            outTree->lep1IsTight = 1;
          else if (outTree->n_looselep == 2)
            outTree->lep2IsTight = 1;
        }
      }
    }

    if (outTree->n_looselep > 1) {
      vec1.SetPtEtaPhiM(outTree->lep1Pt, outTree->lep1Eta, outTree->lep1Phi, 0.0);
      vec2.SetPtEtaPhiM(outTree->lep2Pt, outTree->lep2Eta, outTree->lep2Phi, 0.0);
      vec3 = vec1 + vec2;

      outTree->dilepPt = vec3.Pt();
      outTree->dilepEta = vec3.Eta();
      outTree->dilepPhi = vec3.Phi();
      outTree->dilepMass = vec3.M();
      vec1.SetPtEtaPhiM(outTree->met, 0.0, outTree->metPhi, 0.0);
      vec2 = vec1 + vec3;
      outTree->recoil = vec2.Pt();
    }

    // std::cout << "//// Now we go on to look at photons ////" << std::endl;

    for (Int_t iPhoton = 0; iPhoton < inTree->photonP4->GetEntries(); iPhoton++) {
      TLorentzVector* tempPhoton = (TLorentzVector*) inTree->photonP4->At(iPhoton);

      //// Set photon cuts at some pt and eta ////

      if (tempPhoton->Pt() < 15. || fabs(tempPhoton->Eta()) > 2.5 ||
          ((*(inTree->photonSelBits))[iPhoton] & 8) != 8)
        continue;

      outTree->n_loosepho++;

      if (outTree->pho1Pt < 0) {
        outTree->pho1Pt = tempPhoton->Pt();
        outTree->pho1Eta = tempPhoton->Eta();
        outTree->pho1Phi = tempPhoton->Phi();
      }

      //// Usign the medium photon collection for futher cleaning ////
      if (tempPhoton->Pt() > 175 && ((*(inTree->photonSelBits))[iPhoton] & 16) == 16) {
        photonVecs.push_back(tempPhoton);
        outTree->n_mediumpho++;
      }

    }

    if (outTree->pho1Pt > 0 && outTree->recoil < 0) {
      vec1.SetPtEtaPhiM(outTree->pho1Pt,outTree->pho1Eta,outTree->pho1Phi,0.0);
      vec2.SetPtEtaPhiM(outTree->met,0.0,outTree->metPhi,0.0);
      vec3 = vec1 + vec2;
      outTree->recoil = vec3.Pt();
    }

    // if (outTree->recoil < 0)
    //   continue;

    Double_t checkDPhi = 5.0;
    Double_t clean_checkDPhi = 5.0;

    for (Int_t iJet = 0; iJet < inTree->jetP4->GetEntries(); iJet++) {
      TLorentzVector* tempJet = (TLorentzVector*) inTree->jetP4->At(iJet);

      outTree->jet_ht += tempJet->Pt();

      //// Ignore jets that are not in this region ////

      if (fabs(tempJet->Eta()) > 2.4 || (*(inTree->jetPuId))[iJet] < -0.62 || tempJet->Pt() < 30.0)
        continue;

      //// Now do cleaning ////

      Bool_t match = false;

      for (UInt_t iLepton = 0; iLepton < leptonVecs.size(); iLepton++) {
        if (deltaR(leptonVecs[iLepton]->Phi(),leptonVecs[iLepton]->Eta(),tempJet->Phi(),tempJet->Eta()) < dROverlap) {
          match = true;
          break;
        }
      }

      if (match)
        continue;

      for (UInt_t iPhoton = 0; iPhoton < photonVecs.size(); iPhoton++) {
        if (deltaR(photonVecs[iPhoton]->Phi(),photonVecs[iPhoton]->Eta(),tempJet->Phi(),tempJet->Eta()) < dROverlap) {
          match = true;
          break;
        }
      }

      if (match)
        continue;

      outTree->n_jetsTot++;
      outTree->jet_ht_boosted += tempJet->Pt();

      //// Count jets for b-tagging ////

      float dR_1 = dROverlap + 0.1;
      float dR_2 = dROverlap + 0.1;

      if (outTree->lep1Pt > 0)
        dR_1 = deltaR(outTree->lep1Phi, outTree->lep1Eta, tempJet->Phi(),tempJet->Eta());
      if (outTree->lep2Pt > 0)
        dR_2 = deltaR(outTree->lep2Phi, outTree->lep2Eta, tempJet->Phi(),tempJet->Eta());

      if (dR_1 > dROverlap && dR_2 > dROverlap) {
        if ((*(inTree->jetBdiscr))[iJet] > bCutTight)
          outTree->n_bjetsTight++;
        if ((*(inTree->jetBdiscr))[iJet] > bCutMedium)
          outTree->n_bjetsMedium++;
        if ((*(inTree->jetBdiscr))[iJet] > bCutLoose)
          outTree->n_bjetsLoose++;
        else
          continue;
      }
    }

    // std::cout << "//// Now check number of non-overlapping taus ////" << std::endl;

    for (Int_t iTau = 0; iTau < inTree->tauP4->GetEntries(); iTau++) {
      TLorentzVector* tempTau = (TLorentzVector*) inTree->tauP4->At(iTau);

      if (tempTau->Pt() < 18. || fabs(tempTau->Eta()) > 2.3)
        continue;

      if ((inTree->tauSelBits->at(iTau) & TauDecayModeFinding) != TauDecayModeFinding)
        continue;
      if ((inTree->tauSelBits->at(iTau) & TauDecayModeFindingNewDMs) != TauDecayModeFindingNewDMs)
        continue;

      if ((*(inTree->tauIsoDeltaBetaCorr))[iTau] > 5.0)
        continue;

      //// Now do cleaning ////

      Bool_t match = false;

      for (UInt_t iLepton = 0; iLepton < leptonVecs.size(); iLepton++) {
        if (deltaR(leptonVecs[iLepton]->Phi(),leptonVecs[iLepton]->Eta(),tempTau->Phi(),tempTau->Eta()) < dROverlap) {
          match = true;
          break;
        }
      }

      if (match)
        continue;

      float dR_1 = dROverlap + 0.1;
      float dR_2 = dROverlap + 0.1;

      if (outTree->lep1Pt > 0)
        dR_1 = deltaR(outTree->lep1Phi, outTree->lep1Eta, tempTau->Phi(),tempTau->Eta());
      if (outTree->lep2Pt > 0)
        dR_2 = deltaR(outTree->lep2Phi, outTree->lep2Eta, tempTau->Phi(),tempTau->Eta());

      if (dR_1 > dROverlap && dR_2 > dROverlap)
        outTree->n_tau++;
    }

    // std::cout << "//// Fat Jet Selection ////" << std::endl;

    // Count jets that don't overlap with W jets

    Float_t overlapjetDR = 0.6;
    Int_t overlapping = 0;

    for (Int_t iFatJet = 0; iFatJet < inTree->fatjetAK8CHSP4->GetEntries(); iFatJet++) {
      TLorentzVector* tempFatJet = (TLorentzVector*) inTree->fatjetAK8CHSP4->At(iFatJet);

      // std::cout << "// Clean the fat jets" << std::endl;

      Bool_t match = false;

      for (UInt_t iLepton = 0; iLepton < leptonVecs.size(); iLepton++) {
        if (deltaR(leptonVecs[iLepton]->Phi(),leptonVecs[iLepton]->Eta(),tempFatJet->Phi(),tempFatJet->Eta()) < 2.0 * dROverlap) {
          match = true;
          break;
        }
      }

      for (UInt_t iPhoton = 0; iPhoton < photonVecs.size(); iPhoton++) {
        if (deltaR(photonVecs[iPhoton]->Phi(),photonVecs[iPhoton]->Eta(),tempFatJet->Phi(),tempFatJet->Eta()) < 2.0 * dROverlap) {
          match = true;
          break;
        }
      }

      // std::cout << "Done checking" << std::endl;

      if (match)
        continue;

      // std::cout << "No matches" << std::endl;
      // std::cout << tempFatJet << std::endl;

      if (outTree->fatjet1Pt < 0) {
        outTree->fatjet1Pt   = tempFatJet->Pt();
        outTree->fatjet1Eta  = tempFatJet->Eta();
        outTree->fatjet1Phi  = tempFatJet->Phi();
        outTree->fatjet1Mass = tempFatJet->M();
        outTree->fatjet1PrunedML2L3 = (*(inTree->fatjetAK8CHSCorrectedPrunedMass))[iFatJet];
        outTree->fatjet1PrunedMuncorr = (*(inTree->fatjetAK8CHSPrunedMass))[iFatJet];
        outTree->fatjet1PrunedM = outTree->fatjet1Pt/(*(inTree->fatjetAK8CHSRawPt))[iFatJet] * outTree->fatjet1PrunedMuncorr;
        outTree->fatjet1SoftDropM = (*(inTree->fatjetAK8CHSSoftdropMass))[iFatJet];
        outTree->fatjet1tau21 = (*(inTree->fatjetAK8CHSTau2))[iFatJet]/(*(inTree->fatjetAK8CHSTau1))[iFatJet];
        outTree->fatjet1tau32 = (*(inTree->fatjetAK8CHSTau3))[iFatJet]/(*(inTree->fatjetAK8CHSTau2))[iFatJet];
        // outTree->fatjet1QJetVol = (*(inTree->fatjetAK8CHSQJetVol))[iFatJet];

        outTree->fatjet1MaxBTag = GetMaxBTag(iFatJet,inTree);

        for (Int_t iJet = 0; iJet < inTree->jetP4->GetEntries(); iJet++) {
          TLorentzVector* tempJet = (TLorentzVector*) inTree->jetP4->At(iJet);
          checkDR = deltaR(outTree->fatjet1Phi,outTree->fatjet1Eta,tempJet->Phi(),tempJet->Eta());

          if (tempJet->Pt() > 30 && checkDR < overlapjetDR)
            ++overlapping;
        }

        if (inTree->metP4_GEN->GetEntries() > 0) {

          // std::cout << "Gen Checking" << std::endl;

          Int_t WIndex = -1;

          Double_t QGEnergy = 0.0;
          Int_t QGCat = -1;

          for (Int_t iGen = 0; iGen < inTree->genP4->GetEntries(); iGen++) {
            TLorentzVector *tempGen = (TLorentzVector*) inTree->genP4->At(iGen);
            Int_t checkPdgId = abs((*(inTree->genPdgId))[iGen]);

            if (checkPdgId < 6)
              QGCat = 0;
            else if (checkPdgId == 21)
              QGCat = 1;

            if (QGCat != -1) {
              if (tempGen->Energy() > QGEnergy) {
                QGEnergy = tempGen->Energy();
                outTree->fatjet1QGMatching = QGCat;
              }
            }

            if (checkPdgId < 22 || checkPdgId > 24)
              continue;

            if (tempGen->Pt() < 100)
              continue;

            if (outTree->genBosPt < tempGen->Pt()) {
              outTree->genBosPt = tempGen->Pt();
              outTree->genBosPdgId = (*(inTree->genPdgId))[iGen];
            }

            checkDR = deltaR(outTree->fatjet1Phi,outTree->fatjet1Eta,tempGen->Phi(),tempGen->Eta());
            if (checkDR < outTree->fatjet1DRGenW) {
              outTree->fatjet1DRGenW   = checkDR;
              WIndex = iGen;
            }
          }

          // std::cout << "Gen Checking Done" << std::endl;
        }
      }
    }

    // if (outTree->fatjet1Pt < 0)
    //   continue;

    outTree->fatjet1DPhiMet = deltaPhi(outTree->fatjet1Phi,outTree->metPhi);

    float pt1 = -0.5;
    float pt2 = -0.5;

    if (inTree->metP4_GEN->GetEntries() > 0) {
      for (Int_t iGen = 0; iGen < inTree->genP4->GetEntries(); iGen++) {
        Int_t checkPdgId = (*(inTree->genPdgId))[iGen];
        if (abs(checkPdgId) == 6){
          if (checkPdgId > 0)
            pt1 = ((TLorentzVector*) inTree->genP4->At(iGen))->Pt();
          else
            pt2 = ((TLorentzVector*) inTree->genP4->At(iGen))->Pt();
        }
      }
      if (pt1 > 0.0 && pt2 > 0.0)
        outTree->topPtReweighting = sqrt(exp(0.156 - 0.00137*min(pt1,float(400.0))) *
                                         exp(0.156 - 0.00137*min(pt2,float(400.0)))) / 0.88;
    }

    outTree->n_jetsNotFat = outTree->n_jetsTot - overlapping;

    if (outTree->fatjet1Pt > 0) {
      outTree->fatjet1PtSmearedCentral = smearer->GetSmeared(inTree->rho, outTree->fatjet1Pt, outTree->fatjet1Eta, outTree->fatjet1Phi,
                                                             outTree->fatjet1Pt, kCentral);
      outTree->fatjet1PtSmearedUp   =    smearer->GetSmeared(inTree->rho, outTree->fatjet1Pt, outTree->fatjet1Eta, outTree->fatjet1Phi,
                                                             outTree->fatjet1Pt, kUp);
      outTree->fatjet1PtSmearedDown =    smearer->GetSmeared(inTree->rho, outTree->fatjet1Pt, outTree->fatjet1Eta, outTree->fatjet1Phi,
                                                             outTree->fatjet1Pt, kDown);
      outTree->fatjet1PrunedML2L3SmearedCentral = smearer->GetSmeared(inTree->rho, outTree->fatjet1Pt, outTree->fatjet1Eta, outTree->fatjet1Phi,
                                                                      outTree->fatjet1PrunedML2L3, kCentral);
      outTree->fatjet1PrunedML2L3SmearedUp   =    smearer->GetSmeared(inTree->rho, outTree->fatjet1Pt, outTree->fatjet1Eta, outTree->fatjet1Phi,
                                                                      outTree->fatjet1PrunedML2L3, kUp);
      outTree->fatjet1PrunedML2L3SmearedDown =    smearer->GetSmeared(inTree->rho, outTree->fatjet1Pt, outTree->fatjet1Eta, outTree->fatjet1Phi,
                                                                      outTree->fatjet1PrunedML2L3, kDown);
    }

    outTree->Fill();

  }

  outTree->WriteToFile(outFile);
  outFile->Close();
  inFile->Close();

  delete smearer;
}

from CrombieTools import Nminus1Cut
import os

#metfilter_real = 'metfilter==1 && filterbadChCandidate==1 && filterbadPFMuon==1'
metfilter = 'metfilter==1 && filterbadChCandidate==1 && filterbadPFMuon==1'
#metfilter      = '(1.0)'

balance = '(abs(caloMet-trueMet)/met) < 0.5'

#monojet
met           = 'met>200'        
leadingjetpT  = 'jet1Pt>100.'
leadingjeteta = 'abs(jet1Eta)<2.5'
jetcleaning   = 'jet1isMonoJetIdNew==1'
deltaPhi      = 'abs(minJetMetDPhi_withendcap) > 0.5'
inversemonov  = '(fatjet1Pt<250. || fatjet1tau21 > 0.6 || fatjet1PrunedML2L3 < 65 || met < 250. || fatjet1PrunedML2L3>105)'
jetoutofaccp  = 'leadingJet_outaccp==0'

monojet = str(balance+'&&'+met+'&&'+leadingjetpT+'&&'+leadingjeteta+'&&'+jetcleaning+'&&'+deltaPhi+'&&'+metfilter+'&&'+jetoutofaccp)

############

#monoV
metv              = 'met>250'        
leadingfatjetpT   = 'fatjet1Pt>250.'
leadingfatjeteta  = 'abs(fatjet1Eta)<2.4'
jetsubstructure   = 'fatjet1tau21 < 0.45'
prunedmass        = 'fatjet1PrunedML2L3 > 65 && fatjet1PrunedML2L3 < 105'
        
monoveto = ' && '.join([
        metv,
        leadingfatjetpT,
        leadingfatjeteta,
        jetsubstructure,
        prunedmass
        ])

monov = ' && '.join([
        monoveto,
#        balance,
        deltaPhi,
        jetcleaning,
        jetoutofaccp
        ])

############
#vbf
vbfjetpT   = 'jot1Pt>100. && jot2Pt > 40. && abs(jot1Eta)<4.7 && abs(jot2Eta)<4.7'
vbfjeteta  = 'jot1Eta*jot2Eta < 0'
detajj     = 'abs(jjDEta) > 3.0'

vbf = ' && '.join([
        balance,
        met,
        vbfjetpT,
        vbfjeteta,
        detajj,
        deltaPhi,
        jetoutofaccp
        ])

############
tauveto    = 'n_tau==0'
btagveto   = 'n_bjetsMedium==0'
leptonveto = 'n_looselep==0'
phoveto    = 'n_loosepho==0'


#** Control Regions
leadinglepID = 'n_tightlep > 0'
Zmm_r   = '((n_looselep == 2 && dilep_m > 61 && dilep_m < 121 && (lep1PdgId*lep2PdgId == -169)))'
Zee_r   = '((n_looselep == 2 && dilep_m > 61 && dilep_m < 121 && (lep1PdgId*lep2PdgId == -121)))'
Wmn_r   = '((n_looselep == 1 && abs(lep1PdgId)==13 && mt<160))'
Wen_r   = '((n_looselep == 1 && abs(lep1PdgId)==11 && trueMet>50. && mt<160))'
gjets_r = '((photonPt > 175 && abs(photonEta) < 1.4442 && n_mediumpho == 1 && n_loosepho == 1))'

Zee  = ' && '.join([
        Zee_r,
        phoveto,
        tauveto,
        btagveto,
        leadinglepID,
        ])

Zmm  = ' && '.join([
        Zmm_r,
        phoveto,
        tauveto,
        btagveto,
        leadinglepID
        ])

Wen  = ' && '.join([
        Wen_r,
        phoveto,
        tauveto,
        btagveto,
        leadinglepID
        ])

Wmn  = ' && '.join([
        Wmn_r,
        phoveto,
        tauveto,
        btagveto,
        leadinglepID
        ])

gjet = ' && '.join([
        gjets_r,
        leptonveto,
        tauveto,
        btagveto
        ])

signal = ' && '.join([
        phoveto,
        tauveto,
        btagveto,
        leptonveto
        ])


nocut = Nminus1Cut(Nminus1Cut(monov, 'fatjet1tau21'), 'fatjet1PrunedML2L3')


categoryCuts = {
    'monoJet_inc' : monojet,
    'monoV' : monov,
    'vbf'   : vbf,
    'monoJet' : monojet + ' && !(' + monoveto + ')',
    'nocut' : nocut,
    'full' : ' && '.join([
            nocut,
            prunedmass,
            'fatjet1tau21 < 0.6'
            ]),
    'tight' : ' && '.join([
            nocut,
            prunedmass,
            'fatjet1tau21 < 0.45'
            ]),
    }

regionCuts = {
    'signal' : signal,
    'Zmm'    : Zmm,
    'Zee'    : Zee,
    'Wmn'    : Wmn,
    'Wen'    : Wen,
    'gjets'  : gjet
    }

regions    = regionCuts.keys()
categories = categoryCuts.keys()

defaultMCWeight = 'mcFactors'

# first one is the cut, second one is the SF

metTrigger =  metfilter # + ' && (triggerFired[10]==1 || triggerFired[11] == 1 || triggerFired[12] || triggerFired[13] == 1)'
eleTrigger =  metfilter # + ' && (triggerFired[0] || triggerFired[1] || triggerFired[2] || triggerFired[3] || triggerFired[4] || triggerFired[5] || triggerFired[26])'
gjetsTrigger =  metfilter # + ' && (triggerFired[18] || triggerFired[19] || triggerFired[17] || triggerFired[5] || triggerFired[15] || triggerFired[16] || triggerFired[26])'

additions    = { # key : [Data, MC]
    'signal' :  ['0', defaultMCWeight],
    'Zmm' :     [metTrigger, defaultMCWeight],
    'Wmn' :     [metTrigger, defaultMCWeight],
    'Zee' :     [eleTrigger, defaultMCWeight],
    'Wen' :     [eleTrigger, defaultMCWeight],
    'gjets':    [gjetsTrigger, defaultMCWeight],
    'default' : ['1', defaultMCWeight]
    }

if os.environ.get('UNBLIND') == '1':
    additions['signal'][0] = metTrigger

additionKeys = [key for key in additions.keys() if key != 'default']

def cut(category, region):

    cat_list = category.split('-')

    if len(cat_list) == 1:
        cat = categoryCuts[category]
    elif cat_list[1] == 'loose':
        cat = categoryCuts[cat_list[0]].replace(jetsubstructure, 'fatjet1tau21 > 0.45 && fatjet1tau21 < 0.6')
    else:
        cat = categoryCuts[cat_list[0]].replace(jetsubstructure, 'fatjet1tau21 < 0.6')

    return '((' + cat + ') && (' + regionCuts[region] + '))'

def dataMCCuts(region, isData):
    key = 'default'
    index = 0 if isData else 1

    if region in additions.keys():
        key = region

    return '(' + additions[key][index] + ')'

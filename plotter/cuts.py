from CrombieTools import Nminus1Cut as nm1
from selection import build_selection as bs

# Two dictionaries to define the cuts for separate categories and control regions

dilep = ' && '.join([
        'dilepMass < 121',
        'dilepMass > 61',
        '(lep1PdgId + lep2PdgId) == 0',
        'n_bjetsLoose == 0',
        'n_loosepho == 0',
        'n_tau == 0',
        'n_looselep == 2',
        'n_tightlep > 0',
        'n_mediumlep == 2',
        ])

regionCuts = {
    'dilep' : dilep,
    'diele' : dilep + ' && lep1PdgId * lep2PdgId == -121',
    'dimu' : dilep + ' && lep1PdgId * lep2PdgId == -169',
    'photon' : ' && '.join([
            'n_mediumpho == 1',
            'n_loosepho == 1',
            'n_tau == 0',
            'n_looselep == 0',
            'n_bjetsLoose == 0',
            ]),
    }

categoryCuts = {
    'nocut' : ' && '.join([
            'fatjet1Pt > 250',
            'met > 250',
            ]),
    'full' : ' && '.join([
            'fatjet1tau21 < 0.6',
            'fatjet1PrunedML2L3 > 65',
            'fatjet1PrunedML2L3 < 105',
            ]),
    'tight' : 'fatjet1tau21 < 0.4'
    }

categoryCuts['full'] += ' && ' + categoryCuts['nocut']
categoryCuts['tight'] += ' && ' + categoryCuts['full']

# Making selection of multiple entries

def joinCuts(toJoin=regionCuts.keys(), cuts=regionCuts):
    return ' && '.join([cuts[cut] for cut in toJoin])

# A weight applied to all MC

defaultMCWeight = 'ewk_a*akfactor*ewk_z*zkfactor*ewk_w*wkfactor'

# Additional weights applied to certain control regions

trigger0 = '(triggerFired[10]==1 || triggerFired[11] == 1 || triggerFired[12] || triggerFired[13] == 1)' 
trigger1 = '(triggerFired[0] || triggerFired[1] || triggerFired[2] || triggerFired[3] || triggerFired[4] || triggerFired[5] || triggerFired[26])'

additions    = { # key : [Data,MC]
    'signal'  : ['0','mcWeight*lepton_SF1*lepton_SF2*METTrigger*puWeight*topPtReweighting'],
    'Zmm'     : [trigger0, 'mcWeight*lepton_SF1*lepton_SF2*METTrigger*puWeight*topPtReweighting*tracking_SF1*tracking_SF2'],
    'Wmn'     : [trigger0, 'mcWeight*lepton_SF1*lepton_SF2*METTrigger*puWeight*topPtReweighting*tracking_SF1'],
    'Wen'     : [trigger1, 'mcWeight*puWeight*EleTrigger_w1*EleTrigger_w2*lepton_SF1*topPtReweighting*gsfTracking_SF1'],
    'Zee'     : [trigger1, 'mcWeight*puWeight*lepton_SF1*lepton_SF2*topPtReweighting*gsfTracking_SF1*gsfTracking_SF2'],
    'gjets'   : ['(triggerFired[18] || triggerFired[19] || triggerFired[17] || triggerFired[5] || triggerFired[15] || triggerFired[16])',
                 'mcWeight*PhoTrigger*topPtReweighting*photon_SF*puWeight'],
    'default' : ['1', defaultMCWeight]
    }

# Do not change the names of these functions or required parameters
# Otherwise you cannot use some convenience functions
# Multiple regions are concatenated with '+'
# Generally you can probably leave these alone

def cut(category, region):
    if region in regionCuts.keys():
        regionCut = regionCuts[region]
    else:
        regionCut = nm1(nm1(bs(region, 250), 'fatjet1PrunedM'), 'fatjet1tau21')

    return '((' + regionCut + ') && (' + categoryCuts[category] + '))'


def dataMCCuts(region, isData):
    key = 'default'
    if region in additions.keys():
        key = region

    index = 1
    if isData:
        index = 0

    if key == 'default' or index == 0:
        return 'metfilter==1 && filterbadChCandidate && filterbadPFMuon && (' + additions[key][index] + ')'
    else:
        return '((' + additions[key][index] + ')*(' + defaultMCWeight + '))'

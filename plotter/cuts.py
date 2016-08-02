# Two dictionaries to define the cuts for separate categories and control regions

categoryCuts = {
    'dilep' : ' && '.join([
            'dilepMass < 121',
            'dilepMass > 61',
            '(lep1PdgId + lep2PdgId) == 0',
            'n_bjetsLoose == 0',
            'n_loosepho == 0',
            'n_tau == 0',
            'recoil > 200',
            'n_looselep == 2',
            'n_tightlep > 0',
            'n_mediumlep == 2',
            ]),
    'photon' : ' && '.join([
            'n_mediumpho == 1',
            'n_loosepho == 1',
            'n_tau == 0',
            'n_looselep == 0',
            'n_bjetsLoose == 0',
            'recoil > 200',
            ])
    }

regionCuts = {
    'nocut' : 'fatjet1Pt > 0',
    'full' : ' && '.join([
            'fatjet1tau21 < 0.6',
            'fatjet1PrunedML2L3 > 65',
            'fatjet1PrunedML2L3 < 105',
            ])
    }

# These are just for the users to loop over

categories = categoryCuts.keys()
regions    = regionCuts.keys()

# Making selection of multiple entries

def joinCuts(toJoin=regionCuts.keys(), cuts=regionCuts):
    return ' && '.join([cuts[cut] for cut in toJoin])

# A weight applied to all MC

defaultMCWeight = 'mcFactors'

# Additional weights applied to certain control regions

additions    = { # key : [Data,MC]
    'signal'  : ['0','1'],
    'default' : ['1',defaultMCWeight]
    }

# Do not change the names of these functions or required parameters
# Otherwise you cannot use some convenience functions
# Multiple regions are concatenated with '+'
# Generally you can probably leave these alone

def cut(category, region):
    return '((' + categoryCuts[category] + ') && (' + joinCuts(toJoin=region.split('+')) + '))'

def dataMCCuts(region, isData):
    key = 'default'
    if region in additions.keys():
        key = region

    index = 1
    if isData:
        index = 0

    if key == 'default' or index == 0:
        return '(' + additions[key][index] + ')'
    else:
        return '((' + additions[key][index] + ')*(' + defaultMCWeight + '))'

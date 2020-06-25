import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
                                  'root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18MiniAOD/GluinoGluinoToNeutralinoNeutralinoTo2T2B2S_M-800_CTau-1mm_TuneCP2_13TeV_2018-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/E7677EE5-376B-6F4B-B504-BC820873679A.root'
    )
)

#from ProdTutorial.TrackAndPointsProducer.trackandpointsproducer_cfi import *
process.test = cms.EDProducer('testProd',
        packed_candidates_src = cms.InputTag('packedPFCandidates')
)

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('myOutputFile.root')
    #,outputCommands = cms.untracked.vstring('drop *',
    #  "keep *_generalTracks_*_*",
    #  "keep *_globalMuons_*_*",
    #  "keep *_MuonTrackPoints_*_*",
    #  "keep *_TrackTrackPoints_*_*")

)

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = '102X_upgrade2018_realistic_v15'

process.p = cms.Path(process.test)

process.e = cms.EndPath(process.out)

// -*- C++ -*-
//
// Package:    testCOde/testProd
// Class:      testProd
// 
/**\class testProd testProd.cc testCOde/testProd/plugins/testProd.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Ang Li
//         Created:  Thu, 25 Jun 2020 19:02:24 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/StreamID.h"


#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "LLPAnalyzer/Formats/interface/TrackRefMap.h"
//
// class declaration
//

class testProd : public edm::stream::EDProducer<> {
   public:
      explicit testProd(const edm::ParameterSet&);
      ~testProd();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginStream(edm::StreamID) override;
      virtual void produce(edm::Event&, const edm::EventSetup&) override;
      virtual void endStream() override;

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
      const edm::EDGetTokenT<pat::PackedCandidateCollection> packed_candidates_token;
};

//
// constants, enums and typedefs
//


//
// static data member definitions
//

//
// constructors and destructor
//
testProd::testProd(const edm::ParameterSet& iConfig):
  packed_candidates_token(consumes<pat::PackedCandidateCollection>(iConfig.getParameter<edm::InputTag>("packed_candidates_src")))
{
  produces<reco::TrackRefVector>();
   //register your products
/* Examples
   produces<ExampleData2>();

   //if do put with a label
   produces<ExampleData2>("label");
 
   //if you want to put into the Run
   produces<ExampleData2,InRun>();
*/
   //now do what ever other initialization is needed
  
}


testProd::~testProd()
{
 
   // do anything here that needs to be done at destruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
testProd::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  edm::Handle<pat::PackedCandidateCollection> packed_candidates;
  iEvent.getByToken(packed_candidates_token, packed_candidates);

  auto tracks_map = std::make_unique<reco::TrackRefVector>();

  reco::TrackRefProd h_output_tracks = iEvent.getRefBeforePut<reco::TrackCollection>();

  for (size_t i = 0; i<packed_candidates->size(); ++i){
    const pat::PackedCandidate& cand = (*packed_candidates)[i];
    //const reco::Track& tk = cand.pseudoTrack();
    //tracks_map->push_back(reco::TrackRef(h_output_tracks, tracks_map->size()));
    //tracks_map->insert(std::pair<reco::CandidatePtr, reco::TrackRef>(reco::CandidatePtr(packed_candidates, i), reco::TrackRef(h_output_tracks, tracks_map->size())));
  }

  iEvent.put(std::move(tracks_map));

/* This is an event example
   //Read 'ExampleData' from the Event
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);

   //Use the ExampleData to create an ExampleData2 which 
   // is put into the Event
   iEvent.put(std::make_unique<ExampleData2>(*pIn));
*/

/* this is an EventSetup example
   //Read SetupData from the SetupRecord in the EventSetup
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
*/
 
}

// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
testProd::beginStream(edm::StreamID)
{
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
testProd::endStream() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
testProd::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
testProd::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
testProd::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
testProd::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
testProd::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(testProd);

#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESTransientHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DetectorDescription/DDCMS/interface/DetectorDescriptionRcd.h"
#include "DetectorDescription/DDCMS/interface/DDDetector.h"
#include "DD4hep/Detector.h"
#include "DD4hep/DD4hepRootPersistency.h"

#include "TGeoManager.h"
#include "TFile.h"
#include "TSystem.h"

#include <iostream>
#include <string>

using namespace std;
using namespace cms;
using namespace edm;

class DDTestDumpGeometry : public one::EDAnalyzer<> {
public:
  explicit DDTestDumpGeometry(const ParameterSet&);

  void beginJob() override {}
  void analyze(Event const& iEvent, EventSetup const&) override;
  void endJob() override {}

private:  
  string m_label;
};

DDTestDumpGeometry::DDTestDumpGeometry(const ParameterSet& iConfig)
  : m_label(iConfig.getUntrackedParameter<string>("fromDataLabel", ""))
{}

void
DDTestDumpGeometry::analyze(const Event&, const EventSetup& iEventSetup)
{
  cout << "DDTestDumpGeometry::analyze: " << m_label << "\n";
  ESTransientHandle<DDDetector> det;
  iEventSetup.get<DetectorDescriptionRcd>().get(m_label, det);

  TGeoManager& geom = det->description->manager();

  TGeoIterator next(geom.GetTopVolume());
  TGeoNode *node;
  TString path;
  while(( node = next())) {
    next.GetPath( path );
    cout << path << ": "<< node->GetVolume()->GetName() << "\n";
  }
}

DEFINE_FWK_MODULE( DDTestDumpGeometry );

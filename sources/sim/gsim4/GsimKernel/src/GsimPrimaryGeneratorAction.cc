/**
 *  $Id: GsimPrimaryGeneratorAction.cc,v 1.6 2006/11/30 20:07:11 nanjo Exp $
 *  $Log: GsimPrimaryGeneratorAction.cc,v $
 *  Revision 1.6  2006/11/30 20:07:11  nanjo
 *  Data are re-structured.
 *
 *  Revision 1.5  2006/10/16 01:54:22  nanjo
 *  CLHEP functions are removed from GsimPersistencyManager.
 *
 *  Revision 1.4  2006/08/01 05:27:55  nanjo
 *  GsimSpectrum is added. Debug print is updated. With/without Digi is implemented.
 *
 *  Revision 1.3  2006/01/27 00:06:26  nanjo
 *  Seeds are saved in GsimPersistencyManager
 *
 *  Revision 1.2  2006/01/26 04:50:58  nanjo
 *  Factory pattern and template method on factory and messenger classes is intorduced .
 *
 */
#include "GsimKernel/GsimPrimaryGeneratorAction.h"
#include "GsimPersistency/GsimPersistencyManager.h"
#include "GsimKernel/GsimSpectrum.h"
#include "GsimPersistency/GsimMessage.h"
#include "GsimKernel/GsimRunAction.h"
#include "GsimData/GsimRandData.h"
#include "G4Event.hh"
#include "G4RunManager.hh"

#include "CLHEP/Random/Randomize.h"
#include "CLHEP/Random/engineIDulong.h"

#include <sstream>

GsimPrimaryGeneratorAction::
GsimPrimaryGeneratorAction()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_randData = new GsimRandData();
  m_spectrum=0;
  m_MTwistEngineID=CLHEP::crc32ul("MTwistEngine");
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif  
}

GsimPrimaryGeneratorAction::~GsimPrimaryGeneratorAction()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  delete m_randData;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif  
}


void GsimPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  GsimPersistencyManager* persistencyManager =
    GsimPersistencyManager::getPersistencyManager();
  int eventID=anEvent->GetEventID();
  if(eventID==0) {
    std::string className = m_randData->getClassName();
    persistencyManager->setEventSeedBranch("Rand.",className,&m_randData);
  }
  
  {
    //seed
    if(CLHEP::HepRandom::getTheEngine()->name()!="MTwistEngine") {
      GsimMessage::getInstance()
	->report("warning","GsimPersistencyManager RandomEngine is not MTwiterEngine.");
    }
    std::vector<unsigned long> vSeed = CLHEP::HepRandom::getTheEngine()->put();

    int runID =
      dynamic_cast<const GsimRunAction*>
      (G4RunManager::GetRunManager()->GetUserRunAction())
      ->getRunNumber();
    m_randData->run_number=runID;
    m_randData->event_number=static_cast<unsigned int>(eventID);
    m_randData->engineID=vSeed[0];
    if(m_randData->engineID==m_MTwistEngineID) {
      for(int i=0;i<624;i++) {
	m_randData->seed[i]=vSeed[i+1];
      }
      m_randData->count=vSeed[625];
    }
  }
  shoot(anEvent);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif  

}

void GsimPrimaryGeneratorAction::registerSpectrum(GsimSpectrum* spectrum)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_spectrum=spectrum;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

/**
 *  $Id: gsim4test.cc,v 1.28 2007/02/04 12:58:41 nanjo Exp $
 *  $Log: gsim4test.cc,v $
 *  Revision 1.28  2007/02/04 12:58:41  nanjo
 *  GsimStackingAction is added.
 *
 *  Revision 1.27  2006/12/07 08:52:41  nanjo
 *  Add a comment
 *
 *  Revision 1.26  2006/12/06 19:10:08  nanjo
 *  RunNumberBase.
 *
 *  Revision 1.25  2006/11/17 12:09:54  nanjo
 *  RunIDBase is added.
 *
 *  Revision 1.24  2006/10/26 15:31:38  nanjo
 *  GsimE14Spectrum is utilized.
 *
 *  Revision 1.23  2006/10/26 14:59:23  nanjo
 *  E14 detectors are added.
 *
 *  Revision 1.22  2006/10/19 03:34:13  nanjo
 *  GsimPersistencyManagerMessenger is replaced by GsimRunActionMessenger.
 *
 *  Revision 1.21  2006/09/29 08:22:26  nanjo
 *  Total number of event is automatically stored.
 *
 *  Revision 1.20  2006/08/24 17:39:42  nanjo
 *  Event processing status is printed in batch mode.
 *
 *  Revision 1.19  2006/08/02 02:34:30  nanjo
 *  GsimSpectrum is added.
 *
 *  Revision 1.18  2006/06/22 17:06:05  nanjo
 *  Update macros.
 *
 *  Revision 1.17  2006/06/08 18:02:07  nanjo
 *  Seed can be assigned from command line.
 *
 *  Revision 1.16  2006/06/02 05:07:27  nanjo
 *  GsimCone is supported.
 *
 *  Revision 1.15  2006/05/30 07:52:42  nanjo
 *  GsimGunManager is deleted.
 *
 *  Revision 1.14  2006/05/26 12:34:09  nanjo
 *  GsimHEPEvtInterface is defined.
 *
 *  Revision 1.13  2006/03/22 13:20:52  nanjo
 *  LHEP is set.
 *
 *  Revision 1.12  2006/03/15 09:29:52  nanjo
 *  Arguments are enabled.
 *
 *  Revision 1.11  2006/03/06 01:20:03  nanjo
 *  Interfacess for G4ParticleGun and G4GeneralParticleSource are added.
 *
 *  Revision 1.10  2006/03/05 18:00:57  nanjo
 *  CC04,CC05 are added.
 *
 *  Revision 1.9  2006/03/05 13:30:30  nanjo
 *  CC02 is added.
 *
 *  Revision 1.8  2006/03/04 10:52:06  nanjo
 *  FBAR, CBAR, and CSI are added.
 *
 *  Revision 1.7  2006/03/01 12:49:37  nanjo
 *  Test for cloning is added (test7.mac)
 *
 *  Revision 1.6  2006/02/17 04:38:11  nanjo
 *  Declaration of NistMateral is added in Macrofiles.
 *
 *  Revision 1.5  2006/02/02 21:55:11  nanjo
 *  E391 detector is started.
 *
 *  Revision 1.4  2006/01/31 03:04:20  nanjo
 *  PersistencyManagerMessenger is not a daughter of PersistencyManager now.
 *
 *  Revision 1.3  2006/01/27 00:09:21  nanjo
 *  small modification.
 *
 *  Revision 1.2  2006/01/26 08:13:09  nanjo
 *  Update for using tempalte factory etc.
 *
 */
#include "GsimPersistency/GsimPersistencyManager.h"
#include "GsimKernel/GsimRunActionMessenger.h"
#include "GsimKernel/GsimDetectorConstruction.h"
#include "GsimKernel/GsimPhysicsList.h"
#include "GsimKernel/GsimPhysicsListMessenger.h"
#include "GsimKernel/GsimPhysicsListFactory.h"




/////////////////////////
#include "FTFC.hh"
#include "FTFP.hh"
#include "FTFP_EMV.hh"
#include "LBE.hh"
#include "LHEP.hh"
#include "LHEP_BERT.hh"
#include "LHEP_BERT_HP.hh"
#include "LHEP_EMV.hh"
#include "LHEP_PRECO_HP.hh"
#include "QBBC.hh"
#include "QGSC.hh"
#include "QGSC_EFLOW.hh"
#include "QGSC_EMV.hh"
#include "QGSP.hh"
#include "QGSP_BERT.hh"
#include "QGSP_BERT_EMV.hh"
#include "QGSP_BERT_HP.hh"
#include "QGSP_BERT_NQE.hh"
#include "QGSP_BIC.hh"
#include "QGSP_BIC_HP.hh"
#include "QGSP_EMV.hh"
#include "QGSP_EMV_NQE.hh"
#include "QGSP_EMX.hh"
#include "QGSP_NQE.hh"
#include "QGSP_QEL.hh"
/////////////////////////

#include "G4Version.hh"
#if ( G4VERSION_NUMBER == 830 ) || ( G4VERSION_NUMBER == 831 )
#include "LHEP_BIC.hh"
#include "LHEP_BIC_HP.hh"
#include "LHEP_HP.hh"
#include "LHEP_LEAD.hh"
#include "LHEP_LEAD_HP.hh"
#include "LHEP_PRECO.hh"
#include "QGSC_LEAD.hh"
#include "QGSC_LEAD_HP.hh"
#include "QGSP_HP.hh"
#elif ( G4VERSION_NUMBER == 900 ) || ( G4VERSION_NUMBER == 901 )
#include "QGSP_BERT_TRV.hh"
#endif




#include "GsimKernel/GsimPrimaryGeneratorActionFactory.h"
#include "GsimKernel/GsimDetectorManager.h"
#include "GsimKernel/GsimRunAction.h"
#include "GsimKernel/GsimEventAction.h"
#include "GsimKernel/GsimStackingAction.h"
#include "GsimKernel/GsimTrackingAction.h"
#include "GsimKernel/GsimSteppingAction.h"
#include "GsimKernel/GsimDetectorFactory.h"
#include "GsimKernel/GsimSpectrum.h"
#include "GsimKernel/GsimSpectrumFactory.h"

#include "GsimKernel/GsimMaterialFactory.h"
#include "GsimMaterial/GsimOpticalMaterial.h"

#include "GsimKernel/GsimSurfaceFactory.h"

#include "GsimPhysicsList/GsimLowEnergyEMOp.h"

#include "GsimGun/GsimParticleGun.h"
#include "GsimGun/GsimGeneralParticleSource.h"
#include "GsimGun/GsimHEPEvtInterface.h"
#include "GsimDetector/GsimBox.h"
#include "GsimDetector/GsimTube.h"
#include "GsimDetector/GsimCone.h"
#include "GsimDetector/GsimPolyhedra2.h"
#include "GsimDetector/GsimPolycone2.h"
#include "GsimDetector/GsimBoxWithAHole.h"


#include "GsimE391Detector/GsimE391.h"
#include "GsimE391Detector/GsimE391BCV.h"
#include "GsimE391Detector/GsimE391CC07.h"
#include "GsimE391Detector/GsimE391CC06.h"
#include "GsimE391Detector/GsimE391BHCV.h"
#include "GsimE391Detector/GsimE391CC03.h"
#include "GsimE391Detector/GsimE391BA.h"
#include "GsimE391Detector/GsimE391CC00.h"
#include "GsimE391Detector/GsimE391CV.h"
#include "GsimE391Detector/GsimE391SAND.h"
#include "GsimE391Detector/GsimE391CBAR.h"
#include "GsimE391Detector/GsimE391FBAR.h"
#include "GsimE391Detector/GsimE391CSI.h"
#include "GsimE391Detector/GsimE391CC02.h"
#include "GsimE391Detector/GsimE391CC04.h"
#include "GsimE391Detector/GsimE391CC05.h"

#include "GsimE391Detector/GsimE391Beamline.h"


#include "GsimE391Spectrum/GsimE391Spectrum.h"
#include "GsimE391Spectrum/GsimE391HalonSpectrum.h"
#include "GsimE391Spectrum/GsimE391CorenSpectrum.h"
#include "GsimE14Spectrum/GsimE14Spectrum.h"
#include "GsimE14Spectrum/GsimE14HalonSpectrum.h"

#include "GsimE14Detector/GsimE14.h"
#include "GsimE14Detector/GsimE14Membrane.h"
#include "GsimE14Detector/GsimE14FBAR.h"
#include "GsimE14Detector/GsimE14CBAR.h"
#include "GsimE14Detector/GsimE14BCV.h"
#include "GsimE14Detector/GsimE14CV.h"
#include "GsimE14Detector/GsimE14CSI.h"
#include "GsimE14Detector/GsimE14CC00.h"
#include "GsimE14Detector/GsimE14CC01.h"
#include "GsimE14Detector/GsimE14CC02.h"
#include "GsimE14Detector/GsimE14CC03.h"
#include "GsimE14Detector/GsimE14CC04.h"
#include "GsimE14Detector/GsimE14CC05.h"
#include "GsimE14Detector/GsimE14CC06.h"
#include "GsimE14Detector/GsimE14BHCV.h"
#include "GsimE14Detector/GsimE14BHPV.h"

#include "GsimE14Detector/GsimE14Beamline.h"


#include "GsimUIbash/GsimUIbash.h"

#include "mylib/GsimVirt.h"

//Geant4
#include "G4RunManager.hh"
#include "G4UIdirectory.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4ios.hh"


#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#include <iostream>
#include <cstdlib>

int main(int argc, char** argv)
{


  // arguments
  G4String macroFileName="";
  char* rootFileName=0;
  int eventNumber=0;
  int rndSeed=0;
  int runNumberBase=0;

  if(argc == 1) {
    
  } else if(argc == 2) { 
    macroFileName = argv[1];
  } else if(argc == 3) {
    macroFileName = argv[1];
    rootFileName  = argv[2];
  } else if (argc == 4) {
    macroFileName = argv[1];
    rootFileName  = argv[2];
    eventNumber   = std::atoi(argv[3]);
  } else if(argc ==5) {
    macroFileName = argv[1];
    rootFileName  = argv[2];
    eventNumber   = std::atoi(argv[3]);
    rndSeed       = std::atoi(argv[4]);
  } else if(argc ==6) {
    macroFileName = argv[1];
    rootFileName  = argv[2];
    eventNumber   = std::atoi(argv[3]);
    rndSeed       = std::atoi(argv[4]);
    runNumberBase = std::atoi(argv[5]);
  } else {
    G4cout << "Wrong number of arguments : "
	   <<  argc
	   << G4endl;
    return 1;
  }

  
  
  // run manger
  G4RunManager* runManager = new G4RunManager();
  //runManager->SetVerboseLevel(10);
  
  GsimPersistencyManager* persistencyManager
     = new GsimPersistencyManager(rootFileName);
  
  GsimDetectorManager *dm = new GsimDetectorManager();
  
  // UserInitialization classes - mandatory
  runManager->SetUserInitialization(new GsimDetectorConstruction(dm));
  
  
  runManager->SetUserInitialization(new GsimPhysicsList);
  new GsimPhysicsListMessenger();


  //4.9.0
  new GsimPhysicsListFactory<FTFC>("FTFC");
  new GsimPhysicsListFactory<FTFP>("FTFP");
  new GsimPhysicsListFactory<FTFP_EMV>("FTFP_EMV");
  new GsimPhysicsListFactory<LBE>("LBE");
  new GsimPhysicsListFactory<LHEP>("LHEP");
  new GsimPhysicsListFactory<LHEP_BERT>("LHEP_BERT");
  new GsimPhysicsListFactory<LHEP_BERT_HP>("LHEP_BERT_HP");
  new GsimPhysicsListFactory<LHEP_EMV>("LHEP_EMV");
  new GsimPhysicsListFactory<LHEP_PRECO_HP>("LHEP_PRECO_HP");
  new GsimPhysicsListFactory<QBBC>("QBBC");
  new GsimPhysicsListFactory<QGSC>("QGSC");
  new GsimPhysicsListFactory<QGSC_EFLOW>("QGSC_EFLOW");
  new GsimPhysicsListFactory<QGSC_EMV>("QGSC_EMV");
  new GsimPhysicsListFactory<QGSP>("QGSP");
  new GsimPhysicsListFactory<QGSP_BERT>("QGSP_BERT");
  new GsimPhysicsListFactory<QGSP_BERT_EMV>("QGSP_BERT_EMV");
  new GsimPhysicsListFactory<QGSP_BERT_HP>("QGSP_BERT_HP");
  new GsimPhysicsListFactory<QGSP_BERT_NQE>("QGSP_BERT_NQE");
  new GsimPhysicsListFactory<QGSP_BIC>("QGSP_BIC");
  new GsimPhysicsListFactory<QGSP_BIC_HP>("QGSP_BIC_HP");
  new GsimPhysicsListFactory<QGSP_EMV>("QGSP_EMV");
  new GsimPhysicsListFactory<QGSP_EMV_NQE>("QGSP_EMV_NQE");
  new GsimPhysicsListFactory<QGSP_EMX>("QGSP_EMX");
  new GsimPhysicsListFactory<QGSP_NQE>("QGSP_NQE");
  new GsimPhysicsListFactory<QGSP_QEL>("QGSP_QEL");
  ////
  
#if ( G4VERSION_NUMBER == 830 ) || ( G4VERSION_NUMBER == 831 )
  new GsimPhysicsListFactory<LHEP_BIC>("LHEP_BIC");
  new GsimPhysicsListFactory<LHEP_BIC_HP>("LHEP_BIC_HP");
  new GsimPhysicsListFactory<LHEP_HP>("LHEP_HP");
  new GsimPhysicsListFactory<LHEP_LEAD>("LHEP_LEAD");
  new GsimPhysicsListFactory<LHEP_LEAD_HP>("LHEP_LEAD_HP");
  new GsimPhysicsListFactory<LHEP_PRECO>("LHEP_PRECO");
  new GsimPhysicsListFactory<QGSC_LEAD>("QGSC_LEAD");
  new GsimPhysicsListFactory<QGSC_LEAD_HP>("QGSC_LEAD_HP");
#elif ( G4VERSION_NUMBER == 900 ) || ( G4VERSION_NUMBER == 901 )
  new GsimPhysicsListFactory<QGSP_BERT_TRV>("QGSP_BERT_TRV");
#endif
  
  new GsimPhysicsListFactory<GsimLowEnergyEMOp>("GsimLowEnergyEMOp");
  

  new GsimPrimaryGeneratorActionFactory<GsimParticleGun>
    ("GsimParticleGun");
  new GsimPrimaryGeneratorActionFactory<GsimGeneralParticleSource>
    ("GsimGeneralParticleSource");
  new GsimPrimaryGeneratorActionFactory<GsimHEPEvtInterface>
    ("GsimHEPEvtInterface");
  
#ifdef G4VIS_USE
  // visualization manager
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
#endif

  GsimRunAction* runAction = new GsimRunAction(dm);
  new GsimRunActionMessenger(runAction);
  runAction->setSeed(rndSeed);
  runAction->setRunNumberBase(runNumberBase);
  
  runManager->SetUserAction(runAction);
  GsimEventAction* eventAction = new GsimEventAction(dm); 
  runManager->SetUserAction(eventAction);
  runManager->SetUserAction(new GsimStackingAction);
  runManager->SetUserAction(new GsimTrackingAction(dm));
  runManager->SetUserAction(new GsimSteppingAction(dm));

  new GsimMaterialFactory<GsimOpticalMaterial>("GsimOpticalMaterial");

  new GsimSurfaceFactory(dm);

  new GsimDetectorFactory<GsimDetector>(dm,"GsimDetector");
  new GsimDetectorFactory<GsimBox>(dm,"GsimBox");
  new GsimDetectorFactory<GsimTube>(dm,"GsimTube");
  new GsimDetectorFactory<GsimCone>(dm,"GsimCone");
  new GsimDetectorFactory<GsimPolyhedra2>(dm,"GsimPolyhedra2");
  new GsimDetectorFactory<GsimPolycone2>(dm,"GsimPolycone2");
  new GsimDetectorFactory<GsimBoxWithAHole>(dm,"GsimBoxWithAHole");

  new GsimDetectorFactory<GsimE391>(dm,"GsimE391");
  
  new GsimDetectorFactory<GsimE391BCV>(dm,"GsimE391BCV");
  new GsimDetectorFactory<GsimE391CC07>(dm,"GsimE391CC07");
  new GsimDetectorFactory<GsimE391CC06>(dm,"GsimE391CC06");
  new GsimDetectorFactory<GsimE391BHCV>(dm,"GsimE391BHCV");
  new GsimDetectorFactory<GsimE391CC03>(dm,"GsimE391CC03");
  new GsimDetectorFactory<GsimE391BA>(dm,"GsimE391BA");
  new GsimDetectorFactory<GsimE391CC00>(dm,"GsimE391CC00");
  new GsimDetectorFactory<GsimE391CV>(dm,"GsimE391CV");
  new GsimDetectorFactory<GsimE391SAND>(dm,"GsimE391SAND");
  new GsimDetectorFactory<GsimE391CBAR>(dm,"GsimE391CBAR");
  new GsimDetectorFactory<GsimE391FBAR>(dm,"GsimE391FBAR");
  new GsimDetectorFactory<GsimE391CSI>(dm,"GsimE391CSI");
  new GsimDetectorFactory<GsimE391CC02>(dm,"GsimE391CC02");
  new GsimDetectorFactory<GsimE391CC04>(dm,"GsimE391CC04");
  new GsimDetectorFactory<GsimE391CC05>(dm,"GsimE391CC05");

  new GsimDetectorFactory<GsimE391Beamline>(dm,"GsimE391Beamline");

  new GsimDetectorFactory<GsimE14>(dm,"GsimE14");
  
  new GsimDetectorFactory<GsimE14CSI>(dm,"GsimE14CSI");
  new GsimDetectorFactory<GsimE14CC00>(dm,"GsimE14CC00");
  new GsimDetectorFactory<GsimE14CC01>(dm,"GsimE14CC01");
  new GsimDetectorFactory<GsimE14CC02>(dm,"GsimE14CC02");
  new GsimDetectorFactory<GsimE14CC03>(dm,"GsimE14CC03");
  new GsimDetectorFactory<GsimE14CC04>(dm,"GsimE14CC04");
  new GsimDetectorFactory<GsimE14CC05>(dm,"GsimE14CC05");
  new GsimDetectorFactory<GsimE14CC06>(dm,"GsimE14CC06");
  new GsimDetectorFactory<GsimE14FBAR>(dm,"GsimE14FBAR");
  new GsimDetectorFactory<GsimE14CBAR>(dm,"GsimE14CBAR");
  new GsimDetectorFactory<GsimE14BCV>(dm,"GsimE14BCV");
  new GsimDetectorFactory<GsimE14BHCV>(dm,"GsimE14BHCV");
  new GsimDetectorFactory<GsimE14BHPV>(dm,"GsimE14BHPV");
  new GsimDetectorFactory<GsimE14CV>(dm,"GsimE14CV");
  new GsimDetectorFactory<GsimE14Membrane>(dm,"GsimE14Membrane");

  new GsimDetectorFactory<GsimE14Beamline>(dm,"GsimE14Beamline");

  new GsimSpectrumFactory<GsimSpectrum>("GsimSpectrum");
  new GsimSpectrumFactory<GsimE391Spectrum>("GsimE391Spectrum");
  new GsimSpectrumFactory<GsimE391HalonSpectrum>("GsimE391HalonSpectrum");
  new GsimSpectrumFactory<GsimE391CorenSpectrum>("GsimE391CorenSpectrum");
  new GsimSpectrumFactory<GsimE14Spectrum>("GsimE14Spectrum");
  new GsimSpectrumFactory<GsimE14HalonSpectrum>("GsimE14HalonSpectrum");


  new GsimDetectorFactory<GsimVirt>(dm,"GsimVirt");
  
  // initialize G4 kernel
  //runManager->Initialize();

  // get the pointer to the User Interface manager 
  G4UImanager* UI = G4UImanager::GetUIpointer();

  // session
  G4UIsession* session=0;
  if (argc==1) {
    // define UI session for interactive mode
    session = new G4UIterminal(new GsimUIbash("Gsim(%s)[%/] "));
  }

  if (session) {
    session->SessionStart();
    delete session;
  } else {
    // batch mode
    persistencyManager->readScript(macroFileName.data());
    
    G4String command = "/control/execute ";
    UI->ApplyCommand(command+macroFileName);
    if(eventNumber>0) {
      std::ostringstream ostr;
      ostr << "/run/beamOn ";
      ostr << eventNumber;
      UI->ApplyCommand(ostr.str());
      persistencyManager->readCommand(ostr.str().c_str());
    }
  }

  
  
  persistencyManager->close();
  delete persistencyManager;

  delete dm;
  // delete
  // (objects which visManager has are automatically deleted)
  
  
#ifdef G4VIS_USE
  delete visManager;
#endif

  //should be the last
  delete runManager;
  
  return 0;
}



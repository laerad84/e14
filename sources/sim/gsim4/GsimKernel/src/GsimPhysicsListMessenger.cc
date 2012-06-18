/**
 *  @file
 *  $Id: $
 *  $Log: $
 */
#include "GsimKernel/GsimPhysicsListMessenger.h"
#include "GsimParticle/GsimKLpi0nunu.h"
#include "GsimKernel/GsimUtil.h"
#include "GsimPersistency/GsimMessage.h"
#include "GsimParticle/GsimX.h"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UImanager.hh"
#include "G4RunManager.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"
#include "G4ProcessTable.hh"
#include "G4VProcess.hh"
#include "G4Version.hh"
#include "G4DecayTable.hh"
#include "G4PhaseSpaceDecayChannel.hh"
#include "G4VUserPhysicsList.hh"
#include "G4Transportation.hh"
#include "G4Decay.hh"
#include "G4VDecayChannel.hh"
         
#include <string>
#include <vector>
#include <cstdlib>

GsimPhysicsListMessenger::GsimPhysicsListMessenger()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  std::string dirName="/GsimPhysicsList/";
  m_physicsListDir = new G4UIdirectory(G4String(dirName.c_str()));
  m_physicsListDir->SetGuidance("Control GsimPhysicsList.");
  
  {
    std::string commandName=dirName;
    commandName+="setKLPi0NuNuDecayModel";
    m_cmdSetKLPi0NuNuDecayModel = new G4UIcmdWithAnInteger(G4String(commandName.c_str()),this);
    m_cmdSetKLPi0NuNuDecayModel->SetGuidance("Set KLPi0NuNu decay model.");
    m_cmdSetKLPi0NuNuDecayModel->SetGuidance("0: A model used in E391.");
    m_cmdSetKLPi0NuNuDecayModel->SetGuidance("1: Kmu3 dalitz density.");
    m_cmdSetKLPi0NuNuDecayModel->SetGuidance("2: Phase space.");
    m_cmdSetKLPi0NuNuDecayModel->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="setKLPi0NuNuLambdaPlus";
    m_cmdSetKLPi0NuNuLambdaPlus = new G4UIcmdWithADouble(G4String(commandName.c_str()),this);
    m_cmdSetKLPi0NuNuLambdaPlus->SetGuidance("Set KLPi0NuNu dalitz parameter, lambda+.");
    m_cmdSetKLPi0NuNuLambdaPlus->SetGuidance("Default : 0.0284");
    m_cmdSetKLPi0NuNuLambdaPlus->SetGuidance("        : PDG 2006 (2.84+-0.04)x10^-2");
    m_cmdSetKLPi0NuNuLambdaPlus->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="addXParticle";
    m_cmdAddXParticle = new G4UIcmdWithAString(G4String(commandName.c_str()),this);
    m_cmdAddXParticle->SetGuidance("Add X particle.");
    m_cmdAddXParticle->SetGuidance("  addXParticle mass lifetime width charge -1 -1");
    m_cmdAddXParticle->SetGuidance("    The last two are isStable isShortlived");
    m_cmdAddXParticle->SetGuidance("  214.3*MeV [3.06e-15*ns] [0] [0] [-1] [-1]");
    m_cmdAddXParticle->AvailableForStates(G4State_PreInit,G4State_Idle);
  }


  {
    std::string commandName=dirName;
    commandName+="addPhaseSpaceDecay";
    m_cmdAddPhaseSpaceDecay = new G4UIcmdWithAString(G4String(commandName.c_str()),this);
    m_cmdAddPhaseSpaceDecay->SetGuidance("Add Phasespace Decay (max 4-body decay) ");
    m_cmdAddPhaseSpaceDecay->SetGuidance("addPhaseSpaceDecay parent daughter1 daughter2 ..");
    m_cmdAddPhaseSpaceDecay->SetGuidance("This Br=1, othres are 0.");
    m_cmdAddPhaseSpaceDecay->SetGuidance("If you want to change Br, do as follows.");
    m_cmdAddPhaseSpaceDecay->SetGuidance("   /particle/select kaon0L");
    m_cmdAddPhaseSpaceDecay->SetGuidance("   /particle/property/decay/select 0");
    m_cmdAddPhaseSpaceDecay->SetGuidance("   /particle/property/decay/br 0");
  }


  {
    std::string commandName=dirName;
    commandName+="withUserLimits";
    m_cmdWithUserLimits = new G4UIcmdWithABool(G4String(commandName.c_str()),this);
    m_cmdWithUserLimits->SetGuidance("With/without GsimUserLimits for the  PhysicsList.");
    m_cmdWithUserLimits->SetGuidance("withUserLimits 1/0");
    m_cmdWithUserLimits->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="addCerenkov";
    m_cmdAddCerenkov = new G4UIcmdWithoutParameter(G4String(commandName.c_str()),this);
    m_cmdAddCerenkov->SetGuidance("Add Cerenkov process.");
    m_cmdAddCerenkov->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="setDefaultCut";
    m_cmdSetDefaultCut = new G4UIcmdWithAString(G4String(commandName.c_str()),this);
    m_cmdSetDefaultCut->SetGuidance("Set default cut.");
    m_cmdSetDefaultCut->SetGuidance("setDefaultCut 0.1*mm");
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


GsimPhysicsListMessenger::~GsimPhysicsListMessenger()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  delete m_cmdSetKLPi0NuNuDecayModel;
  delete m_cmdSetKLPi0NuNuLambdaPlus;
  delete m_cmdAddXParticle;
  delete m_cmdAddPhaseSpaceDecay;
  delete m_cmdAddCerenkov;
  delete m_cmdWithUserLimits;
  delete m_cmdSetDefaultCut;
  delete m_physicsListDir;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif

}

void GsimPhysicsListMessenger::SetNewValue(G4UIcommand* command,G4String aValue)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  aValue=G4UImanager::GetUIpointer()->SolveAlias(aValue.data());
  
  if(command == m_cmdSetKLPi0NuNuDecayModel) {
    GsimKLpi0nunu::Definition()
      ->setDecayModel(m_cmdSetKLPi0NuNuDecayModel->GetNewIntValue(aValue));
  } else if (command == m_cmdSetKLPi0NuNuLambdaPlus) {
    GsimKLpi0nunu::Definition()
      ->setLambdaPlus(m_cmdSetKLPi0NuNuLambdaPlus->GetNewDoubleValue(aValue));
  } else if(command==m_cmdAddXParticle) {
    GsimUtil* util = GsimUtil::getUtil();
    G4String tmpline = aValue;
    G4String tmpout;
    std::vector<double> vec;
    bool ok=true;
    while(ok) {
      ok=util->shift(tmpline,tmpout);
      if(ok) {
	vec.push_back(util->interpret(tmpout));
      }
    }
    double mass=214.3*MeV;
    double lifetime=197e-15/214.3/3e8*1e9*ns;
    double width=0.;
    double charge=0.;
    bool isStable=false;
    bool isShortlived=false;
    
    if(vec.size()>6) {
      //Warning
      GsimMessage::getInstance()
	->report("warning","Wrong number of arguments for addXParticle.");
    }
    
    if(vec.size()>=1)  mass=vec[0];
    if(vec.size()>=2)  lifetime=vec[1];
    if(vec.size()>=3)  width=vec[2];
    if(vec.size()>=4)  charge=vec[3];
    if(vec.size()>=5) { if(vec[4]>=0)  isStable=true; }
    if(vec.size()==6) { if(vec[5]>=0)  isShortlived=true; }
    
    GsimX::initialize(mass,lifetime,width,charge,isStable,isShortlived);
    G4RunManager* fRunManager = G4RunManager::GetRunManager();
    const G4VUserPhysicsList* pl = fRunManager->GetUserPhysicsList();
    G4ParticleDefinition* particle = GsimX::Definition();
    const_cast<G4VUserPhysicsList*>(pl)->AddProcessManager(particle);
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4VProcess* theTransportationProcess = new G4Transportation();
    pmanager ->AddProcess(theTransportationProcess);
    pmanager ->SetProcessOrderingToFirst(theTransportationProcess, idxAlongStep);
    pmanager ->SetProcessOrderingToFirst(theTransportationProcess, idxPostStep);
  } else if(command==m_cmdAddPhaseSpaceDecay) {
    GsimUtil* util = GsimUtil::getUtil();
    G4String tmpline = aValue;
    G4String tmpout;
    G4String pname[5];
    bool ok=true;
    int cnt=0;
    while(ok) {
      ok=util->shift(tmpline,tmpout);
      if(ok) {
	pname[cnt]=tmpout;
	cnt++;
	if(cnt>5) {
	  //Warning
	  GsimMessage::getInstance()
	    ->report("warning","Wrong number of arguments for addPhaseSpaceDecay.");
	  return;
	}
      }
    }

    G4PhaseSpaceDecayChannel* mode=0;
    if(cnt<3) {
      //Warning
      GsimMessage::getInstance()
	->report("warning","Wrong number of arguments for addPhaseSpaceDecay.");
      return;
    }
    G4ParticleTable* pt = G4ParticleTable::GetParticleTable();
    if(!pt) {
      //Warning
      GsimMessage::getInstance()
	->report("warning","No particle table for addPhaseSpaceDecay.");
      return;
    }
    G4ParticleDefinition* pd=pt->FindParticle(pname[0]);
    if(!pd) {
      //Warning
      GsimMessage::getInstance()
	->report("warning","No such parent particle for addPhaseSpaceDecay.");
      return;
    }
    if(cnt==3) {
      mode = new G4PhaseSpaceDecayChannel(pname[0],1.,2,pname[1],pname[2]);
    } else if(cnt==4) {
      mode = new G4PhaseSpaceDecayChannel(pname[0],1.,3,pname[1],pname[2],pname[3]);
    } else if(cnt==5) {
      mode = new G4PhaseSpaceDecayChannel(pname[0],1.,4,pname[1],pname[2],pname[3],pname[4]);
    }
    G4DecayTable* dt=pd->GetDecayTable();
    int num=dt->entries();
    for(int i=0;i<num;i++) {
      G4VDecayChannel* dc = dt->GetDecayChannel(i);
      dc->SetBR(0.);
    }
    if(dt==0) {
      dt = new G4DecayTable();
      pd->SetDecayTable(dt);
    }
    dt->Insert(mode);

    
    G4ProcessManager* pmanager = pd->GetProcessManager();
    if(!pmanager) {
      G4RunManager* fRunManager = G4RunManager::GetRunManager();
      const G4VUserPhysicsList* pl = fRunManager->GetUserPhysicsList();
      const_cast<G4VUserPhysicsList*>(pl)->AddProcessManager(pd);
      pmanager = pd->GetProcessManager();
    }
    G4ProcessVector* procV=pmanager->GetProcessList();
    bool isDecay = false;
    for(int i=0;i<procV->size();i++) {
      G4String procName=(*procV)[i]->GetProcessName();
      if(procName=="Decay") {
	isDecay = true;
	break;
      }
    }
    if(!isDecay) {
      G4ProcessTable* procT=G4ProcessTable::GetProcessTable();
      G4ProcessVector* procV=procT->FindProcesses("Decay");
      G4VProcess* fDecayProcess = 0;
      if(procV->size()==1) {
	fDecayProcess = (*procV)[0];
      } else {
	fDecayProcess = new G4Decay();
      }
      pmanager -> AddProcess(fDecayProcess);
      pmanager -> SetProcessOrdering(fDecayProcess, idxPostStep);
      pmanager -> SetProcessOrdering(fDecayProcess, idxAtRest);
    }
  } else if(command==m_cmdAddCerenkov) {
    GsimUtil* util = GsimUtil::getUtil();
    util->addCerenkov();
  } else if(command==m_cmdWithUserLimits) {
    GsimUtil* util = GsimUtil::getUtil();
    util->withUserLimits(m_cmdWithUserLimits->GetNewBoolValue(aValue));
  } else if(command == m_cmdSetDefaultCut) {
    GsimUtil* util = GsimUtil::getUtil();
    G4String tmpline = aValue;
    G4String tmpout;
    if(util->shift(tmpline,tmpout)) {
      double defaultCutValue=util->interpret(tmpout);
      G4RunManager* fRunManager = G4RunManager::GetRunManager();
      const G4VUserPhysicsList* pl = fRunManager->GetUserPhysicsList();
      const_cast<G4VUserPhysicsList*>(pl)->SetDefaultCutValue(defaultCutValue);
      const_cast<G4VUserPhysicsList*>(pl)->SetCutsWithDefault();
    } else {
      GsimMessage::getInstance()
	->report("warning","Wrong command format.");
    }
  } else {
    std::string msg = "Wrong command  at GsimPhysicsListMessenger::";
    msg+="SetNewValue(G4UIcommand* command,G4String newValue=";
    msg+=std::string(aValue.data()) ;
    msg+=")";
    GsimMessage::getInstance()
      ->report("warning",msg);
  } 
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  
}

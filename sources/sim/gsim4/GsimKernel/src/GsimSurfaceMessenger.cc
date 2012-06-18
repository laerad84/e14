#include "GsimKernel/GsimSurfaceMessenger.h"
#include "GsimKernel/GsimSurface.h"
#include "GsimKernel/GsimUtil.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UImanager.hh"

GsimSurfaceMessenger::GsimSurfaceMessenger(GsimSurface* surface)
  :m_surface(surface)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  std::string dirName="/GsimSurface/";
  dirName+=m_surface->getName();
  dirName+="/";
  m_surfaceDir = new G4UIdirectory(G4String(dirName.c_str()));
  G4String guid="Control GsimSurface : ";
  guid+= m_surface->getName();
  guid+= ".";
  m_surfaceDir->SetGuidance(guid);

  {
    std::string commandName=dirName;
    commandName+="setSurfaceProperty";
    m_cmdSetSurfaceProperty = new G4UIcmdWithAString(G4String(commandName.c_str()),this);
    m_cmdSetSurfaceProperty->SetGuidance("setSurfaceProperty type finish model param");
    m_cmdSetSurfaceProperty->SetGuidance("type  : dielectric_metal,dielectric_dielectric,firsov,x_ray");
    m_cmdSetSurfaceProperty->SetGuidance("finish: polished,polishedfrontpainted,polishedbackpainted,ground,groundfrontpainted,groundbackpainted");
    m_cmdSetSurfaceProperty->SetGuidance("model : glisur:original GEANT3,unified");
    m_cmdSetSurfaceProperty->SetGuidance("param : polish for glisur,alpha for unified");
    m_cmdSetSurfaceProperty->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="setRefractiveIndex";
    m_cmdSetRefractiveIndex = new G4UIcmdWithAString(G4String(commandName.c_str()),this);
    m_cmdSetRefractiveIndex->SetGuidance("setRefractiveIndex pw_0 re_0 pw_1 re_1 ....");
    m_cmdSetRefractiveIndex->SetGuidance(" pw_i : photon wavelength [nm]");
    m_cmdSetRefractiveIndex->SetGuidance(" re_i : refractive index");
    m_cmdSetRefractiveIndex->SetGuidance(" if no pw,re are supplied, the property is removed.");
    m_cmdSetRefractiveIndex->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="setReflectivity";
    m_cmdSetReflectivity = new G4UIcmdWithAString(G4String(commandName.c_str()),this);
    m_cmdSetReflectivity->SetGuidance("setReflectivity  pw_0 re_0 pw_1 re_1 ....");
    m_cmdSetReflectivity->SetGuidance(" pw_i : photon wavelength [nm]");
    m_cmdSetReflectivity->SetGuidance(" re_i : reflectivity");
    m_cmdSetReflectivity->SetGuidance(" if no pw,re are supplied, the property is removed.");
    m_cmdSetReflectivity->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="setEfficiency";
    m_cmdSetEfficiency = new G4UIcmdWithAString(G4String(commandName.c_str()),this);
    m_cmdSetEfficiency->SetGuidance("setEfficiency  pw_0 re_0 pw_1 re_1 ....");
    m_cmdSetEfficiency->SetGuidance(" pw_i : photon wavelength [nm]");
    m_cmdSetEfficiency->SetGuidance(" re_i : efficiency");
    m_cmdSetEfficiency->SetGuidance(" if no pw,re are supplied, the property is removed.");
    m_cmdSetEfficiency->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="setProperty";
    m_cmdSetProperty = new G4UIcmdWithAString(G4String(commandName.c_str()),this);
    m_cmdSetProperty->SetGuidance("setProperty type pw_0 re_0 pw_1 re_1 ....");
    m_cmdSetProperty->SetGuidance(" type : RINDEX,REFLECTIVITY,EFFICIENCY,SPECULARSPIKECONSTANT,SPECULARLOBECONSTANT,BACKSCATTERCONSTANT");
    m_cmdSetProperty->SetGuidance(" pw_i : photon wavelength [nm]");
    m_cmdSetProperty->SetGuidance(" re_i : efficiency");
    m_cmdSetProperty->SetGuidance(" if no pw,re are supplied, the property is removed.");
    m_cmdSetProperty->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="dump";
    m_cmdDump = new G4UIcmdWithoutParameter(G4String(commandName.c_str()),this);
    m_cmdDump->SetGuidance("dump");
    m_cmdDump->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


GsimSurfaceMessenger::~GsimSurfaceMessenger()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  delete m_cmdSetSurfaceProperty;
  delete m_cmdSetRefractiveIndex;
  delete m_cmdSetReflectivity;
  delete m_cmdSetEfficiency;
  delete m_cmdSetProperty;
  delete m_cmdDump;
  delete m_surfaceDir;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}



void GsimSurfaceMessenger::SetNewValue(G4UIcommand* command,G4String aValue)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  aValue=G4UImanager::GetUIpointer()->SolveAlias(aValue.data());

  if( command == m_cmdSetSurfaceProperty) {
    GsimUtil* util = GsimUtil::getUtil();
    G4String tmpline = aValue;
    G4String line = aValue;
    G4String tmpout,out1,out2,out3,out4;
    int nArg=0;
    bool ok=true;
    while(ok) {
      ok=util->shift(tmpline,tmpout);
      if(ok) nArg++;
    }
    if(nArg!=4) {
      std::string msg = "Wrong command format at GsimSurfaceMessenger::";
      msg+="SetNewValue(G4UIcommand* command,G4String newValue=";
      msg+=std::string(aValue.data()) ;
      msg+=")";
      GsimMessage::getInstance()
	->report("warning",msg);
      return;
    }
    util->shift(line,out1);
    util->shift(line,out2);
    util->shift(line,out3);
    util->shift(line,out4);
    double param=util->interpret(out4);

    G4SurfaceType type=dielectric_metal;
    if(out1=="dielectric_metal") {
      type=dielectric_metal;
    } else if(out1=="dielectric_dielectric") {
      type=dielectric_dielectric;
    } else if(out1=="firsov") {
      type=firsov;
    } else if(out1=="x_ray") {
      type=x_ray;
    }

    G4OpticalSurfaceFinish finish=polished;
    if(out2=="polished") {
      finish=polished;
    } else if(out2=="polishedfrontpainted") {
      finish=polishedfrontpainted;
    } else if(out2=="polishedbackpainted") {
      finish=polishedbackpainted;
    } else if(out2=="ground") {
      finish=ground;
    } else if(out2=="groundfrontpainted") {
      finish=groundfrontpainted;
    } else if(out2=="groundbackpainted") {
      finish=groundbackpainted;
    }

    G4OpticalSurfaceModel model=glisur;
    if(out3=="glisur") {
      model=glisur;
    } else if(out3=="unified") {
      model=unified;
    }
    m_surface->setSurfaceProperty(type,finish,model,param);
				  
    
  } else if(command == m_cmdSetRefractiveIndex || 
	    command == m_cmdSetReflectivity ||
	    command == m_cmdSetEfficiency ) {
	    
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
    if(vec.size()%2!=0) {
      std::string msg = "Wrong number of paramaeters at GsimSurfaceMessenger::";
      msg+="SetNewValue(G4UIcommand* command,G4String newValue=";
      msg+=std::string(aValue.data()) ;
      msg+=")";
      GsimMessage::getInstance()
	->report("warning",msg);
      return;
    }
    std::vector<double> pwV;
    std::vector<double> reV;
    for(size_t i=0;i<(vec.size()/2);i++) {
      pwV.push_back(vec[2*i]);
      reV.push_back(vec[2*i+1]);
    }
    
    if(command == m_cmdSetRefractiveIndex) {
      m_surface->setRefractiveIndex(pwV,reV);
    } else if(command == m_cmdSetReflectivity) {
      m_surface->setReflectiveity(pwV,reV);
    } else if(command == m_cmdSetEfficiency) {
      m_surface->setEfficiency(pwV,reV);
    }
  } else if(command == m_cmdSetProperty) {
    GsimUtil* util = GsimUtil::getUtil();
    G4String tmpline = aValue;
    G4String tmpout,out1;
    std::vector<double> vec;
    bool ok=true;
    ok=util->shift(tmpline,out1);
    if(!ok) {
      std::string msg = "Wrong number of paramaeters at GsimSurfaceMessenger::";
      msg+="SetNewValue(G4UIcommand* command,G4String newValue=";
      msg+=std::string(aValue.data()) ;
      msg+=")";
      GsimMessage::getInstance()
	->report("warning",msg);
      return;
    }
    while(ok) {
      ok=util->shift(tmpline,tmpout);
      if(ok) {
	vec.push_back(util->interpret(tmpout));
      }
    }
    if(vec.size()%2!=0) {
      std::string msg = "Wrong number of paramaeters at GsimSurfaceMessenger::";
      msg+="SetNewValue(G4UIcommand* command,G4String newValue=";
      msg+=std::string(aValue.data()) ;
      msg+=")";
      GsimMessage::getInstance()
	->report("warning",msg);
      return;
    }
    std::vector<double> pwV;
    std::vector<double> reV;
    for(size_t i=0;i<(vec.size()/2);i++) {
      pwV.push_back(vec[2*i]);
      reV.push_back(vec[2*i+1]);
    }
    m_surface->setProperty(out1.data(),pwV,reV);
  } else if(command == m_cmdDump) {
    m_surface->dump();
  } else {
    std::string msg = "Wrong command  at GsimSurfaceMessenger::";
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

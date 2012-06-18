/**
 *  @file
 *  $Id: GsimMaterialManagerMessenger.cc,v 1.4 2006/12/06 18:44:00 nanjo Exp $
 *  $Log: GsimMaterialManagerMessenger.cc,v $
 *  Revision 1.4  2006/12/06 18:44:00  nanjo
 *  Midas I/O is added and Root I/O is separated. etc.
 *
 */
#include "GsimKernel/GsimMaterialManagerMessenger.h"
#include "GsimKernel/GsimMaterialManager.h"
#include "GsimKernel/GsimUtil.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UImanager.hh"

#include <string>
#include <vector>
#include <cstdlib>

GsimMaterialManagerMessenger::GsimMaterialManagerMessenger(GsimMaterialManager* materialManager)
  :m_materialManager(materialManager)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  std::string dirName="/GsimMaterialManager/";
  m_materialManagerDir = new G4UIdirectory(G4String(dirName.c_str()));
  m_materialManagerDir->SetGuidance("Control GsimMaterialManager.");
  

  {
    std::string commandName=dirName;
    commandName+="useNistMaterial";
    m_cmdUseNistMaterial = new G4UIcmdWithAString(G4String(commandName.c_str()),this);
    m_cmdUseNistMaterial->SetGuidance("useNistMaterial G4_Al G4_Fe G4_GLASS_LEAD G4_Pb G4_SILICON_DIOXIDE G4_W ... ");
    m_cmdUseNistMaterial->SetGuidance("This is not needed from Geant4.8.2.");
    m_cmdUseNistMaterial->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="mixElementByWeight";
    m_cmdMixElementByWeight = new G4UIcmdWithAString(G4String(commandName.c_str()),this);
    m_cmdMixElementByWeight->SetGuidance("mixElementByWeight materialName    ");
    m_cmdMixElementByWeight->SetGuidance("     density pressure temperature  ");
    m_cmdMixElementByWeight->SetGuidance("     elementName1 weightFraction1  ");
    m_cmdMixElementByWeight->SetGuidance("     elementName2 weightFraction2  ");
    m_cmdMixElementByWeight->SetGuidance("     ....         .....");
    m_cmdMixElementByWeight->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="mixElementByNumber";
    m_cmdMixElementByNumber = new G4UIcmdWithAString(G4String(commandName.c_str()),this);
    m_cmdMixElementByNumber->SetGuidance("mixElementByNumber materialName    ");
    m_cmdMixElementByNumber->SetGuidance("     density pressure temperature  ");
    m_cmdMixElementByNumber->SetGuidance("     elementName1 number1  ");
    m_cmdMixElementByNumber->SetGuidance("     elementName2 number2  ");
    m_cmdMixElementByNumber->SetGuidance("     ....         .....");
    m_cmdMixElementByNumber->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="setProperty";
    m_cmdSetProperty = new G4UIcmdWithAString(G4String(commandName.c_str()),this);
    m_cmdSetProperty->SetGuidance("setProperty mat type pw_0 re_0 pw_1 re_1 ....");
    m_cmdSetProperty->SetGuidance(" mat  : Material name");
    m_cmdSetProperty->SetGuidance(" type : RINDEX,REFLECTIVITY,EFFICIENCY,SPECULARSPIKECONSTANT,SPECULARLOBECONSTANT,BACKSCATTERCONSTANT");
    m_cmdSetProperty->SetGuidance(" pw_i : photon wavelength [nm]");
    m_cmdSetProperty->SetGuidance(" re_i : efficiency");
    m_cmdSetProperty->SetGuidance(" if no pw,re are supplied, the property is removed.");
    m_cmdSetProperty->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="setConstProperty";
    m_cmdSetConstProperty = new G4UIcmdWithAString(G4String(commandName.c_str()),this);
    m_cmdSetConstProperty->SetGuidance("setConstProperty mat type value");
    m_cmdSetConstProperty->SetGuidance(" mat  : Material name");
    m_cmdSetConstProperty->SetGuidance(" type : RINDEX,REFLECTIVITY,EFFICIENCY,SPECULARSPIKECONSTANT,SPECULARLOBECONSTANT,BACKSCATTERCONSTANT");
    m_cmdSetConstProperty->SetGuidance(" value");
    m_cmdSetConstProperty->SetGuidance(" if value==-999, the property is removed.");
    m_cmdSetConstProperty->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="dumpProperty";
    m_cmdDumpProperty = new G4UIcmdWithAString(G4String(commandName.c_str()),this);
    m_cmdDumpProperty->SetGuidance("Dump property.");
    m_cmdDumpProperty->SetGuidance("dumpProperty matName");
  }

  {
    std::string commandName=dirName;
    commandName+="listMaterial";
    m_cmdListMaterial = new G4UIcmdWithoutParameter(G4String(commandName.c_str()),this);
    m_cmdListMaterial->SetGuidance("List Materials.");
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


GsimMaterialManagerMessenger::~GsimMaterialManagerMessenger()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  delete m_cmdUseNistMaterial;
  delete m_cmdMixElementByWeight;
  delete m_cmdMixElementByNumber;
  delete m_cmdSetProperty;
  delete m_cmdSetConstProperty;
  delete m_cmdDumpProperty;
  delete m_cmdListMaterial;
  delete m_materialManagerDir;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif

}

void GsimMaterialManagerMessenger::SetNewValue(G4UIcommand* command,G4String aValue)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  
  aValue=G4UImanager::GetUIpointer()->SolveAlias(aValue.data());
  
  if(command == m_cmdUseNistMaterial) {
    GsimUtil* util = GsimUtil::getUtil();
    G4String tmpline = aValue;
    G4String tmpout;
    bool ok=true;
    while(ok) {
      ok=util->shift(tmpline,tmpout);
      if(ok) {
	m_materialManager->useNistMaterial(std::string(tmpout.data()));
      }
    }
  } else if(command == m_cmdMixElementByWeight) {
    GsimUtil* util = GsimUtil::getUtil();
    G4String tmpline = aValue;
    G4String tmpout;
    bool ok=true;

    std::string matName="";
    double density=0.;
    double pressure=0.;
    double temperature=0.;
    ok=util->shift(tmpline,tmpout);
    if(ok) {
      matName=std::string(tmpout.data());
      ok=util->shift(tmpline,tmpout);
      if(ok) {
	density=util->interpret(tmpout);
	ok=util->shift(tmpline,tmpout);
	if(ok) {
	  pressure=util->interpret(tmpout);
	  ok=util->shift(tmpline,tmpout);
	  if(ok) {
	    temperature=util->interpret(tmpout);
	  }
	}
      }
    }
    if(!ok) {
      std::string msg = "Wrong command  at GsimMaterialManagerMessenger::";
      msg+="SetNewValue(G4UIcommand* command,G4String newValue=";
      msg+=std::string(aValue.data()) ;
      msg+=")";
      GsimMessage::getInstance()
	->report("warning",msg);
      return;
    }

    std::vector<std::string> elementVec;
    std::vector<double>      weightVec;
    while(ok) {
      ok=util->shift(tmpline,tmpout);
      if(ok) {
	std::string elem=std::string(tmpout.data());
	ok=util->shift(tmpline,tmpout);
	if(ok) {
	  double weight=util->interpret(tmpout);
	  elementVec.push_back(elem);
	  weightVec.push_back(weight);
	} else {
	  std::string msg = "Wrong command  at GsimMaterialManagerMessenger::";
	  msg+="SetNewValue(G4UIcommand* command,G4String newValue=";
	  msg+=std::string(aValue.data()) ;
	  msg+=")";
	  GsimMessage::getInstance()
	    ->report("warning",msg);
	  return;
	}
      }
    }
    m_materialManager->mixElement(matName,
				  density,pressure,temperature,
				  elementVec,weightVec
				  );
  } else if(command == m_cmdMixElementByNumber) {
    GsimUtil* util = GsimUtil::getUtil();
    G4String tmpline = aValue;
    G4String tmpout;
    bool ok=true;

    std::string matName="";
    double density=0.;
    double pressure=0.;
    double temperature=0.;
    ok=util->shift(tmpline,tmpout);
    if(ok) {
      matName=std::string(tmpout.data());
      ok=util->shift(tmpline,tmpout);
      if(ok) {
	density=util->interpret(tmpout);
	ok=util->shift(tmpline,tmpout);
	if(ok) {
	  pressure=util->interpret(tmpout);
	  ok=util->shift(tmpline,tmpout);
	  if(ok) {
	    temperature=util->interpret(tmpout);
	  }
	}
      }
    }
    if(!ok) {
      std::string msg = "Wrong command  at GsimMaterialManagerMessenger::";
      msg+="SetNewValue(G4UIcommand* command,G4String newValue=";
      msg+=std::string(aValue.data()) ;
      msg+=")";
      GsimMessage::getInstance()
	->report("warning",msg);
      return;
    }

    std::vector<std::string> elementVec;
    std::vector<int>         numberVec;
    while(ok) {
      ok=util->shift(tmpline,tmpout);
      if(ok) {
	std::string elem=std::string(tmpout.data());
	ok=util->shift(tmpline,tmpout);
	if(ok) {
	  int num=std::atoi(tmpout.data());
	  elementVec.push_back(elem);
	  numberVec.push_back(num);
	} else {
	  std::string msg = "Wrong command  at GsimMaterialManagerMessenger::";
	  msg+="SetNewValue(G4UIcommand* command,G4String newValue=";
	  msg+=std::string(aValue.data()) ;
	  msg+=")";
	  GsimMessage::getInstance()
	    ->report("warning",msg);
	  return;
	}
      }
    }
    m_materialManager->mixElement(matName,
				  density,pressure,temperature,
				  elementVec,numberVec
				  );
  } else if(command == m_cmdSetProperty) {
    GsimUtil* util = GsimUtil::getUtil();
    G4String tmpline = aValue;
    G4String tmpout,out1,out2;
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
    ok=util->shift(tmpline,out2);
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
    m_materialManager->setProperty(out1.data(),out2.data(),pwV,reV);
  } else if(command == m_cmdSetConstProperty) {
    GsimUtil* util = GsimUtil::getUtil();
    G4String tmpline = aValue;
    G4String tmpout,out1,out2;
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
    ok=util->shift(tmpline,out2);
    if(!ok) {
      std::string msg = "Wrong number of paramaeters at GsimSurfaceMessenger::";
      msg+="SetNewValue(G4UIcommand* command,G4String newValue=";
      msg+=std::string(aValue.data()) ;
      msg+=")";
      GsimMessage::getInstance()
	->report("warning",msg);
      return;
    }
    ok=util->shift(tmpline,tmpout);
    if(!ok) {
      std::string msg = "Wrong number of paramaeters at GsimSurfaceMessenger::";
      msg+="SetNewValue(G4UIcommand* command,G4String newValue=";
      msg+=std::string(aValue.data()) ;
      msg+=")";
      GsimMessage::getInstance()
	->report("warning",msg);
      return;
    }
    double val=util->interpret(tmpout);
    m_materialManager->setConstProperty(out1.data(),out2.data(),val);
  } else if(command==m_cmdDumpProperty) {
    m_materialManager->dumpProperty(std::string(aValue.data()));
  } else if(command==m_cmdListMaterial) {
    m_materialManager->listMaterial();
  } else {
    std::string msg = "Wrong command  at GsimMaterialManagerMessenger::";
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

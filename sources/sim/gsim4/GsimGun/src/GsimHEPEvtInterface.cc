/**
 *  @file
 *  @brief  GsimHEPEvtInterface
 *  $Id: 
 *  $Log: 
 */
#include "GsimData/GsimDetectorEventData.h"
#include "GsimData/GsimDetectorHitData.h"

#include "GsimGun/GsimHEPEvtInterface.h"
#include "GsimGun/GsimHEPEvtInterfaceMessenger.h"
#include "GsimPersistency/GsimPersistencyManager.h"
#include "GsimPersistency/GsimMessage.h"
#include "G4Event.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4EventManager.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4Geantino.hh"
#include "G4ChargedGeantino.hh"
#include "G4OpticalPhoton.hh"
#include "globals.hh"


#include "TTree.h"
#include "TBranch.h"
#include "TLeaf.h"
#include "TClonesArray.h"

#include <fstream>
#include <sstream>
#include <list>
#include <string>

GsimHEPEvtInterface::GsimHEPEvtInterface()
  : GsimPrimaryGeneratorAction()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_processMode=0;
  m_fileFormat=0;
  m_fileName="";
  m_vertexPosition=G4ThreeVector();
  m_vertexTime=0;
  m_inputRoot=0;
  m_eventCounter=0;

  m_detectorName="";
  m_runNo=0;
  m_KLtype="";
  m_eventData = new GsimDetectorEventData();

  m_zeroPIDParticle = G4Geantino::Definition();
  
  m_hepEvtInterfaceMessenger
    = new GsimHEPEvtInterfaceMessenger(this);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

GsimHEPEvtInterface::~GsimHEPEvtInterface()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(m_inputFile.is_open())
    m_inputFile.close();
  m_inputFile.clear();

  for(size_t iii=0;iii<m_HPlist.size();iii++)
    { delete m_HPlist[iii]; }
  m_HPlist.clear();
  m_PVlist.clear();

  delete m_eventData;
  delete m_hepEvtInterfaceMessenger;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

bool GsimHEPEvtInterface::setInputFileName(std::string fileName)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(m_inputFile.is_open()) {
    m_inputFile.close();
    m_inputFile.clear();
  }
  if(m_inputRoot) { 
    m_inputRoot->Close();
    m_inputRoot=0;
  }
  
  m_processMode=0;
  m_fileFormat=0;
  m_fileName="";
  m_vertexPosition=G4ThreeVector();
  m_vertexTime=0;
  m_inputRoot=0;
  m_eventCounter=0;
  m_detectorName="";
  m_runNo=0;
  m_KLtype="";
  
  bool isExist=false;
  std::ifstream fi;
  fi.open(fileName.c_str());
  if (fi) {
    m_fileName=fileName;
    isExist=true;
  }
  fi.close();
  fi.clear();
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return isExist;
}


bool GsimHEPEvtInterface::setInputEventDataFileName(std::string fileName,
						    std::string detectorName,
						    int runNo,
						    std::string KLtype)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  bool isExist=setInputFileName(fileName);
  
  if(detectorName=="") {
    isExist=false;
  } else {
    m_detectorName=detectorName;
    m_runNo=runNo;
    m_KLtype=KLtype;
  }
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return isExist;
}

void GsimHEPEvtInterface::shoot(G4Event* anEvent)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(m_processMode==0) {
    if(m_fileName=="") {
      GsimMessage::getInstance()
	->report("warning","Input file is not assigned.");
      abort();
      return;
    }

    int slen=m_fileName.size();
    std::string suffix(m_fileName,slen-4,slen);
    if(suffix=="root") {
      m_inputRoot = new TFile(m_fileName.c_str(),"READ");
      m_processMode=2;
      if(m_detectorName!="") m_processMode=3;
    } else {
      m_inputFile.open(m_fileName.c_str());
      m_processMode=1;
    }
  }

  switch (m_processMode)
    {
    case 1://ascii text
      if (!readOneAsciiEvent()) {
	abort();
	return;
      }
      break;
    case 2://root file
      if (!readOneRootEvent()) {
	abort();
	return;
      }
      break;
    case 3://root DetectorHitData
      if(!readOneDetectorHitEvent()) {
	abort();
	return;
      }
      break;
    default:
      return;
      break;
    }
  
  processEvent(anEvent);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}



void GsimHEPEvtInterface::processEvent(G4Event* anEvent)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_eventCounter++;
  
  // check if there is at least one particle
  if( m_HPlist.size() == 0 ) return; 
  
  // make connection between daughter particles decayed from 
  // the same mother
  for( size_t i=0; i<m_HPlist.size(); i++ )
    {
      if( m_HPlist[i]->GetJDAHEP1() > 0 ) //  it has daughters
	{
	  int jda1 = m_HPlist[i]->GetJDAHEP1()-1; // FORTRAN index starts from 1
	  int jda2 = m_HPlist[i]->GetJDAHEP2()-1; // but C++ starts from 0.
	  G4PrimaryParticle* mother = m_HPlist[i]->GetTheParticle();
	  for( int j=jda1; j<=jda2; j++ )
	    {
	      G4PrimaryParticle* daughter = m_HPlist[j]->GetTheParticle();
	      if(m_HPlist[j]->GetISTHEP()>0)
		{
		  mother->SetDaughter( daughter );
		  m_HPlist[j]->Done();
		}
	    }
	}
    }

  if(m_fileFormat==1) {
    // create G4PrimaryVertex object
    G4PrimaryVertex* vertex
      = new G4PrimaryVertex(m_vertexPosition,m_vertexTime);
    
    // put initial particles to the vertex
    for( size_t ii=0; ii<m_HPlist.size(); ii++ ) {
      if( m_HPlist[ii]->GetISTHEP() > 0 ) // ISTHEP of daughters had been 
	// set to negative
	{
	  G4PrimaryParticle* initialParticle = m_HPlist[ii]->GetTheParticle();
	  vertex->SetPrimary( initialParticle );
	}
    }
    anEvent->AddPrimaryVertex( vertex );
  } else if(m_fileFormat==2) {
    std::vector<G4HEPEvtParticle*>::iterator itHP=m_HPlist.begin();
    std::vector<G4PrimaryVertex*>::iterator  itPV=m_PVlist.begin();
    for(;itHP!=m_HPlist.end();itHP++,itPV++) {
      if( (*itHP)->GetISTHEP() > 0 ) // ISTHEP of daughters had been
	{
	  G4PrimaryParticle* initialParticle = (*itHP)->GetTheParticle();
	  (*itPV)->SetPrimary( initialParticle );
	  anEvent->AddPrimaryVertex( (*itPV) );
	}
    }
  } else {
    //error
  }
  // clear G4HEPEvtParticles
  //HPlist.clearAndDestroy();
  for(size_t iii=0;iii<m_HPlist.size();iii++)
    { delete m_HPlist[iii]; }
  m_HPlist.clear();
  m_PVlist.clear();
  
  // Put the vertex to G4Event object
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  
}

bool GsimHEPEvtInterface::readOneAsciiEvent()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  int NHEP=0;  // number of entries
  std::string line;
  if ( ! getline(m_inputFile,line) ) {
    GsimMessage::getInstance()
      ->report("info","GsimHEPEvtInterface:End-Of-File.");
    return false;
  }
  
  head(line);
  tail(line);
  std::istringstream stri(line);
  if( ! (stri >> NHEP) ) {
    GsimMessage::getInstance()
      ->report("warning","GsimHEPEvtInterface:format error.");
    return false;
  }
  
  for( int IHEP=0; IHEP<NHEP; IHEP++ ) {
    if(!readOneAsciiLine()) {
      //format error...
      GsimMessage::getInstance()
	->report("warning","GsimHEPEvtInterface:File format error.");
      for(size_t iii=0;iii<m_HPlist.size();iii++)
	{ delete m_HPlist[iii]; }
      m_HPlist.clear();
      m_PVlist.clear();
      return false;
    }
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return true;
}

bool GsimHEPEvtInterface::readOneAsciiLine()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  G4HEPEvtParticle*  aHEPParticle=0;
  G4PrimaryVertex*   aVertex=0;

  std::string line;
  if ( ! getline(m_inputFile,line) ) {
    //line number error
    GsimMessage::getInstance()
      ->report("warning","Input file line number errror.");
    return false;
  }
  head(line);
  tail(line);

  int ISTHEP;   // status code
  int IDHEP;    // PDG code
  int JDAHEP1;  // first daughter
  int JDAHEP2;  // last daughter
  double PHEP1; // px in GeV
  double PHEP2; // py in GeV
  double PHEP3; // pz in GeV
  double PHEP5; // mass in GeV
  double VHEP1=0; // x [mm]
  double VHEP2=0; // y [mm]
  double VHEP3=0; // z [mm]
  double VHEP4=0; // t [ns]

  std::istringstream stri(line);
  if(m_fileFormat==0) {
    if(stri >> ISTHEP >> IDHEP >> JDAHEP1 >> JDAHEP2
       >> PHEP1 >> PHEP2 >> PHEP3 >> PHEP5) {
      if(stri >> VHEP1 >> VHEP2 >> VHEP3 >> VHEP4) {
	m_fileFormat=2;
      } else {
	m_fileFormat=1;
      }
    }  else {
      //format error
      return false;
    }
  } else if(m_fileFormat==1) {
    if(! (stri >> ISTHEP >> IDHEP >> JDAHEP1 >> JDAHEP2
       >> PHEP1 >> PHEP2 >> PHEP3 >> PHEP5)) {
      //format eroor
      return false;
    }
  } else if(m_fileFormat==2) {
    if(! (stri >> ISTHEP >> IDHEP >> JDAHEP1 >> JDAHEP2
	  >> PHEP1 >> PHEP2 >> PHEP3 >> PHEP5
	  >> VHEP1 >> VHEP2 >> VHEP3 >> VHEP4)) {
      //format eroor
      return false;
    }
  } else {
    //mode error
    return false;
  }

  G4PrimaryParticle* particle=0;
  if(IDHEP==0) {
    particle = new G4PrimaryParticle( m_zeroPIDParticle, PHEP1*GeV, PHEP2*GeV, PHEP3*GeV );
  } else {
    particle = new G4PrimaryParticle( IDHEP, PHEP1*GeV, PHEP2*GeV, PHEP3*GeV );
  }
  particle->SetMass( PHEP5*GeV );
  
  // create G4HEPEvtParticle object
  aHEPParticle
    = new G4HEPEvtParticle( particle, ISTHEP, JDAHEP1, JDAHEP2 );

  if(ISTHEP>0) {
    if(m_fileFormat==2) {
      aVertex = new G4PrimaryVertex(G4ThreeVector(VHEP1*mm,VHEP2*mm,VHEP3*mm),
				    VHEP4*mm/c_light);
    }
  }
  m_HPlist.push_back(aHEPParticle );
  m_PVlist.push_back(aVertex);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return true;
}

void GsimHEPEvtInterface::setZeroPIDParticle(std::string pname)
{
  if(pname=="geantino") {
    m_zeroPIDParticle=G4Geantino::Definition();
  } else if(pname=="chargedgeantino") {
    m_zeroPIDParticle=G4ChargedGeantino::Definition();
  } else if(pname=="opticalphoton") {
    m_zeroPIDParticle=G4OpticalPhoton::Definition();
  } else {
    m_zeroPIDParticle=G4Geantino::Definition();
  }
}

void GsimHEPEvtInterface::convertToRootFile(std::string rootFileName)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(m_processMode==0) {
    if(m_fileName=="") {
      GsimMessage::getInstance()
	->report("warning","Input file is not assigned.");
      return;
    }

    int slen=m_fileName.size();
    std::string suffix(m_fileName,slen-4,slen);
    if(suffix=="root") {
      m_processMode=2;
    } else {
      m_inputFile.open(m_fileName.c_str());
      m_processMode=1;
    }
  }

  if(m_processMode!=1) {
    if(m_inputFile.is_open())
      m_inputFile.close();
    m_inputFile.clear();
    m_processMode=0;
    m_fileFormat=0;
    return;
  }

  // open root
  TFile tf(rootFileName.c_str(),"RECREATE");
  TTree tr("HEPEvt","HEPEvt");

  const int nmax=40000;
  int NHEP;
  int ISTHEP[nmax];   // status code
  int IDHEP[nmax];    // PDG code
  int JDAHEP1[nmax];  // first daughter
  int JDAHEP2[nmax];  // last daughter
  double PHEP1[nmax]; // px in GeV
  double PHEP2[nmax]; // py in GeV
  double PHEP3[nmax]; // pz in GeV
  double PHEP5[nmax]; // mass in GeV
  double VHEP1[nmax]; // x [mm]
  double VHEP2[nmax]; // y [mm]
  double VHEP3[nmax]; // z [mm]
  double VHEP4[nmax]; // t [mm/c~3.33ns]
  
  tr.Branch("NHEP",&NHEP,"NHEP/I");
  tr.Branch("ISTHEP",ISTHEP,"ISTHEP[NHEP]/I");
  tr.Branch("IDHEP",IDHEP,"IDHEP[NHEP]/I");
  tr.Branch("JDAHEP1",JDAHEP1,"JDAHEP1[NHEP]/I");
  tr.Branch("JDAHEP2",JDAHEP2,"JDAHEP2[NHEP]/I");
  tr.Branch("PHEP1",PHEP1,"PHEP1[NHEP]/D");
  tr.Branch("PHEP2",PHEP2,"PHEP2[NHEP]/D");
  tr.Branch("PHEP3",PHEP3,"PHEP3[NHEP]/D");
  tr.Branch("PHEP5",PHEP5,"PHEP5[NHEP]/D");
  
  
  bool isFirst=true;
  while (readOneAsciiEvent()) {
    if(isFirst) {
      if(m_fileFormat==2) {
	tr.Branch("VHEP1",VHEP1,"VHEP1[NHEP]/D");
	tr.Branch("VHEP2",VHEP2,"VHEP2[NHEP]/D");
	tr.Branch("VHEP3",VHEP3,"VHEP3[NHEP]/D");
	tr.Branch("VHEP4",VHEP4,"VHEP4[NHEP]/D");
      }
      isFirst=false;
    }
    //fill
    NHEP=m_HPlist.size();
    if(NHEP>nmax) NHEP=nmax;
    for(int k=0;k<NHEP;k++) {
      ISTHEP[k]=m_HPlist[k]->GetISTHEP();
      JDAHEP1[k]=m_HPlist[k]->GetJDAHEP1();
      JDAHEP2[k]=m_HPlist[k]->GetJDAHEP2();
      G4PrimaryParticle* particle = m_HPlist[k]->GetTheParticle();
      IDHEP[k]=particle->GetPDGcode();
      PHEP5[k]=particle->GetMass()/GeV;
      PHEP1[k]=particle->GetPx()/GeV;
      PHEP2[k]=particle->GetPy()/GeV;
      PHEP3[k]=particle->GetPz()/GeV;

      if(m_fileFormat==2) {
	VHEP1[k]=m_PVlist[k]->GetX0()/mm;
	VHEP2[k]=m_PVlist[k]->GetY0()/mm;
	VHEP3[k]=m_PVlist[k]->GetZ0()/mm;
	VHEP4[k]=m_PVlist[k]->GetT0()*c_light/mm;
      }
    }
    tr.Fill();
  }
  // EOF or bad file format
  tr.Write();
  tf.Close();
  
  if(m_inputFile.is_open())
    m_inputFile.close();
  m_inputFile.clear();
  m_processMode=0;
  m_fileFormat=0;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

bool GsimHEPEvtInterface::readOneRootEvent()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(!m_inputRoot) return false;
  TTree* tr = (TTree*)m_inputRoot->Get("HEPEvt");
  if(!tr) return false;

  TLeaf* lf[13];

  lf[0] = tr->GetLeaf("NHEP");
  lf[1] = tr->GetLeaf("ISTHEP");
  lf[2] = tr->GetLeaf("IDHEP");
  lf[3] = tr->GetLeaf("JDAHEP1");
  lf[4] = tr->GetLeaf("JDAHEP2");
  lf[5] = tr->GetLeaf("PHEP1");
  lf[6] = tr->GetLeaf("PHEP2");
  lf[7] = tr->GetLeaf("PHEP3");
  lf[8] = tr->GetLeaf("PHEP5");

  lf[9] =  tr->GetLeaf("VHEP1");
  lf[10] =  tr->GetLeaf("VHEP2");
  lf[11] =  tr->GetLeaf("VHEP3");
  lf[12] =  tr->GetLeaf("VHEP4");

  for(int k=0;k<9;k++) {
    if(!lf[k]) return false;
  }
  m_fileFormat=1;
  
  if(lf[9]) m_fileFormat=2;
  if(m_fileFormat==2) {
    for(int k=9;k<13;k++) {
      if(!lf[k]) return false;
    }
  }

  Long64_t ientry = tr->LoadTree(m_eventCounter);
  if(ientry<0) return false;
  tr->GetEntry(m_eventCounter);

  int NHEP=int(lf[0]->GetValue());

  for( Long64_t IHEP=0; IHEP<NHEP; IHEP++ ) {
    readOneRootLine(IHEP);
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return true;
}



bool GsimHEPEvtInterface::readOneRootLine(Long64_t iLine)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  G4HEPEvtParticle*  aHEPParticle=0;
  G4PrimaryVertex*   aVertex=0;
  
  TTree* tr = (TTree*)m_inputRoot->Get("HEPEvt");
  
  TLeaf* lf[13];

  lf[0] = tr->GetLeaf("NHEP");
  lf[1] = tr->GetLeaf("ISTHEP");
  lf[2] = tr->GetLeaf("IDHEP");
  lf[3] = tr->GetLeaf("JDAHEP1");
  lf[4] = tr->GetLeaf("JDAHEP2");
  lf[5] = tr->GetLeaf("PHEP1");
  lf[6] = tr->GetLeaf("PHEP2");
  lf[7] = tr->GetLeaf("PHEP3");
  lf[8] = tr->GetLeaf("PHEP5");

  lf[9] =  tr->GetLeaf("VHEP1");
  lf[10] =  tr->GetLeaf("VHEP2");
  lf[11] =  tr->GetLeaf("VHEP3");
  lf[12] =  tr->GetLeaf("VHEP4");


  int ISTHEP=int(lf[1]->GetValue(iLine));
  int IDHEP=int(lf[2]->GetValue(iLine));
  int JDAHEP1=int(lf[3]->GetValue(iLine));
  int JDAHEP2=int(lf[4]->GetValue(iLine));
  double PHEP1=lf[5]->GetValue(iLine);
  double PHEP2=lf[6]->GetValue(iLine);
  double PHEP3=lf[7]->GetValue(iLine);
  double PHEP5=lf[8]->GetValue(iLine);
  double VHEP1=0;
  double VHEP2=0;
  double VHEP3=0;
  double VHEP4=0;
  if(m_fileFormat==2) {
    VHEP1=lf[9]->GetValue(iLine);
    VHEP2=lf[10]->GetValue(iLine);
    VHEP3=lf[11]->GetValue(iLine);
    VHEP4=lf[12]->GetValue(iLine);
  }

  G4PrimaryParticle* particle=0;
  if(IDHEP==0) {
    particle = new G4PrimaryParticle( m_zeroPIDParticle, PHEP1*GeV, PHEP2*GeV, PHEP3*GeV );
  } else {
    particle = new G4PrimaryParticle( IDHEP, PHEP1*GeV, PHEP2*GeV, PHEP3*GeV );
  }
  particle->SetMass( PHEP5*GeV );
  
  // create G4HEPEvtParticle object
  aHEPParticle
    = new G4HEPEvtParticle( particle, ISTHEP, JDAHEP1, JDAHEP2 );

  if(ISTHEP>0) {
    if(m_fileFormat==2) {
      aVertex = new G4PrimaryVertex(G4ThreeVector(VHEP1*mm,VHEP2*mm,VHEP3*mm),
				    VHEP4*mm/c_light);
    }
  }
  m_HPlist.push_back(aHEPParticle );
  m_PVlist.push_back(aVertex);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return true;  
}

bool GsimHEPEvtInterface::readOneDetectorHitEvent()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(!m_inputRoot) return false;
  if(m_detectorName=="") return false;

  char treeName[100];
  std::sprintf(treeName,"eventTree%02d",m_runNo);
  TTree* tr = (TTree*)m_inputRoot->Get(treeName);
  if(!tr) return false;

  //hereherehere........
  //root I/O with class
  
  std::list<std::string> brNameList;
  if(m_detectorName=="all") {
    TObjArray* objArray = tr->GetListOfBranches();
    int n=objArray->GetEntries();
    for(int i=0;i<n;i++) {
      TBranch* br=(TBranch*)( (*objArray)[i] );
      std::string cln=std::string( br->GetClassName() );
      if(cln=="GsimDetectorHitData") {
	brNameList.push_back( std::string(br->GetName()) );
      }
    }
  } else {
    char branchName[1000];
    std::sprintf(branchName,"%s.",m_detectorName.c_str());
    TBranch* br = tr->GetBranch(branchName);
    if(br) {
      brNameList.push_back( std::string(br->GetName()) );
    }
  }


  if(brNameList.size()==0) return false;
  m_fileFormat=2;
  for(std::list<std::string>::iterator it=brNameList.begin();
      it!=brNameList.end();it++) {
    tr->SetBranchAddress((*it).c_str(),&m_eventData);
    //Long64_t nevent = tr->GetEntries();
    {
      Long64_t ientry = tr->LoadTree(m_eventCounter);
      if (ientry < 0) return false;
      tr->GetEntry(m_eventCounter);
      
      int nHit=m_eventData->nHit;
      
      for(int k=0;k<nHit;k++) {
	readOneDetectorHitLine(k);
      }
    }
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return true;
}



bool GsimHEPEvtInterface::readOneDetectorHitLine(Long64_t iLine)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  G4HEPEvtParticle*  aHEPParticle=0;
  G4PrimaryVertex*   aVertex=0;
  
  TClonesArray* ar = m_eventData->hits;
  GsimDetectorHitData* hitData
    = (GsimDetectorHitData*)ar->UncheckedAt(iLine);
  
  int ISTHEP=1;
  int IDHEP=hitData->pid;
  int JDAHEP1=0;
  int JDAHEP2=0;
  double PHEP1=(hitData->p).x();
  double PHEP2=(hitData->p).y();
  double PHEP3=(hitData->p).z();
  double p=(hitData->p).Mag();
  double ke=hitData->ek;
  double PHEP5=0;
  if(ke!=0)
    PHEP5=(p*p-ke*ke)/2./ke;
  else {
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle(IDHEP);
    PHEP5=particle->GetPDGMass();
  }

  double VHEP1=(hitData->r).x();
  double VHEP2=(hitData->r).y();
  double VHEP3=(hitData->r).z();
  double VHEP4=hitData->time;

  G4PrimaryParticle* particle =0;
  if(IDHEP==0) {
    particle = new G4PrimaryParticle( m_zeroPIDParticle, PHEP1*MeV, PHEP2*MeV, PHEP3*MeV );
  } else {
    particle = new G4PrimaryParticle( IDHEP, PHEP1*MeV, PHEP2*MeV, PHEP3*MeV );
  }
  particle->SetMass( PHEP5*MeV );
  
  // create G4HEPEvtParticle object
  aHEPParticle
    = new G4HEPEvtParticle( particle, ISTHEP, JDAHEP1, JDAHEP2 );

  aVertex = new G4PrimaryVertex(G4ThreeVector(VHEP1*mm,VHEP2*mm,VHEP3*mm),
  				VHEP4*ns);
  
  m_HPlist.push_back(aHEPParticle );
  m_PVlist.push_back(aVertex);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return true;  
}


void GsimHEPEvtInterface::gotoEventNumber(int eventNumber)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_eventCounter=eventNumber;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimHEPEvtInterface::abort()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(m_inputFile.is_open()) {
    m_inputFile.close();
    m_inputFile.clear();
  }
  if(m_inputRoot) { 
    m_inputRoot->Close();
    m_inputRoot=0;
  }
  m_eventCounter=0;
  m_processMode=0;
  m_fileFormat=0;

  m_detectorName="";
  m_runNo=0;
  m_KLtype="";
  
  G4RunManager* fRunManager = G4RunManager::GetRunManager();
  fRunManager->AbortEvent();
  fRunManager->AbortRun();
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimHEPEvtInterface::tail(std::string& lin) {
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(lin.size()>0) {
    while(std::string(lin,lin.size()-1,lin.size()) == " ") {
      lin.replace(lin.size()-1,1,"");
    }
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimHEPEvtInterface::head(std::string& lin) {
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(lin.size()>0) {
    while(std::string(lin,0,1) == " ") {
      lin.replace(0,1,"");
    }
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


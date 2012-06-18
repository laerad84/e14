/**
 *  @file
 *  @brief  GsimSpectrums
 *  $Id: GsimSpectrum.cc,v 1.2 2006/12/06 18:44:00 nanjo Exp $
 *  $Log: GsimSpectrum.cc,v $
 *  Revision 1.2  2006/12/06 18:44:00  nanjo
 *  Midas I/O is added and Root I/O is separated. etc.
 *
 */
#include "GsimKernel/GsimSpectrum.h"
#include "GsimKernel/GsimSpectrumMessenger.h"
#include "GsimPersistency/GsimMessage.h"
#include "TF1.h"
#include "G4Event.hh"
#include "G4PrimaryVertex.hh"
#include "G4PrimaryParticle.hh"


GsimSpectrum::GsimSpectrum(std::string name)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_name=name;
  
  messenger = new GsimSpectrumMessenger(this);
  
  m_keyWords.push_back("VX");        //0
  m_keyWords.push_back("VY");        //1
  m_keyWords.push_back("VZ");        //2
  m_keyWords.push_back("VR");        //3
  m_keyWords.push_back("VTheta");    //4
  m_keyWords.push_back("VCosTheta"); //5
  m_keyWords.push_back("VPhi");      //6
  
  m_keyWords.push_back("PAbs");      //7
  m_keyWords.push_back("Energy");    //8 
  m_keyWords.push_back("PTheta");    //9
  m_keyWords.push_back("PCosTheta"); //10 
  m_keyWords.push_back("PPhi");     //11

  m_keyWords.push_back("Special");   //12 for children

  m_modifyVertex=false;
  m_modifyMomentum=false;

  m_parameter=1.;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

GsimSpectrum::~GsimSpectrum()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  for(std::map<int,TF1*>::iterator it=m_spectrumContainer.begin();
      it!=m_spectrumContainer.end();it++) {
    delete (*it).second;
  }
  m_spectrumContainer.clear();
  m_modifyVertex=false;
  m_modifyMomentum=false;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimSpectrum::addSpectrum(std::string formula,double xmin,double xmax)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  int nKey=0;
  int iKey=-1;
  int count=0;
  for(std::vector<std::string>::iterator it=m_keyWords.begin();
      it!=m_keyWords.end();it++,count++) {
    if(formula.find( (*it) ) != std::string::npos) {
      iKey=count;
      nKey++;
    }
  }

  if(nKey!=1) {
    //error
    return;
  }

  if(iKey<7) {
    m_modifyVertex=true;
  } else {
    m_modifyMomentum=true;
  }
  if(iKey==12) {
    TF1* func=0;
    m_spectrumContainer.insert(std::make_pair(iKey,func));
    return;
  }

  std::string key = m_keyWords[iKey];
  size_t pos=formula.find(key);
  while(pos!=std::string::npos) {
    formula.replace(pos,key.size(),"x");
    pos=formula.find(key);
  }

  
  
  int n=m_spectrumContainer.size();
  char name[100];
  std::sprintf(name,"spectrum%d",n);
  
  TF1* func = new TF1(name,formula.c_str(),xmin,xmax);

  m_spectrumContainer.insert(std::make_pair(iKey,func));
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimSpectrum::clear()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  for(std::map<int,TF1*>::iterator it=m_spectrumContainer.begin();
      it!=m_spectrumContainer.end();it++) {
    delete (*it).second;
  }
  m_spectrumContainer.clear();
  m_modifyVertex=false;
  m_modifyMomentum=false;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimSpectrum::generateSpectrum(const G4Event* anEvent)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  if(m_modifyVertex==false &&
     m_modifyMomentum==false) return;
  
  int nPV= anEvent->GetNumberOfPrimaryVertex();

  for(int i=0;i<nPV;i++) {
    G4PrimaryVertex* pv = anEvent->GetPrimaryVertex(i);

    if(m_modifyVertex) {

      G4ThreeVector vPos = pv->GetPosition();
      for(std::map<int,TF1*>::iterator it=m_spectrumContainer.begin();
	  it!=m_spectrumContainer.end();it++) {
	TF1* func = (*it).second;
	double val=func->GetRandom();
	switch ( (*it).first ) {
	case 0://VX
	  val*=mm;
	  vPos.setX(val);
	  pv->SetPosition(vPos.x(),vPos.y(),vPos.z());
	  break;//VY
	case 1:
	  val*=mm;
	  vPos.setY(val);
	  pv->SetPosition(vPos.x(),vPos.y(),vPos.z());
	  break;
	case 2://VZ
	  val*=mm;
	  vPos.setZ(val);
	  pv->SetPosition(vPos.x(),vPos.y(),vPos.z());
	  break;
	case 3://VR
	  val*=mm;
	  vPos.setMag(val);
	  pv->SetPosition(vPos.x(),vPos.y(),vPos.z());
	  break;
	case 4://VTheta
	  vPos.setTheta(val);
	  pv->SetPosition(vPos.x(),vPos.y(),vPos.z());
	  break;
	case 5://VCsoTheta
	  vPos.setTheta(std::acos(val));
	  pv->SetPosition(vPos.x(),vPos.y(),vPos.z());
	  break;
	case 6://VPhi
	  vPos.setPhi(val);
	  pv->SetPosition(vPos.x(),vPos.y(),vPos.z());
	  break;
	default:
	  break;
	}
      }
    }
    if(m_modifyMomentum) {
      
      int nParticle=pv->GetNumberOfParticle();
      
      for(int j=0;j<nParticle;j++) {
	G4PrimaryParticle*    particle    = pv->GetPrimary(j);
	G4ThreeVector vMome = particle->GetMomentum();
	
	for(std::map<int,TF1*>::iterator it=m_spectrumContainer.begin();
	    it!=m_spectrumContainer.end();it++) {
	  TF1* func = (*it).second;
	  double val=0;
	  if((*it).first!=12) val=func->GetRandom();
	  switch ( (*it).first ) {
	  case 7://PAbs
	    val*=MeV;
	    vMome.setMag(val);
	    particle->SetMomentum(vMome.x(),vMome.y(),vMome.z());
	    break;
	  case 8://Energy
	    {
	      val*=MeV;
	      double mass = particle->GetMass();
	      //double mome=(val+mass)*(val+mass)-mass*mass;
	      double mome=val*val+2.*val*mass;
	      if(mome>0) mome=std::sqrt(mome);
	      else mome=0.;
	      vMome.setMag(mome);
	      particle->SetMomentum(vMome.x(),vMome.y(),vMome.z());
	    }
	    break;
	  case 9://PTheta
	    vMome.setTheta(val);
	    particle->SetMomentum(vMome.x(),vMome.y(),vMome.z());
	    break;
	  case 10://PCosTheta
	    vMome.setTheta(std::acos(val));
	    particle->SetMomentum(vMome.x(),vMome.y(),vMome.z());
	    break;
	  case 11://PPhi
	    vMome.setPhi(val);
	    particle->SetMomentum(vMome.x(),vMome.y(),vMome.z());
	    break;
	  case 12://Special
	    generateSpecial(anEvent);
	    break;
	  default:
	    break;
	  }
	}
      }
    }
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void  GsimSpectrum::generateSpecial(const G4Event* )
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

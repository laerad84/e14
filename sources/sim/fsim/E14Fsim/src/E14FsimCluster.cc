#include "E14Fsim/E14FsimCluster.h"
#include "E14Fsim/E14FsimMcGamma.h"
#include "E14Fsim/E14FsimFunction.h"

#include "TMath.h"
#include "TRandom.h"


int E14FsimCluster::s_smearMode=3;

E14FsimCluster::E14FsimCluster()
  :  m_nMcGamma( 0 ),
     m_mcGammaXYDistance( 999 ),
     m_mcFusionProb( 0. ),
     m_clusterID( -999 ),
     m_pos( TVector3(-999,-999,-999) ),
     m_mome( TVector3(-999,-999,-999) ),
     m_energy( -999 ),
     m_time( -999 ),
     m_sigmaE( -999 ),
     m_sigmaX( -999 ),
     m_sigmaY( -999 )
{
  for(int k=0;k<10;k++) {
    m_mcGammaID[k]=-999;
    m_mcGammaE[k]=-999;
    m_mcParentID[k]=-999;
  }
}

E14FsimCluster::~E14FsimCluster()
{
  
}


void E14FsimCluster::addMcGamma(E14FsimMcGamma* mcGamma)
{
  
  if(m_nMcGamma>5) {
    std::cerr << "nMcGamma exceeds 5" << std::endl;
    return;
  }
  m_mcGammaID[m_nMcGamma]=mcGamma->m_gammaID;
  m_mcGammaE[m_nMcGamma]=mcGamma->m_energy;
  m_mcParentID[m_nMcGamma]=mcGamma->m_parentID;
  m_mcGammaT[m_nMcGamma]=mcGamma->m_time;
  m_mcGammaPos[m_nMcGamma]=mcGamma->m_pos;
  m_mcGammaMome[m_nMcGamma]=mcGamma->m_mome;
  m_nMcGamma+=1;

  if(m_nMcGamma==2) {
    TVector3 dv=m_mcGammaPos[1]-m_mcGammaPos[0];
    m_mcGammaXYDistance=dv.Perp();
    m_mcFusionProb = E14FsimFunction::getFunction()->fusionProb(m_mcGammaXYDistance);
  }
}


void E14FsimCluster::smear()
{
  m_energy=0;
  m_mome=TVector3(0,0,0);
  m_time=0;
  m_pos=TVector3(0,0,0);
  m_angleXZ=0;
  m_angleYZ=0;
  for(int k=0;k<m_nMcGamma;k++) {
    m_energy+=m_mcGammaE[k];
    m_mome+=m_mcGammaMome[k];
    m_time+=m_mcGammaT[k];
    m_pos+=m_mcGammaE[k]*m_mcGammaPos[k];
    m_angleXZ+=m_mcGammaE[k]*
      TMath::ATan2(m_mcGammaMome[k].x(),m_mcGammaMome[k].z());
    m_angleYZ+=m_mcGammaE[k]*
      TMath::ATan2(m_mcGammaMome[k].y(),m_mcGammaMome[k].z());
  }
  m_time/=m_nMcGamma;
  m_pos*=1./m_energy;
  m_angleXZ/=m_energy;
  m_angleYZ/=m_energy;

  double tote = m_energy/1000;   //MeV to GeV

  if(s_smearMode==3 || s_smearMode==1) {
    m_sigmaE = E14FsimFunction::getFunction()->csiEnergyRes(tote); //GeV
  } else {
    m_sigmaE = 0;
  }
  m_sigmaE*=1000;//MeV

  if(s_smearMode==3 || s_smearMode==2) {
    m_sigmaX = E14FsimFunction::getFunction()->csiPosRes(tote); //mm
    m_sigmaY = E14FsimFunction::getFunction()->csiPosRes(tote); //mm
  } else {
    m_sigmaX = 0;
    m_sigmaY = 0;
  }
  
  m_energy = gRandom->Gaus(m_energy,m_sigmaE);
  m_pos=TVector3(
		 gRandom->Gaus(m_pos.x(),m_sigmaX),
		 gRandom->Gaus(m_pos.y(),m_sigmaY),
		 m_pos.z()
		 );

  double sigmaA = 0;
  if(s_smearMode!=0) {
    sigmaA = E14FsimFunction::getFunction()->csiAngRes(tote); //rad
  }
  m_angleXZ=gRandom->Gaus(m_angleXZ,sigmaA);
  m_angleYZ=gRandom->Gaus(m_angleYZ,sigmaA);
}


void E14FsimCluster::setSmearMode(int imode)
{
  s_smearMode=imode;
}

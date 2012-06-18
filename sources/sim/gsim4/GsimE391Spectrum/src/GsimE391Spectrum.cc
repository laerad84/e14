/**
 *  $Id: GsimE391Spectrum.cc,v 1.3 2006/12/06 19:16:44 nanjo Exp $
 *  $Log: GsimE391Spectrum.cc,v $
 *  Revision 1.3  2006/12/06 19:16:44  nanjo
 *  CVS variables.
 *
 */

#include "GsimE391Spectrum/GsimE391Spectrum.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4Event.hh"
#include "G4PrimaryVertex.hh"
#include "G4PrimaryParticle.hh"


#include "CLHEP/Random/Randomize.h"



#include <string>
#include <vector>
#include <cmath>



GsimE391Spectrum::GsimE391Spectrum(std::string name)
  : GsimSpectrum(name)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_TargetZ=-1180;//[cm];
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


GsimE391Spectrum::~GsimE391Spectrum()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}




// random
CLHEP::Hep3Vector GsimE391Spectrum::randomVector3( int mode,
					    double x1min, double x1max,
					    double x2min, double x2max,
					    double x3min, double x3max )
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  // welcome
  //std::cout << "randomVector3" << std::endl;
  
  // mode = 0 : X-Y-Z, uniform density
  // mode = 1 : R-Phi-Z, uniform density
  // mode = 2 : R-Theta-Phi
  // mode = 3 : R-CosTh-Phi
  
  double  rr[3];
  //  GRNDM( rr,3 );
  for (int i=0;i<3;i++){
    rr[i]=CLHEP::RandFlat::shoot();
    //random
  }
  if ( mode == 0 ){
    return( CLHEP::Hep3Vector( x1min + rr[0]*(x1max - x1min),
                        x2min + rr[1]*(x2max - x2min),
                        x3min + rr[2]*(x3max - x3min)  ) );
  }
  else if ( mode == 1 ){ // r-phi-z, uniform in r-phi plane
    double ru = sqrt( rr[0] );
    double r = x1min + ru*(x1max - x1min);
    double p = x2min + rr[1]*(x2max - x2min);
    double z = x3min + rr[2]*(x3max - x3min);
    return( CLHEP::Hep3Vector( r*cos(p),r*sin(p),z ) );
  }
  else if ( mode == 2 ){ // r-theta-phi
    double r = x1min + rr[0]*(x1max - x1min);
    double t = x2min + rr[1]*(x2max - x2min);
    double p = x3min + rr[2]*(x3max - x3min);
    return( CLHEP::Hep3Vector( r*sin(t)*cos(p),r*sin(t)*sin(p),r*cos(t) ) );
  }
  else if ( mode == 3 ){ // r-cosTheta-phi
    double r = x1min + rr[0]*(x1max - x1min);
    double tmin = 1 - cos(x2min);
    double tmax = 1 - cos(x2max);
    double t = acos( 1 - ( tmin + rr[1]*(tmax - tmin) ) );
    double p = x3min + rr[2]*(x3max - x3min);
    return( CLHEP::Hep3Vector( r*sin(t)*cos(p),r*sin(t)*sin(p),r*cos(t) ) );
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return( CLHEP::Hep3Vector( 0,0,0 ) );
  //
}



// Momentum distribution at the exit of collimator6
// Observed in the Run-1 
double
GsimE391Spectrum::PklDist_Exp( double p )
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  // Exp2004 1-day data
  // fitting function by H.Watanabe,
  // fitting parameter from K.Sakashita Wed Oct 20 15:19:24 JST 2004
  double  norm        =  1.0;
  double  mean        =  1.655;
  double  sigma       =  1.196;
  double  asym_offset = -0.3597;
  double  asym_slope  =  0.3303e-01;

  double  sig = sigma * (1.0 - (asym_offset + p * asym_slope)*(p - mean) );
  double  f   = norm * exp( -0.5*((p-mean)*(p-mean))/(sig*sig) );
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return( f ); // yield
}


// Density distribution on the E391a beamline at collimator6
double
GsimE391Spectrum::Density_Col6( double r )
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  // Data from S.Inoue.
  // parameters from M.Yamaga, Fri Sep 28 13:19:17 JST 2001
  // Function : Fermi dist. + 1st order polynomial with p0=0.
  double  x0    =  1.9095;
  double  slope =  0.18337;
  double  p0    =  0;
  double  p1    = -0.10679e-01;

  double  f = 1.0 / (1 + exp((r-x0)/slope)) + (p0 + p1*r);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return( f ); // yield
}


////////////////////////////////
// Generate Klong
void
GsimE391Spectrum::GsimGenKlongCol6( double z,CLHEP::Hep3Vector& p, CLHEP::Hep3Vector& vtx )
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  // normalization factor at position z(detector coordinate)
  double  ctau = 1551; // [cm] 
  double  mkl  = 0.497672; // KL mass
  double  m_ct = mkl / ctau;
  double  lbeamline = 987.5; //[cm]
  double  col6_z0 = m_TargetZ + lbeamline;

  double  bz = z - col6_z0; // bz0 = exit point of collimator6
  if ( bz < 0 )
    bz = 0;

  // vertex distribution
  // Data from S.Inoue
  // Parameter from M.Yamaga, Fri Sep 28 15:22:34 JST 2001

  // R of vertex at z0
  double  rmax = 5.24/2;
  double  rr,prob,yield;
  //static int  ct=0;
  do{
    //rr    = sqrt( randomDouble( 0,rmax*rmax ) );
    rr    = sqrt( CLHEP::RandFlat::shoot( 0.,rmax*rmax ) );
    yield = Density_Col6( rr );
    //    prob  = randomDouble( 0,1 );
    prob  = CLHEP::RandFlat::shoot();
    //std::cout << "rr=" << rr 
    //           << " prob=" << prob << " yield=" << yield 
    //          << " ct=" << ++ct
    //          << endl;
  } while( prob > yield );

  vtx = randomVector3( 1, rr, rr, 0, 2*M_PI, col6_z0, col6_z0 );// r-phi-z

  // Momentum direction at z0
  // Data from S.Inoue
  // Parameter from M.Yamaga, Fri Sep 28 15:22:34 JST 2001

  // Polar angle of momentum : uniform
  double  thmax =  0.0004 + (0.0035-0.0004)/3*rr;
  double  thmin = -0.0006 + (0.0033+0.0006)/3*rr;
  if ( thmin < 0 )
    thmin = 0;
  //double  theta = randomDouble( thmin,thmax );
  double  theta = CLHEP::RandFlat::shoot( thmin,thmax );

  // Residual of Azimuth angle of momentum : double Gaussian
  double  gnorm1  = 412.4;
  double  gmean1  = 0.6628e-03;
  double  gsigma1 = 0.1002;
  double  gnorm2  = 60.71;
  double  gmean2  = 0.2593e-03;
  double  gsigma2 = 0.2621;
  double  garea1  = gnorm1*gsigma1;
  double  garea2  = gnorm2*gsigma2;
  double  gfrac1  = garea1/(garea1+garea2);
  double  dphi;
  //  if ( randomDouble(0,1) < gfrac1 )
  //    dphi = randomGauss( gmean1,gsigma1 );
  if ( CLHEP::RandFlat::shoot() < gfrac1 )
    dphi = CLHEP::RandGauss::shoot(gmean1,gsigma1);
  else
    dphi = CLHEP::RandGauss::shoot( gmean2,gsigma2 );

  // Momentum magnitude distribution
  double  MinP = 0.01;
  double  MaxP = 11;
  double  ProbMax = exp( -m_ct*bz/MaxP ); // exp(-t/tau)=exp((M*Z)/(c*tau*P))
  double  pp,norm;
  //static int  ct=0;
  do {
    pp    = CLHEP::RandFlat::shoot( MinP, MaxP );
    norm  = exp( -m_ct*bz/pp ); // exp(-t/tau)=exp((M*Z)/(c*tau*P))
    prob  = CLHEP::RandFlat::shoot( 0., ProbMax );

    yield = PklDist_Exp( pp ) * norm;

    //std::cout << "p=" << pp << " norm=" << norm << " PMax=" << ProbMax 
    //          << " prob=" << prob << " yield=" << yield 
    //          << " ct=" << ct++
    //          << endl;
  } while ( prob > yield );

  p = CLHEP::Hep3Vector( 0,0,pp );

  // All parameter decided

  // set momentum direction at position z
  p.setTheta( theta );
  p.setPhi( vtx.phi() + dphi );

  // set vertex position at position z
  //vtx += p/p.z()*bz;
  vtx += p * ( bz / p.z() );
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimE391Spectrum::generateSpecial(const G4Event* anEvent)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  G4PrimaryVertex* pv = anEvent->GetPrimaryVertex(0);
  G4ThreeVector vPos = pv->GetPosition();
  double z=vPos.getZ();


  CLHEP::Hep3Vector p;
  CLHEP::Hep3Vector vtx;
    
  GsimGenKlongCol6( z/cm,p,vtx);
  
  pv->SetPosition(vtx.x()*cm,vtx.y()*cm,vtx.z()*cm);
  G4PrimaryParticle*    particle    = pv->GetPrimary();
  particle->SetMomentum(p.x()*GeV,p.y()*GeV,p.z()*GeV);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

/**
 *  @file
 *  @brief  GsimE391Spectrum
 *  $Id: GsimE391Spectrum.h,v 1.2 2006/12/06 19:16:44 nanjo Exp $
 *  $Log: GsimE391Spectrum.h,v $
 *  Revision 1.2  2006/12/06 19:16:44  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimE391Spectrum_h
#define GsimE391Spectrum_h

#include "GsimKernel/GsimSpectrum.h"
#include "CLHEP/Vector/ThreeVector.h"
#include <string>
#include <vector>
#include <map>

#ifndef M_PIl
# define M_PIl          3.1415926535897932384626433832795029L  /* pi */
#endif

class G4Event;
class Hep3Vector;

class GsimE391Spectrum : public GsimSpectrum
{
public:
  GsimE391Spectrum(std::string name);
  virtual ~GsimE391Spectrum();

 protected:
  GsimE391Spectrum();
  virtual void   generateSpecial(const G4Event* anEvent);
  
  
  CLHEP::Hep3Vector randomVector3( int mode,
			    double x1min, double x1max,
			    double x2min, double x2max,
			    double x3min, double x3max );
  
  double PklDist_Exp( double p );
  double Density_Col6( double r );
  void GsimGenKlongCol6( double z,CLHEP::Hep3Vector& p, CLHEP::Hep3Vector& vtx );
  
  
  
  
  
  double m_TargetZ;
};


#endif // GsimE391Spectrum_h






/**
 *  @file
 *  @brief  GsimE14Spectrum
 *  $Id: GsimE14Spectrum.h,v 1.2 2006/12/06 19:16:29 nanjo Exp $
 *  $Log: GsimE14Spectrum.h,v $
 *  Revision 1.2  2006/12/06 19:16:29  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimE14Spectrum_h
#define GsimE14Spectrum_h

#include "GsimKernel/GsimSpectrum.h"
#include <string>
#include <vector>
#include <map>

class G4Event;
class TF1;

class GsimE14Spectrum : public GsimSpectrum
{
public:
  GsimE14Spectrum(std::string name);
  virtual ~GsimE14Spectrum();

 protected:
  GsimE14Spectrum();
  double getKaonMomentum(double z);

  void getCircularProfile(double zStart,
			  double& xStart,double& yStart,
			  double& cost,double& sint,double& phi);
    
  void getSquareProfile(double zStart,
			double& xStart,double& yStart,
			double& cost,double& sint,double& phi);
  
  virtual void   generateSpecial(const G4Event* anEvent);

  static double pKLDistExit( double Pk );
  static double pKLWeight( double Pk, double dZ );
  static double pKLDist(double* x,double* par);

  double getMaximumWeight(double z);
    
  double m_pKLDistExitZ;
  double m_pMin;
  double m_wMax;
  double m_z;
  int    m_mode;
  
  TF1* m_pKLFunc;
};


#endif // GsimE14Spectrum_h






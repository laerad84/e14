/**
 *  @file
 *  @brief  GsimE14SurveySpectrum
 *  $Id: 
 *  $Log:
 */
#ifndef GsimE14SurveySpectrum_h
#define GsimE14SurveySpectrum_h

#include "GsimE14Spectrum/GsimE14Spectrum.h"
#include <string>
#include <vector>
#include <map>

class G4Event;
class TF1;

class GsimE14SurveySpectrum : public GsimE14Spectrum
{
public:
  GsimE14SurveySpectrum(std::string name);
  virtual ~GsimE14SurveySpectrum();

 protected:
  GsimE14SurveySpectrum();
  virtual void   generateSpecial(const G4Event* anEvent);

  static double pKLSurveyDistExit( double Pk );
  static double pKLSurveyDist( double *x,double *par );
};


#endif // GsimE14SurveySpectrum_h






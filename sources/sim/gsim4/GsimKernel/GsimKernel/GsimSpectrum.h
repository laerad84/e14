/**
 *  @file
 *  @brief  GsimSpectrum
 *  $Id: GsimSpectrum.h,v 1.2 2006/12/06 18:44:00 nanjo Exp $
 *  $Log: GsimSpectrum.h,v $
 *  Revision 1.2  2006/12/06 18:44:00  nanjo
 *  Midas I/O is added and Root I/O is separated. etc.
 *
 */
#ifndef GsimSpectrum_h
#define GsimSpectrum_h

#include <string>
#include <vector>
#include <map>

class TF1;
class G4Event;
class GsimSpectrumMessenger;

class GsimSpectrum 
{
public:
  GsimSpectrum(std::string name);
  virtual ~GsimSpectrum();

  std::string getName();
  
  void   addSpectrum(std::string formula,double xmin,double xmax);
  void   clear();
  
  void   generateSpectrum(const G4Event* anEvent);

  void   setParameter(double param);
  
 protected:
  GsimSpectrum();
  virtual void   generateSpecial(const G4Event* anEvent);
  std::string m_name;
  GsimSpectrumMessenger* messenger;
  std::vector<std::string> m_keyWords;
  std::map<int,TF1*> m_spectrumContainer;
  bool m_modifyVertex;
  bool m_modifyMomentum;

  double m_parameter;
};

inline std::string GsimSpectrum::getName() 
{
  return m_name;
}

inline void GsimSpectrum::setParameter(double param)
{
  m_parameter=param;
}

#endif // GsimSpectrum_h






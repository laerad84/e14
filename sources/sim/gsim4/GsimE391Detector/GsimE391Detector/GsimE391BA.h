/**
 *  @file
 *  @brief  GsimE391BA
 *  $Id: GsimE391BA.h,v 1.2 2006/12/06 18:58:52 nanjo Exp $
 *  $Log: GsimE391BA.h,v $
 *  Revision 1.2  2006/12/06 18:58:52  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimE391BA_h
#define GsimE391BA_h

//includes
#include <string>
#include <list>
#include "GsimKernel/GsimDetector.h"

//forward declaration

/**
 *  @class GsimE391BA
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimE391BA : public GsimDetector
{
 public:
  GsimE391BA(std::string name,
	     GsimDetector* motherDetector,
	     G4ThreeVector transV,
	     G4ThreeVector rotV,
	     int useFlag=0);

  virtual void   setFastSimulationLevel(int level);
  
  virtual ~GsimE391BA();

 protected:
  std::list<GsimDetector*> m_detList;
  GsimE391BA();

};


#endif // GsimE391BA_h

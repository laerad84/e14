/**
 *  @file
 *  @brief  GsimE391SAND
 *  $Id: GsimE391SAND.h,v 1.2 2006/12/06 18:58:52 nanjo Exp $
 *  $Log: GsimE391SAND.h,v $
 *  Revision 1.2  2006/12/06 18:58:52  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimE391SAND_h
#define GsimE391SAND_h

//includes
#include <string>
#include <list>
#include "GsimKernel/GsimDetector.h"

//forward declaration

/**
 *  @class GsimE391SAND
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimE391SAND : public GsimDetector
{
 public:
  GsimE391SAND(std::string name,
	       GsimDetector* motherDetector,
	       G4ThreeVector transV,
	       G4ThreeVector rotV,
	       int useFlag=0);

  virtual void   setFastSimulationLevel(int level);
  
  virtual ~GsimE391SAND();

 protected:
  std::list<GsimDetector*> m_detList;
  GsimE391SAND();

};


#endif // GsimE391SAND_h

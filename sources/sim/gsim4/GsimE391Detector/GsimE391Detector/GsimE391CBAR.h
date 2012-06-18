/**
 *  @file
 *  @brief  GsimE391CBAR
 *  $Id: GsimE391CBAR.h,v 1.2 2006/12/06 18:58:52 nanjo Exp $
 *  $Log: GsimE391CBAR.h,v $
 *  Revision 1.2  2006/12/06 18:58:52  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimE391CBAR_h
#define GsimE391CBAR_h

//includes
#include <string>
#include <list>
#include "GsimKernel/GsimDetector.h"

//forward declaration

/**
 *  @class GsimE391CBAR
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimE391CBAR : public GsimDetector
{
 public:
  GsimE391CBAR(std::string name,
	       GsimDetector* motherDetector,
	       G4ThreeVector transV,
	       G4ThreeVector rotV,
	       int useFlag=0);

  virtual void   setFastSimulationLevel(int level);
  
  virtual ~GsimE391CBAR();

 protected:
  std::list<GsimDetector*> m_detList;
  GsimE391CBAR();

};


#endif // GsimE391CBAR_h

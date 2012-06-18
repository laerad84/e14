/**
 *  @file
 *  @brief  GsimE14CBAR
 *  $Id: GsimE14CBAR.h,v 1.2 2006/12/06 19:04:45 nanjo Exp $
 *  $Log: GsimE14CBAR.h,v $
 *  Revision 1.2  2006/12/06 19:04:45  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimE14CBAR_h
#define GsimE14CBAR_h

//includes
#include <string>
#include <list>
#include "GsimKernel/GsimDetector.h"

//forward declaration

/**
 *  @class GsimE14CBAR
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimE14CBAR : public GsimDetector
{
 public:
  GsimE14CBAR(std::string name,
	      GsimDetector* motherDetector,
	      G4ThreeVector transV,
	      G4ThreeVector rotV,
	      int userFlag=0);
  
  virtual void   setFastSimulationLevel(int level);
  
  virtual ~GsimE14CBAR();

 protected:
  std::list<GsimDetector*> m_detList;
  GsimE14CBAR();

};


#endif // GsimE14CBAR_h

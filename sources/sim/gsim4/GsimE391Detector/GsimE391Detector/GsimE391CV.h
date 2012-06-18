/**
 *  @file
 *  @brief  GsimE391CV
 *  $Id: GsimE391CV.h,v 1.3 2006/12/06 18:58:52 nanjo Exp $
 *  $Log: GsimE391CV.h,v $
 *  Revision 1.3  2006/12/06 18:58:52  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimE391CV_h
#define GsimE391CV_h

//includes
#include <string>
#include <list>
#include "GsimKernel/GsimDetector.h"

//forward declaration

/**
 *  @class GsimE391CV
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimE391CV : public GsimDetector
{
 public:
  GsimE391CV(std::string name,
	     GsimDetector* motherDetector,
	     G4ThreeVector transV,
	     G4ThreeVector rotV,
	     int useFlag=0);
  virtual void   setFastSimulationLevel(int level);
  virtual ~GsimE391CV();

 protected:
  std::list<GsimDetector*> m_detList;
  GsimE391CV();

};


#endif // GsimE391CV_h

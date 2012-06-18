/**
 *  @file
 *  @brief  GsimE14CV
 *  $Id: GsimE14CV.h,v 1.2 2006/12/06 19:04:45 nanjo Exp $
 *  $Log: GsimE14CV.h,v $
 *  Revision 1.2  2006/12/06 19:04:45  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimE14CV_h
#define GsimE14CV_h

//includes
#include <string>
#include "GsimKernel/GsimDetector.h"

//forward declaration

/**
 *  @class GsimE14CV
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimE14CV : public GsimDetector
{
 public:
  GsimE14CV(std::string name,
	    GsimDetector* motherDetector,
	    G4ThreeVector transV,
	    G4ThreeVector rotV,
	    int userFlag=0);
  
  virtual ~GsimE14CV();
  
 protected:
  GsimE14CV();
  int m_mode;
  void fgetCenter(double width,double l1,double l2,double d,
		  double& xCenter,double& yCenter,double& zCenter);
  void fmakeParameter(double width,double l1,double l2,double d,std::vector<double>& paramVec);
  
  void fgetFiberCenter(double l1,double l2,double d,
		       double& xCenter,double& yCenter,double& zCenter);
  void fmakeFiberParameter(double l1,double l2,double d,std::vector<double>& paramVec);
  

  void rgetCenter(double width,double l,
		 double& xCenter,double& yCenter,double& zCenter);
  void rmakeParameter(double width,double l,std::vector<double>& paramVec);
  void rgetFiberCenter(double l,
		       double& xCenter,double& yCenter,double& zCenter);
  void rmakeFiberParameter(double l,std::vector<double>& paramVec);
};


#endif // GsimE14CV_h

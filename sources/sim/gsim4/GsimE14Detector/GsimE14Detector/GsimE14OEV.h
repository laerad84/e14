/**
 *  @file
 *  @brief  GsimE14OEV
 *  $Id: GsimE14OEV.h,v 1.3 2006/12/06 19:04:45 nanjo Exp $
 *  $Log: GsimE14OEV.h,v $
 *  Revision 1.3  2006/12/06 19:04:45  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimE14OEV_h
#define GsimE14OEV_h

//includes
#include <string>
#include "GsimKernel/GsimDetector.h"

//forward declaration

/**
 *  @class GsimE14OEV
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimE14OEV : public GsimDetector
{
 public:
  GsimE14OEV(std::string name,
	     GsimDetector* motherDetector,
	     G4ThreeVector transV,
	     G4ThreeVector rotV,
	     int userFlag=0);
  virtual ~GsimE14OEV();
 protected:
  GsimE14OEV();
  int m_model;
  std::list<GsimDetector*> m_detList;
 
 private:
  // Get size and position of sandwich layers
  // for the upper modules (1t aluminum flame) 
  void GetLayerVolumeTop(int itype, 
			 int &layerNo, 
			 std::vector<double> &vec, 
			 double &x, 
			 double &y, 
			 bool &isLead,
			 int &id);

  // Get size and position of sandwich layers
  // for the uppermost modules (1t aluminum flame) 
  void GetLayerVolumeTopVer1(int itype, 
			     int &layerNo, 
			     std::vector<double> &vec, 
			     double &x, 
			     double &y, 
			     bool &isLead,
			     int &id);

  // Get size and position of sandwich layers
  // for the lower modules (2t SUS flame) 
  void GetLayerVolumeBottom(int itype, 
			    int &layerNo, 
			    std::vector<double> &vec, 
			    double &x, 
			    double &y, 
			    bool &isLead,
			    int &id);

  // Get size and position of Al bar and air-gaps
  // for the lower modules (2t SUS flame) 
  void GetBarAndAirgap(int itype,
		       int &counter,
		       std::vector<double> &vec,
		       double &x,
		       double &y,
		       bool &isBar,
		       int &id);

};


#endif // GsimE14OEV_h

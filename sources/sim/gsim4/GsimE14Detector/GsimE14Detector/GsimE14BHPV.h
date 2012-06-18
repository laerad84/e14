/**
 *  @file
 *  @brief  GsimE14BHPV
 *  $Id: GsimE14BHPV.h,v 1.2 2006/12/06 19:04:45 nanjo Exp $
 *  $Log: GsimE14BHPV.h,v $
 *  Revision 1.2  2006/12/06 19:04:45  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimE14BHPV_h
#define GsimE14BHPV_h

//includes
#include <string>
#include <list>
#include "GsimKernel/GsimDetector.h"

//forward declaration
class G4Step;
class G4TouchableHistory;
class GsimWinstonCone;

/**
 *  @class GsimE14BHPV
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimE14BHPV : public GsimDetector
{
 public:
  GsimE14BHPV(std::string name,
	      GsimDetector* motherDetector,
	      G4ThreeVector transV,
	      G4ThreeVector rotV,
	      int userFlag=0);
  
  virtual ~GsimE14BHPV();
  
  virtual void setFastSimulationLevel(int level);
  virtual void processHits(const G4Step* aStep,G4TouchableHistory* ROhist);

  void traceFromInsideAerogel(const G4Step* aStep,G4TouchableHistory* ROhist);
  bool traceWCone(double waveL,double* pPos, double* pVec);
  bool traceAerogel(double waveL,double* pPos, double* pVec);
  bool traceOpticalBox(double waveL,double* pPos, double* pVec);
  void scatterInAerogel(double* pVec);
  double getPMTQE(double waveL);
  static double getBHPVLength();

  void translateFromGlobalToAG(const G4Step* aStep,double* pPos, double* pVec);
  void translateFromAGToOBox(double* pPos, double* pVec);
  void translateFromOBoxToWCone(double* pPos, double* pVec);
  void translateFromWConeToOBox(double* pPos, double* pVec);

  double dNextAbsorption(double waveL);
  double dNextScattering(double waveL);
  
 protected:
  bool   m_opticalMode;
  double m_lenXY;//cm
  double m_lenTile;//cm
  double m_pbThick;//cm
  double m_agThick;//cm
  double m_gap1Thick;//cm
  double m_gap2Thick;//cm
  double m_mirrorSpace;//cm
  double m_plateThick;//cm
  double m_mirrorAngle;//degree
  double m_gapOBoxWCone;//cm
  double m_dInWCone;//[cm]
  double m_dOutWCone;//[cm]
  double m_gapWConePMT;//[cm]
  double m_rPMT;//[cm]


  double m_transmittanceWrap;//transmittance of wrap for AG
  double m_reflectanceWall;//reflectance of OBox wall
  double m_reflectanceMirror;//reflectance of mirror
  double m_reflectanceWCone;//reflectance of WinstonCone

  double m_reflectanceAGWall[3];//reflectance of AG xyz walls
  double m_nMaxReflectionAGWall[3];

  double m_QEmisc;//overall efficiency

  int m_nReflectionAGWall[3];
  int m_nReflectionOBoxWall;
  int m_nReflectionMirror;
  int m_nReflectionWConeWall;

  double m_pathLengthAG;
  double m_pathLengthOBox;
  double m_pathLengthWCone;
  double m_pathLengthAir;

  double m_refractiveIndexAG;
  
  int m_nLayer;

  GsimWinstonCone* m_winstonCone;
  
  std::list<GsimDetector*> m_detList;
  GsimE14BHPV();
};

      


#endif // GsimE14BHPV_h

/**
 *  @file
 *  @brief  GsimDetectorData
 *  $Id: GsimDetectorData.h,v 1.9 2006/12/06 18:38:38 nanjo Exp $ 
 *  $Log: GsimDetectorData.h,v $
 *  Revision 1.9  2006/12/06 18:38:38  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimDetectorData_h
#define GsimDetectorData_h

//includes
#include "TObject.h"
#include "TString.h"
#include "TVector3.h"

#include <vector>

/**
 *  @class GsimDetectorData
 *  @brief Detector property data.
 *  This class provides ...
 */
class GsimDetectorData : public TObject
{
 public:
  /**
   *  @function GsimDetectorData
   *  @brief Constructor for GsimDetectorData
   */
  GsimDetectorData();
  GsimDetectorData(const GsimDetectorData&);
  /**
   *  @function ~GsimDetectorData
   *  @brief Destructor for GsimDetectorData
   */
  virtual ~GsimDetectorData();

  virtual void   Clear(Option_t* opt="");

  void initializeDataValues();


  std::vector<Int_t> getChannelList();
  TVector3 getPosition(Int_t channel);
  
  TString m_fullName;
  TString m_briefName;
  TString m_className;

  Int_t m_detectorID;
  Int_t m_briefDetectorID;
  
  Int_t m_motherDetectorID;
  Int_t m_physiDetector;
  
  
  TVector3 m_localCenterVector;
  TVector3 m_translationVector;
  TVector3 m_rotationVector;
  TVector3 m_magneticFieldVector;
  TVector3 m_position;

  Double_t m_userLimitsStepMax;
  Double_t m_userLimitsTrackMax;
  Double_t m_userLimitsTimeMax;
  Double_t m_userLimitsEkinMin;
  Double_t m_userLimitsRangeMin;


  TString m_outerMaterialName;
  TString m_outerColorName;
  Int_t   m_isOuterVisible;
  
  Int_t      m_numberOfParameters;
  Double_t*  m_parameterArray;//[m_numberOfParameters]

  Int_t      m_fastSimulationLevel;
  Int_t      m_userFlag;

  Int_t      m_nDaughter;
  Int_t*     m_daughterIDArray;//[m_nDaughter]
  

  Int_t      m_numberOfSensitiveDetector;
  TString    m_sensitiveDetectorName;
  Int_t      m_sensitiveDetectorWithHit;
  Int_t      m_sensitiveDetectorWithDigi;
  Int_t      m_copyNo;


  Int_t          m_nClone; 
  Int_t*         m_clonedCopyNoArray;//[m_nClone]
  Double_t*      m_clonedTranslationXArray;//[m_nClone]
  Double_t*      m_clonedTranslationYArray;//[m_nClone]
  Double_t*      m_clonedTranslationZArray;//[m_nClone]
  Double_t*      m_clonedRotationVectorXArray;//[m_nClone]
  Double_t*      m_clonedRotationVectorYArray;//[m_nClone]
  Double_t*      m_clonedRotationVectorZArray;//[m_nClone]
  Double_t*      m_clonedPositionXArray;//[m_nClone]
  Double_t*      m_clonedPositionYArray;//[m_nClone]
  Double_t*      m_clonedPositionZArray;//[m_nClone]

  void import(const  GsimDetectorData& right);
  
  GsimDetectorData& operator=(const  GsimDetectorData& right);

  

  
  ClassDef(GsimDetectorData,1)
};

#endif // GsimDetectorData_h


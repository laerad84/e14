/**
 *  $Id: GsimDetectorData.cc,v 1.11 2006/12/07 13:49:47 nanjo Exp $
 *  $Log: GsimDetectorData.cc,v $
 *  Revision 1.11  2006/12/07 13:49:47  nanjo
 *  Remove extra ;
 *
 *  Revision 1.10  2006/12/06 18:38:38  nanjo
 *  CVS variables.
 *
 */
#include "GsimData/GsimDetectorData.h"
#include <iostream>

#if !defined(__CINT__)
ClassImp(GsimDetectorData)
#endif

GsimDetectorData::GsimDetectorData() :
  TObject(),
  m_parameterArray(0),
  m_daughterIDArray(0),
  m_clonedCopyNoArray(0),
  m_clonedTranslationXArray(0),
  m_clonedTranslationYArray(0),
  m_clonedTranslationZArray(0),
  m_clonedRotationVectorXArray(0),
  m_clonedRotationVectorYArray(0),
  m_clonedRotationVectorZArray(0),
  m_clonedPositionXArray(0),
  m_clonedPositionYArray(0),
  m_clonedPositionZArray(0)
{
  
}

GsimDetectorData::GsimDetectorData(const GsimDetectorData& right)
  : TObject(right)
{
  import(right);
}

GsimDetectorData::~GsimDetectorData()
{
  Clear();
}

void GsimDetectorData::Clear(Option_t*)
{
  delete [] m_parameterArray;
  delete [] m_daughterIDArray;
  delete [] m_clonedCopyNoArray;
  delete [] m_clonedTranslationXArray;
  delete [] m_clonedTranslationYArray;
  delete [] m_clonedTranslationZArray;
  delete [] m_clonedRotationVectorXArray;
  delete [] m_clonedRotationVectorYArray;
  delete [] m_clonedRotationVectorZArray;
  delete [] m_clonedPositionXArray;
  delete [] m_clonedPositionYArray;
  delete [] m_clonedPositionZArray;
  
  m_parameterArray=0;
  m_daughterIDArray=0;
  m_clonedCopyNoArray=0;
  m_clonedTranslationXArray=0;
  m_clonedTranslationYArray=0;
  m_clonedTranslationZArray=0;
  m_clonedRotationVectorXArray=0;
  m_clonedRotationVectorYArray=0;
  m_clonedRotationVectorZArray=0;
  m_clonedPositionXArray=0;
  m_clonedPositionYArray=0;
  m_clonedPositionZArray=0;
}

void GsimDetectorData::initializeDataValues()
{
  Clear();
}


void GsimDetectorData::import(const  GsimDetectorData& right)
{
  if (this != &right) {
    Clear();

    m_fullName=right.m_fullName;
    m_briefName=right.m_briefName;
    m_className=right.m_className;

    m_detectorID=right.m_detectorID;
    m_briefDetectorID=right.m_briefDetectorID;
  
    m_motherDetectorID=right.m_motherDetectorID;
    m_physiDetector=right.m_physiDetector;
  
  
    m_localCenterVector=right.m_localCenterVector;
    m_translationVector=right.m_translationVector;
    m_rotationVector=right.m_rotationVector;
    m_position=right.m_position;
    m_magneticFieldVector=right.m_magneticFieldVector;
    

    m_userLimitsStepMax=right.m_userLimitsStepMax;
    m_userLimitsTrackMax=right.m_userLimitsTrackMax;
    m_userLimitsTimeMax=right.m_userLimitsTimeMax;
    m_userLimitsEkinMin=right.m_userLimitsEkinMin;
    m_userLimitsRangeMin=right.m_userLimitsRangeMin;


    m_outerMaterialName=right.m_outerMaterialName;
    m_outerColorName=right.m_outerColorName;
    m_isOuterVisible=right.m_isOuterVisible;
    
    m_numberOfParameters=right.m_numberOfParameters;
    m_parameterArray = new Double_t[m_numberOfParameters];
    for(int k=0;k<m_numberOfParameters;k++) {
      m_parameterArray[k] = right.m_parameterArray[k];
    }

    m_fastSimulationLevel=right.m_fastSimulationLevel;
    m_userFlag=right.m_userFlag;

    m_nDaughter = right.m_nDaughter;
    m_daughterIDArray = new Int_t[m_nDaughter];
    for(int k=0;k<m_nDaughter;k++) {
      m_daughterIDArray[k]=right.m_daughterIDArray[k];
    }
  

    m_numberOfSensitiveDetector=right.m_numberOfSensitiveDetector;
    m_sensitiveDetectorName=right.m_sensitiveDetectorName;
    m_sensitiveDetectorWithHit=right.m_sensitiveDetectorWithHit;
    m_sensitiveDetectorWithDigi = right.m_sensitiveDetectorWithDigi;
    m_copyNo = right.m_copyNo;


    m_nClone = right. m_nClone;
    m_clonedCopyNoArray = new Int_t[m_nClone];
    m_clonedTranslationXArray = new Double_t[m_nClone];
    m_clonedTranslationYArray = new Double_t[m_nClone];
    m_clonedTranslationZArray = new Double_t[m_nClone];
    m_clonedRotationVectorXArray = new Double_t[m_nClone];
    m_clonedRotationVectorYArray = new Double_t[m_nClone];
    m_clonedRotationVectorZArray = new Double_t[m_nClone];
    m_clonedPositionXArray = new Double_t[m_nClone];
    m_clonedPositionYArray = new Double_t[m_nClone];
    m_clonedPositionZArray = new Double_t[m_nClone];

    for(int k=0;k<m_nClone;k++) {
      m_clonedCopyNoArray[k] = right.m_clonedCopyNoArray[k];
      m_clonedTranslationXArray[k] = right.m_clonedTranslationXArray[k];
      m_clonedTranslationYArray[k] = right.m_clonedTranslationYArray[k];
      m_clonedTranslationZArray[k] = right.m_clonedTranslationZArray[k];
      m_clonedRotationVectorXArray[k] = right.m_clonedRotationVectorXArray[k];
      m_clonedRotationVectorYArray[k] = right.m_clonedRotationVectorYArray[k];
      m_clonedRotationVectorZArray[k] = right.m_clonedRotationVectorZArray[k];
      m_clonedPositionXArray[k] = right.m_clonedPositionXArray[k];
      m_clonedPositionYArray[k] = right.m_clonedPositionYArray[k];
      m_clonedPositionZArray[k] = right.m_clonedPositionZArray[k];
    }
  }
}


GsimDetectorData& GsimDetectorData::operator=(const  GsimDetectorData& right)
{
  import(right);
  return *this;
}


std::vector<Int_t> GsimDetectorData::getChannelList()
{
  std::vector<Int_t> chList;
  chList.push_back(m_copyNo);
  for(int i=0;i<m_nClone;i++) {
    chList.push_back(m_clonedCopyNoArray[i]);
  }
  return chList;
}

TVector3 GsimDetectorData::getPosition(Int_t channel)
{
  if(channel==m_copyNo) {
    return m_translationVector;
  } else {
    for(int i=0;i<m_nClone;i++) {
      if(channel==m_clonedCopyNoArray[i]) {
	return TVector3(m_clonedTranslationXArray[i],
			m_clonedTranslationYArray[i],
			m_clonedTranslationZArray[i]);
      }
    }
  }

  std::cerr << "No such channel, " << channel << std::endl;
  return TVector3(-999,-999,-999);
  
}

/**
 *  @file
 *  @brief  GsimPhysicalVolumeData
 *  $Id: GsimPhysicalVolumeData.h,v 1.2 2006/12/06 18:38:38 nanjo Exp $
 *  $Log: GsimPhysicalVolumeData.h,v $
 *  Revision 1.2  2006/12/06 18:38:38  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimPhysicalVolumeData_h
#define GsimPhysicalVolumeData_h

//includes
#include "TObject.h"
#include "TString.h"

//forward declaration


/**
 *  @class GsimPhysicalVolumeData
 *  @brief This class stores event data for output to a ROOT file.
 *
 *  The process ID and Name are stored.
 */
class GsimPhysicalVolumeData : public TObject
{
 public:
  /**
   *  @function GsimPhysicalVolumeData
   *  @brief Constructor for GsimPhysicalVolumeData.
   */
  GsimPhysicalVolumeData();


  GsimPhysicalVolumeData(const GsimPhysicalVolumeData&);

  
  /**
   *  @function ~GsimPhysicalVolumeData
   *  @brief Destructor for GsimPhysicalVolumeData.
   */
  virtual ~GsimPhysicalVolumeData();


  virtual void   Clear(Option_t* opt="");
  
  /**
   *  @function initializeDataValues
   *  @brief Initializes the event.
   *  @param id The event ID.
   *
   *  Initializes the event ID to the given value and clears the briefTracks.
   */
  void initializeDataValues();

  TString  pvName;
  Int_t    pvCopyNo;
  Int_t    detID;
  TString  detFullName;
  TString  detBriefName;
  Int_t    sdFlag;
  TString  sdName;
  Int_t    sdID;
  Int_t    sdNch;
  Int_t*   sdChID;//[sdNch]
  Int_t*   sdClID;//[sdNch]
  
  

  GsimPhysicalVolumeData& operator=(const  GsimPhysicalVolumeData& right);
  
 protected:
  ClassDef(GsimPhysicalVolumeData,1)
};

#endif // GsimPhysicalVolumeData_h


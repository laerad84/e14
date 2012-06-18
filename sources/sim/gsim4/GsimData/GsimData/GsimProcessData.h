/**
 *  @file
 *  @brief  GsimProcessData
 *  $Id: GsimProcessData.h,v 1.2 2006/12/06 18:38:38 nanjo Exp $
 *  $Log: GsimProcessData.h,v $
 *  Revision 1.2  2006/12/06 18:38:38  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimProcessData_h
#define GsimProcessData_h

//includes
#include "TObject.h"
#include "TString.h"

//forward declaration


/**
 *  @class GsimProcessData
 *  @brief This class stores event data for output to a ROOT file.
 *
 *  The process ID and Name are stored.
 */
class GsimProcessData : public TObject
{
 public:
  /**
   *  @function GsimProcessData
   *  @brief Constructor for GsimProcessData.
   */
  GsimProcessData();


  GsimProcessData(const GsimProcessData&);

  
  /**
   *  @function ~GsimProcessData
   *  @brief Destructor for GsimProcessData.
   */
  virtual ~GsimProcessData();


  virtual void   Clear(Option_t* opt="");
  
  /**
   *  @function initializeDataValues
   *  @brief Initializes the event.
   *  @param id The event ID.
   *
   *  Initializes the event ID to the given value and clears the briefTracks.
   */
  void initializeDataValues();

  UShort_t processID;
  TString  processName;

  GsimProcessData& operator=(const  GsimProcessData& right);
  bool operator == (const GsimProcessData& right) const;
  bool operator != (const GsimProcessData& right) const;
  
 protected:
  ClassDef(GsimProcessData,1)
};

#endif // GsimProcessData_h


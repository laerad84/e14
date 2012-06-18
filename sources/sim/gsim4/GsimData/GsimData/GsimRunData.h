/**
 *  @file
 *  @brief  GsimRunData
 *  $Id: GsimRunData.h,v 1.1 2006/12/07 04:44:29 nanjo Exp $
 *  $Log: GsimRunData.h,v $
 *  Revision 1.1  2006/12/07 04:44:29  nanjo
 *  GsimRunData is added.
 *
 */
#ifndef GsimRunData_h
#define GsimRunData_h

//includes
#include <TObject.h>

/**
 *  @class GsimRunData
 *  @brief GsimRunData
 *  This class provides ...
 */
class GsimRunData : public TObject
{
 public:
  /**
   *  @function GsimRunData
   *  @brief Constructor for GsimRunData
   */
  GsimRunData();
  /**
   *  @function ~GsimRunData
   *  @brief Destructor for GsimRunData
   */
  virtual ~GsimRunData();

  virtual void   Clear(Option_t* opt="");

  void initializeDataValues();
  
  /**
   *  @brief The module ID (hit channel).
   */
  UShort_t    runNumber;
  UShort_t    runID;
  UInt_t      nEventsRequested;
  UInt_t      nEventsProcessed;
  UInt_t      nEventsStored;
  UInt_t      version;
  
  ClassDef(GsimRunData,1)
};

#endif // GsimRunData_h


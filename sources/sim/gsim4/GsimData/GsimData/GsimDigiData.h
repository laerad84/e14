/**
 *  @file
 *  @brief  GsimDigiData
 *  $Id: GsimDigiData.h,v 1.13 2006/12/09 21:33:44 nanjo Exp $ 
 *  $Log: GsimDigiData.h,v $
 *  Revision 1.13  2006/12/09 21:33:44  nanjo
 *  briefHistory is corrected.
 *
 *  Revision 1.12  2006/12/09 00:42:57  nanjo
 *  dump.
 *
 *  Revision 1.11  2006/12/06 18:38:38  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimDigiData_h
#define GsimDigiData_h

//includes
#include "TObject.h"

/**
 *  @class GsimDigiData
 *  @brief Digitization data.
 *  This class provides digitization information.
 */
class GsimDigiData : public TObject
{
 public:
  /**
   *  @function GsimDigiData
   *  @brief Constructor for GsimDigiData
   */
  GsimDigiData();
  /**
   *  @function ~GsimDigiData
   *  @brief Destructor for GsimDigiData
   */
  virtual ~GsimDigiData();

  virtual void   Clear(Option_t* opt="");

  void initializeDataValues();

  void dump(int imode=1);

  /**
   *  @brief The detector ID.
   */
  UShort_t     detID;
  /**
   *  @brief The module ID (hit channel).
   */
  UShort_t     modID;
  Float_t      energy;
  Float_t      time;

  /**
   *  @brief This's ID.
   */
  UShort_t  thisID;

  UShort_t status;
  
  /**
   *  @brief Stored track ID.
   */
  UShort_t  track;

  UShort_t  mtimeEntry;
  UShort_t  mtimeSize;
  
  ClassDef(GsimDigiData,1)
};




#endif // GsimDigiData_h


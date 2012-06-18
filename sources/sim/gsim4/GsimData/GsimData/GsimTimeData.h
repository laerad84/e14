/**
 *  @file
 *  @brief  GsimTimeData
 *  $Id: GsimTimeData.h,v 1.6 2006/12/09 00:42:57 nanjo Exp $
 *  $Log: GsimTimeData.h,v $
 *  Revision 1.6  2006/12/09 00:42:57  nanjo
 *  dump.
 *
 *  Revision 1.5  2006/12/06 18:38:38  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimTimeData_h
#define GsimTimeData_h

//includes
#include <TObject.h>

/**
 *  @class GsimTimeData
 *  @brief GsimTimeData
 *  This class provides ...
 */
class GsimTimeData : public TObject
{
 public:
  /**
   *  @function GsimTimeData
   *  @brief Constructor for GsimTimeData
   */
  GsimTimeData();
  /**
   *  @function ~GsimTimeData
   *  @brief Destructor for GsimTimeData
   */
  virtual ~GsimTimeData();

  virtual void   Clear(Option_t* opt="");

  void initializeDataValues();
  
  void dump(int imode=1);
  
  /**
   *  @brief The module ID (hit channel).
   */
  UShort_t     modID;
  Float_t      energy;
  Float_t      time;
  
  ClassDef(GsimTimeData,1)
};

#endif // GsimTimeData_h


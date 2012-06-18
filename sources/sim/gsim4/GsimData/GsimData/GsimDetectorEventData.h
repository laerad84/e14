/**
 *  @file
 *  @brief  GsimDetectorEventData
 *  @author Hajime Nanjo <nanjo@scphys.kyoto-u.ac.jp>
 *  @date   2005.10.5
 *  $Id: GsimDetectorEventData.h,v 1.15 2006/12/09 00:42:57 nanjo Exp $
 *  $Log: GsimDetectorEventData.h,v $
 *  Revision 1.15  2006/12/09 00:42:57  nanjo
 *  dump.
 *
 *  Revision 1.14  2006/12/07 08:51:10  nanjo
 *  Types of mother and mech are changed to Short_t.
 *
 *  Revision 1.13  2006/10/11 03:35:33  nanjo
 *  GsimTriggerData is removed.
 *
 *  Revision 1.12  2006/10/11 01:51:30  nanjo
 *  GsimTriggerData is added.
 *
 *  Revision 1.11  2006/08/24 22:19:01  nanjo
 *  Almost all data type is changed from double to Float_t, from int to UShort_t.
 *
 *  Revision 1.10  2006/08/11 08:48:52  nanjo
 *  Clear is added for some GsimDatas
 *
 *  Revision 1.9  2006/08/11 02:43:20  nanjo
 *  //-> is added since TClonesArray* is always non-zero.
 *
 *  Revision 1.8  2006/08/09 13:24:58  nanjo
 *  ROOT streamer is corrected and warning message in material check is suppressed.
 *
 *  Revision 1.7  2006/08/08 11:15:04  nanjo
 *  GsimTimeData is introduced and TRefArray is used.
 *
 *  Revision 1.6  2006/06/21 03:57:36  jfiggins
 *  Added Javadoc-style Doxygen comments.
 *
 *  Revision 1.5  2006/06/14 14:58:28  nanjo
 *  The size of TClonesArray is defined by a private static const member
 *
 *  Revision 1.4  2006/06/14 03:35:54  nanjo
 *  GsimDigiData is added and size of TClonesArray is expanded.
 *
 *  Revision 1.3  2006/02/01 15:42:25  nanjo
 *  BriefTrajectory is stored in ROOT file.
 *
 *  Revision 1.2  2006/01/31 02:59:16  nanjo
 *  TString is not used for Root I/O.
 *
 *  Revision 1.1  2006/01/26 06:11:19  nanjo
 *  Detector and data classes are added.
 *
 */
#ifndef GsimDetectorEventData_h
#define GsimDetectorEventData_h

//includes
#include "GsimData/GsimDetectorHitData.h"
#include "GsimData/GsimDigiData.h"
#include "GsimData/GsimTimeData.h"

#include "TObject.h"
#include "TClonesArray.h"

//forward declaration


/**
 *  @class GsimDetectorEventData
 *  @brief This class stores detector event data for output to a ROOT file.
 *
 *  The number of hits, the total energy deposited, the time of the first
 *  hit, the time of the last hit, and an array of the hits are stored.
 */
class GsimDetectorEventData : public TObject
{
 public:
  /**
   *  @function GsimDetectorEventData
   *  @brief Constructor for GsimDetectorEventData.
   */
  GsimDetectorEventData();
  /**
   *  @function ~GsimDetectorEventData
   *  @brief Destructor for GsimDetectorEventData.
   */
  virtual ~GsimDetectorEventData();


  virtual void   Clear(Option_t* opt="");
  
  /**
   *  @function initializeDataValues
   *  @brief Initializes the detector event data.
   *
   *  The number of hits, total energy deposited,
   *  and times are set to default values. The hits
   *  array is cleared.
   */
  void initializeDataValues();
  /**
   *  @function clearHitData
   *  @brief Clears the hit data array.
   */
  void clearHitData();
  /**
   *  @function getClassName
   *  @brief Returns the name of the class - "GsimDetectorEventData".
   */
  std::string getClassName();
  /**
   *  @function getArraySize
   *  @brief Returns the size of the hits and digi arrays.
   *  @return 
   */
  static int getArraySize();

  void dumpHits();
  void dumpDigi();

  /**
   *  @brief Detector (trigger) status.
   */
  UShort_t           status;
  
  /**
   *  @brief The number of hits.
   */
  UShort_t           nHit;
  /**
   *  @brief The number of digi.
   */
  UShort_t           nDigi;
  /**
   *  @brief The number of trigger channel.
   */
  UShort_t           nTrig;
  /**
   *  @brief The total energy deposited.
   */
  Float_t        totalEnergy;
  /**
   *  @brief The time of the first hit.
   */
  Float_t        firstHitTime;
  /**
   *  @brief The time of the last hit.
   */
  Float_t        lastHitTime;

  
  /**
   *  @brief An array of the hits.
   */
  TClonesArray* hits;//->
  /**
   *  @brief An array of the digitizers.
   */
  TClonesArray* digi;//->

  /**
   *  @brief An array of time.
   */
  TClonesArray* mtime;//->

  /**
   *  @brief An array of time.
   */
  TClonesArray* trig;//->
  
 protected:
  /**
   *  @brief The name of the detector event.
   *
   *  Currently (release 0-5), this is left blank - "".
   */
  std::string name;//!
  /**
   *  @brief The name of the class.
   *
   *  This is hardcoded to "GsimDetectorEventData".
   */
  std::string className;//!
  Float_t t1;//!
  Float_t t2;//!
  /**
   *  @brief The size of the hits and digi arrays.
   *
   *  As of release-0-5, this is hardcoded to 50,000.
   */
  static const int s_arraySize;//!
  
  ClassDef(GsimDetectorEventData,1)
};

inline std::string GsimDetectorEventData::getClassName() {
  return className;
}

inline int GsimDetectorEventData::getArraySize() {
  return s_arraySize;
}
     

#endif // GsimDetectorEventData_h


/**
 *  @file
 *  @brief  GsimEventData
 *  $Id: GsimEventData.h,v 1.9 2006/12/06 18:38:38 nanjo Exp $
 *  $Log: GsimEventData.h,v $
 *  Revision 1.9  2006/12/06 18:38:38  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimEventData_h
#define GsimEventData_h

//includes
#include "TObject.h"
#include <string>


// Trigger Bit of TRG1
#define  TRIG_ONSPILL   0x01
#define  TRIG_SPILLON   TRIG_ONSPILL
#define  TRIG_CLOCK     0x02
#define  TRIG_COSMIC    0x04
#define  TRIG_XE        0x08
#define  TRIG_NCLUS     0x10
#define  TRIG_NXCLUS    0x20
#define  TRIG_SPECIAL1  0x40
#define  TRIG_SPECIAL2  0x80


//forward declaration


/**
 *  @class GsimEventData
 *  @brief This class stores event data for output to a ROOT file.
 *
 *  The event ID and an array of tracks are stored.
 */
class GsimEventData : 
public TObject
{
 public:
  /**
   *  @function GsimEventData
   *  @brief Constructor for GsimEventData.
   */
  GsimEventData();
  /**
   *  @function ~GsimEventData
   *  @brief Destructor for GsimEventData.
   */
  virtual ~GsimEventData();


  virtual void   Clear(Option_t* opt="");
  
  /**
   *  @function initializeDataValues
   *  @brief Initializes the event.
   *  @param id The event ID.
   *
   *  Initializes the event ID to the given value and clears the briefTracks.
   */
  void initializeDataValues();

  /**
   *  @function getClassName
   *  @brief Returns the name of the class - "GsimEventData".
   */
  std::string getClassName();

  
  UShort_t expMC;          // exp=1,MC=2
  UShort_t run_number;     // 
  UShort_t spill_number;   //
  UInt_t   event_number;   //
  UInt_t   trigger;        // trigger bit pattern
  UInt_t   time_stamp;     // localtime
  UInt_t   status;         // general status
  //Int_t   thisID;
  UShort_t version;
  
 protected:
  /**
   *  @brief The name of this event.
   *
   *  Currently (release 0-5), this is left blank - "".
   */
  std::string name;//!
  /**
   *  @brief The name of the class.
   *
   *  This is hardcoded to "GsimEventData".
   */
  std::string className;//!

  ClassDef(GsimEventData,1)
};

inline std::string GsimEventData::getClassName() {
  return className;
}

#endif // GsimEventData_h


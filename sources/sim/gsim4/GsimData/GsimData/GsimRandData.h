/**
 *  @file
 *  @brief  GsimEventData
 *  $Id: GsimRandData.h,v 1.2 2006/12/06 18:38:38 nanjo Exp $
 *  $Log: GsimRandData.h,v $
 *  Revision 1.2  2006/12/06 18:38:38  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimRandData_h
#define GsimRandData_h

//includes
#include "TObject.h"
#include <string>
#include <vector>


//forward declaration


/**
 *  @class GsimRandData
 *  @brief This class stores event data for output to a ROOT file.
 *
 *  The event ID and an array of tracks are stored.
 */
class GsimRandData : 
public TObject
{
 public:
  /**
   *  @function GsimRandData
   *  @brief Constructor for GsimRandData.
   */
  GsimRandData();
  /**
   *  @function ~GsimRandData
   *  @brief Destructor for GsimRandData.
   */
  virtual ~GsimRandData();


  virtual void   Clear(Option_t* opt="");
  
  /**
   *  @function initializeDataValues
   *  @brief Initializes the event.
   *  @param id The event ID.
   *
   *  Initializes the event ID to the given value and clears the briefTracks.
   */
  void initializeDataValues();


  static bool getSeed(std::string tfName,int treeID,int eventID,
		      std::vector<unsigned long>& seedVector);


  /**
   *  @function getClassName
   *  @brief Returns the name of the class - "GsimRandData".
   */
  std::string getClassName();

  
  UShort_t   run_number;
  UInt_t     event_number;
  UInt_t     engineID;
  /// Seed of Mersenne Twister
  /**
   * std::vector<unsigned long> vSeed = HepRandom::getTheEngine()->put();
   * size is 626
   * [0]       engine flag
   *              #include "CLHEP/Random/engineIDulong.h"
   *              CLHEP::crc32ul("MTwistEngine");
   * [1]-[624] seeds list
   *       The single seed used in setSeed(seed) is placed
   *              at the 1st position of seeds list.
   * [625]     counter value (1..624)
   */
  UInt_t    seed[624];//[624]
  UInt_t    count;
  UShort_t  version;

  //seed1;
  //sedd2;
  //thisID;
  
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
   *  This is hardcoded to "GsimRandData".
   */
  std::string className;//!

  ClassDef(GsimRandData,1)
};

inline std::string GsimRandData::getClassName() {
  return className;
}

#endif // GsimRandData_h


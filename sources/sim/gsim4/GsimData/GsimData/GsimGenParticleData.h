/**
 *  @file
 *  @brief  GsimGenParticleData
 *  $Id: GsimGenParticleData.h,v 1.3 2006/12/07 23:22:20 nanjo Exp $
 *  $Log: GsimGenParticleData.h,v $
 *  Revision 1.3  2006/12/07 23:22:20  nanjo
 *  dump is added.
 *
 *  Revision 1.2  2006/12/06 18:38:38  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimGenParticleData_h
#define GsimGenParticleData_h

//includes
#include "GsimData/GsimTrackData.h"

#include "TObject.h"
#include "TClonesArray.h"
#include <list>

//forward declaration


/**
 *  @class GsimGenParticleData
 *  @brief This class stores event data for output to a ROOT file.
 *
 *  The array of tracks are stored.
 */
class GsimGenParticleData : 
public TObject
{
 public:
  /**
   *  @function GsimGenParticleData
   *  @brief Constructor for GsimGenParticleData.
   */
  GsimGenParticleData();
  /**
   *  @function ~GsimGenParticleData
   *  @brief Destructor for GsimGenParticleData.
   */
  virtual ~GsimGenParticleData();


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
   *  @brief Returns the name of the class - "GsimGenParticleData".
   */
  std::string getClassName();

  /**
   *  @function getArraySize
   *  @brief Returns the size of the array.
   *  @return The size of the array.
   *
   *  As of release-0-5, this is hardcoded to return 50,000.
   */
  static int getArraySize();

  void      dump();
  
  void scanParent(int iParent,
		  std::list<GsimTrackData*>& tdp,
		  std::list<int>& state);
  
  
  /**
   *  @brief An array of the tracks associated with this event.
   */
  TClonesArray* briefTracks;//->
  UShort_t      version;


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
   *  This is hardcoded to "GsimGenParticleData".
   */
  std::string className;//!
  /**
   *  @brief The size of the array.
   *
   *  As of release-0-5, this is hardcoded to 50,000.
   */
  static const int s_arraySize;//!

  

  ClassDef(GsimGenParticleData,1)
};

inline std::string GsimGenParticleData::getClassName() {
  return className;
}

inline int GsimGenParticleData::getArraySize() {
  return s_arraySize;
}

#endif // GsimGenParticleData_h

 

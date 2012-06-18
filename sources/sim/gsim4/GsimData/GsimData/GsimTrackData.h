/**
 *  @file
 *  @brief  GsimTrackData
 *  $Id: GsimTrackData.h,v 1.14 2006/12/09 21:33:44 nanjo Exp $ 
 *  $Log: GsimTrackData.h,v $
 *  Revision 1.14  2006/12/09 21:33:44  nanjo
 *  briefHistory is corrected.
 *
 *  Revision 1.13  2006/12/07 23:22:20  nanjo
 *  dump is added.
 *
 *  Revision 1.12  2006/12/07 08:51:10  nanjo
 *  Types of mother and mech are changed to Short_t.
 *
 *  Revision 1.11  2006/12/06 18:38:38  nanjo
 *  CVS variables.
 * 
 */
#ifndef GsimTrackData_h
#define GsimTrackData_h

//includes
#include "TObject.h"
#include "TVector3.h"
#include <list>
#include <string>

//forward declaration

/**
 *  @class GsimTrackData
 *  @brief This class stores track data for output to a ROOT file.
 *
 *  The track ID, parent track ID, parent brief track ID, particle ID (PDG),
 *  initial momentum, initial position, initial energy, initial creation process ID,
 *  brief detector ID history (maximum is 8)  are stored.
 */
class GsimTrackData : public TObject
{
 public:
  /**
   *  @function GsimTrackData
   *  @brief Constructor for GsimTrack Data.
   *
   *  Initializes the track to default values.
   */
  GsimTrackData();
  /**
   *  @function GsimTrackData
   *  @brief Constructor for GsimTrack Data.
   *  @param trackData Track data to which this track should be set to.
   *
   *  Initializes the track to the given values.
   */
  GsimTrackData(const GsimTrackData& trackData);
  /**
   *  @function ~GsimTrackData
   *  @brief Destructor for GsimTrackData.
   */
  virtual ~GsimTrackData();

  virtual void   Clear(Option_t* opt="");
  /**
   *  @brief The ID of the track.
   *  trackID
   */
  UShort_t         track;

  /**
   *  @brief The ID of the stored parent track ID.
   *  storedMotherTrackID
   */
  Short_t          mother;
  
  /**
   *  @brief The particle ID from the PDG listing.
   *  particleID;
   */
  Int_t         pid;
  /**
   *  @brief The initial momentum.
   *  initialMomentum;
   */
  TVector3    p;
  /**
   *  @brief The initial energy.
   *
   *  initialEnergy;
   */
  Float_t      ek; 

  /**
   *  @brief mass
   */
  Float_t      mass;

  /**
   *  @brief the initial time.
   */
  Float_t      time;
  /**
   *  @brief The initial position.
   *
   *  initialPosition;
   */
  TVector3    v;
  

  /**
   *  @brief The end momentum.
   *
   *  endMomentum.
   */
  TVector3    end_p;

  /**
   *  @brief The end kinetic energy.
   *
   *  endKineticEnergy;
   */
  Float_t     end_ek;

  
  /**
   *  @brief The end time.
   *
   *  endTime
   */
  Float_t     end_time;

  /**
   *  @brief The end position.
   *
   *  endPosition;
   */
  TVector3    end_v;
  
  /**
   *  @brief The ID of the initial creation process.
   *
   *  initialCreationProcessID
   */
  Short_t         mech;

  /**
   *  @brief The stable flag;
   *
   *  0:stable , 1:decay 
   */
  UShort_t         status;


  /**
   *  @brief the index of the array.
   */
  UShort_t         thisID;

  /**
   *  @brief The brief IDs of the detectors the track passed through.
   *
   *  The briefDetectorIDs are 0-30(0-9,a,b,..,u), while 31(v) is blank symbol.
   *  ULong64_t = unsigned long long=64bit=2^(5*12+4)
   *  is used as a buffer whose depth is 12
   *  For example, 012cdev means the track passed the detectors
   *  with brief IDs,  0(start)->1->2->c->d->e(stop). If the number of
   *  brief detectors reaches 12, no more brief detector ID is filled in
   *  the briefDetectorIDHistory.
   *
   */
  ULong64_t         history;
  
  //std::vector<int>  dalist; // List of index number of daughter particles

  /**
   *  @function operator=
   *  @brief Implements the store (=) operator.
   *  @param right Source track data.
   *
   *  All parameters of this GsimTrackData are set equal to those of the given GsimTrackData.
   */
  GsimTrackData& operator=(const  GsimTrackData& right);
  
  void dump(std::list<int>& state);
  
  static std::string convert5(unsigned long long targ);
  
  static int         ptod(std::string p);
  static std::string dtop(int d);
  
 protected:
  ClassDef(GsimTrackData,1)
};


#endif // GsimTrackData_h


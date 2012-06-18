/**
 *  @file
 *  @brief  GsimDetector
 *  @author Hajime Nanjo <nanjo@scphys.kyoto-u.ac.jp>
 *  @date   2005.10.5
 *  $Id: GsimDetectorHitData.h,v 1.16 2006/12/09 21:33:44 nanjo Exp $
 *  $Log: GsimDetectorHitData.h,v $
 *  Revision 1.16  2006/12/09 21:33:44  nanjo
 *  briefHistory is corrected.
 *
 *  Revision 1.15  2006/12/09 00:42:57  nanjo
 *  dump.
 *
 *  Revision 1.14  2006/11/30 20:06:22  nanjo
 *  Data are re-structured.
 *
 *  Revision 1.13  2006/08/24 22:19:01  nanjo
 *  Almost all data type is changed from double to Float_t, from int to UShort_t.
 *
 *  Revision 1.12  2006/08/11 08:48:52  nanjo
 *  Clear is added for some GsimDatas
 *
 *  Revision 1.11  2006/08/08 11:15:04  nanjo
 *  GsimTimeData is introduced and TRefArray is used.
 *
 *  Revision 1.10  2006/08/01 15:29:46  nanjo
 *  DetectorIDHistory is modified.
 *
 *  Revision 1.9  2006/06/22 12:08:32  nanjo
 *  briefDetectorIDHistory is added.
 *
 *  Revision 1.8  2006/06/21 11:53:38  nanjo
 *  GsimTrackData is changed. History of briefDetecotrID is added.
 *
 *  Revision 1.7  2006/06/21 04:03:23  jfiggins
 *  Added Javadoc-style Doxygen comments.
 *
 *  Revision 1.6  2006/06/14 03:34:17  nanjo
 *  Sort is enalbed (ordered by hitChannel, then by time.).
 *
 *  Revision 1.5  2006/06/04 10:14:02  nanjo
 *  mass is removed.
 *
 *  Revision 1.4  2006/06/04 10:08:34  nanjo
 *  mass is added.
 *
 *  Revision 1.3  2006/02/02 19:27:56  nanjo
 *  Add various KL correspondig to decay modes.
 *
 *  Revision 1.2  2006/01/31 02:59:16  nanjo
 *  TString is not used for Root I/O.
 *
 *  Revision 1.1  2006/01/26 06:11:19  nanjo
 *  Detector and data classes are added.
 *
 */
#ifndef GsimDetectorHitData_h
#define GsimDetectorHitData_h

//includes
#include "TObject.h"
#include "TVector3.h"

//forward declaration


/**
 *  @class GsimDetectorHitData
 *  @brief This class stores hit data for output to a ROOT file.
 *
 *  The hit ID, track ID, mother track ID, hit channel, time,
 *  energy, particle ID (PDG), hit position, hit kinetic energy,
 *  hit momentum, process ID, vertex position,
 *  vertex kinetic energy, and vertex momentum direction are stored.
 */
class GsimDetectorHitData : public TObject
{
 public:
  /**
   *  @function GsimDetectorHitData
   *  @brief Constructor for GsimDetectorHitData.
   */
  GsimDetectorHitData();
  /**
   *  @function ~GsimDetectorHitData
   *  @brief Destructor for GsimDetectorHitData.
   */
  virtual ~GsimDetectorHitData();

  /**
   *  @function IsSortable
   *  @brief Determines if the hits can be sorted.
   *  @return True, if the hits can be sorted.
   *
   *  As of release-0-5, this always returns true.
   */
  virtual Bool_t IsSortable() const;

  virtual void   Clear(Option_t* opt="");

  /**
   *  @function Compare
   *  @brief Compares an object with this.
   *  @param obj The object to compare this to.
   *  @return See comment below.
   *
   *  Returns -1, if this has less hit channels than the object or
   *  if the number of hit channels is the same, but this has
   *  less time than the object.
   *  Returns 1, if this has more hit channels than the object or
   *  if the number of hit channels is the same, but this has
   *  more time than the object.
   *  Returns 0, otherwise.
   */
  virtual Int_t  Compare(const TObject* obj) const;


  void dump();
    
  /**
   *  @brief The ID of the hit.hitID.
   */
  UShort_t         thisID;
  /**
   *  @brief The ID of the stored track.trackID.
   */
  UShort_t         track;

  /**
   *  @brief stop flag.
   */
  UShort_t         stop;
  
  /**
   *  @brief The hit channel. 
   */
  UShort_t         hitChannel;

  /**
   *  @brief The time. [ns]
   */
  Float_t      time;
  /**
   *  @brief The energy deposit. [MeV]
   */
  Float_t      edep;

  /**
   *  @brief The particle ID from the PDG listing.hitParticleID.
   */
  Int_t         pid;
  /**
   *  @brief The hit position.hitPosition.[mm]
   */
  TVector3    r;
  /**
   *  @brief The hit kinetic energy. hitKineticEnergy [MeV]
   */
  Float_t      ek;
  /**
   *  @brief The hit momentum.hitMomentum. [MeV]
   */
  TVector3    p;
  
  ClassDef(GsimDetectorHitData,1)
};


#endif // GsimDetectorHitData_h


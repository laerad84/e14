/**
 *  @file
 *  @brief  GsimHEPEvtInterface
 *  $Id: 
 *  $Log: 
 */

#ifndef GsimHEPEvtInterface_h
#define GsimHEPEvtInterface_h

//includes
#include "GsimKernel/GsimPrimaryGeneratorAction.h"
#include "G4PrimaryVertex.hh"
#include "G4ParticleDefinition.hh"
#include "G4HEPEvtParticle.hh"
#include "TFile.h"
#include <vector>
#include <fstream>
//forward declaration
class G4Event;
class GsimDetectorEventData;
class GsimHEPEvtInterfaceMessenger;


/**
 *  @class GsimHEPEvtInterface
 *  @brief This class provides GsimPrimaryGeneratorAction to generate beam particles.
 *  @see http://geant4.web.cern.ch/geant4/G4UsersDocuments/UsersGuides/ForApplicationDeveloper/html/Fundamentals/eventGenerator.html
 *  @see http://pcitapiww.cern.ch/asdcgi/geant4/SRM/G4GenDoc.exe.pl?flag=2&FileName=G4HEPEvtInterface.hh&FileDir=event/include
 *
 *  This class provides G4HEPEvtInterface, one of two G4VPrimaryGenerator concrete classes.
 *
 *   Format of input file
 *    a)
 *      ISTHEP,IDHEP,JDAHEP1,JDAHEP2,PHEP1,PHEP2,PHEP3,PHEP5;
 *      (status=1,pdg,1st daughter,last daughter,Px,Py,Pz,M)
 *      single vertex with m_vertexPosition,m_vertexTime is used.
 *    b)
 *      ISTHEP,IDHEP,JDAHEP1,JDAHEP2,PHEP1,PHEP2,PHEP3,PHEP5,VHEP1,VHEP2,VHEP3,VHEP4;
 *      (status,pdg,1st daughter,last daughter,Px,Py,Pz,M,   x,y,z,t)
 *                                             [GeV/c] [GeV/c^2] [mm]  [mm/c]
 *      meaning and unit
 *      ISTHEP: 1:active
 *      PHEP1
 *      PHEP4
 *      VHEP4
 *
 *     (x,y,z,t) is meaningful only for top particles,
 *      whereras that for daughters is dummy.
 *     Mutilple vertexes corresponding to top particles are used.
 *
 *    *)JDAHEP1,JDAHEP2 counts from 1, which is FORTRAN manner.
 */
class GsimHEPEvtInterface : public GsimPrimaryGeneratorAction
{
 public:
  
  /**
   *  @function GsimHEPEvtInterface
   *  @brief Constructor for GsimHEPEvtInterface
   */
  GsimHEPEvtInterface();

  /**
   *  @function GsimHEPEvtInterface
   *  @brief Constructor for GsimHEPEvtInterface
   */
  ~GsimHEPEvtInterface();

  /**
   *  @function setInputFileName
   *  @brief Sets the input filename.
   *  @param fileName The input filename.
   *  @return Returns true, if the file is available for reading.
   *
   *  If the input filename ends with "root", then the file will be read as a ROOT file.
   */
  bool setInputFileName(std::string fileName);

  /**
   *  @function setInputFileName
   *  @brief Sets the input filename.
   *  @param fileName The input filename.
   *  @param detectorName The name of the detector.
   *  @param runNo The run number.
   *  @param KLtype The k-long type.
   *  @return Returns true, if the file is available for reading and a valid detector name is given.
   *
   *  If the input filename ends with "root", then the file will be read as a ROOT file.
   */
  bool setInputEventDataFileName(std::string fileName,
				 std::string detectorName,
				 int runNo=0,
				 std::string KLtype="");

  /**
   *  @function gotoEventNumber
   *  @brief Sets the event number to the given value.
   *  @param eventNumber The new event number.
   */
  void gotoEventNumber(int eventNumber);

  /**
   *  @function setVertexPosition
   *  @brief Sets the vertex position to the given position.
   *  @param pos The new position.
   */
  inline void setVertexPosition(G4ThreeVector pos) {
    m_vertexPosition=pos;
  }
  
  /**
   *  @function setVertexTime
   *  @brief Sets the vertex time to the given time.
   *  @param tim The new time.
   */
  inline void setVertexTime(double tim) {
    m_vertexTime=tim;
  }
  
  /**
   *  @function convertToRootFile
   *  @brief Converts the input file to a ROOT format.
   *  @rootFileName The output filename.
   */
  void convertToRootFile(std::string rootFileName);

  /**
   *  @function setZeroPIDParticle
   *  @brief set PID=0 as some particle
   *  @pname geantino/chargedgeantino/opticalphoton
   */
  void setZeroPIDParticle(std::string pname);
  
 protected:

  /**
   *  @function processEvent
   *  @brief Processes an event.
   *  @param anEvent The event to process.
   */
  void processEvent(G4Event* anEvent);
  /**
   *  @function readOneAsciiEvent
   *  @brief Reads one event from the console.
   *  @return True, if the event was successfully read.
   */
  bool readOneAsciiEvent();
  /**
   *  @function readOneAsciiLine
   *  @brief Reads one line from the console.
   *  @return True, if the line was successfully read.
   */
  bool readOneAsciiLine();
  /**
   *  @function readOneRootEvent
   *  @brief Reads one event from the ROOT file.
   *  @return True, if the event was successfully read.
   */
  bool readOneRootEvent();
  /**
   *  @function readOneRootLine
   *  @brief Reads one line.
   *  @param iLine The line to read.
   *  @return True, if the line was successfully read.
   */
  bool readOneRootLine(Long64_t iLine);
  
  /**
   *  @function readOneDetectorHitEvent
   *  @brief Reads one event from the input file.
   *  @return True, if the event was successfully read.
   */
  bool readOneDetectorHitEvent();
  /**
   *  @function readOneDetectorHitLine
   *  @brief Reads one line.
   *  @param iLine The line to read.
   *  @return True, if the line was successfully read.
   */
  bool readOneDetectorHitLine(Long64_t iLine);

  /**
   *  @function abort
   *  @brief Closes the input files, ends the event, and ends the run.
   */
  void abort();
  /**
   *  @function head
   *  @brief Removes whitespace from the beginning of a string.
   *  @param The string to modify.
   */
  void head(std::string& lin);
  /**
   *  @function tail
   *  @brief Removes whitespace from the end of a string.
   *  @param The string to modify.
   */
  void tail(std::string& lin);

  /**
   *  @function shoot
   *  @brief Shoots a particle by generating an initial particle vertex.
   *  @param anEvent The event that receives the particle.
   */
  void shoot(G4Event* anEvent);

  
  
  /**
   *  @brief The vertex position.
   */
  G4ThreeVector    m_vertexPosition;
  /**
   *  @brief The vertex time.
   */
  double           m_vertexTime;
  
  /**
   *  @brief The input filename.
   */
  std::string        m_fileName;
  
  /**
   *  @brief Process mode.
   *
   *  0: not opened
   *  1: ascii text
   *  2: root file
   *  3: DetectorEventData
   */
  int m_processMode;

  /**
   *  @brief The file format.
   *
   *  0: not resolved
   *  1: standard
   *  2: extended
   */
  int m_fileFormat;
  

  /**
   *  @brief The input file stream.
   */
  std::ifstream m_inputFile;
  /**
   *  @brief The ROOT file.
   */
  TFile*        m_inputRoot;
  /**
   *  @brief The event counter.
   */
  Long64_t      m_eventCounter;
  /**
   *  @brief Vector of HEP particles.
   */
  std::vector<G4HEPEvtParticle*> m_HPlist;
  /**
   *  @brief Vector of primary vertices.
   */
  std::vector<G4PrimaryVertex*>  m_PVlist;

  /**
   *  @brief The detector name.
   */
  std::string m_detectorName;
  /**
   *  @brief The run number.
   */
  int         m_runNo;
  /**
   *  @brief The k-long type.
   */
  std::string m_KLtype;
  /**
   *  @brief Event data.
   */
  GsimDetectorEventData* m_eventData;
  
  /**
   *  @brief Pointer to the messenger.
   */
  GsimHEPEvtInterfaceMessenger* m_hepEvtInterfaceMessenger;

  
  /**
   *  @brief pointer for zeroPIDParticle
   */
  G4ParticleDefinition* m_zeroPIDParticle;
};

#endif //GsimHEPEvtInterface_h

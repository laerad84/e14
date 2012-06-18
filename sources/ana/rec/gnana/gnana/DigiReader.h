/**
 *  @file   DigiReader.h
 *  @brief  Read GsimDigiData
 * This class provides methods to read GsimDigiData from gsim4 output file.
 *
 *  @author Kazufumi Sato <sato@champ.hep.sci.osaka-u.ac.jp>
 *  @date   2011.9.23
 *  $Id: DigiReader.h,v 1.0 2011/09/23 12:38 sato Exp $
 *  $Log: DigiReader.h,v $
 */

#ifndef DigiReader_h
#define DigiReader_h

#include "GsimData/GsimDetectorEventData.h"
#include "GsimData/GsimGenParticleData.h"
#include <TChain.h>
#include <string>
#include <iostream>


class DigiReader
{
 public:
  enum{ CC01=0, CC02, CC03, CC04, CC05, CC06, 
        CBAR, FBAR, CSI,  BHPV, CV, BCV, BHCV };

  DigiReader(TTree *tr);
  ~DigiReader();
  
  int    addDetector(std::string detName);

  int    getDetID(std::string detName) const;
  TClonesArray*   getDigi(int const detID);
  void   getDigi(int const detID,int &nDigi,int *id,double *E,double *time) const;
  void   getCsiDigi(int &nDigi,int *id,double *E,double *time) const;

  int    getDigiSize(int const detID) const; 
  int    getDigiId(int const detID,int const i) const;
  double getDigiEne(int const detID,int const i) const;
  double getDigiTime(int const detID,int const i) const;
  double getTotalEnergy(int const detID) const;
  
  int    getCsiDigiSize() const;
  int    getCsiDigiId(int const i) const;
  double getCsiDigiEne(int const i) const;
  double getCsiDigiTime(int const i) const;
  double getCsiTotalEnergy() const;
  
  TClonesArray*   getHits(int const detID);
  TClonesArray*   getTrack();
  /*
  void setBranchStatus(int detID,bool stat,std::string bname="");
  void setGenParticleBranchStatus(bool stat,std::string bname="");
  void setCSIBranchStatus(bool stat,std::string bname="");
  void setVetoBranchStatus(bool stat,std::string bname="");
  void setCC01BranchStatus(bool stat,std::string bname="");
  void setCC02BranchStatus(bool stat,std::string bname="");
  void setCC03BranchStatus(bool stat,std::string bname="");
  void setCC04BranchStatus(bool stat,std::string bname="");
  void setCC05BranchStatus(bool stat,std::string bname="");
  void setCC06BranchStatus(bool stat,std::string bname="");
  void setFBARBranchStatus(bool stat,std::string bname="");
  void setCBARBranchStatus(bool stat,std::string bname="");
  void setCVBranchStatus(bool stat,std::string bname="");
  void setBCVBranchStatus(bool stat,std::string bname="");
  void setBHCVBranchStatus(bool stat,std::string bname="");
  void setBHPVBranchStatus(bool stat,std::string bname="");
  */
  static int const s_arrSize = 5000;
  static int const s_maxDet = 20;

 private:
  TTree* m_tr;
  std::string m_detName[s_maxDet];
  std::string m_genParName;
  GsimDetectorEventData* m_det[s_maxDet];
  GsimGenParticleData* m_genPar;

  // Forbid copy 
  DigiReader(const DigiReader&);
  DigiReader& operator=(const DigiReader&);
};

#endif //DigiReader_h

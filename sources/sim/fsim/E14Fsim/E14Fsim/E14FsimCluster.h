#ifndef E14FsimCluster_h
#define E14FsimCluster_h

#include "TVector3.h"

class E14FsimMcGamma;
//
class E14FsimCluster {
public:
  E14FsimCluster();
  ~E14FsimCluster();

  void addMcGamma(E14FsimMcGamma* mcGamma);
  void smear();
  static void setSmearMode(int imode);
  
  int           m_nMcGamma;
  int           m_mcGammaID[5];//[m_nMcGamma]
  double        m_mcGammaE[5];//[m_nMcGamma]
  int           m_mcParentID[5];//[m_nMcGamm
  double        m_mcGammaT[5];//[m_nMcGamma]a]
  TVector3      m_mcGammaPos[5];//[m_nMcGamma]a]
  TVector3      m_mcGammaMome[5];//[m_nMcGamma]a]

  
  double        m_mcGammaXYDistance;
  double        m_mcFusionProb;
  
  int            m_clusterID;
  
  TVector3       m_pos;
  TVector3       m_mome;
  double         m_energy;
  double         m_time;
  
  //temporary for study...
  double         m_angleXZ;
  double         m_angleYZ;

  double         m_sigmaE;
  double         m_sigmaX;
  double         m_sigmaY;

  /// smearing mode
  /** 
   *   - 0 no smearing
   *   - 1 only smear energy
   *   - 2 only smear position
   *   - 3 smear energy and position 
   */
  static int     s_smearMode;
};

//
#endif // E14FsimCluster_h


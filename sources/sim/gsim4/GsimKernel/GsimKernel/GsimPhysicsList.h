/**
 *  @file
 *  @brief  GsimPhysicsList
 *  @author Hajime Nanjo <nanjo@scphys.kyoto-u.ac.jp>
 *  @date   2005.10.5
 *  $Id: GsimPhysicsList.h,v 1.3 2006/01/30 08:40:41 nanjo Exp $
 *  $Log: GsimPhysicsList.h,v $
 *  Revision 1.3  2006/01/30 08:40:41  nanjo
 *  Process name created is stored in persistencyManager.
 *
 *  Revision 1.2  2006/01/26 04:34:22  nanjo
 *  Factory pattern and template method on factory and messenger class is intorduced .
 *
 */

#ifndef GsimPhysicsList_h
#define GsimPhysicsList_h

#include "G4VUserPhysicsList.hh"

/**
 *  @class GsimPhysicsList
 *  @brief Particle construction with empty physics.
 *
 *  This class provides only particle construction.
 */


class GsimPhysicsList: public G4VUserPhysicsList
{
public:
  GsimPhysicsList();
  virtual ~GsimPhysicsList();

  inline void addCerenkov();
  inline void withUserLimits(bool withUL);

  inline bool isCerenkovAdded() const;
  inline bool isUserLimitsOn() const;
  
protected:
  /// Construct particle and physics
  virtual void ConstructParticle();
  virtual void ConstructProcess();
  
  /// 
  virtual void SetCuts();

  void DumpProcesName();

  bool m_withUserLimits;
  bool m_withCerenkov;
  
protected:
  /// these methods Construct particles.
  void  ConstructAllBosons();
  void  ConstructAllLeptons();
  void  ConstructAllMesons();
  void  ConstructAllBaryons();
  void  ConstructAllIons();
  void  ConstructAllShortLiveds();

};

inline void GsimPhysicsList::addCerenkov() { m_withCerenkov=true; } 
inline void GsimPhysicsList::withUserLimits(bool withUL) { m_withUserLimits=withUL; }
inline bool GsimPhysicsList::isCerenkovAdded() const { return m_withCerenkov; }
inline bool GsimPhysicsList::isUserLimitsOn() const { return m_withUserLimits; }

#endif // GsimPhysicsList_h

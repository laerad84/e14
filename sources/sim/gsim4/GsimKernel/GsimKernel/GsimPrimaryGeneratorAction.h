/**
 *  @file
 *  @brief  GsimPrimaryGeneratorAction
 *  @author Hajime Nanjo <nanjo@scphys.kyoto-u.ac.jp>
 *  @date   2005.10.5
 *  $Id: GsimPrimaryGeneratorAction.h,v 1.5 2006/11/30 20:07:11 nanjo Exp $
 *  $Log: GsimPrimaryGeneratorAction.h,v $
 *  Revision 1.5  2006/11/30 20:07:11  nanjo
 *  Data are re-structured.
 *
 *  Revision 1.4  2006/08/01 05:27:55  nanjo
 *  GsimSpectrum is added. Debug print is updated. With/without Digi is implemented.
 *
 *  Revision 1.3  2006/01/27 00:06:26  nanjo
 *  Seeds are saved in GsimPersistencyManager
 *
 *  Revision 1.2  2006/01/26 04:34:22  nanjo
 *  Factory pattern and template method on factory and messenger class is intorduced .
 *
 */

#ifndef GsimPrimaryGeneratorAction_h
#define GsimPrimaryGeneratorAction_h

//includes
#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include <string>
#include <vector>

//forward declaration
class G4Event;
class GsimPrimaryGeneratorActionMessenger;
class GsimSpectrum;
class GsimRandData;

/**
 *  @class GsimPrimaryGeneratorAction
 *  @brief PrimaryGeneratorAction.
 *
 *  This class provides PrimaryGeneratorAction, which is
 *  inherited from G4VUserPrimaryGeneratorAction.
 *  This class can keep daughter  GsimPrimaryGeneratorActions,
 *  which enables to reuse already coded
 *  PrimaryGeneratorAction. A branch value should be assigned
 *  to the corresponding daughter GsimPrimaryGeneratorAction.
 *  It controles branching of daughters under the mother.
 *  Usually only one of the daughters is shot. For the exception,
 *  if the branch value exceeds 1, it is aloways shot,
 *  which can be used for overlaying background.
 *  This object is created using Factory class.
 *  User should inherit this class to make his own
 *  PrimaryGeneratorAction class, where he should code
 *  constructor, shoot, and, defaultGunProperty.
 */
 
class GsimPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
 public:
  
  /// Constructor.
  /**
   *  User should define his own constructor,
   *  where he may construct some daughter
   *  PrimaryGeneratorActions.
   *  The branch should be properly set.
   */
  GsimPrimaryGeneratorAction();

  /// Destructor.
  ~GsimPrimaryGeneratorAction();

  /// GeneratePrimaries.
  /**
   *  This is a pure virtual method declared
   *  in G4VUserPrimaryGeneratorAction.
   */
  void GeneratePrimaries(G4Event* anEvent);

  void registerSpectrum(GsimSpectrum* spectrum);

 protected:
  
  /// Really shoot this gun.
  /**
   *  User should write his own gun
   *  using this method.
   */
  virtual void shoot(G4Event* anEvent)=0;

  GsimRandData* m_randData;
  GsimSpectrum* m_spectrum;

  unsigned long m_MTwistEngineID;
};

#endif //GsimPrimaryGeneratorAction_h

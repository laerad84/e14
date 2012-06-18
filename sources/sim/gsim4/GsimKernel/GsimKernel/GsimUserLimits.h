/**
 *  @file
 *  @brief  GsimUserLimits
 *  $Id: GsimUserLimits.h,v 1.2 2006/12/06 18:44:00 nanjo Exp $
 *  $Log: GsimUserLimits.h,v $
 *  Revision 1.2  2006/12/06 18:44:00  nanjo
 *  Midas I/O is added and Root I/O is separated. etc.
 *
 */
#ifndef GsimUserLimits_h
#define GsimUserLimits_h

#include "G4VPhysicsConstructor.hh"
#include "globals.hh"

class GsimUserLimits : public G4VPhysicsConstructor
{
public:
  GsimUserLimits(const G4String& name = "GsimUserLimits");
  virtual ~GsimUserLimits();

  void ConstructParticle();
  void ConstructProcess();

private:

  
};

#endif






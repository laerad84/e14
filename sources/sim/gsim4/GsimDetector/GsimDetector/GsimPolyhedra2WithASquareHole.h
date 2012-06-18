/**
 *  @file
 *  @brief  GsimPolyhedra2WithASquareHole
 *  $Id: GsimPolyhedra2WithASquareHole.h
 *  $Log: 
 */
#ifndef GsimPolyhedra2WithASquareHole_h
#define GsimPolyhedra2WithASquareHole_h

//includes
#include <string>
#include "GsimKernel/GsimDetector.h"

//forward declaration
class G4Trd;
class G4Trap;
class G4Cons;
class G4Orb;
class G4Sphere;
class G4Torus;
class G4Para;
class G4Hype;
class G4Tubs;
class G4Polycone;
class G4Polyhedra;
class G4Box;


class GsimPolyhedra2WithASquareHole : public GsimDetector
{
 public:
  GsimPolyhedra2WithASquareHole(std::string name,
		 GsimDetector* motherDetector,
		 G4ThreeVector transV,
		 G4ThreeVector rotV,
		 int userFlag=0);
  
  virtual ~GsimPolyhedra2WithASquareHole();

 protected:
  virtual void constructPhysiDetector();
  virtual void updateParametersEtc();
  GsimPolyhedra2WithASquareHole();


};


#endif // GsimPolyhedra2_h

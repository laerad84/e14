/**
 *  @file
 *  @brief  GsimSurface
 *  $Id: $
 *  $Log:$
 */
#ifndef GsimSurface_h
#define GsimSurface_h

//includes
#include "globals.hh"
#include "G4OpticalSurface.hh"
#include "G4SurfaceProperty.hh"

#include <string>
#include <vector>

//forward declaration
class GsimSurfaceMessenger;
class GsimDetector;
class GsimSurfaceMessenger;
class G4VPhysicalVolume;
/**
 *  @class GsimSurface
 *  @brief GsimSurface is the superclass of the Gsim surface.
 */


class GsimSurface
{
 public:

  /**
   *  @function GsimSurface
   *  @brief Constructor for GsimSurface
   *  @param name The name of the surface
   *  @param vol1Detector A pointer to the boundary volume 1.
   *  @param vol2Detector A pointer to the boundary volume 2.
   */
  GsimSurface(std::string name,
	      GsimDetector* vol1Detector,
	      GsimDetector* vol2Detector);

  /**
   *  @function ~GsimSurface
   *  @brief Destructor for GsimSurface
   */
  virtual ~GsimSurface();

  /**
   *  @function setSurfaceProperty
   *  @brief Set SurfaceProperty
   *  @param type G4SurfaceType(dielectric_metal,dielectric_dielectric,firsov,x_ray)
   *  @param finish G4OpticalSurfaceFinish(polished,polishedfrontpainted,polishedbackpainted,ground,groundfrontpainted,groundbackpainted)
   *  @param model G4OpticalSurfaceModel(glisur:original GEANT3,unified)
   *  @param param (polish for glisur,alpha for unified)
   */
  void setSurfaceProperty(G4SurfaceType type,
			  G4OpticalSurfaceFinish finish,
			  G4OpticalSurfaceModel model,
			  double param);
  
  void setRefractiveIndex(std::vector<double> photonWaveLengthVector,
			  std::vector<double> refractiveIndexVector
			  );
  void setReflectiveity(std::vector<double> photonWaveLengthVector,
			std::vector<double> reflectivityVector
			);

  void setEfficiency(std::vector<double> photonWaveLengthVector,
		     std::vector<double> efficiencyVector
		     );

  void setProperty(std::string type,
		   std::vector<double> photonWaveLengthVector,
		   std::vector<double> propertyVector
		   );
  void dump();
  std::string getName();
 protected:
  std::string       m_name;
  G4OpticalSurface* m_opticalSurface;
  G4VPhysicalVolume* m_vol1;
  G4VPhysicalVolume* m_vol2;
  GsimSurfaceMessenger* m_messenger;
};

inline std::string GsimSurface::getName()
{
  return m_name;
}

#endif // GsimSurface_h

/**
 *  @file
 *  @brief  GsimMaterialManager
 *  $Id: GsimMaterialManager.h,v 1.2 2006/12/06 18:44:00 nanjo Exp $
 *  $Log: GsimMaterialManager.h,v $
 *  Revision 1.2  2006/12/06 18:44:00  nanjo
 *  Midas I/O is added and Root I/O is separated. etc.
 *
 */
#ifndef GsimMaterialManager_h
#define GsimMaterialManager_h

//includes
#include <string>
#include <vector>

//forward declaration
class GsimMaterialManagerMessenger;

/**
 *  @class GsimMaterialManager
 *  @brief Track information.
 *
 *  This class provides ...
 */

class GsimMaterialManager 
{
public:
  GsimMaterialManager();
  virtual ~GsimMaterialManager();

  /// Declare Materials to be used.
  /**
   *  Some physics list( neutron_HP ) require
   *  element lists. Elements to be used should be
   *  declared prior to physics list construction.
   */
  void useNistMaterial(std::string matname);

  /// Define Materials.
  /**
   *  Don't define a material which G4NistMangaer can manage.
   *  You should define a material if its optical properties are needed.
   *  At that time, use G4NistMangaer to get G4Element.
   */
  void defineMaterials();
  
  void mixElement(std::string name,
		  double density,
		  double pressure,
		  double temperature,
		  std::vector<std::string> elementVec,
		  std::vector<double> weightVec);

  void mixElement(std::string name,
		  double density,
		  double pressure,
		  double temperature,
		  std::vector<std::string> elementVec,
		  std::vector<int> numVec);


  void setProperty(std::string matName,std::string type,
		   std::vector<double> photonWaveLengthVector,
		   std::vector<double> propertyVector
		   );

  void setConstProperty(std::string matName,std::string type,
			double value
			);

  void dumpProperty(std::string matName);

  void listMaterial();
  

 private:
  GsimMaterialManagerMessenger* m_messenger;

};

#endif // GsimMaterialManager_h


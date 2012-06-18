/**
 *  @file
 *  @brief  GsimDetectorContainer
 *  @author Hajime Nanjo <nanjo@scphys.kyoto-u.ac.jp>
 *  @date   2005.10.5
 *  $Id: GsimDetectorContainer.h,v 1.1 2006/01/26 04:53:30 nanjo Exp $
 *  $Log: GsimDetectorContainer.h,v $
 *  Revision 1.1  2006/01/26 04:53:30  nanjo
 *  Detector and persistency classes are added.
 *
 */
#ifndef GsimDetectorContainer_h
#define GsimDetectorContainer_h

//includes
#include <string>
#include <map>

//forward declaration
class GsimDetector;

/**
 *  @class GsimDetectorContainer
 *  @brief DetectorContainer.
 *
 *  This class provides detector conainer
 *  which is map of detector name and detector pointer.
 */

class GsimDetectorContainer : public std::map<std::string,GsimDetector*> 
{
 public:
  /// Constructor.
  GsimDetectorContainer();

  /// Destructor.
  ~GsimDetectorContainer();

  /// Overloaded method of insert. 
  bool insert(GsimDetector* detector);
};

#endif // GsimDetectorContainer_h

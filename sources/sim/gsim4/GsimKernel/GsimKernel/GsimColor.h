/**
 *  @file
 *  @brief  GsimColor
 *  @author Hajime Nanjo <nanjo@scphys.kyoto-u.ac.jp>
 *  @date   2005.10.5
 *  $Id: GsimColor.h,v 1.2 2006/06/09 17:06:25 jfiggins Exp $
 *  $Log: GsimColor.h,v $
 *  Revision 1.2  2006/06/09 17:06:25  jfiggins
 *  Modified comments. Added two new grays (25% and 75%).
 *
 *  Revision 1.1  2006/01/26 04:53:30  nanjo
 *  Detector and persistency classes are added.
 *
 */
#ifndef GsimColor_h
#define GsimColor_h

//includes
#include "G4Color.hh"

/**
 *  @namespace GsimColor
 *  @brief Defines the colors for visualization.
 *  
 */
namespace GsimColor
{
  const G4Color  white   (1.0, 1.0, 1.0) ;
  const G4Color  gray25  (0.25, 0.25, 0.25) ;
  const G4Color  gray50  (0.5, 0.5, 0.5) ;
  const G4Color  gray70  (0.7, 0.7, 0.7);
  const G4Color  gray75  (0.75, 0.75, 0.75) ;
  const G4Color  black   (0.0, 0.0, 0.0) ;
  const G4Color  red     (1.0, 0.0, 0.0) ;
  const G4Color  green   (0.0, 1.0, 0.0) ;
  const G4Color  blue    (0.0, 0.0, 1.0) ;
  const G4Color  cyan    (0.0, 1.0, 1.0) ;
  const G4Color  magenta (1.0, 0.0, 1.0) ;
  const G4Color  yellow  (1.0, 1.0, 0.0) ;
  const G4Color  purple4 (0.333,0.102,0.545);
  const G4Color  deeppink(1.,  0.78,0.58);
  const G4Color  lightskyblue(0.53,0.81,0.98);
  const G4Color  lightyellow(1.,1.,0.6);
  const G4Color  orange(1.,0.647,0.);
  const G4Color  violet(0.933,0.51,0.9333);
  const G4Color  purple(0.627,0.125,0.941);

}

#endif // GsimColor_h

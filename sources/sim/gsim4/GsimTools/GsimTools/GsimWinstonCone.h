/**
 *  @file
 *  @brief  GsimWinstonCone
 *  $Id: $
 *  $Log:$
 */

#ifndef GsimWinstonCone_h
#define GsimWinstonCone_h




class TH2D;
class TGraph;

class GsimWinstonCone
{
 public:
  GsimWinstonCone(double tin,double tout);
  ~GsimWinstonCone();
  bool trace(double* r, double* v);

  double getHight();
  int    getErrorStatus();
  int    getNReflections();
  double getPathLength();
  void setMaxReflections(int n);

  void drawWinstonCone();
  void drawWinstonConeWithParameters();
  void drawTrace();
  
 private:
  double m_TIN;
  double m_TOUT;
  double m_Length;

  //
  //   <----------> TIN
  //        | z
  //        |
  //  |     |     |
  //  |     |     |
  //   |    |    | 
  //   |    |    |
  //    |   |   |
  // ____|__|__|_____________> y
  //     <----> TOUT
  // The high, m_Length can be calculated with m_TIN,m_TUOT
  //


  
  
  //Calculate max path length from x[3] to v[3] (normalized)
  double getMaxPath(double* r, double* v);
  
  static double cwicof(double s, void* par);

  static double wcp(double z,double a,double th);
  static double wcm(double z,double a,double th);
  
  double m_pathLength;
  int    m_nReflections;
  int    m_maxReflections;

  double m_maxSinTheta;
  double m_maxTheta;
  int    m_errorStatus;

  double *xPoint;
  double *yPoint;
  double *zPoint;

  TH2D* m_frame;
  TGraph* m_grX;
  TGraph* m_grY;
  int     m_nPoint;
};


inline double GsimWinstonCone::getHight() { return m_Length; }
inline int    GsimWinstonCone::getErrorStatus() { return m_errorStatus; }
inline int    GsimWinstonCone::getNReflections() { return m_nReflections; }
inline double GsimWinstonCone::getPathLength() { return m_pathLength; }

#endif //GsimWinstonCone_h

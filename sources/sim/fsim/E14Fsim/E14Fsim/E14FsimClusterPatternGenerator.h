/**
 *  @file
 *  @brief  E14FsimClusterPatternGenerator
 *  $Id: $
 *  $Log: $
 *
 */
#ifndef E14FsimClusterPatternGenerator_h
#define E14FsimClusterPatternGenerator_h

#include <list>
#include <vector>
#include <map>

class E14FsimClusterPatternGenerator
{
 public:
  E14FsimClusterPatternGenerator();
  virtual ~E14FsimClusterPatternGenerator();

  void makeClusterPatternList(int nGamma);
  void dumpClusterPattern(int nGamma);
  void makePool(int nCluster=-1);
  std::list< std::list<int> > getClusterPatternList(int nGamma,int nCluster=-1);
  
 private:
  void makeZeroOnePattern(int n,std::list<int> pattern1,
			  std::list< std::list<int> >& patternList);
  
  
  void makeHitPattern(int nGamma);
		      
  
  void makePair(int nHitGamma);

  void makeFusionPairPattern(int nHitGamma);
	
  

  std::list< std::list<int> >       m_hitPatternList;
  std::vector< std::pair<int,int> > m_pairVec;
  std::list< std::list<int> >       m_fusionPairPatternList;
  std::list< std::list<int> >       m_clusterPatternList;
  
  std::map<int, std::list< std::list<int> > > m_clusterPatternListPoolbyNGamma;
  

};

#endif

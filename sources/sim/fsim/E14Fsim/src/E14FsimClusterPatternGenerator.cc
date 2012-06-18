#include "E14Fsim/E14FsimClusterPatternGenerator.h"
#include <iostream>

E14FsimClusterPatternGenerator::E14FsimClusterPatternGenerator()
{
  m_hitPatternList.clear();
  m_pairVec.clear();
  m_fusionPairPatternList.clear();
  m_clusterPatternList.clear();
  m_clusterPatternListPoolbyNGamma.clear();
}


E14FsimClusterPatternGenerator::~E14FsimClusterPatternGenerator()
{

}


void E14FsimClusterPatternGenerator::
makeZeroOnePattern(int n,std::list<int> pattern1,
		   std::list< std::list<int> >& patternList)
{
  if(n==0) {
    if(pattern1.size()>0)
      patternList.push_back(pattern1);
    return;
  }
  
  std::list<int> pattern0=pattern1;
  pattern1.push_back(1);
  makeZeroOnePattern(n-1,pattern1,patternList);
  pattern0.push_back(0);
  makeZeroOnePattern(n-1,pattern0,patternList);
}

void E14FsimClusterPatternGenerator::
makeHitPattern(int nGamma)
{
  m_hitPatternList.clear();
  std::list<int> pattern1;
  makeZeroOnePattern(nGamma,pattern1,
		     m_hitPatternList);
  
}


void E14FsimClusterPatternGenerator::
makePair(int nHitGamma)
{
  m_pairVec.clear();
  for(int i=0;i<nHitGamma;i++) {
    for(int j=i+1;j<nHitGamma;j++) {
      m_pairVec.push_back(std::make_pair(i,j));
    }
  }
}

void E14FsimClusterPatternGenerator::
makeFusionPairPattern(int nHitGamma)
{
  m_fusionPairPatternList.clear();
  makePair(nHitGamma);

  int nPair=m_pairVec.size();
  
  std::list<int> pairPat1;
  std::list< std::list<int> > tmpPairPatList;
  makeZeroOnePattern(nPair,pairPat1,tmpPairPatList);

  int* seat = new int[nHitGamma];
  for( std::list< std::list<int> >::iterator itp
	 =tmpPairPatList.begin();
       itp!=tmpPairPatList.end();itp++) {
    bool isTrippleOrMoreFusion=false;
    for(int k=0;k<nHitGamma;k++) {
      seat[k]=0;
    }
    int cnt=0;
    for(std::list<int>::iterator ittp=(*itp).begin();
	ittp!=(*itp).end();ittp++,cnt++) {
      if((*ittp)==1) {
	int used[2]={m_pairVec[cnt].first,m_pairVec[cnt].second};
	for(int k=0;k<2;k++) {
	  int is=used[k];
	  seat[is]+=1;
	  if(seat[is]>1) {
	    isTrippleOrMoreFusion=true;
	  }
	}
      }
    }
    if(!isTrippleOrMoreFusion) {
      m_fusionPairPatternList.push_back(*itp);
    }
  }
  delete [] seat;
}


void E14FsimClusterPatternGenerator::
makeClusterPatternList(int nGamma)
{
  m_clusterPatternList.clear();
  makeHitPattern(nGamma);
  int* seat  = new  int[nGamma];
  
  for( std::list< std::list<int> >::iterator it=m_hitPatternList.begin();
       it!=m_hitPatternList.end();it++) {

    std::list<int> gammaHitPattern=(*it);
    int cntGamma=0;
    int cntHit=0;
    std::map<int,int> hitToGammaMap;
    for(std::list<int>::iterator itt=gammaHitPattern.begin();
	itt!=gammaHitPattern.end();itt++,cntGamma++) {
      if( (*itt)==1 ) {
	hitToGammaMap.insert( std::make_pair(cntHit,cntGamma) );
	cntHit++;
      }
    }

    makeFusionPairPattern(cntHit);
    
    if(cntHit==0 || cntHit==1) {
      std::list<int> tmplis;
      m_fusionPairPatternList.push_back(tmplis);
    }

    for(std::list< std::list<int> >::iterator itf=m_fusionPairPatternList.begin();
	itf!=m_fusionPairPatternList.end();itf++) {
      
      int cntCluster=0;
      for(int k=0;k<nGamma;k++) {
	seat[k]=-1;
      }
      
      
      int cnt=0;
      for(std::list<int>::iterator itt=(*itf).begin();
	  itt!=(*itf).end();itt++,cnt++) {
	if( (*itt) == 1) {
	  int iHit[2]={m_pairVec[cnt].first,m_pairVec[cnt].second};
	  for(int j=0;j<2;j++) {
	    int iGamma=hitToGammaMap[iHit[j]];
	    seat[ iGamma ] = cntCluster;
	  }
	  cntCluster++;
	}
      }
      
      int is=0;
      for(std::list<int>::iterator itg=gammaHitPattern.begin();
	  itg!=gammaHitPattern.end();itg++,is++) {
	if( seat[is]==-1 && (*itg)==1) {
	  seat[is]=cntCluster;
	  cntCluster++;
	}
      }
      
      std::list<int> clusterPattern;
      for(int k=0;k<nGamma;k++) {
	clusterPattern.push_back(seat[k]);
      }
      m_clusterPatternList.push_back(clusterPattern);
    }
  }
  delete [] seat;
}

void E14FsimClusterPatternGenerator::
dumpClusterPattern(int nGamma)
{
  makeClusterPatternList(nGamma);
  for(std::list< std::list<int> >::iterator it=m_clusterPatternList.begin();
      it!=m_clusterPatternList.end();it++) {
    for(std::list<int>::iterator itt=(*it).begin();
	itt!=(*it).end();itt++) {
      if( (*itt)==-1) {
	std::cout << "x";
      } else {
	std::cout << (*itt);
      }
    }
    std::cout << std::endl;
  }

}

void E14FsimClusterPatternGenerator::
makePool(int nCluster)
{
  m_clusterPatternListPoolbyNGamma.clear();
  for(int nGamma=0;nGamma<=6;nGamma++) {
    makeClusterPatternList(nGamma);
    if(nCluster==-1) {
      m_clusterPatternListPoolbyNGamma.insert(std::make_pair(nGamma,
							     m_clusterPatternList)
					      );
    } else {
      std::list< std::list<int> > tmpList;
      for( std::list< std::list<int> >::iterator itp=m_clusterPatternList.begin();
	   itp!=m_clusterPatternList.end();itp++) {
	int maxid=-1;
	for(std::list<int>::iterator it=(*itp).begin();
	    it!=(*itp).end();it++) {
	  if((*it)==-1) {
	    //ineefi;
	  } else {
	    //cluster No. (*it);
	    if( (*it)>maxid ) maxid= (*it);
	  }
	}
	int nc=maxid+1;
	if(nc==nCluster) {
	  tmpList.push_back( (*itp) );
	}
      }
      m_clusterPatternListPoolbyNGamma.insert(std::make_pair(nGamma,tmpList));
    }
  }
}


std::list< std::list<int> > E14FsimClusterPatternGenerator::
getClusterPatternList(int nGamma, int nCluster)
{

  if(m_clusterPatternListPoolbyNGamma.size()==0) {
    makePool(nCluster);
  }

  if(nGamma>=0 && nGamma<=6) {
    return m_clusterPatternListPoolbyNGamma[nGamma];
  } else {
    makeClusterPatternList(nGamma);
    return m_clusterPatternList;
  }
}

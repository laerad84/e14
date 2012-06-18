/**
 *  @file
 *  @brief  GsimE14OEV
 *  $Id: GsimE14OEV.cc,v 1.4 2006/12/06 19:04:45 nanjo Exp $ 
 *  $Log: GsimE14OEV.cc,v $
 *  Revision 1.4  2006/12/06 19:04:45  nanjo
 *  CVS variables.
 *
 *
 */
#include "GsimE14Detector/GsimE14OEV.h"
#include "GsimE14Detector/GsimE14UserGeom.h"
#include "GsimPersistency/GsimMessage.h"
#include "GsimDetector/GsimBox.h"
#include "GsimDetector/GsimTrap.h"
#include "GsimDetector/GsimTube.h"
#include "GsimDetector/GsimBox.h"
#include "GsimDetector/GsimBoxWithoutABox.h"
#include "GsimKernel/GsimSensitiveDetector.h"
#include "GsimKernel/GsimUtil.h"


using namespace E14;

GsimE14OEV::GsimE14OEV(std::string name,
		       GsimDetector* motherDetector,
		       G4ThreeVector transV,G4ThreeVector rotV,
		       int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{
  
  m_className = "GsimE14OEV";
  m_model=0;
  
  
  char nam[100];
  int det_id=0;
  const int nOuterTypes = 9; // Module type #0-#8
  const int nk = 8; 
  int index;
  
  // NOTE
  // OEV (Outer Edge Veto) has 9 types of module in shape.
  // From type#0 to type#7 is a trap. shape.

  // index = 0(BL): SUS frame, normal image
  // index = 1(BR): SUS frame, mirror image
  // index = 2(TL): Al frame,  normal image
  // index = 3(TR): Al frame,  mirror image
  // index = 4(RU): Al frame,  normal image
  // index = 5(LU): Al frame,  mirror image
  // index = 6(RD): SUS frame, normal image
  // index = 7(LD): SUS frame, mirror image
  
  GsimTrap* trapOuterCal[nOuterTypes-1][nk];
  GsimBoxWithoutABox* woboxOuterCal[nk];

  for( int i=0; i<nOuterTypes-1; i++ ){
    for( int k=0; k<nk; k++){
      trapOuterCal[i][k] = 0;
      woboxOuterCal[k] = 0;
    }
  }

  // x distance from the beam center to the module center
  std::vector<double> paramXoffset;
  double block_x = (KtevCsic_XY+KtevCsic_Gap)*cm;
  paramXoffset.push_back(  50.10*mm );
  paramXoffset.push_back( 150.05*mm );
  paramXoffset.push_back( 252.06*mm );
  paramXoffset.push_back( 333.09*mm );
  paramXoffset.push_back( 435.21*mm );
  paramXoffset.push_back( 525.04*mm );
  paramXoffset.push_back( 582.59*mm );
  paramXoffset.push_back( 635.09*mm );
  paramXoffset.push_back( 676.28*mm );


  // Y offsets for All type irrespective to KTeVCsI
  std::vector<double> paramYoffset;
  paramYoffset.push_back( -23.93*mm );
  paramYoffset.push_back( -18.60*mm );
  paramYoffset.push_back( - 7.39*mm );
  paramYoffset.push_back( -25.00*mm);
  paramYoffset.push_back( -25.05*mm);
  paramYoffset.push_back( -25.00*mm);
  paramYoffset.push_back( -25.05*mm);
  paramYoffset.push_back( -25.00*mm);
  paramYoffset.push_back( -24.94*mm);
  
  std::vector<double> paramOuterCal[nOuterTypes];
  // TYPE#0
  paramOuterCal[0].push_back(500.*mm);         // pDz
  paramOuterCal[0].push_back(0*deg);           // pTheta
  paramOuterCal[0].push_back(0*deg);           // pPhi
  paramOuterCal[0].push_back(99.7*mm);         // pDy1
  paramOuterCal[0].push_back(49.99*mm);        // pDx1(y=-pDy1 of the face at -pDz)
  paramOuterCal[0].push_back(44.73*mm);        // pDx2(y=+pDy1 of the face at -pDz)
  paramOuterCal[0].push_back(1.509879*deg); // pAlp1
  paramOuterCal[0].push_back(99.7*mm);         // pDy2
  paramOuterCal[0].push_back(49.99*mm);        // pDx3(y=-pDy2 of the face at +pDz)
  paramOuterCal[0].push_back(44.73*mm);        // pDx4(y=+pDy2 of the face at +pDz)
  paramOuterCal[0].push_back(1.509879*deg); // pAlp2

  // TYPE#1
  paramOuterCal[1].push_back(500.*mm);
  paramOuterCal[1].push_back(0*deg);
  paramOuterCal[1].push_back(0*deg);
  paramOuterCal[1].push_back(99.7*mm);
  paramOuterCal[1].push_back(44.662*mm);
  paramOuterCal[1].push_back(28.715*mm);
  paramOuterCal[1].push_back(4.572324*deg);
  paramOuterCal[1].push_back(99.7*mm);
  paramOuterCal[1].push_back(44.662*mm);
  paramOuterCal[1].push_back(28.715*mm);
  paramOuterCal[1].push_back(4.572324*deg);

  // TYPE#2
  paramOuterCal[2].push_back(500.*mm);
  paramOuterCal[2].push_back(0*deg);
  paramOuterCal[2].push_back(0*deg);
  paramOuterCal[2].push_back(102.82*mm);
  paramOuterCal[2].push_back(28.57*mm);
  paramOuterCal[2].push_back(1e-8*mm);
  paramOuterCal[2].push_back(7.910564*deg);
  paramOuterCal[2].push_back(102.82*mm);
  paramOuterCal[2].push_back(28.57*mm);
  paramOuterCal[2].push_back(1e-8*mm);
  paramOuterCal[2].push_back(7.910564*deg);

  // TYPE#3
  paramOuterCal[3].push_back(500.*mm);
  paramOuterCal[3].push_back(0*deg);
  paramOuterCal[3].push_back(0*deg);
  paramOuterCal[3].push_back(49.55*mm);
  paramOuterCal[3].push_back(123.40*mm);
  paramOuterCal[3].push_back(5.6*mm);
  paramOuterCal[3].push_back(49.936401*deg);
  paramOuterCal[3].push_back(49.55*mm);
  paramOuterCal[3].push_back(123.40*mm);
  paramOuterCal[3].push_back(5.6*mm);
  paramOuterCal[3].push_back(49.936401*deg);


  // TYPE#4
  paramOuterCal[4].push_back(500.*mm);
  paramOuterCal[4].push_back(0*deg);
  paramOuterCal[4].push_back(0*deg);
  paramOuterCal[4].push_back(49.55*mm);
  paramOuterCal[4].push_back(111.711*mm);
  paramOuterCal[4].push_back(24.935*mm);
  paramOuterCal[4].push_back(41.206923*deg);
  paramOuterCal[4].push_back(49.55*mm);
  paramOuterCal[4].push_back(111.711*mm);
  paramOuterCal[4].push_back(24.935*mm);
  paramOuterCal[4].push_back(41.206923*deg);


  // TYPE#5
  paramOuterCal[5].push_back(500.*mm);
  paramOuterCal[5].push_back(0*deg);
  paramOuterCal[5].push_back(0*deg);
  paramOuterCal[5].push_back(49.55*mm);
  paramOuterCal[5].push_back(82.482*mm);
  paramOuterCal[5].push_back(12.662*mm);
  paramOuterCal[5].push_back(35.166132*deg);
  paramOuterCal[5].push_back(49.55*mm);
  paramOuterCal[5].push_back(82.482*mm);
  paramOuterCal[5].push_back(12.662*mm);
  paramOuterCal[5].push_back(35.166132*deg);

  // TYPE#6
  paramOuterCal[6].push_back(500.*mm);
  paramOuterCal[6].push_back(0*deg);
  paramOuterCal[6].push_back(0*deg);
  paramOuterCal[6].push_back(49.55*mm);
  paramOuterCal[6].push_back(91.703*mm);
  paramOuterCal[6].push_back(33.256*mm);
  paramOuterCal[6].push_back(30.531124*deg);
  paramOuterCal[6].push_back(49.55*mm);
  paramOuterCal[6].push_back(91.703*mm);
  paramOuterCal[6].push_back(33.256*mm);
  paramOuterCal[6].push_back(30.531124*deg);


  // TYPE#7
  paramOuterCal[7].push_back(500.*mm);
  paramOuterCal[7].push_back(0*deg);
  paramOuterCal[7].push_back(0*deg);
  paramOuterCal[7].push_back(49.55*mm);
  paramOuterCal[7].push_back(92.295*mm);
  paramOuterCal[7].push_back(42.320*mm);
  paramOuterCal[7].push_back(26.761699*deg);
  paramOuterCal[7].push_back(49.55*mm);
  paramOuterCal[7].push_back(92.295*mm);
  paramOuterCal[7].push_back(42.320*mm);
  paramOuterCal[7].push_back(26.761399*deg);

  // TYPE#8
  paramOuterCal[8].push_back(49.55*mm);
  paramOuterCal[8].push_back(49.55*mm);
  paramOuterCal[8].push_back(500.*mm);
  paramOuterCal[8].push_back(10.*mm);
  paramOuterCal[8].push_back(10.*mm);
  paramOuterCal[8].push_back(0.*mm);
  paramOuterCal[8].push_back(-24.775*sqrt(2)*mm);
  paramOuterCal[8].push_back(45.*deg);


  for(index=0; index<8; index++ ){

    // For Type 0-8
    for(int itype=0;itype<nOuterTypes;itype++) {
      
      if( index >= 4 && itype == 8 ) continue;
      if( index >= 4 && itype == 7 ) continue;
      
      double YBlock;
      if( itype <= 1 ){
        YBlock = (KtevCsic_XY+KtevCsic_Gap)*-18*cm
          + paramYoffset.at( itype );
      }else{ 
        YBlock = (KtevCsic_XY+KtevCsic_Gap)*((itype-2)-18.)*cm
          + paramYoffset.at( itype );
      }
      
      double XBlock =  paramXoffset.at( itype );

      G4ThreeVector rot0( 0.*deg,180.*deg,-90.*deg ); //rotation vector for Type#0-#2
      G4ThreeVector rot1( 0.*deg,  0.*deg,180.*deg ); //rotation vector for Type#3-#6
      G4ThreeVector rot7( 0.*deg,  0.*deg,180.*deg ); //rotation vector for Type#7-#8

      
      if( index >= 4 ){
        double dtmp = XBlock;
        XBlock = YBlock;
        YBlock = dtmp;
      }

      switch( index%4 ){
      case 0:
        break;
      case 1:
        XBlock = - XBlock;
        break;
      case 2:
        YBlock = - YBlock; 
        break;
      case 3:
        XBlock = - XBlock;
        YBlock = - YBlock; 
        break;
      }

      switch( index ){
      case 0:
        break;
      case 1:
        rot0.set( 0.*deg,0.*deg,90.*deg );
        rot1.set( 0.,180.*deg,180.*deg );
        rot7.set( 0.,0.*deg,90.*deg );
        break;
      case 2:
        rot0.set( 0.*deg,0.*deg,-90.*deg );
        rot1.set( 180.*deg,0.*deg,180.*deg );
        rot7.set( 0.,0.*deg,270.*deg );
        break;
      case 3:
        rot0.set( 0.*deg,180.*deg,90.*deg );
        rot1.set( 180.*deg,180.*deg,180.*deg );
        rot7.set( 0.,0.*deg,0.*deg );
        break;
      case 4:
        rot0.set( 0.*deg,0.*deg,0.*deg );
        rot1.set( 0.,180.*deg,90.*deg );
        break;
      case 5:
        rot0.set( 0.*deg,180.*deg,0.*deg );
        rot1.set( 0.,0.*deg,-90.*deg );
        break;
      case 6:
        rot0.set( 0.*deg,180.*deg,180.*deg );
        rot1.set( 0.,0.*deg,90.*deg );
        break;
      case 7:
        rot0.set( 0.*deg,0.*deg,180.*deg );
        rot1.set( 0.,180.*deg,-90.*deg );
        break;
      } 

      GsimBox *lead = 0;
      GsimBox *scinti = 0;
      GsimBox *bar = 0;
      GsimBox *airgap = 0;
      GsimTrap *lumirror = 0;
      GsimBoxWithoutABox *lumirror_wobox = 0;

      std::sprintf(nam,"OEV#%d-%d",itype,index);
      if( itype < 8 ){ // Module type 0-7
	if( itype <= 2 ){
	  trapOuterCal[itype][index] = new GsimTrap(std::string(nam),this,
						    G4ThreeVector(XBlock,YBlock,0),rot0);
	}else{
	  trapOuterCal[itype][index] = new GsimTrap(std::string(nam),this,
						    G4ThreeVector(XBlock,YBlock,0),rot1 );
	}
	if( index >= 2 && index <= 5 ){
	  trapOuterCal[itype][index]->setOuterMaterial("G4_Al");
	}else{
	  trapOuterCal[itype][index]->setOuterMaterial("G4_Fe");
	}
	trapOuterCal[itype][index]->setParameters(paramOuterCal[itype]);
	trapOuterCal[itype][index]->setOuterColor("white");
	addDaughter(trapOuterCal[itype][index]);
	
	// ----------------------------INSERT LUMMIOR VOLUME-----------------------
	
	lumirror = 0;
	
	std::sprintf(nam,"Lumirror");
	lumirror = new GsimTrap(std::string(nam),trapOuterCal[itype][index], 
				G4ThreeVector(0,0,0.*mm),G4ThreeVector());
	
	double dx, dy, dz;
	dx = dy = dz = 0.*mm;
	
	//
	if( index==0 || index==3 || index==5 || index==6 ){ // z' axis is -z direction 
	  dz = +40.*mm;
	}else{ // z' axis is +z direction 
	  dz = -40.*mm;
	}
	if( itype > 2 ) dz *= -1.;
	  
	  
	std::vector<double> tmp_size;
	tmp_size.clear();
	
	for( int k=0; k<(int)paramOuterCal[itype].size(); k++){
	  double beta = atan(2*tan(paramOuterCal[itype][6]));
	  double trim_xl, trim_xr;
	  double trim_yb, trim_yt;
	  double dtmp;

	  double t_frame; // thickness of the metal frame SUS:2mm, Al:1mm
	  if( index >= 2 && index <= 5 ){ // for AL frame
	    t_frame = 1.*mm;
	  }else{ // for SUS frame
	    t_frame = 2.*mm;
	  }
	  
	  if( k == 0 ){

	    tmp_size.push_back( 420.*mm );
	    
	  }else if( k==4 || k==8 ){ // for pDx1
	    
	    trim_xl = t_frame;
	    trim_xr = t_frame*(tan(beta)+1./cos(beta));
	    dtmp = paramOuterCal[itype][k] - trim_xl - trim_xr;
	    tmp_size.push_back( dtmp );
	    if( itype == 2 ){
	      dx = (t_frame-t_frame*(tan(beta)+1./cos(beta)))/2.;
	    }
	    
	  }else if( k==5 || k==9 ){ // for pDx2
	    
	    trim_xl = t_frame;
	    trim_xr = t_frame*(-tan(beta)+1./cos(beta));
	    dtmp = paramOuterCal[itype][k] - trim_xl - trim_xr;
	    tmp_size.push_back( dtmp );
	    
	  }else if( k==3 || k==7 ){
	    dtmp = t_frame*2.;
	    if( itype == 2 ){
	      dtmp = t_frame*(1./sin(beta)+1./tan(beta));
	      dy = t_frame-dtmp/2.;
	    }
	    tmp_size.push_back( paramOuterCal[itype][k]-dtmp);
	    
	  }else{
	    tmp_size.push_back( paramOuterCal[itype][k]);
	  }
	}
	
	if( itype==2 ){
	  tmp_size[5] = 1e-8*mm;
	  tmp_size[9] = 1e-8*mm;
	}
	lumirror->setParameters( tmp_size );

	lumirror->setTranslationVector(G4ThreeVector(dx,dy,dz));
	lumirror->setOuterMaterial("G4_MYLAR");
	lumirror->setOuterVisibility(true);
	lumirror->setOuterColor("white");

	trapOuterCal[itype][index]->addDaughter( lumirror );
	  

	// ------------------------INSERT LAYERS---------------------
	int layerNo, id;
	bool isLead;
	double x, y;
	std::vector<double> paramVolumeSize;
	
	layerNo = 0;
	lead = 0;
	scinti = 0;
	id = 0;
	
	while( 1 ){
	  if( index >= 2 && index <= 5 ){ // for AL frame
	    if( (index == 2 || index == 3) && (itype >= 0 && itype <= 2 )){
	      GetLayerVolumeTopVer1( itype, layerNo, paramVolumeSize,
				     x, y, isLead, id );
	    }else{
	      GetLayerVolumeTop( itype, layerNo, paramVolumeSize,
				 x, y, isLead, id );
	    }
	    
	  }else{
	    GetLayerVolumeBottom( itype, layerNo, paramVolumeSize,
				  x, y, isLead, id );
	  }
	  
	  
	  if( layerNo == -1 )break;
	  
	  if( isLead == true ){
	    std::sprintf(nam,"lead%d",id);
	    if( itype <= 2 ){
	      lead = new GsimBox( std::string(nam), lumirror,
				  G4ThreeVector( -y, x, 0. ),
				  G4ThreeVector( 0, 0, -90.*deg ));
	    }else{
	      lead = new GsimBox( std::string(nam), lumirror,
				  G4ThreeVector( x, y, 0. ), G4ThreeVector());
	    }
	    lead->setOuterMaterial("G4_Pb");
	    lead->setOuterColor("gray50");
	    lead->setOuterVisibility(true);
	    lead->setParameters(paramVolumeSize);
	    // lead->setSensitiveDetector("OEV_Lead",det_id);
	    
	    lumirror->addDaughter( lead );
	  }else{
	    // This layer is scintillator
	    std::sprintf(nam,"Scinti%d",id);
	    if( itype <= 2 ){
	      scinti = new GsimBox( std::string(nam), lumirror,
				    G4ThreeVector( -y, x, 0. ),
				    G4ThreeVector( 0, 0, -90.*deg ));
	    }else{
	      scinti = new GsimBox( std::string(nam), lumirror,
				    G4ThreeVector( x, y, 0. ), G4ThreeVector());
	    }
	    
	      
	    scinti->setOuterMaterial("G4_POLYSTYRENE");
	    scinti->setOuterColor("cyan");
	    scinti->setOuterVisibility(true);
	    scinti->setParameters(paramVolumeSize);
	    scinti->setSensitiveDetector("OEV",det_id);
	    
	      
	    lumirror->addDaughter( scinti );
	  }
	  
	  layerNo++;
	}
	
	// ------------------------INSERT AL bar ---------------------
	    
	int counter;
	bool isBar;
	
	counter = 0;
	lead = 0;
	scinti = 0;
	id = 0;
	
	while( 1 ){
	  if( index >= 2 && index <= 5 ){ // for AL frame
	    break;
	  }else{
	    GetBarAndAirgap( itype, counter, paramVolumeSize,
			     x, y, isBar, id );
	  }
	  
	  if( counter == -1 )break;
	  
	  if( isBar == true ){
	    std::sprintf(nam,"Albar%d",id);
	    if( itype <= 2 ){
	      bar = new GsimBox( std::string(nam), lumirror,
				 G4ThreeVector( -y, x, 0. ),
				 G4ThreeVector( 0, 0, -90.*deg ));
	    }else{
	      bar = new GsimBox( std::string(nam), lumirror,
				 G4ThreeVector( x, y, 0. ), G4ThreeVector());
	    }
	    bar->setOuterMaterial("G4_Al");
	    bar->setOuterColor("white");
	    bar->setOuterVisibility(true);
	    bar->setParameters(paramVolumeSize);
	    
	    lumirror->addDaughter( bar );
	  }else{
	    // This layer is Airgap
	    std::sprintf(nam,"Airgap%d",id);
	    if( itype <= 2 ){
	      airgap = new GsimBox( std::string(nam), lumirror,
				    G4ThreeVector( -y, x, 0. ),
				    G4ThreeVector( 0, 0, -90.*deg ));
	    }else{
	      airgap = new GsimBox( std::string(nam), lumirror,
				    G4ThreeVector( x, y, 0. ), G4ThreeVector());
	    }
	    
	      
	    airgap->setOuterMaterial("G4_AIR");
	    airgap->setOuterColor("green");
	    airgap->setOuterVisibility(true);
	    airgap->setParameters(paramVolumeSize);
	      
	    lumirror->addDaughter( airgap );
	  }
	  
	  counter++;
	}



      }else{ // Module type 8
	woboxOuterCal[index] = new GsimBoxWithoutABox(std::string(nam),this,
						      G4ThreeVector(XBlock,YBlock,0),
						      rot7 );
	if( index >= 2 && index <= 5 ){
	  woboxOuterCal[index]->setOuterMaterial("G4_Al");
	}else{
	  woboxOuterCal[index]->setOuterMaterial("G4_Fe");
	}

	woboxOuterCal[index]->setParameters(paramOuterCal[itype]);
	woboxOuterCal[index]->setOuterColor("white");
	addDaughter(woboxOuterCal[index]);
        


	// ----------------------------INSERT LUMIRROR-----------------------

 	std::sprintf(nam,"Lumirror");
	lumirror_wobox = new GsimBoxWithoutABox(std::string(nam),woboxOuterCal[index], 
						G4ThreeVector(0,0,0.*mm),G4ThreeVector());
	
	std::vector<double> tmp_size;
	tmp_size.clear();

	// TYPE#8
	if( index >= 2 && index <= 5 ){
	  tmp_size.push_back(47.6*mm);
	  tmp_size.push_back(47.6*mm);
	}else{
	  tmp_size.push_back(45.6*mm);
	  tmp_size.push_back(45.6*mm);
	}
	tmp_size.push_back(420.*mm);
	tmp_size.push_back(12.*mm);
	tmp_size.push_back(12.*mm);
	tmp_size.push_back(0.*mm);
	if( index >= 2 && index <= 5 ){
	  tmp_size.push_back(-24.8*sqrt(2)*mm+1.*mm);
	}else{
	  tmp_size.push_back(-24.8*sqrt(2)*mm+2.*mm);
	}
	tmp_size.push_back(45.*deg);


	lumirror_wobox->setParameters( tmp_size );
	lumirror_wobox->setTranslationVector(G4ThreeVector(0,0,-40.*mm));
	lumirror_wobox->setOuterMaterial("G4_MYLAR");
	lumirror_wobox->setOuterVisibility(true);
	lumirror_wobox->setOuterColor("white");

	woboxOuterCal[index]->addDaughter( lumirror_wobox );


 	// ------------------------INSERT LAYERS---------------------
	int layerNo, id;
	bool isLead;
	double x, y;
	std::vector<double> paramVolumeSize;
	
	layerNo = 0;
	lead = 0;
	scinti = 0;
	id = 0;
	
	while( 1 ){
	  if( index >= 2 && index <= 5 ){ // for AL frame
	    GetLayerVolumeTop( itype, layerNo, paramVolumeSize,
			       x, y, isLead, id );
	  }else{
	    GetLayerVolumeBottom( itype, layerNo, paramVolumeSize,
				  x, y, isLead, id );
	  }
	  
	  if( layerNo == -1 )break;
	  
	  if( isLead == true ){
	    std::sprintf(nam,"lead%d",id);
	    if( index == 0 || index == 3 ){
	      lead = new GsimBox( std::string(nam), lumirror_wobox,
				  G4ThreeVector( x, y, 0. ), G4ThreeVector());
	    }else{
	      lead = new GsimBox( std::string(nam), lumirror_wobox,
				  G4ThreeVector( -y, -x, 0. ),
				  G4ThreeVector( 0, 0, -90.*deg ));
	    }

	    lead->setOuterMaterial("G4_Pb");
	    lead->setOuterColor("gray50");
	    lead->setOuterVisibility(true);
	    lead->setParameters(paramVolumeSize);
	    
	    lumirror_wobox->addDaughter( lead );
	  }else{
	    // This layer is scintillator
	    std::sprintf(nam,"Scinti%d",id);
	    if( index == 0 || index == 3 ){
	      scinti = new GsimBox( std::string(nam), lumirror_wobox,
				    G4ThreeVector( x, y, 0. ), G4ThreeVector());
	    }else{
	      scinti = new GsimBox( std::string(nam), lumirror_wobox,
				    G4ThreeVector( -y, -x, 0. ),
				    G4ThreeVector( 0, 0, -90.*deg ));
	    }
	    
	    scinti->setOuterMaterial("G4_POLYSTYRENE");
	    scinti->setOuterColor("cyan");
	    scinti->setOuterVisibility(true);
	    scinti->setParameters(paramVolumeSize);
	    scinti->setSensitiveDetector("OEV",det_id);
	      
	    lumirror_wobox->addDaughter( scinti );
	  }
	  
	  layerNo++;

	}

	// ------------------------INSERT AL bar ---------------------
	    
	int counter;
	bool isBar;
	
	counter = 0;
	lead = 0;
	scinti = 0;
	id = 0;
	
	while( 1 ){
	  if( index >= 2 && index <= 5 ){ // for AL frame
	    break;
	  }else{
	    GetBarAndAirgap( itype, counter, paramVolumeSize,
			     x, y, isBar, id );
	  }
	  
	  if( counter == -1 )break;
	  
	  if( isBar == true ){
	    std::sprintf(nam,"Albar%d",id);
	    if( index == 0 || index == 3 ){
	      bar = new GsimBox( std::string(nam), lumirror_wobox,
				 G4ThreeVector( x, y, 0. ), G4ThreeVector());
	    }else{
	      bar = new GsimBox( std::string(nam), lumirror_wobox,
				 G4ThreeVector( -y, -x, 0. ),
				 G4ThreeVector( 0, 0, -90.*deg ));
	    }
	    bar->setOuterMaterial("G4_Al");
	    bar->setOuterColor("white");
	    bar->setOuterVisibility(true);
	    bar->setParameters(paramVolumeSize);
	    
	    lumirror_wobox->addDaughter( bar );
	  }else{
	    // This layer is Airgap
	    std::sprintf(nam,"Airgap%d",id);
	    if( index == 0 || index == 3 ){
	      airgap = new GsimBox( std::string(nam), lumirror_wobox,
				    G4ThreeVector( x, y, 0. ), G4ThreeVector());
	    }else{
	      airgap = new GsimBox( std::string(nam), lumirror_wobox,
				    G4ThreeVector( -y, -x, 0. ),
				    G4ThreeVector( 0, 0, -90.*deg ));
	    }

	    airgap->setOuterMaterial("G4_AIR");
	    airgap->setOuterColor("green");
	    airgap->setOuterVisibility(true);
	    airgap->setParameters(paramVolumeSize);
	      
	    lumirror_wobox->addDaughter( airgap );
	  }

	  counter++;

	}
      }

      det_id++;

    }
  }


  GsimSensitiveDetector* sd =
    dynamic_cast<GsimSensitiveDetector*>(GsimUtil::getUtil()->getSensitiveDetector("OEV"));
  
  setThisAndDaughterBriefName("OEV");

}


GsimE14OEV::~GsimE14OEV()
{
  ;
}

void GsimE14OEV::GetLayerVolumeBottom(int itype, 
				      int &layerNo, 
				      std::vector<double> &vec, 
				      double &x, 
				      double &y, 
				      bool &isLead,
				      int &id
				      )
{
  // itype : detector type (#0 - #8)
  // layer number : -1 ... end of stacking layers

  const double lead_thickness   = 1.495* mm;
  const double scinti_thickness = 4.85 * mm;
  isLead = false;
  static int leadNo = 0;
  static int ScintiNo = 0;

  
  vec.clear();
  
  int index_layer_material_bottom[9][14] = {
    // 0: lead plate
    // 1: scintillator box
    //-1: no layer
    { 0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  1, -1}, //type#0
    { 0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  1, -1, -1, -1}, //type#1
    { 0,  1,  0,  1,  0,  1, -1, -1, -1, -1, -1, -1, -1, -1}, //type#2
    { 0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1, -1, -1}, //type#3
    { 0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  1, -1}, //type#4
    { 0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  1, -1}, //type#5
    { 0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  1, -1}, //type#6
    { 0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  1, -1}, //type#7
    { 0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  1, -1}, //type#8
  };
  
  double lead_width_bottom[9][6] = {
    { 92.7, 95.2, 95.2, 95.2, 95.2, 89.2 },  //type#0
    { 92.7, 95.2, 95.2, 89.2, 66.1,    0 },  //type#1
    { 63.2, 53.5, 28.7,    0,    0,    0 },  //type#2
    { 93.7, 89.8, 73.4, 57.0, 40.6, 24.2 },  //type#3
    { 87.2, 86.1, 74.0, 61.9, 49.9, 37.8 },  //type#4
    { 61.5, 61.2, 51.5, 41.8, 32.0, 22.3 },  //type#5
    { 72.2, 73.3, 65.2, 57.0, 48.9, 40.8 },  //type#6
    { 74.2, 75.5, 69.1, 62.1, 55.2, 48.2 },  //type#7
    { 42.5, 45.1, 45.1, 45.1, 45.1, 36.1 },  //type#8
  };
    
  double lead_x_pos_bottom[9][6] = {
    {    0,    0,    0,    0,    0, -2.9 },  //type#0
    {    0,    0,    0, -3.0,-14.5,    0 },  //type#1
    {-10.0,-16.1,-28.5,    0,    0,    0 },  //type#2
    {-19.7,-16.5, -8.3, -0.1,  8.1, 16.3 },  //type#3
    {-14.0,-12.2, -6.1, -0.1,  6.0, 12.0 },  //type#4
    {-11.2, -9.8, -4.9, -0.1,  4.8,  9.6 },  //type#5
    {- 8.9, -8.2, -4.1, -0.1,  4.0,  8.1 },  //type#6
    {- 7.3, -6.7, -3.5,  0.0,  3.5,  7.0 },  //type#7
    {    0,    0,    0,    0,    0,  4.5 },  //type#8
  };
  
  double lead_y_pos_bottom[9][6] = {
    {-20.5,-13.6, -6.7,  0.2,  7.1, 14.0 },  //type#0
    {-15.2, -8.3, -1.4,  5.5, 12.4,    0 },  //type#1
    { -4.8,  2.1,  9.0,    0,    0,    0 },  //type#2
    {-21.6,-14.7, -7.8, -0.9,  6.0, 12.9 },  //type#3
    {-21.6,-14.7, -7.8, -0.9,  6.0, 12.9 },  //type#4
    {-21.6,-14.7, -7.8, -0.9,  6.0, 12.9 },  //type#5
    {-21.6,-14.7, -7.8, -0.9,  6.0, 12.9 },  //type#6
    {-21.6,-14.7, -7.8, -0.9,  6.0, 12.9 },  //type#7
    {-21.6,-14.7, -7.8, -0.9,  6.0, 12.9 },  //type#8
  };
  
  double scinti_width_bottom[9][7] = {
    { 95.2, 95.2, 95.2, 95.2, 95.2, 83.2, 26.6 },  //type#0
    { 95.2, 95.2, 89.2, 89.2, 56.4, 18.5,    0 },  //type#1
    { 64.5, 51.3, 18.5,    0,    0,    0,    0 },  //type#2
    { 95.0, 88.4, 72.0, 55.5, 39.1, 13.7,    0 },  //type#3
    { 88.5, 85.1, 73.0, 60.9, 48.8, 30.7, 22.0 },  //type#4
    { 62.7, 60.4, 50.6, 40.9, 31.2, 15.5,  8.4 },  //type#5
    { 73.5, 72.6, 64.5, 56.3, 48.2, 34.0, 28.2 },  //type#6
    { 75.5, 75.4, 68.5, 61.5, 54.5, 41.6, 36.5 },  //type#7
    { 45.1, 45.1, 45.1, 45.1, 36.1, 30.1, 30.1 },  //type#8
  };

  double scinti_x_pos_bottom[9][7] = {
    {    0,    0,    0,    0,    0,    0, -28.3 },  //type#0
    {    0,    0, -3.0, -3.0,-13.4,-32.4,     0 },  //type#1
    {-10.6,-17.2,-27.6,    0,    0,    0,     0 },  //type#2
    {-19.1,-15.8, -7.6,  0.6,  8.8, 12.5,     0 },  //type#3
    {-13.3,-11.6, -5.6,  0.4,  6.5,  9.5, 13.9  },  //type#4
    {-10.6,- 9.4, -4.5,  0.3,  5.2,  7.1, 10.6  },  //type#5
    { -8.3,- 7.9, -3.8,  0.3,  4.3,  5.4,  8.3  },  //type#6
    { -6.7, -6.7, -3.2,  0.3,  3.8,  4.3,  6.8 },  //type#7
    {    0,    0,    0,    0,  4.5,  1.5,  1.5 },  //type#8
  };
  
  double scinti_y_pos_bottom[9][7] = {
    {-17.1,-10.2, -3.3,  3.6, 10.5, 17.4, 22.45 },  //type#0
    {-11.7, -4.8,  2.1,  9.0, 15.9, 20.9,     0 },  //type#1
    { -1.4,  5.5, 12.4,    0,    0,    0,     0 },  //type#2
    {-18.2,-11.3, -4.4,  2.5,  9.4, 16.3,     0 },  //type#3
    {-18.2,-11.3, -4.4,  2.5,  9.4, 16.3, 21.3  },  //type#4
    {-18.2,-11.3, -4.4,  2.5,  9.4, 16.3, 21.3  },  //type#5
    {-18.2,-11.3, -4.4,  2.5,  9.4, 16.3, 21.3  },  //type#6
    {-18.2,-11.3, -4.4,  2.5,  9.4, 16.3, 21.3  },  //type#7
    {-18.2,-11.3, -4.4,  2.5,  9.4, 16.3, 21.3  },  //type#8
  };
  


  if( layerNo == 0 ){
    leadNo = 0;
    ScintiNo = 0;
    id = 0;
  }
  
  int layer_material = index_layer_material_bottom[itype][layerNo];
  if( layer_material == -1 ){
    layerNo = -1;
    return;
  }

  if( layer_material == 0 ){ // lead plate
    x = lead_x_pos_bottom[ itype ][ leadNo ]*mm;
    y = lead_y_pos_bottom[ itype ][ leadNo ]*mm;
    isLead = true;
    vec.push_back(lead_width_bottom[ itype ][ leadNo ]*mm);
    vec.push_back(lead_thickness*mm);
    vec.push_back(420*mm);
    id = leadNo++;
  }
    
  if( layer_material != 0 ){ // Scinti plate
    x = scinti_x_pos_bottom[ itype ][ ScintiNo ]*mm;
    y = scinti_y_pos_bottom[ itype ][ ScintiNo ]*mm;
    isLead = false;
    vec.push_back(scinti_width_bottom[ itype ][ ScintiNo ]*mm);
    vec.push_back(scinti_thickness*mm);
    vec.push_back(420*mm);
    id = ScintiNo++;
  }
    
  return;
  
}

void GsimE14OEV::GetLayerVolumeTop(int itype, 
				   int &layerNo, 
				   std::vector<double> &vec, 
				   double &x, 
				   double &y, 
				   bool &isLead,
				   int &id
				   )
{
  // itype : detector type (#0 - #8)
  // layer number : -1 ... end of stacking layers

  const double lead_thickness   = 1.495* mm;
  const double scinti_thickness = 4.85 * mm;
  isLead = false;
  static int leadNo = 0;
  static int ScintiNo = 0;

  
  vec.clear();
  
  int index_layer_material_bottom[9][15] = {
    // 0: lead plate
    // 1: scintillator box
    //-1: no layer
    { 0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  1, -1, -1}, //type#0
    { 0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1, -1, -1, -1}, //type#1
    { 0,  1,  0,  1,  0,  1,  1, -1, -1, -1, -1, -1, -1, -1, -1}, //type#2
    { 0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1, -1}, //type#3
    { 0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1, -1}, //type#4
    { 0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1, -1}, //type#5
    { 0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1, -1}, //type#6
    { 0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1, -1}, //type#7
    { 0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1, -1}  //type#8
  };

  double lead_width_bottom[9][7] = {
    { 97.1, 97.1, 97.1, 97.1, 97.1, 97.1,    0 },  //type#0
    { 97.1, 97.1, 97.1, 97.1, 79.7, 36.6,    0 },  //type#1
    { 86.6, 61.8, 37.0,    0,    0,    0,    0 },  //type#2
    {112.1, 95.7, 79.3, 62.9, 46.5, 30.1, 13.7 },  //type#3
    {103.0, 90.9, 78.8, 66.7, 54.6, 42.5, 30.5 },  //type#4
    { 75.0, 65.3, 55.6, 45.9, 36.1, 26.4, 16.7 },  //type#5
    { 85.1, 77.0, 68.8, 60.7, 52.6, 44.4, 36.3 },  //type#6
    { 86.4, 79.4, 72.4, 65.5, 58.5, 51.6, 44.6 },  //type#7
    { 47.0, 47.0, 47.0, 47.0, 47.0, 47.0, 44.7 }   //type#8
  };

  //---------- 

  double lead_x_pos_bottom[9][7] = {
    {    0,    0,    0,    0,    0,    0,  0 },  //type#0
    {    0,    0,    0,    0, -8.8,-30.3,  0 },  //type#1
    { -3.7,-16.1,-28.5,    0,    0,    0,  0 },  //type#2
    {-25.9,-17.6, -9.4, -1.2,  7.0, 15.2, 23.4 },  //type#3
    {-19.1,-13.0, -7.0, -1.0,  5.1, 11.1, 17.2 },  //type#4
    {-15.3,-10.5, -5.6, -0.8,  4.1,  9.0, 13.8 },  //type#5
    {-12.8, -8.8, -4.7, -0.6,  3.4,  7.5, 11.6 },  //type#6
    {-11.0, -7.5, -4.0, -0.6,  2.9,  6.4,  9.9 },  //type#7
    {    0,    0,    0,    0,    0,    0,  1.1 }   //type#8
  };
  
  double lead_y_pos_bottom[9][7] = {
    {-21.5,-14.6, -7.7, -0.8,  6.1, 13.0,    0 },  //type#0
    {-16.2, -9.3, -2.4,  4.5, 11.4, 18.3,    0 },  //type#1
    { -5.4,  1.5,  8.5,    0,    0,    0,    0 },  //type#2
    {-22.6,-15.7, -8.8, -1.9,  5.0, 11.9, 18.8 },  //type#3
    {-22.6,-15.7, -8.8, -1.9,  5.0, 11.9, 18.8 },  //type#4
    {-22.6,-15.7, -8.8, -1.9,  5.0, 11.9, 18.8 },  //type#5
    {-22.6,-15.7, -8.8, -1.9,  5.0, 11.9, 18.8 },  //type#6
    {-22.6,-15.7, -8.8, -1.9,  5.0, 11.9, 18.8 },  //type#7
    {-22.6,-15.7, -8.8, -1.9,  5.0, 11.9, 18.8 }   //type#8
  };

  double scinti_width_bottom[9][7] = {
    { 97.1, 97.1, 97.1, 97.1, 97.1, 97.1, 63.4 },  //type#0
    { 97.1, 97.1, 97.1, 97.1, 68.4, 23.4,    0 },  //type#1
    { 85.9, 61.1, 36.2,  8.4,    0,    0,    0 },  //type#2
    {111.6, 95.2, 78.8, 62.4, 46.0, 29.6, 13.2 },  //type#3
    {102.6, 90.5, 78.4, 66.4, 54.3, 42.2, 30.1 },  //type#4
    { 74.8, 65.1, 55.3, 45.6, 35.9, 26.1, 16.4 },  //type#5
    { 84.9, 76.8, 68.6, 60.5, 52.3, 44.2, 36.1 },  //type#6
    { 86.2, 79.2, 72.2, 65.3, 58.3, 51.4, 44.4 },  //type#7
    { 47.0, 47.0, 47.0, 47.0, 47.0, 47.0, 44.5 }   //type#8
  };

  double scinti_x_pos_bottom[9][7] = {
    {    0,    0,    0,    0,    0,    0, -16.9 },  //type#0
    {    0,    0,    0,    0,-14.4,-36.9,     0 },  //type#1
    { -4.1,-16.5,-28.9,-42.8,    0,    0,     0 },  //type#2
    {-25.6,-17.4, -9.2, -1.0,  7.2, 15.4, 23.6  },  //type#3
    {-18.9,-12.9, -6.8, -0.8,  5.3, 11.2, 17.3  },  //type#4
    {-15.2,-10.3, -5.5, -0.6,  4.2,  9.1, 14.0  },  //type#5
    {-12.7,- 8.7, -4.6, -0.5,  3.5,  7.6, 11.7  },  //type#6
    {-11.0, -7.4, -3.9, -0.4,  3.0,  6.5, 10.0  },  //type#7
    {    0,    0,    0,    0,    0,    0,  1.3 },  //type#8
  };
  
  double scinti_y_pos_bottom[9][7] = {
    {-18.1,-11.2, -4.3,  2.6,  9.5, 16.4, 21.6 },  //type#0
    {-12.7, -5.8,  1.1,  8.0, 14.9, 21.8,    0 },  //type#1
    { -2.0,  4.9, 11.8, 17.0,    0,    0,    0 },  //type#2
    {-19.2,-12.3, -5.4,  1.5,  8.4, 15.3, 22.2 },  //type#3
    {-19.2,-12.3, -5.4,  1.5,  8.4, 15.3, 22.2  },  //type#4
    {-19.2,-12.3, -5.4,  1.5,  8.4, 15.3, 22.2  },  //type#5
    {-19.2,-12.3, -5.4,  1.5,  8.4, 15.3, 22.2  },  //type#6
    {-19.2,-12.3, -5.4,  1.5,  8.4, 15.3, 22.2  },  //type#7
    {-19.2,-12.3, -5.4,  1.5,  8.4, 15.3, 22.2  },  //type#8
  };
  


  if( layerNo == 0 ){
    leadNo = 0;
    ScintiNo = 0;
    id = 0;
  }
  
  int layer_material = index_layer_material_bottom[itype][layerNo];
  if( layer_material == -1 ){
    layerNo = -1;
    return;
  }

  if( layer_material == 0 ){ // lead plate
    x = lead_x_pos_bottom[ itype ][ leadNo ]*mm;
    y = lead_y_pos_bottom[ itype ][ leadNo ]*mm;
    isLead = true;
    vec.push_back(lead_width_bottom[ itype ][ leadNo ]*mm);
    vec.push_back(lead_thickness*mm);
    vec.push_back(420*mm);
    id = leadNo++;
  }
    
  if( layer_material != 0 ){ // Scinti plate
    x = scinti_x_pos_bottom[ itype ][ ScintiNo ]*mm;
    y = scinti_y_pos_bottom[ itype ][ ScintiNo ]*mm;
    isLead = false;
    vec.push_back(scinti_width_bottom[ itype ][ ScintiNo ]*mm);
    vec.push_back(scinti_thickness*mm);
    vec.push_back(420*mm);
    id = ScintiNo++;
  }
    
  return;
  
}

void GsimE14OEV::GetLayerVolumeTopVer1(int itype, 
				       int &layerNo, 
				       std::vector<double> &vec, 
				       double &x, 
				       double &y, 
				       bool &isLead,
				       int &id
				       )
{
  // itype : detector type (#0 - #2)
  // layer number : -1 ... end of stacking layers

  const double lead_thickness   = 1.495* mm;
  const double scinti_thickness = 4.85 * mm;
  isLead = false;
  static int leadNo = 0;
  static int ScintiNo = 0;
  
  vec.clear();
  
  int index_layer_material_bottom[3][15] = {
    // 0: lead plate
    // 1: scintillator box
    //-1: no layer
    { 0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  1, -1, -1}, //type#0
    { 0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1, -1, -1, -1}, //type#1
    { 0,  1,  0,  1,  0,  1,  1, -1, -1, -1, -1, -1, -1, -1, -1} //type#2
  };

  double lead_width_bottom[3][7] = {
    { 97.1, 97.1, 97.1, 97.1, 97.1, 97.1,    0 },  //type#0
    { 97.1, 97.1, 97.1, 97.1, 76.5, 32.1,    0 },  //type#1
    { 87.6, 62.0, 36.5,    0,    0,    0,    0 }  //type#2
  };

  double lead_x_pos_bottom[3][7] = {
    {    0,    0,    0,    0,    0,    0,  0 },  //type#0
    {    0,    0,    0,    0,-10.3,-32.5,  0 },  //type#1
    { -3.2,-15.8,-28.7,    0,    0,    0,  0 }   //type#2
  };
  
  double lead_y_pos_bottom[9][7] = {
    {-21.9,-14.8, -7.7, -0.6,  6.5, 13.6,    0 },  //type#0
    {-16.4, -9.3, -2.2,  4.9, 12.0, 19.1,    0 },  //type#1
    { -5.8,  1.3,  8.4,    0,    0,    0,    0 }   //type#2
  };

  double scinti_width_bottom[9][7] = {
    { 97.1, 97.1, 97.1, 97.1, 97.1, 97.1, 53.5 },  //type#0
    { 97.1, 97.1, 97.1, 97.1, 72.0, 18.5,    0 },  //type#1
    { 85.1, 59.5, 33.8,  8.5,    0,    0,    0 }   //type#2
  };

  double scinti_x_pos_bottom[9][7] = {
    {    0,    0,    0,    0,    0,    0, -21.8 },  //type#0
    {    0,    0,    0,    0,-12.5,-39.3,     0 },  //type#1
    { -4.4,-17.2,-30.1,-42.7,    0,    0,     0 }   //type#2
  };
  
  double scinti_y_pos_bottom[9][7] = {
    {-18.4,-11.3, -4.2,  2.8, 10.0, 17.1, 22.4 },  //type#0
    {-12.9, -5.8,  1.3,  8.4, 15.5, 22.5,    0 },  //type#1
    { -2.2,  4.9, 12.0, 17.0,    0,    0,    0 }   //type#2
  };

  if( layerNo == 0 ){
    leadNo = 0;
    ScintiNo = 0;
    id = 0;
  }
  
  int layer_material = index_layer_material_bottom[itype][layerNo];
  if( layer_material == -1 ){
    layerNo = -1;
    return;
  }

  if( layer_material == 0 ){ // lead plate
    x = lead_x_pos_bottom[ itype ][ leadNo ]*mm;
    y = lead_y_pos_bottom[ itype ][ leadNo ]*mm;
    isLead = true;
    vec.push_back(lead_width_bottom[ itype ][ leadNo ]*mm);
    vec.push_back(lead_thickness*mm);
    vec.push_back(420*mm);
    id = leadNo++;
  }
    
  if( layer_material != 0 ){ // Scinti plate
    x = scinti_x_pos_bottom[ itype ][ ScintiNo ]*mm;
    y = scinti_y_pos_bottom[ itype ][ ScintiNo ]*mm;
    isLead = false;
    vec.push_back(scinti_width_bottom[ itype ][ ScintiNo ]*mm);
    vec.push_back(scinti_thickness*mm);
    vec.push_back(420*mm);
    id = ScintiNo++;
  }
    
  return;
  
}



void GsimE14OEV::GetBarAndAirgap(int itype, 
				 int &counter, 
				 std::vector<double> &vec, 
				 double &x, 
				 double &y, 
				 bool &isBar,
				 int &id
				 )
{
  // itype : detector type (#0 - #8)
  // layer number : -1 ... end of bar box

  isBar = false;
  static int BarNo = 0;
  static int AirgapNo = 0;
  
  vec.clear();
  
  int index_material[9][5] = {
    // 0: Al bar
    // 1: Air gap
    //-1: no bar and gap
    { 0,  0,  1, -1, -1}, //type#0
    { 0,  0,  1,  1, -1}, //type#1
    { 0,  0,  1,  1, -1}, //type#2
    { 0,  0,  1, -1, -1}, //type#3
    { 0,  0,  1, -1, -1}, //type#4
    { 0,  0,  1, -1, -1}, //type#5
    { 0,  0,  1, -1, -1}, //type#6
    { 0,  0,  1, -1, -1}, //type#7
    { 0,  0,  1,  1, -1} //type#8
  };
  
  
  double bar_width[9][2] = {
    { 6.0, 6.0 }, //type#0
    { 6.0, 6.0 }, //type#1
    { 6.0,12.0 }, //type#2
    { 9.0,12.0 }, //type#3
    { 6.0,12.0 }, //type#4
    { 6.0,11.0 }, //type#5
    { 6.0, 9.0 }, //type#6
    { 6.0, 9.0 }, //type#7
    { 6.0, 9.0 }  //type#8
  };
  
  double bar_height[9][2] = {
    { 6.0, 6.0 }, //type#0
    { 9.0, 9.0 }, //type#1
    { 6.0, 6.0 }, //type#2
    { 8.0, 6.0 }, //type#3
    { 6.0, 6.0 }, //type#4
    { 6.0, 6.0 }, //type#5
    { 6.0, 6.0 }, //type#6
    { 6.0, 6.0 }, //type#7
    { 6.0,13.0 }  //type#8
  };
  
  double bar_x_pos[9][2] = {
    { -44.9,  44.9 },  //type#0
    { -44.9,  44.9 },  //type#1
    { -40.1,  27.9 },  //type#2
    {  24.0, -73.0 },  //type#3
    {  28.1, -63.8 },  //type#4
    {  18.1, -47.7 },  //type#5
    {  25.7, -50.3 },  //type#6
    {  28.2, -49.3 },  //type#7
    {  19.8, -18.3 }   //type#8
  };

  double bar_y_pos[9][2] = {
    {  21.2,  16.5 },  //type#0
    {  19.5,   5.1 },  //type#1
    {  15.0, - 3.0 },  //type#2
    {  18.8, -19.8 },  //type#3
    {  19.8, -19.8 },  //type#4
    {  19.8, -19.8 },  //type#5
    {  19.8, -19.8 },  //type#6
    {  19.8, -19.8 },  //type#7
    {  19.8,  16.3 }   //type#8
  };

  double airgap_width[9][2] = {
    { 6.0, 6.0 }, //type#0
    { 6.0, 6.0 }, //type#1
    { 6.0, 9.0 }, //type#2
    { 9.0,   0}, //type#3
    { 6.0,   0 }, //type#4
    { 6.0,   0 }, //type#5
    { 6.0,   0 }, //type#6
    { 6.0,   0 }, //type#7
    { 6.0, 9.0 }  //type#8
  };
  
  double airgap_height[9][2] = {
    { 3.3,   0 }, //type#0
    { 1.6, 1.1 }, //type#1
    { 2.0, 2.5 }, //type#2
    { 1.0,   0 }, //type#3
    { 3.0,   0 }, //type#4
    { 3.0,   0 }, //type#5
    { 3.0,   0 }, //type#6
    { 3.0,   0 }, //type#7
    { 3.0, 2.9 }  //type#8
  };
  
  double airgap_x_pos[9][2] = {
    { -44.9,    0 },  //type#0
    { -44.9, 44.9 },  //type#1
    { -40.1, 38.4 },  //type#2
    {  24.0,    0 },  //type#3
    {  28.1,    0 },  //type#4
    {  18.1,    0 },  //type#5
    {  25.7,    0 },  //type#6
    {  28.2,    0 },  //type#7
    {  19.8,-18.3 }   //type#8
  };

  double airgap_y_pos[9][2] = {
    {  16.6,    0 },  //type#0
    {  14.2,  0.1 },  //type#1
    {  10.9, -4.7 },  //type#2
    {  14.3,    0 },  //type#3
    {  15.3,    0 },  //type#4
    {  15.3,    0 },  //type#5
    {  15.3,    0 },  //type#6
    {  15.3,    0 },  //type#7
    {  15.3,  8.3 }   //type#8
  };

  

  
  if( counter == 0 ){
    BarNo = 0;
    AirgapNo = 0;
    id = 0;
  }
  
  int material = index_material[itype][counter];
  if( material == -1 ){
    counter = -1;
    return;
  }

  if( material == 0 ){ // Al bar
    x = bar_x_pos[ itype ][ BarNo ]*mm;
    y = bar_y_pos[ itype ][ BarNo ]*mm;
    isBar = true;
    vec.push_back(bar_width[ itype ][ BarNo ]*mm);
    vec.push_back(bar_height[ itype ][ BarNo ]*mm);
    vec.push_back(420*mm);
    id = BarNo++;
  }
    
  if( material != 0 ){ // Airgap
    x = airgap_x_pos[ itype ][ AirgapNo ]*mm;
    y = airgap_y_pos[ itype ][ AirgapNo ]*mm;
    isBar = false;
    vec.push_back(airgap_width[ itype ][ AirgapNo ]*mm);
    vec.push_back(airgap_height[ itype ][ AirgapNo ]*mm);
    vec.push_back(420*mm);
    id = AirgapNo++;
  }
    
  return;
  
}


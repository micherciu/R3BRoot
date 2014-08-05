// -------------------------------------------------------------------------
// -----                   R3BSTaRTraDigit source file                 -----
// -----                  Created 29/04/14  by M.Labiche               -----
// -----                                                               -----
// ----- This class creates a tree with the following information:     -----
// -----  Det_Id (<=> Ladder Id)                                       -----  
// -----         Det_Id<7   (inner layer)                              -----
// -----       6<Det_Id<19  (mid layer)                                -----
// -----      18<Det_Id     (outer layer)                              -----
// -----  StripA Id  (front strips)                                    -----
// -----  Strip B Id (back strips)                                     -----
// -----  Energy loss                                                  -----
// -----  Time                                                         -----
// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
#include "R3BSTaRTraDigit.h"
#include "TMath.h"
#include "TVector3.h"
#include "TGeoMatrix.h"

#include "TClonesArray.h"
#include "TRandom.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"

#include "TGeoManager.h"

#include "R3BSTaRTraPoint.h"
#include "R3BSTaRTrackerDigitHit.h"

using std::cout;
using std::endl;


R3BSTaRTraDigit::R3BSTaRTraDigit() : FairTask("R3B STaRTracker Hit Raw Sim data ") { 
	fThreshold=0.;	   //no threshold
	fTrackerResolution=0.; //perfect resolution
}


R3BSTaRTraDigit::~R3BSTaRTraDigit() {
}


// -----   Public method Init   --------------------------------------------
InitStatus R3BSTaRTraDigit::Init() {
	FairRootManager* ioManager = FairRootManager::Instance();
	if ( !ioManager ) Fatal("Init", "No FairRootManager");
	fSTaRTrackerHitCA = (TClonesArray*) ioManager->GetObject("STaRTraPoint");
	
	
	// Register output array STaRTraDigitHit
	fSTaRTraHitCA = new TClonesArray("R3BSTaRTrackerDigitHit",1000);
	ioManager->Register("STaRTrackerDigitHit", "STaRTracker Hit", fSTaRTraHitCA, kTRUE);	
	
	return kSUCCESS;
	
}



// -----   Public method ReInit   --------------------------------------------
InitStatus R3BSTaRTraDigit::ReInit() {
	
	
	return kSUCCESS;
	
}


// -----   Public method Exec   --------------------------------------------
void R3BSTaRTraDigit::Exec(Option_t* opt) {
	
	Reset();
	
	Double_t pi= 3.141592653589793238;
	// Si Geometrical parameter:
	// Inner layer
	//Double_t Length1  = 19.03 ; // cm
	Double_t Length1  = 21.794 ; // cm
	//Double_t WidthMax1  = 7.945 ; // cm
	Double_t WidthMax1  = 8.1912 ; // cm
	//Double_t WidthMin1  = 2.25 ; // cm
	Double_t WidthMin1  = 1.971 ; // cm
	//Double_t StripPitch1= 0.00515 ; // = 51.5 um
	Double_t StripPitch1= 0.00385 + 0.0012 + 0.0001 + 0.000127+ 2e-6 ; // 
	//Double_t InclAng1=14.9;
	Double_t InclAng1=14.3;
	Double_t Rmin1=1.75;    // cm
	//Double_t AngRangeMin1=7.;    
	Double_t AngRangeMin1=5.26;    
	Double_t AngTrap1=atan((WidthMax1/2 -WidthMin1/2)/Length1);
//	Double_t WidthHalf1=WidthMax1 - (Length1/cos(AngTrap1))*sin(AngTrap1);
	Double_t StepZ1= StripPitch1/sin(AngTrap1) ; // step along the z axis of the detector (in xz plan)
	Double_t StepX1= StripPitch1/cos(AngTrap1) ; // step along the x axis of the detector (in xz plan)
	Int_t    NbStrip1   = int(WidthMax1/StepX1); //
	//cout << "NbStrip1= " << NbStrip1 << endl;
	Double_t Xlab1, Ylab1, Zlab1;  // see trunk/tracker/R3BSTaRTra.cxx
	Xlab1=0.;
	Ylab1=-((Length1/2)*sin(InclAng1*pi/180.)+ Rmin1);
	Zlab1=-Length1*cos(InclAng1*pi/180.)/2 + (Rmin1/tan(AngRangeMin1*pi/180.));

	Double_t ShiftalongZ;
	Double_t Proj ; // cm
	Double_t ProjStrip ; // cm
	Int_t strip=0;
	Int_t StripA_Id=0;
	Int_t StripB_Id=0;
	Double_t SlopA,SlopB,OffsetA,OffsetB;
	

	Int_t ChipA=-1;
	Int_t StripFront=-1;
	Int_t ChipB=-1;
	Int_t StripBack=-1;


	// Middle layer
	//Double_t Length2  = 30.06 ; // cm
	Double_t Length2  = 33.83875 ; // cm
	//Double_t WidthMax2  = 10.4 ; // cm
	Double_t WidthMax2  = 10.80295 ; // cm
	//Double_t WidthMin2  = 1.3 ; // cm
	Double_t WidthMin2  = 1.1406 ; // cm
	//Double_t StripPitch2= 0.00515 ; // = 51.5 um
	Double_t StripPitch2= 0.00385 + 0.0012 + 0.0001 + 0.00007; // 
	Double_t InclAng2=32.155; // deg    
	Double_t Rmin2=2.22;    // cm
	Double_t AngRangeMin2=5.3;// deg    
	//Double_t AngTrap2= 0.14853 ; // in rad = 17/2 degrees
	Double_t AngTrap2= atan((WidthMax2 /2 - WidthMin2 /2)/Length2); // (rad) ;
	Double_t StepZ2= StripPitch2/sin(AngTrap2) ; // step along the z axis of the detector (in xz plan)
	Double_t StepX2= StripPitch2/cos(AngTrap2) ; // step along the x axis of the detector (in xz plan)
	Int_t    NbStrip2   = int(WidthMax2/StepX2); //
	//cout << "NbStrip2= " << NbStrip2 << endl;
	Double_t Xlab2, Ylab2, Zlab2;  // see trunk/tracker/R3BSTaRTra.cxx
	Xlab2=0;
	Ylab2=-((Length2/2)*sin(InclAng2*pi/180.)+ Rmin2);
	Zlab2=-Length2*cos(InclAng2*pi/180.)/2 + (Rmin2/tan(AngRangeMin2*pi/180.));
	
    // Outer layer
	//Double_t Length3  = 30.06 ; // cm
	Double_t Length3  = 33.838753 ; // cm
	//Double_t WidthMax3  = 10.4 ; // cm
	Double_t WidthMax3  = 10.80295 ; // cm
	//Double_t WidthMin3  = 1.3 ; // cm
	Double_t WidthMin3  = 1.1406 ; // cm
	//Double_t StripPitch3= 0.005 ; // = 50 um
	Double_t StripPitch3= 0.00385 + 0.0012 + 0.0001 + 0.00007; // = 51.5 um
        Double_t InclAng3=32.155; // deg    
        Double_t Rmin3=2.95;    // cm
        Double_t AngRangeMin3=6.76; // deg   
	//Double_t AngTrap3= 0.14853 ; // in rad = 17/2 degrees
	Double_t AngTrap3= atan((WidthMax3 /2 - WidthMin3 /2)/Length3); // (rad)
	Double_t StepZ3= StripPitch3/sin(AngTrap3) ; // step along the z axis of the detector (in xz plan)
	Double_t StepX3= StripPitch3/cos(AngTrap3) ; // step along the x axis of the detector (in xz plan)
	Int_t    NbStrip3   = int(WidthMax3/StepX3); //
	//cout << "NbStrip3= " << NbStrip3 << endl;
        Double_t Xlab3, Ylab3, Zlab3;  // see trunk/tracker/R3BSTaRTra.cxx
        Xlab3=0;
        Ylab3=-((Length3/2)*sin(InclAng3*pi/180.)+ Rmin3);
        Zlab3=-Length3*cos(InclAng3*pi/180.)/2 + (Rmin3/tan(AngRangeMin3*pi/180.));
    

	//For v15:
   // Inner layer:
  Double_t M_Inner[6][4][4]=
    {

      {
	{0.866025404,	-0.5,             0,            0},  // Matrice 1 row 0
	{0.484507866,	0.83919224,	-0.246999013,	7.222645407},  // Matrice 1 row 1
	{0.123499506,	0.21390742,	0.969015731,	-8.449337001},   // Matrice 1 row 2
	{          0,           0,             0,            1}   // Matrice 1 row 3
      },

      {
	{             0,	     -1,              0,              0},  // Matrice 2 row 0
	{   0.969015731,	0,	-0.246999013,	7.222645407},  // Matrice 2 row 1
	{   0.246999013,	0,	0.969015731,	-8.449337001},  // Matrice 2 row 2
	{             0,	             0,	             0,             1}   // Matrice 2 row 3
      },

      {
	{  -0.866025404,	-0.5,             0,             0},  // Matrice 3 row 0
	{   0.484507866,	-0.83919224,	-0.246999013,	7.222645407},  // Matrice 3 row 1
	{   0.123499506,	-0.21390742,	0.969015731,	-8.449337001},  // Matrice 3 row 2
	{             0,	      0,             0,             1}   // Matrice 3 row 3
      },

      {
	{-0.866025404,	0.5,             0,             0},  // Matrice 4 row 0
	{-0.484507866,	-0.83919224,	-0.246999013,	7.222645407},  // Matrice 4 row 1
	{-0.123499506,	-0.21390742,	0.969015731,	-8.449337001},  // Matrice 4 row 2
	{          0.,	            0,	           0,             1}   // Matrice 4 row 3
      },

      {
	{   0., 	        1,             0,             0},  // Matrice 5 row 0
	{  -0.969015731,	0,	-0.246999013,	7.222645407},  // Matrice 5 row 1
	{  -0.246999013,	0,	0.969015731,	-8.449337001},  // Matrice 5 row 2
	{             0,	     0,	            0,             1}   // Matrice 5 row 3
      },

      {
	{  0.866025404,	0.5,             0,             0},  // Matrice 6 row 0
	{ -0.484507866,	0.83919224,	-0.246999013,	7.222645407},  // Matrice 6 row 1
	{ -0.123499506,	0.21390742,	0.969015731,	-8.449337001},  // Matrice 6 row 2
	{            0,	            0,	           0,             1}   // Matrice 6 row 3
      }

   };
 
  /*
  cout << M_Inner[0][0][0] << " " << M_Inner[0][0][1] << " " << M_Inner[0][0][2] << " " << M_Inner[0][0][3] << " " << endl;
  cout << M_Inner[0][1][0] << " " << M_Inner[0][1][1] << " " << M_Inner[0][1][2] << " " << M_Inner[0][1][3] << " " << endl;
  cout << M_Inner[0][2][0] << " " << M_Inner[0][2][1] << " " << M_Inner[0][2][2] << " " << M_Inner[0][2][3] << " " << endl;
  cout << M_Inner[0][3][0] << " " << M_Inner[0][3][1] << " " << M_Inner[0][3][2] << " " << M_Inner[0][3][3] << " " << endl;
  */

   // Middle layer:
     Double_t M_Mid[12][4][4]=
    {
      {
	{0.965925826,	-0.258819045,             0,            0},  // Matrice 1 row 0
	{0.219119161,	0.81776384,  -0.532211513,  20.45625232},  // Matrice 1 row 1
	{0.137746476,	0.514076846,   0.846611425, -9.606737174},  // Matrice 1 row 2
	{0,           0,             0,            1}   // Matrice 1 row 3
      },

      {
	{0.707106781,	-0.707106781,             0,            0},  // Matrice 2 row 0
	{0.59864468,	0.59864468,  -0.532211513,  20.45625232},  // Matrice 2 row 1
	{0.37633037,	0.37633037,   0.846611425, -9.606737174},  // Matrice 2 row 2
	{          0,           0,             0,            1}   // Matrice 2 row 3
      },

      {
	{0.258819045,	-0.965925826,            0,             0},  // Matrice 3 row 0
	{0.81776384,	0.219119161, -0.532211513,   20.45625232},  // Matrice 3 row 1
	{0.514076846,	0.137746476,  0.846611425,  -9.606737174},  // Matrice 3 row 2
	{          0,             0,            0,             1}   // Matrice 3 row 3
      },

      {
	{-0.258819045,	-0.965925826,             0,            0},  // Matrice 4 row 0
	{0.81776384,	-0.219119161,  -0.532211513,  20.45625232},  // Matrice 4 row 1
	{0.514076846,	-0.137746476,   0.846611425, -9.606737174},  // Matrice 4 row 2
	{          0,           0,             0,            1}   // Matrice 4 row 3
      },

      {
	{-0.707106781,	-0.707106781,            0,             0},  // Matrice 5 row 0
	{0.59864468,	-0.59864468, -0.532211513,   20.45625232},  // Matrice 5 row 1
	{0.37633037,	-0.37633037,  0.846611425,  -9.606737174},  // Matrice 5 row 2
	{          0,             0,            0,             1}   // Matrice 5 row 3
      },

      {
	{-0.965925826,	-0.258819045,            0,             0},  // Matrice 6 row 0
	{ 0.219119161,	-0.81776384, -0.532211513,   20.45625232},  // Matrice 6 row 1
	{ 0.137746476,	-0.514076846,  0.846611425,  -9.606737174},  // Matrice 6 row 2
	{           0,             0,            0,             1}   // Matrice 6 row 3
      },

      {
	{-0.965925826,	0.258819045,            0,             0},  // Matrice 7 row 0
	{-0.219119161,	-0.81776384, -0.532211513,   20.45625232},  // Matrice 7 row 1
	{-0.137746476,	-0.514076846,  0.846611425,  -9.606737174},  // Matrice 7 row 2
	{           0,             0,            0,             1}   // Matrice 7 row 3
      },

      {
	{-0.707106781,	0.707106781,             0,            0},  // Matrice 8 row 0
	{ -0.59864468,	-0.59864468,  -0.532211513,  20.45625232},  // Matrice 8 row 1
	{ -0.37633037,	-0.37633037,   0.846611425, -9.606737174},  // Matrice 8 row 2
	{ 0,            0,             0,            1}   // Matrice 8 row 3
      },

      {
	{-0.258819045,	0.965925826,             0,            0},  // Matrice 9 row 0
	{-0.81776384,	-0.219119161,  -0.532211513,  20.45625232},  // Matrice 9 row 1
	{-0.514076846,	-0.137746476,   0.846611425, -9.606737174},  // Matrice 9 row 2
	{           0,            0,             0,            1}   // Matrice 9 row 3
      },

      {
	{0.258819045,	0.965925826,             0,            0},  // Matrice 10 row 0
	{-0.81776384,	0.219119161,  -0.532211513,  20.45625232},  // Matrice 10 row 1
	{-0.514076846,	0.137746476,   0.846611425, -9.606737174},  // Matrice 10 row 2
	{           0,   0,             0,            1}   // Matrice 10 row 3
      },

      {
	{0.707106781,	0.707106781,            0,             0},  // Matrice 11 row 0
	{-0.59864468,	0.59864468,  -0.532211513,   20.45625232},  // Matrice 11 row 1
	{-0.37633037,	0.37633037,  0.846611425,  -9.606737174},  // Matrice 11 row 2
	{           0,            0,            0,             1}   // Matrice 11 row 3
      },

      {
	{ 0.965925826,	0.258819045,             0,            0},  // Matrice 12 row 0
	{-0.219119161,	0.81776384,  -0.532211513,  20.45625232},  // Matrice 12 row 1
	{-0.137746476,	0.514076846,   0.846611425, -9.606737174},  // Matrice 12 row 2
	{           0,            0,             0,            1}   // Matrice 12 row 3
      }

    };
  

     // Outer layer:
     Double_t M_Out[12][4][4]=  
    {
      {
	{0.965925826,	-0.258819045,             0,            0},  // Matrice 1 row 0
	{0.219119161,	0.81776384,  -0.532211513,  21.18625232},  // Matrice 1 row 1
	{0.137746476,	0.514076846,   0.846611425, -10.56307389},  // Matrice 1 row 2
	{0,           0,             0,            1}   // Matrice 1 row 3
      },

      {
	{0.707106781,	-0.707106781,             0,            0},  // Matrice 2 row 0
	{0.59864468,	0.59864468,  -0.532211513,  21.18625232},  // Matrice 2 row 1
	{0.37633037,	0.37633037,   0.846611425, -10.56307389},  // Matrice 2 row 2
	{          0,           0,             0,            1}   // Matrice 2 row 3
      },

      {
	{0.258819045,	-0.965925826,               0,             0},  // Matrice 3 row 0
	{0.81776384,	0.219119161,	-0.532211513,   21.18625232},  // Matrice 3 row 1
	{0.514076846,	0.137746476,	 0.846611425,  -10.56307389},  // Matrice 3 row 2
	{          0,             0,               0,             1}   // Matrice 3 row 3
      },

      {
	{-0.258819045,	-0.965925826,             0,            0},  // Matrice 4 row 0
	{0.81776384,	-0.219119161,  -0.532211513,  21.18625232},  // Matrice 4 row 1
	{0.514076846,	-0.137746476,   0.846611425, -10.56307389},  // Matrice 4 row 2
	{          0,           0,             0,            1}   // Matrice 4 row 3
      },

      {
	{-0.707106781,	-0.707106781,               0,             0},  // Matrice 5 row 0
	{0.59864468,	-0.59864468,	-0.532211513,   21.18625232},  // Matrice 5 row 1
	{0.37633037,	-0.37633037,	 0.846611425,  -10.56307389},  // Matrice 5 row 2
	{          0,             0,               0,             1}   // Matrice 5 row 3
      },


      {
	{-0.965925826,	-0.258819045,            0,             0},  // Matrice 6 row 0
	{ 0.219119161,	-0.81776384,	-0.532211513,   21.18625232},  // Matrice 6 row 1
	{ 0.137746476,	-0.514076846,	0.846611425,  -10.56307389},  // Matrice 6 row 2
	{           0,             0,            0,             1}   // Matrice 6 row 3
      },

      {
	{-0.965925826,	0.258819045,                 0,            0},  // Matrice 7 row 0
	{ -0.219119161,	-0.81776384,	-0.532211513,  21.18625232},  // Matrice 7 row 1
	{ -0.137746476,	-0.514076846,	 0.846611425, -10.56307389},  // Matrice 7 row 2
	{ 0,            0,                 0,            1}   // Matrice 7 row 3
      },

      {
	{-0.707106781,	0.707106781,               0,            0},  // Matrice 8 row 0
	{-0.59864468,	-0.59864468,	-0.532211513,  21.18625232},  // Matrice 8 row 1
	{-0.37633037,	-0.37633037,	 0.846611425, -10.56307389},  // Matrice 8 row 2
	{           0,            0,               0,            1}   // Matrice 8 row 3
      },

      {
	{-0.258819045,	0.965925826,              0,             0},  // Matrice 9 row 0
	{-0.81776384,	-0.219119161,	-0.532211513,   21.18625232},  // Matrice 9 row 1
	{-0.514076846,	-0.137746476,	 0.846611425,  -10.56307389},  // Matrice 9 row 2
	{           0,             0,              0,             1}   // Matrice 9 row 3
      },

      {
	{0.258819045,	0.965925826,             0,            0},  // Matrice 10 row 0
	{-0.81776384,	0.219119161,  -0.532211513,  21.18625232},  // Matrice 10 row 1
	{-0.514076846,	0.137746476,   0.846611425, -10.56307389},  // Matrice 10 row 2
	{           0,   0,             0,            1}   // Matrice 10 row 3
      },

      {
	{0.707106781,	0.707106781,               0,             0},  // Matrice 11 row 0
	{-0.59864468,	0.59864468,	-0.532211513,   21.18625232},  // Matrice 11 row 1
	{-0.37633037,	0.37633037,	 0.846611425,  -10.56307389},  // Matrice 11 row 2
	{           0,            0,               0,             1}   // Matrice 11 row 3
      },

      {
	{ 0.965925826,	0.258819045,             0,            0},  // Matrice 12 row 0
	{-0.219119161,	0.81776384,  -0.532211513,  21.18625232},  // Matrice 12 row 1
	{-0.137746476,	0.514076846,   0.846611425, -10.56307389},  // Matrice 12 row 2
	{           0,            0,             0,            1}   // Matrice 12 row 3
      }

    };
  


	/*  // For V14:	
	Double_t M_Inner[6][4][4]=
    {

      {
	{0.965925826,-0.258819045,             0,            0},  // Matrice 1 row 0
	{0.250799726, 0.935997321,  -0.246999013,  7.222645407},  // Matrice 1 row 1
	{0.063928049, 0.238582725,  0.969015731,  -8.449337001},   // Matrice 1 row 2
	{          0,           0,             0,            1}   // Matrice 1 row 3
      },

      {
	{   0.258819045,   -0.965925826,              0,              0},  // Matrice 2 row 0
	{   0.935997321,    0.250799726,   -0.246999013,    7.222645407},  // Matrice 2 row 1
	{   0.238582725,    0.063928049,    0.969015731,   -8.449337001},  // Matrice 2 row 2
	{             0,	      0,	      0,              1}   // Matrice 2 row 3
      },

      {
	{  -0.707106781,   -0.707106781,             0,             0},  // Matrice 3 row 0
	{   0.685197595,   -0.685197595,  -0.246999013,   7.222645407},  // Matrice 3 row 1
	{   0.174654677,   -0.174654677,   0.969015731,  -8.449337001},  // Matrice 3 row 2
	{             0,	      0,             0,             1}   // Matrice 3 row 3
      },

      {
	{-0.965925826,    0.258819045,             0,             0},  // Matrice 4 row 0
	{-0.250799726,   -0.935997321,	-0.246999013,   7.222645407},  // Matrice 4 row 1
	{-0.063928049,   -0.238582725,	 0.969015731,  -8.449337001},  // Matrice 4 row 2
	{          0.,	            0,	           0,             1}   // Matrice 4 row 3
      },

      {
	{  -0.258819045,   0.965925826,             0,             0},  // Matrice 5 row 0
	{  -0.935997321,  -0.250799726,	 -0.246999013,   7.222645407},  // Matrice 5 row 1
	{  -0.238582725,  -0.063928049,	  0.969015731,  -8.449337001},  // Matrice 5 row 2
	{             0,	     0,	            0,             1}   // Matrice 5 row 3
      },

      {
	{  0.707106781,   0.707106781,             0,             0},  // Matrice 6 row 0
	{ -0.685197595,	  0.685197595,	-0.246999013,   7.222645407},  // Matrice 6 row 1
	{ -0.174654677,	  0.174654677,	 0.969015731,  -8.449337001},  // Matrice 6 row 2
	{            0,	            0,	           0,             1}   // Matrice 6 row 3
      }


    };
	
	
	// Middle layer:
	Double_t M_Mid[12][4][4]=
    {

      {
	{1,           0,             0,            0},  // Matrice 1 row 0
	{0, 0.846611425,  -0.532211513,  20.45625232},  // Matrice 1 row 1
	{0, 0.532211513,   0.846611425, -9.606737174},  // Matrice 1 row 2
	{0,           0,             0,            1}   // Matrice 1 row 3
      },

      {
	{0.866025404,        -0.5,             0,            0},  // Matrice 2 row 0
	{0.423305713, 0.733187001,  -0.532211513,  20.45625232},  // Matrice 2 row 1
	{0.266105757, 0.460908691,   0.846611425, -9.606737174},  // Matrice 2 row 2
	{          0,           0,             0,            1}   // Matrice 2 row 3
      },

      {
	{        0.5,  -0.866025404,            0,             0},  // Matrice 3 row 0
	{0.733187001,   0.423305713, -0.532211513,   20.45625232},  // Matrice 3 row 1
	{0.460908691,   0.266105757,  0.846611425,  -9.606737174},  // Matrice 3 row 2
	{          0,             0,            0,             1}   // Matrice 3 row 3
      },

      {
	{          0,          -1,             0,            0},  // Matrice 4 row 0
	{0.846611425,           0,  -0.532211513,  20.45625232},  // Matrice 4 row 1
	{0.532211513,           0,   0.846611425, -9.606737174},  // Matrice 4 row 2
	{          0,           0,             0,            1}   // Matrice 4 row 3
      },

      {
	{       -0.5,  -0.866025404,            0,             0},  // Matrice 5 row 0
	{0.733187001,  -0.423305713, -0.532211513,   20.45625232},  // Matrice 5 row 1
	{0.460908691,  -0.266105757,  0.846611425,  -9.606737174},  // Matrice 5 row 2
	{          0,             0,            0,             1}   // Matrice 5 row 3
      },


      {
	{-0.866025404,          -0.5,            0,             0},  // Matrice 6 row 0
	{ 0.423305713,  -0.733187001, -0.532211513,   20.45625232},  // Matrice 6 row 1
	{ 0.266105757,  -0.460908691,  0.846611425,  -9.606737174},  // Matrice 6 row 2
	{           0,             0,            0,             1}   // Matrice 6 row 3
      },

      {
	{-1,            0,             0,            0},  // Matrice 7 row 0
	{ 0, -0.846611425,  -0.532211513,  20.45625232},  // Matrice 7 row 1
	{ 0, -0.532211513,   0.846611425, -9.606737174},  // Matrice 7 row 2
	{ 0,            0,             0,            1}   // Matrice 7 row 3
      },

      {
	{-0.866025404,          0.5,             0,            0},  // Matrice 8 row 0
	{-0.423305713, -0.733187001,  -0.532211513,  20.45625232},  // Matrice 8 row 1
	{-0.266105757, -0.460908691,   0.846611425, -9.606737174},  // Matrice 8 row 2
	{           0,            0,             0,            1}   // Matrice 8 row 3
      },

      {
	{       -0.5,    0.866025404,            0,             0},  // Matrice 9 row 0
	{-0.733187001,  -0.423305713, -0.532211513,   20.45625232},  // Matrice 9 row 1
	{-0.460908691,  -0.266105757,  0.846611425,  -9.606737174},  // Matrice 9 row 2
	{           0,             0,            0,             1}   // Matrice 9 row 3
      },

      {
	{           0,   1,             0,            0},  // Matrice 10 row 0
	{-0.846611425,   0,  -0.532211513,  20.45625232},  // Matrice 10 row 1
	{-0.532211513,   0,   0.846611425, -9.606737174},  // Matrice 10 row 2
	{           0,   0,             0,            1}   // Matrice 10 row 3
      },

      {
	{         0.5,  0.866025404,            0,             0},  // Matrice 11 row 0
	{-0.733187001,  0.423305713,  -0.532211513,   20.45625232},  // Matrice 11 row 1
	{-0.460908691,  0.266105757,  0.846611425,  -9.606737174},  // Matrice 11 row 2
	{           0,            0,            0,             1}   // Matrice 11 row 3
      },

      {
	{ 0.866025404,          0.5,             0,            0},  // Matrice 12 row 0
	{-0.423305713,  0.733187001,  -0.532211513,  20.45625232},  // Matrice 12 row 1
	{-0.266105757,  0.460908691,   0.846611425, -9.606737174},  // Matrice 12 row 2
	{           0,            0,             0,            1}   // Matrice 12 row 3
      }


      };
	
	
	// Outer layer:
	Double_t M_Out[12][4][4]=  
    {

      {
	{1,           0,             0,            0},  // Matrice 1 row 0
	{0, 0.846611425,  -0.532211513,  21.18625232},  // Matrice 1 row 1
	{0, 0.532211513,   0.846611425, -10.56307389},  // Matrice 1 row 2
	{0,           0,             0,            1}   // Matrice 1 row 3
      },

      {
	{0.866025404,        -0.5,             0,            0},  // Matrice 2 row 0
	{0.423305713, 0.733187001,  -0.532211513,  21.18625232},  // Matrice 2 row 1
	{0.266105757, 0.460908691,   0.846611425, -10.56307389},  // Matrice 2 row 2
	{          0,           0,             0,            1}   // Matrice 2 row 3
      },

      {
	{        0.5,  -0.866025404,               0,             0},  // Matrice 3 row 0
	{0.733187001,	0.423305713,	-0.532211513,   21.18625232},  // Matrice 3 row 1
	{0.460908691,	0.266105757,	 0.846611425,  -10.56307389},  // Matrice 3 row 2
	{          0,             0,               0,             1}   // Matrice 3 row 3
      },

      {
	{          0,          -1,             0,            0},  // Matrice 4 row 0
	{0.846611425,	        0,  -0.532211513,  21.18625232},  // Matrice 4 row 1
	{0.532211513,           0,   0.846611425, -10.56307389},  // Matrice 4 row 2
	{          0,           0,             0,            1}   // Matrice 4 row 3
      },

      {
	{       -0.5,  -0.866025404,               0,             0},  // Matrice 5 row 0
	{0.733187001,	-0.423305713,	-0.532211513,   21.18625232},  // Matrice 5 row 1
	{0.460908691,	-0.266105757,	 0.846611425,  -10.56307389},  // Matrice 5 row 2
	{          0,             0,               0,             1}   // Matrice 5 row 3
      },


      {
	{-0.866025404,          -0.5,            0,             0},  // Matrice 6 row 0
	{ 0.423305713,	-0.733187001,	-0.532211513,   21.18625232},  // Matrice 6 row 1
	{ 0.266105757,	-0.460908691,	0.846611425,  -10.56307389},  // Matrice 6 row 2
	{           0,             0,            0,             1}   // Matrice 6 row 3
      },

      {
	{-1,            0,                 0,            0},  // Matrice 7 row 0
	{ 0, -0.846611425,	-0.532211513,  21.18625232},  // Matrice 7 row 1
	{ 0, -0.532211513,	 0.846611425, -10.56307389},  // Matrice 7 row 2
	{ 0,            0,                 0,            1}   // Matrice 7 row 3
      },

      {
	{-0.866025404,          0.5,               0,            0},  // Matrice 8 row 0
	{-0.423305713,	-0.733187001,	-0.532211513,  21.18625232},  // Matrice 8 row 1
	{-0.266105757,	-0.460908691,	 0.846611425, -10.56307389},  // Matrice 8 row 2
	{           0,            0,               0,            1}   // Matrice 8 row 3
      },

      {
	{       -0.5,    0.866025404,              0,             0},  // Matrice 9 row 0
	{-0.733187001,	-0.423305713,	-0.532211513,   21.18625232},  // Matrice 9 row 1
	{-0.460908691,	-0.266105757,	 0.846611425,  -10.56307389},  // Matrice 9 row 2
	{           0,             0,              0,             1}   // Matrice 9 row 3
      },

      {
	{           0,   1,             0,            0},  // Matrice 10 row 0
	{-0.846611425,   0,  -0.532211513,  21.18625232},  // Matrice 10 row 1
	{-0.532211513,   0,   0.846611425, -10.56307389},  // Matrice 10 row 2
	{           0,   0,             0,            1}   // Matrice 10 row 3
      },

      {
	{         0.5,  0.866025404,               0,             0},  // Matrice 11 row 0
	{-0.733187001,	0.423305713,	-0.532211513,   21.18625232},  // Matrice 11 row 1
	{-0.460908691,	0.266105757,	 0.846611425,  -10.56307389},  // Matrice 11 row 2
	{           0,            0,               0,             1}   // Matrice 11 row 3
      },

      {
	{ 0.866025404,          0.5,             0,            0},  // Matrice 12 row 0
	{-0.423305713,  0.733187001,  -0.532211513,  21.18625232},  // Matrice 12 row 1
	{-0.266105757,  0.460908691,   0.846611425, -10.56307389},  // Matrice 12 row 2
	{           0,            0,             0,            1}   // Matrice 12 row 3
      }

     };
	
 */      
	
	Double_t Energy = 0.;
	Double_t Time = 0.;
	Double_t X_track= 0;
	Double_t Y_track= 0;
	Double_t Z_track= 0;
	Double_t X_track_det= 0;
	Double_t Y_track_det= 0;
	Double_t Z_track_det= 0;
	
	
	Int_t Detector;
	
	R3BSTaRTraPoint** traHit;
	
	Int_t traHitsPerEvent = 0;
	traHitsPerEvent = fSTaRTrackerHitCA->GetEntries();
	
	//cout << " NEW EVENT " << endl;

	
	//cout << traHitsPerEvent <<endl;
	
	//cout << "" << endl;

	
	if(traHitsPerEvent>0){

		traHit = new R3BSTaRTraPoint*[traHitsPerEvent];
		for(Int_t i=0;i<traHitsPerEvent;i++){
			traHit[i] = new R3BSTaRTraPoint;
			traHit[i] = (R3BSTaRTraPoint*) fSTaRTrackerHitCA->At(i);
			Energy = ExpResSmearing(traHit[i]->GetEnergyLoss());
			//Energy = traHit[i]->GetEnergyLoss();
			Detector = traHit[i]->GetDetCopyID();
			
			X_track = traHit[i]->GetXIn();
			Y_track = traHit[i]->GetYIn();
			Z_track = traHit[i]->GetZIn();
			
			Time=traHit[i]->GetTime();       
            
			if(Detector<=6){  // = inner layer
				
				//cout << Detector << " " << j << " " << k << endl;
				
				//cout <<  X_track << " " <<   Y_track << " " <<  Z_track << " " << endl;
				
				// apply Matrix transformation
				X_track_det=  X_track*M_Inner[Detector-1][0][0] 
				            + Y_track*M_Inner[Detector-1][0][1]
				            + Z_track*M_Inner[Detector-1][0][2]
				            +         M_Inner[Detector-1][0][3];
				
				//cout << M_Inner[Detector-1][0][0] << " " << M_Inner[Detector-1][0][1] << " " << M_Inner[Detector-1][0][2] << " " << M_Inner[Detector-1][0][3] << endl ;
				
				Y_track_det=  X_track*M_Inner[Detector-1][1][0] 
				            + Y_track*M_Inner[Detector-1][1][1]
				            + Z_track*M_Inner[Detector-1][1][2]
				            +         M_Inner[Detector-1][1][3];
				
				//cout << M_Inner[Detector-1][1][0] << " " << M_Inner[Detector-1][1][1] << " " << M_Inner[Detector-1][1][2] << " " << M_Inner[Detector-1][1][3] << endl ;

				Z_track_det=  X_track*M_Inner[Detector-1][2][0] 
				            + Y_track*M_Inner[Detector-1][2][1]
				            + Z_track*M_Inner[Detector-1][2][2]
				            +         M_Inner[Detector-1][2][3];
				
				//cout << M_Inner[Detector-1][2][0] << " " << M_Inner[Detector-1][2][1] << " " << M_Inner[Detector-1][2][2] << " " << M_Inner[Detector-1][2][3] << endl ;

				//cout <<  X_track_det << " " <<   Y_track_det << " " <<  Z_track_det << " " << endl;
				
				// find 1st strip hit:
				// step 1 : projection parallel to the 1st longitudinal side of the detector (ie: offset at z=0 of this straight line in plane xz)
				//SlopA= (2*Length1)/(WidthMax1-WidthMin1);
				SlopA= (2*Length1)/(WidthMin1-WidthMax1);
				Proj=  Z_track_det - SlopA*X_track_det;
				
				// step 2 : compare with projection of middle line of each strips.
				strip=0;
				ProjStrip=0.;
				//ProjStrip= (-Length1/2-(StepZ1/2)*(2*strip+1)) - SlopA*(-WidthMax1/2);  // 1st strip proj at z=0
			        ShiftalongZ= ( Xlab1*M_Inner[0][2][0] 
					       + Ylab1*M_Inner[0][2][1] 
					       + Zlab1*M_Inner[0][2][2] 
					       +     1*M_Inner[0][2][3])+ 0.03; // shift along z axis (-1.35855= z lab coordinate of the center of the detector after inverse transformation, 0.03 is an extra shift thought to be coinciding with the middle line of a strip: to be checked !! ).
				ProjStrip= (-Length1/2 + ShiftalongZ) - SlopA*(WidthMax1/2 - (StepX1/2)*(2*strip+1));  // 1st strip proj at x=0
				//ProjStrip= (-Length1/2 -1.1) - SlopA*(WidthMax1/2 - (StepX1/2)*(2*strip+1));  // 1st strip proj at x=0. -1.1 is a shift along z axis (TODO: find analytic formula).
				
				//cout << "SlopA= " << SlopA << " Length1= " << Length1 << " WidthMax1= " << WidthMax1 << " WidthMin1= " << WidthMin1 << endl;
				//cout << "Proj= " << Proj  << " ProjStrip= " << ProjStrip << endl;
				//cout << "StepZ1/2 = " << StepZ1/2  << " ProjStrip - Proj= " << ProjStrip-Proj << endl;
				
				while(strip<NbStrip1)
				{
				  if( (ProjStrip -Proj)<= StepZ1/2 && 
				      (ProjStrip -Proj)> -StepZ1/2)
				    {
				      // first strip hit is:
				      StripA_Id=strip+1;  // strip starts at #1
				      OffsetA= ProjStrip;
				      strip=NbStrip1;  // to end the loop
				    }else
				    {
				      strip++;
				      ProjStrip= (-Length1/2 + ShiftalongZ) - SlopA*(WidthMax1/2 - (StepX1/2)*(2*strip+1));
				    }

				}
				
				// find 2nd strip hit:
				// step 1 : projection parallel to the 2nd longitudinal side of the detector (ie: offset at z=0 of this straight line in plane xz)
				SlopB= -SlopA;
				Proj=  Z_track_det - SlopB*X_track_det;
				// step 2 : compare with projection of middle line of each strips.
				strip=0;
				ProjStrip=0.;
				//ProjStrip= (-Length1/2-(StepZ1/2)*(2*strip+1)) - SlopB*(WidthMax1/2);  // 1st strip proj at z=0
				//ProjStrip= (-Length1/2 -1.1) - SlopB*(-WidthMax1/2 + (StepX1/2)*(2*strip+1)); 
				ProjStrip= (-Length1/2 + ShiftalongZ) - SlopB*(-WidthMax1/2 + (StepX1/2)*(2*strip+1));  // 1st strip proj at x=0
				
				//cout << "SlopB= " << SlopB << " Length1= " << Length1 << " WidthMax1= " << WidthMax1 << " WidthMin1= " << WidthMin1 << endl;
				//cout << "Proj= " << Proj  << " ProjStrip= " << ProjStrip << endl;
				//cout << "StepZ1/2 = " << StepZ1/2  << " ProjStrip - Proj= " << ProjStrip-Proj << endl;
				
				while(strip<NbStrip1)
				{

				  if( (ProjStrip - Proj)<= StepZ1/2 && 
				      (ProjStrip - Proj)> -StepZ1/2)
				    {
				      // 2nd strip hit:
				      StripB_Id=strip+1;
				      OffsetB= ProjStrip;
				      strip=NbStrip1; // to end the loop
				    }else
				    {
				      strip++;
				      ProjStrip= (-Length1/2 + ShiftalongZ) - SlopB*(-WidthMax1/2 + (StepX1/2)*(2*strip+1));
				    }

				}
				
				ChipA=int((StripA_Id-1)/128);
				StripFront=(StripA_Id-1) - (ChipA*128);
				ChipB=int((StripB_Id-1)/128);
				StripBack=(StripB_Id-1) - (ChipB*128);			
				
				
			}   // end of Det=7 ( inner layer)
			
			if(Detector>=7 && Detector<=18){  // = Middle layer
				
				//cout << Detector << endl;
				
				// apply Matrix transformation 
				X_track_det=  X_track*M_Mid[Detector-7][0][0] 
				+ Y_track*M_Mid[Detector-7][0][1]
				+ Z_track*M_Mid[Detector-7][0][2]
				+               M_Mid[Detector-7][0][3];
				Y_track_det=  X_track*M_Mid[Detector-7][1][0] 
				+ Y_track*M_Mid[Detector-7][1][1]
				+ Z_track*M_Mid[Detector-7][1][2]
				+               M_Mid[Detector-7][1][3];
				Z_track_det=  X_track*M_Mid[Detector-7][2][0] 
				+ Y_track*M_Mid[Detector-7][2][1]
				+ Z_track*M_Mid[Detector-7][2][2]
				+               M_Mid[Detector-7][2][3];
				
				//cout <<  X_track << " " <<   Y_track << " " <<  Z_track << " " << endl;
				//cout <<  X_track_det << " " <<   Y_track_det << " " <<  Z_track_det << " " << endl;
				
				// find 1st strip hit:
				// step 1 : projection parallel to the 1st longitudinal side of the detector (ie: offset at z=0 of this straight line in plane xz)
				//SlopA= (2*Length2)/(WidthMax2-WidthMin2);
				SlopA= (2*Length2)/(WidthMin2-WidthMax2);
				Proj=  Z_track_det - SlopA*X_track_det;
				
				// step 2 : compare with projection of middle line of each strips.
				strip=0;
				ProjStrip=0.;
				//ProjStrip= (-Length2/2-(StepZ2/2)*(2*strip+1)) - SlopA*(-WidthMax2/2);  // 1st strip proj at z=0
				ShiftalongZ= ( Xlab2*M_Mid[0][2][0] 
					       + Ylab2*M_Mid[0][2][1] 
					       + Zlab2*M_Mid[0][2][2] 
					       +     1*M_Mid[0][2][3])+ 0.03; // shift along z axis (z lab coordinate of the center of the detector after inverse transformation, 0.03 is an extra shift thought to be coinciding with the middle line of a strip: to be checked !! ).
				ProjStrip= (-Length2/2 + ShiftalongZ) - SlopA*(WidthMax2/2 -(StepX2/2)*(2*strip+1));  // 1st strip proj at x=0 

				//ProjStrip= (-Length2/2 -5.5) - SlopA*(WidthMax2/2 -(StepX2/2)*(2*strip+1));  // 1st strip proj at x=0, -5.5 ia a shift along Z axis (TODO: find the analytic formula)
				
				//cout << "SlopA= " << SlopA << " Length2= " << Length2 << " WidthMax2= " << WidthMax2 << " WidthMin2= " << WidthMin2 << endl;
				//cout << "Proj= " << Proj  << " ProjStrip= " << ProjStrip << endl;
				//cout << "StepZ2/2 = " << StepZ2/2  << " ProjStrip - Proj= " << ProjStrip-Proj << endl;
				
				while(strip<NbStrip2)
				{

				  if( (ProjStrip - Proj)<=StepZ2/2 &&
				      (ProjStrip - Proj)>-StepZ2/2)
				    {
				      // first strip hit is:
				      StripA_Id=strip+1;
				      //cout << "StripA_Id= " << StripA_Id << endl;
				      OffsetA= ProjStrip;
				      strip=NbStrip2;  // to end the loop
				    }else
				    {
				      strip++;
				      ProjStrip= (-Length2/2 + ShiftalongZ) - SlopA*(WidthMax2/2 -(StepX2/2)*(2*strip+1));
				    }

				}
				
				// find 2nd strip hit:
				// step 1 : projection parallel to the 2nd longitudinal side of the detector (ie: offset at z=0 of this straight line in plane xz)
				SlopB= -SlopA;
				Proj=  Z_track_det - SlopB*X_track_det;
				// step 2 : compare with projection of middle line of each strips.
				strip=0;
				ProjStrip=0.;
				//ProjStrip= (-Length2/2-(StepZ2/2)*(2*strip+1)) - SlopB*(WidthMax2/2);  // 1st strip proj at z=0
				ProjStrip= (-Length2/2 + ShiftalongZ) - SlopB*(-WidthMax2/2 + (StepX2/2)*(2*strip+1));
				//ProjStrip= (-Length2/2 -5.5) - SlopB*(-WidthMax2/2 + (StepX2/2)*(2*strip+1));
				
				while(strip<NbStrip2)
				{
				  if( (ProjStrip - Proj)<=StepZ2/2 &&
				      (ProjStrip - Proj)>-StepZ2/2)
				    {
				      // 2nd strip hit:
				      StripB_Id=strip+1;
				      OffsetB= ProjStrip;
				      strip=NbStrip2; // to end the loop
				    }else
				    {
				      strip++;
				      ProjStrip= (-Length2/2 +ShiftalongZ) - SlopB*(-WidthMax2/2 + (StepX2/2)*(2*strip+1));
				    }

				  /*
					if( (ProjStrip-Proj)<StepZ2/2 ){
						// 2nd strip hit:
						StripB_Id=strip;
						//cout << "StripB_Id= " << StripB_Id << endl;
						OffsetB= ProjStrip;
						strip=NbStrip2; // to end the loop
					}else
					{
						strip++;
						//ProjStrip= (-Length2/2-(StepZ2/2)*(2*strip+1)) - SlopB*(WidthMax2/2);
						ProjStrip= (-Length2/2 -5.5) - SlopB*(-WidthMax2/2 + (StepX2/2)*(2*strip+1));
					}
				  */
				}


				ChipA=int((StripA_Id-1)/128);
				StripFront=(StripA_Id-1) - (ChipA*128);
				ChipB=int((StripB_Id-1)/128);
				StripBack=(StripB_Id-1) - (ChipB*128);			
				
				
			} 
			
			if(Detector>=19){  // = outer layer
				
				
				// apply Matrix transformation M_Out[x][4][4] 
				X_track_det=  X_track*M_Out[Detector-19][0][0] 
				+ Y_track*M_Out[Detector-19][0][1]
				+ Z_track*M_Out[Detector-19][0][2]
				+               M_Out[Detector-19][0][3];
				Y_track_det=  X_track*M_Out[Detector-18][1][0] 
				+ Y_track*M_Out[Detector-19][1][1]
				+ Z_track*M_Out[Detector-19][1][2]
				+               M_Out[Detector-19][1][3];
				Z_track_det=  X_track*M_Out[Detector-19][2][0] 
				+ Y_track*M_Out[Detector-19][2][1]
				+ Z_track*M_Out[Detector-19][2][2]
				+               M_Out[Detector-19][2][3];
				
				//cout <<  X_track << " " <<   Y_track << " " <<  Z_track << " " << endl;
				//cout <<  X_track_det << " " <<   Y_track_det << " " <<  Z_track_det << " " << endl;
				
				// find 1st strip hit:
				// step 1 : projection parallel to the 1st longitudinal side of the detector (ie: offset at z=0 of this straight line in plane xz)
				SlopA= (2*Length3)/(WidthMin3-WidthMax3);
				//SlopA= (2*Length3)/(WidthMax3-WidthMin3);
				Proj=  Z_track_det - SlopA*X_track_det;
				
				// step 2 : compare with projection of middle line of each strips.
				strip=0;
				ProjStrip=0.;
				//ProjStrip= (-Length3/2-(StepZ3/2)*(2*strip+1)) - SlopA*(-WidthMax3/2);  // 1st strip proj at z=0
				ShiftalongZ= ( Xlab3*M_Out[0][2][0] 
					       + Ylab3*M_Out[0][2][1] 
					       + Zlab3*M_Out[0][2][2] 
					       +     1*M_Out[0][2][3])+ 0.03; // shift along z axis (z lab coordinate of the center of the detector after inverse transformation, 0.03 is an extra shift thought to be coinciding with the middle line of a strip: to be checked !! ).
				ProjStrip= (-Length3/2 + ShiftalongZ) - SlopA*(WidthMax3/2 -(StepX3/2)*(2*strip+1));  // 1st strip proj at x=0
				//ProjStrip= (-Length3/2 -5) - SlopA*(WidthMax3/2 -(StepX3/2)*(2*strip+1));  // 1st strip proj at x=0
				
				//cout << "SlopA= " << SlopA << " Length3= " << Length3 << " WidthMax3= " << WidthMax3 << " WidthMin3= " << WidthMin3 << endl;
				//cout << "Proj= " << Proj  << " ProjStrip= " << ProjStrip << endl;
				//cout << "StepZ3/2 = " << StepZ3/2  << " ProjStrip - Proj= " << ProjStrip-Proj << endl;
				
				while(strip<NbStrip3)
				{
			    
				  if( (ProjStrip - Proj)<=StepZ3/2 &&
				      (ProjStrip - Proj)> -StepZ3/2)
				    {
				      // first strip hit is:
				      StripA_Id=strip+1;
				      OffsetA= ProjStrip;
				      strip=NbStrip3;  // to end the loop
				    }else
				    {
				      strip++;
				      ProjStrip= (-Length3/2 + ShiftalongZ) - SlopA*(WidthMax3/2 -(StepX3/2)*(2*strip+1));
				    }

				}

				
				// find 2nd strip hit:
				// step 1 : projection parallel to the 2nd longitudinal side of the detector (ie: offset at z=0 of this straight line in plane xz)
				SlopB= -SlopA;
				Proj=  Z_track_det - SlopB*X_track_det;
				// step 2 : compare with projection of middle line of each strips.
				strip=0;
				ProjStrip=0.;
				//ProjStrip= (-Length3/2-(StepZ3/2)*(2*strip+1)) - SlopB*(WidthMax3/2);  // 1st strip proj at z=0
				ProjStrip= (-Length3/2 + ShiftalongZ) - SlopB*(-WidthMax3/2 +(StepX3/2)*(2*strip+1));  // 1st strip proj at x=0
				//ProjStrip= (-Length3/2 -5) - SlopB*(-WidthMax3/2 +(StepX3/2)*(2*strip+1));  // 1st strip proj at x=0
				
				
				while(strip<NbStrip3)
				{
				  if( (ProjStrip - Proj)<=StepZ3/2 &&
				      (ProjStrip - Proj)> -StepZ3/2)
				    {
				      // 2nd strip hit:
				      StripB_Id=strip+1;
				      OffsetB= ProjStrip;
				      strip=NbStrip3; // to end the loop
				    }else
				    {
				      strip++;
				      ProjStrip= (-Length3/2 + ShiftalongZ) - SlopB*(-WidthMax3/2 + (StepX3/2)*(2*strip+1));  // 1st strip proj at x=0
				    }

				}


				ChipA=int((StripA_Id-1)/128);
				StripFront=(StripA_Id-1) - (ChipA*128);
				ChipB=int((StripB_Id-1)/128);
				StripBack=(StripB_Id-1) - (ChipB*128);			
				
			}
            
				

			//if(Energy >= fThreshold) AddHit(Energy, Detector, StripA_Id, StripB_Id, Time);
			if(Energy >= fThreshold)
			  {
			    AddHit(Detector, ChipA, 0, StripFront, Energy, Time);
			    AddHit(Detector, ChipB, 1, StripBack, Energy, Time);
			  }
				
			}
		}
		
		
		//cout << " " << endl;
		
	}
	
	
// ---- Public method Reset   --------------------------------------------------
void R3BSTaRTraDigit::Reset(){
	// Clear the CA structure
	// cout << " -I- R3BSTaRTraDigit:Reset() called " << endl;
	
if (fSTaRTraHitCA) fSTaRTraHitCA->Clear();
}   


// ---- Public method Finish   --------------------------------------------------
void R3BSTaRTraDigit::Finish()
{
	// here event. write histos
	cout << "" << endl;
	cout << " -I- Digit Finish() called " << endl;
	// Write control histograms
		
}


// -----  Public method SetExperimentalResolution  ----------------------------------
 void R3BSTaRTraDigit::SetExperimentalResolution(Double_t trackerRes)
{	
	fTrackerResolution=trackerRes;
    cout << "-I- R3BSTaRTraDigit::SetExperimentalResolution to " << fTrackerResolution << " GeV" << endl;
}


// -----  Public method SetDetectionThreshold  ----------------------------------
void R3BSTaRTraDigit::SetDetectionThreshold(Double_t thresholdEne)
{	
	fThreshold=thresholdEne;
	cout << "-I- R3BSTaRTraDigit::SetDetectionThreshold to " << fThreshold << " GeV" << endl;
}


// -----   Private method ExpResSmearing  --------------------------------------------
Double_t R3BSTaRTraDigit::ExpResSmearing(Double_t inputEnergy) {

	if(fTrackerResolution == 0) return inputEnergy;
	else{
		Double_t energy = gRandom->Gaus(inputEnergy,fTrackerResolution);
		//cout << "energy " << energy << " for and Energy of "<< inputEnergy  << endl;
		return energy;
	}

}


// -----   Private method AddHit  --------------------------------------------
//      R3BSTaRTrackerDigitHit* R3BSTaRTraDigit::AddHit(Double_t ene,Int_t det,Int_t Stripfrt, Int_t Stripbck, Double_t time){   
        R3BSTaRTrackerDigitHit* R3BSTaRTraDigit::AddHit(Int_t det,Int_t chip, Int_t side, Int_t strip, Double_t ene, Double_t time){   
	TClonesArray& clref = *fSTaRTraHitCA;
	Int_t size = clref.GetEntriesFast();
//	return new(clref[size]) R3BSTaRTrackerDigitHit(ene, det, Stripfrt, Stripbck, time);  
	return new(clref[size]) R3BSTaRTrackerDigitHit(det, chip, side, strip, ene, time);  
}

ClassImp(R3BSTaRTraDigit)

// -------------------------------------------------------------------------
// -----                        R3BLand header file                     -----
// -----                  Created 26/03/09  by D.Bertini               -----
// -------------------------------------------------------------------------

/**  R3BLand.h
 **/


#ifndef R3BLAND_H
#define R3BLAND_H

#include "R3BDetector.h"
#include "TLorentzVector.h"
#include "TGeoMedium.h"
#include <iostream>
#include <map>

using namespace std;

class TClonesArray;
class R3BLandPoint;
class FairVolume;



class R3BLand : public R3BDetector
{

 public:

  /** Default constructor **/
  R3BLand();


  /** Standard constructor.
   *@param name    detetcor name
   *@param active  sensitivity flag
   **/
  R3BLand(const char* name, Bool_t active);


  /** Destructor **/
  virtual ~R3BLand();


  /** Virtual method ProcessHits
   **
   ** Defines the action to be taken when a step is inside the
   ** active volume. Creates a R3BLandPoint and adds it to the
   ** collection.
   *@param vol  Pointer to the active volume
   **/
  virtual Bool_t ProcessHits(FairVolume* vol = 0);


  /** Virtual method BeginEvent
   **
   ** If verbosity level is set, print hit collection at the
   ** end of the event and resets it afterwards.
   **/

  virtual void BeginEvent();

  /** Virtual method EndOfEvent
   **
   ** If verbosity level is set, print hit collection at the
   ** end of the event and resets it afterwards.
   **/

  virtual void EndOfEvent();



  /** Virtual method Register
   **
   ** Registers the hit collection in the ROOT manager.
   **/
  virtual void Register();


  /** Accessor to the hit collection **/
  virtual TClonesArray* GetCollection(Int_t iColl) const;


  /** Virtual method Print
   **
   ** Screen output of hit collection.
   **/
  virtual void Print() const;


  /** Virtual method Reset
   **
   ** Clears the hit collection
   **/
  virtual void Reset();


  /** Virtual method CopyClones
   **
   ** Copies the hit collection with a given track index offset
   *@param cl1     Origin
   *@param cl2     Target
   *@param offset  Index offset
   **/
  virtual void CopyClones(TClonesArray* cl1, TClonesArray* cl2,
        Int_t offset);


  /** Virtaul method Construct geometry
   **
   ** Constructs the STS geometry
   **/
  virtual void ConstructGeometry();
  virtual void Initialize();
  virtual void SetSpecialPhysicsCuts(){;}

  void UseNeuLand(Double_t _paddle_length, Double_t _paddle_width, Double_t _paddle_depth, 
  Double_t _neuLAND_depth, Double_t _paddle_gap, Double_t _wrapping);


  //  void SaveGeoParams();

  private:


    /** Track information to be stored until the track leaves the
  active volume. **/
    Int_t          fTrackID;           //!  track index
    Int_t          fVolumeID;          //!  volume id
    Int_t          fCopyNo;            //!  copy no
    Int_t          fPaddleTyp;               //!  box number
    TLorentzVector fPosIn, fPosOut;    //!  position
    TLorentzVector fMomIn, fMomOut;    //!  momentum
    Double32_t     fTime;              //!  time
    Double32_t     fLength;            //!  length
    Double32_t     fELoss;             //!  energy loss
    Double32_t     fLightYield;        //!  light yield

    Int_t          fPosIndex;          //!
    TClonesArray*  fLandCollection;    //!  The hit collection
    Bool_t         kGeoSaved;          //!
    TList *flGeoPar;                   //!
    Double_t fBirkC0,fBirkC1,fBirkC2;  //!

    bool useNeuLAND;
    Double_t neuLAND_paddle_dimx;      // half of the length [cm]
    Double_t neuLAND_paddle_dimy;      // half of the width [cm]
    Double_t neuLAND_paddle_dimz;      // half of the depth [cm]
    Double_t neuLAND_depth_dim;        // total detector depth [cm]
    Double_t neuLAND_gap_dim;          // half of air gap between two scintillators [cm]
    Double_t neuLAND_wrapping_dim;        // thickness of wrapping [cm]
    
    /** Private method AddHit
     **
     ** Adds a LandPoint to the HitCollection
     **/
    R3BLandPoint* AddHit(Int_t trackID, Int_t detID, Int_t box, Int_t id1, Int_t id2,
       TVector3 posIn,
       TVector3 pos_out, TVector3 momIn,
       TVector3 momOut, Double_t time,
       Double_t length, Double_t eLoss,Double_t lightYield);

    //Constructs the NeuLand Geometry
    void ConstructNeuLandGeometry(TGeoVolume* vWorld,  TGeoMedium *Iron, TGeoMedium *BC408);

    //Construct Land Geometry
    void ConstructLandGeometry(TGeoVolume* vWorld, TGeoMedium *Iron, TGeoMedium *BC408);

    /** Private method ResetParameters
     **
     ** Resets the private members for the track parameters
     **/
    void ResetParameters();

    /** Map of MCis with fixed VolID */
    map <Int_t,Int_t> fMapMcId;


    ClassDef(R3BLand,2);

};


inline void R3BLand::ResetParameters() {
  fTrackID = fVolumeID = 0;
  fPosIn.SetXYZM(0.0, 0.0, 0.0, 0.0);
  fPosOut.SetXYZM(0.0, 0.0, 0.0, 0.0);
  fMomIn.SetXYZM(0.0, 0.0, 0.0, 0.0);
  fMomOut.SetXYZM(0.0, 0.0, 0.0, 0.0);
  fTime = fLength = fELoss = fLightYield = 0;
  fPosIndex = 0;
};


#endif 

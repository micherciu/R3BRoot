// ---------------------------------------------------------------------------------------
// -----                                                                             -----
// -----                           R3BGUI class                                      -----
// -----                            Version 0.1                                      -----
// -----                          Created @ 05.2015                                  -----
// -----                        by ISS,Bucharest Group                               -----
// -----                    e-mail: mcherciu@spacescience.ro                         -----
// -----                            version: 04                                      -----
// ---------------------------------------------------------------------------------------

#ifndef R3BGUI_H
#define R3BGUI_H

#include <FairModule.h>
#include <R3BModule.h>
#include <R3BCave.h>
#include <R3BDetector.h>
#include <R3BAsciiGenerator.h>
#include <R3BSpecificGenerator.h>
#include <R3BAladinFieldMap.h>
#include <R3BGladFieldMap.h>
#include <TFile.h>
#include <TTree.h>
#include <TGClient.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TRandom.h>
#include <TGButton.h>
#include <TGDockableFrame.h>
#include <TGFrame.h>
#include <TRootEmbeddedCanvas.h>
#include <TQObject.h>
#include <TGedFrame.h>
#include <TGTextEntry.h>
#include <TGNumberEntry.h>
#include <TGTextView.h>
#include <TRint.h>
#include <TGComboBox.h>
#include <TMap.h>
#include <Rtypes.h>                    // for Int_t, Bool_t, etc
#include <Getline.h>

#include <stddef.h>                     // for NULL
#include <string.h>                     // for strcmp, strncmp
#include <iostream>                     // for NULL
#include <list>
#include <fstream>

class TGWindow;
class TGMainFrame;
class TRootEmbeddedCanvas;
class FairLogger;
class FairRunSim;
class FairRuntimeDb;
class FairModule;
class FairPrimaryGenerator;
class FairField;
class FairBoxGenerator;
class FairAsciiGenerator;
class R3BDetector;
class R3BCave;
class R3BCalo;

class IDList {

private:
   Int_t fID;  //create widget Id(s)

public:
   IDList() : fID(0) {}
   ~IDList() {}
   Int_t GetUnID(void) { return ++fID; }
};

class R3BGui : public TGMainFrame
{

public:
/**
  * default constructor
  */
 R3BGui();
 virtual ~R3BGui();
 void Init(); // initialization of the steering class
 void SetWindowWidth(UInt_t wwidth);  // window width
 void SetWindowHeight(UInt_t wheight); // window height
 void StartWindow(); // Start Window
 void SimulationWindow(); //Simulation Window ... in progress
 void AnalysisWindow(); // Analysis Window ...not yet developed
 void RunSimulation(); // Run simulation method ...in progress

 // to process signal
 void HandleButton(Int_t id);
 void HandleMenu(Int_t id); //signal functions
 void SaveConfigurationFile();
 void SelectedButtonOpt(TGComboBox* Combo){fCombo = Combo;}
 TGComboBox* GetSelectedButtonOpt(){return fCombo;}
 void CTE1();
 void CTE2();
 Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t);
 
private:
// TFile* conf_xml_file;
// TTree* tree4xml;

// Fair variables 
 FairRunSim *run;
 FairRuntimeDb *rtdb;
// FairModule *cave;
 FairPrimaryGenerator *primGen;
 FairField *mag_type;
 FairBoxGenerator *boxGen;
 R3BAsciiGenerator *gen;
 R3BGladFieldMap *glad_type;
 R3BAladinFieldMap *aladin_type;
// R3B variables  
 R3BModule *target, *vesselcool, *mag;
 R3BDetector *xball, *calo, *tra, *dch, *tof, *mTof, *gfi, *land, *mfi, *psp, *lumon;
 
// Root variables
 TMap fDetList;
 TRootEmbeddedCanvas *fEcanvas;
 TGMainFrame* fMain;
 TGMainFrame* MainFrame1;
 TGMainFrame* MainFrame2;
 TGMainFrame* MainFrame3;
 TGPopupMenu* fMenuFile1;
 TGPopupMenu* fMenuFile2;
 TGPopupMenu* fMenuFile3;
 TGTextEntry* fCommand;      // text entry for CINT commands
 TGTextBuffer* fCommandBuf;
 TGTextView * fTextView;    // display CINT output
 Int_t visible_lines = 28;  // visible line from TGTextView
 TString     fName;         // name of temp created file
 TGComboBox* fCombo;
 TGComboBox *fComboBox1, *fComboBox2, *fComboBox3, *fComboBox4, *fComboBox5, *fComboBox6, *fComboBox7, *fComboBox8;
 TGGroupFrame *fGroupFrame1, *fGroupFrame2, *fGroupFrame3, *fGroupFrame4, *fGroupFrame5, *fGroupFrame6, *fGroupFrame7;
 TGLabel *fLabel1, *fLabel2, *fLabel3, *fLabel4, *fLabel5, *fLabel6, *fLabel7, *fLabel8,*fLabel9,*fLabel10,*fLabel11,*fLabel12,*fLabel13,*fLabel14,*fLabel15,*fLabel16;
 TGTextEntry *fTextEntry1, *fTextEntry2;
 TGNumberEntry *fNumberEntry1, *fNumberEntry2, *fNumberEntry3, *fNumberEntry4;
 TGCheckButton * fCheckButton1[17];
 IDList fIDs;
 EButtonState fState;       // button state
 Event_t* event;
 ofstream asciifile;
 
 // buffer variables
 TString fMC = "";
 Bool_t fUserPList = kFALSE;
 TString fGene = "";
 Bool_t Vis = kFALSE;
 const char* magField = "";
 Bool_t fR3BMagnet = kFALSE;
 const char* material_def = "";
 TString Target = "";
 TString OutFile = "";
 TString ParFile = "";
 Int_t scalenr = 0;
 Int_t fMeasCurrent = 0;
 Int_t runnr = 0;
 Int_t nEvents = 0;
 TString detectorList[18]={""};
 Int_t ftoggle[18];
 

public:
 UInt_t wwidth; // Width of the Frame Window
 UInt_t wheight; // Height of the Frame Window
 Bool_t fShow;  // Flag to display the start window ... just for checking

 
 ClassDef(R3BGui,0)
}; 
#endif
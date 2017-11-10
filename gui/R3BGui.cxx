// ---------------------------------------------------------------------------------------
// -----                                                                             -----
// -----                           R3BGui class                                      -----
// -----                            Version 0.1                                      -----
// -----                          Created @ 05.2015                                  -----
// -----                        by ISS,Bucharest Group                               -----
// -----                    e-mail: mcherciu@spacescience.ro                         -----
// -----                            version: 04                                     -----
// ---------------------------------------------------------------------------------------


// test class for graphical interface
#include "R3BGui.h"

// Fairroot include
#include <FairLogger.h>
#include <FairRunSim.h>
#include <FairModule.h>
#include <FairPrimaryGenerator.h>
#include <FairBoxGenerator.h>
#include <FairParRootFileIo.h>
// R3BRoot include

#include <R3BCave.h>
#include <R3BTarget.h>
#include <R3BVacVesselCool.h>
#include <R3BMagnet.h>
#include <R3BGladMagnet.h>
#include <R3BDetector.h>
#include <R3BXBall.h>
#include <R3BCalo.h>
#include <R3BTra.h>
#include <R3BSTaRTra.h>
#include <R3BDch.h>
#include <R3BTof.h>
#include <R3BmTof.h>
#include <R3BGfi.h>
#include <R3BLand.h>
#include <R3BMfi.h>
#include <R3BPsp.h>
#include <R3BAladinFieldMap.h>
#include <R3BGladFieldMap.h>
#include <R3BFieldPar.h>

// ROOT include
#include <TROOT.h>
#include <TClass.h>
#include <TApplication.h>
#include <TVirtualX.h>
#include <TVirtualPadEditor.h>
#include <TVirtualMC.h>
#include <TGResourcePool.h>
#include <TGListBox.h>
#include <TGListTree.h>
#include <TGFSContainer.h>
#include <TGClient.h>
#include <TGFrame.h>
#include <TGIcon.h>
#include <TGLabel.h>
#include <TGButton.h>
#include <TGButtonGroup.h>
#include <TGTextEntry.h>
#include <TGNumberEntry.h>
#include <TGMsgBox.h>
#include <TGMenu.h>
#include <TGCanvas.h>
#include <TGComboBox.h>
#include <TGTab.h>
#include <TGSlider.h>
#include <TGDoubleSlider.h>
#include <TGFileDialog.h>
#include <TGTextEdit.h>
#include <TGShutter.h>
#include <TGProgressBar.h>
#include <TGColorSelect.h>
#include <RQ_OBJECT.h>
#include <TRootEmbeddedCanvas.h>
#include <TCanvas.h>
#include <TColor.h>
#include <TH1.h>
#include <TH2.h>
#include <TRandom.h>
#include <TSystem.h>
#include <TSystemDirectory.h>
#include <TEnv.h>
#include <TFile.h>
#include <TXMLFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TKey.h>
#include <TGDockableFrame.h>
#include <TGFontDialog.h>
#include <TGRedirectOutputGuard.h>
#include <KeySymbols.h>
#include "TStopwatch.h"
#include "TMap.h"

#include <stddef.h>                     // for NULL
#include <string.h>                     // for strcmp, strncmp
#include <iostream>                     // for NULL
#include <list>
#include <fstream>

using namespace std;
using std::cout;
using std::endl;
using std::list;

enum ECommandIdentifiers {
   M_FILE_OPEN,
   M_FILE_SAVE,
   M_FILE_SAVEAS,
   M_FILE_IMPORT,
   M_FILE_EXPORT,
   M_FILE_PRINT,
   M_FILE_PRINTSETUP,
   M_FILE_EXIT,

   M_HELP_CONTENTS,
   M_HELP_SEARCH,
   M_HELP_ABOUT,

   ID_1,
   ID_2,
   ID_3,
   ID_4,
   ID_5,
   ID_6,
   ID_7,
   ID_8,
   ID_9,
   ID_10,
   ID_11,
   ID_12,
   ID_13,
   ID_14,
   ID_15,
   ID_16,
   ID_17,
   ID_18,
   ID_19,
   ID_20,
   ID_21,
   ID_22,
   ID_23,
   ID_24,
   ID_25,
   ID_26,
   ID_27,
   ID_28,
   ID_29,
   ID_30,
   ID_31,
   ID_32,
   ID_33,
   ID_34,
   ID_35,
   ID_36,
   ID_37,
   ID_38,
   ID_39,
   ID_40,
   ID_41,
   ID_42,
   ID_43,
   ID_44
 
};

const char *fnewtypes[] = { "All files",     "*",
                            "ROOT files",    "*.root",
                            "XML files",   "*.xml",
                            "ASCII files",    "*.txt",
                            0,               0 };

R3BGui::R3BGui()
:fShow(kTRUE)
{
// This is the constructor


} 

R3BGui::~R3BGui() 
{
delete fComboBox1, fComboBox2, fComboBox3, fComboBox4, fComboBox5, fComboBox6, fComboBox7, fComboBox8;

asciifile.close();

// This is the destructor
Cleanup();
}


void R3BGui::Init()
{	
	
  if(fShow)
  {
	StartWindow();
  }
  else
  {
	LOG(INFO)<<"The display is not activated ... "<<FairLogger::endl;    
  }  
}

// Within this window the user can proceed to Simulation or Analysis task

void R3BGui::StartWindow()
{
	
// -----------------------------------------------------------------------------------------------------------------------------------------------	
//	wwidth = gClient->GetDisplayWidth();
//	wheight = gClient->GetDisplayWidth();
	wwidth = 850;
	wheight =400;

	 // main frame
	   MainFrame1 = new TGMainFrame(gClient->GetRoot(),wwidth,wheight, kMainFrame | kFixedWidth | kFixedHeight);
	   MainFrame1->SetName("MainFrame1");
	   
//-------------------------- Menu Bar ------------------------------------------------------------------------------------  
	   TGLayoutHints* fMenuBarLayout1 = new TGLayoutHints(kLHintsTop | kLHintsExpandX, 2, 2, 2, 5);
	   TGLayoutHints* fMenuBarItemLayout1 = new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 4, 0, 0);
	   TGLayoutHints* fMenuBarHelpLayout1 = new TGLayoutHints(kLHintsTop | kLHintsRight);	   
/*	   
	   TGMenuBar* fMenuBar1 = new TGMenuBar(MainFrame1, MainFrame1->GetWidth(), 50, kHorizontalFrame | kFitWidth);	   
	   	   
// Create menubar and popup menus. The hint objects are used to place
// and group the different menu widgets with respect to eachother.
	   	   
	   fMenuFile1 = new TGPopupMenu(gClient->GetRoot());
	   fMenuFile1->AddEntry("&Open...", M_FILE_OPEN);
	   fMenuFile1->AddEntry("&Save", M_FILE_SAVE);
	   fMenuFile1->AddEntry("S&ave as...", M_FILE_SAVEAS);
	   fMenuFile1->AddSeparator();
	   fMenuFile1->AddEntry("&Print", M_FILE_PRINT);
	   fMenuFile1->AddEntry("P&rint setup...", M_FILE_PRINTSETUP);
	   fMenuFile1->AddSeparator();
	   fMenuFile1->AddEntry("E&xit", M_FILE_EXIT);
	   fMenuFile1->DisableEntry(M_FILE_SAVEAS);
	   fMenuFile1->HideEntry(M_FILE_PRINT);        
	   fMenuFile1->Connect("Activated(Int_t)", "R3BGui", MainFrame1,"HandleMenu(Int_t)");	   
	   fMenuBar1->AddPopup("&File", fMenuFile1, fMenuBarItemLayout1);
	   
	   MainFrame1->AddFrame(fMenuBar1, fMenuBarLayout1);	   
*/	   
//------------------------------------------------------------------------------------------------------------------------
// main frame
   	   TGVerticalFrame *fVMainFrame1 = new TGVerticalFrame(MainFrame1, MainFrame1->GetWidth(), MainFrame1->GetHeight(), kVerticalFrame | kLHintsCenterX);
   	   fVMainFrame1->SetName("fVMainFrame1");

	   TGFont *ufont;         // will reflect user font changes
	   ufont = gClient->GetFont("-*-times-bold-i-*-*-34-*-*-*-*-*-*-*");
	   TGGC   *uGC;           // will reflect user GC changes

// graphics context changes
	   GCValues_t val1;
	   val1.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
	   gClient->GetColorByName("#ff0000",val1.fForeground);
	   gClient->GetColorByName("#e0e0e0",val1.fBackground);
	   val1.fFillStyle = kFillSolid;
	   val1.fFont = ufont->GetFontHandle();
	   val1.fGraphicsExposures = kFALSE;
	   uGC = gClient->GetGC(&val1, kTRUE);

	   ULong_t ucolor;        // will reflect user color changes
	   gClient->GetColorByName("#d4cf87",ucolor);
	   fLabel1 = new TGLabel(fVMainFrame1,"R3BROOT",uGC->GetGC(),ufont->GetFontStruct(),kChildFrame,ucolor);
	   fLabel1->SetTextJustify(36);
	   fLabel1->SetMargins(0,0,0,0);
	   fLabel1->SetWrapLength(-1);
	   fVMainFrame1->AddFrame(fLabel1, new TGLayoutHints(kLHintsTop | kLHintsCenterX ,2,2,2,2));
	   fLabel1->MoveResize(300,50,200,50);

// graphics context changes
	   ufont = gClient->GetFont("-*-times-bold-i-*-*-20-*-*-*-*-*-*-*");
	   GCValues_t val2;
	   val2.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
	   gClient->GetColorByName("#ff0000",val2.fForeground);
	   gClient->GetColorByName("#e0e0e0",val2.fBackground);
	   val2.fFillStyle = kFillSolid;
	   val2.fFont = ufont->GetFontHandle();
	   val2.fGraphicsExposures = kFALSE;
	   uGC = gClient->GetGC(&val2, kTRUE);

	   fLabel2 = new TGLabel(fVMainFrame1,"Interface for Simulation and Analysis",uGC->GetGC(),ufont->GetFontStruct(),kChildFrame,ucolor);
	   fLabel2->SetTextJustify(36);
	   fLabel2->SetMargins(0,0,0,0);
	   fLabel2->SetWrapLength(-1);
	   fVMainFrame1->AddFrame(fLabel2, new TGLayoutHints(kLHintsCenterX | kLHintsExpandX,2,2,2,2));
	   fLabel2->MoveResize(200,100,400,50);
	   
// new orizontal frame
	   	   	   
	   TGHorizontalFrame *fHBaseFrame2 = new TGHorizontalFrame(MainFrame1, MainFrame1->GetWidth(),MainFrame1->GetHeight(), kFitWidth);
	   fHBaseFrame2->SetName("fHBaseFrame2");
	   
	   TGPictureButton *fPictureButton1 = new TGPictureButton(fHBaseFrame2,gClient->GetPicture("r3b_simulation.png"));
	   fPictureButton1->Connect("Clicked()","R3BGui",this,"SimulationWindow()");
	   fPictureButton1->Connect("Clicked()","R3BGui",MainFrame1,"CloseWindow()");
	   fHBaseFrame2->AddFrame(fPictureButton1, new TGLayoutHints(kLHintsTop | kFitWidth | kFitHeight,2,2,2,2));

	   TGPictureButton *fPictureButton2 = new TGPictureButton(fHBaseFrame2,gClient->GetPicture("r3b_analysis.png"));
	   fPictureButton2->Connect("Clicked()","R3BGui",this,"AnalysisWindow()");
	   fPictureButton2->Connect("Clicked()","R3BGui",MainFrame1,"CloseWindow()");
	   fHBaseFrame2->AddFrame(fPictureButton2, new TGLayoutHints(kLHintsTop | kFitWidth | kFitHeight,2,2,2,2));
	   fHBaseFrame2->MoveResize(0,150,850,250);
// add frames to the Start Window

//	   MainFrame1->AddFrame(fVMainFrame1, new TGLayoutHints(kLHintsCenterX | kLHintsTop | kLHintsExpandX,2, 0, 2, 2));
	   MainFrame1->AddFrame(fVMainFrame1, new TGLayoutHints(kLHintsCenterX | kLHintsTop,1,1,1,1));
	   MainFrame1->AddFrame(fHBaseFrame2, new TGLayoutHints(kLHintsCenterX | kLHintsBottom,2,0,2,2));

	   
	   
	   MainFrame1->SetMWMHints(kMWMDecorAll, kMWMFuncAll, kMWMInputModeless);
           MainFrame1->SetWMSize(MainFrame1->GetWidth(), MainFrame1->GetHeight());
           MainFrame1->SetWMSizeHints(MainFrame1->GetWidth(), MainFrame1->GetHeight(), MainFrame1->GetWidth(), MainFrame1->GetHeight(), 0, 0);

           MainFrame1->MapSubwindows();
           MainFrame1->Resize(MainFrame1->GetDefaultSize());
           MainFrame1->MapWindow();
           
           
}

void R3BGui::SimulationWindow()
{

	
	   MainFrame2 = new TGMainFrame(gClient->GetRoot(),600,800,kMainFrame | kVerticalFrame | kFixedHeight);
	   MainFrame2->SetName("MainFrame2");
//	   MainFrame2->SetLayoutBroken(kTRUE);
//	   MainFrame2->CenterOnParent();
	   
//-------------------------- Menu Bar ------------------------------------------------------------------------------------  
	   	   TGLayoutHints* fMenuBarLayout2 = new TGLayoutHints(kLHintsTop | kLHintsExpandX, 2, 2, 2, 5);
	   	   TGLayoutHints* fMenuBarItemLayout2 = new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 4, 0, 0);
	   	   TGLayoutHints* fMenuBarHelpLayout2 = new TGLayoutHints(kLHintsTop | kLHintsRight);	   

	   	   TGMenuBar* fMenuBar2 = new TGMenuBar(MainFrame2, MainFrame2->GetWidth(), 20, kFitWidth | kFitHeight);
	   	   	   
// Create menubar and popup menus. The hint objects are used to place
// and group the different menu widgets with respect to eachother.
	   	   	   
	   	   fMenuFile2 = new TGPopupMenu(gClient->GetRoot());
	   	   fMenuFile2->AddEntry("&Open...", M_FILE_OPEN);
	   	   fMenuFile2->AddEntry("&Save", M_FILE_SAVE);
	   	   fMenuFile2->AddEntry("S&ave as...", M_FILE_SAVEAS);	   	   
	   	   fMenuFile2->AddSeparator();
	   	   fMenuFile2->AddEntry("E&xit", M_FILE_EXIT);        
	   	   fMenuFile2->Connect("Activated(Int_t)", "R3BGui", MainFrame2,"HandleMenu(Int_t)");	   
	   	   fMenuBar2->AddPopup("&File", fMenuFile2, fMenuBarItemLayout2);
	   	   
	   	   MainFrame2->AddFrame(fMenuBar2, fMenuBarLayout2);
	   	   

	   	   
//-------------------------- Composite Frame ------------------------------------------------------------------------------------  	   	   
	   
	   // composite frame
	   TGCompositeFrame *fCompFrame1 = new TGCompositeFrame(MainFrame2,MainFrame2->GetWidth(),MainFrame2->GetHeight(), kVerticalFrame | kRaisedFrame | kFitWidth | kFitHeight);
	   fCompFrame1->SetName("fCompFrame1");
	   fCompFrame1->SetLayoutBroken(kTRUE);
	   

	   // "Monte Carlo Options" group frame
	   fGroupFrame1 = new TGGroupFrame(fCompFrame1,"Monte Carlo Options", kHorizontalFrame | kFitWidth | kFitHeight);
	   fGroupFrame1->SetLayoutBroken(kTRUE);

	   ULong_t ucolor;        // will reflect user color changes
	   gClient->GetColorByName("#ffffff",ucolor);

// Choose Monte Carlo transport engine
	   
	   fLabel3 = new TGLabel(fGroupFrame1,"Transport Engine");
	   fLabel3->SetTextJustify(36);
	   fLabel3->SetMargins(0,0,0,0);
	   fLabel3->SetWrapLength(-1);
	   fGroupFrame1->AddFrame(fLabel3, new TGLayoutHints(kLHintsLeft | kLHintsTop | kFitWidth | kFitHeight,2,2,2,2));
	   fLabel3->MoveResize(8,32,120,16);
	   
	   // combo box
	   fComboBox1 = new TGComboBox(fGroupFrame1,"",fIDs.GetUnID(), kHorizontalFrame | kSunkenFrame | kDoubleBorder | kOwnBackground | kFitWidth | kFitHeight);
	   fComboBox1->AddEntry("Geant 4",ID_1);
	   fComboBox1->AddEntry("Geant 3",ID_2);
	   fComboBox1->Connect("Selected(Int_t)", "R3BGui", this, "HandleButton(Int_t)");
	   fComboBox1->Select(-1);
	   fGroupFrame1->AddFrame(fComboBox1, new TGLayoutHints(kLHintsLeft | kLHintsTop | kFitWidth | kFitHeight,2,2,2,2));
	   fComboBox1->MoveResize(8,48,128,20);
	   
// Choose Phyiscs List option 

	   fLabel4 = new TGLabel(fGroupFrame1,"User Physics List");
	   fLabel4->SetTextJustify(36);
	   fLabel4->SetMargins(0,0,0,0);
	   fLabel4->SetWrapLength(-1);
	   fGroupFrame1->AddFrame(fLabel4, new TGLayoutHints(kLHintsLeft | kLHintsTop | kFitWidth | kFitHeight,2,2,2,2));
	   fLabel4->MoveResize(168,32,112,16);
	   	   
	   // combo box
	   fComboBox2 = new TGComboBox(fGroupFrame1,"",fIDs.GetUnID(),kHorizontalFrame | kSunkenFrame | kDoubleBorder | kOwnBackground | kFitWidth | kFitHeight);
	   fComboBox2->AddEntry("ON",ID_3);
	   fComboBox2->AddEntry("OFF",ID_4);
	   fComboBox2->Select(-1);
	   fGroupFrame1->AddFrame(fComboBox2, new TGLayoutHints(kLHintsLeft | kLHintsTop | kFitWidth | kFitHeight,2,2,2,2));
	   fComboBox2->MoveResize(160,48,128,20);
	   fComboBox2->Connect("Selected(Int_t)", "R3BGui", this, "HandleButton(Int_t)");
	   
// Choose Primary Generator type

	   fLabel5 = new TGLabel(fGroupFrame1,"Primary Generator");
	   fLabel5->SetTextJustify(36);
	   fLabel5->SetMargins(0,0,0,0);
	   fLabel5->SetWrapLength(-1);
	   fGroupFrame1->AddFrame(fLabel5, new TGLayoutHints(kLHintsLeft | kLHintsTop | kFitWidth | kFitHeight,2,2,2,2));
	   fLabel5->MoveResize(8,88,120,16);
	   
	   // combo box
	   fComboBox3 = new TGComboBox(fGroupFrame1,"",fIDs.GetUnID(),kHorizontalFrame | kSunkenFrame | kDoubleBorder | kOwnBackground | kFitWidth | kFitHeight);
	   fComboBox3->AddEntry("box ",ID_5);
	   fComboBox3->AddEntry("ascii ",ID_6);
	   fComboBox3->AddEntry("r3b ",ID_7);
	   fComboBox3->Select(-1);
	   fGroupFrame1->AddFrame(fComboBox3, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	   fComboBox3->MoveResize(8,104,128,20);
	   fComboBox3->Connect("Selected(Int_t)", "R3BGui", this, "HandleButton(Int_t)");

// Choose to Activate Particles Trajectory Visualization to the Root output	   
	   fLabel6 = new TGLabel(fGroupFrame1,"Trajectory Visualization");
	   fLabel6->SetTextJustify(36);
	   fLabel6->SetMargins(0,0,0,0);
	   fLabel6->SetWrapLength(-1);
	   fGroupFrame1->AddFrame(fLabel6, new TGLayoutHints(kLHintsLeft | kLHintsTop | kFitWidth | kFitHeight,2,2,2,2));
	   fLabel6->MoveResize(144,88,144,16);

	   // combo box
	   fComboBox4 = new TGComboBox(fGroupFrame1,"",fIDs.GetUnID(),kHorizontalFrame | kSunkenFrame | kDoubleBorder | kOwnBackground | kFitWidth | kFitHeight);
	   fComboBox4->AddEntry("ON ",ID_8);
	   fComboBox4->AddEntry("OFF ",ID_9);
	   fComboBox4->Select(0);
	   fGroupFrame1->AddFrame(fComboBox4, new TGLayoutHints(kLHintsLeft | kLHintsTop | kFitWidth | kFitHeight,2,2,2,2));
	   fComboBox4->MoveResize(160,104,126,20);
	   fComboBox4->Connect("Selected(Int_t)", "R3BGui", this, "HandleButton(Int_t)");
	   
	   fGroupFrame1->SetLayoutManager(new TGVerticalLayout(fGroupFrame1));
	   fCompFrame1->AddFrame(fGroupFrame1, new TGLayoutHints(kLHintsLeft | kLHintsTop | kFitWidth | kFitHeight,2,2,2,2));
	   fGroupFrame1->MoveResize(8,40,296,144);

// "Magnetif Field Options" group frame
	   
	   fGroupFrame2 = new TGGroupFrame(fCompFrame1,"Magnetif Field Options");
	   fGroupFrame2->SetLayoutBroken(kTRUE);

// Choose to the Magnet Type for the experiment 
	   
	   fLabel7 = new TGLabel(fGroupFrame2,"Magnet Type");
	   fLabel7->SetTextJustify(36);
	   fLabel7->SetMargins(0,0,0,0);
	   fLabel7->SetWrapLength(-1);
	   fGroupFrame2->AddFrame(fLabel7, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	   fLabel7->MoveResize(8,16,120,16);

	   fComboBox6 = new TGComboBox(fGroupFrame2,"",fIDs.GetUnID(),kHorizontalFrame | kSunkenFrame | kDoubleBorder | kOwnBackground | kFitWidth | kFitHeight);
	   fComboBox6->AddEntry("ALADIN",ID_10);
	   fComboBox6->AddEntry("GLAD",ID_11);
	   fComboBox6->AddEntry("NULL",ID_44);
	   fComboBox6->Select(-1);
	   fGroupFrame2->AddFrame(fComboBox6, new TGLayoutHints(kLHintsNormal));
	   fComboBox6->MoveResize(8,32,128,20);
	   fComboBox6->Connect("Selected(Int_t)", "R3BGui", this, "HandleButton(Int_t)");
	   

// Chose to activate or not the magnetic field
	   
	   fLabel8 = new TGLabel(fGroupFrame2,"Magnetic Field");
	   fLabel8->SetTextJustify(36);
	   fLabel8->SetMargins(0,0,0,0);
	   fLabel8->SetWrapLength(-1);
	   fGroupFrame2->AddFrame(fLabel8, new TGLayoutHints(kLHintsLeft | kLHintsTop | kFitWidth | kFitHeight,2,2,2,2));
	   fLabel8->MoveResize(160,16,112,16);

	   // combo box
	   fComboBox5 = new TGComboBox(fGroupFrame2,"",fIDs.GetUnID(),kHorizontalFrame | kSunkenFrame | kDoubleBorder | kOwnBackground | kFitWidth | kFitHeight);
	   fComboBox5->AddEntry("ON ",ID_12);
	   fComboBox5->AddEntry("OFF ",ID_13);
	   fComboBox5->Select(-1);
	   fGroupFrame2->AddFrame(fComboBox5, new TGLayoutHints(kLHintsLeft | kLHintsTop | kFitWidth | kFitHeight,2,2,2,2));
	   fComboBox5->MoveResize(152,32,128,20);
	   fComboBox5->Connect("Selected(Int_t)", "R3BGui", this, "HandleButton(Int_t)");
	   
// Choose to define the Scale for Magnetic Field

	   fLabel9 = new TGLabel(fGroupFrame2,"Scale");
	   fLabel9->SetTextJustify(36);
	   fLabel9->SetMargins(0,0,0,0);
	   fLabel9->SetWrapLength(-1);
	   fGroupFrame2->AddFrame(fLabel9, new TGLayoutHints(kLHintsLeft | kLHintsTop | kFitWidth | kFitHeight,2,2,2,2));
	   fLabel9->MoveResize(176,56,62,16);

	   fNumberEntry1 = new TGNumberEntry(fGroupFrame2, (Double_t) 0,18,ID_39,(TGNumberFormat::EStyle) 5);
	   fGroupFrame2->AddFrame(fNumberEntry1, new TGLayoutHints(kLHintsLeft | kLHintsTop | kFitWidth | kFitHeight,2,2,2,2));
	   fNumberEntry1->MoveResize(152,72,128,20);
	   fNumberEntry1->SetState(kFALSE);
	   fNumberEntry1->Associate(this);

// Choose the Meas Curent	   

	   fLabel10 = new TGLabel(fGroupFrame2,"Meas Current");
  	   fLabel10->SetTextJustify(36);
   	   fLabel10->SetMargins(0,0,0,0);
   	   fLabel10->SetWrapLength(-1);
   	   fGroupFrame2->AddFrame(fLabel10, new TGLayoutHints(kLHintsLeft | kLHintsTop | kFitWidth | kFitHeight,2,2,2,2));
   	   fLabel10->MoveResize(8,56,120,16);	   
	   
	   fNumberEntry2 = new TGNumberEntry(fGroupFrame2, (Double_t) 0,18,ID_40,(TGNumberFormat::EStyle) 5);
	   fGroupFrame2->AddFrame(fNumberEntry2, new TGLayoutHints(kLHintsLeft | kLHintsTop | kFitWidth | kFitHeight,2,2,2,2));
	   fNumberEntry2->MoveResize(8,72,128,20);
	   fNumberEntry2->Associate(this);
	   
	   fGroupFrame2->SetLayoutManager(new TGVerticalLayout(fGroupFrame2));
	   fCompFrame1->AddFrame(fGroupFrame2, new TGLayoutHints(kLHintsLeft | kLHintsTop | kFitWidth | kFitHeight,2,2,2,2));
	   fGroupFrame2->MoveResize(8,184,296,104);

// "Detector Options" group frame
	   fGroupFrame3 = new TGGroupFrame(fCompFrame1,"Detector Options");
	   fGroupFrame3->SetLayoutBroken(kTRUE);

// Choose what detectors you want to activate for the simulation

	   fLabel11 = new TGLabel(fGroupFrame3,"Detector Selection");
	   fLabel11->SetTextJustify(36);
	   fLabel11->SetMargins(0,0,0,0);
	   fLabel11->SetWrapLength(-1);
	   fGroupFrame3->AddFrame(fLabel11, new TGLayoutHints(kLHintsLeft | kLHintsTop | kFitWidth | kFitHeight,2,2,2,2));
	   fLabel11->MoveResize(8,20,128,15);
	   
	   TGVButtonGroup* fButtonGroup1 = new TGVButtonGroup(fGroupFrame3, "");
	      
//	      fCheckButton1[1] = new TGCheckButton(fButtonGroup1, new TGHotString("ALADIN"),ID_22);
//	      fCheckButton1[1]->Associate(this);
	      fCheckButton1[2] = new TGCheckButton(fButtonGroup1, new TGHotString("CRYSTALBALL"),ID_23);
	      fCheckButton1[2]->Associate(this);
	      fCheckButton1[3] = new TGCheckButton(fButtonGroup1, new TGHotString("CALIFA"),ID_24);
	      fCheckButton1[3]->Associate(this);
	      fCheckButton1[4] = new TGCheckButton(fButtonGroup1, new TGHotString("DCH"),ID_25);
	      fCheckButton1[4]->Associate(this);
	      fCheckButton1[5] = new TGCheckButton(fButtonGroup1, new TGHotString("GFI"),ID_26);
	      fCheckButton1[5]->Associate(this);
//	      fCheckButton1[6] = new TGCheckButton(fButtonGroup1, new TGHotString("GLAD"),ID_27);
//	      fCheckButton1[6]->Associate(this);
	      fCheckButton1[7] = new TGCheckButton(fButtonGroup1, new TGHotString("LAND"),ID_28);
	      fCheckButton1[7]->Associate(this);
	      fCheckButton1[8] = new TGCheckButton(fButtonGroup1, new TGHotString("LUMON"),ID_29);
	      fCheckButton1[8]->Associate(this);
	      fCheckButton1[9] = new TGCheckButton(fButtonGroup1, new TGHotString("MFI"),ID_30);
	      fCheckButton1[9]->Associate(this);
	      fCheckButton1[10] = new TGCheckButton(fButtonGroup1, new TGHotString("MTOF"),ID_31);
	      fCheckButton1[10]->Associate(this);
	      fCheckButton1[11] = new TGCheckButton(fButtonGroup1, new TGHotString("PSP"),ID_32);
	      fCheckButton1[11]->Associate(this);
	      fCheckButton1[12] = new TGCheckButton(fButtonGroup1, new TGHotString("SCINTNEULAND"),ID_33);
	      fCheckButton1[12]->Associate(this);
	      fCheckButton1[13] = new TGCheckButton(fButtonGroup1, new TGHotString("STaRTrack"),ID_34);
	      fCheckButton1[13]->Associate(this);
	      fCheckButton1[14] = new TGCheckButton(fButtonGroup1, new TGHotString("TARGET"),ID_35);
	      fCheckButton1[14]->Associate(this);
	      fCheckButton1[15] = new TGCheckButton(fButtonGroup1, new TGHotString("TOF"),ID_36);
	      fCheckButton1[15]->Associate(this);
	      fCheckButton1[16] = new TGCheckButton(fButtonGroup1, new TGHotString("TRACKER"),ID_37);
	      fCheckButton1[16]->Associate(this);
 	      fCheckButton1[17] = new TGCheckButton(fButtonGroup1, new TGHotString("VACVESSELCOOL"),ID_38);
 	      fCheckButton1[17]->Associate(this); 	      
 
	   fButtonGroup1->Show();
	   fGroupFrame3->AddFrame(fButtonGroup1, new TGLayoutHints(kLHintsLeft | kLHintsTop | kFitWidth | kFitHeight,2,2,2,2));
	   fButtonGroup1->MoveResize(10,20,128,310);
	   gClient->GetColorByName("#ffffff",ucolor);

// Choose the media file for materials definition
	   
	   fLabel12 = new TGLabel(fGroupFrame3,"Material Definition");
	   fLabel12->SetTextJustify(36);
	   fLabel12->SetMargins(0,0,0,0);
	   fLabel12->SetWrapLength(-1);
	   fGroupFrame3->AddFrame(fLabel12, new TGLayoutHints(kLHintsLeft | kLHintsTop | kFitWidth | kFitHeight,2,2,2,2));
	   fLabel12->MoveResize(160,24,128,16);

	   // combo box
	   fComboBox7 = new TGComboBox(fGroupFrame3,"",fIDs.GetUnID(),kHorizontalFrame | kSunkenFrame | kDoubleBorder | kOwnBackground | kFitWidth | kFitHeight);
	   fComboBox7->AddEntry("MEDIA-R3B ",ID_14);
	   fComboBox7->AddEntry("NULL ",ID_15);
	   fComboBox7->Select(-1);
	   fGroupFrame3->AddFrame(fComboBox7, new TGLayoutHints(kLHintsLeft | kLHintsTop | kFitWidth | kFitHeight,2,2,2,2));
	   fComboBox7->MoveResize(160,40,128,20);
	   fComboBox7->Connect("Selected(Int_t)", "R3BGui", this, "HandleButton(Int_t)");
// Choose the Taget Type for the simulation	   
	   
	   fLabel13 = new TGLabel(fGroupFrame3,"Target Selection");
	   fLabel13->SetTextJustify(36);
	   fLabel13->SetMargins(0,0,0,0);
	   fLabel13->SetWrapLength(-1);
	   fGroupFrame3->AddFrame(fLabel13, new TGLayoutHints(kLHintsLeft | kLHintsTop | kFitWidth | kFitHeight,2,2,2,2));
	   fLabel13->MoveResize(160,80,120,16);
	   
	   // combo box
	   fComboBox8 = new TGComboBox(fGroupFrame3,"",fIDs.GetUnID(),kHorizontalFrame | kSunkenFrame | kDoubleBorder | kOwnBackground | kFitWidth | kFitHeight);
	   fComboBox8->AddEntry("LeadTarget ",ID_16);
	   fComboBox8->AddEntry("Parafin-ODeg ",ID_17);
           fComboBox8->AddEntry("Parafin-45Deg ",ID_18);
           fComboBox8->AddEntry("LiH ",ID_19);
           fComboBox8->Resize(128,20);
           fComboBox8->Select(-1);
           fGroupFrame3->AddFrame(fComboBox8, new TGLayoutHints(kLHintsLeft | kLHintsTop | kFitWidth | kFitHeight,2,2,2,2));
           fComboBox8->MoveResize(160,96,128,20);
//---------------------------------------------------------------------------------------------------------------------------------   fComboBox8->MoveResize(160,96,128,20);
	   fComboBox8->Connect("Selected(Int_t)", "R3BGui", this, "HandleButton(Int_t)");
//------------------------------------------------------------------------------------------------------------------------------------------------	   
	   fGroupFrame3->SetLayoutManager(new TGVerticalLayout(fGroupFrame3));
	   fGroupFrame3->Resize(296,284);
	   fCompFrame1->AddFrame(fGroupFrame3, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY | kFitWidth | kFitHeight));
	   fGroupFrame3->MoveResize(8,288,296,375);
 

// "Events & Runs" group frame

	   fGroupFrame4 = new TGGroupFrame(fCompFrame1,"Events & Runs");
	   fGroupFrame4->SetLayoutBroken(kTRUE);

// Choose the Runs Number	   
	   
	   fLabel14 = new TGLabel(fGroupFrame4,"No. Runs");
	   fLabel14->SetTextJustify(36);
	   fLabel14->SetMargins(0,0,0,0);
	   fLabel14->SetWrapLength(-1);
	   fGroupFrame4->AddFrame(fLabel14, new TGLayoutHints(kLHintsLeft | kLHintsTop | kFitWidth | kFitHeight,2,2,2,2));
	   fLabel14->MoveResize(16,24,62,15);
	   
	   fNumberEntry3 = new TGNumberEntry(fGroupFrame4, (Double_t) 0,11,ID_41,(TGNumberFormat::EStyle) 5);
	   fGroupFrame4->AddFrame(fNumberEntry3, new TGLayoutHints(kLHintsLeft | kLHintsTop | kFitWidth | kFitHeight,2,2,2,2));
	   fNumberEntry3->MoveResize(8,48,88,15);
	   fNumberEntry3->SetState(kFALSE);

// Choose the Events Number

	   fLabel15 = new TGLabel(fGroupFrame4,"No. Events");
	   fLabel15->SetTextJustify(36);
	   fLabel15->SetMargins(0,0,0,0);
	   fLabel15->SetWrapLength(-1);
	   fGroupFrame4->AddFrame(fLabel15, new TGLayoutHints(kLHintsLeft | kLHintsTop | kFitWidth | kFitHeight,2,2,2,2));
	   fLabel15->MoveResize(112,24,62,15);

	   fNumberEntry4 = new TGNumberEntry(fGroupFrame4, (Double_t) 0,10,ID_42, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 99999);
	   fGroupFrame4->AddFrame(fNumberEntry4, new TGLayoutHints(kLHintsLeft | kLHintsTop | kFitWidth | kFitHeight,2,2,2,2));
	   fNumberEntry4->MoveResize(112,48,77,15);


	   fGroupFrame4->SetLayoutManager(new TGVerticalLayout(fGroupFrame4));
	   fGroupFrame4->Resize(200,80);
	   fCompFrame1->AddFrame(fGroupFrame4, new TGLayoutHints(kLHintsLeft | kLHintsTop | kFitWidth | kFitHeight,2,2,2,2));
	   fGroupFrame4->MoveResize(336,545,200,75);
	   
	   TGFont *ufont; 
	   ufont = gClient->GetFont("-*-times-bold-i-*-*-20-*-*-*-*-*-*-*");

// graphics context changes
  	   GCValues_t val6;
  	   val6.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
   	   gClient->GetColorByName("#000000",val6.fForeground);
   	   gClient->GetColorByName("#e0e0e0",val6.fBackground);
   	   val6.fFillStyle = kFillSolid;
   	   val6.fFont = ufont->GetFontHandle();
   	   val6.fGraphicsExposures = kFALSE;
   	   TGGC   *uGC;
   	   uGC = gClient->GetGC(&val6, kTRUE);
	   
	   TGTextButton *fTextButton3 = new TGTextButton(fCompFrame1,"Save Configuration File",ID_43,uGC->GetGC(),ufont->GetFontStruct());
	   fTextButton3->SetTextJustify(10);
	   fTextButton3->SetMargins(0,0,0,0);
	   fTextButton3->SetWrapLength(-1);
	   fCompFrame1->AddFrame(fTextButton3, new TGLayoutHints(kLHintsLeft | kLHintsTop | kFitWidth | kFitHeight,2,2,2,2));
	   fTextButton3->MoveResize(336,615,200,30); 	   
	   fTextButton3->Connect("Clicked()","R3BGui",this,"SaveConfigurationFile()");
//---------------------------------------------------------------------------------------------------------------------------------------------------
	   
// "ROOT Files " group frame

	   fGroupFrame5 = new TGGroupFrame(fCompFrame1,"ROOT Files ");
	   fGroupFrame5->SetLayoutBroken(kTRUE);

//	   TGFont *ufont;         // will reflect user font changes
	   ufont = gClient->GetFont("-*-times-medium-i-*-*-12-*-*-*-*-*-*-*");

	   // graphics context changes
	   GCValues_t val4;
	   val4.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
	   gClient->GetColorByName("#000000",val4.fForeground);
	   gClient->GetColorByName("#e0e0e0",val4.fBackground);
	   val4.fFillStyle = kFillSolid;
	   val4.fFont = ufont->GetFontHandle();
	   val4.fGraphicsExposures = kFALSE;
//	   TGGC   *uGC;           // will reflect user GC changes
	   uGC = gClient->GetGC(&val4, kTRUE);
	   
// will reflect user color changes
	   gClient->GetColorByName("#cccccc",ucolor);
	   fTextEntry1 = new TGTextEntry(fGroupFrame5, new TGTextBuffer(31), ID_20, uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kDoubleBorder | kOwnBackground,ucolor);
	   fTextEntry1->SetMaxLength(4096);
	   fTextEntry1->SetAlignment(kTextLeft);
	   fTextEntry1->SetText("Please set the output file ... ex. r3bsim.root");
	   fGroupFrame5->AddFrame(fTextEntry1, new TGLayoutHints(kLHintsLeft | kLHintsTop | kFitWidth | kFitHeight,2,2,2,2));
	   fTextEntry1->MoveResize(8,48,280,20);
	   fTextEntry1->Associate(this);
	   fTextEntry1->Connect("DoubleClicked()", "R3BGui", this, "CTE1()");

	   ufont = gClient->GetFont("-*-times-medium-i-*-*-12-*-*-*-*-*-*-*");

	   // graphics context changes
	   GCValues_t val5;
	   val5.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
	   gClient->GetColorByName("#000000",val5.fForeground);
	   gClient->GetColorByName("#e0e0e0",val5.fBackground);
	   val5.fFillStyle = kFillSolid;
	   val5.fFont = ufont->GetFontHandle();
	   val5.fGraphicsExposures = kFALSE;
	   uGC = gClient->GetGC(&val5, kTRUE);
	   
// will reflect user color changes
   	   gClient->GetColorByName("#cccccc",ucolor);
	   fTextEntry2 = new TGTextEntry(fGroupFrame5, new TGTextBuffer(31), ID_21, uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kDoubleBorder | kOwnBackground,ucolor);
	   fTextEntry2->SetMaxLength(4096);
	   fTextEntry2->SetAlignment(kTextLeft);
	   fTextEntry2->SetText("Please set the parameter file ... ex. r3bpar.root");
	   fTextEntry2->Resize(280,fTextEntry2->GetDefaultHeight());
	   fGroupFrame5->AddFrame(fTextEntry2, new TGLayoutHints(kLHintsLeft | kLHintsTop | kFitWidth | kFitHeight,2,2,2,2));
	   fTextEntry2->MoveResize(8,16,280,20);
	   fTextEntry2->Associate(this);
	   fTextEntry2->Connect("DoubleClicked()", "R3BGui", this, "CTE2()");

	   fGroupFrame5->SetLayoutManager(new TGVerticalLayout(fGroupFrame5));
	   fCompFrame1->AddFrame(fGroupFrame5, new TGLayoutHints(kLHintsLeft | kLHintsTop | kFitWidth | kFitHeight,2,2,2,2));
	   fGroupFrame5->MoveResize(336,40,296,80);

//----------------------------------------------------------------------------------------------------------------------------------------------------	   
	   
	   TGVProgressBar *fVProgressBar1 = new TGVProgressBar(fCompFrame1,408);
	   fVProgressBar1->SetName("fVProgressBar1");
	   fVProgressBar1->SetFillType(TGProgressBar::kBlockFill);
	   fVProgressBar1->ChangeOptions(kSunkenFrame | kDoubleBorder | kOwnBackground);

	   gClient->GetColorByName("#ffffff",ucolor);
	   fVProgressBar1->SetBackgroundColor(ucolor);
	   fVProgressBar1->SetPosition(25);
	   fCompFrame1->AddFrame(fVProgressBar1, new TGLayoutHints(kLHintsLeft | kLHintsTop | kFitWidth | kFitHeight,2,2,2,2));
	   fVProgressBar1->MoveResize(872,120,24,416);

// "Details" group frame
	   
	   fGroupFrame6 = new TGGroupFrame(fCompFrame1,"Details");
	   fGroupFrame6->SetLayoutBroken(kTRUE);
	   
	   gClient->GetColorByName("#ffffff",ucolor);
	   fTextView = new TGTextView(fGroupFrame6, 500, 94, fIDs.GetUnID(), kFitWidth | kFitHeight);
	   fTextView->SetBackground(ucolor);
	   fTextView->MoveResize(5,15,515,400);

	   fGroupFrame6->AddFrame(fTextView, new TGLayoutHints(kLHintsExpandX));
	   fCompFrame1->AddFrame(fGroupFrame6, new TGLayoutHints(kLHintsLeft | kLHintsTop | kFitWidth | kFitHeight,2,2,2,2));
	   fGroupFrame6->MoveResize(336,115,528,430);

	   ufont = gClient->GetFont("-*-times-bold-i-*-*-20-*-*-*-*-*-*-*");

	   // graphics context changes
	   GCValues_t val3;
	   val3.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
	   gClient->GetColorByName("#ff0000",val3.fForeground);
	   gClient->GetColorByName("#e0e0e0",val3.fBackground);
	   val3.fFillStyle = kFillSolid;
	   val3.fFont = ufont->GetFontHandle();
	   val3.fGraphicsExposures = kFALSE;
	   uGC = gClient->GetGC(&val3, kTRUE);
//-----------------------------------------------------------------------------------------------------------------------------------------------------	   

	   TGTextButton *fTextButton1 = new TGTextButton(fCompFrame1,"Run Simulation",-1,uGC->GetGC(),ufont->GetFontStruct());
	   fTextButton1->SetTextJustify(36);
	   fTextButton1->SetMargins(0,0,0,0);
	   fTextButton1->SetWrapLength(-1);
	   fCompFrame1->AddFrame(fTextButton1, new TGLayoutHints(kLHintsLeft | kLHintsTop | kFitWidth | kFitHeight,2,2,2,2));
	   fTextButton1->MoveResize(608,550,256,32);  
	   fTextButton1->Connect("Clicked()","R3BGui",this,"RunSimulation()");
	   ufont = gClient->GetFont("-*-times-bold-i-*-*-20-*-*-*-*-*-*-*");

	   // graphics context changes
	   GCValues_t valButton4521;
	   valButton4521.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
	   gClient->GetColorByName("#33ff33",valButton4521.fForeground);
	   gClient->GetColorByName("#e0e0e0",valButton4521.fBackground);
	   valButton4521.fFillStyle = kFillSolid;
	   valButton4521.fFont = ufont->GetFontHandle();
	   valButton4521.fGraphicsExposures = kFALSE;
	   uGC = gClient->GetGC(&valButton4521, kTRUE);
	   
	   TGTextButton *fTextButton2 = new TGTextButton(fCompFrame1,"Go To Analysis",-1,uGC->GetGC(),ufont->GetFontStruct());
	   fTextButton2->SetTextJustify(36);
	   fTextButton2->SetMargins(0,0,0,0);
	   fTextButton2->SetWrapLength(-1);
	   fTextButton2->Resize(256,32);
	   fCompFrame1->AddFrame(fTextButton2, new TGLayoutHints(kLHintsLeft | kLHintsTop | kFitWidth | kFitHeight,2,2,2,2));
	   fTextButton2->MoveResize(608,600,256,32);
	   fTextButton2->Connect("Clicked()","R3BGui",this,"AnalysisWindow()");
	   fTextButton2->Connect("Clicked()","R3BGui",MainFrame2,"CloseWindow()");
	   
	   //----------------------------------------------------------------------------------------------------------------------------------------------------
	   
	   MainFrame2->AddFrame(fCompFrame1, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY | kFitWidth | kFitHeight));
	   fCompFrame1->MoveResize(0,0,937,564);

	   MainFrame2->SetMWMHints(kMWMDecorAll, kMWMFuncAll, kMWMInputModeless);

	   MainFrame2->MapSubwindows();
           MainFrame2->Resize(MainFrame2->GetDefaultSize());
	   MainFrame2->MapWindow();

           MainFrame2->SetWMSize(MainFrame2->GetWidth(), MainFrame2->GetHeight());
           MainFrame2->SetWMSizeHints(MainFrame2->GetWidth(), MainFrame2->GetHeight(), MainFrame2->GetWidth(), MainFrame2->GetHeight(), 0, 0);

	   MainFrame1->CloseWindow(); // Close the Start Window
}

void R3BGui::RunSimulation()
{
	  TString dir = getenv("VMCWORKDIR");
	  TString r3bdir = dir + "/macros";

	  TString r3b_geomdir = dir + "/geometry";
	  gSystem->Setenv("GEOMPATH",r3b_geomdir.Data());

	  TString r3b_confdir = dir + "gconfig";
	  gSystem->Setenv("CONFIG_DIR",r3b_confdir.Data());
	  
// In general, the following parts need not be touched
// ========================================================================

// ----    Debug option   -------------------------------------------------
	  gDebug = 0;
	  
// -----   Timer   --------------------------------------------------------

 	  TStopwatch timer;
	  timer.Start();

// ------------------------------------------------------------------------
// -----   Create simulation run   ----------------------------------------

	   run = new FairRunSim();
	   run->SetName(fMC.Data());              // Transport engine
	   run->SetOutputFile(OutFile.Data());          // Output file
	   fTextView->AddLine(run->GetName());

	   rtdb = run->GetRuntimeDb();

	   //  R3B Special Physics List in G4 case
	   if ( (fUserPList  == kTRUE ) && (fMC.CompareTo("TGeant4")   == 0)) {
	     run->SetUserConfig("g4R3bConfig.C");
	     run->SetUserCuts("SetR3BCuts.C");
	   }
	   // -----   Create media   -------------------------------------------------
	     run->SetMaterials("media_r3b.geo");       // Materials
	   // Magnetic field map type
	     Int_t fFieldMap = 0;

	   // Global Transformations
	   //- Two ways for a Volume Rotation are supported
	   //-- 1) Global Rotation (Euler Angles definition)
	   //-- This represent the composition of : first a rotation about Z axis with
	   //-- angle phi, then a rotation with theta about the rotated X axis, and
	   //-- finally a rotation with psi about the new Z axis.
	     Double_t phi,theta,psi;

	   //-- 2) Rotation in Ref. Frame of the Volume
	   //-- Rotation is Using Local Ref. Frame axis angles
	     Double_t thetaX,thetaY,thetaZ;

	   //- Global Translation  Lab. frame.
	     Double_t tx,ty,tz;

	   // Create detector map

	     if(detectorList[1] == "ALADIN"){fDetList.Add(new TObjString("ALADIN"), new TObjString("aladin_v13a.geo.root"));}
	     if(detectorList[2] == "CRYSTALBALL"){fDetList.Add(new TObjString("CRYSTALBALL"), new TObjString("cal_v13a.geo.root"));}
	     if(detectorList[3] == "CALIFA"){fDetList.Add(new TObjString("CALIFA"), new TObjString("califa_v14a.geo.root"));}
	     //  if(detectorList[3] == "CALIFA"){fDetList.Add(new TObjString("CALIFA"),        new TObjString("califa_v13_811.geo.root"));}
	     if(detectorList[4] == "DCH"){fDetList.Add(new TObjString("DCH"), new TObjString("dch_v13a.geo.root"));}
	     if(detectorList[5] == "GFI"){fDetList.Add(new TObjString("GFI"), new TObjString("gfi_v13a.geo.root"));}
	     if(detectorList[6] == "GLAD")  {fDetList.Add(new TObjString("GLAD"), new TObjString("glad_v13a.geo.root"));}
	     if(detectorList[7] == "LAND"){fDetList.Add(new TObjString("LAND"), new TObjString("land_v12a_10m.geo.root"));}
	     if(detectorList[9] == "MFI"){fDetList.Add(new TObjString("MFI"), new TObjString("mfi_v13a.geo.root"));}
	     if(detectorList[10] == "MTOF"){fDetList.Add(new TObjString("MTOF"), new TObjString("mtof_v13a.geo.root"));}
	     if(detectorList[11] == "PSP"){fDetList.Add(new TObjString("PSP"), new TObjString("psp_v13a.geo.root"));}
	     if(detectorList[12] == "SCINTNEULAND"){fDetList.Add(new TObjString("SCINTNEULAND"), new TObjString("neuland_v12a_14m.geo.root"));}
	     if(detectorList[13] == "STaRTrack"){fDetList.Add(new TObjString("STaRTrack"), new TObjString("startra_v14a.geo.root"));}
//	     if(detectorList[13] == "STaRTrack"){fDetList.Add(new TObjString("STaRTrack"), new TObjString("startra_v13a.geo.root"));}	     
	     if(detectorList[14] == "TARGET"){
	    	 if( Target != ""){
	    	 fDetList.Add(new TObjString("TARGET"), new TObjString("target_"+Target+".geo.root"));
	         }
	         else{
	    	 fTextView->AddLine("You must select the TARGET Material");
	         }
	     }
	     if(detectorList[15] == "TOF"){fDetList.Add(new TObjString("TOF"), new TObjString("tof_v13a.geo.root"));}
	     if(detectorList[16] == "TRACKER"){fDetList.Add(new TObjString("TRACKER"), new TObjString("tra_v13vac.geo.root"));}
	     //  if(detectorList[17] == "VACCESSELCOOL"){fDetList.Add(new TObjString("VACVESSELCOOL"), new TObjString("vacvessel_v14a.geo.root"));}   // to be used only with the R3B tracker: "STaRTrack", not "TRACKER"
	     if(detectorList[17] == "VACCESSELCOOL"){fDetList.Add(new TObjString("VACVESSELCOOL"), new TObjString("vacvessel_v13a.geo.root"));}
	    
	     
	     
// -----   Create R3B geometry --------------------------------------------
	   //R3B Cave definition
	     FairModule* cave = new R3BCave("CAVE"); 
	     cave->SetGeometryFileName("r3b_cave.geo");
	     run->AddModule(cave);

	   //R3B Target definition
	     if (fDetList.FindObject("TARGET") ) {
	       target= new R3BTarget(Target.Data());
	       target->SetGeometryFileName(((TObjString*)fDetList.GetValue("TARGET"))->GetString().Data());
	       fTextView->AddLine("TARGET object was loaded ");
	       run->AddModule(target);
	     }
	     
	    //R3B Magnet definition
	      if (fDetList.FindObject("ALADIN") ) {
	        fFieldMap = 0;
	        mag = new R3BMagnet("AladinMagnet");
	        mag->SetGeometryFileName(((TObjString*)fDetList.GetValue("ALADIN"))->GetString().Data());
	        run->AddModule(mag);
	        fTextView->AddLine("ALADIN object was loaded ");
	      }
	      
	    //R3B Magnet definition
	      if (fDetList.FindObject("GLAD") ) {
	        fFieldMap = 1;
	        mag = new R3BGladMagnet("GladMagnet");
	        mag->SetGeometryFileName(((TObjString*)fDetList.GetValue("GLAD"))->GetString().Data());
	        run->AddModule(mag);
	        fTextView->AddLine("GLAD object was loaded ");
	      }
	      
	      if (fDetList.FindObject("CRYSTALBALL") ) {                               
	        //R3B Crystal Calorimeter
	        xball = new R3BXBall("XBall", kTRUE);
	        xball->SetGeometryFileName(((TObjString*)fDetList.GetValue("CRYSTALBALL"))->GetString().Data());
	        run->AddModule(xball);
	        fTextView->AddLine("XBall object was loaded ");
	      }

	      if (fDetList.FindObject("CALIFA") ) {
	        // CALIFA Calorimeter
	        calo = new R3BCalo("Califa", kTRUE);
	        ((R3BCalo *)calo)->SelectGeometryVersion(10);
	        //Selecting the Non-uniformity of the crystals (1 means +-1% max deviation)
	        ((R3BCalo *)calo)->SetNonUniformity(1.0);
	        calo->SetGeometryFileName(((TObjString*)fDetList.GetValue("CALIFA"))->GetString().Data());
	        run->AddModule(calo);
	        fTextView->AddLine("Califa object was loaded ");
	      }
	      // Tracker
	       if (fDetList.FindObject("TRACKER")  ) {
	         tra = new R3BTra("Tracker", kTRUE);
	         tra->SetGeometryFileName(((TObjString*)fDetList.GetValue("TRACKER"))->GetString().Data());
	         tra->SetEnergyCut(1e-4);
	         run->AddModule(tra);
	         fTextView->AddLine("TRACKER object was loaded ");
	       }

	       // STaRTrack
	       if (fDetList.FindObject("STaRTrack")  ) {
	         tra = new R3BSTaRTra("STaRTrack", kTRUE);
	         tra->SetGeometryFileName(((TObjString*)fDetList.GetValue("STaRTrack"))->GetString().Data());
	         run->AddModule(tra);
	         fTextView->AddLine("STaRTrack object was loaded ");
	       }

	       // DCH drift chambers
	       if (fDetList.FindObject("DCH") ) {
	         dch = new R3BDch("Dch", kTRUE);
	         dch->SetGeometryFileName(((TObjString*)fDetList.GetValue("DCH"))->GetString().Data());
	         run->AddModule(dch);
	         fTextView->AddLine("DCH object was loaded ");
	       }
	       
	       // Tof
	        if (fDetList.FindObject("TOF") ) {
	          tof = new R3BTof("Tof", kTRUE);
	          tof->SetGeometryFileName(((TObjString*)fDetList.GetValue("TOF"))->GetString().Data());
	          run->AddModule(tof);
	          fTextView->AddLine("TOF object was loaded ");
	        }

	        // mTof
	        if (fDetList.FindObject("MTOF") ) {
	          mTof = new R3BmTof("mTof", kTRUE);
	          mTof->SetGeometryFileName(((TObjString*)fDetList.GetValue("MTOF"))->GetString().Data());
	          run->AddModule(mTof);
	          fTextView->AddLine("MTOF object was loaded ");
	        }

	        // GFI detector
	        if (fDetList.FindObject("GFI") ) {
	          gfi = new R3BGfi("Gfi", kTRUE);
	          gfi->SetGeometryFileName(((TObjString*)fDetList.GetValue("GFI"))->GetString().Data());
	          run->AddModule(gfi);
	          fTextView->AddLine("GFI object was loaded ");
	        }

	        // Land Detector
	        if (fDetList.FindObject("LAND") ) {
	          land = new R3BLand("Land", kTRUE);
	          land->SetVerboseLevel(1);
	          land->SetGeometryFileName(((TObjString*)fDetList.GetValue("LAND"))->GetString().Data());
	          run->AddModule(land);
	          fTextView->AddLine("LAND object was loaded ");
	        }

	        // MFI Detector
	        if(fDetList.FindObject("MFI")) {
	          mfi = new R3BMfi("Mfi", kTRUE);
	          mfi->SetGeometryFileName(((TObjString*)fDetList.GetValue("MFI"))->GetString().Data());
	          run->AddModule(mfi);
	          fTextView->AddLine("MFI object was loaded ");
	        }

	        // PSP Detector
	        if(fDetList.FindObject("PSP")) {
	          psp = new R3BPsp("Psp", kTRUE);
	          psp->SetGeometryFileName(((TObjString*)fDetList.GetValue("PSP"))->GetString().Data());
	          run->AddModule(psp);
	          fTextView->AddLine("PSP object was loaded ");
	        }

	        //R3B SiTracker Cooling definition
	 	     if (fDetList.FindObject("VACVESSELCOOL") ) {
	 	       vesselcool= new R3BVacVesselCool(Target.Data());
	 	       vesselcool->SetGeometryFileName(((TObjString*)fDetList.GetValue("VACVESSELCOOL"))->GetString().Data());
	 	       run->AddModule(vesselcool);
	 	      fTextView->AddLine("VACVESSELCOOL object was loaded ");
	 	     }
	        
	        // Luminosity detector
	        //if (fDetList.FindObject("LUMON") ) {
	        //   lumon = new ELILuMon("LuMon", kTRUE);
	        //   lumon->SetGeometryFileName(((TObjString*)fDetList.GetValue("LUMON"))->GetString().Data());
	        //   run->AddModule(lumon);
	        // }	   
	      
// -----   Create R3B  magnetic field ----------------------------------------
	           
	         if (magField == "ALADIN") {
	           aladin_type = new R3BAladinFieldMap("AladinMaps");
	           aladin_type->SetCurrent(fMeasCurrent);
	           aladin_type->SetScale(scalenr);
	           mag_type=(FairField* )&aladin_type;
	           if ( fR3BMagnet == kTRUE ) {  
	             run->SetField(aladin_type);
	           } else {
	             run->SetField(NULL);
	           }
	         } else if(magField == "GLAD"){   
	           glad_type = new R3BGladFieldMap("R3BGladMap");
	           glad_type->SetPosition(0., 0., +350-119.94);
	           glad_type->SetScale(scalenr);
	           mag_type=(FairField*)&glad_type;
	           if ( fR3BMagnet == kTRUE ) {
	               run->SetField(glad_type);
	             } else {
	               run->SetField(NULL);
	             }
	         }  //! end of field map section

// -----   Create PrimaryGenerator   --------------------------------------
// 1 - Create the Main API class for the Generator

	          primGen = new FairPrimaryGenerator();
	            
	          if (fGene.CompareTo("box") == 0  ) {
	            // 2- Define the BOX generator
	            Int_t pdgId = 211; // pion beam
	            Double32_t theta1 = 0.;  // polar angle distribution
	            Double32_t theta2 = 7.;
	            Double32_t momentum = 0.8;
	            boxGen = new FairBoxGenerator(pdgId, 50);
	            boxGen->SetThetaRange(theta1, theta2);
	            boxGen->SetPRange(momentum, momentum*2.);
	            boxGen->SetPhiRange(0, 360);
	            boxGen->SetXYZ(0.0, 0.0, -1.5);
	        //    boxGen->SetXYZ(0.0, 0.0, -300.);
	            // add the box generator
	            primGen->AddGenerator(boxGen);
	          }

	          if (fGene.CompareTo("ascii") == 0  ) {
	            gen = new R3BAsciiGenerator((dir+"/input/"+"evt_gen.dat").Data());
	            primGen->AddGenerator(gen);
	          }

	          if (fGene.CompareTo("r3b") == 0  ) {
	            R3BSpecificGenerator *pR3bGen = new R3BSpecificGenerator();

	            // R3bGen properties
	            pR3bGen->SetBeamInteractionFlag("off");
	            pR3bGen->SetBeamInteractionFlag("off");
	            pR3bGen->SetRndmFlag("off");
	            pR3bGen->SetRndmEneFlag("off");
	            pR3bGen->SetBoostFlag("off");
	            pR3bGen->SetReactionFlag("on");
	            pR3bGen->SetGammasFlag("off");
	            pR3bGen->SetDecaySchemeFlag("off");
	            pR3bGen->SetDissociationFlag("off");
	            pR3bGen->SetBackTrackingFlag("off");
	            pR3bGen->SetSimEmittanceFlag("off");

	            // R3bGen Parameters
	            pR3bGen->SetBeamEnergy(1.); // Beam Energy in GeV
	            pR3bGen->SetSigmaBeamEnergy(1.e-03); // Sigma(Ebeam) GeV
	            pR3bGen->SetParticleDefinition(2212); // Use Particle Pdg Code
	            pR3bGen->SetEnergyPrim(0.3); // Particle Energy in MeV
	            Int_t fMultiplicity = 50;
	            pR3bGen->SetNumberOfParticles(fMultiplicity); // Mult.
	            // Reaction type
	            //        1: "Elas"
	            //        2: "iso"
	            //        3: "Trans"
	            pR3bGen->SetReactionType("Elas");

	            // Target  type
	            //        1: "LeadTarget"
	            //        2: "Parafin0Deg"
	            //        3: "Parafin45Deg"
	            //        4: "LiH"

	            pR3bGen->SetTargetType(Target.Data());
	            Double_t thickness = (0.11/2.)/10.;  // cm
	            pR3bGen->SetTargetHalfThicknessPara(thickness); // cm
	            pR3bGen->SetTargetThicknessLiH(3.5); // cm
	            pR3bGen->SetTargetRadius(1.); // cm

	            pR3bGen->SetSigmaXInEmittance(1.); //cm
	            pR3bGen->SetSigmaXPrimeInEmittance(0.0001); //cm

	            // Dump the User settings
	            pR3bGen->PrintParameters();
	            primGen->AddGenerator(pR3bGen);
	            }

//-------Set generator flag -----------------------------------------------
	            run->SetGenerator(primGen);
	          
//-------Set visualisation flag to true------------------------------------
	            run->SetStoreTraj(Vis);
//	            FairLogger::GetLogger()->SetLogVerbosityLevel("LOW");

	            
// -----   Initialize simulation run   ------------------------------------
	            run->Init();

	            
// ------  Increase nb of step for CALO
	            Int_t nSteps = -15000;
	            gMC->SetMaxNStep(nSteps);


// -----   Runtime database   ---------------------------------------------

//	            R3BFieldPar* fieldPar = (R3BFieldPar*) rtdb->getContainer("R3BFieldPar");
//	            fieldPar->SetParameters(mag_type);
//	            fieldPar->setChanged();
	            
	            Bool_t kParameterMerged = kTRUE;
	            FairParRootFileIo* parOut = new FairParRootFileIo(kParameterMerged);
	            parOut->open(ParFile.Data());
	            rtdb->setOutput(parOut);
	            rtdb->saveOutput();
	            rtdb->print();

// -----   Start run   ----------------------------------------------------
	            if(nEvents > 0) {
	              run->Run(nEvents);
	            }
// -----   Finish   -------------------------------------------------------
	              timer.Stop();
	              Double_t rtime = timer.RealTime();
	              Double_t ctime = timer.CpuTime();
	              cout << endl << endl;
	              cout << "Macro finished succesfully." << endl;
	              cout << "Output file is "    << OutFile << endl;
	              cout << "Parameter file is " << ParFile << endl;
	              cout << "Real time " << rtime << " s, CPU time " << ctime << "s" << endl << endl;
	              // ------------------------------------------------------------------------

	              
	              cout << " Test passed" << endl;
	              cout << " All ok " << endl;
}


// Within this window the user will be able the perform analysis on ROOT files from Simulation/Experiment
void R3BGui::AnalysisWindow()
{
	   MainFrame3 = new TGMainFrame(gClient->GetRoot(),600,800,kMainFrame | kVerticalFrame | kFitWidth | kFitHeight);
	   MainFrame3->SetName("MainFrame3");
//	   MainFrame3->SetLayoutBroken(kTRUE);
//	   MainFrame3->SetCleanup(kDeepCleanup);
  
	   TGLayoutHints* fMenuBarLayout3 = new TGLayoutHints(kLHintsTop | kLHintsExpandX, 2, 2, 2, 5);
	   TGLayoutHints* fMenuBarItemLayout3 = new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 4, 0, 0);
	   TGLayoutHints* fMenuBarHelpLayout3 = new TGLayoutHints(kLHintsTop | kLHintsRight);	   
	   
	   TGMenuBar* fMenuBar3 = new TGMenuBar(MainFrame3, MainFrame3->GetWidth(), 50, kHorizontalFrame | kFitWidth);	   
	   
	   // Create menubar and popup menus. The hint objects are used to place
	   // and group the different menu widgets with respect to eachother.	   
	   fMenuFile3 = new TGPopupMenu(gClient->GetRoot());
	   fMenuFile3->AddEntry("&Open...", M_FILE_OPEN);
	   fMenuFile3->AddEntry("&Save", M_FILE_SAVE);
	   fMenuFile3->AddEntry("S&ave as...", M_FILE_SAVEAS);
	   fMenuFile3->AddSeparator();
	   fMenuFile3->AddEntry("E&xit", M_FILE_EXIT);
	   fMenuFile3->Connect("Activated(Int_t)", "R3BGui", MainFrame3,"HandleMenu(Int_t)");	   
	   fMenuBar3->AddPopup("&File", fMenuFile3, fMenuBarItemLayout3);
 	   MainFrame3->AddFrame(fMenuBar3, fMenuBarLayout3);
	     
//----------------------    vertical frame --> Under Construction ---------------------------------------------------------------------------
	      TGVerticalFrame *fVerticalFrame1 = new TGVerticalFrame(MainFrame3,MainFrame3->GetWidth(),MainFrame3->GetHeight(),kVerticalFrame | kFitWidth);
	      fVerticalFrame1->SetName("fVerticalFrame1");
	      TGIcon *fIcon1 = new TGIcon(fVerticalFrame1,"in_construction.jpg");
	      fIcon1->SetName("fIcon1");
	      fVerticalFrame1->AddFrame(fIcon1, new TGLayoutHints(kLHintsTop | kLHintsExpandX |kLHintsExpandY,2, 0, 2, 2));
	      
	      MainFrame3->AddFrame(fVerticalFrame1, new TGLayoutHints(kLHintsCenterX,1,1,1,1));

// -------------------------------------------------------------------------------------------------------------------------------------------
	 
	   MainFrame3->SetMWMHints(kMWMDecorAll, kMWMFuncAll, kMWMInputModeless);	   
	   MainFrame3->MapSubwindows();
	   MainFrame3->Resize(MainFrame3->GetDefaultSize());
	   MainFrame3->MapWindow();
}

void R3BGui::SaveConfigurationFile()
{
	const char* def_file="r3b_conf.txt";
	
	asciifile.open(def_file, std::ofstream::out | std::ofstream::trunc);
	asciifile << "Engine       = "<<fMC<<"\n";
	asciifile << "UserPhys     = "<<fUserPList<<"\n";
	asciifile << "GenType      = "<<fGene<<"\n";
	asciifile << "TrajVis      = "<<Vis<<"\n";
	asciifile << "MagType      = "<<magField<<"\n";
	asciifile << "MagFlag      = "<<fR3BMagnet<<"\n";
	asciifile << "MeasCurrent  = "<<fMeasCurrent<<"\n";
	asciifile << "Mag.Scale    = "<<scalenr<<"\n";
	asciifile << "Materials    = "<<material_def<<"\n";
	asciifile << "Target       = "<<Target<<"\n";
	for(int i=1;i<18;i++){
		if(detectorList[i]!=""){
			asciifile << "Add detector = "<<detectorList[i]<<"\n";
		}
	}
	asciifile << "Par. File    = "<<ParFile<<"\n";	
	asciifile << "Sim. File    = "<<OutFile<<"\n";
	asciifile << "Run Nr.      = "<<runnr<<"\n";
	asciifile << "Event Nr.    = "<<nEvents<<"\n";
	asciifile.close();
// de pus variabilele ce urmeaza sa fie scrise: name->Write();    
    fTextView->AddLine("Configuration File saved with success ..."); 
    if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());} 
}

void R3BGui::CTE1()
{
	fTextEntry1->Clear();
	TGFont *ufont;         // will reflect user font changes
	ufont = gClient->GetFont("-*-times-medium-r-*-*-12-*-*-*-*-*-*-*");
	fTextEntry1->SetForegroundColor(0x000000);
	fTextEntry1->SetBackgroundColor(0xffffff);
	fTextEntry1->SetFont(ufont);
	fTextView->AddLine("Please give a name for the ROOT Simulation File ... then press Enter!");
	if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
}

void R3BGui::CTE2()
{
	fTextEntry2->Clear();
	TGFont *ufont;         // will reflect user font changes
	ufont = gClient->GetFont("-*-times-medium-r-*-*-12-*-*-*-*-*-*-*");
	fTextEntry2->SetForegroundColor(0x000000);
	fTextEntry2->SetBackgroundColor(0xffffff);
	fTextEntry2->SetFont(ufont);
	fTextView->AddLine("Please give a name for the ROOT Parameter File ... then press Enter!");
	if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
}

void R3BGui::HandleMenu(Int_t id)
{
// Handle menu items.

   switch (id) {

      case M_FILE_OPEN:
         {
            static TString dir(".");
        	static TGFileInfo fi;
            fi.fFileTypes = fnewtypes;
            fi.fIniDir    = StrDup(dir);          
            new TGFileDialog(gClient->GetRoot(), gClient->GetRoot(), kFDOpen, &fi);
            dir = fi.fIniDir;
         }
         break;

      case M_FILE_SAVE:
         break;

         
      case M_FILE_SAVEAS:
    	  static TGFileInfo fi;
    	  fi.fFileTypes = fnewtypes;
    	  new TGFileDialog(gClient->GetRoot(), gClient->GetRoot(), kFDSave, &fi);
         break;
         
         
      case M_FILE_IMPORT:
               printf("M_FILE_IMPORT\n");
               break;
               
      case M_FILE_EXPORT:
               printf("M_FILE_EXPORT\n");
               break;

      case M_FILE_PRINT:
         printf("M_FILE_PRINT\n");
//         printf("Hiding itself, select \"Print Setup...\" to enable again\n");
//         fMenuFile3->HideEntry(M_FILE_PRINT);
         break;

      case M_FILE_PRINTSETUP:
         printf("M_FILE_PRINTSETUP\n");
//         fMenuFile3->EnableEntry(M_FILE_PRINT);
         break;
          	  
      case M_FILE_EXIT:
         gApplication->Terminate(0);
         break;

      default:
         printf("Menu item %d selected\n", id);
         break;
   }
}

void R3BGui::HandleButton(Int_t id)
{
switch (id) {
   case ID_1:
      if(fMC == "TGeant3"){
    	  fMC="TGeant4";
    	  fTextView->AddLine("You change the Transport Engine from Geant 3 -> Geant 4 ...");
    	  if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
      }
      else if (fMC == "TGeant4"){
    	  fTextView->AddLine("You already did the Transport Engine for Geant 4 ...");
    	  if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
      }
      else{
      fMC="TGeant4";
      fTextView->AddLine("Particle Transport Engine: Geant 4 -> activated");
      if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
      }
      break;
   case ID_2:
	   if(fMC == "TGeant4"){
	      fMC="TGeant3";
	      fTextView->AddLine("You change the Transport Engine from Geant 4 -> Geant 3 ...");
	      if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	   }
	   else if (fMC == "TGeant3"){
	     fTextView->AddLine("You already did the Transport Engine for Geant 3 ...");
	     if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	   }
	   else{
	   fMC="TGeant3";
	   fTextView->AddLine("Particle Transport Engine: Geant 3 -> activated");
	   if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	   }
      break;
//------------------------------------------------------------------------------------------------------------------      
   case ID_3:
	   if(fUserPList == kFALSE){
//		   fUserPList="g4R3bConfig.C";
	      fTextView->AddLine("User Physics List -> activated ...");
	      if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	   }
	   else if (fUserPList == kTRUE){
	     fTextView->AddLine("You already activated User Physics List ...");
	     if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	     
	   }
	   else{
	   fTextView->AddLine("User Physics List -> activated");
	   if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
//	   fUserPList="g4R3bConfig.C";
	   }
      break;
 
   case ID_4:
	    if(fUserPList == kTRUE){
//	   		 fUserPList="Default";
	   	     fTextView->AddLine("User Physics List -> dezactivated ...");
	   	     if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	   	   }
	    else if (fUserPList == kFALSE){
	   	     fTextView->AddLine("You already dezactivated User Physics List ...");
	   	     if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	   	   }
	    else{
	         fTextView->AddLine("Physics List: Default -> dezactivated");
	         if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
//	         fUserPList="g4Config.C";
	    }
      break;
//------------------------------------------------------------------------------------------------------------------
 
   case ID_5:
	    if(fGene== "ascii"){
	      fGene="box";
	      fTextView->AddLine("You changed the Generator type from ascii to box type");
	      if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	    }
	    else if (fGene== "r3b"){
	      fGene="box";
		  fTextView->AddLine("You changed the Generator type from r3b to box type");
		  if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	    }
	    else if (fGene== "box"){
	      fTextView->AddLine("You already selected the Generator as box type");
	      if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	    }
	    else{
	      fGene="box";
	      fTextView->AddLine("Generator type: box  -> activated");
	      if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	    }
      break;
 
   case ID_6:
	    if(fGene== "box"){
	   	  fGene="ascii";
	   	  fTextView->AddLine("You changed the Generator type from box to ascii type");
	   	  if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	    }
	    else if (fGene== "r3b"){
	   	  fGene="ascii";
	   	  fTextView->AddLine("You changed the Generator type from r3b to box type");
	   	  if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	    }
	    else if (fGene== "ascii"){
	  	  fTextView->AddLine("You already selected the Generator as ascii type");
	  	  if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	    }
	    else{
	      fTextView->AddLine("Generator type: ascii -> activated");
	      if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	      fGene="ascii";
	    }
      break;
   case ID_7:
	    if(fGene== "box"){
	      fGene="r3b";
	      fTextView->AddLine("You changed the Generator type from box to r3b type");
	      if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	    }
	    else if (fGene== "ascii"){
	   	  fGene="r3b";
	  	  fTextView->AddLine("You changed the Generator type from ascii to r3b type");
	  	  if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	    }
	    else if (fGene== "box"){
	  	  fTextView->AddLine("You already selected the Generator as r3b type");
	  	  if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	    }
	    else{
	      fTextView->AddLine("Generator type: r3b -> activated");
	      if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	      fGene="r3b";
	    }
      break;
 //----------------------------------------------------------------------------------------------------------------------------------------------------      
   case ID_8:
	    if(Vis == kFALSE){
	   	  fTextView->AddLine("Trajectory visualization -> activated");
	   	  if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	   	  Vis=kTRUE;		  
	    }
	    else if (Vis == kTRUE){
		 fTextView->AddLine("You already selected Trajectory Visualization as TRUE");
		 if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	    }
	    else{
		  Vis=kTRUE;
	    }
      break;
      
   case ID_9:
	    if(Vis == kTRUE){
	     fTextView->AddLine("Trajectory visualization -> dezactivated");
	     if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	     Vis=kFALSE;
	    }
	    else if (Vis == kFALSE){
	     fTextView->AddLine("You already selected Trajectory Visualization as FALSE");
	     if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	    }
	    else{
		 Vis=kFALSE;
	    }	   
      break;
//-----------------------------------------------------------------------------------------------------------------------------------------------------

   case ID_10:
	    if(magField == "GLAD"){
   	      fTextView->AddLine("You changed the Magnet type from GLAD to ALADIN type");
   	      if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
   	      magField="ALADIN";
          detectorList[1]=magField;
          fNumberEntry1->SetState(kTRUE);
          fNumberEntry2->SetState(kTRUE);
          fComboBox5->GetTextEntry()->SetState(kTRUE);
//          fCheckButton1[6]->SetEnabled(kFALSE);
//          fCheckButton1[1]->SetEnabled(kTRUE);
//          fCheckButton1[1]->Toggle(kTRUE);
//          ftoggle[1]=1;
	    }
	    else if (magField == "ALADIN"){
	      fTextView->AddLine("You already selected the Magnet type as ALADIN");
	      if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	    }
	    else{
		  fTextView->AddLine("Magnet type: ALADIN -> was activated");
		  if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
		  magField="ALADIN";
          detectorList[1]=magField;
		  fNumberEntry1->SetState(kTRUE);
          fNumberEntry2->SetState(kTRUE);
          fComboBox5->GetTextEntry()->SetState(kTRUE);
//          fCheckButton1[6]->SetEnabled(kFALSE);
//          fCheckButton1[1]->SetEnabled(kTRUE);
//          fCheckButton1[1]->Toggle(kTRUE);
//          ftoggle[1]=1;
	    }
      break;

   case ID_11:
	    if (magField == "ALADIN"){
	      fTextView->AddLine("You changed the Magnet type from ALADIN to GLAD type");
	      if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	      magField="GLAD";
		  detectorList[6]=magField;
	      fNumberEntry1->SetState(kFALSE);
          fNumberEntry2->SetState(kFALSE);
          fComboBox5->GetTextEntry()->SetState(kTRUE);
//		  fCheckButton1[1]->SetEnabled(kFALSE);
//		  fCheckButton1[6]->SetEnabled(kTRUE);
//		  fCheckButton1[6]->Toggle(kTRUE);
//		  ftoggle[6]=1;
	    }
	    else if (magField == "GLAD"){
	      fTextView->AddLine("You already selected the Magnet type as GLAD");
	      if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	    }
	    else{
          fTextView->AddLine("Magnet type: GLAD -> was activated");
          if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
          magField="GLAD";
		  detectorList[6]=magField;
          fNumberEntry1->SetState(kFALSE);
          fNumberEntry2->SetState(kFALSE);
          fComboBox5->GetTextEntry()->SetState(kTRUE);
//		  fCheckButton1[1]->SetEnabled(kFALSE);
//		  fCheckButton1[6]->SetEnabled(kTRUE);
//		  fCheckButton1[6]->Toggle(kTRUE);
//		  ftoggle[6]=1;
	    }
      break;

   case ID_44:
	    if (magField == "ALADIN"){
	      fTextView->AddLine("You dezactivated the ALADIN Magnet Type");
	      if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	      magField="";
		  detectorList[6]=magField;
	      fNumberEntry1->SetState(kFALSE);
          fNumberEntry2->SetState(kFALSE);
          fComboBox5->GetTextEntry()->SetState(kFALSE);
	    }
	    else if (magField == "GLAD"){
	      fTextView->AddLine("You deselected the GLAD Magnet Type");
	      if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	      magField="";
		  detectorList[6]=magField;
	      fNumberEntry1->SetState(kFALSE);
          fNumberEntry2->SetState(kFALSE);
          fComboBox5->GetTextEntry()->SetState(kFALSE);
	    }
	    else{
          fTextView->AddLine("You selected NO Magnet Type");
          if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
          magField="";
		  detectorList[6]=magField;
	      fNumberEntry1->SetState(kFALSE);
          fNumberEntry2->SetState(kFALSE);
          fComboBox5->GetTextEntry()->SetState(kFALSE);
	    }
      break;

//-----------------------------------------------------------------------------------------------------------------------------------------------------      

   case ID_12:
    	fTextView->AddLine("Magnetig Field -> activated");
    	if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
    	fR3BMagnet=kTRUE;
      break;      
   case ID_13:
        fTextView->AddLine("Magnetic Field -> dezactivated");
        if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
        fR3BMagnet=kFALSE;
      break;

//----------------------------------------------------------------------------------------------------------------------------------------------------      
   case ID_14:
       	fTextView->AddLine("Media file: MEDIA-R3B activated");
       	if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
       	material_def="media_r3b.geo";
      break;
      
    case ID_15:
        fTextView->AddLine("Media file: Default activated");
        if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
        material_def="media.geo";
      break;      
//------------------------------------------------------------------------------------------------------------------    
    case ID_16:
     	fTextView->AddLine("Target: Lead -> activated");
     	if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
     	Target="LeadTarget";
       break;
       
    case ID_17:
        fTextView->AddLine("Target: Parafin-0 deg -> activated");
        if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
        Target="Parafin0deg";
       break;
       
    case ID_18:
        fTextView->AddLine("Target: Parafin-45 deg -> activated");
        if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
        Target="Parafin45deg";
       break;
       
    case ID_19:
        fTextView->AddLine("Target: LiH -> activated");
        if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
        Target="LiH";
       break;
//------------------------------------------------------------------------------------------------------------------       
    }
}

Bool_t R3BGui::ProcessMessage(Long_t msg, Long_t parm1, Long_t)
{
	switch (GET_MSG(msg)) {
	      case kC_TEXTENTRY:
	    	  switch (GET_SUBMSG(msg)) {
	    	  	  case kTE_ENTER:	    	  
	    	  		  	  switch (parm1) {
	    	  		  	  	  case ID_20:
	    	  		  	  		  fTextView->AddLine("Root Simulation File was changed ...");
	    	  		  	  	      if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	    	  		  	  		  OutFile=fTextEntry1->GetText();
	    	  		  	  		  break;
	    	  		  	  	  case ID_21:
	    	  		  	  		  fTextView->AddLine("Root Parameter Files was changed ...");
	    	  		  	  	      if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	    	  		  	  	      ParFile=fTextEntry2->GetText();
	    	  		  	  		  break;
	    	  		  	  }
	    	  		  	  break;
	    	  }
	          break;

	      case kC_COMMAND:
	    	  switch (GET_SUBMSG(msg)) {
	    	  	    case kCM_CHECKBUTTON:
	    	  	    	switch (parm1){
/*	    	  	    	
	    	  	    	        case ID_22:
	    	  	    				  if (ftoggle[1]==1){
		    	  	    			     fCheckButton1[6]->SetEnabled(kTRUE);
		    	  	    			     fTextView->AddLine("You deselected ALADIN magnet ...");
		    	  	    			     if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
		    	  	    			     detectorList[1]="";
		    	  	    			     ftoggle[1] = 0;
	    	  	    				  }
	    	  	    				  else{
		    	  	    				 fTextView->AddLine("You selected ALADIN magnet ...");
		    	  	    				 if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
		    	  	    				 detectorList[1]="ALADIN";
		    	  	    				 fCheckButton1[6]->SetEnabled(kFALSE);	    	  	    					  
	    	  	    				     ftoggle[1] = 1;
	    	  	    				  }
	    	  	    			break;
*/	    	  	    			
	    	  	    			case ID_23:
	    	  	    				
	    	  	    				  if (ftoggle[2]==1){
		    	  	    			     fTextView->AddLine("You deselected CRYSTAL BALL detector ...");
		    	  	    			     if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
		    	  	    			     detectorList[2]="";
		    	  	    			     ftoggle[2] = 0;
	    	  	    				  }
	    	  	    				  else{
	  	    	  	    				 fTextView->AddLine("You selected CRYSTAL BALL detector ...");
	  	    	  	    				 if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	  	    	  	    				 detectorList[2]="CRYSTALBALL";	    	  	    					  
	    	  	    				     ftoggle[2] = 1;
	    	  	    				  }
	    	  	    			break;
	    	  	    				
	    	  	    			case ID_24:
	    	  	    				  if (ftoggle[3]==1){
		    	  	    			     fTextView->AddLine("You deselected CALIFA detector ...");
		    	  	    			     if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
		    	  	    			     detectorList[3]="";
		    	  	    			     ftoggle[3] = 0;
	    	  	    				  }
	    	  	    				  else{
	  	    	  	    				 fTextView->AddLine("You selected CALIFA detector ...");
	  	    	  	    				 if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	  	    	  	    				 detectorList[3]="CALIFA";	    	  	    					  
	    	  	    				     ftoggle[3] = 1;
	    	  	    				  }	    	  	    				
	    	  	    			break;

	    	  	    			case ID_25:

	    	  	    			 	  if (ftoggle[4]==1){
		    	  	    			     fTextView->AddLine("You deselected DCH detector ...");
		    	  	    			     if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
		    	  	    			     detectorList[4]="";
		    	  	    			     ftoggle[4] = 0;
	    	  	    				  }
	    	  	    				  else{
	  	    	  	    				 fTextView->AddLine("You selected DCH detector ...");
	  	    	  	    				 if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	  	    	  	    				 detectorList[4]="DCH";
	    	  	    				     ftoggle[4] = 1;
	    	  	    				  }
	    	  	    			break;
	    	  	    				
	    	  	    			case ID_26:
	    	  	    			 	  if (ftoggle[5]==1){
		    	  	    			     fTextView->AddLine("You deselected GFI detector ...");
		    	  	    			     if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
		    	  	    			     detectorList[5]="";
		    	  	    			     ftoggle[5] = 0;
	    	  	    				  }
	    	  	    				  else{
	  	    	  	    				 fTextView->AddLine("You selected GFI detector ...");
	  	    	  	    				 if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	  	    	  	    				 detectorList[5]="GFI";
	    	  	    				     ftoggle[5] = 1;
	    	  	    				  }
	    	  	    			break;
/*
	    	  	    			case ID_27:	    	  	    					    	  	    				
	    	  	    				  if (ftoggle[6] == 1){
		    	  	    			     fCheckButton1[1]->SetEnabled(kTRUE);
		    	  	    			     fTextView->AddLine("You deselected GLAD magnet ...");
		    	  	    			     if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
		    	  	    			     detectorList[6]="";
		    	  	    			     ftoggle[6] = 0;
	    	  	    				  }
	    	  	    				  else{
		    	  	    				 fTextView->AddLine("You selected GLAD magnet ...");
		    	  	    				 if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
		    	  	    				 detectorList[6]="GLAD";
		    	  	    				 fCheckButton1[1]->SetEnabled(kFALSE);	    	  	    					  
	    	  	    				     ftoggle[6] = 1;
	    	  	    				  }
	    	  	    			break;
*/	    	  	    				
	    	  	    			case ID_28:
	    	  	    				  if (ftoggle[7] == 1){
		    	  	    			     fCheckButton1[12]->SetEnabled(kTRUE);
		    	  	    			     fTextView->AddLine("You deselected LAND detector ...");
		    	  	    			     if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	  	    	  	    				 detectorList[7]="";
		    	  	    			     ftoggle[7] = 0;
	    	  	    				  }
	    	  	    				  else{
	  	    	  	    				 fTextView->AddLine("You selected LAND detector ...");
	  	    	  	    				 if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	  	    	  	    				 detectorList[7]="LAND";
		    	  	    				 fCheckButton1[12]->SetEnabled(kFALSE);	    	  	    					  
	    	  	    				     ftoggle[7] = 1;
	    	  	    				  }	    	  	    				
	    	  	    				
	    	  	    			break;
	    	  	    				
	    	  	    			case ID_29:
	    	  	    			 	  if (ftoggle[8]==1){
		    	  	    			     fTextView->AddLine("You deselected LUMON detector ...");
		    	  	    			     if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
		    	  	    			     detectorList[8]="";
		    	  	    			     ftoggle[8] = 0;
	    	  	    				  }
	    	  	    				  else{
	  	    	  	    				 fTextView->AddLine("You selected LUMON detector ...");
	  	    	  	    				 if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	  	    	  	    				 detectorList[8]="LUMON";
	    	  	    				     ftoggle[8] = 1;
	    	  	    				  }
	    	  	    			break;
	    	  	    				
	    	  	    			case ID_30:
	    	  	    			 	  if (ftoggle[9]==1){
		    	  	    			     fTextView->AddLine("You deselected MFI detector ...");
		    	  	    			     if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
		    	  	    			     detectorList[9]="";
		    	  	    			     ftoggle[9] = 0;
	    	  	    				  }
	    	  	    				  else{
	  	    	  	    				 fTextView->AddLine("You selected MFI detector ...");
	  	    	  	    				 if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	  	    	  	    				 detectorList[9]="MFI";
	    	  	    				     ftoggle[9] = 1;
	    	  	    				  }	    	  	    				
	    	  	    			break;
	    	  	    				
	    	  	    			case ID_31:
	    	  	    			 	  if (ftoggle[10]==1){
		    	  	    			     fTextView->AddLine("You deselected MTOF detector ...");
		    	  	    			     if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
		    	  	    			     detectorList[10]="";
		    	  	    			     ftoggle[10] = 0;
	    	  	    				  }
	    	  	    				  else{
	  	    	  	    				 fTextView->AddLine("You selected MTOF detector ...");
	  	    	  	    				 if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	  	    	  	    				 detectorList[10]="MTOF";
	    	  	    				     ftoggle[10] = 1;
	    	  	    				  }	    	  	    			 	  
	    	  	    			break;
	    	  	    				
	    	  	    			case ID_32:
	    	  	    			 	  if (ftoggle[11]==1){
		    	  	    			     fTextView->AddLine("You deselected PSP detector ...");
		    	  	    			     if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
		    	  	    			     detectorList[11]="";
		    	  	    			     ftoggle[11] = 0;
	    	  	    				  }
	    	  	    				  else{
	  	    	  	    				 fTextView->AddLine("You selected PSP detector ...");
	  	    	  	    				 if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	  	    	  	    				 detectorList[11]="PSP";
	    	  	    				     ftoggle[11] = 1;
	    	  	    				  }	    	  	    			 	  
	    	  	    			break;

	    	  	    			case ID_33:	    	  	    				
	    	  	    				if (ftoggle[12] == 1){
		    	  	    			   fCheckButton1[7]->SetEnabled(kTRUE);
		    	  	    			   fTextView->AddLine("You deselected SCINTNEULAND detector ...");
		    	  	    			   if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	  	    	  	    			   detectorList[12]="";
		    	  	    			   ftoggle[12] = 0;
	    	  	    				}
	    	  	    				else{
		    	  	    			   fTextView->AddLine("You selected SCINTNEULAND detector ...");
		    	  	    			   if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
		    	  	    			   detectorList[12]="SCINTNEULAND";
		    	  	    			   fCheckButton1[7]->SetEnabled(kFALSE);	    	  	    					  
	    	  	    				   ftoggle[12] = 1;
	    	  	    				}	    	  	    					    	  	    				
	    	  	    			break;
	    	  	    				
	    	  	    			case ID_34:
	    	  	    			 	  if (ftoggle[13]==1){
		    	  	    			     fTextView->AddLine("You deselected STaRTrack detector ...");
		    	  	    			     if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
		    	  	    			     detectorList[13]="";
		    	  	    			     ftoggle[13] = 0;
	    	  	    				  }
	    	  	    				  else{
	  	    	  	    				  fTextView->AddLine("You selected STaRTrack detector ...");
	  	    	  	    			     if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	  	    	  	    				  detectorList[13]="STaRTrack";
	    	  	    				      ftoggle[13] = 1;
	    	  	    				  }
	    	  	    			break;
	    	  	    				
	    	  	    			case ID_35:
	    	  	    			 	  if (ftoggle[14]==1){
		    	  	    			     fTextView->AddLine("You deselected TARGET detector ...");
		    	  	    			     if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
		    	  	    			     detectorList[14]="";
		    	  	    			     ftoggle[14] = 0;
	    	  	    				  }
	    	  	    				  else{
	  	    	  	    				 fTextView->AddLine("You selected TARGET detector ...");
	  	    	  	    				 if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	  	    	  	    				 detectorList[14]="TARGET";
	    	  	    				     ftoggle[14] = 1;
	    	  	    				  }	    	  	    				
	    	  	    			break;
	    	  	    				
	    	  	    			case ID_36:
	    	  	    			 	  if (ftoggle[15]==1){
		    	  	    			     fTextView->AddLine("You deselected TOF detector ...");
		    	  	    			     if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
		    	  	    			     detectorList[15]="";
		    	  	    			     ftoggle[15] = 0;
	    	  	    				  }
	    	  	    				  else{
	  	    	  	    				fTextView->AddLine("You selected TOF detector ...");
	  	    	  	    			    if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	  	    	  	    				detectorList[15]="TOF";
	    	  	    				     ftoggle[15] = 1;
	    	  	    				  }
	    	  	    			break;
	    	  	    				
	    	  	    			case ID_37:
	    	  	    			 	  if (ftoggle[16]==1){
		    	  	    			     fTextView->AddLine("You deselected TRACKER detector ...");
		    	  	    			     if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
		    	  	    			     detectorList[16]="";
		    	  	    			     ftoggle[16] = 0;
	    	  	    				  }
	    	  	    				  else{
	  	    	  	    				 fTextView->AddLine("You selected TRACKER detector ...");
	  	    	  	    				 if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	  	    	  	    				 detectorList[16]="TRACKER";
	  	    	  	    				 fCheckButton1[17]->SetEnabled(kFALSE);
	    	  	    				     ftoggle[16] = 1;
	    	  	    				  }
	    	  	    				break;
	    	  	    				
	    	  	    			case ID_38:
	    	  	    			 	  if (ftoggle[17]==1){
		    	  	    			     fTextView->AddLine("You deselected VACVESSELCOOL detector ...");
		    	  	    			     if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
		    	  	    			     detectorList[17]="";
		    	  	    			     ftoggle[17] = 0;
	    	  	    				  }
	    	  	    				  else{
	  	    	  	    				 fTextView->AddLine("You selected VACVESSELCOOL detector ...");
	  	    	  	    				 if(fTextView->ReturnLineCount() > visible_lines){fTextView->SetVsbPosition(fTextView->ReturnLineCount());}
	  	    	  	    				 detectorList[17]="VACVESSELCOOL";
	  	    	  	    				 fCheckButton1[16]->SetEnabled(kFALSE);
	    	  	    				     ftoggle[17] = 1;
	    	  	    				  }
	    	  	    				break;
	    	  	    			}
	    	  	    
	    	  	    case kCM_BUTTON:
	    	  	    	switch (parm1){
                            
	    	  				case ID_41:
//                                   const char* cc_run=
//                                   char str1[10]=
 	    	  	    				 fTextView->AddLine("You selected ... Runs");
	    	  	    				break;

                        			case ID_42:
 	    	  	    				 fTextView->AddLine("You selected ... Events");
	    	  	    				break;
	    	  	    		      }
	    			break;
	    	  	    }
	    	   break;
	    	  }
}


ClassImp(R3BGui)

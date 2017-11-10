void r3bgui()
{
  gSystem->Load("libGeom");
  gSystem->Load("libBase");
  gSystem->Load("libField.so");
  gSystem->Load("libR3Bbase");
  gSystem->Load("libR3BGui.so");
  gSystem->Load("libR3BGen.so");
  gSystem->Load("libR3BPassive.so");
  gSystem->Load("libR3BCalo.so");
  gSystem->Load("libR3BDch.so");
  gSystem->Load("libR3BGfi.so");
  gSystem->Load("libR3BLand.so");
  gSystem->Load("libR3BMfi.so");
  gSystem->Load("libR3BPsp.so");
  gSystem->Load("libR3BSTaRTra.so");
  gSystem->Load("libR3BTof.so");
  gSystem->Load("libR3BXBall.so");
  gSystem->Load("libR3BmTof.so");
  gSystem->Load("libR3BTra.so");
  // -----   Initialize R3BGui Interface for Simulation & Analysis    ----------------------------------------
   R3BGui* fGui = new R3BGui();
   fGui->Init();
}

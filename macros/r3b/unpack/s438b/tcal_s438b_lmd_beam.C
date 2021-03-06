
void run(TString runNumber)
{
    TStopwatch timer;
    timer.Start();

    const Int_t nModules = 800;
    const Int_t trigger = 1;              // 1 - onspill, 2 - offspill. -1 - all

    TString dirIn1 = "/Users/kresan/data/s438b/data/";
    TString dirOut = "/Users/kresan/data/s438b/tcal/";
    TString inputFileName1 = dirIn1 + runNumber + "_raw_land.root";              // name of input file
    TString parFileName    = dirIn1 + "params_" + runNumber + "_raw_land.root";  // name of parameter file
    TString outputFileName = dirOut + runNumber + "_tcal_land.root";             // name of output file

    // Create analysis run -------------------------------------------------------
    FairRunAna* run = new FairRunAna();
    run->SetInputFile(inputFileName1.Data());
    run->SetOutputFile(outputFileName.Data());
    // ---------------------------------------------------------------------------

    // ----- Runtime DataBase info -----------------------------------------------
    FairRuntimeDb* rtdb = run->GetRuntimeDb();
    FairParRootFileIo* parIo1 = new FairParRootFileIo();
    parIo1->open(parFileName);
    rtdb->setFirstInput(parIo1);
    rtdb->setOutput(parIo1);
    rtdb->saveOutput();
    // ---------------------------------------------------------------------------

    // Time calibration ----------------------------------------------------------
    R3BLandTcal* landTcal = new R3BLandTcal("LandTcal", 1);
    landTcal->SetTrigger(trigger);
    landTcal->SetNofModules(nModules, 50);
    run->AddTask(landTcal);

    R3BLosTcal* losTcal = new R3BLosTcal("LosTcal", 1);
    losTcal->SetNofModules(20);
    run->AddTask(losTcal);
    // ---------------------------------------------------------------------------

    R3BLandTcalTest *testTcal = new R3BLandTcalTest("TestTcal", 1);
    run->AddTask(testTcal);

    // Initialize ----------------------------------------------------------------
    run->Init();
    FairLogger::GetLogger()->SetLogScreenLevel("INFO");
    // ---------------------------------------------------------------------------

    // Run -----------------------------------------------------------------------
    run->Run();
    // ---------------------------------------------------------------------------

    timer.Stop();
    Double_t rtime = timer.RealTime();
    Double_t ctime = timer.CpuTime();
    cout << endl << endl;
    cout << "Macro finished succesfully." << endl;
    cout << "Output file is " << outputFileName << endl;
    cout << "Parameter file is " << parFileName << endl;
    cout << "Real time " << rtime << " s, CPU time " << ctime << "s" << endl << endl;
}


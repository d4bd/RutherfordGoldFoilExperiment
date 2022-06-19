#include "FPRRunAction.hh"
#include "FPRAnalysis.hh"
#include "FPRDetectorConstruction.hh"

#include "Geant4/G4Run.hh"
#include "Geant4/G4RunManager.hh"
#include "Geant4/G4SystemOfUnits.hh"
#include "Geant4/G4UnitsTable.hh"
#include "Geant4/tls.hh"

FPRRunAction::FPRRunAction()
 : G4UserRunAction()
{
    G4int noBins = FPRDetectorConstruction::returnScreenNo();
    G4double openingAngle = FPRDetectorConstruction::returnOpeningAngle();

    // Create analysis manager
    // The choice of analysis technology is done via selectin of a namespace
    // in FPRAnalysis.hh
    auto analysisManager = G4AnalysisManager::Instance();
    G4cout << "Using " << analysisManager->GetType() << G4endl;
    analysisManager->SetVerboseLevel(1);

    // Creating histograms
    analysisManager->CreateH1("ScreenHit",
                        "Number of events in functions of the screen hit", 
                        noBins, 0, noBins);
    analysisManager->CreateH1("AngleHit",
                        "Number of events in functions of the angle", 
                        noBins, openingAngle, 360.*deg - openingAngle);
    //Histogram that store only very deflected hits
    analysisManager->CreateH1("ScreenHitIMP",
        "Number of events in functions of the screen hit (with big angle of deflection)", 
        noBins, 0, noBins);
    analysisManager->CreateH1("AngleHitIMP",
        "Number of events in functions of the angle (with big angle of deflection)", 
        noBins, openingAngle, 360.*deg - openingAngle); 
}

FPRRunAction::~FPRRunAction() 
{
    delete G4AnalysisManager::Instance();
}

void FPRRunAction::BeginOfRunAction(const G4Run*) 
{  
    // Get analysis manager
    auto analysisManager = G4AnalysisManager::Instance();

    // Open an output file
    //
    G4String fileName = "FPR";
    analysisManager->OpenFile(fileName);
}

void FPRRunAction::EndOfRunAction(const G4Run*) 
{
    //Print histogram statistics
    auto analysisManager = G4AnalysisManager::Instance();
    if ( analysisManager->GetH1(0) ) {
        if(isMaster) 
        {
            G4cout << "\n########## Histogram statistic ##########\n"
            << "            (for the entire run)\n\n"  
            << "Hit distribution in function of the hit screen:\n"
            << "Entries: " << analysisManager->GetH1(0)->entries() << "\n"
            << "Mean = " << std::setprecision(3) << analysisManager->GetH1(0)->mean() << "\n"
            << "Rms = " << std::setprecision(2) << analysisManager->GetH1(0)->rms() << "\n\n"
            << "Hit distribution in function of the angle:\n"
            << "Entries: " << analysisManager->GetH1(1)->entries() << "\n"
            << "Mean = " << std::setprecision(5) << analysisManager->GetH1(1)->mean()/deg << " deg" << "\n"
            << "Rms = " << std::setprecision(3) << analysisManager->GetH1(1)->rms()/deg << " deg\n\n"
            << "Hit distribution in function of the hit screen (with big angle of deflection):\n"
            << "Entries: " << analysisManager->GetH1(2)->entries() << "\n"
            << "Mean = " << std::setprecision(3) << analysisManager->GetH1(2)->mean() << "\n"
            << "Rms = " << std::setprecision(2) << analysisManager->GetH1(2)->rms() << "\n\n"
            << "Hit distribution in function of the angle (with big angle of deflection):\n"
            << "Entries: " << analysisManager->GetH1(3)->entries() << "\n"
            << "Mean = " << std::setprecision(5) << analysisManager->GetH1(3)->mean()/deg << " deg" << "\n"
            << "Rms = " << std::setprecision(3) << analysisManager->GetH1(3)->rms()/deg << " deg\n\n"
            << "Frequency of big angle hits: " 
            << G4double(analysisManager->GetH1(2)->entries())/analysisManager->GetH1(0)->entries() << "\n"
            << "\n#########################################\n" << G4endl;
        }
    }

    //Save histograms & ntuple
    analysisManager->Write();
    analysisManager->CloseFile();
}

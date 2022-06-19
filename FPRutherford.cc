#include "Geant4/G4RunManagerFactory.hh"
#include "Geant4/G4UImanager.hh"
#include "Geant4/G4VisExecutive.hh"
#include "Geant4/G4UIExecutive.hh"
#include "Geant4/QGSP_BIC.hh"
#include "Geant4/G4StepLimiterPhysics.hh"
#include "Geant4/G4TScoreNtupleWriter.hh"

#include "FPRDetectorConstruction.hh"
#include "FPRPhysicsList.hh"
#include "FPRActionInitialization.hh"
#include "FPRAnalysis.hh"

int main(int argc,char** argv)
{
	// Detect interactive mode (if no arguments) and define UI session
	//
	G4UIExecutive* ui = 0;
	if ( argc == 1 ) {
		ui = new G4UIExecutive(argc, argv);
	}

	// Construct the default run manager
	//
	auto* runManager =
		G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

	//Setting for multi threading
	G4int nThreads = 8;
	runManager->SetNumberOfThreads(nThreads);
	
	// Set mandatory initialization classes
	//
	// Detector construction
	runManager->SetUserInitialization(new FPRDetectorConstruction());

	// Physics list
	runManager->SetUserInitialization(new FPRPhysicsList);
	//runManager->SetUserInitialization(new QGSP_BIC);

	// User action initialization
	runManager->SetUserInitialization(new FPRActionInitialization());

	// Initialize visualization
	//
	G4VisManager* visManager = new G4VisExecutive;
	visManager->Initialize();

	// Get the pointer to the User Interface manager
	G4UImanager* UImanager = G4UImanager::GetUIpointer();

	// Process macro or start UI session
	//
	if ( ! ui ) { 
		//Batch mode
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UImanager->ApplyCommand(command+fileName);
	}
	else { 
		//Interactive mode
		UImanager->ApplyCommand("/control/execute init_vis.mac");
		if (ui->IsGUI()) {
		UImanager->ApplyCommand("/control/execute Macro/GUI/gui.mac");
		}
		ui->SessionStart();
		delete ui;
	}

	// Job termination
	// Free the store: user actions, physics_list and detector_description are
	// owned and deleted by the run manager, so they should not be deleted 
	// in the main() program !
	delete visManager;
	delete runManager;
}
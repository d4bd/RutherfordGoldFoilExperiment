#include "FPRDetectorMessenger.hh"
#include "FPRDetectorConstruction.hh"

#include "Geant4/G4UIcmdWithAString.hh"
#include "Geant4/G4UIcmdWithoutParameter.hh"

FPRDetectorMessenger::FPRDetectorMessenger(FPRDetectorConstruction* Detector)
 : G4UImessenger(),
   fDetectorConstruction(Detector)
{
    fFPRDirectory = new G4UIdirectory("/FPR/");
    fFPRDirectory->SetGuidance("UI commands specific to this example.");

    fDetectorDirectory = new G4UIdirectory("/FPR/Detector/");
    fDetectorDirectory->SetGuidance("Detector control");

    fSetFoilMaterialCmd = new G4UIcmdWithAString("/FPR/Detector/setFoilMaterial",this);
    fSetFoilMaterialCmd->SetGuidance("Select Material for the Foil.");
    fSetFoilMaterialCmd->SetParameterName("Foil material",false);
    fSetFoilMaterialCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

	fSetWorldAir = new G4UIcmdWithoutParameter("/FPR/Detector/setWorldAir",this);
	fSetWorldAir->SetGuidance("Set air as the world material.");
	fSetWorldAir->AvailableForStates(G4State_PreInit,G4State_Idle);

	fSetWorldVoid = new G4UIcmdWithoutParameter("/FPR/Detector/setWorldVoid",this);
	fSetWorldVoid->SetGuidance("Set void as the world material.");
	fSetWorldVoid->AvailableForStates(G4State_PreInit,G4State_Idle);
}

FPRDetectorMessenger::~FPRDetectorMessenger()
{
	delete fSetFoilMaterialCmd;
	delete fFPRDirectory;
	delete fDetectorDirectory;
}

void FPRDetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
 	if( command == fSetFoilMaterialCmd )
   	{ 
		fDetectorConstruction->SetFoilMaterial(newValue);
	}

	if( command == fSetWorldAir )
   	{ 
		fDetectorConstruction->SetWorldMaterialAir();
	}

	if( command == fSetWorldVoid )
   	{ 
		fDetectorConstruction->SetWorldMaterialVoid();
	}
}




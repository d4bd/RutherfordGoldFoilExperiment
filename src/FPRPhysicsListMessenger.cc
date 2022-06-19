#include "FPRPhysicsListMessenger.hh"
#include "FPRPhysicsList.hh"

#include "Geant4/G4SystemOfUnits.hh"
#include "Geant4/G4UIdirectory.hh"
#include "Geant4/G4UIcmdWithAString.hh"
#include "Geant4/G4UIcmdWithADoubleAndUnit.hh"

FPRPhysicsListMessenger::FPRPhysicsListMessenger(FPRPhysicsList* pPhys)
  :G4UImessenger(), fPhysicsList(pPhys), fMaxChargedStep(1*CLHEP::mm)
{
	fPhysDir = new G4UIdirectory("/testem/phys/");
	fPhysDir->SetGuidance("physics list commands");

	fListCmd = new G4UIcmdWithAString("/testem/phys/addPhysics",this);  
	fListCmd->SetGuidance("Add modula physics list.");
	fListCmd->SetParameterName("PList",false);
	fListCmd->AvailableForStates(G4State_PreInit);
	fListCmd->SetToBeBroadcasted(false);      

	fStepMaxCmd = new G4UIcmdWithADoubleAndUnit("/testem/stepMax",this);
	fStepMaxCmd->SetGuidance("Set max allowed step length");
	fStepMaxCmd->SetParameterName("mxStep",false);
	fStepMaxCmd->SetRange("mxStep>0.");
	fStepMaxCmd->SetUnitCategory("Length");
	fStepMaxCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}

FPRPhysicsListMessenger::~FPRPhysicsListMessenger()
{
	delete fListCmd;
	delete fPhysDir;
	delete fStepMaxCmd;
}

void FPRPhysicsListMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 
    if( command == fListCmd )
        { fPhysicsList->AddPhysicsList(newValue); }

    if (command == fStepMaxCmd)
        { fMaxChargedStep = fStepMaxCmd->GetNewDoubleValue(newValue); }
}
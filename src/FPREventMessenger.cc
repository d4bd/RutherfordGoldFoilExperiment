#include "FPREventMessenger.hh"
#include "FPREventAction.hh"

#include "Geant4/G4UIcmdWithAnInteger.hh"

FPREventMessenger::FPREventMessenger(FPREventAction* Event)
 : G4UImessenger(),
   fEventAction(Event)
{
  fFPRDirectory = new G4UIdirectory("/FPR/");
  fFPRDirectory->SetGuidance("UI commands specific to this example.");

  fEventDirectory = new G4UIdirectory("/FPR/event/");
  fEventDirectory->SetGuidance("Event action control");

  fModuloCmd = new G4UIcmdWithAnInteger("/FPR/event/modulo",this);
  fModuloCmd->SetGuidance("Define the modulo for periodic printing of eventID");
  fModuloCmd->SetParameterName("Modulo",false);
  fModuloCmd->AvailableForStates(G4State_Idle);
}

FPREventMessenger::~FPREventMessenger()
{
  delete fModuloCmd;
  delete fFPRDirectory;
  delete fEventDirectory;
}

void FPREventMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
    if( command == fModuloCmd )
    { 
        fEventAction->setModulo(fModuloCmd->GetNewIntValue(newValue));
    }
}


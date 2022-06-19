#include "FPREventAction.hh"
#include "FPRAnalysis.hh"

#include "Geant4/G4Event.hh"
#include "Geant4/G4EventManager.hh"
#include "Geant4/G4SDManager.hh"
#include "Geant4/G4HCofThisEvent.hh"

FPREventAction::FPREventAction()
: G4UserEventAction(), fPrintModuloNum(100)
{
    fMessenger = new FPREventMessenger(this);
}

FPREventAction::~FPREventAction()
{
    delete fMessenger;
}

void FPREventAction::BeginOfEventAction(const G4Event* event)
{
    //Periodic printing
    G4int eventID = event->GetEventID();
    if ( eventID < 100 || eventID % fPrintModuloNum == 0)
    {
        G4cout << ">>> Event: " << eventID  << G4endl;
    }
}

void FPREventAction::EndOfEventAction(const G4Event*)
{}  

#include "FPRSteppingAction.hh"

#include "G4SteppingManager.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4TrackStatus.hh"
#include "G4VPhysicalVolume.hh"


FPRSteppingAction::FPRSteppingAction()
{}

FPRSteppingAction::~FPRSteppingAction()
{}

void FPRSteppingAction::UserSteppingAction(const G4Step * theStep)
{
    //If is an alive track in a screen kills it
    G4Track * theTrack = theStep->GetTrack();
    
    //Check if it is alive
    if(theTrack->GetTrackStatus()!=fAlive) { return; }

    //Check if at the beginning of the step 
    //is in one of the detector screens
    G4StepPoint* thePrePoint = theStep->GetPreStepPoint();
    G4VPhysicalVolume* thePrePV = thePrePoint->GetPhysicalVolume();
    G4String thePrePVname = thePrePV->GetName();
    if(thePrePVname == "ScreenZnS") 
    { 
        theTrack->SetTrackStatus(fKillTrackAndSecondaries); 
        return; 
    }
}
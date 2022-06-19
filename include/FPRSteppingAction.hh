#ifndef FPRSTEPPINGACTION
#define FPRSTEPPINGACTION

#include "Geant4/globals.hh"
#include "Geant4/G4UserSteppingAction.hh"

class FPRSteppingAction : public G4UserSteppingAction
{
  public:
    FPRSteppingAction();
    virtual ~FPRSteppingAction();

    virtual void UserSteppingAction(const G4Step*);
};

#endif
#ifndef FPRRUNACTION
#define FPRRUNACTION

#include "Geant4/G4UserRunAction.hh"
#include "Geant4/globals.hh"

class G4Run;

//Run action class
class FPRRunAction : public G4UserRunAction
{
  public:
    FPRRunAction();
    virtual ~FPRRunAction();

    virtual void BeginOfRunAction(const G4Run* run);
    virtual void   EndOfRunAction(const G4Run* run);
};

#endif
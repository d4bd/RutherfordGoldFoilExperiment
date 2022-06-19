#ifndef FPRACTIONIINITIALIZATION
#define FPRACTIONIINITIALIZATION

#include "Geant4/G4VUserActionInitialization.hh"

//Action initialization class.
class FPRActionInitialization : public G4VUserActionInitialization
{
  public:
    FPRActionInitialization();
    virtual ~FPRActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

#endif
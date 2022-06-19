#ifndef FPRSTEPMAX
#define FPRSTEPMAX7

#include "Geant4/globals.hh"
#include "Geant4/G4VEmProcess.hh"
#include "Geant4/G4ParticleDefinition.hh"
#include "Geant4/G4Step.hh"

class FPRPhysicsListMessenger;

class FPRStepMAx : public G4VEmProcess
{
    public:
        FPRStepMAx(FPRPhysicsListMessenger* mess);
        virtual ~FPRStepMAx();

        virtual G4bool IsApplicable(const G4ParticleDefinition&);

        virtual void PreparePhysicsTable(const G4ParticleDefinition&);

        virtual void BuildPhysicsTable(const G4ParticleDefinition&);

        virtual void InitialiseProcess(const G4ParticleDefinition*);

        virtual G4double PostStepGetPhysicalInteractionLength(const G4Track& track,
                                                                G4double previousStep,
                                                                G4ForceCondition* cond);

        virtual G4VParticleChange* PostStepDoIt(const G4Track&, const G4Step&);

    private:
        FPRPhysicsListMessenger* fMessenger;

        G4double fMaxChargedStep;
        G4bool isInitialised;
};


#endif
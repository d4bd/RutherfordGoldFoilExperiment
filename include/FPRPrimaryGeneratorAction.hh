#ifndef FPRPRIMARYGENERATORACTION
#define FPRPRIMARYGENERATORACTION

#include "Geant4/G4VUserPrimaryGeneratorAction.hh"
#include "Geant4/G4ParticleGun.hh"

class G4ParticleGun;
class G4Event;

class FPRPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
    public:
		FPRPrimaryGeneratorAction();
		~FPRPrimaryGeneratorAction();

    public:
	      void GeneratePrimaries(G4Event* anEvent);

    private:
		G4ParticleGun* fParticleGun;
		G4double fEnergy;
		G4double fRadiusDetector;
		G4double fRadiusCollimator;
		G4double fCollimatorLenght;
		G4double fMaxMom;
};

#endif

#ifndef FPRPHYSICSLIST
#define FPRPHYSICSLIST

#include "Geant4/G4VModularPhysicsList.hh"

class FPRPhysicsListMessenger;
class G4VPhysicsConstructor;
class G4StepLimiter;

class FPRPhysicsList: public G4VUserPhysicsList
{
	public:
		FPRPhysicsList();
		virtual ~FPRPhysicsList();

		virtual void ConstructParticle();

		virtual void ConstructProcess();
			
		void AddPhysicsList(const G4String& name);

	private:
		G4String               fEmName;
		G4VPhysicsConstructor* fEmPhysicsList;
		G4VPhysicsConstructor* fDecPhysicsList;

		FPRPhysicsListMessenger* fMessenger;
};

#endif

#ifndef FPRPHYSICSLISTMESSENGER
#define FPRPHYSICSLISTMESSENGER

#include "Geant4/G4UImessenger.hh"
#include "Geant4/globals.hh"

class FPRPhysicsList;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;

class FPRPhysicsListMessenger: public G4UImessenger
{
	public:	
		FPRPhysicsListMessenger(FPRPhysicsList* );
		~FPRPhysicsListMessenger();
			
		virtual void SetNewValue(G4UIcommand*, G4String);

		inline G4double GetMaxChargedStep() const { return fMaxChargedStep; }
		
	private:
		FPRPhysicsList*            fPhysicsList;
			
		G4UIdirectory*             fPhysDir;    
		G4UIcmdWithAString*        fListCmd;    
		G4UIcmdWithADoubleAndUnit* fStepMaxCmd;
		G4double                   fMaxChargedStep;
};


#endif
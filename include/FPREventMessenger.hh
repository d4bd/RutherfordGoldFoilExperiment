#ifndef FPREVENTMESSENGER
#define FPREVENTMESSENGER

#include "Geant4/globals.hh"
#include "Geant4/G4UImessenger.hh"

class FPREventAction;
class G4UIdirectory;
class G4UIcmdWithAnInteger;

class FPREventMessenger: public G4UImessenger
{
	public:
		FPREventMessenger(FPREventAction* );
		virtual ~FPREventMessenger();
		
		virtual void SetNewValue(G4UIcommand*, G4String);
		
	private:
		FPREventAction*         fEventAction;

		G4UIdirectory*          fFPRDirectory;
		G4UIdirectory*          fEventDirectory;

		G4UIcmdWithAnInteger*   fModuloCmd;   
};

#endif  
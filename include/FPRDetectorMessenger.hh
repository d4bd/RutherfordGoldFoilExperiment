#ifndef FPRDETERCTORMESSENGER
#define FPRDETERCTORMESSENGER

#include "Geant4/globals.hh"
#include "Geant4/G4UImessenger.hh"

class FPRDetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithoutParameter;

class FPRDetectorMessenger: public G4UImessenger
{
  public:
    FPRDetectorMessenger(FPRDetectorConstruction* );
    virtual ~FPRDetectorMessenger();
    
    virtual void SetNewValue(G4UIcommand*, G4String);
    
  private:
    FPRDetectorConstruction*    fDetectorConstruction;

    G4UIdirectory*              fFPRDirectory;
    G4UIdirectory*              fDetectorDirectory;

    G4UIcmdWithAString*         fSetFoilMaterialCmd;    
    G4UIcmdWithoutParameter*    fSetWorldAir;
    G4UIcmdWithoutParameter*    fSetWorldVoid;  
};

#endif
#ifndef FPRSCREENSD
#define FPRSCREENSD

#include "FPRScreenHit.hh"

#include "Geant4/G4VSensitiveDetector.hh"

#include <vector>


class G4Step;
class G4HCofThisEvent;

class FPRScreenSD : public G4VSensitiveDetector
{
    public:
        FPRScreenSD(const G4String& name, 
                    const G4String& hitsCollectionName);
        virtual ~FPRScreenSD();
    
        //Methods from base class
        virtual void   Initialize(G4HCofThisEvent* hitCollection);
        virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
        virtual void   EndOfEvent(G4HCofThisEvent* hitCollection);

    private:
        FPRScreenHitsCollection* screenCollection;

        //Varible to store the copyNum of the hit detector screen
        G4int fScreenNo;            

        //Variable to store di ID of the hit collection
        G4int fhcID;               

        //Variable to store the complessive number of detector screens
        G4int fScreenCount; 
                
        G4double fOpeningAngle;
        G4double fSpacingAngle;
};

#endif  
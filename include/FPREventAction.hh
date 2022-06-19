#ifndef FPREVENTACTION
#define FPREVENTACTION

#include "FPREventMessenger.hh"

#include "Geant4/G4UserEventAction.hh"
#include "Geant4/globals.hh"
#include "Geant4/tls.hh"
#include "Geant4/G4THitsMap.hh"

//Event action class
class FPREventAction : public G4UserEventAction
{
    public:
        FPREventAction();
        virtual ~FPREventAction();

        virtual void  BeginOfEventAction(const G4Event* );
        virtual void    EndOfEventAction(const G4Event* );

        void setModulo(G4int num) {fPrintModuloNum = num;}

    private:
        G4int fPrintModuloNum;

        FPREventMessenger* fMessenger;
};

#endif
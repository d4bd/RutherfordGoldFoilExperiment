#ifndef FPRSCREENPARAMETRIZATION
#define FPRSCREENPARAMETRIZATION

#include "Geant4/globals.hh"
#include "Geant4/G4VPVParameterisation.hh"

class G4VPhysicalVolume;
class G4Box;

// Dummy declarations to get rid of warnings ...
class G4Trd;
class G4Trap;
class G4Cons;
class G4Orb;
class G4Sphere;
class G4Torus;
class G4Para;
class G4Hype;
class G4Tubs;
class G4Polycone;
class G4Polyhedra;

class FPRScreenParameterisation : public G4VPVParameterisation
{ 
    public:
        FPRScreenParameterisation(G4int NoScreens, 
                            G4double bigRadius,
                            G4double openingAngle,
                            G4double spacingAngle);

    virtual                                 
   ~FPRScreenParameterisation();
   
    void ComputeTransformation (const G4int copyNo,
                                G4VPhysicalVolume* physVol) const;
    
    //Dummy declarations to get rid of warnings ...
    private:         
        void ComputeDimensions (G4Trd&,const G4int,const G4VPhysicalVolume*) const {}
        void ComputeDimensions (G4Trap&,const G4int,const G4VPhysicalVolume*) const {}
        void ComputeDimensions (G4Cons&,const G4int,const G4VPhysicalVolume*) const {}
        void ComputeDimensions (G4Sphere&,const G4int,const G4VPhysicalVolume*) const {}
        void ComputeDimensions (G4Orb&,const G4int,const G4VPhysicalVolume*) const {}
        void ComputeDimensions (G4Torus&,const G4int,const G4VPhysicalVolume*) const {}
        void ComputeDimensions (G4Para&,const G4int,const G4VPhysicalVolume*) const {}
        void ComputeDimensions (G4Hype&,const G4int,const G4VPhysicalVolume*) const {}
        void ComputeDimensions (G4Tubs&,const G4int,const G4VPhysicalVolume*) const {}
        void ComputeDimensions (G4Polycone&,const G4int,const G4VPhysicalVolume*) const {}
        void ComputeDimensions (G4Polyhedra&,const G4int,const G4VPhysicalVolume*) const {}

    private:
        G4int    fNoScreens; 
        G4double fBigRadius;     
        G4double fOpeningAngle; 
        G4double fSpacingAngle;
};

#endif
#include "FPRScreenParametrization.hh"

#include "Geant4/G4VPhysicalVolume.hh"
#include "Geant4/G4ThreeVector.hh"
#include "Geant4/G4RotationMatrix.hh"
#include "Geant4/G4Box.hh"
#include "Geant4/G4SystemOfUnits.hh"

#include <cmath>

FPRScreenParameterisation::FPRScreenParameterisation(G4int NoScreens,
                            G4double bigRadius,
                            G4double openingAngle,
                            G4double spacingAngle) :
    fNoScreens(NoScreens), 
    fBigRadius(bigRadius),     
    fOpeningAngle(openingAngle), 
    fSpacingAngle(spacingAngle)
{}

FPRScreenParameterisation::~FPRScreenParameterisation()
{}

void FPRScreenParameterisation::ComputeTransformation
(const G4int copyNo, G4VPhysicalVolume* physVol) const
{
    G4double angle = fOpeningAngle + ((copyNo + 0.5) * fSpacingAngle);

    G4double Xposition = fBigRadius * cos( (angle/deg)*M_PI/180. );
    G4double Yposition = fBigRadius * sin( (angle/deg)*M_PI/180. );

    G4RotationMatrix* rm = new G4RotationMatrix();
    rm->rotateZ(-angle);
    G4ThreeVector position(Xposition, Yposition, 0);

    physVol->SetTranslation(position);
    physVol->SetRotation(rm);
}
#include "FPRPrimaryGeneratorAction.hh"

#include "Geant4/G4Event.hh"
#include "Geant4/G4ParticleGun.hh"
#include "Geant4/G4ParticleTable.hh"
#include "Geant4/G4ParticleDefinition.hh"
#include "Geant4/globals.hh"
#include "Geant4/G4SystemOfUnits.hh"
#include "Geant4/G4LogicalVolume.hh"
#include "Geant4/Randomize.hh"
#include "Geant4/G4LogicalVolumeStore.hh"
#include "Geant4/G4RunManager.hh"
#include "G4VSolid.hh"
#include "G4Tubs.hh"

#include <cmath>

FPRPrimaryGeneratorAction::FPRPrimaryGeneratorAction()
: fEnergy(0), fRadiusDetector(0), fRadiusCollimator(0), fCollimatorLenght(0), fMaxMom(0)
{
  G4int n_particle = 1;
  fParticleGun = new G4ParticleGun(n_particle);

  //Calculation of emission settings
  G4Tubs* detector = 0;
  G4Tubs* collimator = 0;

  //Necessary check since the constructor is called for every thread
  if (!detector)
  {
    G4LogicalVolume* volumeDetector
        = G4LogicalVolumeStore::GetInstance()->GetVolume("Detector");
    if ( volumeDetector ) detector = dynamic_cast<G4Tubs*>(volumeDetector->GetSolid()->GetConstituentSolid(0));
  }

  if ( detector ) {
      fRadiusDetector = detector->GetRMax();
    }  
  else { 
    G4ExceptionDescription msg;
    msg << "Detector volume of box shape not found.\n"; 
    msg << "Perhaps you have changed geometry.\n";
    msg << "The gun will be place at the center.";
    G4Exception("FPRPrimaryGeneratorAction::GeneratePrimaries()",
     "MyCode0001",JustWarning,msg);
  }

  if (!collimator)
  {
    G4LogicalVolume* volumeCollimator
        = G4LogicalVolumeStore::GetInstance()->GetVolume("Collimator");
    if ( volumeCollimator ) collimator = dynamic_cast<G4Tubs*>(volumeCollimator->GetSolid());
  }

  if ( collimator ) {
    fRadiusCollimator = collimator->GetRMax();
    fCollimatorLenght = 10*collimator->GetZHalfLength()/6;
    fMaxMom = sin(atan(2*fRadiusCollimator/fCollimatorLenght));
  }  
  else  {
    G4ExceptionDescription msg;
    msg << "Collimator volume of tubs shape not found.\n"; 
    msg << "Perhaps you have changed geometry.\n";
    msg << "The gun will be place at the center.";
    G4Exception("FPRPrimaryGeneratorAction::GeneratePrimaries()",
    "MyCode0002",JustWarning,msg);
  }
}

FPRPrimaryGeneratorAction::~FPRPrimaryGeneratorAction()
{
  delete fParticleGun;
}

void FPRPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{

  //Energy of alpha in radium decay
  fEnergy = 4.6*MeV;

  G4double ypos = 0;
  G4double zpos = 0;
  
  G4double ymom = 0;
  G4double zmom = 0;

  //Randomly set the output position form the collimator
  do
  {
    ypos = CLHEP::RandFlat::shoot(-fRadiusCollimator, fRadiusCollimator);
    zpos = CLHEP::RandFlat::shoot(-fRadiusCollimator, fRadiusCollimator);
  } while (!((sqrt(ypos*ypos + zpos*zpos)) < fRadiusCollimator));
  
  ymom = CLHEP::RandFlat::shoot(-fMaxMom, fMaxMom);
  zmom = CLHEP::RandFlat::shoot(-fMaxMom, fMaxMom);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  fParticleGun->SetParticleDefinition(particleTable->FindParticle(particleName="alpha"));
  fParticleGun->SetParticleEnergy(fEnergy);

  fParticleGun->SetParticlePosition(G4ThreeVector(fRadiusDetector + 10.*cm - 1.*um, ypos, zpos)); 

  G4ThreeVector v(-1.0,ymom,zmom);
  fParticleGun->SetParticleMomentumDirection(v);
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
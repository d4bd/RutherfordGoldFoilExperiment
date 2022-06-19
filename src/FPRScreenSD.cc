#include "FPRScreenSD.hh"
#include "FPRAnalysis.hh"
#include "FPRDetectorConstruction.hh"

#include "Geant4/G4HCofThisEvent.hh"
#include "Geant4/G4Step.hh"
#include "Geant4/G4ThreeVector.hh"
#include "Geant4/G4SDManager.hh"
#include "Geant4/G4ios.hh"
#include "Geant4/G4SystemOfUnits.hh"

#include <cmath>

FPRScreenSD::FPRScreenSD(const G4String& name,
                         const G4String& hitsCollectionName) 
 : G4VSensitiveDetector(name),
	screenCollection(nullptr),
	fScreenNo(-1),
	fhcID(-1)

{
	collectionName.insert(hitsCollectionName);

	fScreenCount = FPRDetectorConstruction::returnScreenNo();
	fOpeningAngle = FPRDetectorConstruction::returnOpeningAngle();
	fSpacingAngle = (360.*deg - (2. * fOpeningAngle)) / fScreenCount;
}

FPRScreenSD::~FPRScreenSD()
{}

void FPRScreenSD::Initialize(G4HCofThisEvent* hce)
{
	// Create hits collection
	screenCollection = new FPRScreenHitsCollection
							(SensitiveDetectorName,collectionName[0]); 
	
	// Add this collection in hce
	if( fhcID == -1)
	{
		fhcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
	}
	hce->AddHitsCollection( fhcID, screenCollection );
	fScreenNo = -1;
}

G4bool FPRScreenSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
	fScreenNo = aStep->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber(1);

	FPRScreenHit* newHit = new FPRScreenHit();
	newHit->SetTrackID  (aStep->GetTrack()->GetTrackID());
	newHit->SetScreenNb (fScreenNo);
	newHit->SetPos      (aStep->GetPostStepPoint()->GetPosition());
	screenCollection->insert( newHit );

	return true;
}

void FPRScreenSD::EndOfEvent(G4HCofThisEvent*)
{
	G4double angle = fOpeningAngle + ((fScreenNo + 0.5) * fSpacingAngle);
	G4double bigAngle = 90.*deg;

	if (verboseLevel > 0) //Contorlled with /hits/verbose <int>
	{
		G4cout << "\n---------- Hit data ----------\n"
		<< " Screen hit: " << fScreenNo
		<< "\n Angle: " << std::setprecision(5) << angle/deg << " deg"
		<< "\n------------------------------\n" << G4endl;
	}

	//Get analysis manager
    auto analysisManager = G4AnalysisManager::Instance();

    //Fill histograms
	if (fScreenNo >= 0 && fScreenNo < fScreenCount)
	{    
		analysisManager->FillH1(0, fScreenNo);
		analysisManager->FillH1(1, angle);
		if( angle < 180.*deg - bigAngle || angle > 180.*deg + bigAngle )
		{
			analysisManager->FillH1(2, fScreenNo);
			analysisManager->FillH1(3, angle);
		}
	}
} 
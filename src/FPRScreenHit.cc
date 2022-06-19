#include "FPRScreenHit.hh"

#include "Geant4/G4UnitsTable.hh"
#include "Geant4/G4VVisManager.hh"
#include "Geant4/G4Circle.hh"
#include "Geant4/G4Colour.hh"
#include "Geant4/G4VisAttributes.hh"

#include <iomanip>

G4ThreadLocal G4Allocator<FPRScreenHit>* FPRScreenHitAllocator=0;

FPRScreenHit::FPRScreenHit() :
	G4VHit(),
	trackID(-1),
	screenNb(-1),
	pos(G4ThreeVector()) 
{}

FPRScreenHit::FPRScreenHit(const FPRScreenHit& right)
 : G4VHit()
{
	trackID   = right.trackID;
	screenNb  = right.screenNb;
	pos       = right.pos;
}

FPRScreenHit::~FPRScreenHit() {}

const FPRScreenHit& FPRScreenHit::operator=(const FPRScreenHit& right)
{
	trackID   = right.trackID;
	screenNb  = right.screenNb;
	pos       = right.pos;
	return *this;
}

G4bool FPRScreenHit::operator==(const FPRScreenHit& right) const
{
	return (this==&right) ? true : false;
}

void FPRScreenHit::Draw()
{
	G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
	if(pVVisManager)
	{
		G4Circle circle(pos);
		circle.SetScreenSize(2.);
		circle.SetFillStyle(G4Circle::filled);
		G4Colour colour(1.,0.,0.);
		G4VisAttributes attribs(colour);
		circle.SetVisAttributes(attribs);
		pVVisManager->Draw(circle);
	}
}

void FPRScreenHit::Print()
{
  	G4cout << "  TrackID: " << trackID 
	  		<< ",  Screen hit: " << screenNb 
			<< ",  Position: " << G4BestUnit(pos,"Length") << G4endl;
}


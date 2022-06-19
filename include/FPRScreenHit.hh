#ifndef FPRSCREENHIT
#define FPRSCREENHIT

#include "Geant4/G4VHit.hh"
#include "Geant4/G4THitsCollection.hh"
#include "Geant4/G4Allocator.hh"
#include "Geant4/G4ThreeVector.hh"
#include "Geant4/tls.hh"

class FPRScreenHit : public G4VHit
{
  	public:

		FPRScreenHit();
		FPRScreenHit(const FPRScreenHit&);
		~FPRScreenHit();
		
		const FPRScreenHit& operator=(const FPRScreenHit&);
		G4bool operator==(const FPRScreenHit&) const;

		inline void* operator new(size_t);
		inline void  operator delete(void*);

		void Draw();
		void Print();

	public:
	
		void SetTrackID   	(G4int track)      	{ trackID = track; };
		void SetScreenNb	(G4int screen)     	{ screenNb = screen; };  
		void SetPos      	(G4ThreeVector xyz)	{ pos = xyz; };
		
		G4int GetTrackID()    	{ return trackID; };
		G4int GetScreenNb()  	{ return screenNb; };
		G4ThreeVector GetPos()	{ return pos; };
			
	private:
	
		G4int         trackID;
		G4int         screenNb;
		G4ThreeVector pos;
};

typedef G4THitsCollection<FPRScreenHit> FPRScreenHitsCollection;

extern G4ThreadLocal G4Allocator<FPRScreenHit>* FPRScreenHitAllocator;

inline void* FPRScreenHit::operator new(size_t)
{
	if(!FPRScreenHitAllocator)
	{
     	FPRScreenHitAllocator = new G4Allocator<FPRScreenHit>;
	}
	void * hit = FPRScreenHitAllocator->MallocSingle();
	return hit;	
}

inline void FPRScreenHit::operator delete(void *hit)
{
    if ( ! FPRScreenHitAllocator) {
        FPRScreenHitAllocator = new G4Allocator<FPRScreenHit>;
    }
    FPRScreenHitAllocator->FreeSingle(reinterpret_cast<FPRScreenHit *>(hit));
}

#endif
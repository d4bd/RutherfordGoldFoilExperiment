#ifndef FPRDETECTORCONSTRUCTION
#define FPRDETECTORCONSTRUCTION

#include "FPRDetectorMessenger.hh"

#include "Geant4/G4VUserDetectorConstruction.hh"
#include "Geant4/G4Material.hh"

class G4LogicalVolume;

class FPRDetectorConstruction : public G4VUserDetectorConstruction
{
	public:

		FPRDetectorConstruction();
		FPRDetectorConstruction(G4int screenNo, G4double openingAngle);
		~FPRDetectorConstruction();

		G4VPhysicalVolume* Construct();
		virtual void ConstructSDandField();

	///-----------------------------
	/// FOIL
	///-----------------------------

	public:
		void SetFoilMaterial(G4String);

	private:
		G4double fFoilYZDimesion;
		G4double fFoilThickness;
		G4Material* fFoilMaterial;
		G4LogicalVolume* fLogicFoil;

	///-----------------------------
	/// DETECTOR BOX AND SCREEN
	///-----------------------------
	public:
		static G4int returnScreenNo()	{ return fScreenNo; }
		static void setScreenNo(G4int num) { fScreenNo = num; }
		static G4double returnOpeningAngle()	{ return fOpeningAngle; }
		static void setOpeningAngle(G4int angl) { fOpeningAngle = angl; }

	private:
		static G4int fScreenNo;
		G4double fOpeningLenght;
		G4double fDetectorRadius;
		G4double fZnSLayerDepht;
		G4double fDepthScreen;
		G4double fHeightScreen;
		G4Material* ZnS;
		G4Material* fBackScreenMaterial;
		G4LogicalVolume* fLogicZnS;
		G4LogicalVolume* fLogicDetector;

		static G4double fOpeningAngle;

	///-----------------------------
	/// EMITTER
	///-----------------------------

	private:
		G4double fEmitterXDimension;
		G4double fEmitterYZDimension; 
		G4Material* fEmitterMaterial;

		G4double fCollimatorRadius;

	///-----------------------------
	/// WORLD
	///-----------------------------

	public:
		void SetWorldMaterialAir();
		void SetWorldMaterialVoid();

	private:
		G4Material* fWorldMaterial;
		G4LogicalVolume* fLogicWorld;

	///-----------------------------
	/// MESSENGER
	///-----------------------------
	
	private:
		FPRDetectorMessenger* fMessenger;
};


#endif
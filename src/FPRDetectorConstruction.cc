#include "FPRDetectorConstruction.hh"
#include "FPRScreenParametrization.hh"
#include "FPRScreenSD.hh"


#include "Geant4/G4VSolid.hh"
#include "Geant4/G4Box.hh"
#include "Geant4/G4Tubs.hh"
#include "Geant4/G4LogicalVolume.hh"
#include "Geant4/G4ThreeVector.hh"
#include "Geant4/G4PVPlacement.hh"
#include "Geant4/globals.hh"
#include "Geant4/G4SystemOfUnits.hh"
#include "Geant4/G4NistManager.hh"
#include "Geant4/G4PVParameterised.hh"
#include "Geant4/G4SubtractionSolid.hh"
#include "Geant4/G4SDManager.hh"
#include "Geant4/G4AutoDelete.hh"


#include <cmath>

//fScreenNo must always be > 1
G4int FPRDetectorConstruction::fScreenNo = 20;

G4double FPRDetectorConstruction::fOpeningAngle = 0.*deg;

FPRDetectorConstruction::FPRDetectorConstruction() 
: fFoilYZDimesion(0), fFoilThickness(0), fFoilMaterial(nullptr), fLogicFoil(nullptr),
    fOpeningLenght(0), fDetectorRadius(0), fZnSLayerDepht(0), fDepthScreen(0), fHeightScreen(0), 
    ZnS(nullptr), fBackScreenMaterial(nullptr), fLogicZnS(nullptr),
    fLogicDetector(nullptr),
    fEmitterXDimension(0), fEmitterYZDimension(0), fEmitterMaterial(nullptr), 
    fCollimatorRadius(0),
    fWorldMaterial(nullptr), fLogicWorld(nullptr)
{
    fMessenger = new FPRDetectorMessenger(this);
}

FPRDetectorConstruction::FPRDetectorConstruction(G4int screenNo, G4double openingAngle) 
: fFoilYZDimesion(0), fFoilThickness(0), fFoilMaterial(nullptr), fLogicFoil(nullptr),
    fOpeningLenght(0), fDetectorRadius(0), fZnSLayerDepht(0), fDepthScreen(0), fHeightScreen(0),
    ZnS(nullptr), fBackScreenMaterial(nullptr), fLogicZnS(nullptr),
    fLogicDetector(nullptr),
    fEmitterXDimension(0), fEmitterYZDimension(0), fEmitterMaterial(nullptr), 
    fCollimatorRadius(0),
    fWorldMaterial(nullptr), fLogicWorld(nullptr)
{
    fMessenger = new FPRDetectorMessenger(this);
    setScreenNo(screenNo);
    setOpeningAngle(openingAngle);
}
 

FPRDetectorConstruction::~FPRDetectorConstruction()
{
    delete fMessenger;
}

G4VPhysicalVolume* FPRDetectorConstruction::Construct()
{
    // Get nist material manager
    G4NistManager* nist = G4NistManager::Instance();

    // Option to switch on/off checking of volumes overlaps
    //
    G4bool checkOverlaps = true;

    ////////////////////////////////////////////////////////////////////////
    ////////////////////////      VARIABLES      ///////////////////////////
    ////////////////////////////////////////////////////////////////////////

    ///-----------------------------
    /// FOIL
    ///-----------------------------

    fFoilYZDimesion = 5.*cm;
    fFoilThickness = 1.*um;
    fFoilMaterial = nist->FindOrBuildMaterial("G4_Au");

    ///-----------------------------
    /// DETECTOR BOX AND SCREEN
    ///-----------------------------

    fOpeningLenght = 1.*cm;
    fDetectorRadius = 20.*cm;
    fZnSLayerDepht = 0.5*mm;
    fDepthScreen = 5.*mm;
    fHeightScreen = 60.*cm;

    fOpeningAngle = ((atan((fOpeningLenght * 0.5)/fDetectorRadius))/M_PI) * (180.*deg);
    G4double spacingAngle = (360.*deg - (2. * fOpeningAngle)) / fScreenNo;
    G4double halfWidthScreen = fDetectorRadius * tan( ((0.5 * spacingAngle)/deg)*M_PI/180. );

    //Zns : Solfuro di Zinco
    G4double A;
    G4double Z;

    A = 65.38*g/mole;
    G4Element* elZn = new G4Element("Zinc","Zn",Z = 30.,A);

    A = 32.064*g/mole;
    G4Element* elS = new G4Element("Sulfur","S",Z = 16.,A);

    G4double d = 4.09*g/cm3;
    ZnS = new G4Material("ZnS",d,2);
    ZnS->AddElement(elZn,1);
    ZnS->AddElement(elS,1);

    fBackScreenMaterial = nist->FindOrBuildMaterial("G4_GLASS_PLATE");

    G4double detectorContainerInnerRadius = fDetectorRadius;
    G4double detectorContainerOuterRadius = (fDetectorRadius + fDepthScreen) / cos( ((0.5 * spacingAngle)/deg)*M_PI/180. );

    ///-----------------------------
    /// EMITTER
    ///-----------------------------

    fEmitterXDimension = 20.*cm;
    fEmitterYZDimension = 8.*cm; 
    fCollimatorRadius = 1.*mm;
    fEmitterMaterial = nist->FindOrBuildMaterial("G4_Pb");

    ///-----------------------------
    /// WORLD
    ///-----------------------------

    G4double worldSizeX = detectorContainerOuterRadius + 15.*cm + fEmitterXDimension;
    G4double worldSizeY = detectorContainerOuterRadius + 5.*cm;
    G4double worldSizeZ = 1.3 * fHeightScreen;
    fWorldMaterial = nist->FindOrBuildMaterial("G4_Galactic");

    ////////////////////////////////////////////////////////////////////////
    ///////////////////////      WORLD      ////////////////////////////////
    ////////////////////////////////////////////////////////////////////////

    G4Box* solidWorld =    
    new G4Box("World",                          //its name
       worldSizeX, worldSizeY, 0.5*worldSizeZ); //its size
        
    fLogicWorld =                         
        new G4LogicalVolume(solidWorld,         //its solid
                            fWorldMaterial,     //its material
                            "World");           //its name
                                    
    G4VPhysicalVolume* physWorld = 
        new G4PVPlacement(0,                    //no rotation
                        G4ThreeVector(),        //at (0,0,0)
                        fLogicWorld,            //its logical volume
                        "World",                //its name
                        0,                      //its mother  volume
                        false,                  //no boolean operation
                        0,                      //copy number
                        checkOverlaps);         //overlaps checking  

    ////////////////////////////////////////////////////////////////////////
    ////////////////////////      FOIL      ////////////////////////////////
    ////////////////////////////////////////////////////////////////////////
    
    G4Box* solidFoil =    
    new G4Box("Foil",                                                   //its name
       0.5*fFoilThickness, 0.5*fFoilYZDimesion, 0.5*fFoilYZDimesion);   //its size
        
    fLogicFoil=                         
        new G4LogicalVolume(solidFoil,          //its solid
                            fFoilMaterial,      //its material
                            "Foil");            //its name
                                    
    new G4PVPlacement(0,                        //no rotation
                    G4ThreeVector(),            //at (0,0,0)
                    fLogicFoil,                 //its logical volume
                    "Foil",                     //its name
                    fLogicWorld,                //its mother  volume
                    false,                      //no boolean operation
                    0,                          //copy number
                    checkOverlaps);             //overlaps checking  

    ////////////////////////////////////////////////////////////////////////
    ////////////////////////      DETECTOR      ////////////////////////////
    ////////////////////////////////////////////////////////////////////////
  
    ///-----------------------------
    /// DETECTOR BOX
    ///-----------------------------

    G4Tubs* detectorFull = new G4Tubs("DetectorFull", 
                            detectorContainerInnerRadius, 
                            detectorContainerOuterRadius, 
                            0.5 * (1.1 * fHeightScreen), 
                            0.*deg, 360.*deg);

    G4double xDimensionHole = 1.2*(detectorContainerOuterRadius 
                                - detectorContainerInnerRadius);
    G4double yDimensionHole = fOpeningLenght - 1.*mm;
    G4double zDimensionHole = 1.15 * fHeightScreen;

    G4Box* detectorHole = new G4Box("DetectorHole", 
                            0.5*xDimensionHole, 
                            0.5*yDimensionHole, 
                            0.5*zDimensionHole);

    G4double xPositionHole = 0.5*(detectorContainerOuterRadius 
                                - detectorContainerInnerRadius) 
                                + detectorContainerInnerRadius;

    G4VSolid* solidDetector = new G4SubtractionSolid("Detector", 
                            detectorFull, detectorHole, 
                            0, G4ThreeVector(xPositionHole, 0., 0.));

    fLogicDetector =                         
        new G4LogicalVolume(solidDetector,  //its solid
                            fWorldMaterial, //its material
                            "Detector");    //its name
                            
    new G4PVPlacement(0,                    //no rotation
                    G4ThreeVector(),        //at (0,0,0)
                    fLogicDetector,         //its logical volume
                    "Detector",             //its name
                    fLogicWorld,            //its mother  volume
                    false,                  //no boolean operation
                    0,                      //copy number
                    checkOverlaps);         //overlaps checking  

    ///-----------------------------
    /// DETECTOR SCREENS
    ///-----------------------------

    G4Box* solidScreen =    
    new G4Box("Screen",        
       0.5*fDepthScreen, 
       halfWidthScreen, 
       0.5*fHeightScreen);     
        
    G4LogicalVolume* logicScreen =                         
        new G4LogicalVolume(solidScreen,        //its solid
                            fWorldMaterial,     //its material
                            "Screen");          //its name

    G4Box* solidZnS =    
    new G4Box("ScreenZnS",                                      
       0.5*fZnSLayerDepht, 
       halfWidthScreen, 
       0.5*fHeightScreen);     
        
    fLogicZnS =                         
        new G4LogicalVolume(solidZnS,           //its solid
                            ZnS,                //its material
                            "ScreenZnS");       //its name

    new G4PVPlacement(0,                                                                //no rotation
                    G4ThreeVector(- (0.5*fDepthScreen) + (0.5*fZnSLayerDepht), 
                                    0., 0.), 
                    fLogicZnS,                                                          //its logical volume
                    "ScreenZnS",                                                        //its name
                    logicScreen,                                                        //its mother  volume
                    false,                                                              //no boolean operation
                    0,                                                                  //copy number
                    checkOverlaps);                                                     //overlaps checking
                    
    G4Box* solidScreenBack =    
    new G4Box("ScreenBack",                                      
       0.5*(fDepthScreen - fZnSLayerDepht), 
       halfWidthScreen, 
       0.5*fHeightScreen);    
        
    G4LogicalVolume* logicScreenBack =                         
        new G4LogicalVolume(solidScreenBack,    //its solid
                            fBackScreenMaterial,//its material
                            "ScreenBack");      //its name

    new G4PVPlacement(0,                                            //no rotation
                    G4ThreeVector(0.5*fZnSLayerDepht, 0., 0.),       
                    logicScreenBack,                                //its logical volume
                    "ScreenBack",                                   //its name
                    logicScreen,                                    //its mother  volume
                    false,                                          //no boolean operation
                    0,                                              //copy number
                    checkOverlaps);                                 //overlaps checking

    auto screenParam = new FPRScreenParameterisation(fScreenNo,
        fDetectorRadius + (0.5 * fDepthScreen),
        fOpeningAngle,
        spacingAngle);

    new G4PVParameterised(
                        "Screen",       // their name
                        logicScreen,    // their logical volume
                        fLogicDetector, // Mother logical volume
                        kUndefined,     // Are placed along this axis 
                        fScreenNo,      // Number of chambers
                        screenParam);   // The parametrisation

    ////////////////////////////////////////////////////////////////////////
    ////////////////////////      EMITTER      /////////////////////////////
    ////////////////////////////////////////////////////////////////////////

    fEmitterXDimension = 20.*cm;
    fEmitterYZDimension = 8.*cm; 
    fCollimatorRadius = 1.*mm;
    fEmitterMaterial = nist->FindOrBuildMaterial("G4_Pb");

    G4Box* emitterCase = new G4Box("EmitterCase", 
                                0.5*fEmitterXDimension, 
                                0.5*fEmitterYZDimension, 
                                0.5*fEmitterYZDimension);

    G4Box* emitterCavity = new G4Box("EmitterCavity", 
                                0.5*0.2*fEmitterYZDimension, 
                                0.5*0.2*fEmitterYZDimension, 
                                0.5*0.2*fEmitterYZDimension);

    G4Tubs* collimator = new G4Tubs("Collimator", 
                                0.*m, fCollimatorRadius, 
                                0.5*0.6*fEmitterXDimension,
                                0.*deg, 360.*deg);

    G4VSolid* emitter 
        = new G4SubtractionSolid("Emitter1", 
            emitterCase, emitterCavity, 
            0, G4ThreeVector(0.5*0.2*fEmitterYZDimension, 0., 0.));

    G4RotationMatrix* rm = new G4RotationMatrix();
    rm->rotateY(90.*deg);

    G4VSolid* solidEmitter 
        = new G4SubtractionSolid("Emitter", 
            emitter, collimator, 
            rm, G4ThreeVector(-0.5*0.6*fEmitterXDimension, 0., 0.));

    G4LogicalVolume* logicEmitter =                         
        new G4LogicalVolume(solidEmitter,                               //its solid
                            fEmitterMaterial,                           //its material
                            "Emitter");                                 //its name

    new G4PVPlacement(0,                                                //no rotation
                    G4ThreeVector(detectorContainerOuterRadius 
                        + 10.*cm + 0.5*fEmitterXDimension, 0., 0.),     
                    logicEmitter,                                       //its logical volume
                    "Emitter",                                          //its name
                    fLogicWorld,                                        //its mother  volume
                    false,                                              //no boolean operation
                    0,                                                  //copy number
                    checkOverlaps);                                     //overlaps checking 

    //Dummy definition for PrimaryGeneratorAction 
    //of the logicVolume of the collider                       
    new G4LogicalVolume(collimator,                                     //its solid
                    fWorldMaterial,                                     //its material
                    "Collimator");                                      //its name 

   return physWorld;
}

void FPRDetectorConstruction::ConstructSDandField()
{
    ////////////////////////////////////////////////////////////////////////
    //////////////////      SENSITIVE DETECTOR      ////////////////////////
    ////////////////////////////////////////////////////////////////////////

    G4String screenSDname = "FPR/ScreenSD";
    FPRScreenSD* aScreenSD = new FPRScreenSD(screenSDname,
                                                "ScreenHitsCollection");
    G4SDManager::GetSDMpointer()->AddNewDetector(aScreenSD);
    SetSensitiveDetector( fLogicZnS,  aScreenSD );
}

void FPRDetectorConstruction::SetFoilMaterial(G4String materialName)
{
    G4NistManager* nistManager = G4NistManager::Instance();

    G4Material* pttoMaterial =
                nistManager->FindOrBuildMaterial(materialName);

    if (fFoilMaterial != pttoMaterial) 
    {
        if ( pttoMaterial ) 
        {
            fFoilMaterial = pttoMaterial;
            if (fLogicFoil) fLogicFoil->SetMaterial(fFoilMaterial);
            G4cout << "\n----> The target is now made of " << materialName << "\n" << G4endl;
        } 
        else 
        {
            G4cout << "\n-->  WARNING from SetFoilMaterial : "
            << materialName << " not found\n" << G4endl;
        }
  }
}

void FPRDetectorConstruction::SetWorldMaterialAir()
{
    G4NistManager* nistManager = G4NistManager::Instance();

    G4Material* pttoMaterial =
                nistManager->FindOrBuildMaterial("G4_AIR");

    if (fWorldMaterial != pttoMaterial) 
    {
        fWorldMaterial = pttoMaterial;
        if (fLogicFoil)
        {
            fLogicWorld->SetMaterial(fWorldMaterial);
            fLogicDetector->SetMaterial(fWorldMaterial);
            G4cout << "\n----> The world is now made of air\n" << G4endl;
        }
    }
}

void FPRDetectorConstruction::SetWorldMaterialVoid()
{
    G4NistManager* nistManager = G4NistManager::Instance();

    G4Material* pttoMaterial =
                nistManager->FindOrBuildMaterial("G4_Galactic");

    if (fWorldMaterial != pttoMaterial) 
    {
        fWorldMaterial = pttoMaterial;
        if (fLogicFoil)
        {
            fLogicWorld->SetMaterial(fWorldMaterial);
            fLogicDetector->SetMaterial(fWorldMaterial);
            G4cout << "\n----> The world is now made of void\n" << G4endl;
        }
    }
}
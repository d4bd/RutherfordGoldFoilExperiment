#include "FPRPhysicsList.hh"
#include "FPRPhysicsListMessenger.hh"
#include "FPRStepMax.hh"

#include "Geant4/G4ParticleTypes.hh"
#include "Geant4/G4SystemOfUnits.hh"
#include "Geant4/G4EmStandardPhysics.hh"
#include "Geant4/G4EmStandardPhysics_option1.hh"
#include "Geant4/G4EmStandardPhysics_option2.hh"
#include "Geant4/G4EmStandardPhysics_option3.hh"
#include "Geant4/G4EmStandardPhysics_option4.hh"
#include "Geant4/G4EmLivermorePhysics.hh"
#include "Geant4/G4EmPenelopePhysics.hh"
#include "Geant4/G4DecayPhysics.hh"
#include "Geant4/G4ProcessManager.hh"
#include "Geant4/G4Gamma.hh"
#include "Geant4/G4Electron.hh"
#include "Geant4/G4Positron.hh"

FPRPhysicsList::FPRPhysicsList()
{
	fMessenger = new FPRPhysicsListMessenger(this);

	SetVerboseLevel(1);

	// EM physics
	fEmName = G4String("emlivermore");  

	fEmPhysicsList = new G4EmLivermorePhysics();

	// Deacy physics and all particles
	fDecPhysicsList = new G4DecayPhysics();
}

FPRPhysicsList::~FPRPhysicsList()
{
	delete fMessenger;
	delete fEmPhysicsList;
	delete fDecPhysicsList;
}

void FPRPhysicsList::ConstructParticle()
{
	fDecPhysicsList->ConstructParticle();
}

void FPRPhysicsList::ConstructProcess()
{
 	// transportation
	AddTransportation();
	
	// electromagnetic physics list
	fEmPhysicsList->ConstructProcess();

	// decay physics list
	fDecPhysicsList->ConstructProcess();   
}

void FPRPhysicsList::AddPhysicsList(const G4String& name)
{
	if (verboseLevel>1) 
	{
		G4cout << "FPRPhysicsList::AddPhysicsList: <" << name << ">" << G4endl;
	}

	if (name == fEmName) return;

	if (name == "emstandard_opt0") 
	{
		fEmName = name;
		delete fEmPhysicsList;
		fEmPhysicsList = new G4EmStandardPhysics(1);

	} 
	else if (name == "emstandard_opt1") 
	{
		fEmName = name;
		delete fEmPhysicsList;
		fEmPhysicsList = new G4EmStandardPhysics_option1();

	} 
	else if (name == "emstandard_opt2") 
	{
		fEmName = name;
		delete fEmPhysicsList;
		fEmPhysicsList = new G4EmStandardPhysics_option2();
		
	} 
	else if (name == "emstandard_opt3") 
	{
		fEmName = name;
		delete fEmPhysicsList;
		fEmPhysicsList = new G4EmStandardPhysics_option3();    
	}
	else if (name == "emstandard_opt4") 
	{
		fEmName = name;
		delete fEmPhysicsList;
		fEmPhysicsList = new G4EmStandardPhysics_option4();    
	} 
	else if (name == "emlivermore") 
	{
		fEmName = name;
		delete fEmPhysicsList;
		fEmPhysicsList = new G4EmLivermorePhysics();
	} 
	else if (name == "empenelope") 
	{	
		fEmName = name;
		delete fEmPhysicsList;
		fEmPhysicsList = new G4EmPenelopePhysics();
	} 
}
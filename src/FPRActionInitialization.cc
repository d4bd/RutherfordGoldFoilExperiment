#include "FPRActionInitialization.hh"
#include "FPRPrimaryGeneratorAction.hh"
#include "FPRRunAction.hh"
#include "FPREventAction.hh"
#include "FPRSteppingAction.hh"

FPRActionInitialization::FPRActionInitialization()
 : G4VUserActionInitialization()
{}

FPRActionInitialization::~FPRActionInitialization()
{}

void FPRActionInitialization::BuildForMaster() const
{
  SetUserAction(new FPRRunAction);
}

void FPRActionInitialization::Build() const
{
  //Event generation
  SetUserAction(new FPRPrimaryGeneratorAction);

  //Run action
  SetUserAction(new FPRRunAction);

  //Event action
  SetUserAction(new FPREventAction);

  //Stepping action
  SetUserAction(new FPRSteppingAction);
}  
// NikotiN Game Studio. All Rights Reserved 


#include "STUGameModeBase.h"
#include "Player/STU_Character.h"
#include "Player/STU_PlayerController.h"

ASTUGameModeBase::ASTUGameModeBase()
{

	DefaultPawnClass = ASTU_Character::StaticClass();
	PlayerControllerClass = ASTU_PlayerController::StaticClass();

}
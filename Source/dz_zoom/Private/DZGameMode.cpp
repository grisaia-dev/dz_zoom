// DZ_ZOOM by Eugene.


#include "DZGameMode.h"
#include "Player/DZPlayerCharacter.h"
#include "Player/DZPlayerController.h"

ADZGameMode::ADZGameMode() {
	DefaultPawnClass = ADZPlayerCharacter::StaticClass();
	PlayerControllerClass = ADZPlayerController::StaticClass();
}
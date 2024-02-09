// DZ_ZOOM by Eugene.


#include "Player/DZPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/DecalComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ADZPlayerCharacter::ADZPlayerCharacter() {
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->SetUsingAbsoluteRotation(true);
	SpringArmComponent->TargetArmLength = ArmLength;
	SpringArmComponent->SetRelativeRotation(FRotator(ArmYRotation, 0.0f, 0.0f));
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->bEnableCameraLag = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->SetFieldOfView(CameraFOV);
	CameraComponent->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

// Called when the game starts or when spawned
void ADZPlayerCharacter::BeginPlay() {
	Super::BeginPlay();
	if (CursorMaterial)
		CurrentCursor = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), CursorMaterial, CursorSize, FVector(0));
	
}

// Called every frame
void ADZPlayerCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		FHitResult ResultHit;
		PC->GetHitResultUnderCursor(ECC_GameTraceChannel1, true, ResultHit);
		float FindRotatorResultYaw = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),
			ResultHit.Location).Yaw;
		SetActorRotation(FQuat(FRotator(0.0f, FindRotatorResultYaw, 0.0f)));
		if (CurrentCursor)
		{
			CurrentCursor->SetWorldLocation(ResultHit.Location);
		}
	}

}

// Called to bind functionality to input
void ADZPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("PMoveForward", this, &ADZPlayerCharacter::PMoveForward);
	PlayerInputComponent->BindAxis("PMoveRight", this, &ADZPlayerCharacter::PMoveRight);
	PlayerInputComponent->BindAxis("PZoom", this, &ADZPlayerCharacter::PZoom);

}

void ADZPlayerCharacter::PMoveForward(float Value) {
	AddMovementInput(GetActorForwardVector(), Value);
}

void ADZPlayerCharacter::PMoveRight(float Value) {
	AddMovementInput(GetActorRightVector(), Value);
}

void ADZPlayerCharacter::PZoom(float Value) {
	if (!CameraComponent) return;
	FVector pos = CameraComponent->GetRelativeLocation();
	float newPosX = pos[0] + Value * ZoomStep;
	pos[0] = FMath::Clamp(newPosX, MinZoomLength, MaxZoomLength);
	CameraComponent->SetRelativeLocation(pos);
}
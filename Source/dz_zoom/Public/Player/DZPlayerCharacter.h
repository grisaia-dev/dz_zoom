// DZ_ZOOM by Eugene.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DZPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class DZ_ZOOM_API ADZPlayerCharacter : public ACharacter {
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADZPlayerCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY()
	UDecalComponent* CurrentCursor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	UMaterialInterface* CursorMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	FVector CursorSize = FVector(20.0f, 40.0f, 40.0f);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void PMoveForward(float Value);
	void PMoveRight(float Value);

	float ArmLength = 1400.F;
	float ArmYRotation = -75.f;
	float CameraFOV = 55.f;
};

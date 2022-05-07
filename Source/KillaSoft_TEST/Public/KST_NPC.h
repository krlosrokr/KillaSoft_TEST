// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KST_NPC.generated.h"


class UWidgetComponent;
class UWidget;
class UKST_MarkerWidget;

UCLASS()
class KILLASOFT_TEST_API AKST_NPC : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Appearance")
	FColor NPC_Color;


public:
	// Sets default values for this character's properties
	AKST_NPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

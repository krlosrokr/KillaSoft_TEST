// Fill out your copyright notice in the Description page of Project Settings.


#include "KST_NPC.h"
#include "WidgetBlueprint.h"
#include "Components/WidgetComponent.h"
#include "Components/Widget.h"

// Sets default values
AKST_NPC::AKST_NPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	NPC_Color = FColor::Blue;
}

// Called when the game starts or when spawned
void AKST_NPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKST_NPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKST_NPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


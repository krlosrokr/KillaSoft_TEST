// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KST_Marker.generated.h"

class UKST_MarkerWidget;
class UWidgetComponent;

UCLASS()
class KILLASOFT_TEST_API AKST_Marker : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Marker|Widget")
	float HideDistance = 15.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Marker|Widget")
	bool bForcedHide;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Marker|Widget")
	bool bOnScreen;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Marker|Widget")
	bool bShowDistance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Marker")
	AActor* CurrentOwner;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Marker|Widget")
	FColor Color;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Marker|Widget")
	TSubclassOf<UKST_MarkerWidget> HUDMarkerClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Marker|Widget")
	TSubclassOf<UKST_MarkerWidget> WorldMarkerClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Marker|Widget")
	UKST_MarkerWidget* HUDMarker;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Marker|Widget")
	UKST_MarkerWidget* WorldMarker;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Marker|Widget")
	UWidgetComponent* WorldWidgetComponent;

	UPROPERTY(BlueprintReadWrite, Category = "Marker|Material")
	UMaterialInstanceDynamic* HudMaterial;
	UPROPERTY(BlueprintReadWrite, Category = "Marker|Material")
	UMaterialInstanceDynamic* WorldMaterial;



public:	
	// Sets default values for this actor's properties
	AKST_Marker();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Marker|Info")
	float GetDistanceFromActor(AActor* TargetActor = nullptr);

	UFUNCTION(BlueprintCallable, Category = "Marker|GamePlay")
	void Remove();

	UFUNCTION(BlueprintCallable, Category = "Marker|GamePlay")
	void Hide();

	UFUNCTION(BlueprintCallable, Category = "Marker|GamePlay")
	void Show();

	UFUNCTION(BlueprintCallable, Category = "Marker")
	void SetColor();

	UFUNCTION(BlueprintCallable, Category = "Marker")
	bool IsOnScreen(bool bPlayerViewportRelative);

	UFUNCTION(BlueprintCallable, Category = "Marker")
	void HandleOnScreen();

	UFUNCTION(BlueprintCallable, Category = "Marker")
	void HandleDistance();

	UFUNCTION(BlueprintCallable, Category = "Marker")
	bool IsOverlapingPlayerCharacter();

};

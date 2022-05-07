// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KST_MarkerManagerComponent.generated.h"

class UKST_MarkerWidget;
class AKST_Marker;
class UWidgetComponent;
class UKST_NavArrowWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KILLASOFT_TEST_API UKST_MarkerManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UKST_MarkerManagerComponent();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Marker")
	FName MarkerSocket = "MarkerSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Marker")
	int CurrentMarkerIndex = -1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Marker")
	bool bMarkerSet = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Marker")
	TArray <AKST_Marker*> Markers;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Marker")
	TArray <UKST_MarkerWidget*> MarkerWidgets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Marker")
	TArray <UKST_MarkerWidget*> WorldMarkerWidgets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Marker|Widget")
	TSubclassOf<UKST_NavArrowWidget> NavArrowClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Marker|Widget")
	UKST_NavArrowWidget* NavArrow;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Marker|Widget")
	UWidgetComponent* NavWidgetComponent;

public:

	UFUNCTION(BlueprintCallable, Category = "Marker")
	void CreateMarkerActor(AActor* TargetActor, TSubclassOf<AKST_Marker> Marker, FColor Color, bool bShowDistance = false);

	UFUNCTION(BlueprintCallable, Category = "Marker")
	void CreateMarkerLocation(FVector Location, TSubclassOf<AKST_Marker> Marker, FColor Color, bool bShowDistance = false);

	UFUNCTION(BlueprintCallable, Category = "Marker")
	void Add(AKST_Marker* Marker);

	UFUNCTION(BlueprintCallable, Category = "Marker")
	void Remove(AKST_Marker* Marker);

	UFUNCTION(BlueprintCallable, Category = "Marker")
	void RemoveActorRef(AActor* TargetActor);

	UFUNCTION(BlueprintCallable, Category = "Marker")
	void HideAll();

	UFUNCTION(BlueprintCallable, Category = "Marker")
	void ShowAll();

	UFUNCTION(BlueprintCallable, Category = "Marker")
	void ClearAll();

	UFUNCTION(BlueprintCallable, Category = "Marker")
	TArray<AActor*> GetAll();

	UFUNCTION(BlueprintCallable, Category = "Marker")
	void CreateNavArrow();

	UFUNCTION(BlueprintCallable, Category = "Marker")
	void DestroyNavArrow();

	UFUNCTION(BlueprintCallable, Category = "Marker")
	void UpdateArrowRotation();

	UFUNCTION(BlueprintCallable, Category = "Marker")
	void SwitchCurrentMarker();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KST_MarkerWidget.generated.h"

class AActor;
class UTextBlock;
class UImage;
class UKismetMathLibrary;
class UWidgetTree;
class UPanelWidget;

/**
 * 
 */
UCLASS()
class KILLASOFT_TEST_API UKST_MarkerWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Marker|Parent")
	AActor* CurrentOwner;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Marker|Text")
	UTextBlock* DistanceInfo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Marker|Image")
	TArray<UImage*> WidgetImages;

	//-------------------------------------------------------------------------

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Marker|Image")
	UImage* FrameImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Marker|Image")
	UImage* MarkerImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Marker|Image")
	UImage* GridImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Marker|Image")
	UImage* BgImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Marker|Text")
	float FontSize_Close;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Marker|Text")
	float FontSize_Far;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Marker|Image")
	FVector2D ImageSize_Close;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Marker|Image")
	FVector2D ImageSize_Far;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Marker|Canvas")
	float Z_Position;

public:

	UFUNCTION(BlueprintCallable, Category = "Init")
	void CreateDefault();

	UFUNCTION(BlueprintCallable, Category = "Init")
	void InitializeWidget();

	UFUNCTION(BlueprintCallable, Category = "Info")
	float GetDistanceFromActor(AActor* TargetActor = nullptr);

};

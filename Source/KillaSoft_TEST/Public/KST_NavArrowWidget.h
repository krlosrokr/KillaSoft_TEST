// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KST_NavArrowWidget.generated.h"

/**
 * 
 */
UCLASS()
class KILLASOFT_TEST_API UKST_NavArrowWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "NavArrow|Parent")
	AActor* CurrentOwner;

};

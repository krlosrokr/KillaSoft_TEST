// Fill out your copyright notice in the Description page of Project Settings.


#include "KST_Marker.h"
#include "Widget/KST_MarkerWidget.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
// Sets default values
AKST_Marker::AKST_Marker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WorldWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WorldWidget"));
}

// Called when the game starts or when spawned
void AKST_Marker::BeginPlay()
{
	Super::BeginPlay();

	HUDMarker = CreateWidget<UKST_MarkerWidget>(GetWorld(), HUDMarkerClass);
	WorldMarker = CreateWidget<UKST_MarkerWidget>(GetWorld(), WorldMarkerClass);

	if (HUDMarker)
	{
		HUDMarker->CurrentOwner = this;
		HUDMarker->AddToViewport();
	}

	if (WorldMarker && WorldWidgetComponent)
	{
		WorldMarker->CurrentOwner = this;
		WorldWidgetComponent->SetWidget(WorldMarker);
		WorldWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		WorldWidgetComponent->SetDrawSize(FVector2D(50, 50));
		//WorldMarker->AddToViewport();
	}
}

// Called every frame
void AKST_Marker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleDistance();
}

float AKST_Marker::GetDistanceFromActor(AActor* TargetActor)
{
	float Distance = -1.0f;

	if (TargetActor == nullptr)
	{
		TargetActor = GetWorld()->GetFirstPlayerController()->GetPawn(); //Player 
	}

	if (IsValid(CurrentOwner) && IsValid(TargetActor))
	{
		Distance = UKismetMathLibrary::Vector_Distance(TargetActor->GetActorLocation(), CurrentOwner->GetActorLocation());
	}

	return Distance/100.0f; //-1.0f Means Invalid Actor, (/ 100) Converted to meters
}

void AKST_Marker::Remove()
{
	if (HUDMarker)
	{
		HUDMarker->RemoveFromParent();
	}

	if (WorldMarker)
	{
		WorldMarker->RemoveFromParent();
	}

	this->Destroy();
}

void AKST_Marker::Hide()
{
	bForcedHide = true;

	if (HUDMarker)
	{
		HUDMarker->SetVisibility(ESlateVisibility::Hidden);
	}

	if (WorldMarker)
	{
		WorldMarker->SetVisibility(ESlateVisibility::Hidden);
	}

}

void AKST_Marker::Show()
{
	bForcedHide = false;

	if (HUDMarker)
	{
		HUDMarker->SetVisibility(ESlateVisibility::Visible);
	}

	if (WorldMarker)
	{
		WorldMarker->SetVisibility(ESlateVisibility::Visible);
	}

}

void AKST_Marker::SetColor()
{

	if (HudMaterial)
	{
		HudMaterial->SetVectorParameterValue(FName("Color"), Color);
	}

	if (WorldMaterial)
	{
		WorldMaterial->SetVectorParameterValue(FName("Color"), Color);
	}

}

bool AKST_Marker::IsOnScreen(bool bPlayerViewportRelative)
{
	bool OnScreen=false;
	if (IsValid(CurrentOwner))
	{
		FVector2D ScreenPosition;
		FVector2D ViewportSize;

		bool btmp =	GetWorld()->GetFirstPlayerController()->ProjectWorldLocationToScreen(CurrentOwner->GetActorLocation(), ScreenPosition, bPlayerViewportRelative);
		GetWorld()->GetGameViewport()->GetViewportSize(ViewportSize);

		if (btmp)
		{
			if (ScreenPosition.X >= 0 && ScreenPosition.Y >= 0)
			{
				if (ScreenPosition.X <= ViewportSize.X && ScreenPosition.Y <= ViewportSize.Y)
				{
					OnScreen = true;
				}
			}
		}
	}
	return OnScreen;
}

void AKST_Marker::HandleOnScreen()
{
	if (bOnScreen)
	{

	}
	else
	{

	}
}

void AKST_Marker::HandleDistance()
{
	if (bForcedHide)
	{
		return;
	}

	float const Distance = GetDistanceFromActor();
	bool const OnScreen = IsOnScreen(true);

	if (Distance <= HideDistance && OnScreen)
	{
		if (HUDMarker)
		{
			HUDMarker->SetVisibility(ESlateVisibility::Hidden);
			//WorldWidgetComponent->SetWidgetSpace(EWidgetSpace::World);
		}
	}
	else if ((Distance > HideDistance) | (!OnScreen))
	{
		if (HUDMarker)
		{
			HUDMarker->SetVisibility(ESlateVisibility::Visible);
			//WorldWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		}
	}


}

bool AKST_Marker::IsOverlapingPlayerCharacter()
{
	


	return false;
}


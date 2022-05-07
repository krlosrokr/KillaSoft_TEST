// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/KST_MarkerWidget.h"
#include "GameFramework/Actor.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Blueprint/WidgetTree.h"
#include "Components/PanelWidget.h"
#include "Kismet/KismetMathLibrary.h"


void UKST_MarkerWidget::CreateDefault()
{
	UPanelWidget* RootWidget = Cast<UPanelWidget>(GetRootWidget());

	FrameImage = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), TEXT("Frame"));
	MarkerImage = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), TEXT("Marker"));
	GridImage = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), TEXT("Grid"));
	BgImage = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), TEXT("BackGround"));

	RootWidget->AddChild(FrameImage);
	RootWidget->AddChild(MarkerImage);
	RootWidget->AddChild(GridImage);
	RootWidget->AddChild(BgImage);
}


void UKST_MarkerWidget::InitializeWidget()
{

	////TEXTBox
	FontSize_Far = 18.0f;
	FontSize_Close = 24.0f;

	//Image

	

}

//Calculates the Distance From Marker to Actor

float UKST_MarkerWidget::GetDistanceFromActor(AActor* TargetActor)
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

	return Distance; //-1.0f Means Invalid Actor
}

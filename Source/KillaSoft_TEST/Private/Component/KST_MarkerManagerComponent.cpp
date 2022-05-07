// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/KST_MarkerManagerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Widget/KST_MarkerWidget.h"
#include "KST_Marker.h"
#include "Components/WidgetComponent.h"
#include "KST_NavArrowWidget.h"

// Sets default values for this component's properties
UKST_MarkerManagerComponent::UKST_MarkerManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


void UKST_MarkerManagerComponent::CreateMarkerActor(AActor* TargetActor, TSubclassOf<AKST_Marker> Marker, FColor Color, bool bShowDistance)
{
	if (TargetActor == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor is NUll!!"));
		return;
	}

	AKST_Marker* TmpMarker;
	FActorSpawnParameters SpawnParams;
	TmpMarker = GetWorld()->SpawnActor<AKST_Marker>(Marker, TargetActor->GetActorLocation(), TargetActor->GetActorRotation(), SpawnParams);

	if (IsValid(TmpMarker))
	{
		TmpMarker->CurrentOwner = TargetActor;
		TmpMarker->SetActorEnableCollision(false);
		TmpMarker->bShowDistance = bShowDistance;

		USkeletalMeshComponent* Mesh;
		Mesh = Cast<USkeletalMeshComponent>(TargetActor->FindComponentByClass(USkeletalMeshComponent::StaticClass()));
		
		if (IsValid(Mesh))
		{
			FVector TmpLoc = Mesh->GetSocketLocation(MarkerSocket);
			//TmpMarker->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, MarkerSocket);
			TmpMarker->SetActorLocation(TmpLoc);
			TmpMarker->AttachToActor(TargetActor, FAttachmentTransformRules::KeepWorldTransform);
		}
		else
		{
			TmpMarker->AttachToActor(TargetActor, FAttachmentTransformRules::SnapToTargetNotIncludingScale, MarkerSocket);
			UE_LOG(LogTemp, Warning, TEXT("Actor is NUll!!"));
		}
	
		TmpMarker->Color = Color;
		TmpMarker->SetColor();
		Add(TmpMarker);
	}
}

void UKST_MarkerManagerComponent::CreateMarkerLocation(FVector Location, TSubclassOf<AKST_Marker> Marker, FColor Color, bool bShowDistance)
{
	AKST_Marker* TmpMarker;
	FActorSpawnParameters SpawnParams;

	TmpMarker = GetWorld()->SpawnActor<AKST_Marker>(Marker, Location, FRotator::ZeroRotator, SpawnParams);

	if (IsValid(TmpMarker))
	{
		TmpMarker->bShowDistance = bShowDistance;
		TmpMarker->Color = Color;
		TmpMarker->SetColor();
		Add(TmpMarker);
	}
}

void UKST_MarkerManagerComponent::Add(AKST_Marker* Marker)
{
	if (!Markers.Contains(Marker))
	{
		Markers.Add(Marker);
	}
}

void UKST_MarkerManagerComponent::Remove(AKST_Marker* Marker)
{
	if (Markers.Contains(Marker))
	{
		Markers.Remove(Marker);
		Markers.Sort();
		Marker->Remove();
	}

}

void UKST_MarkerManagerComponent::RemoveActorRef(AActor* TargetActor)
{
	int i = 0;
	AKST_Marker* TargetMarker = nullptr;

	for  (i; i < Markers.Num(); i++)
	{
		if (Markers[i]->CurrentOwner == TargetActor)
		{
			TargetMarker=Markers[i];
			break; 
		}
	}

	if (TargetMarker != nullptr)
	{
		Remove(TargetMarker);
	}
}

void UKST_MarkerManagerComponent::HideAll()
{
	const int Count = Markers.Num();
	for (int i = 0; i < Count; i++)
	{
		Markers[i]->Hide();
	}
}

void UKST_MarkerManagerComponent::ShowAll()
{
	const int Count = Markers.Num();
	for (int i = 0; i < Count; i++)
	{
		Markers[i]->Show();
	}
}

void UKST_MarkerManagerComponent::ClearAll()
{
	const int Count = Markers.Num();
	for (int i = 0; i < Count; i++)
	{
		Markers[i]->Remove();
	}
	Markers.Sort();
}

TArray<AActor*> UKST_MarkerManagerComponent::GetAll()
{
	TArray<AActor*> AllMarkers;
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AKST_Marker::StaticClass(), AllMarkers);

	return AllMarkers;
}

void UKST_MarkerManagerComponent::CreateNavArrow()
{

	if (!IsValid(NavArrowClass))
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Nav Class OK"));

	AActor* TmpOwner = GetWorld()->GetFirstPlayerController();

	if (!IsValid(TmpOwner))
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Player OK"));

	NavWidgetComponent = TmpOwner->CreateDefaultSubobject<UWidgetComponent>(TEXT("NavigationWidget"));

	if (IsValid(NavWidgetComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("Nav Component OK"));

		NavArrow = CreateWidget<UKST_NavArrowWidget>(GetWorld(), NavArrowClass);

		if (NavArrow && NavWidgetComponent)
		{
			UE_LOG(LogTemp, Warning, TEXT("Nav Widget OK"));

			NavArrow->CurrentOwner = TmpOwner;
			NavWidgetComponent->SetWidget(NavArrow);
			NavWidgetComponent->SetWidgetSpace(EWidgetSpace::World);
			NavWidgetComponent->SetDrawSize(FVector2D(1024, 1024));
			NavWidgetComponent->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.25f));
			NavWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -80.0f));
			NavWidgetComponent->SetRelativeRotation(FRotator(180.0f, 90.0f, 0.0f));
			NavWidgetComponent->SetPivot(FVector2D(0.5f, 0.5f));
			bMarkerSet = true;
		}
	}
}

void UKST_MarkerManagerComponent::DestroyNavArrow()
{
	if (IsValid(NavWidgetComponent))
	{
		NavWidgetComponent->DestroyComponent();
	}

	bMarkerSet = false;
}

void UKST_MarkerManagerComponent::UpdateArrowRotation()
{
	if (bMarkerSet)
	{
		if (CurrentMarkerIndex < 0)
		{
			return;
		}

		//UE_LOG(LogTemp, Warning, TEXT("Marker Set!"));

		if (IsValid(Markers[CurrentMarkerIndex]))
		{
			FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(),
				Markers[CurrentMarkerIndex]->GetActorLocation());

			if (IsValid(NavWidgetComponent))
			{
				NavWidgetComponent->SetRelativeRotation(FRotator(180.0f, 90.0f,Rotation.Yaw));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Invalid Arrow Widget Set!"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Invalid Marker Set!"));
		}
	}
}

void UKST_MarkerManagerComponent::SwitchCurrentMarker()
{
	if (Markers.Num() == 0)
	{
		return;
	}

	if (CurrentMarkerIndex >= 0)
	{
		Markers[CurrentMarkerIndex]->bShowDistance = false;
	}

	CurrentMarkerIndex += 1;

	if (CurrentMarkerIndex >= Markers.Num())
	{
		CurrentMarkerIndex = -1;
	}
	else
	{
        Markers[CurrentMarkerIndex]->bShowDistance = true;
	}

	

}


// Called when the game starts
void UKST_MarkerManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...

}


// Called every frame
void UKST_MarkerManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateArrowRotation();
	// ...
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include <Runtime/NavigationSystem/Public/NavigationSystem.h>
#include "BluePrint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

AMyAIController::AMyAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> bt(TEXT("BehaviorTree'/Game/AI/BT_MyBT.BT_MyBT'"));

	if (bt.Succeeded())
	{
		_bt = bt.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBlackboardData> bd(TEXT("BlackboardData'/Game/AI/BB_MyBBData.BB_MyBBData'"));

	if (bd.Succeeded())
	{
		_bd = bd.Object;
	}
}

void AMyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//GetWorld()->GetTimerManager().SetTimer(_timerHandle, this, &AMyAIController::RandMove, 3.0f, true);

	if (UseBlackboard(_bd, Blackboard))
	{
		if (RunBehaviorTree(_bt))
		{
			UE_LOG(LogTemp, Warning, TEXT("Behavior Tree Succeeded"));
		}
	}
	
}

void AMyAIController::OnUnPossess()
{
	Super::OnUnPossess();
	
	//GetWorld()->GetTimerManager().ClearTimer((_timerHandle));
}

void AMyAIController::RandMove()
{
	auto currentPawn = GetPawn();

	if (!IsValid(currentPawn))
		return;

	UNavigationSystemV1* naviSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (naviSystem == nullptr)
		return;


	FNavLocation randLocation;

	if (naviSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, randLocation))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, randLocation);
	}
}

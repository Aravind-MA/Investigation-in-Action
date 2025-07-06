// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimalAIController.h"
#include "Creature_npc.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"


AAnimalAIController::AAnimalAIController(FObjectInitializer const& onjectIntiializer)
{
	PrimaryActorTick.bCanEverTick = true;

	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	check(BlackboardComponent);

	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	check(BehaviorTreeComponent);
}

void AAnimalAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (InPawn == nullptr) return;

	ACreature_npc* Npc = Cast<ACreature_npc>(InPawn);
	if (Npc)
	{
		if (Npc->GetBehaviorTree())
		{
			BlackboardComponent->InitializeBlackboard(*(Npc->GetBehaviorTree()->BlackboardAsset));
		}
	}
}

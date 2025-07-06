// Fill out your copyright notice in the Description page of Project Settings.


#include "Creature_npc.h"
#include "Components/SphereComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AnimalAIController.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h" 
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Particles/ParticleSystemComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Controller.h"
#include "TP_ThirdPersonCharacter.h"
#include "cooki_actor.h"

// Sets default values
ACreature_npc::ACreature_npc()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(GetRootComponent());

	

	AttackSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AttackSphere"));
	AttackSphere->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ACreature_npc::BeginPlay()
{
	Super::BeginPlay();

	

	AiAnimalController = Cast<AAnimalAIController>(GetController());

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ACreature_npc::AgroSphere);

	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ACreature_npc::AgroSphereEnd);


	AttackSphere->OnComponentBeginOverlap.AddDynamic(this, &ACreature_npc::EatSphere);

	//SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ACreature_npc::AgroSphereEnd);

	FVector WorldPatrolPoint = UKismetMathLibrary::TransformLocation(
		GetActorTransform(),
		PatrolPoint);
	DrawDebugSphere(
		GetWorld(),
		WorldPatrolPoint,
		25.f,
		12,
		FColor::Red,
		true);

	FVector WorldPatrolPoint2 = UKismetMathLibrary::TransformLocation(
		GetActorTransform(),
		PatrolPoint2);
	DrawDebugSphere(
		GetWorld(),
		WorldPatrolPoint2,
		25.f,
		12,
		FColor::Orange,
		true);


	if (AiAnimalController)
	{
		AiAnimalController->GetBlackboardComponent()->SetValueAsVector(
			TEXT("PatrolPoint"),
			WorldPatrolPoint);

		AiAnimalController->GetBlackboardComponent()->SetValueAsVector(
			TEXT("PatrolPoint2"),
			WorldPatrolPoint2);

		AiAnimalController->RunBehaviorTree(Tree);
	}
	
}

// Called every frame
void ACreature_npc::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	/*if (PlayerActor)
	{

		if (AiAnimalController->LineOfSightTo(PlayerActor))
		{
			SphereComponent->SetGenerateOverlapEvents(false);

			AiAnimalController->MoveToActor(PlayerActor, radius);
			AiAnimalController->SetFocus(PlayerActor);


		}
		else
		{
			AiAnimalController->ClearFocus(EAIFocusPriority::Gameplay);

			SphereComponent->SetGenerateOverlapEvents(true);
		}

	}*/
}

// Called to bind functionality to input
void ACreature_npc::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACreature_npc::AgroSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (!OtherActor) return; // Null check first

	// Assign PlayerActor before checking the tag
	PlayerActor = Cast<AActor>(OtherActor);

	if (PlayerActor && PlayerActor->ActorHasTag(TagSpeci))
	{
		UE_LOG(LogTemp, Warning, TEXT("Active overlap"));

		if (AiAnimalController)
		{
			AiAnimalController->GetBlackboardComponent()->SetValueAsObject(TEXT("Enemy"), PlayerActor);
			UE_LOG(LogTemp, Warning, TEXT("Active character123"));

			AiAnimalController->MoveToActor(PlayerActor, Radius);
			AiAnimalController->SetFocus(PlayerActor);
		}
		else
		{
			AiAnimalController->ClearFocus(EAIFocusPriority::Gameplay);
		}
	}
}

void ACreature_npc::AgroSphereEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor) return; // Null check first

	// Assign PlayerActor before checking the tag
	PlayerActor = Cast<AActor>(OtherActor);

	if (PlayerActor && PlayerActor->ActorHasTag(TagSpeci))
	{
		UE_LOG(LogTemp, Warning, TEXT("Active overlap"));

		if (AiAnimalController)
		{
			AiAnimalController->GetBlackboardComponent()->SetValueAsObject(TEXT("Enemy"), PlayerActor);
			UE_LOG(LogTemp, Warning, TEXT("Active character123"));

			AiAnimalController->MoveToActor(PlayerActor, Radius);
			AiAnimalController->SetFocus(PlayerActor);
		}
		else
		{
			AiAnimalController->ClearFocus(EAIFocusPriority::Gameplay);
		}
	}
}



		

void ACreature_npc::EatSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{


	cooki = Cast<Acooki_actor>(OtherActor);

	if (cooki)
	{
		//Radius = 200.f;
		AttackSphere->SetGenerateOverlapEvents(false);
		//SphereComponent->SetGenerateOverlapEvents(false);
		cooki->Destroy();
		UE_LOG(LogTemp, Warning, TEXT("Active cooki"));
		UE_LOG(LogTemp, Warning, TEXT("Active off collision"));
		OnDamaged();
	}

}

void ACreature_npc::Tagchase()
{
	if (PlayerActor && PlayerActor->ActorHasTag(TagSpeci))
	{
		UE_LOG(LogTemp, Warning, TEXT("Active overlap"));

		if (AiAnimalController)
		{
			AiAnimalController->GetBlackboardComponent()->SetValueAsObject(TEXT("Enemy"), PlayerActor);
			UE_LOG(LogTemp, Warning, TEXT("Active character123"));

			AiAnimalController->MoveToActor(PlayerActor, Radius);
			AiAnimalController->SetFocus(PlayerActor);
			

		}

	}

}





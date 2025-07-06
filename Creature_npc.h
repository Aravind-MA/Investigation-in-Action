// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Creature_npc.generated.h"

UCLASS()
class AI_ANIMAL_API ACreature_npc : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACreature_npc();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void AgroSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void AgroSphereEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void EatSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "MyCategory")
	void Tagchase();
	
	//void AgroSphereEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//void AttackAnim(FName Section, float PlayRate);
	// This event will be implemented in Blueprint
	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void OnDamaged();


private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Agro", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Agro", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* AttackSphere;

	/** Behavior tree for the AI Character */
	UPROPERTY(EditAnywhere, Category = "Behavior Tree", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* Tree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Agro", meta = (AllowPrivateAccess = "true"))
	class ACharacter* character;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Agro", meta = (AllowPrivateAccess = "true"))
	class APawn* PlayerPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Agro", meta = (AllowPrivateAccess = "true"))
	FName TagSpeci;

	class Acooki_actor* cooki;

	class AActor* PlayerActor;

	class AAnimalAIController* AiAnimalController;

	UPROPERTY(EditAnywhere, Category = "Behavior Tree", meta = (AllowPrivateAccess = "true", MakeEditWidget = "true"))
	FVector PatrolPoint;

	UPROPERTY(EditAnywhere, Category = "Behavior Tree", meta = (AllowPrivateAccess = "true", MakeEditWidget = "true"))
	FVector PatrolPoint2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Agro", meta = (AllowPrivateAccess = "true"))
	float Radius = 10.f;

public:
	FORCEINLINE UBehaviorTree* GetBehaviorTree() const { return Tree; }

};

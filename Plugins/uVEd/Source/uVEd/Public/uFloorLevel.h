// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "uFloorLevel.generated.h"



UCLASS()
class AuFloorLevel : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AuFloorLevel();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
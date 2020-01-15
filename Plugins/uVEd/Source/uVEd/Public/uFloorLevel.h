/*
	uVR Model open-source UE4 plugin
	author: B.Fanini (bruno.fanini__AT__gmail.com)
	https://github.com/phoenixbf/uVRmodel

===================================================*/

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
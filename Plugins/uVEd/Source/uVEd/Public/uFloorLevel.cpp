/*
	uVR Model open-source UE4 plugin
	author: B.Fanini (bruno.fanini__AT__gmail.com)
	https://github.com/phoenixbf/uVRmodel

===================================================*/

#include "uFloorLevel.h"


// Sets default values
AuFloorLevel::AuFloorLevel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AuFloorLevel::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AuFloorLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
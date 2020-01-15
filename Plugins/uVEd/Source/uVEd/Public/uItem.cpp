/*
	uVR Model open-source UE4 plugin
	author: B.Fanini (bruno.fanini__AT__gmail.com)
	https://github.com/phoenixbf/uVRmodel

===================================================*/

#include "uItem.h"


// Sets default values
AuItem::AuItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

/*
	FVector iCenter;
	this->GetActorBounds(false, iCenter, _exts);
	_rad = FMath::Max3(_exts.X, _exts.Y, _exts.Z);

	UE_LOG(LogTemp, Warning, TEXT("[uGM] ITEM radius: %f"), _rad);
*/
}

// Called when the game starts or when spawned
void AuItem::BeginPlay()
{
	Super::BeginPlay();

/*
	FVector iCenter;
	this->GetActorBounds(false, iCenter, _exts);
	_rad = FMath::Max3(_exts.X, _exts.Y, _exts.Z);
*/
}

// Called every frame
void AuItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AuItem::GetExtentsAndRadius(FVector& extents, float& radius) {
	FVector iCenter;
	this->GetActorBounds(true, iCenter, _exts);
	_rad = FMath::Max3(_exts.X, _exts.Y, _exts.Z);

	extents = _exts;
	radius  = _rad;
	//UE_LOG(LogTemp, Warning, TEXT("[uItem] ITEM radius: %f"), _rad);
}


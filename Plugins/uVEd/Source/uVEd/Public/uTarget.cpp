/*
	uVR Model open-source UE4 plugin
	author: B.Fanini (bruno.fanini__AT__gmail.com)
	https://github.com/phoenixbf/uVRmodel

===================================================*/

#include "uTarget.h"


// Sets default values
AuTarget::AuTarget(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//_volume.Init();
}

// Called when the game starts or when spawned
void AuTarget::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AuTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AuTarget::GetVolume(FVector& WorldCenter, FVector& WorldMin, FVector& WorldMax, float& iratio){
	//_volume.Init();

	FVector tLoc = this->GetActorLocation();
	WorldCenter = tLoc;

	// NOTE: target bounds seem to large
	//FVector tCenter, tBoxExtents;
	//this->GetActorBounds(false, tCenter, tBoxExtents);


	if (!_uItem) {
		UE_LOG(LogTemp, Warning, TEXT("[uTarget] This uTarget has NO uItem!!"));
		return;
		}

	// We have a valid item
	//FVector iCenter, iBoxExtents;
	//_uItem->GetActorBounds(true, iCenter, iBoxExtents);

	FVector iBoxExtents;
	float iRadius;
	_uItem->GetExtentsAndRadius(iBoxExtents, iRadius);

	//iRadius *= padding;

	FVector iLoc = _uItem->GetActorLocation();

	WorldMin.Set(
		FMath::Min(iLoc.X - iRadius, tLoc.X - iRadius),
		FMath::Min(iLoc.Y - iRadius, tLoc.Y - iRadius),
		FMath::Min(iLoc.Z - iRadius, tLoc.Z - iRadius)
	);

	WorldMax.Set(
		FMath::Max(iLoc.X + iRadius, tLoc.X + iRadius),
		FMath::Max(iLoc.Y + iRadius, tLoc.Y + iRadius),
		FMath::Max(iLoc.Z + iRadius, tLoc.Z + iRadius)
	);
/*
	WorldMin.Set(
		FMath::Min(iLoc.X - iBoxExtents.X, tLoc.X - iBoxExtents.X),
		FMath::Min(iLoc.Y - iBoxExtents.Y, tLoc.Y - iBoxExtents.Y),
		FMath::Min(iLoc.Z - iBoxExtents.Z, tLoc.Z - iBoxExtents.Z)
		);

	WorldMax.Set(
		FMath::Max(iLoc.X + iBoxExtents.X, tLoc.X + iBoxExtents.X),
		FMath::Max(iLoc.Y + iBoxExtents.Y, tLoc.Y + iBoxExtents.Y),
		FMath::Max(iLoc.Z + iBoxExtents.Z, tLoc.Z + iBoxExtents.Z)
		);
*/
	WorldCenter = (WorldMin + WorldMax) * 0.5f;

	// iRatio
	//float iRadius = FMath::Max3(iBoxExtents.X, iBoxExtents.Y, iBoxExtents.Z);
	float vSize = FMath::Max3(
		WorldMax.X - WorldMin.X,
		WorldMax.Y - WorldMin.Y,
		WorldMax.Z - WorldMin.Z
		);

	iratio = (iRadius / vSize);

	//UE_LOG(LogTemp, Warning, TEXT("[uTarget] iRatio: %f"), iratio);
}


/*
	uVR Model open-source UE4 plugin
	author: B.Fanini (bruno.fanini__AT__gmail.com)
	https://github.com/phoenixbf/uVRmodel

===================================================*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "EngineUtils.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

#include "uItem.h"
#include "uTarget.h"

#include "uGM.generated.h"


/**
 * 
 */
UCLASS()
class AuGM : public AGameModeBase
{
	GENERATED_BODY()

public:
	AuGM();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "uVR")
	void SetPlayAreaExtents(FVector vSize);

	UFUNCTION(BlueprintCallable, Category = "uVR")
	void GetPlayAreaExtents(FVector& extents){ extents = _playAreaExtents; }

	UFUNCTION(BlueprintCallable, Category = "uVR")
	void uFilterBySize(float f);

	UFUNCTION(BlueprintCallable, Category = "uVR")
	void uFilterByDistance(float f);

	UFUNCTION(BlueprintCallable, Category = "uVR")
	void uCompute(FVector& BaseVR, float& WorldScale, float padding=0.0f);

	UFUNCTION(BlueprintCallable, Category = "uVR")
	void GetSolvingStatus(uint8& numTotal, uint8& numSolved){
		numTotal  = _totItems;
		numSolved = _numSolved;
		}

	UFUNCTION(BlueprintCallable, Category = "uVR")
	void GetUnsolvedVolume(
		FVector& WorldCenter, 
		FVector& WorldMin, 
		FVector& WorldMax, 
		FVector& Extents
		);

	// Events
	UFUNCTION(BlueprintImplementableEvent, Category = "uVR")
	void OnAllItemsSolved();

private:
	uint8 _numSolved = 0;
	uint8 _totItems = 0;
	bool _bAllItemsSolved = false;

	FVector _playAreaExtents;
	float _playAreaMinRad;

	FVector _uOrigin;
	float _uScaleWorld;
	bool _bUcomputed = false;

	//FBox _unsolvedVolume;
	FVector _uvMin, _uvMax, _uvCenter;
	FVector _uvExtents;

	//float _uPadding = 1.0f;

	TArray< AuTarget* > _TargetList;
	
};

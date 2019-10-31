// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "uItem.h"
#include "uFloorLevel.h"

#include "uTarget.generated.h"

UCLASS()
class AuTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AuTarget();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "uVR")
	void SetSolved(bool b) {
		_bSolved = b;
		if (_uItem) _uItem->SetSolved(b);
		}

	UFUNCTION(BlueprintCallable, Category = "uVR")
	bool isSolved(){ return _bSolved; }

	UFUNCTION(BlueprintCallable, Category = "uVR")
	void SetItem(AuItem* item) { _uItem = item; }

	UFUNCTION(BlueprintCallable, Category = "uVR")
	AuItem* GetItem(){ return _uItem; }

	UFUNCTION(BlueprintCallable, Category = "uVR")
	void GetVolume(FVector& WorldCenter, FVector& WorldMin, FVector& WorldMax, float& iratio);

	UFUNCTION(BlueprintCallable, Category = "uVR")
	void SetFloorLevel(AuFloorLevel* floorlevel) { _uFloorLevel = floorlevel; }

	UFUNCTION(BlueprintCallable, Category = "uVR")
	AuFloorLevel* GetFloorLevel() { return _uFloorLevel;  }

	UFUNCTION(BlueprintCallable, Category = "uVR")
	void SetEnabled(bool b) { 
		_bEnabled = b;
		if (_uItem) _uItem->SetEnabled(b);
		}

	UFUNCTION(BlueprintCallable, Category = "uVR")
	bool isEnabled(){ return _bEnabled; }

	// Events
	UFUNCTION(BlueprintImplementableEvent, Category = "uVR")
	void OnDisabled();

	UFUNCTION(BlueprintImplementableEvent, Category = "uVR")
	void OnEnabled();

private:
	AuItem* _uItem = NULL;
	AuFloorLevel* _uFloorLevel = NULL;

	bool _bSolved  = false;
	bool _bEnabled = true;
};

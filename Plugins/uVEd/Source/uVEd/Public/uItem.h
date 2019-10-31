// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "uItem.generated.h"



UCLASS()
class AuItem : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AuItem();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "uVR")
	void SetSolved(bool b) { _bSolved = b; }

	UFUNCTION(BlueprintCallable, Category = "uVR")
	bool isSolved() const { return _bSolved; }

	UFUNCTION(BlueprintCallable, Category = "uVR")
	void SetEnabled(bool b) { _bEnabled = b; }

	UFUNCTION(BlueprintCallable, Category = "uVR")
	bool isEnabled() const { return _bEnabled; }

	UFUNCTION(BlueprintCallable, Category = "uVR")
	void GetExtentsAndRadius(FVector& extents, float& radius);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool _bSolved  = false;
	bool _bEnabled = true;

	FVector _exts;
	float _rad;
};

// Fill out your copyright notice in the Description page of Project Settings.

#include "uGM.h"

AuGM::AuGM(){

	_uScaleWorld = 1.0f;

	// Defaults to 1x1 meters and 170 cm height
	SetPlayAreaExtents(FVector(100.0f, 100.0f, 170.0f));

	//_unsolvedVolume.BuildAABB(_uOrigin, FVector(0.5f, 0.5f, 0.5f));
}

void AuGM::BeginPlay() {
	//GetWorld()->GetFirstPlayerController()->GetPawn();

	Super::BeginPlay();
}

void AuGM::SetPlayAreaExtents(FVector vSize) { 
	_playAreaExtents = vSize;
	//_playAreaMinRad = FMath::Min(_playAreaExtents.X, _playAreaExtents.Y);
	_playAreaMinRad = FMath::Min3(_playAreaExtents.X, _playAreaExtents.Y, _playAreaExtents.Z);
}


void AuGM::GetUnsolvedVolume(
	FVector& WorldCenter, 
	FVector& WorldMin, 
	FVector& WorldMax, 
	FVector& Extents
){
	WorldCenter = _uvCenter;
	WorldMin = _uvMin;
	WorldMax = _uvMax;
	Extents  = _uvExtents;
}


/*
	uCompute: core routine for uVR Model
=====================================================================*/
void AuGM::uCompute(FVector& BaseVR, float& WorldScale, float padding){
	
	_numSolved = 0;
	_totItems  = 0;

	//_unsolvedVolume.Init();
	FVector wGlobalMin(FLT_MAX, FLT_MAX, FLT_MAX), wGlobalMax(-FLT_MAX,-FLT_MAX,-FLT_MAX);
	bool bFirstFound = false;
	float wMinFloor = FLT_MAX;
	bool bFoundFloor = false;

	FVector C(0, 0, 0), wMin(0, 0, 0), wMax(0, 0, 0);
	float iRatio;
	bool bAccepted = true;

	// Loop all uTargets-uItems in our world
	for (TActorIterator<AuTarget> ActorItr(GetWorld()); ActorItr; ++ActorItr){
		AuTarget* T = *ActorItr;

		_totItems++;

		bAccepted = T->isEnabled();

		// Take into account only unsolved targets
		if (!T->isSolved() && bAccepted){
			
			//_unsolvedVolume = _unsolvedVolume.ExpandBy(T->GetActorLocation());
			//if (T->GetItem()) _unsolvedVolume = _unsolvedVolume.ExpandBy(T->GetItem()->GetActorLocation());

			T->GetVolume(C, wMin, wMax, iRatio);

			//UE_LOG(LogTemp, Warning, TEXT("[uGM] item uVOL: min(%f %f %f) --- max(%f %f %f)"), wMin.X, wMin.Y, wMin.Z, wMax.X, wMax.Y, wMax.Z);
			//UE_LOG(LogTemp, Warning, TEXT("[uGM] iRatio: %f"), iRatio);

			wGlobalMin.Set(
				FMath::Min(wGlobalMin.X, wMin.X),
				FMath::Min(wGlobalMin.Y, wMin.Y),
				FMath::Min(wGlobalMin.Z, wMin.Z)
				);

			wGlobalMax.Set(
				FMath::Max(wGlobalMax.X, wMax.X),
				FMath::Max(wGlobalMax.Y, wMax.Y),
				FMath::Max(wGlobalMax.Z, wMax.Z)
				);

			// Target has a floorlevel attached
			if (T->GetFloorLevel()) {
				//wGlobalMin.Z = FMath::Min(wGlobalMin.Z, T->GetFloorLevel()->GetActorLocation().Z);
				//wGlobalMin.Z = T->GetFloorLevel()->GetActorLocation().Z;
				wMinFloor = FMath::Min(wMinFloor, T->GetFloorLevel()->GetActorLocation().Z);
				bFoundFloor = true;
				//UE_LOG(LogTemp, Warning, TEXT("[uGM] Floor: %f"), wMinFloor);
				}

/*
			if (_bUcomputed){
				float r;
				FVector exts;

				T->GetItem()->GetExtentsAndRadius(exts, r);


				float f = (r / _uScaleWorld);
				UE_LOG(LogTemp, Warning, TEXT("[uGM] Item f: %f"), f);
				}
*/

			}

		// This is solved
		else {
			_numSolved++;
			}
		}

	// Loop completed, update globals

	if (_totItems == 0) return; // No uItems-uTargets at all

	if (_numSolved >= _totItems){ // Everything is solved
		_uScaleWorld = 1.0f;
		WorldScale = _uScaleWorld;
		_bAllItemsSolved = true;
		OnAllItemsSolved();
		return;
		}

	if (bFoundFloor) wGlobalMin.Z = FMath::Min(wGlobalMin.Z, wMinFloor);

	float di = FVector::Dist(wGlobalMax,wGlobalMin);
	FVector P = FVector(di*padding, di*padding, di*padding);

	_uvMin = (wGlobalMin - P);
	_uvMax = (wGlobalMax + P);

	UE_LOG(LogTemp, Warning, TEXT("[uGM] GLOBAL uVOL: min(%f %f %f) --- max(%f %f %f)"), _uvMin.X, _uvMin.Y, _uvMin.Z, _uvMax.X, _uvMax.Y, _uvMax.Z);

	_uvExtents = (_uvMax - _uvMin);
	_uvCenter  = (_uvMin + _uvMax) * 0.5f;

	//_playAreaMinRad = FMath::Min(_playAreaExtents.X, _playAreaExtents.Y);
	////_playAreaMinRad = FMath::Min3(_playAreaExtents.X, _playAreaExtents.Y, _playAreaExtents.Z);

	_uScaleWorld = FMath::Max3(_uvExtents.X, _uvExtents.Y, _uvExtents.Z) / _playAreaMinRad;

	// Return values
	WorldScale = _uScaleWorld;

	if (bFoundFloor) BaseVR.Set(_uvCenter.X, _uvCenter.Y, wMinFloor);
	else BaseVR.Set(_uvCenter.X, _uvCenter.Y, _uvMin.Z);

	_bUcomputed = true;

	//_unsolvedVolume = _unsolvedVolume.ExpandBy(_uPadding);
}

// uFiltering: before uCompute to filter out unsolved targets
//===========================================================
void AuGM::uFilterBySize(float f){
	if (_bAllItemsSolved) return;

	unsigned int numUnsolved = 0;
	float minRad = FLT_MAX, maxRad = 0.0f;

	float r;
	FVector exts;

	// Retrieve min/max
	for (TActorIterator<AuTarget> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		AuTarget* T = *ActorItr;

		if (!T->isSolved()){
			T->GetItem()->GetExtentsAndRadius(exts, r);

			if (r < minRad) minRad = r;
			if (r > maxRad) maxRad = r;
			numUnsolved++;
			}
		}

	if (f <= 0.0f || f >= 1.0f) return;

	float bias = FMath::Lerp(minRad, maxRad, f);

	UE_LOG(LogTemp, Warning, TEXT("[uGM] Filter (min: %f, max: %f) - Bias: %f"), minRad,maxRad,bias);

	// Apply filter
	for (TActorIterator<AuTarget> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		AuTarget* T = *ActorItr;

		if (!T->isSolved()) {
			T->GetItem()->GetExtentsAndRadius(exts, r);

			if ((r < bias) && (numUnsolved > 1)){
				T->SetEnabled(false);
				T->OnDisabled();
				}
			else {
				T->SetEnabled(true);
				T->OnEnabled();
				}
			}
		}
}

void AuGM::uFilterByDistance(float f) {
	if (_bAllItemsSolved) return;

	unsigned int numUnsolved = 0;
	float minDist = FLT_MAX, maxDist = 0.0f;

	float d;

	// Retrieve min/max
	for (TActorIterator<AuTarget> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		AuTarget* T = *ActorItr;

		if (!T->isSolved()) {
			d = T->GetDistanceTo(T->GetItem());

			if (d < minDist) minDist = d;
			if (d > maxDist) maxDist = d;
			numUnsolved++;
		}
	}

	if (f <= 0.0f || f >= 1.0f) return;

	float bias = FMath::Lerp(minDist, maxDist, f);

	UE_LOG(LogTemp, Warning, TEXT("[uGM] Filter (min: %f, max: %f) - Bias: %f"), minDist, maxDist, bias);

	// Apply filter
	for (TActorIterator<AuTarget> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		AuTarget* T = *ActorItr;

		if (!T->isSolved()) {
			d = T->GetDistanceTo(T->GetItem());

			if ((d > bias) && (numUnsolved > 1)) {
				T->SetEnabled(false);
				T->OnDisabled();
			}
			else {
				T->SetEnabled(true);
				T->OnEnabled();
			}
		}
	}

}

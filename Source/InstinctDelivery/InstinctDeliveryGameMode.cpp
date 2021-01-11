// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "InstinctDeliveryGameMode.h"
#include "InstinctDeliveryBall.h"
#include "Engine/World.h"

AInstinctDeliveryGameMode::AInstinctDeliveryGameMode()
{
	// set default pawn class to our ball
	DefaultPawnClass = AInstinctDeliveryBall::StaticClass();
	FVector location;
	FRotator rotation;
	//GetWorld()->SpawnActor<AActor>(cell_class_name, location, rotation);
}

// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "InstinctDeliveryGameMode.h"
#include "InstinctDeliveryBall.h"
#include "Engine/World.h"
#include "level_cell_interface.h"

AInstinctDeliveryGameMode::AInstinctDeliveryGameMode()
{
	// set default pawn class to our ball
	DefaultPawnClass = AInstinctDeliveryBall::StaticClass();
	
}

void AInstinctDeliveryGameMode::BeginPlay()
{
	FVector location(0,0,0);
	FRotator rotation(0,0,0);
	AActor* cell = GetWorld()->SpawnActor<AActor>(cell_class_name, location, rotation);
	if (cell->GetClass()->ImplementsInterface(Ulevel_cell_interface::StaticClass())) {
		UE_LOG(LogTemp, Warning, TEXT("SUCESS!"));
		int val = Ilevel_cell_interface::Execute_getValue(cell);
		UE_LOG(LogTemp, Warning, TEXT("Value is %d !"), val);
	}
	
}

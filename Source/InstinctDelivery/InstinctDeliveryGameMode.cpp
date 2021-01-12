// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "InstinctDeliveryGameMode.h"
#include "InstinctDeliveryBall.h"
#include "Engine/World.h"
#include "LevelCellInterface.h"

#define IMPLEMENTS_CELL_INTERFACE(actor_ptr) actor_ptr->GetClass()->ImplementsInterface(ULevelCellInterface::StaticClass())
#define CALL_CELL_INTERFACE_FUNC(actor_ptr,func) ILevelCellInterface::Execute_##func(actor_ptr)

AInstinctDeliveryGameMode::AInstinctDeliveryGameMode()
{
	// set default pawn class to our ball
	DefaultPawnClass = AInstinctDeliveryBall::StaticClass();
}


FVector AInstinctDeliveryGameMode::getCellSpawnLocationAtIndex(int32  x_index, int32  y_index)
{
	if (IMPLEMENTS_CELL_INTERFACE(m_cells[y_index][x_index])) {
		return  CALL_CELL_INTERFACE_FUNC(m_cells[y_index][x_index], getSpawnLocation);
	}
	return FVector();
}

void AInstinctDeliveryGameMode::ConstructCells(int32  cellCountX, int32  cellCountY)
{
	FVector location(0, 0, 0);
	FRotator rotation(0, 0, 0);
	FTransform transform;

	for (int32  y = 0; y < cellCountY; y++) {
		TArray<AActor * > row;
		for (int32  x = 0; x < cellCountX; x++) {
			AActor* cell = GetWorld()->SpawnActor<AActor>(cell_class_name, location, rotation);
			if (IMPLEMENTS_CELL_INTERFACE(cell)) {
				UE_LOG(LogTemp, Warning, TEXT("SUCESS!"));
				transform = CALL_CELL_INTERFACE_FUNC(cell,getXEdgeTransform);
				location = transform.GetLocation();
				UE_LOG(LogTemp, Warning, TEXT("Value is x:%f, y:%f , z: %f !"), transform.GetLocation().X, transform.GetLocation().Y, transform.GetLocation().Z);
			}
			row.Add(cell);
		}
		m_cells.Add(row);
		if (IMPLEMENTS_CELL_INTERFACE(m_cells[y][0])) {
			transform = CALL_CELL_INTERFACE_FUNC(m_cells[y][0], getNextCellToRightTransform);
			location = transform.GetLocation();
		}
	}
}

bool AInstinctDeliveryGameMode::IsVaildCell(int32 x_index, int32 y_index)
{
	if ((int)y_index >= 0 && m_cells.Num() > (int)y_index)
		if ((int)x_index >= 0 && m_cells[y_index].Num() > (int)x_index)
			return true;
	return false;
}

void AInstinctDeliveryGameMode::getMedianCellIndex(int32 & x_index, int32 & y_index)
{
	y_index = (int32)(m_cells.Num() / 2);
	x_index = (int32)(m_cells[y_index].Num() / 2);
}

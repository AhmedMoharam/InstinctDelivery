// Fill out your copyright notice in the Description page of Project Settings.


#include "GridManagerComponent.h"
#include "Engine/World.h"
#include "LevelCellInterface.h"

#define IMPLEMENTS_CELL_INTERFACE(actor_ptr) actor_ptr->GetClass()->ImplementsInterface(ULevelCellInterface::StaticClass())
#define CALL_CELL_INTERFACE_FUNC(actor_ptr,func) ILevelCellInterface::Execute_##func(actor_ptr)


// Sets default values for this component's properties
UGridManagerComponent::UGridManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGridManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGridManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


FVector UGridManagerComponent::getCellSpawnLocationAtIndex(int32  x_index, int32  y_index)
{
	if (IMPLEMENTS_CELL_INTERFACE(m_cells[y_index][x_index].CellActor)) {
		return  CALL_CELL_INTERFACE_FUNC(m_cells[y_index][x_index].CellActor, getSpawnLocation);
	}
	return FVector();
}

void UGridManagerComponent::ConstructCells(int32  cellCountX, int32  cellCountY)
{
	FVector location(0, 0, 0);
	FRotator rotation(0, 0, 0);
	FTransform transform;

	for (int32 y = 0; y < cellCountY; y++) {
		TArray<Cell> row;
		for (int32 x = 0; x < cellCountX; x++) {
			Cell cell;
			AActor* cellActor = GetWorld()->SpawnActor<AActor>(cell_class_name, location, rotation);
			if (IMPLEMENTS_CELL_INTERFACE(cellActor)) {
				transform = CALL_CELL_INTERFACE_FUNC(cellActor, getXEdgeTransform);
				location = transform.GetLocation();
			}
			cell.CellActor = cellActor;
			row.Add(cell);
		}
		m_cells.Add(row);
		if (IMPLEMENTS_CELL_INTERFACE(m_cells[y][0].CellActor)) {
			transform = CALL_CELL_INTERFACE_FUNC(m_cells[y][0].CellActor, getNextCellToRightTransform);
			location = transform.GetLocation();
		}
	}
}

bool UGridManagerComponent::IsVaildCell(int32 x_index, int32 y_index)
{
	if ((int)y_index >= 0 && m_cells.Num() > (int)y_index)
		if ((int)x_index >= 0 && m_cells[y_index].Num() > (int)x_index)
			return true;
	return false;
}

void UGridManagerComponent::getMedianCellIndex(int32 & x_index, int32 & y_index)
{
	y_index = (int32)(m_cells.Num() / 2);
	x_index = (int32)(m_cells[y_index].Num() / 2);
}

void UGridManagerComponent::getCellAtIndex(int XIndex, int YIndex, AActor* & cell)
{
	cell = m_cells[YIndex][XIndex].CellActor;
	 
}

void UGridManagerComponent::getAvailableCells(TArray<AActor*>& cells)
{
	for (auto & cell_row : m_cells) {
		for (auto & cell : cell_row) {
			if (!cell.busy)
				cells.Add(cell.CellActor);
		}
	}
}

void UGridManagerComponent::markCellBusy(int XIndex, int YIndex)
{
	m_cells[YIndex][XIndex].busy = true;
}

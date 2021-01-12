// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InstinctDeliveryGameMode.generated.h"

UCLASS(minimalapi)
class AInstinctDeliveryGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AInstinctDeliveryGameMode();
	UFUNCTION(BlueprintCallable, Category = "Cell_Helper")
	FVector getCellSpawnLocationAtIndex(int32  x_index, int32  y_index);

	UFUNCTION(BlueprintCallable, Category = "Cell_Helper")
	void ConstructCells(int32  cellCountX, int32  cellCountY);

	UFUNCTION(BlueprintCallable, Category = "Cell_Helper")
	bool IsVaildCell(int32  x_index, int32  y_index);

	UFUNCTION(BlueprintCallable, Category = "Cell_Helper")
	void getMedianCellIndex(int32 & x_index, int32 & y_index);

	

public:
	UPROPERTY(EditDefaultsOnly, Category = "Cell_Helper")
	TSubclassOf<AActor> cell_class_name;
	
		
private:
	int32  m_CellCountX;
	int32  m_CellCountY;
	TArray < TArray<AActor*> > m_cells;
};




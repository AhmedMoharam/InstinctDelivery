// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GridManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INSTINCTDELIVERY_API UGridManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGridManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable, Category = "GridManagerComponent")
		FVector getCellSpawnLocationAtIndex(int32  x_index, int32  y_index);

	UFUNCTION(BlueprintCallable, Category = "GridManagerComponent")
		void ConstructCells(int32  cellCountX, int32  cellCountY);

	UFUNCTION(BlueprintCallable, Category = "GridManagerComponent")
		bool IsVaildCell(int32  x_index, int32  y_index);

	UFUNCTION(BlueprintCallable, Category = "GridManagerComponent")
		void getMedianCellIndex(int32 & x_index, int32 & y_index);



public:
	UPROPERTY(EditDefaultsOnly, Category = "Cell_Helper")
		TSubclassOf<AActor> cell_class_name;


private:
	int32  m_CellCountX;
	int32  m_CellCountY;
	TArray < TArray<AActor*> > m_cells;
		
};

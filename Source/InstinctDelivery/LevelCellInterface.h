// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LevelCellInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class ULevelCellInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INSTINCTDELIVERY_API ILevelCellInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	FTransform getXEdgeTransform();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	FTransform getYEdgeTransform();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	FTransform getXMinusEdgeTransform();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	FTransform getYMinusEdgeTransform();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	FTransform getNextCellToRightTransform();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	FTransform getNextCellToLeftTransform();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	FVector getSpawnLocation();
};

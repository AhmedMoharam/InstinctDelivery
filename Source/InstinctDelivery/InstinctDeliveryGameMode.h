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
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Parameters")
	TSubclassOf<AActor> cell_class_name;
		
};




// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "InstinctDeliveryGameMode.h"
#include "InstinctDeliveryBall.h"

AInstinctDeliveryGameMode::AInstinctDeliveryGameMode()
{
	// set default pawn class to our ball
	DefaultPawnClass = AInstinctDeliveryBall::StaticClass();
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JsonConfigurator.generated.h"

struct Grid {
	int XCount;
	int YCount;
};

struct Turret {
	TArray <int> Position;
	float ProjectileSpeed;
	float FireRate;
	float Range;
	bool UseSmartProjectile;
};

struct PlayerSettings {
	TArray <int> StartPosition;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INSTINCTDELIVERY_API UJsonConfigurator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UJsonConfigurator();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "JsonConfigurator")
	void getGridSetup(int & XCount, int & YCount);

	UFUNCTION(BlueprintCallable, Category = "JsonConfigurator")
	void getTurretsCount(int & TurretsCount);

	UFUNCTION(BlueprintCallable, Category = "JsonConfigurator")
	void getTurretSetupByIndex(int TurretIndex, int & XIndex, int & YIndex, int & YawAngle, float & ProjectileSpeed, float & FireRate, float & Range, bool & UseSmartProjectile);

	UFUNCTION(BlueprintCallable, Category = "JsonConfigurator")
	void getPlayerStartPosition(int & XIndex, int & YIndex, int & YawAngle);

private:
	Grid m_grid;
	TArray <Turret> m_turrets;
	PlayerSettings m_playerSettings;

		
};

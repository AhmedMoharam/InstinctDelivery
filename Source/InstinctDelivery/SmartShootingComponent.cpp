// Fill out your copyright notice in the Description page of Project Settings.


#include "SmartShootingComponent.h"

// Sets default values for this component's properties
USmartShootingComponent::USmartShootingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USmartShootingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USmartShootingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USmartShootingComponent::predictTargetLocation(const AActor* ShootingTarget, float projectileVelocity, FVector MuzzleLocation, FVector & TragetPredictedLocation)
{
	FVector Vtarget = ShootingTarget->GetVelocity();
	FVector R = ShootingTarget->GetActorLocation() - MuzzleLocation;
	double a = (Vtarget.X * Vtarget.X) + (Vtarget.Y * Vtarget.Y) + (Vtarget.Z * Vtarget.Z) - (projectileVelocity * projectileVelocity);
	double b = (2 * R.X * Vtarget.X)
		+ (2 * R.Y * Vtarget.Y)
		+ (2 * R.Z * Vtarget.Z);
	double c = (R.X * R.X) + (R.Y * R.Y) + (R.Z * R.Z);
	double t = SolveQuadraticEqn(a, b, c);
	if (t != -1){
		TragetPredictedLocation = ShootingTarget->GetActorLocation() + t * Vtarget;
	}
	else {
		TragetPredictedLocation = ShootingTarget->GetActorLocation();
	}
}

double USmartShootingComponent::SolveQuadraticEqn(double a, double b, double c)
{
	double discriminant, x1,x2;
	discriminant = b * b - 4 * a*c;
	if (discriminant > 0) {
		x1 = (-b + sqrt(discriminant)) / (2 * a);
		x2 = (-b - sqrt(discriminant)) / (2 * a);
		UE_LOG(LogTemp, Warning, TEXT("Roots are real and different. %f,%f"), x1,x2);
		if (x1 < 0 && x2 < 0)
			return -1.0f;
		else if (x1 < 0)
			return x2;
		else if (x2 < 0)
			return x1;
		else
			return x1 < x2 ? x1 : x2;
	}
	else if (discriminant == 0) {
		x1 = (-b + sqrt(discriminant)) / (2 * a);
		UE_LOG(LogTemp, Warning, TEXT("Roots are real and same. %f"), x1);
		return x1;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Roots are complex and different."));
		return -1.0f;
	}
}


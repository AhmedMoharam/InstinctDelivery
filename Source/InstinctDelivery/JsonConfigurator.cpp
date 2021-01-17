// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonConfigurator.h"
#include "Json/json.hpp"
#include "Misc/Paths.h"
#include <fstream>

using json = nlohmann::json;

// Sets default values for this component's properties
UJsonConfigurator::UJsonConfigurator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
	// ...
	FString ConfigFile = FPaths::ProjectContentDir() + "/Configuration/Config.json";
	if (FPaths::FileExists(ConfigFile)) {
		std::ifstream fs(*ConfigFile);
		json jsonFileData;
		fs >> jsonFileData;

		UE_LOG(LogTemp, Warning, TEXT("[UJsonConfigurator] Parsing Config.json ..."));
		// parsing grid elements
		m_grid.XCount = jsonFileData["Grid"]["XCount"];
		m_grid.YCount = jsonFileData["Grid"]["YCount"];

		// parsing turrets settings
		for (json::iterator it = jsonFileData["Turrets"].begin(); it != jsonFileData["Turrets"].end(); it++) {
			m_turrets.Emplace(Turret());
			json turret_data = it.value();
			std::vector<int> position = turret_data["Position"].get<std::vector<int> >();
			for (int i = 0; i < position.size(); i++) {
				m_turrets.Last().Position.Add(position[i]);
			}
			m_turrets.Last().ProjectileSpeed = turret_data["ProjectileSpeed"].get<float>();
			m_turrets.Last().FireRate = turret_data["FireRate"].get<float>();
			m_turrets.Last().Range = turret_data["Range"].get<float>();
			m_turrets.Last().UseSmartProjectile = turret_data["UseSmartProjectile"].get<bool>();
			m_turrets.Last().ProjectileDamage = turret_data["ProjectileDamage"].get<float>();
		}

		// parsing player settings
		m_playerSettings.StartPosition.SetNum(3);
		std::vector<int> position = jsonFileData["PlayerSettings"]["StartPosition"].get<std::vector<int> >();
		for (int i = 0; i < position.size(); i++) {
			m_playerSettings.StartPosition[i] = position[i];
		}
		m_playerSettings.MaxHealth = jsonFileData["PlayerSettings"]["MaxHealth"].get<int>();

		// coins settings
		m_coinsSettings.CoinsMaxCount = jsonFileData["CoinsSettings"]["CoinsMaxCount"].get<int>();
		m_coinsSettings.CoinsGenerationThreshold = jsonFileData["CoinsSettings"]["CoinsGenerationThreshold"].get<int>();
		m_coinsSettings.ScorePerCoin = jsonFileData["CoinsSettings"]["ScorePerCoin"].get<float>();
		UE_LOG(LogTemp, Warning, TEXT("[UJsonConfigurator] Parsing successful!"));
	}

}


// Called when the game starts
void UJsonConfigurator::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UJsonConfigurator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UJsonConfigurator::getGridSetup(int & XCount, int & YCount)
{
	XCount = m_grid.XCount;
	YCount = m_grid.YCount;
}

void UJsonConfigurator::getTurretsCount(int & TurretsCount)
{
	TurretsCount = m_turrets.Num();
}

void UJsonConfigurator::getTurretSetupByIndex(int TurretIndex, int & XIndex, int & YIndex, int & YawAngle, float & ProjectileSpeed, float & FireRate, float & Range, bool & UseSmartProjectile, float & ProjectileDamage)
{
	XIndex = m_turrets[TurretIndex].Position[0];
	YIndex = m_turrets[TurretIndex].Position[1];
	YawAngle = m_turrets[TurretIndex].Position[2];
	ProjectileSpeed = m_turrets[TurretIndex].ProjectileSpeed;
	FireRate = m_turrets[TurretIndex].FireRate;
	Range = m_turrets[TurretIndex].Range;
	UseSmartProjectile = m_turrets[TurretIndex].UseSmartProjectile;
	ProjectileDamage = m_turrets[TurretIndex].ProjectileDamage;
}

void UJsonConfigurator::getPlayerStartPosition(int & XIndex, int & YIndex, int & YawAngle)
{
	XIndex = m_playerSettings.StartPosition[0];
	YIndex = m_playerSettings.StartPosition[1];
	YawAngle = m_playerSettings.StartPosition[2];
}

void UJsonConfigurator::getPlayerMaxHealth(float & PlayerMaxHealth)
{
	PlayerMaxHealth = m_playerSettings.MaxHealth;
}

void UJsonConfigurator::getCoinsSettings(int & CoinsMaxCount, int & CoinsGenerationThreshold, float & ScorePerCoin)
{
	CoinsMaxCount = m_coinsSettings.CoinsMaxCount;
	CoinsGenerationThreshold = m_coinsSettings.CoinsGenerationThreshold;
	ScorePerCoin = m_coinsSettings.ScorePerCoin;
}


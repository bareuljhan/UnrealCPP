// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "MyStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FHpChangedRatio, float)

USTRUCT()
struct FCharacterStat : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BluePrintReadWrite)
	int32 level;
	UPROPERTY(EditAnywhere, BluePrintReadWrite)
	int32 maxHp;	
	UPROPERTY(EditAnywhere, BluePrintReadWrite)
	int32 maxMp;
	UPROPERTY(EditAnywhere, BluePrintReadWrite)
	int32 attack;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4_PROJECT_API UMyStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyStatComponent();

	virtual void InitializeComponent() override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetStatByLevel(int32 level);
	
	void Damaged(int32 amount);

	void SetCurHp(int32 hp);

	int32 GetHp() { return _curHp; }
	int32 GetAtk() { return _atk; }

	float HpRatio();

	FHpChangedRatio _onHpChangedRatio;

private:
	int32 _level;
	int32 _maxHp;
	int32 _curHp;
	int32 _atk;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SRC/Game/Character/BaseCharacter.h"
#include "FoundationCharacter.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType, Blueprintable)
struct FProduceResourceInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FString productName;

	UPROPERTY(EditAnywhere)
	int32 productNb;

	UPROPERTY(EditAnywhere)
	int32 productDepositeLimit;
};

USTRUCT(BlueprintType, Blueprintable)
struct FIntrinsicEffectInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	FString effectName;

	/** 标识效果类型
	* 0代表TickEffect
	* 1代表PassiveEffect
	* 2代表OneTimeEffect
	*/
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	uint8 effectType;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TArray<FString> preconditionEffectNames;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TArray<int32> effectValues;

	UPROPERTY()
	TArray<int32> modifyEffectValues;

	UPROPERTY()
	ABaseCharacter* pHost;
};

UCLASS()
class COLLISIONWAR_API AFoundationCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaSeconds) override;

	virtual void EvaluateShortTask() override;
	
	virtual void ImplementSkill_Int(int32 campFlag) override;

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyAddLevelPS(int32 level);

	FLogicVec2D m_fireTargetDir;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TArray<FIntrinsicEffectInfo> m_intrinsicEffectInfo;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TArray<FLogicVec2D> m_coverRangePts;

	UPROPERTY()
	FFoundationCharacterOccupyInfo m_occupyInfo;

	/** 合成类型
	* 0 - 培育场
	* 1 - 熔炉
	* 2 - 研究所
	* 3 - 药水制作
	* 4 - 静思处
	* 5 - 手工制作场
	* 6 - 祭坛
	* 7 - 卡牌复制
	* 8 - 攻击设施
	* 9 - 事件触发器
	*/
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_tradeType;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_inputNb;
	
	int32 m_level;

	bool m_isActivate = false;
};

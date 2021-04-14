// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../../Base/Battle/BattleLevelPlayerController.h"
#include "FoundationCharacter.h"




void AFoundationCharacter::Tick(float DeltaSeconds)
{

}

void AFoundationCharacter::EvaluateShortTask()
{
	if (!m_pNormalShortTask || !m_pBaseEquipment || !m_pBaseAnimInstance || m_pBaseAnimInstance->m_motionStateString != "PMS_NULL") return;
	ETaskType taskType = ETaskType::TT_NULL;
	int32 skillNb = -1;
	ABaseCharacter* pCharacter = NULL;
	for (int32 i = 0; i < m_pBaseEquipment->m_pSkills.Num(); i++)
	{
		if (!m_pBaseEquipment->m_pSkills[i]->m_canImplementFlag) continue;
		bool hasTarget = false;
		for (int32 j = 0; j < m_pBaseEquipment->m_pSkills[i]->m_pOverlapCharacters.Num(); j++)
		{
			hasTarget = true;
			break;
		}
		if (!hasTarget) continue;
		skillNb = i;
		break;
	}
	if (skillNb == -1)
	{
		m_pNormalShortTask->m_taskType = ETaskType::TT_NULL;
		m_pNormalShortTask->m_pTarget = NULL;
		m_pNormalShortTask->m_evaluateActionName = "NULL";
		m_pNormalShortTask->m_evaSkillNb = -1;
		//taskType = ETaskType::TT_NULL;
		//pCharacter = NULL;
		return;
	}

	int32 minHp = 0;
	float minDis = 0;
	int32 minHpCharacterNb = 0;
	int32 minDisCharacterNb = 0;
	TArray<int32> scores;
	for (int32 i = 0; i < m_pBaseEquipment->m_pSkills[skillNb]->m_pOverlapCharacters.Num(); i++)
	{
		int32 score = 0;
		scores.Add(score);
		FVector targetDir = m_pBaseEquipment->m_pSkills[skillNb]->m_pOverlapCharacters[i]->GetActorLocation() - GetActorLocation();
		float dis = FMath::Sqrt(targetDir.Size());
		int32 hp = m_pBaseEquipment->m_pSkills[skillNb]->m_pOverlapCharacters[i]->m_Hp;
		if (i == 0 || dis <= minDis)
		{
			minDis = dis;
			minDisCharacterNb = i;
		}
		if (i == 0 || hp <= minHp)
		{
			minHp = hp;
			minHpCharacterNb = i;
		}
	}

	if (scores.Num() > 0)
	{
		scores[minDisCharacterNb] += 2;
		scores[minHpCharacterNb] += 1;
		int32 maxScore = 0;
		int32 maxScoreNb = 0;
		for (int32 i = 0; i < scores.Num(); i++)
		{
			if (scores[i] >= maxScore)
			{
				maxScore = scores[i];
				maxScoreNb = i;
			}
		}
		taskType = ETaskType::TT_ImplementSkill;
		pCharacter = m_pBaseEquipment->m_pSkills[skillNb]->m_pOverlapCharacters[maxScoreNb];
	}
	else
	{
		taskType = ETaskType::TT_NULL;
		pCharacter = NULL;
	}

	//根据evaluate结果赋值
	if (taskType == ETaskType::TT_NULL)
	{
		m_pNormalShortTask->m_evaluateActionName = "StopContinuousTask";
		m_pNormalShortTask->m_evaSkillNb = -1;
		m_pNormalShortTask->m_pTarget = NULL;
		m_pNormalShortTask->m_taskType = ETaskType::TT_NULL;
	}
	else if (taskType == ETaskType::TT_ImplementSkill)
	{
		m_pNormalShortTask->m_evaluateActionName = "ImplementSkill";
		m_pNormalShortTask->m_evaSkillNb = skillNb;
		m_pNormalShortTask->m_pTarget = pCharacter;
		m_pNormalShortTask->m_taskType = ETaskType::TT_ImplementSkill;
		FVector targetDirOffset = pCharacter->GetActorLocation() - GetActorLocation();
		FVector2D targetDir(targetDirOffset.X, targetDirOffset.Y);
		float yaw = UCollisionWarBpFunctionLibrary::GetYawFromLogicVec(targetDir);
		m_pNormalLongTask->m_evaYaw = yaw;
	}
}

void AFoundationCharacter::ImplementSkill_Int(int32 campFlag)
{
	//更新技能号curSkillNb
	m_curSkillNb = m_skillOperationNb;
	UBaseSkill* pSkill = m_pBaseEquipment->m_pSkills[m_curSkillNb];
	pSkill->m_campFlag = campFlag;
	m_pBaseAnimInstance->m_motionStateString = pSkill->m_skillMotionTypeString;
	//m_pBaseAnimInstance->NotifyImplementSkill(pSkill->m_skillAnimName);
	//更新技能信息
	pSkill->m_canImplementFlag = false;

	//实施所有信息后，恢复接口
	m_actionName = "NULL";
}

void AFoundationCharacter::NotifyAddLevelPS_Implementation(int32 level)
{

}


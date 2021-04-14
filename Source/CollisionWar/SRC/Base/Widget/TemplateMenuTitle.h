// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TextBlock.h"
#include "TemplateMenuTitle.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTemplateMenuTitle : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void DeleteDemoText();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyInitial();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
		void NotifyShowDemoText();

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pTitle;
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FString m_chineseTitle;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FString m_englishTitle;
};

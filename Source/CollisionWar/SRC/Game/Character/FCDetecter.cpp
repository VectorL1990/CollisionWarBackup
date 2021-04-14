// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "FCDetecter.h"


// Sets default values
AFCDetecter::AFCDetecter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFCDetecter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFCDetecter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFCDetecter::OnBeginOverlap(class UPrimitiveComponent* OverlapedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this || !OtherActor || !OtherComp) return;
	if (OtherComp->ComponentHasTag(FName("BasePhysActor")) ||
		OtherComp->ComponentHasTag(FName("DumpActor")) ||
		OtherComp->ComponentHasTag(FName("FoundationCharacter")))
		m_pOverlapActors.Add(OtherActor);
}

void AFCDetecter::OnEndOverlap(class UPrimitiveComponent* OverlapedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor || !OtherComp) return;
	if (m_pOverlapActors.Contains(OtherActor)) m_pOverlapActors.Remove(OtherActor);
}


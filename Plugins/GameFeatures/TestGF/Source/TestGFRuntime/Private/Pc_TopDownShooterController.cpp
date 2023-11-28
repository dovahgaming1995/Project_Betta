// Copyright 2021-2022 Mickael Daniel. All Rights Reserved.


#include "Pc_TopDownShooterController.h"

#include "GameFramework/Character.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"


APc_TopDownShooterController::APc_TopDownShooterController()
{
}

void APc_TopDownShooterController::spawnCharacter(TSubclassOf<ACharacter> characterClass)
{
	
	// Set Local Var
	TArray<AActor*> FoundActors;
	const TSubclassOf<APlayerStart>ActorClass ;
	// Set Default Spawn Location
	const FVector defaultLocationFVector(0.0f,0.0f,240.0f);
	const FRotator defaultRotation(0.0f,-180.0f,0.0f);
	const FVector defaultScale(1.0f,1.0f,1.0f);
	FTransform spawnLocationTransform (defaultRotation,defaultLocationFVector,defaultScale);
	// Get All Actor Of Class APlayerStart
	UGameplayStatics::GetAllActorsOfClass(this,ActorClass,FoundActors);
	// If The APlayerStart Is Not Empty
	if (FoundActors.Num() > 0)
	{
		// Set Spawn Location Based On FoundActors
		const int32 randomIndex=FMath::RandRange(0,FoundActors.Num()-1);
		const AActor* selectedActor = FoundActors[randomIndex];
		spawnLocationTransform.SetLocation(selectedActor->GetActorLocation());
	}
	
	//Spawn Actor
	FActorSpawnParameters spawnParam;
	spawnParam.Owner=this;
	spawnParam.Instigator=GetInstigator();
	ACharacter* character=GetWorld()->SpawnActor<ACharacter>(characterClass,spawnLocationTransform,spawnParam);
	APawn* pawnCharacter = Cast<APawn>(character);
	if(character)
	{
		Possess(pawnCharacter);
	}


}

	bool APc_TopDownShooterController::ChangeCurveFloat(UTimelineComponent* timeLine,const UCurveFloat* curveTable,const FName trackName,float newTime)
	{
	// Check if the timeline and the curve are valid
	if(timeLine && curveTable)
	{
		// Cast away the const-ness of CurveTable as SetFloatCurve expects a non-const pointer
		timeLine->SetFloatCurve(const_cast<UCurveFloat*>(curveTable), trackName);
        
		// Set the new time for the timeline
		timeLine->SetNewTime(newTime);
		
		// If the timeline is not playing, start playing it from the start
		if(!timeLine->IsPlaying())
		{
			timeLine->PlayFromStart();
		}
		return true; // Return true if everything goes well
	}
	return false; // Return false if the timeline or curve is invalid
	}


void APc_TopDownShooterController::createTimeLine(UCurveFloat* CurveFloat)
{
	/*
	// Time Line Init
	MyTimeline = NewObject<UTimelineComponent>(this, FName("MyTimeline"));
	
	if (!MyTimeline)// Handle the error appropriately
	{
		return;
	}
	MyTimeline->CreationMethod = EComponentCreationMethod::UserConstructionScript;
	this->BlueprintCreatedComponents.Add(MyTimeline);

	// Create float Track instance
	FOnTimelineFloat TimelineFunction;
	TimelineFunction.BindUFunction(this, FName("callable"));
	MyTimeline->AddInterpFloat(CurveFloat, TimelineFunction);

	// Create Event Track instance
	FOnTimelineEvent TimelineEventFunction;
	TimelineEventFunction.BindUFunction(this, FName("OnTimelineEvent"));
	MyTimeline->AddEvent(2.0f, TimelineEventFunction);
	
	//Create Finished Func Instance 
	FOnTimelineEventStatic FTimeLine;
	FTimeLine.BindUFunction(this,FName("timeLineFinished"));
	MyTimeline->SetTimelineFinishedFunc(FTimeLine);
	
	// Start The Time Line 
	MyTimeline->RegisterComponent();
	MyTimeline->PlayFromStart();
	*/

}

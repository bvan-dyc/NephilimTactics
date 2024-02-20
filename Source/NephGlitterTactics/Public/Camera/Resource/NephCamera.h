#pragma once

#include "CoreMinimal.h"

struct NEPHGLITTERTACTICS_API FNephCamera
{
public:
	
	TWeakObjectPtr<class ANephCameraActor> CameraActor;
	TWeakObjectPtr<class AActor> CameraTarget;
};

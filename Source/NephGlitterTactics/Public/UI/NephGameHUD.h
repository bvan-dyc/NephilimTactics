// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CommonActivatableWidget.h"
#include "NephGameHUD.generated.h"

UCLASS(Abstract, BlueprintType, Blueprintable)
class NEPHGLITTERTACTICS_API UNephGameHUD : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:

	UNephGameHUD() {}

	static UNephGameHUD* Get(const UObject* context);
};

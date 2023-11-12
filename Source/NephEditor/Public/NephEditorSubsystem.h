#pragma once

#include "EditorSubsystem.h"

#include "NephEditorSubsystem.generated.h"

UCLASS()
class UNephEditorSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:

	UNephEditorSubsystem();

	virtual void Initialize(class FSubsystemCollectionBase& Collection) override;
};

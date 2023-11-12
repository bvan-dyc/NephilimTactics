#pragma once

#include "InteractiveTool.h"
#include "BaseBehaviors/SingleClickBehavior.h"

#include "SPBaseTool.generated.h"

UCLASS()
class UNephBaseToolMouseTarget
	: public UObject
	, public IClickBehaviorTarget
	, public IClickDragBehaviorTarget
	, public IHoverBehaviorTarget
{
	GENERATED_BODY()

public:
	
	// IClickBehavior
	virtual FInputRayHit IsHitByClick(const FInputDeviceRay& clickPos) override;
	virtual void OnClicked(const FInputDeviceRay& clickPos) override;
	// ~IClickBehavior

	// IClickDragBehavior
	virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& pressPos) override;
	virtual void OnClickPress(const FInputDeviceRay& pressPos) override;
	virtual void OnClickDrag(const FInputDeviceRay& dragPos) override;
	virtual void OnClickRelease(const FInputDeviceRay& releasePos) override;
	virtual void OnTerminateDragSequence() override;
	// ~IClickDragBehavior
	
	// IHoverBehavior
	virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& pressPos) override;
	virtual void OnBeginHover(const FInputDeviceRay& devicePos) override;
	virtual bool OnUpdateHover(const FInputDeviceRay& devicePos) override;
	virtual void OnEndHover() override;
	// ~IHoverBehavior
	
protected:

	class UNephBaseTool* GetTool() const;
};

UCLASS()
class UNephBaseToolKeyTarget : public UObject, public IModifierToggleBehaviorTarget
{
	GENERATED_BODY()

protected:

	TMap<int, FKey> IDToKey;

public:

	void AddKey(const FKey& key);
	
	// IModifierToggleBehaviorTarget
	virtual void OnUpdateModifierState(int modifierID, bool bIsOn) override;
	// ~IModifierToggleBehaviorTarget

protected:
	
	class UNephBaseTool* GetTool() const;
};

UCLASS()
class NEPHEDITOR_API UNephBaseTool : public UInteractiveTool
{
	GENERATED_BODY()

private:
	
	UPROPERTY()
	UNephBaseToolMouseTarget* MouseTarget = nullptr;
	
	UPROPERTY()
	UNephBaseToolKeyTarget* KeyTarget = nullptr;

public:
	
	UNephBaseTool();

	// UInteractiveTool
	virtual void Setup() override;
	// UInteractiveTool end
	
	void AddKeyToCapture(const FKey& key);

	virtual void HandleMouseMove(const FInputDeviceRay& devicePos) {}
	virtual void HandleClick(const FInputDeviceRay& clickPos) {}
	virtual void HandleDragStart(const FInputDeviceRay& pressPos) {}
	virtual void HandleDragEnd(const FInputDeviceRay& releasePos) {}
	virtual void HandleDrag(const FInputDeviceRay& dragPos) {}
	virtual void HandleKey(const FKey& key, bool bPressed) {}
	
protected:
	
	bool bWantsMouseCapture = true;
};
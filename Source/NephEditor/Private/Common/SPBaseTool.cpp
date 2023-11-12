#include "SPBaseTool.h"
#include "BaseBehaviors/MouseHoverBehavior.h"
#include "BaseBehaviors/SingleClickOrDragBehavior.h"
#include "BaseBehaviors/SingleKeyCaptureBehavior.h"

UNephBaseTool* UNephBaseToolMouseTarget::GetTool() const
{
	return Cast<UNephBaseTool>(GetOuter());
}

FInputRayHit UNephBaseToolMouseTarget::IsHitByClick(const FInputDeviceRay& ClickPos)
{
	return FInputRayHit(0.0f);
}

void UNephBaseToolMouseTarget::OnClicked(const FInputDeviceRay& clickPos)
{
	if (UNephBaseTool* tool = GetTool())
	{
		tool->HandleClick(clickPos);
	}
}

FInputRayHit UNephBaseToolMouseTarget::CanBeginClickDragSequence(const FInputDeviceRay& pressPos)
{
	return FInputRayHit(0.0f);
}

void UNephBaseToolMouseTarget::OnClickPress(const FInputDeviceRay& pressPos)
{
	if (UNephBaseTool* tool = GetTool())
	{
		tool->HandleDragStart(pressPos);
	}
}

void UNephBaseToolMouseTarget::OnClickDrag(const FInputDeviceRay& dragPos)
{
	if (UNephBaseTool* tool = GetTool())
	{
		tool->HandleDrag(dragPos);
	}
}

void UNephBaseToolMouseTarget::OnClickRelease(const FInputDeviceRay& releasePos)
{
	if (UNephBaseTool* tool = GetTool())
	{
		tool->HandleDragEnd(releasePos);
	}
}

void UNephBaseToolMouseTarget::OnTerminateDragSequence()
{
}

FInputRayHit UNephBaseToolMouseTarget::BeginHoverSequenceHitTest(const FInputDeviceRay& pressPos)
{
	return FInputRayHit(0.0f);
}

void UNephBaseToolMouseTarget::OnBeginHover(const FInputDeviceRay& devicePos)
{
}

bool UNephBaseToolMouseTarget::OnUpdateHover(const FInputDeviceRay& devicePos)
{
	if (UNephBaseTool* tool = GetTool())
	{
		tool->HandleMouseMove(devicePos);
	}
	return true;
}

void UNephBaseToolMouseTarget::OnEndHover()
{
}

UNephBaseTool* UNephBaseToolKeyTarget::GetTool() const
{
	return Cast<UNephBaseTool>(GetOuter());
}

void UNephBaseToolKeyTarget::AddKey(const FKey& key)
{
	IDToKey.Add(static_cast<int>(GetTypeHash(key)), key);
}

void UNephBaseToolKeyTarget::OnUpdateModifierState(int modifierID, bool bIsOn)
{
	UNephBaseTool* tool = GetTool();
	const FKey* key = IDToKey.Find(modifierID);
	if (key && tool)
	{
		tool->HandleKey(*key, bIsOn);
	}
}

UNephBaseTool::UNephBaseTool() {}

void UNephBaseTool::Setup()
{
	UInteractiveTool::Setup();

	MouseTarget = NewObject<UNephBaseToolMouseTarget>(this);
	KeyTarget = NewObject<UNephBaseToolKeyTarget>(this);

	USingleClickOrDragInputBehavior* mouseBehavior = NewObject<USingleClickOrDragInputBehavior>();
	mouseBehavior->Initialize(MouseTarget, MouseTarget);
	mouseBehavior->SetUseLeftMouseButton();
	mouseBehavior->ModifierCheckFunc = [&](const FInputDeviceState&) {
		return bWantsMouseCapture;
	};
	AddInputBehavior(mouseBehavior);

	UMouseHoverBehavior* hoverBehavior = NewObject<UMouseHoverBehavior>();
	hoverBehavior->Initialize(MouseTarget);
	AddInputBehavior(hoverBehavior);
}

void UNephBaseTool::AddKeyToCapture(const FKey& key)
{
	if (!KeyTarget) { return; }
	KeyTarget->AddKey(key);
	
	USingleKeyCaptureBehavior* keyBehavior = NewObject<USingleKeyCaptureBehavior>();
	keyBehavior->Initialize(KeyTarget, static_cast<int>(GetTypeHash(key)), key);
	AddInputBehavior(keyBehavior);
}

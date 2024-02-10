#include "UI\Widget\Dialogue\NephCutsceneSpeakerWidget.h"

#include "Components/Image.h"

void UNephCutsceneSpeakerWidget::SetImage(UTexture2D* image) const
{
	if (SpeakerImage)
	{
		SpeakerImage->SetBrushFromTexture(image);
	}
}

void UNephCutsceneSpeakerWidget::HideSpeaker()
{
	SetVisibility(ESlateVisibility::Hidden);
}

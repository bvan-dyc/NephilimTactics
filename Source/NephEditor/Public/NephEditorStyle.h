#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"

class  FNephEditorStyle
{
public:

	static void Initialize();
	static void Shutdown();

	static TSharedPtr<ISlateStyle> Get() { return StyleSet; }
	static const FName& GetStyleSetName();

	static const FSlateBrush* GetBrush(FName PropertyName, const ANSICHAR* Specifier = nullptr)
	{
		return StyleSet->GetBrush(PropertyName, Specifier);
	}
	
	static FString InContentRoot();
	static FString InContent(const FString& RelativePath, const ANSICHAR* Extension);

private:

	static TSharedPtr<FSlateStyleSet> StyleSet;
};

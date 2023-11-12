#pragma once

#include "NativeGameplayTags.h"

namespace NephGameplayTags
{
	NEPHGLITTERTACTICS_API	FGameplayTag FindTagByString(const FString& TagString, bool bMatchPartialString = false);

	// Declare all of the custom native tags that NephTactics will use
};

#pragma once

struct FNephNarrativeSetup
{
	static void Setup(
		class FArcUniverse& Universe,
		struct FArcScheduleBuilder& InitScheduleBuilder,
		struct FArcScheduleBuilder& TickScheduleBuilder
	);
};

#pragma once

struct FNephBoardSetup
{
	static void Setup(
		class FArcUniverse& Universe,
		struct FArcScheduleBuilder& InitScheduleBuilder,
		struct FArcScheduleBuilder& TickScheduleBuilder
	);
	
	static void SetupForEditor(
		class FArcUniverse& Universe,
		struct FArcScheduleBuilder& InitScheduleBuilder,
		struct FArcScheduleBuilder& TickScheduleBuilder
	);
};

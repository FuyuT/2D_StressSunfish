#pragma once

//イベント
enum Event
{
	Event_None,
	Event_Summer,
	Event_Winter,
	Event_Turtle,
	Event_ShoalSardine,
	Event_Garbage,

	Event_Count,
};

//チュートリアル
enum TutorialStep
{
	Task_Movement = 2,
	Task_Action = 3,
	Task_Complete = 6,
	Task_End = 7,
};

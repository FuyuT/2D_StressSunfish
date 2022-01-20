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
	Task_Movement,
	Task_Action,
	Task_Complete,
	Task_End,
};

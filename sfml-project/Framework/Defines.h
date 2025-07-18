#pragma once

#define DEF_DEV
#define SCALE 30.f

enum class SortingLayers
{
	Background,
	Foreground,
	Default,
	UI,
};

enum class Origins
{
	TL, TC, TR,	// 0 1 2
	ML, MC, MR,	// 3 4 5
	BL, BC, BR, // 6 7 8
	Custom
};

enum class SceneIds
{
	None = -1,
	Start,
	ChooseStage,
	Dev1,
	Dev2,
	Test,
	Stage,
	Editor,
	Count,
};

enum class Sides
{
	Left,
	Right,
	None,
};
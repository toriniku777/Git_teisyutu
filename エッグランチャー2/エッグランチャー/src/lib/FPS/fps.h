#pragma once

class Fps
{
public:

	//•Ï”ŠÖ˜A‰Šú‰»
	static void InitFps();

	//FPS•\¦ŠÖ”
	static bool IsNextFrame();

	static void StepFps();

	static void PrintFps(void);
};


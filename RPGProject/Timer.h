﻿#pragma once

#include <SDL.h>
#include <stdio.h>

#include <string>
#include <sstream>

#ifndef TIMER_H_
#define TIMER_H_

class Timer
{
public:
	Timer();
	void start();
	void stop();
	void pause();
	void unpause();
	Uint32 getTicks();
	bool isStarted();
	bool isPaused();
private:
	Uint32 mStartTicks;
	Uint32 mPausedTicks;
	bool mPaused;
	bool mStarted;
};

#endif // !TIMER_H_

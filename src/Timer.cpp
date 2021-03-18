#include "Timer.hpp"

Timer::Timer()
{
	stop();
}

void Timer::start()
{
	started = true;
	paused = false;

	start_ticks = SDL_GetTicks();
	paused_ticks = 0;
}

void Timer::stop()
{
	started = false;
	paused = false;

	started = 0;
	paused_ticks = 0;
}

void Timer::pause()
{
	if(started && !paused)
	{
		paused = true;

		paused_ticks = SDL_GetTicks() - start_ticks;
		start_ticks = 0;
	}
}

void Timer::unpause()
{
	if(started && paused)
	{
		paused = false;

		start_ticks = SDL_GetTicks() - paused_ticks;
		paused_ticks = 0;
	}
}

int Timer::get_ticks()
{
	int time = 0;

	if(started)
	{
		if(paused)
			time = paused_ticks;

		else
			time = SDL_GetTicks() - start_ticks;
	}

	return time;
}

bool Timer::is_started()
{
	return started;
}

bool Timer::is_paused()
{
	return paused && started;
}
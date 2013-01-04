#include "Timer.h"

namespace Advanced2D {
	Timer::Timer() {
		timer_start = timeGetTime();
		reset();
	}

	Timer::~Timer() {
	}

	DWORD Timer::getTimer() {
		return (DWORD) (timeGetTime());
	}

	DWORD Timer::getStartTimeMillis() {
		return (DWORD) (timeGetTime() - timer_start);
	}

	void Timer::sleep(int ms) {
		DWORD start = getTimer();
		while (start + ms > getTimer());
	}

	void Timer::reset() {
		stopwatch_start = getTimer();
	}

	bool Timer::stopwatch(int ms) {
		if (timeGetTime() > stopwatch_start + ms) {
			stopwatch_start = getTimer();
			return true;
		} else {
			return false;
		}
	}
}

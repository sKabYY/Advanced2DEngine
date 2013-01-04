#pragma once

#include <time.h>
#include <windows.h>

namespace Advanced2D {
	class Timer {
		public:
			Timer(void);
			~Timer(void);
			DWORD getTimer();
			DWORD getStartTimeMillis();
			void sleep(int ms);
			void reset();
			bool stopwatch(int ms);
		private:
			DWORD timer_start;
			DWORD stopwatch_start;
	};
}

#ifndef __TIMER_H__
#define __TIMER_H__
#include <stdio.h>

#ifdef __linux
#include <sys/time.h>
#endif
#ifdef _WIN32
#include <windows.h>
#endif

//c++
#ifdef __cplusplus
class Timer {
	private:
#ifdef __linux
	struct timeval t0, t1;
#endif
#ifdef _WIN32
	LARGE_INTEGER t0, t1, f;
#endif
	
	public:
	Timer()
	{
		reset();
	}
	void disp(const char *str)
	{
		long dt;
		dt = getus();
		printf("%s: %.3lfms\n", str, dt / 1000.0);
	}
	void disp()
	{
		disp("deta time");
	}

#ifdef __linux
	void reset()
	{
		gettimeofday(&t0, 0);
	}
	long getus()
	{
		gettimeofday(&t1, 0);
		return ((t1.tv_sec - t0.tv_sec) * 1000000.0 + t1.tv_usec - t0.tv_usec);
	}
#endif

#ifdef _WIN32
	void reset()
	{
		QueryPerformanceCounter(&t0);
		QueryPerformanceFrequency(&f);
	}

	long getus()
	{
		QueryPerformanceCounter(&t1);
		return ((t1.QuadPart - t0.QuadPart) * 1000000.0 / (double)f.QuadPart); 
	}
#endif
};
//c only
#else
#ifdef __linux
typedef struct timeval Timer;
void timerReset(Timer *t)
{
	gettimeofday(t, 0);
}
void timerDisp(const char *str, const Timer *tStart)
{
	Timer t1;
	gettimeofday(&t1, 0);
	printf("%s: %.3lfms\n", str, (t1.tv_sec - tStart->tv_sec) * 1000.0 \
								+ (t1.tv_usec - tStart->tv_usec) / 1000.0);
}
#endif
#ifdef _WIN32
typedef LARGE_INTEGER Timer;
void timerReset(Timer *t)
{
	QueryPerformanceCounter(t);
}
void timerDisp(const char *str, const Timer *tStart)
{
	Timer t1, f;
	QueryPerformanceCounter(&t1);
	QueryPerformanceFrequency(&f);
	printf("%s: %.3lfms\n", str, (t1.QuadPart - tStart->QuadPart) * 1000.0 / (double)f.QuadPart);
}
#endif
#endif

#endif

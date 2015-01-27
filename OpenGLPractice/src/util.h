#ifndef UTIL_H
#define UTIL_H
#include <SDL2/SDL.h>

class FrameCounter {
public:
	FrameCounter();
	void showFramerate(Uint32 interval);
	FrameCounter& operator++() = delete;
	FrameCounter operator++(int);
private:
	Uint32 m_prev_frame_count;
	Uint32 m_curr_frame_count;
};
#endif // UTIL_H
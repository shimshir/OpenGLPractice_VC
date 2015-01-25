#include "util.h"
#include <iostream>

FrameCounter::FrameCounter()
{
	m_prev_frame_count = 0;
	m_curr_frame_count = 0;
}
void FrameCounter::showFramerate(Uint32 interval)
{
	std::cout << "Framerate: " << 1000 * (m_curr_frame_count - m_prev_frame_count) / (float)interval << std::endl;
	m_prev_frame_count = m_curr_frame_count;
}
FrameCounter FrameCounter::operator++(int)
{
	++m_curr_frame_count;
	return *this;
}
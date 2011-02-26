// Provide progress bars to console applications.  See complete documentation
// in Shared/Progress/Progress.h.

// Shared library headers
#include "Progress.h"

// Standard library headers
#ifdef __MSVC
#define NOMINMAX
#endif
#include <algorithm>
#include <cassert>
#include <iostream>

namespace Progress {

#if 0
////////////////////////////////////////////////////////////

Progresser::Progresser()
	: m_count(0), m_state(CREATED), m_majorSize(10), m_minorSize(1)
{}

Progresser::Progresser(int majorSize, int minorSize)
	: m_count(0), m_state(CREATED)
{
	// Need at least two minor divisions (with at least one tick apiece) per
	// major, or they'll butt together in the display.
	m_majorSize = std::max<int>(2, std::max<int>(minorSize, majorSize));

	// At least one per minor, and not more than 20 minors per major.
	m_minorSize = std::max<int>(1, std::max<int>(minorSize, m_majorSize / 20));
}

// If we've not already started, do so, and display the initial marker.
void Progresser::start() {
	if (stopped()) {
		m_count = 0;
		m_state = STARTED;
		major();
	}
}

// Up the count and display any necessary indicators
void Progresser::next() {
	if (stopped())
		start();

	m_count++;

	if (count() % m_majorSize == 0)
		major();
	else if (count() % m_minorSize == 0)
		minor();
}

// Display a minor indicator, in this case, a dot
void Progresser::minor() {
	std::cout << '.';
}

// Progresser::Set(x)
// Progresser::Add(x)
//
// Call these if you've done some batch processing or ignored a chunk of work
// and want to indicate it was done.  The code will count its way up to where
// you want the bar to be.
//
// Method returns false if the value set is less than the current count.  If
// the count was changed it returns true.
//
// Lots of room for performance improvement here.  We can take shortcuts with
// output generation since we know the interval size and number of items
// skipped by this call, and since the Major and Minor displays are virtual.

bool Progresser::set(const int x) {
	if (x < count())
		return false;
	while (count() < x)
		next();
	return true;
}

bool Progresser::add(const int x) {
	return set(count() + x);
}

// If we've not already stopped, display the final marker and stop.
void Progresser::stop() {
	if (!stopped()) {
		m_state = STOPPED;
		std::cout << std::endl;
	}
}

// We want to reuse this progresser.  Stop, and reset the count.
void Progresser::reset() {
	stop();
	m_count = 0;
}

////////////////////////////////////////////////////////////

ProgressBar::ProgressBar(int total)
	: Progresser()
{
	// TODO: Lots of room for improvement.  Use Brezhenham's algorithm.
	m_total = std::max<int>(1, total);

	if (m_total < 20) {
		m_majorSize = m_total;
		m_minorSize = 1;
	}
	else {
		m_majorSize = std::max<int>(2, m_total / 10);  // 10 per bar
		m_minorSize = std::max<int>(1, m_total / 50);  // 5 per major
	}
}

void ProgressBar::major() {
	std::cout << 100 * (m_count /*+ m_minorSize / 2*/) / m_total << "%";
}

void ProgressBar::start() {
	if (stopped()) {
		m_state = STARTED;
		major();
	}
}

void ProgressBar::stop() {
	if (m_count == 0)
		std::cout << "(no work)" << std::endl;
	else if (!stopped()) {
		m_state = STOPPED;
		std::cout << std::endl;
	}
}

#endif

} // namespace

// end of file

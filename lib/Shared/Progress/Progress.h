// Shared/Progress/Progress.h
// Copyright (c) 2007-2009
//
// Provide progress bars to console applications.

#ifndef PROGRESS_H__
#define PROGRESS_H__

#include <iostream>
#include <string>

namespace Progress {

// ==========================================================================
//
// class Counter
// class ProgressBar
// 
// Counter is an indeterminate progress bar, which displays a marker at every 
// <interval> number of ticks.  ProgressBar is has a known completion total
// and displays markers every 10%.
//
// Terminology:
//
// Division markers show progress.  There are major division markers at fixed
// intervals, and minor markers which show progress between majors.
//
//		0%....10%... (...) ....100%
//		^     ^   ^            ^ 
//		|     |   |            |
//		|     |  Minor()       |
//		|     |                |
//		+-----+----- Major() --+
//
// Typical Usage:
//
// Say you're scanning entries in a large directory or archive and want to 
// provide feedback to the user every few thousand files.  The following will
// create a progress bar with dots every 5000 and a total every 25000 files.
// The precise total is displayed at the end.  Numbers in the thousands and
// millions are shortened and an S.I. multiplier appeneded.  To end the 
// progress bar, call Stop() or let it fall out of scope.
//
//		printf("Counting things: ");
//		Progress::Counter progress(25000);
//		while (something_not_done) {
//			// do something
//			progress.Next();
//		}
//		progress.Stop();
//
// Output:
//
//		Counting things: 0....25k....50k....75k...90131 Done
//
// Say you're performing a costly operation on a large number of items, like
// copying files, and you want to provide the user with feedback on progress.
// The following code will create a progress bar with dots every 1% and a total
// every 10%.  To end the progress bar, call Stop() or let it fall out of scope.
//
//		printf("Progress: ");
//		int things = 200;
//		Progress::ProgressBar progress(things);
//		for (i = 0; i < things; ++i) {
//			// do something
//			progress.Next();
//		}
//		progress.Stop();
//
// Output:
//
//		Progress: 0%....10%.... /* ... */ ....90%....100%
//
// For more advanced control of the progressers, callers can use Set() and 
// Add() to control exactly how much progress has occured.  Callers can change 
// the number of minor indicators by providing a second constructor parameter.

#if 0
class Progresser {
protected:
	int m_count;
	float m_minorSize;  // number of ticks per minor marker
	float m_majorSize;  // number of ticks per major marker

	enum State { CREATED, STARTED, STOPPED } m_state;
	enum LastDisplayed { FIRST, MINOR, MAJOR, LAST } m_lastDisplayed;

	bool stopped() const  { return m_state == STOPPED; }
	int count() const     { return m_count; }
	// int majorSize() const { return m_majorSize; }
	// int minorSize() const { return m_minorSize; }

	virtual void minor();
	virtual void major() = 0;

public:
	Progresser();
	Progresser(const int majorSize, const int minorSize = 1);
	virtual ~Progresser() {}

	virtual void start();
	virtual void next();
	virtual bool add(const int ticks);
	virtual bool set(const int ticks);
	virtual void stop();
	virtual void reset();

private:
	// Disallow copy construction and assignment (for now)
	Progresser( const Progresser& other ) {}
	Progresser& operator=( const Progresser& other ) {}
};
#endif

// ==========================================================================

#if 0
class Bar : public Progresser { 
private:
	int m_total;
	virtual inline int total() { return m_total; }
	virtual void major();
public:
	Bar(int total);
	~Bar() { stop(); }
	virtual void start();
	virtual void stop();
};
#endif

} // namespace

#endif

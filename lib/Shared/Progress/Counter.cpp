#include "Counter.h"

#include <cassert>
#include <string>
#include <iostream>

namespace Progress {

	const std::string Counter::s_minorMarker( "." );
	const int Counter::s_minorMarksBetweenMajorMarks = 4;

	Counter* Counter::Create( std::ostream& out,
							  const int ticksPerMinorMark )
	{
		if ( ticksPerMinorMark < 1 )
			return NULL;
		return new Counter( out, ticksPerMinorMark );
	}

	Counter::Counter( std::ostream& out, const int ticksPerMinorMarker ) :
		m_outputStream( out ),
		m_ticksPerMinorMarker( ticksPerMinorMarker ),
		m_ticks( 0 ),
		m_ticksSinceLastMarker( 0 ),
		m_minorsSinceLastMajor( 0 ),
		m_state( STOPPED )
	{}

	void Counter::minor() {
		if ( stopped() )
			return;
		++m_minorsSinceLastMajor;
		m_outputStream << s_minorMarker;
	}

	// Display a major indicator, in this case the current count
	void Counter::major() {
		if ( stopped() )
			return;
		m_minorsSinceLastMajor = 0;
		m_outputStream << count();
	}

	void Counter::mark() {
		if ( stopped() )
			return;
		assert( m_minorsSinceLastMajor <= s_minorMarksBetweenMajorMarks );
		m_minorsSinceLastMajor == s_minorMarksBetweenMajorMarks ? major() : minor();
		m_ticksSinceLastMarker = 0;
	}

	// Assemble the count completion message and summary
	void Counter::done() {
		if ( stopped() )
			return;
		m_outputStream << " done (" << count() << ")" << std::endl;
	}

	void Counter::start() {
		if ( !stopped() )
			return;
		m_state = STARTED;
		m_ticks = 0;
		major();
	}

	void Counter::next() {
		if ( stopped() )
			start();
		++m_ticks;
		if ( ++m_ticksSinceLastMarker >= m_ticksPerMinorMarker )
			mark();
	}

	void Counter::add( const int ticks ) {
		assert( ticks >= 0 );
		for ( int i = 0; i < ticks; ++i )
			next();
	}

	void Counter::set( const int ticks ) {
		assert( ticks >= 0 );

		if ( ticks > count() )
			add( ticks - count() );
	}

	void Counter::stop() {
		if ( stopped() )
			return;
		done();
		m_state = STOPPED;
	}

	void Counter::reset() {
		stop();
		start();
	}

}

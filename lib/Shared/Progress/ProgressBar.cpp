#include "ProgressBar.h"

#include <cassert>
#include <string>
#include <iostream>

namespace Progress {
	const std::string ProgressBar::s_minorMarker = ".";
	const int ProgressBar::s_minorMarkWidth = 2;
	
	ProgressBar::ProgressBar( std::ostream& output ) :
		m_outputStream( output ),
		m_position( 0.0 ),
		m_lastDisplayedPosition( -minorMarkWidth() ),
		m_state( STOPPED )
	{}
	
	void ProgressBar::start() {
		if ( !stopped() )
			return;
		updateDisplay();
		m_state = STARTED;
	}

	void ProgressBar::setPositionWithinBounds( const float value ) {
		const float hiBoundedValue = std::min<float>( value, maximum() );
		const float boundedValue = std::max<float>( 0, hiBoundedValue );
		m_position = boundedValue;
	}

	void ProgressBar::checkForCompletion() {
		if ( position() >= maximum() )
			stop();
	}

	void ProgressBar::add( const float value ) {
		set( position() + value );
	}

	void ProgressBar::set( const float value ) {
		if ( stopped() )
			return;
		setPositionWithinBounds( value );
		updateDisplay();
		checkForCompletion();
	}

	bool ProgressBar::isValueNear( const float value1, const float value2 ) {
		const float tolerance = 0.0001;
		return ( value1 + tolerance >= value2 &&
				 value1 - tolerance <= value2 );
	}
				
	bool ProgressBar::nearMajorMark( const float value ) {
		for ( float i = 0.0; i <= maximum(); i += 20.0 )
			if ( isValueNear( value, i ) )
				return true;
		return false;
	}

	void ProgressBar::updateDisplay() {
		for ( float nextPosition = m_lastDisplayedPosition + minorMarkWidth();
			 nextPosition <= position();
			 nextPosition += minorMarkWidth() )
		{
			if ( nearMajorMark( nextPosition ) )
				m_outputStream << nextPosition << '%';  // TODO: fix formatting
			else
				m_outputStream << s_minorMarker;
		}

		m_lastDisplayedPosition = position();
	}

	void ProgressBar::abort() {
		if ( stopped() )
			return;
		// TODO: Format position to four significant digits
		m_outputStream << " abort (" << position() << ")" << std::endl;
		stop();
	}
	
	void ProgressBar::stop() {
		m_state = STOPPED;
		m_outputStream << std::endl;
	}
}

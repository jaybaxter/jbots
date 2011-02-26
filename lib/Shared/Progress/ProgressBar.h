#ifndef PROGRESS_PROGRESSBAR_H__
#define PROGRESS_PROGRESSBAR_H__

#include <iostream>

namespace Progress {
	
	class ProgressBar {
	public:
		ProgressBar( std::ostream& out );
		~ProgressBar() { stop(); }
		
		// accessors
		float position() const { return m_position; }
		
		// manipulators
		void start();
		void next();
		void add( const float progress );
		void set( const float progress );
		void reset();
		void abort();
		
	private:
		// Disallow copy construction and assignment
		ProgressBar( const ProgressBar& );
		ProgressBar& operator=( const ProgressBar& );

		// Defining properties
		static const std::string s_minorMarker;
		static const int s_minorMarkWidth;
		static const float maximum() { return 100.0; }
		static const float minorMarkWidth() { return s_minorMarkWidth; }
		static const float majorMarkWidth() { return 10 * s_minorMarkWidth; }

		// accessors
		bool stopped() const { return m_state == STOPPED; }

		// actions
		void mark();
		void minor();
		void major();
		void stop();

		// internal helpers
		void setPositionWithinBounds( const float value );
		void checkForCompletion();
		bool isValueNear( const float value1, const float value2 );
		bool nearMajorMark( const float value );
		void updateDisplay();

		std::ostream& m_outputStream;
		float m_position;
		float m_lastDisplayedPosition;
		enum State { STARTED, STOPPED } m_state;		
	};
}

#endif

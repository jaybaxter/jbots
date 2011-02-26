#ifndef PROGRESS_COUNTER_H__
#define PROGRESS_COUNTER_H__

#include <iostream>

namespace Progress {

	class Counter {
	public:
		static Counter* Create( std::ostream& out,
							    const int countBetweenMajorMarks );
		~Counter() { stop(); }

		// accessors
		int count() const { return m_ticks; }

		// manipulators
		void start();
		void next();
		void add( const int ticks );
		void set( const int ticks );
		void reset();
		void stop();

	private:
		// Construction only via factory method
		Counter( std::ostream& out, const int ticksPerMinorMark );

		// Disallow copy construction and assignment
		Counter( const Counter& );
		Counter& operator=( const Counter& );
		
		// accessors
		bool stopped() const { return m_state == STOPPED; }

		// actions
		void mark();
		void minor();
		void major();
		void done();

		static const std::string s_minorMarker;
		static const int s_minorMarksBetweenMajorMarks;

		std::ostream& m_outputStream;
		const int m_ticksPerMinorMarker;
		int m_ticks;
		int m_ticksSinceLastMarker;
		int m_minorsSinceLastMajor;

		enum State { STARTED, STOPPED } m_state;
	};

}

#endif

#include "../../Shared/Progress/Counter.h"

#include "../../Contrib/UnitTest++/UnitTest++.h"
#include <iostream>

//////////////////////////////

bool CounterRunner( const int countTo,
				    const int countBy,
				    const std::string& expected )
{
	std::ostringstream out;
	Progress::Counter* c = Progress::Counter::Create( out, countBy );
	assert( c != NULL );
	if ( c == NULL )
		return false;

	c->start();
	for ( int i = 0; i < countTo; ++i )
		c->next();
	c->stop();
	delete c;
	return out.str() == expected;
}

//////////////////////////////

class SimpleCounter {
protected:
	std::ostringstream output;
	Progress::Counter* counter;

	SimpleCounter() :
	output(),
	counter( Progress::Counter::Create( output, 1 ) )
	{
		assert( counter != NULL );
	}

	virtual ~SimpleCounter() {
		delete counter;
	}

private:
	// Disallowed
	SimpleCounter( const SimpleCounter& );
	SimpleCounter& operator=( const SimpleCounter& );
};

//////////////////////////////

TEST( Counter_To_STDOUT ) {
	Progress::Counter* c = Progress::Counter::Create( std::cout, 50 );
	CHECK( c != NULL );
	delete c;
}

TEST( Counter_To_STDERR ) {
	Progress::Counter* c = Progress::Counter::Create( std::cerr, 50 );
	CHECK( c != NULL );
	delete c;
}

TEST( Counter_To_STDLOG ) {
	Progress::Counter* c = Progress::Counter::Create( std::clog, 50 );
	CHECK( c != NULL );
	delete c;
}

TEST( Counter_To_String ) {
	std::stringstream out;
	Progress::Counter* c = Progress::Counter::Create( out, 50 );
	CHECK( c != NULL );
	delete c;
}

TEST( Counter_Invalid_Interval_Negative ) {
	Progress::Counter* c = Progress::Counter::Create( std::cout, -5 );
	CHECK( c == NULL );
	delete c;
}

TEST( Counter_Invalid_Interval_Zero ) {
	Progress::Counter* c = Progress::Counter::Create( std::cout, 0 );
	CHECK( c == NULL);
	delete c;
}

TEST_FIXTURE( SimpleCounter, Counter_No_Output_Unless_Started ) {
	CHECK( output.str().empty() );
}

TEST( Nothing_To_Count ) {
	CHECK( CounterRunner( 0, 1, "0 done (0)\n" ) );
}

TEST( Count_Minors_Before_First_Major ) {
	CHECK( CounterRunner( 1, 1, "0. done (1)\n" ) );
	CHECK( CounterRunner( 2, 1, "0.. done (2)\n" ) );
	CHECK( CounterRunner( 3, 1, "0... done (3)\n" ) );
	CHECK( CounterRunner( 4, 1, "0.... done (4)\n" ) );
}

TEST( Count_To_Majors ) {
	CHECK( CounterRunner( 5, 1, "0....5 done (5)\n" ) );
	CHECK( CounterRunner( 100, 10, "0....50....100 done (100)\n" ) );
}

TEST( Count_Minors_After_First_Major ) {
	CHECK( CounterRunner( 6, 1, "0....5. done (6)\n" ) );
	CHECK( CounterRunner( 7, 1, "0....5.. done (7)\n" ) );
	CHECK( CounterRunner( 8, 1, "0....5... done (8)\n" ) );
	CHECK( CounterRunner( 9, 1, "0....5.... done (9)\n" ) );
}

TEST( Count_Weird_Totals ) {
	CHECK( CounterRunner( 37, 3, "0....15....30.. done (37)\n" ) );
	CHECK( CounterRunner( 999, 50, "0....250....500....750.... done (999)\n") );
	CHECK( CounterRunner( 27272, 1000, "0....5000....10000....15000....20000....25000.. done (27272)\n") );
	CHECK( CounterRunner( 27272, 1111, "0....5555....11110....16665....22220.... done (27272)\n") );
}

TEST_FIXTURE( SimpleCounter, Count_Starts_With_Zero ) {
	CHECK_EQUAL( counter->count(), 0 );
}

TEST_FIXTURE( SimpleCounter, Count_Add_Ticks ) {
	const int someNumber = 71;
	counter->add( someNumber );
	CHECK_EQUAL( counter->count(), someNumber );
	counter->add( someNumber );
	CHECK_EQUAL( counter->count(), 2 * someNumber );
}

TEST_FIXTURE( SimpleCounter, Count_Set_Ticks ) {
	const int someNumber = 71;
	counter->add( 3 );
	counter->set( someNumber );
	CHECK_EQUAL( counter->count(), someNumber );
	counter->set( someNumber );
	CHECK_EQUAL( counter->count(), someNumber );
	counter->next();
	counter->set( someNumber );
	CHECK_EQUAL( counter->count(), someNumber + 1 );
}

TEST_FIXTURE( SimpleCounter, Count_Reset ) {
	counter->next();
	counter->reset();
	CHECK_EQUAL( counter->count(), 0 );
	CHECK_EQUAL( output.str(), "0. done (1)\n0" );
}

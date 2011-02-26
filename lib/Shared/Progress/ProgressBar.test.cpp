#include "Shared/Progress/ProgressBar.h"

#include "Contrib/UnitTest++/UnitTest++.h"
#include <iostream>

//////////////////////////////

const float maximum() { return 100.0; }
const float tolerance() { return 0.0001; }
const float someNumber() { return 21.3; }

const std::string expectedOutputAt20( "0%.........20%" );
const std::string expectedOutputAt100( "0%.........20%.........40%.........60%.........80%.........100%\n" );

//////////////////////////////

class SimpleProgressBar {
public:
	std::ostringstream output;
	Progress::ProgressBar p;

	SimpleProgressBar() :
		output(),
		p( output )
	{}

	virtual ~SimpleProgressBar() {}
};

//////////////////////////////

TEST_FIXTURE( SimpleProgressBar, ThereIsNoOutputBeforeStarting ) {
	CHECK( output.str().empty() );
}

TEST_FIXTURE( SimpleProgressBar, UserCannotChangePositionBeforeStarting ) {
	p.add( someNumber() );
	CHECK_CLOSE( p.position(), 0.0, tolerance() );
	p.set( someNumber() );
	CHECK_CLOSE( p.position(), 0.0, tolerance() );
}

TEST_FIXTURE( SimpleProgressBar, PositionIsZeroAtStart ) {
	p.start();
	CHECK_CLOSE( p.position(), 0.0, tolerance() );
}

TEST_FIXTURE( SimpleProgressBar, OutputIsZeroPercentAtStart ) {
	p.start();
	CHECK_EQUAL( output.str(), "0%" );
}

TEST_FIXTURE( SimpleProgressBar, AddXIncreasesPositionByX ) {
	p.start();
	p.add( someNumber() );
	CHECK_CLOSE( p.position(), someNumber(), tolerance() );
	p.add( someNumber() );
	CHECK_CLOSE( p.position(), 2 * someNumber(), 2 * tolerance() );
}

TEST_FIXTURE( SimpleProgressBar, AddCanNotAddPast100Percent ) {
	p.start();
	p.add( 101.0 );
	CHECK_CLOSE( p.position(), maximum(), tolerance() );
}

TEST_FIXTURE( SimpleProgressBar, SetXSetsPositionToX ) {
	p.start();
	p.set( someNumber() );
	CHECK_CLOSE( p.position(), someNumber(), tolerance() );
	p.add( someNumber() );
	CHECK_CLOSE( p.position(), 2 * someNumber(), 2 * tolerance() );
}

TEST_FIXTURE( SimpleProgressBar, AddingPast100PercentStopsTheBar ) {
	p.start();
	p.add( 101.0 );
	CHECK_EQUAL( expectedOutputAt100, output.str() );
	p.add( 1.0 );
	CHECK_EQUAL( expectedOutputAt100, output.str() );
	p.set( 1.0 );
	CHECK_EQUAL( expectedOutputAt100, output.str() );
}

TEST_FIXTURE( SimpleProgressBar, SettingPast100PercentStopsTheBar ) {
	p.start();
	p.set( 101.0 );
	// TODO: check that output reaches 100% and further adds+sets do nothing.

	const float beforePosition = p.position();
	p.add( 1.0 );
	CHECK_CLOSE( beforePosition, p.position(), tolerance() );
	p.set( 95.0 );
	CHECK_CLOSE( beforePosition, p.position(), tolerance() );
}

TEST_FIXTURE( SimpleProgressBar, CannotSetValueWhenStopped ) {
	p.set( someNumber() );
	CHECK_CLOSE( p.position(), 0.0, tolerance() );
}

TEST_FIXTURE( SimpleProgressBar, CannotAddValueWhenStopped ) {
	p.add( someNumber() );
	CHECK_CLOSE( p.position(), 0.0, tolerance() );
}

TEST_FIXTURE( SimpleProgressBar, CannotAddMoreThan100Percent ) {
	p.start();
	p.add( maximum() + someNumber() );
	CHECK_CLOSE( p.position(), maximum(), tolerance() );
}

TEST_FIXTURE( SimpleProgressBar, CannotSetMoreThan100Percent ) {
	p.start();
	p.set( maximum() + someNumber() );
	CHECK_CLOSE( p.position(), maximum(), tolerance() );
}

TEST_FIXTURE( SimpleProgressBar, CannotAddNegativeValue ) {
	p.start();
	p.add( -someNumber() );
	CHECK_CLOSE( p.position(), 0.0, tolerance() );	
}

TEST_FIXTURE( SimpleProgressBar, CannotSetLessThan0Percent ) {
	p.start();
	p.set( -someNumber() );
	CHECK_CLOSE( p.position(), 0.0, tolerance() );	
}

// Plan:
//		Success: 0%.........20%... [...] ...100%\n
//		Failure: 0%.........20%... abort (25.5%)\n

TEST_FIXTURE( SimpleProgressBar, At2PercentOneMinorMarkIsDisplayed ) {
	p.start();
	p.set( 2.0 );
	CHECK_EQUAL( "0%.", output.str() );
}

TEST_FIXTURE( SimpleProgressBar, At3PercentOneMinorMarkIsDisplayed ) {
	p.start();
	p.set( 3.0 );
	CHECK_EQUAL( "0%.", output.str() );
}

TEST_FIXTURE( SimpleProgressBar, At4PercentTwoMinorMarkIsDisplayed ) {
	p.start();
	p.set( 4.0 );
	CHECK_EQUAL( "0%..", output.str() );
}

TEST_FIXTURE( SimpleProgressBar, At20PercentAMajorMarkIsDisplayed ) {
	p.start();
	p.set( 20.0 );
	CHECK_EQUAL( expectedOutputAt20, output.str() );
}

TEST_FIXTURE( SimpleProgressBar, SuccessShows100Percent ) {
	p.start();
	p.add( maximum() );
	CHECK_EQUAL( expectedOutputAt100, output.str() );
}

// TODO: Test output during progress change

#include "Contrib/UnitTest++/src/UnitTest++.h"

#include "../Shared/Geometry.h"

SUITE(GeometryTestSuite) {

TEST(Pi) {
	CHECK_CLOSE(3.14159, Geometry::pi, 0.0001);
	CHECK_CLOSE(6.28318, Geometry::twopi, 0.0001);
}

////////////////////////////////////////

TEST(PointInitialization) {
	Geometry::Point p;
	CHECK_EQUAL(0.0, p.x());
	CHECK_EQUAL(0.0, p.y());

	Geometry::Point q(1.1, 2.2);
	CHECK_EQUAL(1.1, q.x());
	CHECK_EQUAL(2.2, q.y());
	
	Geometry::Point r(q);
	CHECK_EQUAL(q.x(), r.x());
	CHECK_EQUAL(q.y(), r.y());
}

TEST(PointAssignment) {
	Geometry::Point p;
	p.x(1.1);
	p.y(2.2);
	CHECK_EQUAL(1.1, p.x());
	CHECK_EQUAL(2.2, p.y());

	Geometry::Point q(3.3, 4.4);
	p = q;
	CHECK_EQUAL(3.3, p.x());
	CHECK_EQUAL(4.4, p.y());

	p += q;
	CHECK_EQUAL(6.6, p.x());
	CHECK_EQUAL(8.8, p.y());

	p -= q;
	CHECK_EQUAL(3.3, p.x());
	CHECK_EQUAL(4.4, p.y());
}

TEST(PointComparison) {
	Geometry::Point p(1,2);
	Geometry::Point q(1,2);
	Geometry::Point r(9,9);
	CHECK(p == q);
	p = q;
	CHECK(p == q);
	CHECK(p != r);
}

////////////////////////////////////////

TEST(AngleInitialization) {
	Geometry::Angle a;
	CHECK_EQUAL(0.0, a.as_r());
	
	Geometry::Angle b(1.1);
	CHECK_EQUAL(1.1, b.as_r());

	Geometry::Angle c(b);
	CHECK_EQUAL(1.1, c.as_r());
}

TEST(AngleConversion) {
	Geometry::Angle a;
	CHECK_CLOSE(0.0, a.as_r(), 0.0001);
	CHECK_CLOSE(0.0, a.as_d(), 0.0001);

	a.set(Geometry::pi);
	CHECK_CLOSE(Geometry::pi, a.as_r(), 0.0001);
	CHECK_CLOSE(180.0, a.as_d(), 0.0001);
}

TEST(AngleAssignment) {
	Geometry::Angle a;
	a.set(1.0);
	CHECK_EQUAL(1.0, a.as_r());

	a.clear();
	CHECK_EQUAL(0.0, a.as_r());

	Geometry::Angle b(Geometry::pi);
	a = b;
	CHECK_CLOSE(Geometry::pi, a.as_r(), 0.0001);

	a += b;
	CHECK_CLOSE(Geometry::twopi, a.as_r(), 0.0001);

	a -= b;
	CHECK_CLOSE(Geometry::pi, a.as_r(), 0.0001);
	
	a += Geometry::twopi;
	a.normalize();
	CHECK_CLOSE(Geometry::pi, a.as_r(), 0.0001);
}

TEST(AngleComparison) {
	Geometry::Angle a(Geometry::pi);
	Geometry::Angle b(Geometry::pi);
	Geometry::Angle c(Geometry::twopi);
	
	CHECK(a == a);
	CHECK(a == b);
	CHECK(a != c);

	CHECK(a < c);
	CHECK(a <= a);
	CHECK(a <= c);

	CHECK(c > a);
	CHECK(c >= a);
	CHECK(c >= c);
	
	Geometry::Angle epsilon(0.0001);
	CHECK(a.near(b, 0.0001));
	CHECK(a.near(b, epsilon));
}

////////////////////////////////////////

TEST(EntityCreation) {
	// default constructor
	Geometry::Entity e1;
	Geometry::Point origin;
	CHECK(e1.position() == origin);
	CHECK(e1.facing() == 0);
	CHECK_CLOSE(0.0, e1.speed(), 0.0001);
	
	// parameterized constructor
	Geometry::Point position(1,2);
	Geometry::Angle facing(Geometry::pi);
	double speed = 100;
	Geometry::Entity e2(position, facing, speed);
	CHECK(e2.position() == position);
	CHECK(e2.facing() == facing);
	CHECK_CLOSE(speed, e2.speed(), 0.0001);

	// copy constructor
	Geometry::Entity e3(e2);
	CHECK(e3.position() == e2.position());
	CHECK(e3.facing() == e2.facing());
	CHECK(e3.speed() == e2.speed());
}

TEST(EntityAssignment) {
	Geometry::Entity e1;
	Geometry::Entity e2(Geometry::Point(1,2), Geometry::Angle(Geometry::pi), 100);
	e1 = e2;
	CHECK(e1.position() == e2.position());
	CHECK(e1.facing() == e2.facing());
	CHECK(e1.speed() == e2.speed());
}

TEST(EntityModification) {
	Geometry::Entity e;
	Geometry::Angle a(Geometry::pi);
	e.setFacing(a);
	CHECK(e.facing() == a);
	double speed = 100;
	e.setSpeed(speed);
	CHECK(e.speed() == speed);
}

TEST(EntityMotion) {
	const Geometry::Point origin(0,0);
	const Geometry::Angle angle_zero(0);
	const Geometry::Angle angle_pi(Geometry::pi);
	const double speed_zero = 0;
	
	{
		// test position setting
		Geometry::Entity e(origin, angle_pi, speed_zero);
		CHECK(e.position() == origin);
	}
	
	{
		// test move(), zero speed
		Geometry::Entity e(origin, angle_pi, speed_zero);
		e.move();
		CHECK(e.position() == origin);
	}
	
	{
		// test move(), non-zero speed
		Geometry::Entity e(origin, angle_zero, 100);
		Geometry::Point p(100, 0);
		e.move();
		CHECK(e.position().near(p, 0.001));

		e.setFacing(angle_pi);
		e.setSpeed(50);
		e.move();
		CHECK(e.position().near(Geometry::Point(50,0), 0.001));
	}
}

} // suite

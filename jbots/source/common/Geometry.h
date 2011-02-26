// Geometry.h
// A collection of simple classes for an oversimplified 2D physics engine.
// Jay Baxter (jaybaxter@gmail.com)
// January, 2008

#ifndef Geometry_h__
#define Geometry_h__

#include <iostream>

namespace Geometry {

// Forward declarations
class Point;
class Angle;
class Entity;

////////////////////////////////////////////////////////////

// Useful constants
const double pi    = 3.14159;
const double twopi = 2 * pi;

////////////////////////////////////////////////////////////

// Computes the linear distance between the two specified points.  Returned
// distances are non-negative.
double distance(const Point& from, const Point& to);

// Returns the angle of a line from 'from' to 'to'.  Returned angle is the 
// smallest non-negative angle between 0 and the line between the two points.
Angle& bearing(const Point& from, const Point& to);

////////////////////////////////////////////////////////////
//
// class Point
//
// Represents a point in 2D space.

class Point {
private:
	double m_x, m_y;
public:
	// Creators
	Point() : m_x(0.0), m_y(0.0) {}
	Point(double x, double y) : m_x(x), m_y(y) {}
	Point(const Point& other) : m_x(other.x()), m_y(other.y()) {}

	// Accessors
	double x() const { return m_x; }
	double y() const { return m_y; }
	bool near(const Point& other, double epsilon) const;
	
	// Modifiers
	void x(double x) { m_x = x; }
	void y(double y) { m_y = y; }
	Point& operator=(const Point& other);
	Point& operator+=(const Point& other);
	Point& operator-=(const Point& other);
};

Point operator+(const Point& a, const Point& b);
Point operator*(const Point& a, const double factor);
bool operator==(const Point& a, const Point& b);
bool operator!=(const Point& a, const Point& b);
std::ostream& operator<<(std::ostream& os, const Point& a);

////////////////////////////////////////////////////////////
//
// class Angle
//
// Angles are stored anti-clockwise in radians from the 3 o'clock position.
// Turns clockwise are negative and anti-clockwise are positive.  Callers can
// interface with the class in degrees or radians as they wish.

class Angle {
private:
	double m_value;  // in radians, may be negative
public:
	enum Unit { degrees, radians };

	// Creators
	Angle() : m_value(0.0) {}
	Angle(const double to) : m_value(to) {}
	Angle(const Angle& to) : m_value(to.as_r()) {}

	// Accessors
	double as_d() const; // value in degree
	double as_r() const; // value in radians
	bool near(const Angle& other, const Angle& epsilon) const;
	bool near(const Angle& other, const double epsilon) const;
	
	// Modifiers
	Angle& set(const double angle) { m_value = angle; return *this; }
	Angle& clear() { return set(0.0); }
	Angle& normalize();
	Angle& operator=(const double b) { return set(b); }
	Angle& operator=(const Angle& b) { return set(b.as_r()); }
	Angle& operator+=(const Angle& b) { return set(as_r() + b.as_r()); }
	Angle& operator+=(const double b) { return set(as_r() + b); }
	Angle& operator-=(const Angle& b) { return set(as_r() - b.as_r()); }
	Angle& operator-=(const double b) { return set(as_r() - b); }

	// TODO: maybe these should be free functions
	static double r2d(const double angle);
	static double d2r(const double angle);
};

bool operator<(const Angle& a, const Angle& b);
bool operator>(const Angle& a, const Angle& b);
bool operator<=(const Angle& a, const Angle& b);
bool operator>=(const Angle& a, const Angle& b);
bool operator==(const Angle& a, const Angle& b);
bool operator!=(const Angle& a, const Angle& b);
std::ostream& operator<<(std::ostream& os, const Angle& a);

////////////////////////////////////////////////////////////
//
// class Entity
//
// Represents a physics object with location, facing, and speed.  Does not
// implement size, mass, impulse, collision, etc.

class Entity {
private:
	Point m_position;
	Angle m_facing;
	double m_speed;

public:
	// Creators
	Entity();
	Entity(const Point& position, const Angle& facing, const double speed);
	Entity(const Entity& other);

	// Accessors
	const Point& position() const { return m_position; }
	const Angle& facing() const { return m_facing; }
	const double speed() const { return m_speed; }
	
	// Modifiers
	const double setSpeed(const double speed);
	const Angle& setFacing(const Angle& facing);
	const Point& setPosition(const Point& position);
	void move();
	Entity& operator=(const Entity& other);
};

} // namespace Geometry

#endif // Geometry_h__

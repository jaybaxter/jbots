// Geometry.h
// A collection of simple classes for an oversimplified 2D physics engine.
// Jay Baxter (jaybaxter@gmail.com)
// January, 2008

#include "../Shared/Geometry.h"

#include <cmath> // pow(), sqrt(), sin(), cos(), tan(), abs()
#include <iostream>

namespace Geometry {

double distance(const Point& a, const Point& b) {
	return sqrt( pow(a.x() - b.x(), 2)  + pow(a.y() - b.y(), 2) );
}

Angle& bearing(const Point& from, const Point& to, Angle& bearing) {
	return bearing.set( tan( (to.y() - from.y()) / (to.x() - from.x()) ) );
}

////////////////////////////////////////////////////////////
// class Point

bool Point::near(const Point& other, double epsilon) const {
	if (epsilon < 0)
		return false;
	return sqrt( pow(x() - other.x(), 2) + pow(y() - other.y(), 2) ) < epsilon;
}

Point& Point::operator=(const Point& other) {
	x(other.x());
	y(other.y());
	return *this;
}

Point& Point::operator+=(const Point& other) {
	x(x() + other.x());
	y(y() + other.y());
	return *this;
}

Point& Point::operator-=(const Point& other) {
	x(x() - other.x());
	y(y() - other.y());
	return *this;
}

bool operator==(const Point& a, const Point& b) {
	return a.x() == b.x() && a.y() == b.y();
}

bool operator!=(const Point& a, const Point& b) {
	return !(a == b);
}

Point operator+(const Point& a, const Point& b) {
	Point result(a);
	result += b;
	return result;
}

Point operator*(const Point& a, const double factor) {
	Point result(a.x() * factor, a.y() * factor);
	return result;
}

std::ostream& operator<<(std::ostream& os, const Point& point) {
	return os << '<' << point.x() << ',' << point.y() << '>';
}

////////////////////////////////////////////////////////////
// class Angle

double Angle::r2d(const double angle) { 
	return angle * 360.0 / twopi;
}

double Angle::d2r(const double angle) { 
	return angle * twopi / 360.0;
}
 
// Return the angle's value in radians
double Angle::as_r() const {
	return m_value;
}

// Return the angle's value in degrees
double Angle::as_d() const {
	return r2d(as_r());
}

// clamp the value to +/- one orbit
Angle& Angle::normalize() {
	// TODO: would modulo be more efficient and equally accurate?
	while (as_r() >= twopi)  { set(as_r() - twopi); } 
	while (as_r() <= -twopi) { set(as_r() + twopi); }
	return *this;
}

// is this angle within +/- epsilon of another angle?  epsilon must be > 0
bool Angle::near(const Angle& other, const Angle& epsilon) const {
	return near(other, epsilon.as_r());
}

// is this angle within +/- epsilon of another angle?  epsilon must be > 0
bool Angle::near(const Angle& other, const double epsilon) const {
	return abs(as_r() - other.as_r()) <= epsilon;
}

bool operator<(const Angle& a, const Angle& b) {
	return a.as_r() < b.as_r();
}

bool operator>(const Angle& a, const Angle& b) {
	return a.as_r() > b.as_r();
}

bool operator<=(const Angle& a, const Angle& b) {
	return a.as_r() <= b.as_r();
}

bool operator>=(const Angle& a, const Angle& b) {
	return a.as_r() >= b.as_r();
}

bool operator==(const Angle& a, const Angle& b) {
	return a.as_r() == b.as_r();
}

bool operator!=(const Angle& a, const Angle& b) {
	return a.as_r() != b.as_r();
}

std::ostream& operator<<(std::ostream& os, const Angle& angle) {
	return os << angle.as_r() << 'r';
}

////////////////////////////////////////////////////////////
// class Point

Entity::Entity() : m_speed(0.0) {}

Entity::Entity(const Point& position, const Angle& facing, const double speed)
	: m_position(position), m_facing(facing), m_speed(speed)
{}

Entity::Entity(const Entity& other) 
	: m_position(other.position()), m_facing(other.facing()), m_speed(other.speed())
{}

const Point& Entity::setPosition(const Point& position) {
	m_position = position;
	return this->position();
}

const double Entity::setSpeed(const double speed) {
	if (speed >= 0.0)
		m_speed = speed;
	return this->speed();
}

const Angle& Entity::setFacing(const Angle& facing) {
	m_facing = facing;
	m_facing.normalize();
	return this->facing();
}

void Entity::move() {
	// Note that this method jumps the object to the new position.
	// TODO: saving the last velocity vector would improve performance
	const double r = facing().as_r();
	Point velocity(speed() * cos(r), speed() * sin(r));
	setPosition(position() + velocity);
}

Entity& Entity::operator=(const Entity& other) {
	setPosition(other.position());
	setFacing(other.facing());
	setSpeed(other.speed());
	return *this;
}

}

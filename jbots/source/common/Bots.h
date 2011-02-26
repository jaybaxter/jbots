#ifndef BOTS_H__
#define BOTS_H__

#include <string>
#include <vector>

namespace Bots {

class PhysicalThing {
protected:
	Point m_position
	Angle m_facing;
	double m_velocity;
public:
	bool Move();
};

class Sensor {
public:
	Angle m_facing;
	Angle m_theta;
	double m_range;
};

class Weapon {
protected:
	double m_range;
	double m_damage;
	double m_damageRadius;
public:
	Weapon(double range, double damage, double dmgRadius = 0.0);
};

struct Bot : public PhysicalThing {
protected:
	std::string m_name;
	std::vector<Sensor> m_sensors;
	std::vector<Weapon> m_weapons;
public:
	Bot(std::string name) : m_name(name) {}
	std::string& Name() { return m_name; }
	bool Add(Sensor& sensor);
	bool Add(Weapon& weapon);
};

} // namespace

#endif
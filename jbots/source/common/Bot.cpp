#include "Bot.h"

namespace Server {

Bot::Bot(const std::string& name)
	: m_name(name)
{
}

Bot::Bot(const std::string& name, const Geometry::Point& p, const Geometry::Angle& a) 
	: m_name(name)
{
	setPosition(p);
	setFacing(a);
	setSpeed(0);
}

double Bot::scan(const Geometry::Angle& direction, const Geometry::Angle& resolution) const {
	// Bot must be able to query Arena
	// TODO: implement
	return 0.0;
}

void Bot::fire(const Geometry::Angle& direction, const double range) const {
	// Bot must be able to request that the Arena create a missile
	// TODO: implement
}

void Bot::drive(const Geometry::Angle& direction, const double speed) {
	// TODO: implement
}

} // namespace Server

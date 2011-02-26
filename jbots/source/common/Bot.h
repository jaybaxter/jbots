#ifndef Bot_h__
#define Bot_h__

#include <string>

#include "Geometry.h"

struct Order;

namespace Server {

	class Bot : private Geometry::Entity {
	protected:
		std::string m_name;
		double m_health;
	public:
		// Creators
		Bot() {}
		Bot(const Bot& other) {}
		Bot(const std::string& name);
		Bot(const std::string& name, const Geometry::Point& p, const Geometry::Angle& a);

		// Accessors
		const std::string& name() const { return m_name; }
		bool alive() const { return health() > 0; }
		const double health() const { return m_health; }

		// Modifiers
		double scan(const Geometry::Angle& direction, const Geometry::Angle& resolution) const;
		void fire(const Geometry::Angle& direction, const double range) const;
		void drive(const Geometry::Angle& direction, const double speed);
	};
	typedef std::vector<Bot> Bots;

}

namespace Client {

class Bot {
public:
	Bot();
	~Bot();
	
	// Called by Match to determine the next order
	Order order();
};

} // namespace Client

////////////////////////////////////////////////////////////

#if 0
struct Order {
	enum OrderType { nothing, accelerate, turn, fire, scan } type;

	// 
	double parameter1, parameter2;
	double const& newVelocity = parameter1;
	double const& newFacing = parameter1;
	double const& fireAngle = parameter1;
	double const& fireRange = parameter2;
	double const& scanRange = parameter1;
	double const& scanWidth = parameter2;
};
#endif // 0

#endif // Bot_h__

#pragma once

#include "Polygon.h"

namespace  core {
	class WeilerAtherton {
	public:
		WeilerAtherton();
		~WeilerAtherton();
		static Point doWalk(std::list<Point>& enteringPoints, std::list<Point>& exitingPoints, std::list<Point>& walking_points, Polygon& pol, Point& start);
		double distance(Point p, Point q) const;
		void addPointInPlace(std::list<Point>& list, const Line& line, const IntersectionPoint& ip) const;
		std::list<Polygon> process(Polygon& subject, Polygon& clipping) const;
	};
}

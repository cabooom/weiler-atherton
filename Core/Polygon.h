#pragma once

#include <list>
#include "Point.h"
#include "Line.h"

namespace core {
	class Polygon {
		std::list<Point> _points;
		std::list<Line> _lines;
	public:
		Polygon();
		~Polygon();
		bool isSelfIntersecting();
		bool isClockwiseOriented();
		void addPoint(Point p);
		Point deletePoint();
		void clear();
		void reverse();
		const std::list<Point>& points() const;
		const std::list<Line>& lines() const;
	};
}
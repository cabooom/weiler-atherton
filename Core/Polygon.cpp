#include <algorithm>
#include "Polygon.h"

using namespace core;
Polygon::Polygon() {}


Polygon::~Polygon() {}

bool Polygon::isSelfIntersecting() {
	if (_points.size() < 4) {
		return false;
	}
	for (auto&& line1 : _lines) {
		for (auto&& line2 : _lines) {
			if (line1 != line2 &&
				line1.B() != line2.A() &&
				line1.A() != line2.B() &&
				line1.isIntersecting(line2)) {
				return true;
			}
		}
	}
	return false;
}

bool Polygon::isClockwiseOriented() {	
	double sum = 0;
	for (auto it_next = _points.begin(), it = it_next++; it_next != _points.end(); it++, it_next++) {
		sum += (it_next->x() - it->x()) * (it_next->y() + it->y());
	}
	sum += (_points.front().x() - _points.back().x()) * (_points.front().y() + _points.back().y());
	return sum > 0;
}

void Polygon::addPoint(Point p) {
	if (_points.size()) {
		if (_lines.size()) _lines.pop_back();
		_lines.push_back(Line(_points.back(), p));
		_lines.push_back(Line(p, _points.front()));
	}
	_points.push_back(p);
}

Point Polygon::deletePoint() {
	Point tmp = _points.back();
	_points.pop_back();
	if (_lines.size()) _lines.pop_back(); // delete line from last point to first
	if (_lines.size()) _lines.pop_back(); // delete prev line 
	if (_points.size() > 1)
	// construct line from new last point to first
		_lines.push_back(Line(_points.back(), _points.front()));
	return tmp;
}

void Polygon::clear() {
	_points.clear();
	_lines.clear();
}

void Polygon::reverse() {
	_points.reverse();

	// reverse lines, but keep last one in place
	Line tmp = _lines.back();
	_lines.pop_back();
	_lines.reverse();
	_lines.push_back(tmp);
	for (Line& line : _lines) {
		line = Line(line.B(), line.A());
	}
}

const std::list<Point>& Polygon::points() const {
	return _points;
}

const std::list<Line>& Polygon::lines() const {
	return _lines;
}

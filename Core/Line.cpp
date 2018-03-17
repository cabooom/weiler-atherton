#include "Line.h"
#include <algorithm>

using namespace core;
void Line::computeEquation() {
	_a1 = _B.y() - _A.y();
	_b1 = _A.x() - _B.x();
	_c1 = _a1 * _A.x() + _b1 * _A.y();
}

Line::Line()
{
}

Line::Line(const Point& A, const Point& B): _A(A), _B(B) {
	computeEquation();
}

Line::Line(double x1, double y1, double x2, double y2) {
	_A = Point(x1, y1);
	_B = Point(x2, y2);
	computeEquation();
}

bool Line::operator==(Line& l2) const {
	return _A == l2.A() && _B == l2.B();
}

bool Line::operator!=(Line& l2) const {
	return !(*this == l2);
}

const Point& Line::A() const { return _A; }

const Point& Line::B() const { return _B; }


IntersectionPoint Line::findIntersection(const Line& l) const {
	double a2 = l._B.y() - l._A.y();
	double b2 = l._A.x() - l._B.x();
	double c2 = a2 * l._A.x() + b2 * l._A.y();

	double determinant = _a1 * b2 - a2 * _b1;

	if (determinant == 0) {
		return IntersectionPoint();
	}
	else {
		double x = (b2 * _c1 - _b1 * c2) / determinant;
		double y = (_a1 * c2 - a2 * _c1) / determinant;

		// check if point belongs to segment
		if (x < std::min(_A.x(), _B.x()) || x > std::max(_A.x(), _B.x())) return IntersectionPoint();
		if (y < std::min(_A.y(), _B.y()) || y > std::max(_A.y(), _B.y())) return IntersectionPoint();

		if (x < std::min(l.A().x(), l.B().x()) || x > std::max(l.A().x(), l.B().x())) return IntersectionPoint();
		if (y < std::min(l.A().y(), l.B().y()) || y > std::max(l.A().y(), l.B().y())) return IntersectionPoint();
		return IntersectionPoint(x, y, determinant < 0);
	}
}

bool Line::isIntersecting(Line& b) const {
	auto res = findIntersection(b);
	return res.isValid();
}

Line::~Line()
{
}

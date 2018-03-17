#include "WeilerAtherton.h"

using namespace core;
WeilerAtherton::WeilerAtherton() {
}

WeilerAtherton::~WeilerAtherton() {
}

template <class T>
bool listContains(std::list<T> list, T value) {
	return std::find(list.begin(), list.end(), value) != list.end();
}

Point WeilerAtherton::doWalk(std::list<Point>& enteringPoints, std::list<Point>& exitingPoints, std::list<Point>& walking_points, Polygon& pol, Point& start) {
	auto iter = std::find(walking_points.begin(), walking_points.end(), start);

	while (true) {
		pol.addPoint(*iter++);
		
		if (iter == walking_points.end()) { // simulate circular list
			iter = walking_points.begin();
		}

		if (listContains<Point>(enteringPoints, *iter)) {
			//enteringPoints.erase(it);
			break;
		}
		
		if (listContains<Point>(exitingPoints, *iter)) {
			//exitingPoints.erase(it);
			break;
		}
	}
	return *iter;
}

double WeilerAtherton::distance(Point p, Point q) const {
	return std::sqrt((p.x() - q.x())*(p.x() - q.x()) +
		(p.y() - q.y())*(p.y() - q.y()));
}

void WeilerAtherton::addPointInPlace(std::list<Point>& list, const Line& line, const IntersectionPoint& ip) const {
	auto start = std::find(list.begin(), list.end(), line.A());
	auto end_line = std::find(list.begin(), list.end(), line.B());

	auto it = start;
	double dist_from_start = distance(ip, *it);

	while (it != end_line && it != list.end()) {		
		if (distance(*it, *start) >= dist_from_start) {
			break;
		}
		it++;
	}
	list.insert(it, ip);
}

std::list<Polygon> WeilerAtherton::process(Polygon & in_subject, Polygon & in_clipping) const {
	std::list<Polygon> result;
	Polygon subject(in_subject), clipping(in_clipping);
	if (subject.lines().size() < 3 || clipping.lines().size() < 3) {
		return result;		
	}
	if (!subject.isClockwiseOriented()) {
		subject.reverse();
	}
		
	if (!clipping.isClockwiseOriented()) {
		clipping.reverse();
	}

	std::list<Point> subj_points(subject.points());
	std::list<Point> clip_points(clipping.points());
	std::list<Point> entering_points;
	std::list<Point> exiting_points;

	//auto subjPointsIterator = subj_points.begin();	
	for (auto&& subj_line : subject.lines()) {
		//auto clipPointsIterator = clip_points.begin();
		for (auto&& clip_line : clipping.lines()) {
			IntersectionPoint ip = subj_line.findIntersection(clip_line);
			if (ip.isValid()) {
				if (ip.isEntering()) {
					entering_points.push_back(ip);
				}
				else {
					exiting_points.push_back(ip);
				}
				addPointInPlace(subj_points, subj_line, ip);
				addPointInPlace(clip_points, clip_line, ip);
			}
		}
	}

	entering_points.swap(exiting_points);

	auto iter_entering_points = entering_points.begin();
	while (iter_entering_points != entering_points.end()) {
		Polygon pol;
		Point start = *iter_entering_points++, next = start;
		
		do {
			next = doWalk(entering_points, exiting_points, subj_points, pol, next);
			next = doWalk(entering_points, exiting_points, clip_points, pol, next);
		} while (next != start);
		//enteringPoints.pop_front();
		result.push_back(pol);
	}

	return result;
}

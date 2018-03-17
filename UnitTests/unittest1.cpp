#include "stdafx.h"
#include "CppUnitTest.h"

#include "../Core/Line.h"
#include "../Core/Point.h"
#include "../Core/Polygon.h"
#include "../Core/WeilerAtherton.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace core;

namespace UnitTests {		
	TEST_CLASS(UnitTest1) {
	public:
		
		TEST_METHOD(LineIntersection) {
			Line line1(0, 0, 4, 4);
			Line line2(0, 4, 4, 0);

			IntersectionPoint p = line1.findIntersection(line2);

			Assert::IsTrue(line2.isIntersecting(line1));
			Assert::AreEqual(Point(2, 2).x(), p.x());
			Assert::AreEqual(Point(2, 2).y(), p.y());
			Assert::IsTrue(p.isEntering());
		}
		TEST_METHOD(AddPolygonPoint) {
			Polygon	p;
			p.addPoint(Point(0, 0));
			p.addPoint(Point(0, 0));
			Assert::AreEqual(p.points().size(), static_cast<size_t>(2));
		}

		TEST_METHOD(PolygonSelfintersection) {
			Polygon p;
			p.addPoint(Point(0, 0));
			p.addPoint(Point(0, 1));
			p.addPoint(Point(1, 0));
			Assert::IsFalse(p.isSelfIntersecting());

			p.addPoint(Point(1, 1));
			Assert::IsTrue(p.isSelfIntersecting());
		}

		TEST_METHOD(PolygonClockwiseOrientation) {
			Polygon p;
			p.addPoint(Point(0, 0));
			p.addPoint(Point(0, 1));
			p.addPoint(Point(1, 0));
			Assert::IsTrue(p.isClockwiseOriented());

			Polygon p1;			
			p1.addPoint(Point(1, 0));
			p1.addPoint(Point(0, 1));
			p1.addPoint(Point(0, 0));
			Assert::IsFalse(p1.isClockwiseOriented());
		}

		TEST_METHOD(PolygonIntersection1) {
			Polygon p;
			p.addPoint(Point(-3, -3));
			p.addPoint(Point(-3, 3));
			p.addPoint(Point(1, 0));

			Polygon p1;
			p1.addPoint(Point(-1, 0));
			p1.addPoint(Point(3, 3));
			p1.addPoint(Point(3, -3));
			auto res = WeilerAtherton().process(p, p1);
			Assert::IsTrue(res.size() > 0);
		}

		TEST_METHOD(PolygonIntersection2) {
			Polygon p;
			p.addPoint(Point(-2, 1));
			p.addPoint(Point(2, 1));
			p.addPoint(Point(2, -1));
			p.addPoint(Point(-2, -1));

			Polygon p1;
			p1.addPoint(Point(-1, 2));
			p1.addPoint(Point(1, 2));
			p1.addPoint(Point(1, -2));
			p1.addPoint(Point(-1, -2));
			auto res = WeilerAtherton().process(p, p1);
			Assert::IsTrue(res.size() > 0);
		}

		TEST_METHOD(PolygonIntersection3) {
			Polygon p1;
			p1.addPoint(Point(0, -1));
			p1.addPoint(Point(0, 0));
			p1.addPoint(Point(1, 1));
			p1.addPoint(Point(2, 0));
			p1.addPoint(Point(3, 1));
			p1.addPoint(Point(4, 0));
			p1.addPoint(Point(5, 1));
			p1.addPoint(Point(6, 0));
			p1.addPoint(Point(6, -1));
			
			Polygon p2;
			p2.addPoint(Point(0, 0.5));
			p2.addPoint(Point(0, 3));
			p2.addPoint(Point(6, 3));
			p2.addPoint(Point(6, 0.5));
			auto res = WeilerAtherton().process(p1, p2);
			Assert::IsTrue(res.size() > 0);
		}
	};
}
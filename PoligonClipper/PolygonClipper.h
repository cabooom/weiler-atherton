#pragma once

#include <QtGui>
#include "ui_PolygonClipper.h"
#include "FileUtils.h"
#include "../Core/Point.h"
#include "../Core/Line.h"
#include "../Core/Polygon.h"
#include "../Core/WeilerAtherton.h"

class PolygonClipper : public QMainWindow
{
	Q_OBJECT

public:
	PolygonClipper(QWidget *parent = Q_NULLPTR);
	void paintEvent(QPaintEvent* event);
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;

private slots:
	void interceptionSelected();
	void polygon1Selected();
	void polygon2Selected();
	void saveToJson();
	void loadFromJson();
	void printToPdf();

private:
	Ui::PolygonClipperClass ui;
	QPolygon p1;
	QPolygon p2;
	core::Polygon wa_p1;
	core::Polygon wa_p2;
	std::list<core::Polygon> intersection;
};

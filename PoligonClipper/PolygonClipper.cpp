#include "PolygonClipper.h"

PolygonClipper::PolygonClipper(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->setMouseTracking(true);
	ui.paintWidget->setMouseTracking(true);
	ui.statusBar->addWidget(ui.xyLabel);

	connect(ui.rbPolygon1, SIGNAL(clicked()), this, SLOT(polygon1Selected()));
	connect(ui.rbPolygon2, SIGNAL(clicked()), this, SLOT(polygon2Selected()));
	connect(ui.rbIntersection, SIGNAL(clicked()), this, SLOT(interceptionSelected()));
	connect(ui.btnSave, SIGNAL(clicked()), this, SLOT(saveToJson()));
	connect(ui.btnLoad, SIGNAL(clicked()), this, SLOT(loadFromJson()));
	connect(ui.btnPrint, SIGNAL(clicked()), this, SLOT(printToPdf()));
}

void PolygonClipper::interceptionSelected()
{
	update();
}

void PolygonClipper::polygon1Selected()
{
	update();
}

void PolygonClipper::polygon2Selected()
{
	update();
}

void PolygonClipper::printToPdf()
{
	QPrinter printer(QPrinter::HighResolution);
	printer.setOutputFormat(QPrinter::PdfFormat);
	printer.setOutputFileName(QFileDialog::getSaveFileName(this,
		"Save polygons to PDF", "",
		"Adobe PDF (*.pdf);;All Files (*)"));
	printer.setFullPage(true);

	QPainter painter(&printer);

	double xscale = printer.pageRect().width() / double(ui.paintWidget->width());
	double yscale = printer.pageRect().height() / double(ui.paintWidget->height());
	double scale = qMin(xscale, yscale);
	painter.translate(printer.paperRect().x() + printer.pageRect().width() / 2,
		printer.paperRect().y() + printer.pageRect().height() / 2);
	painter.scale(scale, scale);
	painter.translate(-ui.paintWidget->width() / 2, -ui.paintWidget->height() / 2);
	render(&painter);
}

void PolygonClipper::loadFromJson()
{
	QString filename = QFileDialog::getOpenFileName(this,
		"Load polygons from Json", "",
		"*.json");
	QJsonDocument doc = FileUtils::GetInstance().loadJson(filename);
	QJsonArray polygon1 = doc.object().value("polygon_1").toArray();
	QJsonArray polygon2 = doc.object().value("polygon_2").toArray();

	p1.clear();
	p2.clear();
	wa_p1.clear();
	wa_p2.clear();
	for (auto&& p : polygon1) 
	{
		const QJsonObject& point = p.toObject();
		int x = point["x"].toInt();
		int y = point["y"].toInt();
		p1.append(QPoint(x, y));
		wa_p1.addPoint(core::Point(x, y));
	}
	for (auto&& p : polygon2)
	{
		const QJsonObject& point = p.toObject();
		int x = point["x"].toInt();
		int y = point["y"].toInt();
		p2.append(QPoint(x, y));
		wa_p2.addPoint(core::Point(x, y));
	}
	intersection = core::WeilerAtherton().process(wa_p1, wa_p2);
	update();
}

void PolygonClipper::saveToJson()
{
	QJsonObject obj;
	QJsonArray polygons;
	QJsonArray pol_1;
	for (auto&& p: p1)
	{
		QJsonObject point;
		point["x"] = p.x();
		point["y"] = p.y();
		pol_1.append(point);
	}
	obj["polygon_1"] = pol_1;

	QJsonArray pol_2;
	for (auto&& p : p2)
	{
		QJsonObject point;
		point["x"] = p.x();
		point["y"] = p.y();
		pol_2.append(point);
	}
	obj["polygon_2"] = pol_2;

	QString filename = QFileDialog::getSaveFileName(this,
		"Save polygons to Json", "",
		"*.json");
	FileUtils::GetInstance().saveJson(QJsonDocument(obj), filename);
}

void PolygonClipper::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);

	if (!ui.rbIntersection->isChecked())
	{
		QColor color;
		color = wa_p1.isSelfIntersecting() ? Qt::red : Qt::black;
		painter.setPen(QPen(color, 2, Qt::SolidLine));
		painter.drawPolygon(p1);
		color = wa_p2.isSelfIntersecting() ? Qt::red : Qt::black;
		painter.setPen(QPen(color, 2, Qt::DashDotDotLine));
		painter.drawPolygon(p2);
	}

	if (!wa_p1.isSelfIntersecting() && !wa_p2.isSelfIntersecting()) 
	{
		painter.setPen(QPen(Qt::green, 2, Qt::SolidLine));
		//painter.setBackground(QBrush(Qt::green, Qt::SolidPattern));
		for (auto&& poly : intersection)
		{
			QPolygon qp;
			for (auto&& point : poly.points())
			{
				qp.append(QPoint(point.x(), point.y()));
			}
			painter.drawPolygon(qp);
		}
	}
}

void PolygonClipper::mousePressEvent(QMouseEvent* event)
{
	if (ui.rbIntersection->isChecked())
	{
		return;
	}
	if (event->button() == Qt::MouseButton::LeftButton) 
	{
		if (ui.rbPolygon1->isChecked())
		{
			p1.append(QPoint(event->x(), event->y()));
			wa_p1.addPoint(core::Point(event->x(), event->y()));
		}
		if (ui.rbPolygon2->isChecked())
		{
			p2.append(QPoint(event->x(), event->y()));
			wa_p2.addPoint(core::Point(event->x(), event->y()));
		}
	} 
	if (event->button() == Qt::MouseButton::RightButton)
	{
		if (ui.rbPolygon1->isChecked())
		{
			if (!p1.isEmpty()) 
			{
				p1.removeLast();
				wa_p1.deletePoint();
			}
		}
		if (ui.rbPolygon2->isChecked())
		{
			if (!p2.isEmpty())
			{
				p2.removeLast();
				wa_p2.deletePoint();
			}
		}
	}
	intersection = core::WeilerAtherton().process(wa_p1, wa_p2);
	update();
}

void PolygonClipper::mouseMoveEvent(QMouseEvent *event)
{
	QString label_text = "X=" + QString().setNum(event->x()) +
		" Y=" + QString().setNum(event->y());
	//ui.statusBar->showMessage("X=" + QString().setNum(event->x()));
	ui.xyLabel->setText(label_text);
}

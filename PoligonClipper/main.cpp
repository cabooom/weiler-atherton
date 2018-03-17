#include "PolygonClipper.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	PolygonClipper w;
	w.show();
	return a.exec();
}

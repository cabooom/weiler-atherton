#pragma once

#include <QObject>
#include <QFileDialog>
#include <QtGui>
#include <QPrinter>
#include <QJsonDocument>

class FileUtils {
	FileUtils();
public:
	~FileUtils();
	QJsonDocument loadJson(QString& filename);
	void saveJson(QJsonDocument& document, QString& filename);
	static FileUtils& GetInstance() {
		static FileUtils instance;
		return instance;
	}
};

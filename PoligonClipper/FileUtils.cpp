#include "FileUtils.h"

FileUtils::FileUtils()
{
}

FileUtils::~FileUtils()
{
}

QJsonDocument FileUtils::loadJson(QString& filename) {
	QFile jsonFile(filename);
	jsonFile.open(QFile::ReadOnly);
	return QJsonDocument().fromJson(jsonFile.readAll());
}

void FileUtils::saveJson(QJsonDocument& document, QString& filename) {
	QFile jsonFile(filename);
	jsonFile.open(QFile::WriteOnly);
	jsonFile.write(document.toJson(QJsonDocument::Indented));
}



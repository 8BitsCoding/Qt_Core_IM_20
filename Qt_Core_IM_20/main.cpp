#include <QtCore/QCoreApplication>

#include <qdebug.h>
#include <qdatastream.h>
#include <qtextstream.h>
#include <qfile.h>
#include <qdir.h>
#include <qfileinfo.h>
#include <qrandom.h>

bool createFile(QString path) {
	QFile file(path);
	if (!file.open(QIODevice::WriteOnly)) {
		qWarning() << file.errorString();
		return false;
	}

	QTextStream stream(&file);
	int max = 1000;
	QString banner = "Random number: ";
	qInfo() << "Writing " << banner;
	stream << banner;

	for (int i = 0; i < 5; i++) {
		qint32 num = QRandomGenerator::global()->bounded(max);
		qInfo() << "Writing: " << num;
		stream << num << "\r\n";
	}

	file.close();
	return true;
}

void readFile(QString path) {
	QFile file(path);
	if (!file.open(QIODevice::ReadOnly)) {
		qWarning() << file.errorString();
		return;
	}

	QTextStream stream(&file);

	QString banner;
	stream >> banner;

	qInfo() << "Banner : " << banner;

	for (int i = 0; i < 5; i++) {
		// qint32 num;
		QString num;
		stream >> num;
		qInfo() << "Random: " << num;
	}

	file.close();
}

int main(int argc, char* argv[])
{
	QCoreApplication a(argc, argv);

	QString path = QDir::currentPath() + QDir::separator() + "test.txt";
	qInfo() << "Path : " << path;

	if (createFile(path)) {
		readFile(path);
	}

	return a.exec();
}
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	// QSettings values
	QCoreApplication::setOrganizationName("evgom");
	QCoreApplication::setApplicationName("Alarma2");

	MainWindow w;
	w.show();

	return a.exec();
}

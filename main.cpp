#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	// QSettings values
	QCoreApplication::setOrganizationName("evgom");
	QCoreApplication::setApplicationName("Alarma2");

	//---------------------------------------------------
	//	Crear Clase Alarms y Settings, para así escribir y borrar Alarmas
	//---------------------------------------------------

	MainWindow w;
	w.show();

	return a.exec();
}

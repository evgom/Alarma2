#include "systemtray.h"

SystemTray::SystemTray(QObject *parent) : QSystemTrayIcon(parent)
{
	QIcon *ico = new QIcon("/home/erick/Qt/Alarma2/TFC.ico");
	setIcon(*ico);

	setToolTip("Alarsdfdma");

	QMenu *menu = new QMenu("hola");
	menu->addAction("Temporal");
	menu->addAction("Salir");
	setContextMenu(menu);

	show();


	connect(this, SIGNAL(messageClicked()), parent, SLOT(close()));
	connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason) ), this,
			SLOT(actionsSysTray(QSystemTrayIcon::ActivationReason)));

	connect(this, SIGNAL(hideMain()), parent, SLOT(close()));
}

void SystemTray::actionsSysTray(QSystemTrayIcon::ActivationReason e)
{
	switch (e) {
	case QSystemTrayIcon::Unknown:
		qDebug() << "Unknown";
		break;

	/*case QSystemTrayIcon::Context:
		qDebug() << "Context";
		break;*/

	case QSystemTrayIcon::DoubleClick:
		qDebug() << "DoubleClick";
		break;

	/*case QSystemTrayIcon::Trigger:
		qDebug() << "Trigger";
		break;*/

	case QSystemTrayIcon::MiddleClick:
		qDebug() << "MiddleClick";
		break;

	default:
		break;
	}

	qDebug() << "Valor recibido" << e;

	//emit hideMain();
	//deleteLater();
	msgCritical();
}

void SystemTray::msgCritical()
{
	showMessage("Mensaje de prueba", "Hola hola", QSystemTrayIcon::Critical, 5000);
}

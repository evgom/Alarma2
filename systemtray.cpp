#include "systemtray.h"

SystemTray::SystemTray(QObject *parent) : QSystemTrayIcon(parent)
{
	QIcon *ico = new QIcon("/home/erick/Qt/Alarma2/alarm-clock.png");
	setIcon(*ico);

	setToolTip("Alarma 2");

	QMenu *menu = new QMenu(qobject_cast<QWidget*>(parent) );
	menu->addAction("Activar/Desactivar Alarma", this, SIGNAL(toogleEnableAlarm()));
	menu->addAction("Salir", this, SLOT(closeProgram()));
	setContextMenu(menu);

	show();


	connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason) ), this,
			SLOT(actionsSysTray(QSystemTrayIcon::ActivationReason)));

	connect(this, SIGNAL(hideMain()), parent, SLOT(hide()));
	connect(this, SIGNAL(showMain()), parent, SLOT(show()));
	connect(this, SIGNAL(closeMain()), parent, SLOT(close()));

	// Creo que se esto se puede cambiar a un emit y un connect.
	connect(this, SIGNAL(getIsHiddenMain()), parent, SLOT(isMainHidden()));
	connect(parent, SIGNAL(sendIsMainHidden(bool)), this, SLOT(mainHideShow(bool)));

	connect(this, SIGNAL(toogleEnableAlarm()), parent, SLOT(toogleEnableAlarm()));
	connect(parent, SIGNAL(EnableAlarmChanged(bool)), this, SLOT(updateEnableAlarmMenu(bool)));
}

void SystemTray::actionsSysTray(QSystemTrayIcon::ActivationReason e)
{
	qDebug() << "Valor recibido" << e;

	switch (e) {
	case QSystemTrayIcon::Unknown:
		qDebug() << "Unknown";
		break;

	case QSystemTrayIcon::Context:
		qDebug() << "Context";
		closeProgram();
		break;

	case QSystemTrayIcon::DoubleClick:
		qDebug() << "DoubleClick";
		break;

	case QSystemTrayIcon::Trigger:
		//qDebug() << "Trigger";
		emit getIsHiddenMain();
		break;

	case QSystemTrayIcon::MiddleClick:
		qDebug() << "MiddleClick";
		break;

	default:
		qDebug() << "Default" << e;
		break;
	}
}

void SystemTray::msgCritical()
{
	showMessage("Mensaje de prueba", "Hola hola", QSystemTrayIcon::Critical, 5000);
}

void SystemTray::mainHideShow(bool stateWindow)
{
	if (stateWindow)
	{
		emit showMain();
		qDebug() << "Unhide main screen";
	}
	else
	{
		emit hideMain();
		qDebug() << "Hide main screen";
	}
}

void SystemTray::updateEnableAlarmMenu(bool statusAlarm)
{
	// Implementar checked en el menú como ícono
	qDebug() << "Alarma:" << statusAlarm;
}

// Implementación temporal. Parece que tiene que ver con closeevent.
void SystemTray::closeProgram()
{
	deleteLater();
	emit closeMain();
}

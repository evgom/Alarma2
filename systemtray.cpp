#include "systemtray.h"

SystemTray::SystemTray(QObject *parent) : QSystemTrayIcon(parent)
{
	QIcon *ico = new QIcon("/home/erick/Qt/Alarma2/alarm-clock.png");
	setIcon(*ico);

	setToolTip("Alarma 2");


	QAction *actionAlarm = new QAction("Activar/Desactivar Alarma", this);
	actionAlarm->setCheckable(true);

	QMenu *menu = new QMenu(qobject_cast<QWidget*>(parent) );
	menu->insertAction(0, actionAlarm);
	menu->addAction("Salir", this, SLOT(closeProgram()));
	setContextMenu(menu);

	connect(actionAlarm, SIGNAL(toggled(bool)), parent, SLOT(setEnableAlarm(bool)));
	connect(parent, SIGNAL(enableAlarmChanged(bool)), actionAlarm, SLOT(setChecked(bool)));
	//Es probable que se necesite un QAction para el checkbox de la venta principal.


	connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason) ), this,
			SLOT(actionsSysTray(QSystemTrayIcon::ActivationReason)));

	connect(this, SIGNAL(closeMain()), parent, SLOT(close()));
	connect(this, SIGNAL(toogleMainHide()), parent, SLOT(toogleMainHide()));
	connect(parent, SIGNAL(alarmStartedStoped(bool)),
			this, SLOT(msgAlarmStartedStoped(bool)));


	connect(this, SIGNAL(messageClicked()), this, SLOT(slotDePrueba()));

	show();
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
		emit toogleMainHide();
		break;

	case QSystemTrayIcon::MiddleClick:
		qDebug() << "MiddleClick";
		break;

	default:
		qDebug() << "Default" << e;
		break;
	}
}

// Implementación temporal. Parece que tiene que ver con closeevent.
void SystemTray::closeProgram()
{
	deleteLater();
	emit closeMain();
}

void SystemTray::msgAlarmStartedStoped(bool started)
{
	const qint32 timeMessage = 20000;

	if(started)
		showMessage(QApplication::applicationName(), "Alarma activada",
					QSystemTrayIcon::Information, timeMessage);
	else
		showMessage(QApplication::applicationName(), "Alarma detenida",
					QSystemTrayIcon::Warning, timeMessage);
}

void SystemTray::slotDePrueba()
{
	qDebug() << "Slot de Prueba";
}

#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QSystemTrayIcon>
#include <QDebug>
#include <QMenu>
#include <QApplication>

class SystemTray : public QSystemTrayIcon
{
	Q_OBJECT
public:
	explicit SystemTray(QObject *parent = 0);

public slots:
	void actionsSysTray(QSystemTrayIcon::ActivationReason e);

private slots:
	void closeProgram();
	void msgAlarmStartedStoped(bool started);
	void slotDePrueba();

signals:
	void closeMain();
	void toogleMainHide();
};

#endif // SYSTEMTRAY_H

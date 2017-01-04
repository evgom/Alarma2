#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QSystemTrayIcon>
#include <QDebug>
#include <QMenu>

class SystemTray : public QSystemTrayIcon
{
	Q_OBJECT
public:
	explicit SystemTray(QObject *parent = 0);

public slots:
	void actionsSysTray(QSystemTrayIcon::ActivationReason e);
	void msgCritical();

private slots:
	void closeProgram();
	void mainHideShow(bool);
	void updateEnableAlarmMenu(bool);

signals:
	void hideMain();
	void showMain();
	void closeMain();
	void getIsHiddenMain();
	void toogleEnableAlarm();
};

#endif // SYSTEMTRAY_H

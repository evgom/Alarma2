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

signals:
	void hideMain();

public slots:
	void actionsSysTray(QSystemTrayIcon::ActivationReason e);
	void msgCritical();
};

#endif // SYSTEMTRAY_H

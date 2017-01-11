#ifndef ALARMSETTINGS_H
#define ALARMSETTINGS_H

#include <QSettings>
#include <QApplication>
#include <QDebug>
#include "alarm.h"

#define formatTime "h:mm"

class AlarmSettings : public QObject
{
	Q_OBJECT
public:
	explicit AlarmSettings(QObject *parent = 0);

	Alarm* getAlarm();
	void setAlarm(const Alarm &newAlarm);
	void writeAlarmSettings();

private:
	QSettings *alarmSettings;
	QString destination;
	Alarm *alarm;
	void readAlarmSettings();
	QSet<int8_t> days;

signals:

public slots:
};

#endif // ALARMSETTINGS_H

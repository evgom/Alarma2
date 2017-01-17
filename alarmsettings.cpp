#include "alarmsettings.h"

AlarmSettings::AlarmSettings(QObject *parent) : QObject(parent)
{
	destination = ".config/";
	destination += QCoreApplication::organizationName() + "/";
	//destination += QCoreApplication::applicationName() + "/";
	destination += "alarms.ini";

	alarm = new Alarm(this);

	readAlarmSettings();
}

void AlarmSettings::readAlarmSettings()
{
	QString time, file, days;
	QSettings settingsAlarms(destination, QSettings::NativeFormat, this);

	settingsAlarms.beginGroup("Alarms");
	time = settingsAlarms.value("time", "7:00").toString();
	file = settingsAlarms.value("file").toString();
	days = settingsAlarms.value("days", "1 2 3 4 5 6 7").toString();
	settingsAlarms.endGroup();

	alarm->setTime(QTime::fromString(time, formatTime));
	alarm->setFile(file);
	alarm->setDays(days);
}

void AlarmSettings::writeAlarmSettings()
{
	QSettings settingsAlarms(destination, QSettings::NativeFormat, this);

	settingsAlarms.beginGroup("Alarms");
	settingsAlarms.setValue("time", alarm->getTime().toString("h:mm"));
	settingsAlarms.setValue("file", alarm->getFile());
	settingsAlarms.setValue("days", alarm->getDaysQstring());
	settingsAlarms.endGroup();
}

Alarm* AlarmSettings::getAlarm()
{
	return alarm;
}

void AlarmSettings::setAlarm(const Alarm &newAlarm)
{
	*alarm = newAlarm;
}

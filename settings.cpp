#include "settings.h"

Settings::Settings(QObject *parent) : QSettings(parent)
{
	readSettings();
}


void Settings::readSettings()
{
	enableAlarm = value("enableAlarm", false).toBool();
	closeToTray = value("closeToTray", true).toBool();

	beginGroup("Volume");
	enableVolGrad = value("volGradual", true).toBool();
	volIni = value("volumeInicial", 0).toInt();
	volFin = value("volumeFinal", 100).toInt();
	volInc = value("volumeIncrement", 5).toInt();
	timeMaxVol = value("timeToMaxVolumen", 60).toInt();
	endGroup();

	beginGroup("Sleep");
	enableSleep = value("enableSleep", true).toBool();
	timeSleep = value("timeSleep", 5).toInt();
	endGroup();
}

void Settings::writeSettings()
{
	setValue("enableAlarm", enableAlarm);
	setValue("closeToTray", closeToTray);

	beginGroup("Volume");
	setValue("volGradual", enableVolGrad);
	setValue("volumeInicial", volIni);
	setValue("volumeFinal", volFin);
	setValue("volumeIncrement", volInc);
	setValue("timeToMaxVolumen", timeMaxVol);
	endGroup();

	beginGroup("Sleep");
	setValue("enableSleep", enableSleep);
	setValue("timeSleep", timeSleep);
	endGroup();
}

bool Settings::isEnableAlarm()
{
	return enableAlarm;
}

bool Settings::isCloseToTray()
{
	return closeToTray;
}

bool Settings::isEnableVolGrad()
{
	return enableVolGrad;
}

bool Settings::isEnableSleep()
{
	return enableSleep;
}

quint8 Settings::getVolIni()
{
	return volIni;
}

quint8 Settings::getVolFin()
{
	return volFin;
}

quint8 Settings::getVolInc()
{
	return volInc;
}

quint32 Settings::getTimeMaxVol()
{
	return timeMaxVol;
}

quint32 Settings::getTimeSleep()
{
	return timeSleep;
}

void Settings::setEnableAlarm(bool value)
{
	enableAlarm = value;
}

void Settings::setCloseToTray(bool value)
{
	closeToTray = value;
}

void Settings::setEnableVolGrad(bool value)
{
	enableVolGrad = value;
}

void Settings::setEnableSleep(bool value)
{
	enableSleep = value;
}

void Settings::setVolIni(quint8 value)
{
	volIni = value;
}

void Settings::setVolFin(quint8 value)
{
	volFin = value;
}

void Settings::setVolInc(quint8 value)
{
	volInc = value;
}

void Settings::setTimeMaxVol(quint32 value)
{
	timeMaxVol = value;
}

void Settings::setTimeSleep(quint32 value)
{
	timeSleep = value;
}

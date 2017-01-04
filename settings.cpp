#include "settings.h"

Settings::Settings(QObject *parent) : QSettings(parent)
{
	readSettings();
}


void Settings::readSettings()
{
	isEnableAlarm = value("enableAlarm", false).toBool();

	beginGroup("Volume");
	isEnableVolGrad = value("volGradual", true).toBool();
	volIni = value("volumeInicial", 0).toInt();
	volFin = value("volumeFinal", 100).toInt();
	volInc = value("volumeIncrement", 5).toInt();
	timeMaxVol = value("timeToMaxVolumen", 60).toInt();
	endGroup();

	beginGroup("Sleep");
	isEnableSleep = value("enableSleep", true).toBool();
	timeSleep = value("timeSleep", 5).toInt();
	endGroup();
}

void Settings::writeSettings()
{
	setValue("enableAlarm", isEnableAlarm);

	beginGroup("Volume");
	setValue("volGradual", isEnableVolGrad);
	setValue("volumeInicial", volIni);
	setValue("volumeFinal", volFin);
	setValue("volumeIncrement", volInc);
	setValue("timeToMaxVolumen", timeMaxVol);
	endGroup();

	beginGroup("Sleep");
	setValue("enableSleep", isEnableSleep);
	setValue("timeSleep", timeSleep);
	endGroup();
}

bool Settings::getIsEnableAlarm()
{
	return isEnableAlarm;
}

bool Settings::getIsEnableVolGrad()
{
	return isEnableVolGrad;
}

bool Settings::getIsEnableSleep()
{
	return isEnableSleep;
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
	isEnableAlarm = value;
}

void Settings::setEnableVolGrad(bool value)
{
	isEnableVolGrad = value;
}

void Settings::setEnableSleep(bool value)
{
	isEnableSleep = value;
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

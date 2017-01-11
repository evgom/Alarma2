#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

class Settings : public QSettings
{
	Q_OBJECT
public:
	explicit Settings(QObject *parent = 0);

private:
	bool enableAlarm, enableVolGrad, enableSleep, closeToTray;
	quint8 volIni, volFin, volInc;
	quint32 timeMaxVol, timeSleep;

public:
	void readSettings();

public slots:
	bool isEnableAlarm();
	bool isCloseToTray();
	bool isEnableVolGrad();
	bool isEnableSleep();
	quint8 getVolIni();
	quint8 getVolFin();
	quint8 getVolInc();
	quint32 getTimeMaxVol();
	quint32 getTimeSleep();

	void setEnableAlarm(bool value);
	void setCloseToTray(bool value);
	void setEnableVolGrad(bool value);
	void setEnableSleep(bool value);
	void setVolIni(quint8 value);
	void setVolFin(quint8 value);
	void setVolInc(quint8 value);
	void setTimeMaxVol(quint32 value);
	void setTimeSleep(quint32 value);
	void writeSettings();
};

#endif // SETTINGS_H

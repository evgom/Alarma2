#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QtConcurrent/QtConcurrentRun>
#include <QDebug>
#include <QMediaPlayer>
#include <QTimer>
#include <options.h>
#include <alarms.h>
#include <QSettings>
#include <QMap>
#include <QMediaPlaylist>
#include <dialogsure.h>
#include <systemtray.h>
#include <settings.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	SystemTray *systemTrayIcon;


private:
	Ui::MainWindow *ui;
	QTime *timeNow, *nextAlarm;
	QMediaPlayer *sound;
	QMediaPlaylist *listSongs;
	QTimer *timerVol, *timerDisplays, *timerGetTimes, *timerSleepSong;
	QSettings settingsAlarms;
	Settings *settings;
	quint8 volume, volIni, volFin, volInc;
	quint32 timeStepVolume, timeSleep, timeMaxVol;
	bool isEnableVolGrad, isEnableSleep, isEnableAlarm;
	QString file, timeFormat;
	QUrl urlFile;
	QDateTime timeLeft;

	void calcStepVolume(const quint32 timeTotal);
	void playSong();
	void stopSong();
	void sleepSong();
	void readSettings();
	void writeSettings();
	void readAlarmsSettings();
	void timeLeftNextAlarm();
	void setTimeNow();
	void checkAlarm();

public slots:
	void toogleMainHide();
	void setEnableAlarm(bool);
	void toogleEnableAlarm();

private slots:
	void updateDisplays();
	void incVolume();
	void on_BTNduerme_clicked();
	void on_actionConfigurar_triggered();
	void on_BTNAlarms_clicked();
	void setFile(const QString file);
	void setNextAlarm(const QTime &time);
	void reloadSettings();
	void getTimes();
	void on_CHKenableAlarm_clicked(bool checked);
	void on_BTNstop_clicked();
	void on_BTNtest_clicked();
	void initVal();

signals:
	void mainHideChanged(bool);
	void enableAlarmChanged(bool);
};

#endif // MAINWINDOW_H

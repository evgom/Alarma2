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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();


private:
	Ui::MainWindow *ui;
	QTime *timeNow, *nextAlarm;
	QMediaPlayer *sound;
	QTimer *timerVol, *timerDisplays, *timerGetTimes;
	QSettings settings, settingsAlarms;
	quint8 volume, volIni, volFin, volInc;
	quint32 timeStepVolume, timeSleep, timeMaxVol;
	bool isEnableGrad, isEnableSleep, isPlaying, isEnableAlarm;
	QString file, timeFormat;
	QUrl urlFile;
	QDateTime timeLeft;

	void calcStepVolume(const quint32 timeTotal);
	void initVal();
	void playSong();
	void stopSong();
	void sleepSong();
	void readSettings();
	void readAlarmsSettings();
	void timeLeftNextAlarm();
	void setTimeNow();
	void checkAlarm();

private slots:
	void updateDisplays();
	void on_Reproduce_clicked();
	void incVolume();
	void on_BTNduerme_clicked();
	void on_actionConfigurar_triggered();
	void on_BTNAlarms_clicked();
	void setFile(const QString file);
	void setNextAlarm(const QTime &time);
	void reloadSettings();
	void getTimes();
};

#endif // MAINWINDOW_H

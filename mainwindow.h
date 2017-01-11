#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QtConcurrent/QtConcurrentRun>
#include <QDebug>
#include <QMediaPlayer>
#include <QTimer>
#include "options.h"
#include "alarmsconfigdialog.h"
#include <QMap>
#include <QMediaPlaylist>
#include "dialogsure.h"
#include "systemtray.h"
#include "settings.h"
#include <QtMath>
#include <QMessageBox>
#include <QCloseEvent>

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
	QDateTime *timeNow;
	Alarm *nextAlarm;
	QMediaPlayer *sound;
	QMediaPlaylist *listSongs;
	QTimer *timerVol, *timerDisplays, *timerGetTimes, *timerSleepSong;
	quint8 volume, volIni, volFin, volInc;
	quint32 timeStepVolume, timeSleep, timeMaxVol;
	bool enableVolGrad, enableSleep, enableAlarm, alarmActive;
	QString timeFormat;
	QDateTime timeLeft;
	bool closeToTray;
	Options *op;
	AlarmsConfigDialog *al;
	DialogSure *sure;

	void calcStepVolume(const quint32 timeTotal);
	void playSong();
	void stopSong();
	void sleepSong();
	void writeSettings();
	void timeLeftNextAlarm();
	void setTimeNow();
	void checkAlarm();
	void startAlarm();
	void stopAlarm();
	void calcDateNextAlarm();

public slots:
	void toogleMainHide();
	void setEnableAlarm(bool);
	void toogleEnableAlarm();
	void closeApp();

protected:
	void closeEvent(QCloseEvent *event);

private slots:
	void updateDisplays();
	void incVolume();
	void on_actionConfigurar_triggered();
	void on_BTNAlarms_clicked();
	void setFile(const QString file);
	void setNextAlarm(const Alarm &newAlarm);
	void calcTimes();
	void on_CHKenableAlarm_clicked(bool checked);
	void on_BTNstop_clicked();
	void on_BTNtest_clicked();
	void initVal();
	void readSettings();
	void readAlarmsSettings();
	void on_BTNsleep_clicked();

	void on_actionAcerca_de_Qt_triggered();

	void on_actionAcerca_de_triggered();

	void on_actionSalir_triggered();

signals:
	void mainHideChanged(bool);
	void enableAlarmChanged(bool);
	void alarmStartedStoped(bool);
};

#endif // MAINWINDOW_H

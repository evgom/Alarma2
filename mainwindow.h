#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QtConcurrent/QtConcurrentRun>
#include <QDebug>
#include <QMediaPlayer>
#include <QTimer>
#include <unistd.h>
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
	QTime *horaActual, *nextAlarm;
	QMediaPlayer *sound;
	QTimer *timerVol, *timerDisplay;
	QSettings settings;
	quint8 volume, volIni, volFin, volInc;
	quint32 timeStepVolume, timeSleep, timeMaxVol;
	bool isEnableGrad, isEnableSleep, isPlaying;
	QString file;
	QUrl urlFile;

	void calcStepVolume(const quint32 timeTotal);
	void initVal();
	void sleepSongThread();
	void readSettings();
	void playSong();
	void stopSong();

private slots:
	void actualizaDisplay(const QTime &hora);
	void on_Reproduce_clicked();
	void incVolume();
	void getHora();
	void on_BTNduerme_clicked();
	void on_actionConfigurar_triggered();
	void on_BTNAlarms_clicked();
	void setFile(const QString file);
	void setNextAlarm(const QTime &time);
	void reloadSettings();

signals:
	void enviaHora(const QTime &hora);
};

#endif // MAINWINDOW_H

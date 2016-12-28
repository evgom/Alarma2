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
	QTime *horaActual;
	QTime *nextAlarm;
	QMediaPlayer *sound;
	QTimer *timerVol;
	QTimer *timerDisplay;
	qint8 volume;
	qint8 volIni;
	qint8 volFin;
	qint8 incVol;
	qint32 timeStepVolume;
	qint32 timeSleep;
	QString file;
	QUrl urlFile;
	bool isGrad, isSleep;

	void calcStepVolume(const qint32 timeTotal);
	void initVal();
	void sleepSongThread();

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
	/* void setSleep(const qint32 timeSleep);
	void setIncVol(const qint8 incVol);
	void setVolIni(const qint8 volIni);
	void setVolFin(const qint8 volFin);
	void setGrad(const bool grad);
	void setTimeSleep(const bool sleep);*/

signals:
	void enviaHora(const QTime &hora);
};

#endif // MAINWINDOW_H

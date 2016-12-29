#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	timeNow = new QTime();
	nextAlarm = new QTime();
	sound = new QMediaPlayer;


	// Feo
	isEnableAlarm = true;

	initVal();

	// Timers
	timerDisplays = new QTimer(this);
	connect(timerDisplays, SIGNAL(timeout()), this, SLOT(updateDisplays()));
	timerDisplays->start(500);

	timerVol = new QTimer(this);
	connect(timerVol, SIGNAL(timeout()), this, SLOT(incVolume()));

	timerGetTimes = new QTimer(this);
	connect(timerGetTimes, SIGNAL(timeout()), this, SLOT(getTimes()));
	timerGetTimes->start(100);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::initVal()
{
	readSettings();
	readAlarmsSettings();

	timeFormat = "h:mm:ss ap";
	isPlaying = false;
	calcStepVolume(timeMaxVol);
	urlFile = QUrl::fromLocalFile(file);

	sound->setMedia(urlFile);
	ui->LEsong->setText(urlFile.fileName());
	ui->LEnextAlarm->setText(nextAlarm->toString(timeFormat));
}

void MainWindow::timeLeftNextAlarm()
{
	// Calcula cuanto tiempo ha pasado
	qint32 msecs = timeNow->msecsTo(*nextAlarm);
	qint32 secsTime;

	// Si la fecha pasó hace un ajuste.
	if (timeNow->operator <(*nextAlarm))
		secsTime = msecs / 1000;
	else
		// 86400000 es el numero de segundos en el día
		secsTime = 86400000 + (msecs / 1000);

	// Es necesario para evitar el desfase del huso horario
	timeLeft = QDateTime::fromTime_t(secsTime).toUTC();
}

void MainWindow::getTimes()
{
	timeLeftNextAlarm();
	setTimeNow();
	checkAlarm();
}

void MainWindow::setTimeNow()
{
	*timeNow = QTime::currentTime();
}

void MainWindow::checkAlarm()
{
	qint32 timeDiff = qAbs(timeNow->msecsTo(*nextAlarm));
	if (isEnableAlarm && ( timeDiff < 1000 ))
		playSong();
}

void MainWindow::incVolume()
{
	if(volume < volFin){
		volume += volInc;
	}
	if (volume > volFin)
	{
		volume = volFin;
		timerVol->stop();
	}
	sound->setVolume(volume);
	qDebug() << "Volumen:" << volume << "%";
}

void MainWindow::updateDisplays()
{
	ui->LEtime->setText(timeNow->toString(timeFormat));
	ui->LEleftAlarm->setText(timeLeft.toString("h:mm:ss"));
}

void MainWindow::on_Reproduce_clicked()
{
	playSong();
}

void MainWindow::calcStepVolume(const quint32 timeTotal)
{
	quint8 numberSteps = volFin / volInc;
	timeStepVolume = timeTotal / numberSteps * 1000;
}


void MainWindow::on_BTNduerme_clicked()
{
	stopSong();

	//QtConcurrent::run(this, &MainWindow::sleepSongThread);

	// BUG en el hilo, tambien verificar si está corriendo o no.
	qDebug() << "Durmiendo por" << timeSleep << "segundos.";
	sleep(timeSleep);
	on_Reproduce_clicked();
}

void MainWindow::sleepSongThread()
{
	qDebug() << "Durmiendo por" << timeSleep << "segundos.";
	sleep(timeSleep);
	on_Reproduce_clicked();
}

void MainWindow::on_actionConfigurar_triggered()
{
	Options *op = new Options(this);
	op->show();
	//readSettings();
}

void MainWindow::on_BTNAlarms_clicked()
{
	Alarms *al = new Alarms(this);
	al->show();
}

void MainWindow::setFile(const QString file)
{
	this->file = file;
	initVal();
}

void MainWindow::setNextAlarm(const QTime &time)
{
	*nextAlarm = time;
	ui->LEnextAlarm->setText(nextAlarm->toString(timeFormat));
}

void MainWindow::reloadSettings()
{
	readSettings();
}

void MainWindow::readSettings()
{
	settings.beginGroup("Volume");
	isEnableGrad = settings.value("volGradual", true).toBool();
	volIni = settings.value("volumeInicial", 0).toInt();
	volFin = settings.value("volumeFinal", 100).toInt();
	volInc = settings.value("volumeIncrement", 5).toInt();
	timeMaxVol = settings.value("timeToMaxVolumen", 60).toInt();
	settings.endGroup();

	settings.beginGroup("Sleep");
	isEnableSleep = settings.value("enableSleep", true).toBool();
	timeSleep = settings.value("timeSleep", 5).toInt();
	settings.endGroup();
}

void MainWindow::playSong()
{
	if (!isPlaying){
		volume = volIni;
		sound->setVolume(volume);

		// Aumenta Volumen
		if (isEnableGrad)
			timerVol->start(timeStepVolume);

		sound->play();
		isPlaying = true;
		qDebug() << "Reproduciendo";
		qDebug() << "Volumen:" << volume << "%";
	}
}

void MainWindow::stopSong()
{
	sound->stop();
	timerVol->stop();
	isPlaying = false;
}

void MainWindow::readAlarmsSettings()
{
	QString date;

	// Bug, falta crear el caso cuando no hay time guardado.
	settingsAlarms.beginGroup("Alarms");
	date = settingsAlarms.value("time").toString();
	file = settingsAlarms.value("fileSong").toString();
	settingsAlarms.endGroup();

	*nextAlarm = QTime::fromString(date, "h:mm");
}

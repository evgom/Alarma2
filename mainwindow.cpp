#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	timeNow = new QTime();
	nextAlarm = new QTime();
	sound = new QMediaPlayer(this);
	systemTrayIcon = new SystemTray(this);
	settings = new Settings(this);

	// Timers
	timerDisplays = new QTimer(this);
	connect(timerDisplays, SIGNAL(timeout()), this, SLOT(updateDisplays()));
	timerDisplays->start(500);

	timerVol = new QTimer(this);
	connect(timerVol, SIGNAL(timeout()), this, SLOT(incVolume()));

	timerGetTimes = new QTimer(this);
	connect(timerGetTimes, SIGNAL(timeout()), this, SLOT(getTimes()));
	timerGetTimes->start(100);

	timerSleepSong = new QTimer(this);
	connect(timerSleepSong, SIGNAL(timeout()), this, SLOT(on_BTNtest_clicked()));

	initVal();
}

MainWindow::~MainWindow()
{
	writeSettings();
	delete ui;
}

void MainWindow::initVal()
{
	timerSleepSong->setSingleShot(true);
	timerSleepSong->stop();
	stopSong();

	readSettings();
	readAlarmsSettings();
	calcStepVolume(timeMaxVol);

	timeFormat = "h:mm:ss ap";
	urlFile = QUrl::fromLocalFile(file);

	sound->setMedia(urlFile);
	ui->LEsong->setText(urlFile.fileName());
	ui->LEnextAlarm->setText(nextAlarm->toString(timeFormat));
	ui->CHKenableAlarm->setChecked(isEnableAlarm);
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
	if (isEnableAlarm && ( timeDiff < 1000 ) && (ui->LEnextAlarm->text() != "") )
		playSong();
}

void MainWindow::isMainHidden()
{
	emit sendIsMainHidden(isHidden());
}

void MainWindow::setEnableAlarm(bool state)
{
	isEnableAlarm = state;
	ui->CHKenableAlarm->setChecked(state);
}

bool MainWindow::getEnableAlarm()
{
	emit sendIsEnableAlarm(isEnableAlarm);
	return isEnableAlarm;
}

void MainWindow::incVolume()
{
	if(volume < volFin){
		volume += volInc;
	}
	if (volume >= volFin)
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

	if (isEnableAlarm)
		ui->LEleftAlarm->setText(timeLeft.toString("h:mm:ss"));
	else
		ui->LEleftAlarm->setText("");
}

void MainWindow::calcStepVolume(const quint32 timeTotal)
{
	quint8 numberSteps = volFin / volInc;
	timeStepVolume = timeTotal / numberSteps * 1000;
}


void MainWindow::on_BTNduerme_clicked()
{
	sleepSong();
}

void MainWindow::on_actionConfigurar_triggered()
{
	Options *op = new Options(this);
	op->show();
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
	calcStepVolume(timeMaxVol);
}

void MainWindow::readSettings()
{
	isEnableAlarm = settings->getIsEnableAlarm();
	isEnableVolGrad = settings->getIsEnableVolGrad();
	volIni = settings->getVolIni();
	volFin = settings->getVolFin();
	volInc = settings->getVolInc();
	timeMaxVol = settings->getTimeMaxVol();
	isEnableSleep = settings->getIsEnableSleep();
	timeSleep = settings->getTimeSleep();
}

void MainWindow::writeSettings()
{
	settings->setEnableAlarm(isEnableAlarm);
	settings->writeSettings();
}

void MainWindow::playSong()
{
	if ( sound->mediaStatus() == QMediaPlayer::LoadedMedia ){
		volume = volIni;
		sound->setVolume(volume);

		// Aumenta Volumen si está activado el volumen gradual.
		if (isEnableVolGrad)
			timerVol->start(timeStepVolume);

		sound->play();
		qDebug() << "Reproduciendo";
		qDebug() << "Volumen:" << volume << "%";
	}
}

void MainWindow::stopSong()
{
	sound->stop();
	timerVol->stop();
	qDebug() << "Deteniendo.";
}

void MainWindow::sleepSong()
{
	if (sound->state() == QMediaPlayer::PlayingState){
		stopSong();
		qDebug() << "Durmiendo por" << timeSleep << "segundos.";
		timerSleepSong->start(timeSleep * 1000);
	}
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

void MainWindow::on_CHKenableAlarm_clicked(bool checked)
{
	isEnableAlarm = checked;
}

void MainWindow::on_BTNstop_clicked()
{
	if(sound->state() == QMediaPlayer::PlayingState)
	{
		DialogSure *sure = new DialogSure(this);
		sure->setWindowTitle("¿Detener Alarma?");
		sure->show();
	}
}

void MainWindow::on_BTNtest_clicked()
{
	playSong();
}

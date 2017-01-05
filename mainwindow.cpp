#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	timeFormat = "h:mm:ss ap";

	timeNow = new QTime();
	nextAlarm = new QTime();
	sound = new QMediaPlayer(this);
	listSongs = new QMediaPlaylist(this);
	systemTrayIcon = new SystemTray(this);

	// Timers
	timerDisplays = new QTimer(this);
	connect(timerDisplays, SIGNAL(timeout()), this, SLOT(updateDisplays()));
	timerDisplays->start(500);

	timerVol = new QTimer(this);
	connect(timerVol, SIGNAL(timeout()), this, SLOT(incVolume()));

	timerGetTimes = new QTimer(this);
	connect(timerGetTimes, SIGNAL(timeout()), this, SLOT(calcTimes()));
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
	stopAlarm();

	readSettings();
	readAlarmsSettings();
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

void MainWindow::calcTimes()
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
	if (enableAlarm && ( timeDiff < 1000 ) && (ui->LEnextAlarm->text() != "") )
		startAlarm();
}

void MainWindow::startAlarm()
{
	alarmActive = true;
	playSong();
}

void MainWindow::stopAlarm()
{
	alarmActive = false;
	stopSong();
}

void MainWindow::toogleMainHide()
{
	setHidden(!isHidden());
	if (isHidden())
		qDebug() << "Main screen hidden";
	else
		qDebug() << "Main screen showed";
	emit mainHideChanged(isHidden());
}

void MainWindow::setEnableAlarm(bool state)
{
	if(state != enableAlarm) {
		enableAlarm = state;
		ui->CHKenableAlarm->setChecked(state);
		qDebug() << "Alarma:" << state;
		emit enableAlarmChanged (enableAlarm);
	}
}

void MainWindow::toogleEnableAlarm()
{
	setEnableAlarm(!enableAlarm);
}

void MainWindow::incVolume()
{
	if(volume < volFin) {
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

	if (enableAlarm)
		ui->LEleftAlarm->setText(timeLeft.toString("h:mm:ss"));
	else
		ui->LEleftAlarm->setText("");
}

void MainWindow::calcStepVolume(const quint32 timeTotal)
{
	quint8 numberSteps = qCeil(1.0 * (volFin - volIni) / volInc);
	timeStepVolume = 1000 * timeTotal / numberSteps;
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
	AlarmsConfigDialog *al = new AlarmsConfigDialog(this);
	al->show();
}

void MainWindow::setFile(const QString file)
{
	QFileInfo checkFile(file);
	QUrl urlFile;

	if (checkFile.exists() && checkFile.isFile())
		urlFile = QUrl::fromLocalFile(file);

	listSongs->setPlaybackMode(QMediaPlaylist::Loop);
	listSongs->clear();
	listSongs->addMedia(urlFile);

	sound->setPlaylist(listSongs);
	ui->LEsong->setText(urlFile.fileName());
}

void MainWindow::setNextAlarm(const QTime &time)
{
	// Posible leak de memoria
	*nextAlarm = time;
	ui->LEnextAlarm->setText(nextAlarm->toString(timeFormat));
}

void MainWindow::readSettings()
{
	settings = new Settings(this);

	setEnableAlarm(settings->isEnableAlarm());
	enableVolGrad = settings->isEnableVolGrad();
	volIni = settings->getVolIni();
	volFin = settings->getVolFin();
	volInc = settings->getVolInc();
	timeMaxVol = settings->getTimeMaxVol();
	enableSleep = settings->isEnableSleep();
	timeSleep = settings->getTimeSleep();

	delete settings;

	calcStepVolume(timeMaxVol);
}

void MainWindow::writeSettings()
{
	settings = new Settings(this);

	settings->setEnableAlarm(enableAlarm);
	settings->writeSettings();

	delete settings;
}

void MainWindow::playSong()
{
	if (sound->mediaStatus() == QMediaPlayer::LoadedMedia) {
		volume = volIni;
		sound->setVolume(volume);

		// Aumenta Volumen si está activado el volumen gradual.
		if (enableVolGrad)
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
	if (sound->state() == QMediaPlayer::PlayingState) {
		stopSong();
		qDebug() << "Durmiendo por" << timeSleep << "segundos.";
		timerSleepSong->start(timeSleep * 1000);
	}
}

void MainWindow::readAlarmsSettings()
{
	AlarmSettings settingsAlarms(this);
	Alarm *next = settingsAlarms.getAlarm();

	setNextAlarm(next->getTime());
	setFile(next->getFile());
}

void MainWindow::on_CHKenableAlarm_clicked(bool checked)
{
	setEnableAlarm(checked);
}

void MainWindow::on_BTNstop_clicked()
{
	if( alarmActive || (sound->state() == QMediaPlayer::PlayingState) )
	{
		DialogSure *sure = new DialogSure(this);
		sure->setWindowTitle("¿Detener Alarma?");
		sure->show();
	}
}

void MainWindow::on_BTNtest_clicked()
{
	startAlarm();
}

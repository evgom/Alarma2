#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	// Ensure working directory is home
	QDir::setCurrent(QDir::homePath());

	ui->setupUi(this);
	timeFormat = "h:mm:ss ap";

	timeNow = new QDateTime();
	nextAlarm = new Alarm(this);
	sound = new QMediaPlayer(this);
	listSongs = new QMediaPlaylist(this);
	systemTrayIcon = new SystemTray(this);
	op = new Options(this);
	al = new AlarmsConfigDialog(this);
	sure = new DialogSure(this);

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
	connect(timerSleepSong, SIGNAL(timeout()), this, SLOT(startAlarm()));

	initVal();
}

MainWindow::~MainWindow()
{
	writeSettings();
	delete ui;
}

void MainWindow::initVal()
{
	// Config
	timerSleepSong->setSingleShot(true);
	sound->setAudioRole(QAudio::AlarmRole);

	// Tal vez se necesite un método para desactivar el loop si únicamente
	// hay archivos fallidos.
	listSongs->setPlaybackMode(QMediaPlaylist::Loop);

	stopAlarm();

	readSettings();
	readAlarmsSettings();
}

void MainWindow::timeLeftNextAlarm()
{
	// Calcula cuanto tiempo ha pasado
	qint64 secsTime = timeNow->secsTo(nextAlarm->getDateTime());

	// Si la fecha pasó hace un ajuste.
	if (*timeNow > nextAlarm->getDateTime())
		// 86400000 es el numero de segundos en el día
		secsTime += 86400000;

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
	*timeNow = QDateTime::currentDateTime();
}

void MainWindow::checkAlarm()
{
	qint64 timeDiff = qAbs(timeNow->msecsTo(nextAlarm->getDateTime()));
	if (enableAlarm && ( timeDiff < 1000 ) && (ui->LEnextAlarm->text() != "") )
		startAlarm();
}

void MainWindow::startAlarm()
{
	if (sound->state() == QMediaPlayer::StoppedState)
		emit alarmStartedStoped(true);

	alarmActive = true;
	playSong();
}

void MainWindow::stopAlarm()
{
	if (sound->state() == QMediaPlayer::PlayingState)
		emit alarmStartedStoped(false);

	timerSleepSong->stop();
	alarmActive = false;
	stopSong();
}

void MainWindow::calcDateNextAlarm()
{
	QDate dateAlarm(QDate::currentDate());
	QDate today(QDate::currentDate());
	qint8 daysToAdd;

	QSet<int8_t> days;
	days = nextAlarm->getDays();

	QList<int8_t> daysList(days.toList());
	// Ordena la lista para que los días vayan de manera ascendente.
	std::sort(daysList.begin(), daysList.end());
	QListIterator<int8_t> i(daysList);

	// Cálcula el número de días para la siguiente alarma
	while(true) {
		// Si alarma es el día de hoy, pero ya pasó se calcula para la siguiente.
		if ( (today.dayOfWeek() == i.peekNext()) && (nextAlarm->getTime() < QTime::currentTime()) )
		{
			// Avanza una posición si la lista es mayor a uno.
			if (daysList.count() > 1)
				i.next();
		}
		daysToAdd = i.next() - today.dayOfWeek();

		if (daysToAdd >= 0)
			break;

		// Si la fecha es la siguiente semana, hace un ajuste.
		if (!i.hasNext()) {
			daysToAdd = daysList.at(0) - today.dayOfWeek() + 7;
			break;
		}
	}

	dateAlarm = dateAlarm.addDays(daysToAdd);
	nextAlarm->setDate(dateAlarm);
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
		if (state)
			qDebug() << "Alarma enabled";
		else
			qDebug() << "Alarma disabled";

		emit enableAlarmChanged (enableAlarm);
	}
}

void MainWindow::toogleEnableAlarm()
{
	setEnableAlarm(!enableAlarm);
}

void MainWindow::closeApp()
{
	qApp->quit();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	if (closeToTray)
		toogleMainHide();
	else
		closeApp();
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

	if (enableAlarm) {
		QString stringTimeLeft = "";
		qint64 daysLeft = timeNow->daysTo(nextAlarm->getDateTime());

		if (nextAlarm->getTime() < timeNow->time())
			daysLeft--;

		if (daysLeft != 0)
			stringTimeLeft = QString::number(daysLeft) + " días ";
		if (daysLeft == -1)
			stringTimeLeft = QString::number(6) + " días ";


		stringTimeLeft += timeLeft.toString("h:mm:ss");
		ui->LEleftAlarm->setText(stringTimeLeft);
	}
	else
		ui->LEleftAlarm->setText("");
}

void MainWindow::calcStepVolume(const quint32 timeTotal)
{
	quint8 numberSteps = qCeil(1.0 * (volFin - volIni) / volInc);
	timeStepVolume = 1000 * timeTotal / numberSteps;
}

void MainWindow::on_actionConfigurar_triggered()
{
	op->show();
}

void MainWindow::on_BTNAlarms_clicked()
{
	al->show();
}

void MainWindow::setFile(const QString file)
{
	QFileInfo checkFile(file);

	if (checkFile.exists() && checkFile.isFile()){
		urlFile = QUrl::fromLocalFile(file);


		listSongs->clear();
		listSongs->addMedia(urlFile);

		sound->setPlaylist(listSongs);
		// Para que no use el recurso de audio, hasta que se necesite.
		listSongs->setCurrentIndex(-1);
	}
	ui->LEsong->setText(urlFile.fileName());
}

void MainWindow::setNextAlarm(const Alarm &newAlarm)
{
	*nextAlarm = newAlarm;
	// Calcular la fecha para la siguiente alarma con respecto a los días dados
	calcDateNextAlarm();

	ui->LEnextAlarm->setText(nextAlarm->getTime().toString(timeFormat));
	ui->LEday->setText(QDate::longDayName(nextAlarm->getDate().dayOfWeek()));
}

void MainWindow::readSettings()
{
	Settings settings(this);

	setEnableAlarm(settings.isEnableAlarm());
	enableVolGrad = settings.isEnableVolGrad();
	closeToTray = settings.isCloseToTray();
	volIni = settings.getVolIni();
	volFin = settings.getVolFin();
	volInc = settings.getVolInc();
	timeMaxVol = settings.getTimeMaxVol();
	enableSleep = settings.isEnableSleep();
	timeSleep = settings.getTimeSleep();

	calcStepVolume(timeMaxVol);
}

void MainWindow::writeSettings()
{
	Settings settings(this);

	settings.setEnableAlarm(enableAlarm);
	settings.writeSettings();
}

void MainWindow::playSong()
{
	if (sound->state() != QMediaPlayer::PlayingState) {
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

	// Index inexistente para que se libere el recurso de audio.
	listSongs->setCurrentIndex(-1);
	timerVol->stop();
	qDebug() << "Deteniendo.";
}

void MainWindow::sleepSong()
{
	if (sound->state() == QMediaPlayer::PlayingState && enableSleep) {
		stopSong();
		qDebug() << "Durmiendo por" << timeSleep << "segundos.";
		timerSleepSong->start(timeSleep * 1000);
	}
}

void MainWindow::readAlarmsSettings()
{
	AlarmSettings settingsAlarms(this);
	setNextAlarm(*settingsAlarms.getAlarm());

	setFile(nextAlarm->getFile());
}

void MainWindow::on_CHKenableAlarm_clicked(bool checked)
{
	setEnableAlarm(checked);
}

void MainWindow::on_BTNstop_clicked()
{
	if( alarmActive || (sound->state() == QMediaPlayer::PlayingState) )
	{
		sure->setWindowTitle("¿Detener Alarma?");
		sure->show();
	}
}

void MainWindow::on_BTNtest_clicked()
{
	startAlarm();
}

void MainWindow::on_BTNsleep_clicked()
{
	sleepSong();
}

void MainWindow::on_actionAcerca_de_Qt_triggered()
{
	QMessageBox::aboutQt(this, "Acerca de Qt");
}

void MainWindow::on_actionAcerca_de_triggered()
{
	QMessageBox::about(this, "Acerca de", "Texto");
}

void MainWindow::on_actionSalir_triggered()
{
	closeApp();
}

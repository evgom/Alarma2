#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	horaActual = new QTime();
	sound = new QMediaPlayer;
	nextAlarm = new QTime();



	file = "/home/erick/Qt/Alarma2/1.mp3";


	initVal();

	// Timers
	timerDisplay = new QTimer(this);
	connect(timerDisplay, SIGNAL(timeout()), this, SLOT(getHora()));
	timerDisplay->start(500);

	timerVol = new QTimer(this);
	connect(timerVol, SIGNAL(timeout()), this, SLOT(incVolume()));

	// Connects
	connect(this, &MainWindow::enviaHora, this, &MainWindow::actualizaDisplay);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::initVal()
{
	volume = 0;
	incVol = 5;
	timeSleep = 10;
	sound->setVolume(volume);
	calcStepVolume(60);
	urlFile = QUrl::fromLocalFile(file);

	sound->setMedia(urlFile);
	ui->LEsong->setText(urlFile.fileName());
}

void MainWindow::getHora()
{
	*horaActual = QTime::currentTime();
	emit enviaHora(*horaActual);
}

void MainWindow::incVolume()
{
	if(volume < 100){
		volume += incVol;
		sound->setVolume(volume);
		qDebug() << "Volumen:" << volume << "%";
	}
}

void MainWindow::actualizaDisplay(const QTime &hora)
{
	ui->LEtime->setText(hora.toString("h:mm:ss ap"));
}

void MainWindow::on_Reproduce_clicked()
{
	// Aumenta Volumen
	timerVol->start(timeStepVolume);

	sound->play();
	qDebug() << "Reproduciendo";
}

void MainWindow::calcStepVolume(const qint32 timeTotal)
{
	qint8 numberSteps = 100 / incVol;
	timeStepVolume = timeTotal / numberSteps * 1000;
}


void MainWindow::on_BTNduerme_clicked()
{
	// añadir método para stopSong
	sound->stop();
	volume = 0;
	timerVol->stop();
	sound->setVolume(volume);
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
	ui->LEnextAlarm->setText(nextAlarm->toString("h:mm ap"));
}

#include "alarms.h"
#include "ui_alarms.h"

Alarms::Alarms(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Alarms)
{
	ui->setupUi(this);
	alarm = new QTime();
	initVal();

	connect(this, SIGNAL(newFile(QString)), parent, SLOT(setFile(QString)));
	connect(this, SIGNAL(newAlarm(QTime)), parent, SLOT(setNextAlarm(const QTime)));
}

Alarms::~Alarms()
{
	delete ui;
}

void Alarms::on_toolButton_clicked()
{
	// Buscar mejores extensiones
	file = QFileDialog::getOpenFileName(this, "Seleccionar Canción", "~/",
										"Archivos mp3(*.mp3);;Archivos m4a(*.m4a);;Todos(*.*)");

	// crear validación mejor para archivo.
	if(!file.isEmpty())
		ui->LEfile->setText(file);
}

void Alarms::on_buttonBox_accepted()
{
	*alarm = ui->TEalarm->time();
	// para que funcione el arrastrar hay que quitar file:/// del resultado
	file = ui->LEfile->text();
	writeAlarmsSettings();

	emit newFile(file);
	emit newAlarm(*alarm);
}

void Alarms::initVal()
{
	readAlarmsSettings();
	ui->TEalarm->setTime(*alarm);
	ui->LEfile->setText(file);
}

void Alarms::readAlarmsSettings()
{
	QString date;

	// Bug, falta crear el caso cuando no hay time guardado.
	settingsAlarms.beginGroup("Alarms");
	date = settingsAlarms.value("time").toString();
	file = settingsAlarms.value("fileSong").toString();
	settingsAlarms.endGroup();

	*alarm = QTime::fromString(date, "h:mm");
}

void Alarms::writeAlarmsSettings()
{
	settingsAlarms.beginGroup("Alarms");
	settingsAlarms.setValue("time", alarm->toString("h:mm"));
	settingsAlarms.setValue("fileSong", file);
	settingsAlarms.endGroup();
}

#include "alarmsconfigdialog.h"
#include "ui_alarmsconfigdialog.h"

AlarmsConfigDialog::AlarmsConfigDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AlarmsConfigDialog)
{
	ui->setupUi(this);

	alarm = new QTime();
	initVal();

	connect(this, SIGNAL(newFile(QString)), parent, SLOT(setFile(QString)));
	connect(this, SIGNAL(newAlarm(QTime)), parent, SLOT(setNextAlarm(const QTime)));
}

AlarmsConfigDialog::~AlarmsConfigDialog()
{
	delete ui;
}

void AlarmsConfigDialog::on_BBalarmsConfigDialog_accepted()
{
	*alarm = ui->TEalarm->time();
	// para que funcione el arrastrar hay que quitar file:/// del resultado
	file = ui->LEfile->text();
	writeAlarmsSettings();

	emit newFile(file);
	emit newAlarm(*alarm);
}

void AlarmsConfigDialog::on_TBfile_clicked()
{
	// Buscar mejores extensiones
	file = QFileDialog::getOpenFileName(this, "Seleccionar Canción", "~/",
										"Archivos mp3(*.mp3);;Archivos m4a(*.m4a);;Todos(*.*)");

	// crear validación mejor para archivo.
	if(!file.isEmpty())
		ui->LEfile->setText(file);
}

void AlarmsConfigDialog::initVal()
{
	readAlarmsSettings();
	ui->TEalarm->setTime(*alarm);
	ui->LEfile->setText(file);
}

void AlarmsConfigDialog::readAlarmsSettings()
{
	QString date;

	// Bug, falta crear el caso cuando no hay time guardado.
	settingsAlarms.beginGroup("Alarms");
	date = settingsAlarms.value("time").toString();
	file = settingsAlarms.value("fileSong").toString();
	settingsAlarms.endGroup();

	*alarm = QTime::fromString(date, "h:mm");
}

void AlarmsConfigDialog::writeAlarmsSettings()
{
	settingsAlarms.beginGroup("Alarms");
	settingsAlarms.setValue("time", alarm->toString("h:mm"));
	settingsAlarms.setValue("fileSong", file);
	settingsAlarms.endGroup();
}

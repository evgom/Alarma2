#include "alarmsconfigdialog.h"
#include "ui_alarmsconfigdialog.h"

AlarmsConfigDialog::AlarmsConfigDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AlarmsConfigDialog)
{
	ui->setupUi(this);

	settingsAlarms = new AlarmSettings(this);

	initVal();

	connect(this, SIGNAL(alarmUpdated()), parent, SLOT(readAlarmsSettings()));
}

AlarmsConfigDialog::~AlarmsConfigDialog()
{
	delete ui;
}

void AlarmsConfigDialog::on_BBalarmsConfigDialog_accepted()
{
	alarm->setTime(ui->TEalarm->time());
	// para que funcione el arrastrar hay que quitar file:/// del resultado
	alarm->setFile(ui->LEfile->text());
	writeAlarmsSettings();

	emit alarmUpdated();
}

void AlarmsConfigDialog::on_TBfile_clicked()
{
	// Buscar mejores extensiones
	QString file;
	file = QFileDialog::getOpenFileName(this, "Seleccionar Canción", "~/",
										"Archivos mp3(*.mp3);;Archivos m4a(*.m4a);;Todos(*.*)");

	// crear validación mejor para archivo.
	if(!file.isEmpty())
	{
		alarm->setFile(file);
		ui->LEfile->setText(file);
	}
}

void AlarmsConfigDialog::initVal()
{
	readAlarmsSettings();
	ui->TEalarm->setTime(alarm->getTime());
	ui->LEfile->setText(alarm->getFile());
}

void AlarmsConfigDialog::readAlarmsSettings()
{
	alarm = settingsAlarms->getAlarm();
}

void AlarmsConfigDialog::writeAlarmsSettings()
{
	settingsAlarms->writeAlarmSettings();
}

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
	CHKDaysToAlarm();


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

	// set widgets values
	ui->TEalarm->setTime(alarm->getTime());
	ui->LEfile->setText(alarm->getFile());
	setCHKDays();
}

void AlarmsConfigDialog::readAlarmsSettings()
{
	alarm = settingsAlarms->getAlarm();
}

void AlarmsConfigDialog::writeAlarmsSettings()
{
	settingsAlarms->writeAlarmSettings();
}

void AlarmsConfigDialog::setCHKDays()
{
	QSet<int8_t> days = alarm->getDays();

	if (days.contains(Alarm::Monday))
		ui->CHKmonday->setChecked(true);
	if (days.contains(Alarm::Tuesday))
		ui->CHKtuesday->setChecked(true);
	if (days.contains(Alarm::Wednesday))
		ui->CHKwednesday->setChecked(true);
	if (days.contains(Alarm::Thursday))
		ui->CHKthursday->setChecked(true);
	if (days.contains(Alarm::Friday))
		ui->CHKfriday->setChecked(true);
	if (days.contains(Alarm::Saturday))
		ui->CHKsaturday->setChecked(true);
	if (days.contains(Alarm::Sunday))
		ui->CHKsunday->setChecked(true);
}

void AlarmsConfigDialog::CHKDaysToAlarm()
{
	QSet<int8_t> days;

	if (ui->CHKmonday->isChecked())
		days.insert(Alarm::Monday);
	if (ui->CHKtuesday->isChecked())
		days.insert(Alarm::Tuesday);
	if (ui->CHKwednesday->isChecked())
		days.insert(Alarm::Wednesday);
	if (ui->CHKthursday->isChecked())
		days.insert(Alarm::Thursday);
	if (ui->CHKfriday->isChecked())
		days.insert(Alarm::Friday);
	if (ui->CHKsaturday->isChecked())
		days.insert(Alarm::Saturday);
	if (ui->CHKsunday->isChecked())
		days.insert(Alarm::Sunday);

	alarm->setDays(days);
}

#include "options.h"
#include "ui_options.h"

Options::Options(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Options)
{
	ui->setupUi(this);

	settings = new Settings(this);

	readSettings();
	iniValues();

	connect(this, SIGNAL(settingsUpdated()), parent, SLOT(readSettings()));
}

Options::~Options()
{
	delete ui;
}

void Options::iniValues()
{
	QStringList list;

	for(int i = 0; i <= 100; i+=5)
		list.append(QString::number(i));

	ui->CBvolIni->addItems(list);
	ui->CBvolFin->addItems(list);
	ui->CBtimeSleep->addItems(list);
	ui->CBtimeMaxVol->addItems(list);
	ui->CBvolInc->addItems({"5", "10", "15", "20"});

	// Set wdigets settings
	ui->CBvolIni->setCurrentText(QString::number(volIni));
	ui->CBvolFin->setCurrentText(QString::number(volFin));
	ui->CBvolInc->setCurrentText(QString::number(volInc));
	ui->CBtimeMaxVol->setCurrentText(QString::number(timeMaxVol));
	ui->CBtimeSleep->setCurrentText(QString::number(timeSleep));
	ui->CHKSleep->setChecked(enableSleep);
	ui->CHKvolGradual->setChecked(enableVolGrad);

	Options::on_CHKSleep_toggled(enableSleep);
	Options::on_CHKvolGradual_toggled(enableVolGrad);
}

void Options::readSettings()
{
	enableVolGrad = settings->isEnableVolGrad();
	volIni = settings->getVolIni();
	volFin = settings->getVolFin();
	volInc = settings->getVolInc();
	timeMaxVol = settings->getTimeMaxVol();
	enableSleep = settings->isEnableSleep();
	timeSleep = settings->getTimeSleep();
}

void Options::writeSettings()
{
	settings->setEnableVolGrad(enableVolGrad);
	settings->setVolIni(volIni);
	settings->setVolFin(volFin);
	settings->setVolInc(volInc);
	settings->setTimeMaxVol(timeMaxVol);
	settings->setEnableSleep(enableSleep);
	settings->setTimeSleep(timeSleep);

	settings->writeSettings();
}

void Options::readValuesUI()
{
	enableVolGrad = ui->CHKvolGradual->isChecked();
	volIni = ui->CBvolIni->currentText().toInt();
	volFin = ui->CBvolFin->currentText().toInt();
	volInc = ui->CBvolInc->currentText().toInt();
	timeMaxVol = ui->CBtimeMaxVol->currentText().toInt();
	enableSleep = ui->CHKSleep->isChecked();
	timeSleep = ui->CBtimeSleep->currentText().toInt();
}

void Options::on_CHKSleep_toggled(bool checked)
{
	ui->CBtimeSleep->setEnabled(checked);
}

void Options::on_CHKvolGradual_toggled(bool checked)
{
	ui->CBvolFin->setEnabled(checked);
	ui->CBvolInc->setEnabled(checked);
	ui->CBtimeMaxVol->setEnabled(checked);
}

void Options::on_buttonBox_accepted()
{
	readValuesUI();
	writeSettings();
	emit settingsUpdated();
}


// Implementar bien esta parte. Parece que QValidator es una buena opción
void Options::on_CBvolIni_currentTextChanged(const QString &arg1)
{
	QRegExp digit("\\d+");

	if (!digit.exactMatch(arg1))
		ui->label->setToolTip("Sólo numeros");
}

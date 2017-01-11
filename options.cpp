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
	valiVol= new QIntValidator(0, 100, this);
	valiVolInc = new QIntValidator(1, 100, this);

	QStringList list;
	for(int i = 0; i <= 100; i+=5)
		list.append(QString::number(i));

	ui->CBvolIni->addItems(list);
	ui->CBvolFin->addItems(list);
	ui->CBvolInc->addItems({"5", "10", "15", "20"});

	// Set widgets values
	ui->CBvolIni->setCurrentText(QString::number(volIni));
	ui->CBvolFin->setCurrentText(QString::number(volFin));
	ui->CBvolInc->setCurrentText(QString::number(volInc));
	ui->TEtimeMaxVol->setTime(secsToTime(timeMaxVol));
	ui->TEtimeSleep->setTime(secsToTime(timeSleep));
	ui->CHKSleep->setChecked(enableSleep);
	ui->CHKvolGradual->setChecked(enableVolGrad);
	ui->CHKcloseToTray->setChecked(closeToTray);

	// Set widgets settings
	ui->TEtimeMaxVol->setAccelerated(true);
	ui->TEtimeMaxVol->setDisplayFormat(formatTimer);
	ui->TEtimeMaxVol->setToolTip("Minutos:Segundos");
	ui->TEtimeSleep->setAccelerated(true);
	ui->TEtimeSleep->setDisplayFormat(formatTimer);
	ui->TEtimeSleep->setToolTip("Minutos:Segundos");


	// Validators, only for range
	ui->CBvolIni->setValidator(valiVol);
	ui->CBvolFin->setValidator(valiVol);
	ui->CBvolInc->setValidator(valiVolInc);

	Options::on_CHKSleep_toggled(enableSleep);
	Options::on_CHKvolGradual_toggled(enableVolGrad);
}

void Options::readSettings()
{
	enableVolGrad = settings->isEnableVolGrad();
	closeToTray = settings->isCloseToTray();
	volIni = settings->getVolIni();
	volFin = settings->getVolFin();
	volInc = settings->getVolInc();
	timeMaxVol = settings->getTimeMaxVol();
	enableSleep = settings->isEnableSleep();
	timeSleep = settings->getTimeSleep();
}

void Options::writeSettings()
{
	settings->setEnableVolGrad(newEnableSleep);
	settings->setCloseToTray(newCloseToTray);
	settings->setVolIni(newVolIni);
	settings->setVolFin(newVolFin);
	settings->setVolInc(newVolInc);
	settings->setTimeMaxVol(newTimeMaxVol);
	settings->setEnableSleep(newEnableSleep);
	settings->setTimeSleep(newTimeSleep);

	settings->writeSettings();
}

void Options::readValuesUI()
{
	newEnableSleep = ui->CHKvolGradual->isChecked();
	newCloseToTray = ui->CHKcloseToTray->isChecked();
	newVolIni = ui->CBvolIni->currentText().toInt();
	newVolFin = ui->CBvolFin->currentText().toInt();
	newVolInc = ui->CBvolInc->currentText().toInt();
	newTimeMaxVol = timeToSecs(ui->TEtimeMaxVol->time());
	newEnableSleep = ui->CHKSleep->isChecked();
	newTimeSleep = timeToSecs(ui->TEtimeSleep->time());
}

qint32 Options::timeToSecs(const QTime &time)
{
	return QTime(0, 0).secsTo(time);
}

QTime Options::secsToTime(const qint32 time)
{
	return QTime(0, 0).addSecs(time);
}

void Options::checkConfig()
{
	readValuesUI();

	int pos = 0;
	QString newVolIniS = QString::number(newVolIni);
	QString newVolFinS = QString::number(newVolFin);
	QString newVolIncS = QString::number(newVolInc);

	calcValidates();

	ui->buttonBox->buttons().at(0)->setEnabled(true);
	ui->CBvolIni->setStyleSheet("");
	ui->CBvolFin->setStyleSheet("");
	ui->CBvolInc->setStyleSheet("");

	QString redStyle = "background-color: #da4453";

	if( !(vVolIni->validate(newVolIniS, pos) == QValidator::Acceptable) ) {
		ui->CBvolIni->setStyleSheet(redStyle);
		ui->buttonBox->buttons().at(0)->setEnabled(false);
	}
	if( !(vVolFin->validate(newVolFinS, pos) == QValidator::Acceptable) ) {
		ui->CBvolFin->setStyleSheet(redStyle);
		ui->buttonBox->buttons().at(0)->setEnabled(false);
	}
	if( !(valiVolInc->validate(newVolIncS, pos) == QValidator::Acceptable) ) {
		ui->CBvolInc->setStyleSheet(redStyle);
		ui->buttonBox->buttons().at(0)->setEnabled(false);
	}
}

// Real Validators
void Options::calcValidates()
{
	vVolIni = new QIntValidator(0, newVolFin - 1);
	vVolFin = new QIntValidator(newVolIni + 1, 100);
}

void Options::on_CHKSleep_toggled(bool checked)
{
	ui->TEtimeSleep->setEnabled(checked);
}

void Options::on_CHKvolGradual_toggled(bool checked)
{
	ui->CBvolFin->setEnabled(checked);
	ui->CBvolInc->setEnabled(checked);
	ui->TEtimeMaxVol->setEnabled(checked);
}

void Options::on_CBvolIni_editTextChanged(const QString &arg1)
{
	checkConfig();
}

void Options::on_CBvolFin_editTextChanged(const QString &arg1)
{
	checkConfig();
}

void Options::on_CBvolInc_editTextChanged(const QString &arg1)
{
	checkConfig();
}

void Options::on_buttonBox_accepted()
{
	checkConfig();

	writeSettings();
	emit settingsUpdated();

	/*this->close();
	deleteLater();
	emit accepted();*/
}

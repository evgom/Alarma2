#include "options.h"
#include "ui_options.h"

Options::Options(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Options)
{
	ui->setupUi(this);

	readSettings();
	iniValues();

	connect(this, SIGNAL(settingsUpdated()), parent, SLOT(reloadSettings()));
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

	// Set settings
	ui->CBvolIni->setCurrentText(QString::number(volIni));
	ui->CBvolFin->setCurrentText(QString::number(volFin));
	ui->CBvolInc->setCurrentText(QString::number(volInc));
	ui->CBtimeMaxVol->setCurrentText(QString::number(timeMaxVol));
	ui->CBtimeSleep->setCurrentText(QString::number(timeSleep));
	ui->CHKSleep->setChecked(isEnableSleep);
	ui->CHKvolGradual->setChecked(isEnableGrad);

	Options::on_CHKSleep_toggled(isEnableSleep);
	Options::on_CHKvolGradual_toggled(isEnableGrad);
}

void Options::readSettings()
{
	settings.beginGroup("Volume");
	isEnableGrad = settings.value("volGradual", true).toBool();
	volIni = settings.value("volumeInicial", 0).toInt();
	volFin = settings.value("volumeFinal", 100).toInt();
	volInc = settings.value("volumeIncrement", 5).toInt();
	timeMaxVol = settings.value("timeToMaxVolumen", 60).toInt();
	settings.endGroup();

	settings.beginGroup("Sleep");
	isEnableSleep = settings.value("enableSleep", true).toBool();
	timeSleep = settings.value("timeSleep", 5).toInt();
	settings.endGroup();
}

void Options::writeSettings()
{
	settings.beginGroup("Volume");
	settings.setValue("volGradual", isEnableGrad);
	settings.setValue("volumeInicial", volIni);
	settings.setValue("volumeFinal", volFin);
	settings.setValue("volumeIncrement", volInc);
	settings.setValue("timeToMaxVolumen", timeMaxVol);
	settings.endGroup();

	settings.beginGroup("Sleep");
	settings.setValue("enableSleep", isEnableSleep);
	settings.setValue("timeSleep", timeSleep);
	settings.endGroup();
}

void Options::readValuesUI()
{
	isEnableGrad = ui->CHKvolGradual->isChecked();
	volIni = ui->CBvolIni->currentText().toInt();
	volFin = ui->CBvolFin->currentText().toInt();
	volInc = ui->CBvolInc->currentText().toInt();
	timeMaxVol = ui->CBtimeMaxVol->currentText().toInt();
	isEnableSleep = ui->CHKSleep->isChecked();
	timeSleep = ui->CBtimeSleep->currentText().toInt();
}

void Options::sendValues()
{

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
	sendValues();
	emit settingsUpdated();
}


// Implementar bien esta parte. Parece que QValidator es una buena opción
void Options::on_CBvolIni_currentTextChanged(const QString &arg1)
{
	QRegExp digit("\\d+");

	if (!digit.exactMatch(arg1))
		ui->label->setToolTip("Sólo numeros");
}

#include "options.h"
#include "ui_options.h"
#include <QDebug>

Options::Options(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Options)
{
	ui->setupUi(this);

	iniValues();
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
	ui->CBincVol->addItems({"5", "10", "15", "20"});

	ui->CBvolFin->setCurrentIndex(list.size() - 1);
	ui->CBtimeSleep->setCurrentIndex(2);
	ui->CHKSleep->setChecked(true);
	ui->CHKvolGradual->setChecked(true);


	Options::on_CHKSleep_toggled(true);
	Options::on_CHKvolGradual_toggled(true);
}


void Options::on_CHKSleep_toggled(bool checked)
{
	ui->CBtimeSleep->setEnabled(checked);
}

void Options::on_CHKvolGradual_toggled(bool checked)
{
	ui->CBvolFin->setEnabled(checked);
	ui->CBincVol->setEnabled(checked);
}

void Options::on_buttonBox_accepted()
{

}

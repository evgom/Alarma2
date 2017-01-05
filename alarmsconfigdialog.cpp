#include "alarmsconfigdialog.h"
#include "ui_alarmsconfigdialog.h"

AlarmsConfigDialog::AlarmsConfigDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AlarmsConfigDialog)
{
	ui->setupUi(this);
}

AlarmsConfigDialog::~AlarmsConfigDialog()
{
	delete ui;
}

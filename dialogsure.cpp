#include "dialogsure.h"
#include "ui_dialogsure.h"

DialogSure::DialogSure(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DialogSure)
{
	ui->setupUi(this);

	connect(this, SIGNAL(stopAlarm()), parent, SLOT(initVal()));
}

DialogSure::~DialogSure()
{
	delete ui;
}

void DialogSure::on_buttonBox_accepted()
{
	emit stopAlarm();
}

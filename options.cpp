#include "options.h"
#include "ui_options.h"
#include <QDebug>

options::options(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::options)
{
    ui->setupUi(this);

    iniValues();
}

options::~options()
{
    delete ui;
}

void options::iniValues()
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


    options::on_CHKSleep_toggled(true);
    options::on_CHKvolGradual_toggled(true);
}


void options::on_CHKSleep_toggled(bool checked)
{
    ui->CBtimeSleep->setEnabled(checked);
}

void options::on_CHKvolGradual_toggled(bool checked)
{
    ui->CBvolFin->setEnabled(checked);
    ui->CBincVol->setEnabled(checked);
}

void options::on_buttonBox_accepted()
{

}

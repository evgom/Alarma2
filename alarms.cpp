#include "alarms.h"
#include "ui_alarms.h"

Alarms::Alarms(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Alarms)
{
    ui->setupUi(this);
    alarm = new QTime();

    connect(this, SIGNAL(newFile(QString)), parent, SLOT(setFile(QString)));
    connect(this, SIGNAL(newAlarm(QTime)), parent, SLOT(setNextAlarm(const QTime)));
}

Alarms::~Alarms()
{
    delete ui;
}

void Alarms::on_toolButton_clicked()
{
    file = QFileDialog::getOpenFileName(this, "Seleccionar Canción", "~/",
                                        "Archivos mp3(*.mp3);;Archivos m4a(*.m4a);;Todos(*.*)");
    if(!file.isEmpty())
        ui->LEfile->setText(file);
    else
        ui->LEfile->setText("");
}

void Alarms::on_buttonBox_accepted()
{
    *alarm = ui->TEalarm->time();

    emit newFile(file);
    emit newAlarm(*alarm);
}

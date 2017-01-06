#ifndef ALARMSCONFIGDIALOG_H
#define ALARMSCONFIGDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QSettings>
#include "alarmsettings.h"

namespace Ui {
class AlarmsConfigDialog;
}

class AlarmsConfigDialog : public QDialog
{
	Q_OBJECT

public:
	explicit AlarmsConfigDialog(QWidget *parent = 0);
	~AlarmsConfigDialog();

private slots:
	void on_BBalarmsConfigDialog_accepted();
	void on_TBfile_clicked();

private:
	Ui::AlarmsConfigDialog *ui;
	Alarm *alarm;
	AlarmSettings *settingsAlarms;
	void initVal();
	void readAlarmsSettings();
	void writeAlarmsSettings();
	void setCHKDays();
	void CHKDaysToAlarm();

signals:
	void alarmUpdated();
};

#endif // ALARMSCONFIGDIALOG_H

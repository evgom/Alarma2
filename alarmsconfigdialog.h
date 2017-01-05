#ifndef ALARMSCONFIGDIALOG_H
#define ALARMSCONFIGDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QSettings>

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
	QString file;
	QTime *alarm;
	QSettings settingsAlarms;
	void initVal();
	void readAlarmsSettings();
	void writeAlarmsSettings();

signals:
	void newAlarm(const QTime &time);
	void newFile(const QString file);
};

#endif // ALARMSCONFIGDIALOG_H

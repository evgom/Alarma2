#ifndef ALARMS_H
#define ALARMS_H

#include <QDialog>
#include <QFileDialog>
#include <QDebug>
#include <QSettings>

namespace Ui {
class Alarms;
}

class Alarms : public QDialog
{
	Q_OBJECT

public:
	explicit Alarms(QWidget *parent = 0);
	~Alarms();

private slots:
	void on_toolButton_clicked();

	void on_buttonBox_accepted();

private:
	Ui::Alarms *ui;
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

#endif // ALARMS_H

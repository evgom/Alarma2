#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>
#include <QDebug>
#include "settings.h"
#include <QTime>
#include <QValidator>

#define formatTimer "m:ss"

namespace Ui {
class Options;
}

class Options : public QDialog
{
	Q_OBJECT

public:
	explicit Options(QWidget *parent = 0);
	~Options();

private:
	Ui::Options *ui;
	bool enableVolGrad, enableSleep;
	quint8 volIni, volFin, volInc;
	quint32 timeMaxVol, timeSleep;
	Settings *settings;
	void iniValues();
	void readSettings();
	void writeSettings();
	void readValuesUI();
	qint32 timeToSecs(const QTime &time);
	QTime secsToTime(const qint32 time);
	QIntValidator *valiVol, *valiVolInc, *vVolIni, *vVolFin;
	bool newEnableVolGrad, newEnableSleep;
	quint8 newVolIni, newVolFin, newVolInc;
	quint32 newTimeMaxVol, newTimeSleep;

	void checkConfig();
	void calcValidates();

private slots:
	void on_CHKSleep_toggled(bool checked);
	void on_CHKvolGradual_toggled(bool checked);
	void on_CBvolIni_editTextChanged(const QString &arg1);
	void on_CBvolFin_editTextChanged(const QString &arg1);
	void on_CBvolInc_editTextChanged(const QString &arg1);
	void on_buttonBox_accepted();

signals:
	void settingsUpdated();
};

#endif // OPTIONS_H

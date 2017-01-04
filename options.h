#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>
#include <QDebug>
#include <settings.h>

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

private slots:
	void on_CHKSleep_toggled(bool checked);
	void on_CHKvolGradual_toggled(bool checked);
	void on_buttonBox_accepted();
	void on_CBvolIni_currentTextChanged(const QString &arg1);

signals:
	void settingsUpdated();
};

#endif // OPTIONS_H

#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>
#include <QSettings>
#include <QDebug>

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
	QSettings settings;
	bool isEnableGrad;
	bool isEnableSleep;
	quint8 volIni;
	quint8 volFin;
	quint8 volInc;
	quint32 timeMaxVol;
	quint32 timeSleep;
	void iniValues();
	void readSettings();
	void writeSettings();
	void readValuesUI();
	void sendValues();

private slots:
	void on_CHKSleep_toggled(bool checked);
	void on_CHKvolGradual_toggled(bool checked);
	void on_buttonBox_accepted();
	void on_CBvolIni_currentTextChanged(const QString &arg1);

signals:
	void settingsUpdated();
};

#endif // OPTIONS_H

#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>

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
	void iniValues();

private slots:
	void on_CHKSleep_toggled(bool checked);
	void on_CHKvolGradual_toggled(bool checked);
	void on_buttonBox_accepted();

signals:
	void newSleep(const qint32 timeSleep);
	void newIncVol(const qint8 incVol);
	void newVolIni(const qint8 volIni);
	void newVolFin(const qint8 volFin);
	void VolGrad(const bool grad);
	void TimeSleep(const bool sleep);

};

#endif // OPTIONS_H

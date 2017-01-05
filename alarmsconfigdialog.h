#ifndef ALARMSCONFIGDIALOG_H
#define ALARMSCONFIGDIALOG_H

#include <QDialog>

namespace Ui {
class AlarmsConfigDialog;
}

class AlarmsConfigDialog : public QDialog
{
	Q_OBJECT

public:
	explicit AlarmsConfigDialog(QWidget *parent = 0);
	~AlarmsConfigDialog();

private:
	Ui::AlarmsConfigDialog *ui;
};

#endif // ALARMSCONFIGDIALOG_H

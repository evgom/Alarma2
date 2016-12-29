#ifndef DIALOGSURE_H
#define DIALOGSURE_H

#include <QDialog>

namespace Ui {
class DialogSure;
}

class DialogSure : public QDialog
{
	Q_OBJECT

public:
	explicit DialogSure(QWidget *parent = 0);
	~DialogSure();

private slots:
	void on_buttonBox_accepted();

private:
	Ui::DialogSure *ui;

signals:
	void stopAlarm();
};

#endif // DIALOGSURE_H

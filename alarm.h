#ifndef ALARM_H
#define ALARM_H

#include <QObject>
#include <QDateTime>
#include <QDebug>

class Alarm : public QObject
{
	Q_OBJECT
public:
	explicit Alarm(QObject *parent = 0);
	explicit Alarm(const QString file, const QDate &date, const QTime &time,Qt::TimeSpec spec = Qt::LocalTime, QObject *parent = 0);
	explicit Alarm(const QString file, const QDateTime &other, QObject *parent = 0);

	void setDateTime(const QDateTime &dateTime);
	void setDate(const QDate &date);
	void setTime(const QTime &time);
	void setFile(const QString file);
	QDateTime getDateTime();
	QDate getDate() const;
	QTime getTime() const;
	QString getFile() const;
	void setAlarm(const Alarm &other);

private:
	QDateTime *dateTime;
	QString file;

signals:

public slots:
};

#endif // ALARM_H

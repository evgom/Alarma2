#ifndef ALARM_H
#define ALARM_H

#include <QObject>
#include <QDateTime>
#include <QDebug>
#include <QAction>

class Alarm : public QObject
{
	Q_OBJECT
public:
	explicit Alarm(QObject *parent = 0);
	explicit Alarm(const QString file, const QDate &date, const QTime &time,Qt::TimeSpec spec = Qt::LocalTime, QObject *parent = 0);
	explicit Alarm(const QString file, const QDateTime &other, QObject *parent = 0);

	enum Days {
		Monday = 1,
		Tuesday = 2,
		Wednesday = 3,
		Thursday = 4,
		Friday = 5,
		Saturday = 6,
		Sunday = 7
	};

	void setDateTime(const QDateTime &dateTime);
	void setDate(const QDate &date);
	void setTime(const QTime &time);
	void setFile(const QString file);
	void setDays(const QSet<int8_t> days);
	void setDays(const QString days);
	QDateTime getDateTime();
	QDate getDate() const;
	QTime getTime() const;
	QString getFile() const;
	QSet<int8_t> getDays() const;
	QString getDaysQstring() const;

	void setAlarm(const Alarm &other);

	static QSet<int8_t> qstringDaysToQset(const QString string);
	static QString qsetDaysToQstring(const QSet<int8_t> set);

private:
	QDateTime *dateTime;
	QString file;
	QSet<int8_t> days;

signals:

public slots:
};

#endif // ALARM_H

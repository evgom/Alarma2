#include "alarm.h"

Alarm::Alarm(QObject *parent) : QObject(parent)
{
	QDate date(2000, 1, 1);
	QTime time(0, 0);
	dateTime = new QDateTime(date, time);
}

Alarm::Alarm(const QString file, const QDate &date, const QTime &time,
			 Qt::TimeSpec spec, QObject *parent) : QObject(parent)
{
	this->file = file;
	dateTime = new QDateTime(date, time, spec);
}

Alarm::Alarm(const QString file, const QDateTime &other, QObject *parent) : QObject(parent)
{
	this->file = file;
	dateTime = new QDateTime(other);
}

Alarm::~Alarm()
{
	delete dateTime;
}

void Alarm::setDateTime(const QDateTime &dateTime)
{
	*this->dateTime = dateTime;
}

void Alarm::setDate(const QDate &date)
{
	dateTime->setDate(date);
}

void Alarm::setTime(const QTime &time)
{
	dateTime->setTime(time);
}

void Alarm::setFile(const QString file)
{
	this->file = file;
}

void Alarm::setDays(const QSet<int8_t> days)
{
	qint8 value;
	QSetIterator<int8_t> i(days);

	this->days.clear();
	while(i.hasNext())
	{
		value = i.next();
		if ( (value >= Monday) && (value <= Sunday) )
			this->days.insert(value);
	}
}

void Alarm::setDays(const QString days)
{
	setDays(qstringDaysToQset(days));
}

QDateTime Alarm::getDateTime()
{
	QDateTime temp(*dateTime);
	/*QDateTime temp;
	temp.operator =(*dateTime);*/
	return temp;
}

QDate Alarm::getDate() const
{
	return dateTime->date();
}

QTime Alarm::getTime() const
{
	return dateTime->time();
}

QString Alarm::getFile() const
{
	return file;
}

QSet<int8_t> Alarm::getDays() const
{
	return days;
}

QString Alarm::getDaysQstring() const
{
	return qsetDaysToQstring(days);
}

void Alarm::setAlarm(const Alarm &other)
{
	setDate(other.getDate());
	setTime(other.getTime());
	setFile(other.getFile());
	setDays(other.getDays());
}

QSet<int8_t> Alarm::qstringDaysToQset(const QString string)
{
	QSet<int8_t> set;
	QStringList list = string.split(" ");
	QListIterator<QString> i(list);

	while (i.hasNext())
		set << i.next().toInt();

	return set;
}

QString Alarm::qsetDaysToQstring(const QSet<int8_t> set)
{
	QString string = "";
	QSetIterator<int8_t> i(set);

	while (i.hasNext())
	{
		if (i.hasPrevious())
			string += " ";

		string += QString::number( i.next() );
	}

	return string;
}

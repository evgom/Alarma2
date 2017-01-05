#include "alarm.h"

Alarm::Alarm(QObject *parent) : QObject(parent)
{
	dateTime = new QDateTime();

}

Alarm::Alarm(const QString file, const QDate &date, const QTime &time, Qt::TimeSpec spec, QObject *parent)
{
	this->file = file;
	dateTime = new QDateTime(date, time);
}

Alarm::Alarm(const QString file, const QDateTime &other, QObject *parent) : QObject(parent)
{
	this->file = file;
	dateTime = new QDateTime(other);
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

void Alarm::setAlarm(const Alarm &other)
{
	setDate(other.getDate());
	setTime(other.getTime());
	setFile(other.getFile());
}



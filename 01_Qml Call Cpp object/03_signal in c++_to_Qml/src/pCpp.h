#pragma once

#include <QObject>
#include <QDebug>
#include <QDateTime>
#include <QTimer>

/*
 * Point : Must be inherited from QObject Class
 */
class PCpp : public QObject
{
	Q_OBJECT
public:
	PCpp()
	{
		/*
		* Point : Timer signal 
		*/
		QTimer *timer = new QTimer(this);
		connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
		timer->start(1000);
	}
	~PCpp() { }
public:
	/*
	 * Point : Q_INVOKABLE make normal function could be called by qml
	 */
	Q_INVOKABLE QDateTime getCurrentDateTime() {
		return QDateTime::currentDateTime();
	}

signals:
	/*
	* Point : define dataChanged here , but onDataChanged in qml , the letter is not the same
	*/
	void dataChanged();
public slots :
	/*
	 * Point : slot function could be called by qml
	 */
	void cppSlot(int number) {
		qDebug() << "Called the C++ slot with" << number;
	}
	void onTimer()
	{
		/*
		* Point : emit means trigger the signal
		*/
		emit dataChanged();
	}
};


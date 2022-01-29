#pragma once

#include <QObject>
#include <QDebug>

/*
 * Point ： Must be inherited from QObject Class
 */
class PCpp : public QObject
{
	Q_OBJECT
public:
	/*
	 * Point ： Q_INVOKABLE make normal function could be called by qml
	 */
	Q_INVOKABLE void cppMethod(const QString &msg) {
		qDebug() << "Called the C++ method with" << msg;
	}

public slots :
	/*
	 * Point ： slot function could be called by qml
	 */
	void cppSlot(int number) {
		qDebug() << "Called the C++ slot with" << number;
	}

};


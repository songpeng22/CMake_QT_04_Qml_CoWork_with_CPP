#include <QApplication>
#include <QGuiApplication>

#include <QQuickWindow>
#include <QPushButton>
#include <QQuickItem>
//For Method 1
#include <QQmlApplicationEngine>
//For Method 2
#include <QQuickView>
//For Method 3
#include <QQuickWidget>
#include "SingletonTypeExample.h"

#if 1

QObject * FindSubObjectByObjectName(QObject * objParent,QString qstr){
	QObject * objSub = objParent->findChild<QObject*>(qstr);
	if(objSub)
		qDebug() << "PName:" << objParent->objectName() << "SName:" << objSub->objectName() << endl;
	return objSub;
}

/*
 * qmlRegisterSingletonType : method 2 callback
 */
static QJSValue example_qjsvalue_singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
	Q_UNUSED(engine)

	static int seedValue = 5;
	QJSValue example = scriptEngine->newObject();
	example.setProperty("someProperty", seedValue++);
	return example;
}

/*
* qmlRegisterSingletonType : method 3 provider
*/
#if 0
class SingletonTypeExample : public QObject
{
	Q_OBJECT
		Q_PROPERTY(int someProperty READ someProperty WRITE setSomeProperty NOTIFY somePropertyChanged)

public:
	SingletonTypeExample(QObject* parent = 0)
		: QObject(parent), m_someProperty(0)
	{
	}

	~SingletonTypeExample() {}

	Q_INVOKABLE int doSomething() { setSomeProperty(6); return m_someProperty; }

	int someProperty() const { return m_someProperty; }
	void setSomeProperty(int val) { m_someProperty = val; emit somePropertyChanged(val); }

signals:
	void somePropertyChanged(int newValue);

private:
	int m_someProperty;
};
#endif

// Second, define the singleton type provider function (callback).
static QObject *example_qobject_singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
	Q_UNUSED(engine)
	Q_UNUSED(scriptEngine)

	SingletonTypeExample *example = new SingletonTypeExample();

	return example;
}

int main(int argc, char *argv[]) {
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication app(argc, argv);
	QQmlApplicationEngine engine;

	/*
	 * qmlRegisterSingletonType : method 1
	 * int qmlRegisterSingletonType(const QUrl &url, const char *uri, int versionMajor, int versionMinor, const char *qmlName)
	 */
	qmlRegisterSingletonType(QUrl("qrc:///style.qml"), "com.bizerba.style", 1, 0, "Style");

	/*
	* qmlRegisterSingletonType : method 2
	* int qmlRegisterSingletonType(const char *uri, int versionMajor, int versionMinor, const char *typeName, QJSValue (*)(QQmlEngine *, QJSEngine *) callback)
	*/
	qmlRegisterSingletonType("com.bizerba.singletonexample2", 1, 0, "QJSValueSingleton", example_qjsvalue_singletontype_provider);

	/*
	* qmlRegisterSingletonType : method 3
	* int qmlRegisterSingletonType(const char *uri, int versionMajor, int versionMinor, const char *typeName, QObject *(*)(QQmlEngine *, QJSEngine *) callback)
	*/
	qmlRegisterSingletonType<SingletonTypeExample>("com.bizerba.singletonexample3", 1, 0, "QObjectSingleton", example_qobject_singletontype_provider);

	engine.load(QUrl(QStringLiteral("qrc:///main.qml")));
	if (engine.rootObjects().isEmpty()) return -1;
	QQuickWindow * rootWindow = (QQuickWindow *)engine.rootObjects().first();
	if (rootWindow) {
		rootWindow->setProperty("width", 1024);
		rootWindow->setProperty("height", 768);
	}
	QObject * qmlObjectParent = Q_NULLPTR;
	QObject * qmlObjectSub = Q_NULLPTR;
/*
	//Find Root
	QObject* rootObject = engine.rootObjects().first();
	//Find Sub1
	qmlObjectSub = FindSubObjectByObjectName(rootObject, "objRect1");
	if (Q_NULLPTR == qmlObjectSub)
		return -1;
	//Find Sub2
	qmlObjectParent = qmlObjectSub;
	qmlObjectSub = FindSubObjectByObjectName(qmlObjectParent, "objButton1");
	if (Q_NULLPTR == qmlObjectSub)
		return -1;

	QPushButton * btn = (QPushButton *) qmlObjectSub;
	if (btn)
		btn->setProperty("text", "textNew3");
*/
	return app.exec();
}

#elif 0
/*
* Find Sub Object(Button) by objectName
* Method : From QQuickWindow
*/
int main(int argc, char *argv[]){
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication app(argc, argv);
	QQmlApplicationEngine engine;
	engine.load(QUrl(QStringLiteral("qrc:///main.qml")));
	if (engine.rootObjects().isEmpty()) return -1;
	QQuickWindow * rootWindow = (QQuickWindow *)engine.rootObjects().first();
	if (rootWindow) {
		rootWindow->setProperty("width", 1024);
		rootWindow->setProperty("height", 768);
	}
	QObject * btn = Q_NULLPTR;
	auto list = rootWindow->contentItem()->childItems();
	for (QQuickItem *item : list) {
		qDebug() << item->objectName() << endl;
		if (item->objectName() == "objButton1") {
			qDebug() << "Found the button";
			btn = item;
		}
		if (btn) break;
	}
	if(btn)
		btn->setProperty("text", "textNew1");

	return app.exec();
}

#elif 0
/*
* Find Sub Object by objectName
* Method : From QObject
*/
int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication app(argc, argv);
	QQmlApplicationEngine engine;
	engine.load(QUrl(QStringLiteral("qrc:///main.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;
	QObject* rootObject = engine.rootObjects().first();
	QObject * btn = rootObject->findChild<QObject*>("objButton1");

	btn->setProperty( "text", "textNew2" );

	return app.exec();
}

#elif 1

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication app(argc, argv);
	QQmlApplicationEngine engine;
	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;
	return app.exec();
}

#endif

#if 0
/*
 * Trace out objectName under rootObj
 */
int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QGuiApplication app(argc, argv);

	QQmlApplicationEngine engine;
	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;
	QObject *rootObj = engine.rootObjects().first();
	qDebug() << Q_FUNC_INFO << "\n" << rootObj->objectName() << endl;
	foreach(auto o1, rootObj->children()) {
		qDebug() << o1->objectName() << endl;
	}

	return app.exec();
}

#endif



#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include"VideoProducer.h"

int main(int argc, char *argv[])
{
    VideoProducer::registerQmlType();

    //для возможности вызова QApplication::desktop() QGuiApplication недостаточно
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}

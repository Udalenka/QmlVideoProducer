#include <QApplication>
#include <QQmlApplicationEngine>

#include"VideoProducer.h"

int main(int argc, char *argv[])
{
    VideoProducer::registerQmlType();

    //для возможности вызова QApplication::desktop() QGuiApplication недостаточно
    //QGuiApplication app(argc, argv);
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}

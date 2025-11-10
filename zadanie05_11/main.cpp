#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml/qqmlcontext.h>

#include "filehandler.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    FileHandler fileHandler;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("FileHandler", &fileHandler);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("zadanie05_11", "Main");

    return app.exec();
}

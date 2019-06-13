#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include <QFile>
#include "fileloader.h"

#include "treemodel.h"
#include "customtype.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;


    // expose FileLoader to qml
    FileLoader fileLoader;
    engine.rootContext()->setContextProperty("FileLoader", &fileLoader);

    // expose model
    QFile file(":/default.txt");
    file.open(QIODevice::ReadOnly);
    TreeModel model;

    engine.rootContext()->setContextProperty("theModel", &model);
    qmlRegisterType<CustomType>("animedit.highfidelity.com", 1, 0, "CustomType");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl) {
            QCoreApplication::exit(-1);
        } else {
            ;
        }
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

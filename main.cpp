#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include "UHDGUIWrapper.h"
#include "WaveformDataProvider.h"


int main(int argc, char *argv[]){

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    UHDGUIWrapper usrp;
    WaveformDataProvider provider(usrp.rxDeque());

    QQmlContext *context = engine.rootContext();

    context->setContextProperty("__USRPSession", &usrp);
    context->setContextProperty("__usrpList", usrp.devicesList());
    context->setContextProperty("__rxSignalProvider", &provider);

    const QUrl url(QString("qrc:/GUI/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl){
        if(!obj && url == objUrl) QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);


    return app.exec();
}

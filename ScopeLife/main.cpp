#include "mainwindow.h"

#include <QApplication>
#include <QWebEngineSettings>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);

    QPixmap pixmap(":/splash.png");
    QSplashScreen splash(pixmap);
    splash.show();
    a.processEvents();
    splash.showMessage("Loaded modules");

    MainWindow w;

    QString startup = w.getCore()->getStringValue("system_startup");
    if(startup.compare("window")==0){
        w.resize(1920,1080);
        w.show();
    }
    if(startup.compare("fullscreen")==0){
        w.showFullScreen();
    }

    splash.finish(&w);

    return a.exec();
}

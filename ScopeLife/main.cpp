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
    w.resize(1920,1080);
    w.show();
    splash.finish(&w);

    return a.exec();
}

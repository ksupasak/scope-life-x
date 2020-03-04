#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include "stationwindow.h"
#include <QWebEngineSettings>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pixmap(":/AOC.png");
    QSplashScreen splash(pixmap);
    splash.show();
    a.processEvents();
    splash.showMessage("Loaded modules");

    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);

    MainWindow w;
    w.show();
    splash.finish(&w);

    return a.exec();
}

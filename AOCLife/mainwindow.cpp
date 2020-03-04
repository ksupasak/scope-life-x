#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stationwindow.h"
#include <QFile>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QFile File(":/main.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());

    this->setStyleSheet(StyleSheet);

    ui->web->setUrl(QUrl("https://pcm-life.com:1792/miot/Sas/index"));
//    ui->web->setUrl(QUrl("https://localhost:1792/miot/Sas/index"));



    connect(ui->actionStation_Window, SIGNAL(triggered()), this, SLOT(openStationWindow()));
    connect(ui->actionDVR_Window, SIGNAL(triggered()), this, SLOT(openDVRWindow()));
    connect(ui->actionTele_Window, SIGNAL(triggered()), this, SLOT(openTeleWindow()));


    connect(ui->web, &WebController::consoleMessage, this,  &MainWindow::consoleMessage);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openStationWindow()
{
    if(station_window==NULL){
        station_window = new StationWindow();
    }

    station_window->show();
    if(station_window->isMinimized()){
        station_window->showMaximized();
    }
}

void MainWindow::openDVRWindow()
{
    if(dvr_window==NULL){
        dvr_window = new StationWindow();
    }

    dvr_window->show();
    if(dvr_window->isMinimized()){
        dvr_window->showMaximized();
    }
}

void MainWindow::openTeleWindow()
{
    if(tele_window==NULL){
       tele_window = new StationWindow();
    }

    tele_window->show();
    if(tele_window->isMinimized()){
        tele_window->showMaximized();
    }
}


void MainWindow::consoleMessage(QWebEnginePage::JavaScriptConsoleMessageLevel level, const QString &message)
{
    if(message.at(0)=='#'){
        QStringList params = message.split(" ");
        qDebug()<<" Console x : "<< message;
        if(params.at(0)=="#select"){
            QUrl url(params.at(1).split("|").last());
            qDebug()<<" Station : "<< url;
            openStationWindow();
            station_window->setUrl(url);

            QUrl url2(params.at(2).split("|").last());
            qDebug()<<" DVR : "<< url2;
            openDVRWindow();
            dvr_window->setUrl(url2);


            QUrl url3(params.at(3).split("|").last());
            qDebug()<<" Tele : "<< url3;
            openTeleWindow();
            tele_window->setUrl(url3);

        }
    }
}


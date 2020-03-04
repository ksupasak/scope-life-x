#include "stationwindow.h"
#include "ui_stationwindow.h"
#include <QFile>
StationWindow::StationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StationWindow)
{
    ui->setupUi(this);


    QFile File(":/main.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());

    this->setStyleSheet(StyleSheet);
}

StationWindow::~StationWindow()
{
    delete ui;
}

void StationWindow::setUrl(QUrl &url)
{
    ui->web->setUrl(url);
}

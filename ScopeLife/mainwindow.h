#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "videocontroller.h"
#include "corelib.h"
#include "medialibrarycontext.h"
#include "session.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void on_finish_clicked();
    void on_back_btn_clicked();
    void startCapture(const QUrl &url);
    void backButton();
    void processCaptureImage(QString filename);
    void processFinish();
    void queue_timeout();


    void on_start_btn_clicked();

private:
    Ui::MainWindow *ui;
    CoreLib *core;
    MediaLibraryContext * media_context;
    Session *current_session;
    QTimer *queue_process;

};
#endif // MAINWINDOW_H

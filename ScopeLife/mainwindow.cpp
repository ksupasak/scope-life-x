#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QUrlQuery>
#include <QTimer>
#include "emrsession.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    ui->stage->setCurrentIndex(0);

//    QUrl url("http://gi.emr-life.com/endo/Home/index");
//    QUrl url("https://cuor.emr-life.com/cuor/Home/index");
//    QUrl url("http://mfer.emr-life.com/endo/Home/index");
//    QUrl url("http://gi.emr-life.com/endo/Home/index");

       QUrl url("http://gi.emr-life.com/endo/Colono/create?patient_id=54b38ac9790f9b2146000024&record_name=test&parent_id=5e413539790f9b46ff000003");

       ui->web->setUrl(url);


    // Test


       this->core = new CoreLib();

       this->core->loadConfig();

       this->media_context = new MediaLibraryContext(this->core);


       QHash<QString, QString> params;

        params["hn"] = "1234/45";
        params["id"] = "1231231312313";
        params["doc_name"] = "colo";
        params["full_name"] = "Supasak";

        media_context->setParams(params);

        QString out = media_context->generateInternalStoragePath(params,"img");

        qDebug()<<out;



        QFile File(":/main.qss");
        File.open(QFile::ReadOnly);
        QString StyleSheet = QLatin1String(File.readAll());

        this->setStyleSheet(StyleSheet);



        // final hook up

        ui->web->setCore(core);
        ui->video->setCore(core);
        ui->video->setMediaLibraryContext(media_context);

        connect(ui->web, &WebController::startCapture, this, &MainWindow::startCapture);

        connect(ui->web, &WebController::back, this, &MainWindow::backButton);
        connect(ui->video, &VideoController::back, this, &MainWindow::backButton);
        connect(ui->video, &VideoController::finish, this, &MainWindow::processFinish);
        connect(ui->video, &VideoController::callbackCaptureImage, this, &MainWindow::processCaptureImage);


        // queue tiemr
        queue_process = new QTimer(this);
        connect(queue_process, SIGNAL(timeout()), this, SLOT(queue_timeout()));
        queue_process->start(1000);

       //
        ui->video->setupCapturePreview(ui->live);
        ui->video->prepare();
        ui->video->startPreview();

        //ui->stage->setCurrentIndex(2);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_finish_clicked()
{
//    ui->stage->setCurrentIndex(1);
}

void MainWindow::on_back_btn_clicked()
{
//    ui->stage->setCurrentIndex(0);
}

void MainWindow::startCapture(const QUrl &url)
{

//      if(current_session!=NULL){
//          delete current_session;
//      }

//    QUrl("http://gi.emr-life.com/esm_image/300/snap?field_id=F0921787468&p_id=252&path=esm/gi/endo/test/colono/2020-02-24-5e53fb09790f9b4bf3000008/image&ref=test")
//    http://gi.emr-life.com/esm_image/945/snap?field_id=F6594394918&p_id=252&path=esm/gi/endo/test/liver_ultrasound_and_fibroscan/2020-02-26-5e561b2d790f9b6e1d00059e/us_image&ref=test


     QDateTime now = QDateTime::currentDateTime();
     QString ssid = QString::number(now.toTime_t());
     current_session = new Session();
     current_session->setSsid(ssid);
     current_session->parseUrl(url);
     current_session->init();

     media_context->setParams(current_session->getParams());

     core->setCurrentSession(current_session);

     ui->stage->setCurrentIndex(2);
     ui->video->startSession();
}

void MainWindow::backButton()
{
    if(ui->stage->currentIndex()==2){
         ui->stage->setCurrentIndex(1);
    }else
    if(ui->stage->currentIndex()==1){
         ui->stage->setCurrentIndex(0);
         ui->video->startPreview();
    }
}

void MainWindow::processCaptureImage(QString filename)
{
    qDebug()<<"Image capture at : "<<filename;

    Session *session = this->current_session;
    QDateTime stamp = QDateTime::currentDateTime();
    JobQueue *job = new JobQueue(session->getsnapUrl(),filename, stamp);

    this->core->pushJobQueue(job);

}

void MainWindow::processFinish()
{
    ui->web->finish();
    core->finishSession();
    delete  current_session;
    current_session = NULL;
    ui->stage->setCurrentIndex(1);
}

void MainWindow::queue_timeout()
{


    this->core->processQueue();

//    bool sum_job=false;
//    int count = 0;
//    while(queue->size()>0){

//        JobQueue *last = queue->front();
//        queue->pop_front();
//        processQueue(last);
//        sum_job = true;
//        if(count>1){
//            if(this->capture_mode==3&&this->mode==MODE_CAPTURE&&sum_job){
//                WebPage * page = ui->mode_live_content->getCurrentWebPage();
//                page->runJavaScript("refresh_procedure()");
//                live_capture_scene->clear();
//                core->log("UI updating..");
//                count = 0;
//            }
//        }

//        count+=1;


//    }
//    refresh_procedure

//    ui->stage->setCurrentWidget(ui->mode_web_capture);
//    if(this->capture_mode==3&&this->mode==MODE_CAPTURE&&sum_job){
//        WebPage * page = ui->mode_live_content->getCurrentWebPage();
//        page->runJavaScript("refresh_procedure()");
//        live_capture_scene->clear();
//        core->log("UI updating..");
//    }


}

void MainWindow::on_start_btn_clicked()
{
     ui->stage->setCurrentIndex(1);
}

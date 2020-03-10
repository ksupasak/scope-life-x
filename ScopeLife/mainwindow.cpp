#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QUrlQuery>
#include <QTimer>
#include "emrsession.h"
#include <QFuture>
#include <QtConcurrent>

#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>
#include <libavutil/imgutils.h>
#include <qmessagebox.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);





//    QUrl url("http://gi.emr-life.com/endo/Home/index");
//    QUrl url("https://cuor.emr-life.com/cuor/Home/index");
//    QUrl url("http://mfer.emr-life.com/endo/Home/index");
//    QUrl url("http://gi.emr-life.com/endo/Home/index");



    // Test


       this->core = new CoreLib();

       this->core->loadConfig();

       this->core->getStringValue("system_mode","scope_life");

       this->core->getStringValue("system_name","mfer");
       this->core->getStringValue("system_host","https://mfer.emr-life.com/endo/Home/index");
       this->core->getStringValue("system_title","GI-CU ออกหน่วย รพ.พระจอมเกล้าเพชรบุรี 2563");

       this->core->getStringValue("system_startup","window");


       this->core->getStringValue("input_source_1","default");
       this->core->getStringValue("input_source_2","-");

       this->core->getStringValue("image_resolution","source");
       this->core->getStringValue("image_quality","90");

       this->core->getStringValue("video_resolution","full_hd");
       this->core->getStringValue("video_codec","libx264");

       this->core->getStringValue("image_path",":home/scopelife/db/:date/:hn/:doc_name/:id/:hn|:full_name|:stamp");
       this->core->getStringValue("video_path",":home/scopelife/db/:date/:hn/:doc_name/:id/:hn|:full_name|:stamp");

       this->core->getStringValue("video_record_limit","2GB");
       this->core->getStringValue("video_record_auto","false");


       this->core->getStringValue("timer_1_enabled","true");
       this->core->getStringValue("timer_1_title","Intubation");
       this->core->getStringValue("timer_1_key","cecal_intubation_time");

       this->core->getStringValue("timer_2_enabled","true");
       this->core->getStringValue("timer_2_title","Withdrawal");
       this->core->getStringValue("timer_2_key","withdrawal_time");



       ui->stage->setCurrentIndex(0);

//       QUrl url("http://gi.emr-life.com/endo/Colono/create?patient_id=54b38ac9790f9b2146000024&record_name=test&parent_id=5e413539790f9b46ff000003");

       QUrl url(this->core->getStringValue("system_host"));

       ui->web->setUrl(url);



       this->core->saveConfig();

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
        ui->setting->setCore(core);
        ui->video->setMediaLibraryContext(media_context);

        connect(ui->web, &WebController::startCapture, this, &MainWindow::startCapture);

        connect(ui->web, &WebController::back, this, &MainWindow::backButton);
        connect(ui->video, &VideoController::back, this, &MainWindow::backButton);
        connect(ui->video, &VideoController::finish, this, &MainWindow::processFinish);
        connect(ui->video, &VideoController::callbackCaptureImage, this, &MainWindow::processCaptureImage);
        connect(ui->setting, &SettingController::back, this, &MainWindow::backButton);


        // queue tiemr
        queue_process = new QTimer(this);
        connect(queue_process, SIGNAL(timeout()), this, SLOT(queue_timeout()));
        queue_process->start(1000);

       //
        ui->video->setupCapturePreview(ui->live);
        ui->video->prepare();
        ui->video->startPreview();

       // ui->stage->setCurrentIndex(2);
       // ui->video->startSession();

        connect(ui->actionCapture, SIGNAL(triggered()), this, SLOT(captureImage()));
        connect(ui->actionRecord, SIGNAL(triggered()), this, SLOT(recordVideo()));
        connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(exitApplication()));



        pedal_switch = new HIDPedal(this);

        connect(pedal_switch, &HIDPedal::key, this, &MainWindow::processKey);

        pedal_switch_process = new QTimer(this);

 //       QTimer::singleShot(100,QtConcurrent::run(this,&MainWindow::startKey));

//        QFuture<void> future = QtConcurrent::run(startKey);
       // pedal_switch_process->singleShot(1000,this, &MainWindow::startKey);


        QFuture<void> future1 = QtConcurrent::run(this,&MainWindow::startKey);


        ui->title->setText(core->getStringValue("system_title"));


}

MainWindow::~MainWindow()
{
    delete ui;
}

CoreLib* MainWindow::getCore()
{
    return this->core;
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
    }else
    if(ui->stage->currentIndex()==3){
             ui->stage->setCurrentIndex(0);

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

    QDateTime now = QDateTime::currentDateTime();

    ui->clock->setText(now.toString("hh:mm:ss"));
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

void MainWindow::captureImage()
{
    ui->video->capture();
}

void MainWindow::recordVideo()
{
    ui->video->record();
}

void MainWindow::processKey(int key)
{
    if(key==1||key==2)
    ui->video->capture();

    if(key==1)qDebug()<<"Left Button";
    if(key==2)qDebug()<<"Middle Button";
    if(key==4)qDebug()<<"Right Button";


}

void MainWindow::on_start_btn_clicked()
{
    ui->stage->setCurrentIndex(1);
}

void MainWindow::startKey()
{
    qDebug()<<"Start Key()";
    pedal_switch->start();
}

void MainWindow::on_info_btn_clicked()
{
     pedal_switch->start();
}

void MainWindow::on_setting_btn_clicked()
{
    ui->stage->setCurrentIndex(3);
    ui->setting->load();

}

void MainWindow::exitApplication()
{

    QMessageBox msgBox;
    msgBox.setText("Quit");
    msgBox.setInformativeText("Exit ScopeLife");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    if(ret == QMessageBox::Ok)exit(0);
}

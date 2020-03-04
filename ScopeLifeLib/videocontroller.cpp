#include "videocontroller.h"
#include "ui_videocontroller.h"
#include <QMessageBox>
#include <QMediaMetaData>
#include <QMediaService>
#include <QMediaRecorder>

//#include "videosettings.h"
//#include "imagesettings.h"

VideoController::VideoController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoController)
{
    ui->setupUi(this);


    // init camera

    QString default_input = "FaceTime HD Camera (Built-in)";

    // default source input from configure

    const QList<QCameraInfo> availableCameras = QCameraInfo::availableCameras();

    QCameraInfo last;

    qDebug()<< "Number of Camera : "<< availableCameras.length();

    for (const QCameraInfo &cameraInfo : availableCameras) {

        qDebug()<< "Camera : "<< cameraInfo.description();


         if(default_input.compare(cameraInfo.description())==0){
             defaultCameraInfo = cameraInfo;
         }


        last = cameraInfo;

    }


    if (defaultCameraInfo.isNull()){

        defaultCameraInfo = QCameraInfo::defaultCamera();

    }


    qDebug()<< "Camera Default : "<< defaultCameraInfo.description();

    setCamera(defaultCameraInfo);



}




//void setCamera(const QCameraInfo &cameraInfo);

//void updateCaptureMode();



//void updateRecordTime();
//void updateCameraState(QCamera::State state);
//void updateRecorderState(QMediaRecorder::State state);
//void setExposureCompensation(int index);
//void displayRecorderError();
//void displayCameraError();
//void updateCameraDevice(QAction *action);
//void processCapturedImage(int requestId, const QImage &img);

//void capture();

VideoController::~VideoController()
{
    delete ui;
}

void VideoController::setupCapturePreview(QCameraViewfinder *view)
{
    m_camera_capture->setViewfinder(view);
    m_camera_capture->start();
}



void VideoController::setCamera(const QCameraInfo &cameraInfo)
{
    m_camera.reset(new QCamera(cameraInfo));
    m_camera_capture.reset(new QCamera(cameraInfo));



    connect(m_camera.data(), &QCamera::stateChanged, this, &VideoController::updateCameraState);
    connect(m_camera.data(), QOverload<QCamera::Error>::of(&QCamera::error), this, &VideoController::displayCameraError);




    m_mediaRecorder.reset(new QMediaRecorder(m_camera.data()));
    connect(m_mediaRecorder.data(), &QMediaRecorder::stateChanged, this, &VideoController::updateRecorderState);

    connect(m_mediaRecorder.data(), &QMediaRecorder::durationChanged, this, &VideoController::updateRecordTime);
    connect(m_mediaRecorder.data(), QOverload<QMediaRecorder::Error>::of(&QMediaRecorder::error),
            this, &VideoController::displayRecorderError);



//    connect(ui->exposureCompensation, &QAbstractSlider::valueChanged, this, &MainWindow::setExposureCompensation);

    m_camera->setViewfinder(ui->live);

    updateCameraState(m_camera->state());
//    updateLockStatus(m_camera->lockStatus(), QCamera::UserRequest);
    updateRecorderState(m_mediaRecorder->state());

    m_imageCapture.reset(new QCameraImageCapture(m_camera_capture.data()));


//    connect(m_imageCapture.data(), &QCameraImageCapture::readyForCaptureChanged, this, &MainWindow::readyForCapture);
    connect(m_imageCapture.data(), &QCameraImageCapture::imageCaptured, this, &VideoController::processCapturedImage);
//    connect(m_imageCapture.data(), &QCameraImageCapture::imageSaved, this, &MainWindow::imageSaved);
//    connect(m_imageCapture.data(), QOverload<int, QCameraImageCapture::Error, const QString &>::of(&QCameraImageCapture::error),
//            this, &MainWindow::displayCaptureError);

//    connect(m_camera.data(), QOverload<QCamera::LockStatus, QCamera::LockChangeReason>::of(&QCamera::lockStatusChanged),
//            this, &MainWindow::updateLockStatus);

//    ui->captureWidget->setTabEnabled(0, (m_camera->isCaptureModeSupported(QCamera::CaptureStillImage)));
//    ui->captureWidget->setTabEnabled(1, (m_camera->isCaptureModeSupported(QCamera::CaptureVideo)));

    m_mediaRecorder.reset(new QMediaRecorder(m_camera.data()));
    connect(m_mediaRecorder.data(), &QMediaRecorder::stateChanged, this, &VideoController::updateRecorderState);



    connect(m_mediaRecorder.data(), &QMediaRecorder::durationChanged, this, &VideoController::updateRecordTime);
    connect(m_mediaRecorder.data(), QOverload<QMediaRecorder::Error>::of(&QMediaRecorder::error),
            this, &VideoController::displayRecorderError);

//    m_mediaRecorder->setMetaData(QMediaMetaData::Title, QVariant(QLatin1String("Test Title")));


    updateCaptureMode();
    configureVideoSettings();

    m_camera->start();

}


void VideoController::updateCaptureMode()
{
//    int tabIndex = ui->captureWidget->currentIndex();

    QCamera::CaptureModes captureMode =  QCamera::CaptureVideo;

    if (m_camera->isCaptureModeSupported(captureMode))
        m_camera->setCaptureMode(captureMode);
    else
        m_camera->setCaptureMode(QCamera::CaptureStillImage);

    m_camera_capture->setCaptureMode(QCamera::CaptureStillImage);


}

void VideoController::setCore(CoreLib *core)
{
    this->core = core;
}

void VideoController::setMediaLibraryContext(MediaLibraryContext *media_context)
{
    this->media_context = media_context;
}






void VideoController::updateCameraState(QCamera::State state)
{
//    switch (state) {
//    case QCamera::ActiveState:
//        ui->actionStartCamera->setEnabled(false);
//        ui->actionStopCamera->setEnabled(true);
//        ui->captureWidget->setEnabled(true);
//        ui->actionSettings->setEnabled(true);
//        break;
//    case QCamera::UnloadedState:
//    case QCamera::LoadedState:
//        ui->actionStartCamera->setEnabled(true);
//        ui->actionStopCamera->setEnabled(false);
//        ui->captureWidget->setEnabled(false);
//        ui->actionSettings->setEnabled(false);
//    }
}

void VideoController::updateRecorderState(QMediaRecorder::State state)
{
//    switch (state) {
//    case QMediaRecorder::StoppedState:
//        ui->recordButton->setEnabled(true);
//        ui->pauseButton->setEnabled(true);
//        ui->stopButton->setEnabled(false);
//        break;
//    case QMediaRecorder::PausedState:
//        ui->recordButton->setEnabled(true);
//        ui->pauseButton->setEnabled(false);
//        ui->stopButton->setEnabled(true);
//        break;
//    case QMediaRecorder::RecordingState:
//        ui->recordButton->setEnabled(false);
//        ui->pauseButton->setEnabled(true);
//        ui->stopButton->setEnabled(true);
//        break;
//    }
}

void VideoController::setExposureCompensation(int index)
{
    m_camera->exposure()->setExposureCompensation(index*0.5);
}

void VideoController::displayRecorderError()
{
    QMessageBox::warning(this, tr("Capture Error"), m_mediaRecorder->errorString());
}

void VideoController::displayCameraError()
{
    QMessageBox::warning(this, tr("Camera Error"), m_camera->errorString());
}

void VideoController::updateCameraDevice(QAction *action)
{
//    setCamera(qvariant_cast<QCameraInfo>(action->data()));
}
void VideoController::updateRecordTime()
{
    QString str = QString("Recorded %1 sec").arg(m_mediaRecorder->duration()/1000);
}


void VideoController::processCapturedImage(int requestId, const QImage& img)
{
    Q_UNUSED(requestId);

    qDebug()<<"Image Capturing";


    QImage scaledImage = img.scaled(ui->preview->size(),
                                    Qt::KeepAspectRatio,
                                    Qt::SmoothTransformation);

    ui->preview->setPixmap(QPixmap::fromImage(scaledImage));

    QString filename = media_context->generateInternalStoragePath("img")+".jpeg";

    qDebug()<<"Image Path : "<<filename;

    if(img.save( filename, "JPEG",90)){

        emit callbackCaptureImage(filename);

    }else{
        emit callbackErrorCapture("Image Caputre Error");
    }


//    displayCapturedImage();
//    QTimer::singleShot(4000, this, &Camera::displayViewfinder);

//    m_camera->setCaptureMode(QCamera::CaptureVideo);

}

void VideoController::record()
{


        if(m_mediaRecorder->status()==QMediaRecorder::RecordingStatus){
            m_mediaRecorder->stop();
            qDebug()<<"Video stop record  : "<<m_mediaRecorder->outputLocation();

        }else{


    //        configureVideoSettings();

    //        qDebug()<<" Codec "<<m_videoSettings.codec();
    //        qDebug()<<" Resolution "<<m_videoSettings.resolution();
    //        qDebug()<<" Rate "<<m_videoSettings.bitRate();
    //        qDebug()<<" Quality "<<m_videoSettings.quality();
    //        qDebug()<<" FPS "<<m_videoSettings.frameRate();
    //        m_mediaRecorder->setVideoSettings(m_videoSettings);



            QString filename = media_context->generateInternalStoragePath("video")+".mp4";
            m_mediaRecorder->setMetaData(QMediaMetaData::Title, QVariant(QLatin1String("Test Title")));
            m_mediaRecorder->setOutputLocation(QUrl::fromLocalFile(filename));
            qDebug()<<"Video start record : "<<filename;

            m_mediaRecorder->record();


        }

        updateRecordTime();


}

void VideoController::capture()
{
     qDebug()<<"Start capture";
//     m_camera->setCaptureMode(QCamera::CaptureStillImage);
     m_imageCapture->capture();
     qDebug()<<"Finish capture";



}


void VideoController::on_back_btn_clicked()
{
    emit back();
}

void VideoController::on_finish_button_clicked()
{
    emit finish();
}

void VideoController::on_capture_btn_clicked()
{

     this->capture();

}

void VideoController::on_record_btn_clicked()
{
    record();
}

void VideoController::configureCaptureSettings()
{

}

void VideoController::configureImageSettings()
{

    //    ImageSettings settingsDialog(m_imageCapture.data());
    //    settingsDialog.setWindowFlags(settingsDialog.windowFlags() & ~Qt::WindowContextHelpButtonHint);

    //    settingsDialog.setImageSettings(m_imageSettings);

    //    if (settingsDialog.exec()) {
    //        m_imageSettings = settingsDialog.imageSettings();
    //        m_imageCapture->setEncodingSettings(m_imageSettings);

}

void VideoController::configureVideoSettings()
{


     m_camera->unlock();


       QVideoEncoderSettings settings = m_mediaRecorder->videoSettings();
       settings.setResolution(1280,720);
//     settings.setQuality(QMultimedia::VeryHighQuality);
       settings.setFrameRate(30.0);
       settings.setCodec("avc1");
       settings.setBitRate(8000);



       //    qDebug()<<" Codec "<<settings.codec();
       //    qDebug()<<" Resolution "<<settings.resolution();
       //    qDebug()<<" Rate "<<settings.bitRate();
       //    qDebug()<<" Quality "<<settings.quality();
       //    qDebug()<<" FPS "<<settings.frameRate();


       m_mediaRecorder->setVideoSettings(settings);
       m_mediaRecorder->setContainerFormat("mp4");

       m_camera->setCaptureMode(QCamera::CaptureVideo);
       m_camera->focus();


       QAudioEncoderSettings audioSettings;
       m_mediaRecorder->setAudioSettings(audioSettings);
       m_mediaRecorder->setVideoSettings(m_videoSettings);
       m_mediaRecorder->setEncodingSettings(audioSettings,m_videoSettings,"mp4");






//    audioSettings.setCodec("audio/amr");
//    audioSettings.setQuality(QMultimedia::HighQuality);



    m_camera->locked();


}



QVariant VideoController::boxValue(const QComboBox *box) const
    {
        int idx = box->currentIndex();
        if (idx == -1)
            return QVariant();

        return box->itemData(idx);
    }

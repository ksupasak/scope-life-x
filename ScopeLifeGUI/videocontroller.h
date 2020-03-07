#ifndef VIDEOCONTROLLER_H
#define VIDEOCONTROLLER_H
#include <QWidget>
#include <QCameraImageCapture>
#include <QCameraInfo>
#include <QMediaRecorder>
#include <corelib.h>
#include <medialibrarycontext.h>
#include <QComboBox>
#include <QCameraViewfinder>
#include "ScopeLifeGUI_global.h"
namespace Ui {
class VideoController;
}

class SCOPELIFEGUI_EXPORT VideoController : public QWidget
{

    Q_OBJECT

signals:
    void back();
    void finish();
    void callbackCaptureImage(QString filename);
    void callbackErrorCapture(QString msg);


public:
    explicit VideoController(QWidget *parent = nullptr);
    ~VideoController();



    void setupCapturePreview(QCameraViewfinder *view);


    void setCamera(const QCameraInfo &cameraInfo);

    void updateCaptureMode();

    void setCore(CoreLib *core);
    void setMediaLibraryContext(MediaLibraryContext *media_context);

public slots:

    void updateRecordTime();
    void updateCameraState(QCamera::State state);
    void updateRecorderState(QMediaRecorder::State state);
    void setExposureCompensation(int index);
    void displayRecorderError();
    void displayCameraError();
    void updateCameraDevice(QAction *action);
    void processCapturedImage(int requestId, const QImage &img);

    void record();
    void capture();

private slots:
    void on_back_btn_clicked();

    void on_finish_button_clicked();

    void on_capture_btn_clicked();

    void on_record_btn_clicked();


    void configureCaptureSettings();

    void configureVideoSettings();

    void configureImageSettings();

private:

    CoreLib *core;
    MediaLibraryContext *media_context;
    Ui::VideoController *ui;

    QCameraInfo defaultCameraInfo;

    QScopedPointer<QCamera> m_camera;
    QScopedPointer<QCamera> m_camera_capture;

    QScopedPointer<QCameraImageCapture> m_imageCapture;
    QScopedPointer<QMediaRecorder> m_mediaRecorder;

    QImageEncoderSettings m_imageSettings;
    QAudioEncoderSettings m_audioSettings;
    QVideoEncoderSettings m_videoSettings;
    QString m_videoContainerFormat;
    bool m_isCapturingImage = false;
    bool m_applicationExiting = false;
    QVariant boxValue(const QComboBox*) const;

};

#endif // VIDEOCONTROLLER_H

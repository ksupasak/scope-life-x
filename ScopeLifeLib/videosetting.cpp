#include "videosetting.h"
#include "ui_videosetting.h"

VideoSetting::VideoSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoSetting)
{
    ui->setupUi(this);


    //    QVideoEncoderSettings settings = m_mediaRecorder->videoSettings();
    //    m_videoSettings.setCodec(boxValue(ui->videoCodecBox).toString());
    //    m_videoSettings.setQuality(QMultimedia::EncodingQuality(ui->videoQualitySlider->value()));
    //    m_videoSettings.setResolution(boxValue(ui->videoResolutionBox).toSize());
    //    m_videoSettings.setFrameRate(boxValue(ui->videoFramerateBox).value<qreal>());

    //    VideoSettings settingsDialog(m_mediaRecorder.data());
    //    settingsDialog.setWindowFlags(settingsDialog.windowFlags() & ~Qt::WindowContextHelpButtonHint);

    //    settingsDialog.setAudioSettings(m_audioSettings);
    //    settingsDialog.setVideoSettings(m_videoSettings);
    //    settingsDialog.setFormat(m_videoContainerFormat);

    //    if (settingsDialog.exec()) {
    //        m_audioSettings = settingsDialog.audioSettings();
    //        m_videoSettings = settingsDialog.videoSettings();
    //        m_videoContainerFormat = settingsDialog.format();

    //        m_mediaRecorder->setEncodingSettings(
    //                    m_audioSettings,
    //                    m_videoSettings,
    //                    m_videoContainerFormat);
    //    }
    //    settings.setCodec(boxValue(ui->videoCodecBox).toString());
    //    settings.setQuality(QMultimedia::EncodingQuality(ui->videoQualitySlider->value()));
    //    settings.setResolution(boxValue(ui->videoResolutionBox).toSize());
    //    settings.setFrameRate(boxValue(ui->videoFramerateBox).value<qreal>());
}



VideoSetting::~VideoSetting()
{
    delete ui;
}

void VideoSetting::setUp(QMediaRecorder *recorder,QVideoEncoderSettings &setting)
{


           //video codecs
           ui->videoCodecBox->addItem(tr("Default video codec"), QVariant(QString()));
           const QStringList supportedVideoCodecs = recorder->supportedVideoCodecs();
           for (const QString &codecName : supportedVideoCodecs) {
               QString description = recorder->videoCodecDescription(codecName);
               ui->videoCodecBox->addItem(codecName + ": " + description, QVariant(codecName));
           }

           ui->videoQualitySlider->setRange(0, int(QMultimedia::VeryHighQuality));


           ui->videoResolutionBox->addItem(tr("Default"));
           const QList<QSize> supportedResolutions = recorder->supportedResolutions();
           for (const QSize &resolution : supportedResolutions) {
               ui->videoResolutionBox->addItem(QString("%1x%2").arg(resolution.width()).arg(resolution.height()),
                                               QVariant(resolution));
           }

           ui->videoFramerateBox->addItem(tr("Default"));
           const QList<qreal> supportedFrameRates = recorder->supportedFrameRates();
           for (qreal rate : supportedFrameRates) {
               QString rateString = QString("%1").arg(rate, 0, 'f', 2);
               ui->videoFramerateBox->addItem(rateString, QVariant(rate));
           }

           //containers
           ui->containerFormatBox->addItem(tr("Default container"), QVariant(QString()));
           const QStringList formats = recorder->supportedContainers();
           for (const QString &format : formats) {
               ui->containerFormatBox->addItem(format + ": " + recorder->containerDescription(format),
                                               QVariant(format));
           }


}

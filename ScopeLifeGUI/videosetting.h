#ifndef VIDEOSETTING_H
#define VIDEOSETTING_H

#include <QWidget>
#include <QMediaRecorder>

namespace Ui {
class VideoSetting;
}

class VideoSetting : public QWidget
{
    Q_OBJECT

public:
    explicit VideoSetting(QWidget *parent = nullptr);
    ~VideoSetting();
    void setUp(QMediaRecorder *recorder, QVideoEncoderSettings &setting);
private:
    Ui::VideoSetting *ui;
};

#endif // VIDEOSETTING_H

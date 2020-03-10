#ifndef VIDEORECORDER_H
#define VIDEORECORDER_H

#include <QObject>

#include <libavcodec/avcodec.h>

#include <libavutil/opt.h>
#include <libavutil/imgutils.h>

class VideoRecorder : public QObject
{
public:
    VideoRecorder(QObject *parent);

    void encode(AVFrame *frame);

    void setOutputLocation(QUrl &output);
    void setFormat(QString encoder, int w, int h, int fps, int bitrate);
    void start();
    void stop();
    void pause();

private:

    AVCodecContext *ctx;
    AVPacket *pkt;
    AVCodec *codec;
    QString filename;
    QString codec_name;
    FILE *file_output;
    int width;
    int height;
    int fps;
    int bitrate;
    bool recording=false;

};

#endif // VIDEORECORDER_H

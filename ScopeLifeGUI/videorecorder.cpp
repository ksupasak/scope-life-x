#include "videorecorder.h"


#include <libavcodec/avcodec.h>

#include <libavutil/opt.h>
#include <libavutil/imgutils.h>
#include <QUrl>
#include <QDebug>


VideoRecorder::VideoRecorder(QObject *parent)
{

}

void VideoRecorder::encode(AVFrame *frame)
{

    if(recording){

    }
    int ret;

    /* send the frame to the encoder */
    if (frame)
        printf("Send frame %3\n", frame->pts);

    ret = avcodec_send_frame(ctx, frame);
    if (ret < 0) {
        fprintf(stderr, "Error sending a frame for encoding\n");
        exit(1);
    }

    while (ret >= 0) {
        ret = avcodec_receive_packet(ctx, pkt);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
            return;
        else if (ret < 0) {
            fprintf(stderr, "Error during encoding\n");
            exit(1);
        }

        printf("Write packet %3 (size=%5d)\n", pkt->pts, pkt->size);

        fwrite(pkt->data,1,pkt->size, file_output);
        av_packet_unref(pkt);

    }

}

void VideoRecorder::setOutputLocation(QUrl &output)
{
     filename = output.toLocalFile();

}

void VideoRecorder::setFormat(QString encoder, int w, int h, int fps, int bitrate)
{
    this->codec_name = encoder;
    this->width = w;
    this->height = h;
    this->fps = fps;
    this->bitrate = bitrate;
}

void VideoRecorder::start()
{
    int ret;

    codec = avcodec_find_encoder_by_name(codec_name.toStdString().c_str());

    if (!codec) {

        qDebug()<<"Codec not found : "<<codec_name;

        exit(1);
    }

    ctx = avcodec_alloc_context3(codec);
    if (!ctx) {
        fprintf(stderr, "Could not allocate video codec context\n");
        exit(1);
    }

    pkt = av_packet_alloc();
    if (!pkt)
        exit(1);

    ctx->bit_rate = this->bitrate;

    /* resolution must be a multiple of two */
    ctx->width = 352;
    ctx->height = 288;
    /* frames per second */
//    ctx->time_base = (AVRational){1, 25};
 //   ctx->framerate = (AVRational){25, 1};

    /* emit one intra frame every ten frames
     * check frame pict_type before passing frame
     * to encoder, if frame->pict_type is AV_PICTURE_TYPE_I
     * then gop_size is ignored and the output of encoder
     * will always be I frame irrespective to gop_size
     */
    ctx->gop_size = 10;
    ctx->max_b_frames = 1;
    ctx->pix_fmt = AV_PIX_FMT_YUV420P;

    if (codec->id == AV_CODEC_ID_H264)
        av_opt_set(ctx->priv_data, "preset", "fast", 0);

    /* open it */
    ret = avcodec_open2(ctx, codec, NULL);
    if (ret < 0) {
       // fprintf(stderr, "Could not open codec: %s\n", av_err2str(ret));
        exit(1);
    }

    file_output = fopen(filename.toStdString().c_str(), "wb");
    if (!file_output) {
//        fprintf(stderr, "Could not open %s\n", filename);
        qDebug()<<"Could not open : "<< filename;
        exit(1);

    }


    recording = true;


}

void VideoRecorder::stop()
{


    uint8_t endcode[] = { 0, 0, 1, 0xb7 };


    /* flush the encoder */
    encode(NULL);

    /* add sequence end code to have a real MPEG file */
    if (codec->id == AV_CODEC_ID_MPEG1VIDEO || codec->id == AV_CODEC_ID_MPEG2VIDEO)
        fwrite(endcode, 1, sizeof(endcode), file_output);
    fclose(file_output);

    avcodec_free_context(&ctx);
    av_packet_free(&pkt);


    recording = false;

}

void VideoRecorder::pause()
{

    recording = false;
}

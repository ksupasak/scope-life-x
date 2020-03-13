#include "settingcontroller.h"
#include "ui_settingcontroller.h"
#include "qmessagebox.h"
SettingController::SettingController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingController)
{
    ui->setupUi(this);
}

SettingController::~SettingController()
{
    delete ui;
}

CoreLib *SettingController::getCore() const
{
    return core;
}

void SettingController::setCore(CoreLib *value)
{
    core = value;
}

void SettingController::load()
{
    core->loadConfig();



    ui->system_mode->setText(core->getStringValue("system_mode"));
    ui->system_name->setText(core->getStringValue("system_name"));
    ui->system_host->setText(core->getStringValue("system_host"));
    ui->system_title->setText(core->getStringValue("system_title"));
    ui->system_mode->setText(core->getStringValue("system_mode"));
    ui->system_startup->setText(core->getStringValue("system_startup"));

    ui->input_source_1->setText(core->getStringValue("input_source_1"));
    ui->input_source_2->setText(core->getStringValue("input_source_2"));

    ui->image_path->setText(core->getStringValue("image_path"));
    ui->image_resolution->setText(core->getStringValue("image_resolution"));
    ui->image_quality->setText(core->getStringValue("image_quality"));
    ui->image_crop->setText(core->getStringValue("image_crop"));

    ui->video_path->setText(core->getStringValue("video_path"));
    ui->video_resolution->setText(core->getStringValue("video_resolution"));
    ui->video_codec->setText(core->getStringValue("video_codec"));
    ui->video_record_limit->setText(core->getStringValue("video_record_limit"));
    ui->video_record_auto->setText(core->getStringValue("video_record_auto"));

    ui->timer_1_title->setText(core->getStringValue("timer_1_title"));
    ui->timer_1_key->setText(core->getStringValue("timer_1_key"));
    ui->timer_2_title->setText(core->getStringValue("timer_2_title"));
    ui->timer_2_key->setText(core->getStringValue("timer_2_key"));

}

void SettingController::save()
{

    core->setValue("system_mode", ui->system_mode->text());
    core->setValue("system_name", ui->system_name->text());
    core->setValue("system_host", ui->system_host->text());
    core->setValue("system_title", ui->system_title->text());
    core->setValue("system_startup", ui->system_startup->text());

    core->setValue("input_source_1", ui->input_source_1->text());
    core->setValue("input_source_2", ui->input_source_2->text());


    core->setValue("image_path", ui->image_path->text());
    core->setValue("image_resolution", ui->image_resolution->text());
    core->setValue("image_quality", ui->image_quality->text());
    core->setValue("image_crop", ui->image_crop->text());

    core->setValue("video_path", ui->video_path->text());
    core->setValue("video_resolution", ui->video_resolution->text());
    core->setValue("video_codec", ui->video_codec->text());
    core->setValue("video_record_limit", ui->video_record_limit->text());
    core->setValue("video_record_auto", ui->video_record_auto->text());

    core->setValue("timer_1_title", ui->timer_1_title->text());
    core->setValue("timer_1_key", ui->timer_1_key->text());
    core->setValue("timer_2_title", ui->timer_2_title->text());
    core->setValue("timer_2_key", ui->timer_2_key->text());




    core->saveConfig();
}

void SettingController::reset()
{

}

void SettingController::on_save_btn_clicked()
{
    this->save();
}

void SettingController::on_load_btn_clicked()
{
    this->load();
}

void SettingController::on_quit_btn_clicked()
{
    if(core->getStringValue("system_startup").compare("window")==0){
        QMessageBox msgBox;
        msgBox.setText("Quit");
        msgBox.setInformativeText("Exit with Save?");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Ok){
            this->save();
            exit(0);
        }
        if(ret == QMessageBox::Discard){
            exit(0);
        }
    }else{
        this->save();
        exit(0);
    }

}

void SettingController::on_reset_btn_clicked()
{
    emit back();
}

#ifndef SETTINGCONTROLLER_H
#define SETTINGCONTROLLER_H

#include <QWidget>
#include "corelib.h"
#include "ScopeLifeGUI_global.h"

namespace Ui {
class SettingController;
}

class SCOPELIFEGUI_EXPORT SettingController : public QWidget
{
    Q_OBJECT

public:
    explicit SettingController(QWidget *parent = nullptr);
    ~SettingController();

    CoreLib *getCore() const;
    void setCore(CoreLib *value);


    void load();

    void save();

    void reset();

signals:

    void back();


private slots:
    void on_save_btn_clicked();

    void on_load_btn_clicked();

    void on_quit_btn_clicked();

    void on_reset_btn_clicked();

private:
    Ui::SettingController *ui;
    CoreLib* core;

};

#endif // SETTINGCONTROLLER_H

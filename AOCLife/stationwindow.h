#ifndef STATIONWINDOW_H
#define STATIONWINDOW_H

#include <QMainWindow>

namespace Ui {
class StationWindow;
}

class StationWindow : public QMainWindow
{
    Q_OBJECT

public:
     StationWindow(QWidget *parent = nullptr);
    ~StationWindow();
    void setUrl(QUrl &url);
private:
    Ui::StationWindow *ui;
};

#endif // STATIONWINDOW_H

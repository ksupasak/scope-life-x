#ifndef HIDPEDAL_H
#define HIDPEDAL_H

#include "libusb.h"
#include <QObject>
#include "ScopeLifeHW_global.h"


class SCOPELIFEHW_EXPORT HIDPedal : public QObject
{
    Q_OBJECT

public:
    HIDPedal(QObject *parent);
    int start();

signals:

    void key(int k);

private:
    int vid;
    int pid;


};

#endif // HIDPEDAL_H

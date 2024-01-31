#ifndef ADDRCDEVICE_H
#define ADDRCDEVICE_H

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QCheckBox>
#include <QLabel>
#include <QFont>
#include <QMap>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QByteArray>
#include <QJsonObject>
#include "httpclinet.h"
#include "common.h"
#include "util.h"
#include <QJsonDocument>
#include <QFile>
#include <QDir>
#include <QGridLayout>
#include <QJsonArray>



namespace Ui {
class AddRCDevice;
}

class AddRCDevice : public QWidget
{
    Q_OBJECT

public:
    explicit AddRCDevice(QWidget *parent = nullptr);
    ~AddRCDevice();
    void init();
    void connectevent();
    void addTimeCks(QList<QCheckBox *> &timecks,QGridLayout &timeset,QWidget *w);

signals:
    void sendFinished(bool);


public slots:
    void onAdd();

private:
    Ui::AddRCDevice *ui;
    QFont ckFont;
    QList<QCheckBox *> timecks;
    QList<QCheckBox *> typecks;
    QMap<QString,QStringList> selckMap;
    QStringList portsList;
    QStringList cmdlist;
    QGridLayout al1,al2,al3,al4;
    QMap<QString,QString> facnameMap;
    Util util;
    httpclinet pClient;
    QString cmdinfofile;

};

#endif // ADDRCDEVICE_H
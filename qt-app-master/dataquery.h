#ifndef DATAQUERY_H
#define DATAQUERY_H

#include <QWidget>
#include <QStackedWidget>
#include <QDebug>
#include "httpclient.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QMap>
#include <QString>
#include <QList>
#include <QMessageBox>
#include <QFont>
#include <QStringList>


#include "common.h"


namespace Ui {
class DataQuery;
}

class DataQuery : public QWidget
{
    Q_OBJECT

public:
    explicit DataQuery(QStringList names,QWidget *parent = nullptr);
    ~DataQuery();
    void init();
    void connectevent();
    void getFactors();
    void getCommonFactors();
    void getUpsetAddr();

    void query_rtk();
    void query_min();
    void query_hour();
    void query_day();
    void query_month();
    void query_trans();

    void fillinTable_rtk(QJsonObject &resObj,QTableWidget * table = nullptr);
    void fillinTable_unrtk(QJsonObject &resObj,QTableWidget * table = nullptr);

signals:

public slots:
    void onQuery();
    void onExport();
    void onReceiveFac(QString facname);

private:
    Ui::DataQuery *ui;
    QJsonObject fullFactorsInfo;
    QJsonObject fullDevicesInfo;
    QStringList names;
};

#endif // DATAQUERY_H
#ifndef RCLOGDLG_H
#define RCLOGDLG_H

#include <QWidget>
#include <QTextBrowser>
#include <QString>
#include <QDebug>
#include <QDateTime>

namespace Ui {
class RCLogDlg;
}

class RCLogDlg : public QWidget
{
    Q_OBJECT

public:
    explicit RCLogDlg(QString str,QWidget *parent = nullptr);
    ~RCLogDlg();
    void init();
    void connectevent();

public slots:
    void onSlotLog(QString str);

private:
    Ui::RCLogDlg *ui;
    QString curStr;
};

#endif // RCLOGDLG_H
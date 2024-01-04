#include "upsetadd.h"
#include "ui_upsetadd.h"

UpsetAdd::UpsetAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpsetAdd)
{
    ui->setupUi(this);
    setModal(true);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle(QStringLiteral(" "));

    ui->comboBox->setEditable(true);

    ui->checkBox->setStyleSheet("QCheckBox{spacing: 8px;}QCheckBox::indicator{width: 60px;height: 30px;} QCheckBox::indicator:unchecked {image: url(:/images/Off.png);} QCheckBox::indicator:checked {image: url(:/images/On.png);}");
    ui->checkBox_2->setStyleSheet("QCheckBox{spacing: 8px;}QCheckBox::indicator{width: 60px;height: 30px;} QCheckBox::indicator:unchecked {image: url(:/images/Off.png);} QCheckBox::indicator:checked {image: url(:/images/On.png);}");

    UpAdd_filled();
}

UpsetAdd::~UpsetAdd()
{
    delete ui;
}

void UpsetAdd::UpAdd_filled()
{
    QJsonArray pJsonArray;
    httpclinet pClient;
    if(pClient.get(DCM_MNINFO,pJsonArray))
    {
        for(int i=0;i<pJsonArray.size();i++)  //获得总数据的个数 做个循环来处理每条数据
        {
            QJsonValue iconArray = pJsonArray.at(i);
            QJsonObject icon = iconArray.toObject();
            ui->comboBox->addItem(icon[QLatin1String("mn")].toString());
        }
    }
}

void UpsetAdd::on_pushButton_confirm_clicked()
{
    // add
    QJsonObject obj;

    int is_open_heartbeat = ui->checkBox->isChecked() ? 1 : 0;
    int is_send_rtd = ui->checkBox_2->isChecked()? 1:0;
    //合法性判断
    if(ui->comboBox->currentText().isEmpty()){
        QMessageBox::about(NULL, "提示", "<font color='black'>MN不能为空!</font>");
        return;
    }
    if(ui->lineEdit_addr->text().isEmpty()){
        QMessageBox::about(NULL, "提示", "<font color='black'>IP不能为空!</font>");
        return;
    }
    if(ui->lineEdit_pw->text().isEmpty()){
        QMessageBox::about(NULL, "提示", "<font color='black'>IP不能为空!</font>");
        return;
    }
    if(ui->lineEdit_upload_intval->text().isEmpty()){
        QMessageBox::about(NULL, "提示", "<font color='black'>上传间隔不能为空!</font>");
        return;
    }
    if(is_open_heartbeat && ui->lineEdit_hi->text().isEmpty()){
        QMessageBox::about(NULL, "提示", "<font color='black'>心跳间隔不能为空!</font>");
        return;
    }
    if(ui->lineEdit_min->text().isEmpty()){
        QMessageBox::about(NULL, "提示", "<font color='black'>分钟数据间隔不能为空!</font>");
        return;
    }
    if(ui->lineEdit_retry->text().isEmpty()){
        QMessageBox::about(NULL, "提示", "<font color='black'>重试次数不能为空!</font>");
        return;
    }
    if(ui->lineEdit_To->text().isEmpty()){
        QMessageBox::about(NULL, "提示", "<font color='black'>发送超时不能为空!</font>");
        return;
    }

    obj.insert(QLatin1String("mn"), ui->comboBox->currentText());
    obj.insert(QLatin1String("ip_addr_port"), ui->lineEdit_addr->text());
    obj.insert(QLatin1String("interval_upload"), ui->lineEdit_upload_intval->text().toInt());
    obj.insert(QLatin1String("interval_minute_data_upload"), ui->lineEdit_min->text().toInt());
    obj.insert(QLatin1String("is_open_heartbeat"), is_open_heartbeat);
    obj.insert(QLatin1String("interval_heartbeat"), ui->lineEdit_hi->text().toInt());
    obj.insert(QLatin1String("pw"), ui->lineEdit_pw->text());
    obj.insert(QLatin1String("is_send_rtd"), is_send_rtd);
    obj.insert(QLatin1String("over_time"), ui->lineEdit_To->text().toInt());
    obj.insert(QLatin1String("resend_times"), ui->lineEdit_retry->text().toInt());
    obj.insert(QLatin1String("protocol_version"), ui->comboBox_2->currentText());

    obj.insert(QLatin1String("id"), "");

    // qDebug() << "obj==>>" << obj;

    httpclinet pClient;
    if(pClient.put(DCM_MNINFO,obj))
    {
        QMessageBox::about(NULL, "提示", "<font color='black'>新增上传配置成功！</font>");
        this->close();
        return;
    }
    else
    {
        QMessageBox::about(NULL, "提示", "<font color='black'>新增上传配置失败！</font>");
    }
}

void UpsetAdd::on_pushButton_cancel_clicked()
{
    this->close();
}
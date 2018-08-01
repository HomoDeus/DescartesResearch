
#include "ForceCurveWidget.h"
#include <FTSensorMonitor.h>
#include <Eigen/Eigen>
#include <iostream>
FTSensorMonitor::FTSensorMonitor(){
    initWidget();
    _device =new DeviceDriver();
    connect(_device,&DeviceDriver::forceUpdated,[=](Eigen::Matrix<double,6,1> wrench){
//        std::cout<<"_origData:"<<wrench.adjoint()<<"\n";
        _currentWrench=wrench;
        _record[6]=wrench(0);
        _record[7]=wrench(1);
        _record[8]=wrench(2);
        _record[9]=wrench(3);
        _record[10]=wrench(4);
        _record[11]=wrench(5);
    });

    ui->forceCurveWidget->StartPainting();
    QTimer* timer=new QTimer(this);
    connect(timer,&QTimer::timeout,[=](){
        addRecord();
    });
    timer->start(10);
}

FTSensorMonitor::~FTSensorMonitor() {

}

void FTSensorMonitor::initWidget() {

    ui = new Ui::FTSensorMonitorWidget();
    ui->setupUi(this);
    ui->probeSlide->setRange(0,0);

    connect(ui->btn_reset,&QPushButton::released,[=](){
        ui->probeSlide->setRange(0,0);
        ui->lbl_counts->setText(QString::number(0));
    });

    connect(ui->btn_connect,&QPushButton::released,[=](){
        _device->start(ui->lEdit_IP->text(),ui->lEdit_Port->text().toInt());
        ui->btn_disconnect->setEnabled(true);
        ui->btn_connect->setEnabled(false);
    });
    connect(ui->btn_disconnect,&QPushButton::released,[=](){
       _device->stop();
        ui->btn_connect->setEnabled(true);
        ui->btn_disconnect->setEnabled(false);
    });

    connect(ui->PPoint_x,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged)
            ,this,&FTSensorMonitor::updatePolishPoint);
    connect(ui->PPoint_y,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged)
            ,this,&FTSensorMonitor::updatePolishPoint);
    connect(ui->PPoint_z,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged)
            ,this,&FTSensorMonitor::updatePolishPoint);
    connect(ui->PPoint_roll,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged)
            ,this,&FTSensorMonitor::updatePolishPoint);
    connect(ui->PPoint_pitch,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged)
            ,this,&FTSensorMonitor::updatePolishPoint);
    connect(ui->PPoint_yaw,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged)
            ,this,&FTSensorMonitor::updatePolishPoint);

}

void FTSensorMonitor::updatePolishPoint(){
    auto x=ui->PPoint_x->value()/1000.0;
    auto y=ui->PPoint_y->value()/1000.0;
    auto z=ui->PPoint_z->value()/1000.0;
    auto roll=ui->PPoint_roll->value()/180.0*M_PI;
    auto pitch=ui->PPoint_pitch->value()/180.0*M_PI;
    auto yaw=ui->PPoint_yaw->value()/180.0*M_PI;

}
void FTSensorMonitor::addRecord() {
    auto wrench=_device->getWrench();
    ui->forceCurveWidget->AddData(wrench);
}



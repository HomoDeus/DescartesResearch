//
// Created by 杨帆 on 18-1-15.
//
//

#ifndef PROJECT_DEVICE_DRIVER_H
#define PROJECT_DEVICE_DRIVER_H


#include <QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QTimer>
#include "Eigen/Eigen"

class DeviceDriver :
    public QObject{
    Q_OBJECT
public:
	DeviceDriver();
	~DeviceDriver();
	void start(QString address,quint16 port);
	void stop();

	Eigen::Matrix<double,6,1> getWrench(){ return _origData;}

signals:
    void forceUpdated(Eigen::Matrix<double,6,1> wrench);

private:
	QTcpSocket* _tcpSocket;
	QTimer* _timer;
    Eigen::Matrix<double,6,1> _origData;//力传感器采集到的原始数据

    bool _robotReady;
    bool _ftsensorReady;
    bool _calibMode;
};

#endif //PROJECT_DEVICE_DRIVER_H

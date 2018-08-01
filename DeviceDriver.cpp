//
// Created by 杨帆 on 17-4-18.
//
//

#include "DeviceDriver.h"

#include <QTimer>
#include <iostream>

DeviceDriver::DeviceDriver(){
	_robotReady=false;
	_ftsensorReady=false;
    _calibMode=false;
	_tcpSocket = new QTcpSocket(this);
	_tcpSocket->setSocketOption(QAbstractSocket::LowDelayOption, 1);



	_timer = new QTimer();
	connect(_timer,&QTimer::timeout,[=](){
		if(_tcpSocket->isWritable()){
			_tcpSocket->write((char *)"R", 1);
		}
		//only for demo --sail;
        static double val=0.0;
        _origData(0)=std::sin(val);
        _origData(1)=std::cos(val);
        _origData(2)=2*std::sin(val);
        _origData(3)=2*std::cos(val);
        _origData(4)=4*std::sin(val);
        _origData(5)=4*std::cos(val);
        Q_EMIT forceUpdated(_origData);
        val+=0.01;
	});
    //only for demo --sail;
    _timer->start(10);
	connect(_tcpSocket, &QTcpSocket::readyRead,[=](){
		_robotReady=true;
		auto ba = _tcpSocket->readAll();
		if (ba.size()==27) {
			QString list1;
			QString list;
			QByteArray barr;
			double dat[6];
			bool ok;

			for(int ii=0;ii<6;ii++){
				barr=ba.mid(1+ii*4,4);
				if(ii<3){
					dat[ii]=(double)(barr.toInt(&ok,16)-8192)/32.765;
				}else{
					dat[ii]=(double)(barr.toInt(&ok,16)-8192)/1638.25;
				}

				list1=list1.append(barr).append(" ");
				list=list.append(QString::number(dat[ii])).append(" ");
			}

			for(int ii=0;ii<6;ii++){
				_origData(ii)=dat[ii];
			}

			Q_EMIT forceUpdated(_origData);
		}
	});

	connect(_tcpSocket, &QTcpSocket::connected,[=](){
		std::cout<<"DeviceDriver"<<"Robot is connected";
		if(_tcpSocket->isWritable()){
			_tcpSocket->write((char *)"V", 1);
		}
		_timer->start(10);
	});

	connect(_tcpSocket, &QTcpSocket::disconnected,[=](){
		_robotReady=false;
		std::cout<<"DeviceDriver"<<"Robot is disconnected";
	});


}

DeviceDriver::~DeviceDriver() {

}

void DeviceDriver::start(QString address,quint16 port) {
    if(_tcpSocket){
		std::cout<<"DeviceDriver"<<"address "<<address.toStdString()<<" port "<<port;
        _tcpSocket->connectToHost(address, port);
    }

}

void DeviceDriver::stop() {

    if (_tcpSocket->isOpen()) {
		_timer->stop();
        _tcpSocket->close();

    }
}


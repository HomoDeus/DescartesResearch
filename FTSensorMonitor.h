#ifndef FTSENSOR_MONITOR_WIDGET_H_
#define FTSENSOR_MONITOR_WIDGET_H_

#include "ui_FTSensorMonitorWidget.h"
#include "DeviceDriver.h"
#include <Eigen/Eigen>
class FTSensorMonitor: public QWidget
{
    Q_OBJECT
public:
	FTSensorMonitor( );
    ~FTSensorMonitor();
    void initWidget();
    void addRecord();

private:
    void updatePolishPoint();
    class Ui::FTSensorMonitorWidget *ui;

	DeviceDriver* _device;
    Eigen::Matrix<double,12,1> _record;
    QList<std::vector<double> > _samples;

    Eigen::Matrix<double,6,1> _currentWrench;
    Eigen::Matrix<double,6,1> _upWrench;
    Eigen::Matrix<double,6,1> _downWrench;
    Eigen::Matrix<double,6,1> _lampWrench;

    bool _robotReady;
    bool _ftsensorReady;
};

#endif //FTSENSOR_MONITOR_WIDGET_H_

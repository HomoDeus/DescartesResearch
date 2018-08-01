//
// Created by 杨帆 on 17-4-18.
//
//

#include "ForceCurveWidget.h"
#include "QTime"
#include "QApplication"
#include <qwt_legend.h>
#include "iostream"
#include "QVBoxLayout"

ForceCurveWidget::ForceCurveWidget(QWidget* parent) {
    this->maximumSize = 5000;
    this->updated = false;
    for(size_t i = 0; i < maximumSize; i++)
    {
        this->xdata.push_back(i * 1.0f);
    }

    setupUi(this);
}

ForceCurveWidget::~ForceCurveWidget(){
    delete cb_x;
    delete cb_y;
    delete cb_z;
    delete cb_R;
    delete cb_P;
    delete cb_Y;
    delete updateTimer;
    delete curveX;
    delete curveY;
    delete curveZ;
    delete curveR;
    delete curveP;
    delete curve_Y;
    delete plot;
}

void ForceCurveWidget::resizeEvent(QResizeEvent *size) {
    this->plot->setGeometry(50, 50, this->width()-150, this->height() - 70);
    this->cb_x->setGeometry(10, 100, 85, 21);
    this->cb_y->setGeometry(10, 120, 85, 21);
    this->cb_z->setGeometry(10, 140, 85, 21);
    this->cb_R->setGeometry(10, 160, 85, 21);
    this->cb_P->setGeometry(10, 180, 85, 21);
    this->cb_Y->setGeometry(10, 200, 85, 21);
}

void ForceCurveWidget::setupUi(QWidget *widget)
{
    widget->resize(589, 378);
    widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    cb_x = new QCheckBox(widget);
    cb_x->setObjectName(QString::fromUtf8("cb_x"));
    cb_x->setGeometry(QRect(440, 50, 85, 21));
    cb_x->setChecked(true);

    cb_y = new QCheckBox(widget);
    cb_y->setObjectName(QString::fromUtf8("cb_y"));
    cb_y->setGeometry(QRect(440, 80, 85, 21));
    cb_y->setChecked(true);

    cb_z = new QCheckBox(widget);
    cb_z->setObjectName(QString::fromUtf8("cb_z"));
    cb_z->setGeometry(QRect(440, 110, 85, 21));
    cb_z->setChecked(true);

    cb_R = new QCheckBox(widget);
    cb_R->setObjectName(QString::fromUtf8("cb_R"));
    cb_R->setGeometry(QRect(440, 140, 85, 21));
    cb_R->setChecked(true);

    cb_P = new QCheckBox(widget);
    cb_P->setObjectName(QString::fromUtf8("cb_Y"));
    cb_P->setGeometry(QRect(440, 170, 85, 21));
    cb_P->setChecked(true);

    cb_Y = new QCheckBox(widget);
    cb_Y->setObjectName(QString::fromUtf8("cb_Y_2"));
    cb_Y->setGeometry(QRect(440, 200, 85, 21));
    cb_Y->setChecked(true);

    plot = new QwtPlot(widget);
    plot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    plot->setGeometry(QRect(60, 30, 371, 320));

    plot->setCanvasBackground(Qt::gray);//背景
    plot->insertLegend(new QwtLegend(),QwtPlot::RightLegend);
    plot->setAxisTitle(QwtPlot::xBottom, "System Time");
    plot->setAxisTitle(QwtPlot::yLeft,"Force");
    plot->setAxisAutoScale(QwtPlot::yLeft, true);
    this->plot->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);

    this->curveX = new QwtPlotCurve();
    curveX->setTitle("X");//曲线名字
    curveX->setPen( Qt::yellow, 1 );//曲线的颜色 宽度;

    this->curveY = new QwtPlotCurve();
    curveY->setTitle("Y");//曲线名字
    curveY->setPen( Qt::red, 1 );//曲线的颜色 宽度;

    this->curveZ = new QwtPlotCurve();
    curveZ->setTitle("Z");//曲线名字
    curveZ->setPen( Qt::green, 1 );//曲线的颜色 宽度;

    this->curveR = new QwtPlotCurve();
    curveR->setTitle("R");//曲线名字
    curveR->setPen( Qt::blue, 1 );//曲线的颜色 宽度;

    this->curveP = new QwtPlotCurve();
    curveP->setTitle("P");//曲线名字
    curveP->setPen( Qt::black, 1 );//曲线的颜色 宽度;

    this->curve_Y = new QwtPlotCurve();
    curve_Y->setTitle("_Y");//曲线名字
    curve_Y->setPen(Qt::gray, 1 );//曲线的颜色 宽度;
    this->updateTimer = new QTimer;
    connect(updateTimer,SIGNAL(timeout()), this, SLOT(updateDataSlot()));

    retranslateUi(widget);

    QMetaObject::connectSlotsByName(widget);
}

void ForceCurveWidget::StartPainting() {
    this->updateTimer->setInterval(100);
    this->updateTimer->start();
}

void ForceCurveWidget::StopPainting() {
    this->updateTimer->stop();
}

double ForceCurveWidget::getData(double degree){

    return qCos( degree / 180.0f * M_PI * 2 ) ;
}

void ForceCurveWidget::SetLabels(std::vector<std::string> labels){
//    curveX->setTitle(labels[0].c_str());//曲线名字
//    curveY->setTitle(labels[1].c_str());//曲线名字
//    curveZ->setTitle(labels[2].c_str());//曲线名字
//    curveR->setTitle(labels[3].c_str());//曲线名字
//    curveP->setTitle(labels[4].c_str());//曲线名字
//    curve_Y->setTitle(labels[5].c_str());//曲线名字
//
//    cb_x->setText(QApplication::translate("Form", labels[0].c_str(), 0));
//    cb_y->setText(QApplication::translate("Form", labels[1].c_str(), 0));
//    cb_z->setText(QApplication::translate("Form", labels[2].c_str(), 0));
//    cb_R->setText(QApplication::translate("Form", labels[3].c_str(), 0));
//    cb_P->setText(QApplication::translate("Form", labels[4].c_str(), 0));
//    cb_Y->setText(QApplication::translate("Form", labels[5].c_str(), 0));
}

void ForceCurveWidget::AddData(Eigen::Matrix<double,6,1> forces) {

    this->queueMutex.lock();
    this->ydata.push_back(forces);
    if(this->ydata.size() > maximumSize)
    {
        this->ydata.pop_front();
    }
    this->queueMutex.unlock();

    this->updateMutex.lock();
    this->updated = true;
    this->updateMutex.unlock();
}

void ForceCurveWidget::ShowCurve(QwtPlotCurve *curve, int dataIndex, bool visible) {
    if(visible)
    {
        std::vector<double> axleData;
        for(size_t i = 0; i < ydata.size(); i++)
        {
            axleData.push_back(ydata[i][dataIndex]);
        }

        curve->setSamples(&xdata[0], &axleData[0], axleData.size());
        curve->attach(plot);
        curve->show();
    }
    else
    {
        curve->hide();
    }
}

void ForceCurveWidget::updateDataSlot() {
    this->updateMutex.lock();
    if(!this->updated)
    {
        this->updateMutex.unlock();
        Eigen::Matrix<double,6,1> forces(6, 0);
        this->AddData(forces);
    }
    else
    {
        this->updateMutex.unlock();
    }

    this->updateMutex.lock();
    this->updated = false;
    this->updateMutex.unlock();

    this->queueMutex.lock();
    this->ShowCurve(this->curveX, 0, this->cb_x->isChecked());
    this->ShowCurve(this->curveY, 1, this->cb_y->isChecked());
    this->ShowCurve(this->curveZ, 2, this->cb_z->isChecked());
    this->ShowCurve(this->curveR, 3, this->cb_R->isChecked());
    this->ShowCurve(this->curveP, 4, this->cb_P->isChecked());
    this->ShowCurve(this->curve_Y, 5, this->cb_Y->isChecked());
    this->queueMutex.unlock();
    plot->replot();
}


void ForceCurveWidget::retranslateUi(QWidget *widget)
{
    widget->setWindowTitle(QApplication::translate("Form", "Form", 0));
    cb_x->setText(QApplication::translate("Form", "X", 0));
    cb_y->setText(QApplication::translate("Form", "Y", 0));
    cb_z->setText(QApplication::translate("Form", "Z", 0));
    cb_R->setText(QApplication::translate("Form", "R", 0));
    cb_P->setText(QApplication::translate("Form", "P", 0));
    cb_Y->setText(QApplication::translate("Form", "Y", 0));
} // retranslateUi

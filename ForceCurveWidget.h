//
// Created by 杨帆 on 17-4-18.
//
//
#ifndef FORCECURVEWIDGET_H
#define FORCECURVEWIDGET_H

#include <QAction>
#include <QButtonGroup>
#include <QCheckBox>
#include <QWidget>
#include <qwt_plot.h>

#include <qwt_plot_curve.h>
#include <QTimer>
#include <deque>
#include <QMutex>
#include <Eigen/Eigen>

    class ForceCurveWidget : public QWidget
    {
    Q_OBJECT
    public:
        ForceCurveWidget(QWidget* parent = nullptr);
        virtual ~ForceCurveWidget();
        void StartPainting();
        void StopPainting();
        void SetLabels(std::vector<std::string> labels);
        void AddData(Eigen::Matrix<double,6,1> forces);
    private:
        void setupUi(QWidget *widget);
        void retranslateUi(QWidget *widget);
        void ShowCurve(QwtPlotCurve *curve, int dataIndex, bool visible);
        void resizeEvent(QResizeEvent* size);
        double getData(double inteval);
    private slots:
        void updateDataSlot();

    private:
        QCheckBox *cb_x;
        QCheckBox *cb_y;
        QCheckBox *cb_z;
        QCheckBox *cb_R;
        QCheckBox *cb_P;
        QCheckBox *cb_Y;
        QTimer* updateTimer;
        QwtPlotCurve *curveX;
        QwtPlotCurve *curveY;
        QwtPlotCurve *curveZ;
        QwtPlotCurve *curveR;
        QwtPlotCurve *curveP;
        QwtPlotCurve *curve_Y;
        QwtPlot *plot;
        std::vector<double> xdata;
        std::deque<Eigen::Matrix<double,6,1>> ydata;
        size_t maximumSize = 20;
        QMutex updateMutex;
        QMutex queueMutex;
        bool updated;
    };



#endif // FORCECURVEWIDGET_H

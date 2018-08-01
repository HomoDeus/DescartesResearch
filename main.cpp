#include "FTSensorMonitor.h"
#include <QApplication>

int main(int argc, char** argv) {

    QApplication a(argc, argv);
    FTSensorMonitor mainWindow;
    mainWindow.resize( 1200, 600 );
    mainWindow.show();
//    mainWindow.showFullScreen();
    return a.exec();
}
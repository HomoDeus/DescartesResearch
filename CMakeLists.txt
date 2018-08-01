project(FTSensorMonitor)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} $ENV{QT5_INSTALL_PATH})
# 貌似如果使用AUTOMOC，需要把Qt5Core这个引用进来。这个find_package是必须的。
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED) # Fuck, 如果要使用autouic那么必须引用这个Qt5Widgets.
find_package(Qt5Network REQUIRED)

SET(GLOB UIS_FILES *.ui)
# if we want to use ui files add them here
QT5_WRAP_UI(UIS_OUT_H ${UIS_FILES})



include_directories(qwt/include)
include_directories(eigen3)

link_libraries(${CMAKE_SOURCE_DIR}/qwt/lib)

file(GLOB ${PROJECT_NAME}_files *.cpp *.h ${UIS_OUT_H})

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_files})

target_link_libraries(${PROJECT_NAME}  Qt5::Widgets Qt5::Network Qt5::Core ${CMAKE_SOURCE_DIR}/qwt/lib/libqwt.so)



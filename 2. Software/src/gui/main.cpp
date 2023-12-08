#include "MainWindow.h"
#include <QApplication>


int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/robotic-arm.png"));

    MainWindow w;
    w.show();

    return a.exec();
}

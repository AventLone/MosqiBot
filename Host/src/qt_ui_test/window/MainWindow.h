#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
// #include <QProcess>
#include <cv_bridge/cv_bridge.h>
// #include <my_interface/srv/clean_up.hpp>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/bool.hpp>
#include <std_msgs/msg/byte.hpp>

#include <thread>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum Command : unsigned char
    {
        FAN_ON,
        FAN_OFF,
        MOSQUITO_KILLER_ON,
        MOSQUITO_KILLER_OFF,
        OUTLET_OPEN,
        OUTLET_CLOSE,
        START_SHOOT
    };

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:   // Member variable
    Ui::MainWindow* ui;
    //    QProcess* mosqibot_process{nullptr};

    std::thread mythread;

    /*** ROS2 part ***/
    std::shared_ptr<rclcpp::Node> node;

    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr target_img_sub;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr heap_img_sub;
    rclcpp::Publisher<std_msgs::msg::Byte>::SharedPtr mCommandPublisher;


private:   // Member function
    void runningStatusCallback(const std_msgs::msg::Bool::ConstSharedPtr msg);
    void target_img_sub_callback(const sensor_msgs::msg::Image::ConstSharedPtr msg);
    void heap_img_sub_callback(const sensor_msgs::msg::Image::ConstSharedPtr msg);

    void spinNode();

    // void cleanupClient_callback(rclcpp::Client<my_interface::srv::CleanUp>::SharedFuture result);

signals:
    void displayTargetImg(const QImage& img);
    void displayHeapImg(const QImage& img);

private slots:
    void on_displayTargetImg(const QImage& img);
    void on_displayHeapImg(const QImage& img);

    void on_pushButton_fan_on_clicked();
    void on_pushButton_fan_off_clicked();
    void on_pushButton_killer_on_clicked();
    void on_pushButton_killer_off_clicked();
    void on_pushButton_outlet_on_clicked();
    void on_pushButton_outlet_off_clicked();
    void on_pushButton_start_shoot_clicked();
};

#endif   // MAINWINDOW_H

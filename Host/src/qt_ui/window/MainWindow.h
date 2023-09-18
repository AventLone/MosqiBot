#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <cv_bridge/cv_bridge.h>
#include <my_interface/srv/clean_up.hpp>
#include <rclcpp/rclcpp.hpp>
// #include <std_msgs/msg/string.hpp>
#include <std_msgs/msg/bool.hpp>

#include <thread>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:   // Member variable
    Ui::MainWindow* ui;
    QProcess* mosqibot_process = nullptr;

    std::thread mythread;

    /*** ROS2 part ***/
    std::shared_ptr<rclcpp::Node> node = nullptr;

    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr target_img_sub = nullptr;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr heap_img_sub = nullptr;

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

    void on_pushButton_on_clicked();
    void on_pushButton_off_clicked();
};

#endif   // MAINWINDOW_H

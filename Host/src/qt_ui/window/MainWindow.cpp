#include "MainWindow.h"
#include "../ui/ui_MainWindow.h"
// #include "WaitDialog.h"
#include <QBitmap>
// #include <QCursor>
// #include <QGuiApplication>
#include <QMessageBox>
#include <QPainter>
#include <QScreen>
#include <QThread>
#include <QToolButton>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mosqibot_process = new QProcess();
    connect(this, SIGNAL(displayTargetImg(QImage)), this, SLOT(on_displayTargetImg(QImage)));
    connect(this, SIGNAL(displayHeapImg(QImage)), this, SLOT(on_displayHeapImg(QImage)));

    node = std::make_shared<rclcpp::Node>("mosqibot_qt");
    target_img_sub = node->create_subscription<sensor_msgs::msg::Image>(
        "MosqiBot/target_img", 10, std::bind(&MainWindow::target_img_sub_callback, this, std::placeholders::_1));
    heap_img_sub = node->create_subscription<sensor_msgs::msg::Image>(
        "MosqiBot/heap_img", 10, std::bind(&MainWindow::heap_img_sub_callback, this, std::placeholders::_1));

    mythread = std::thread(&MainWindow::spinNode, this);
}

MainWindow::~MainWindow()
{
    delete ui;
    rclcpp::shutdown();
    if (mosqibot_process->state() == QProcess::Running)
    {
        QStringList args;
        args.append(":/end_process.sh");
        mosqibot_process->startDetached("/bin/bash", args);
        mosqibot_process->terminate();
    }
    if (mythread.joinable())
    {
        mythread.join();
    }
}

void MainWindow::target_img_sub_callback(const sensor_msgs::msg::Image::ConstSharedPtr msg)
{
    cv_bridge::CvImageConstPtr cv_ptr;
    try
    {
        //        cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
        cv_ptr = cv_bridge::toCvShare(msg);
    }
    catch (cv_bridge::Exception& e)
    {
        RCLCPP_ERROR(node->get_logger(), "cv_bridge exception: %s", e.what());
        return;
    }
    cv::Mat resized_img;
    //    int width = ui->label_target->width();
    //    int height = ui->label_target->height();
    int width = 800;
    int height = 600;
    cv::resize(cv_ptr->image, resized_img, cv::Size(width, height));
    /*** Convert the cv::Mat to a QImage ***/
    QImage img(resized_img.data, resized_img.cols, resized_img.rows, QImage::Format_BGR888);
    emit displayTargetImg(img);
}

void MainWindow::heap_img_sub_callback(const sensor_msgs::msg::Image::ConstSharedPtr msg)
{
    cv_bridge::CvImageConstPtr cv_ptr;
    try
    {
        //        cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
        cv_ptr = cv_bridge::toCvShare(msg);
    }
    catch (cv_bridge::Exception& e)
    {
        RCLCPP_ERROR(node->get_logger(), "cv_bridge exception: %s", e.what());
        return;
    }
    cv::Mat resized_img;

    int width = 800;
    int height = 600;
    cv::resize(cv_ptr->image, resized_img, cv::Size(width, height));
    /*** Convert the cv::Mat to a QImage ***/
    QImage img(resized_img.data, resized_img.cols, resized_img.rows, QImage::Format_BGR888);
    emit displayHeapImg(img);
}

void MainWindow::spinNode()
{
    rclcpp::spin(node);
}

void MainWindow::on_displayTargetImg(const QImage& img)
{
    /*** Set the QImage as the pixmap for the QLabel ***/
    ui->label_target->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_displayHeapImg(const QImage& img)
{
    /*** Set the QImage as the pixmap for the QLabel ***/
    ui->label_heap->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_pushButton_on_clicked()
{
    QProcess::ProcessState state = mosqibot_process->state();
    if (state == QProcess::NotRunning)
    {
        QStringList args;
        // args.append(":/mosqibot.sh");
        args.append("/home/avent/Public/MyProjects/MosqiBot/ROS2-QT/src/qt_ui/resource/mosqibot.sh");
        mosqibot_process->start("/bin/bash", args);
    }
    else
    {
        QMessageBox::critical(this, "Error", "系统已经启动无需再次启动！");
    }
}

void MainWindow::on_pushButton_off_clicked()
{
    if (mosqibot_process->state() == QProcess::Running)
    {
        QStringList args;
        args.append("/home/avent/Public/MyProjects/MosqiBot/end_process.sh");
        mosqibot_process->startDetached("/bin/bash", args);
        mosqibot_process->terminate();
    }
    else
    {
        QMessageBox::critical(this, "Error", "系统已经关闭或者还未启动！");
    }
}

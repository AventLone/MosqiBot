#include "MainWindow.h"
#include "../ui/ui_MainWindow.h"

#include <QBitmap>
#include <QMessageBox>
#include <QPainter>
#include <QScreen>
#include <QThread>
#include <QToolButton>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(this, SIGNAL(displayTargetImg(QImage)), this, SLOT(on_displayTargetImg(QImage)));
    connect(this, SIGNAL(displayHeapImg(QImage)), this, SLOT(on_displayHeapImg(QImage)));

    mRosNode = std::make_shared<rclcpp::Node>("mosqibot_qt");
    mTargetImgSub = mRosNode->create_subscription<sensor_msgs::msg::Image>(
        "MosqiBot/target_img", 10, std::bind(&MainWindow::target_img_sub_callback, this, std::placeholders::_1));
    mHeapImgSub = mRosNode->create_subscription<sensor_msgs::msg::Image>(
        "MosqiBot/heap_img", 10, std::bind(&MainWindow::heap_img_sub_callback, this, std::placeholders::_1));
    mCommandPublisher = mRosNode->create_publisher<std_msgs::msg::Byte>("MosqiBot/command_from_GUI",
                                                                        rclcpp::ParametersQoS().reliable());

    mMyThread = std::thread(&MainWindow::spinNode, this);
}

MainWindow::~MainWindow()
{
    delete ui;
    rclcpp::shutdown();
}

void MainWindow::target_img_sub_callback(const sensor_msgs::msg::Image::ConstSharedPtr msg)
{
    cv_bridge::CvImageConstPtr cv_ptr;
    try
    {
        cv_ptr = cv_bridge::toCvShare(msg);
    }
    catch (cv_bridge::Exception& e)
    {
        RCLCPP_ERROR(mRosNode->get_logger(), "cv_bridge exception: %s", e.what());
        return;
    }
    cv::Mat resized_img;

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
        cv_ptr = cv_bridge::toCvShare(msg);
    }
    catch (cv_bridge::Exception& e)
    {
        RCLCPP_ERROR(mRosNode->get_logger(), "cv_bridge exception: %s", e.what());
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
    rclcpp::spin(mRosNode);
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

void MainWindow::on_pushButton_fan_on_clicked()
{
    std_msgs::msg::Byte msg;
    msg.data = FAN_ON;
    mCommandPublisher->publish(msg);
}

void MainWindow::on_pushButton_fan_off_clicked()
{
    std_msgs::msg::Byte msg;
    msg.data = FAN_OFF;
    mCommandPublisher->publish(msg);
}

void MainWindow::on_pushButton_killer_on_clicked()
{
    std_msgs::msg::Byte msg;
    msg.data = MOSQUITO_KILLER_ON;
    mCommandPublisher->publish(msg);
}

void MainWindow::on_pushButton_killer_off_clicked()
{
    std_msgs::msg::Byte msg;
    msg.data = MOSQUITO_KILLER_OFF;
    mCommandPublisher->publish(msg);
}

void MainWindow::on_pushButton_outlet_on_clicked()
{
    std_msgs::msg::Byte msg;
    msg.data = OUTLET_OPEN;
    mCommandPublisher->publish(msg);
}

void MainWindow::on_pushButton_outlet_off_clicked()
{
    std_msgs::msg::Byte msg;
    msg.data = OUTLET_CLOSE;
    mCommandPublisher->publish(msg);
}

void MainWindow::on_pushButton_start_shoot_clicked()
{
    std_msgs::msg::Byte msg;
    msg.data = START_SHOOT;
    mCommandPublisher->publish(msg);
}

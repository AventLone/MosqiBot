#include "Task.h"
#include <filesystem>
#include <ament_index_cpp/get_package_share_directory.hpp>

namespace MosqiBot
{
Task::Task() : mGroupIndex(0)
{
    mNode = std::make_shared<RosClient>("ros_client");

    mNode->declare_parameter("MosquitoTargetNum", 5);
    mNode->get_parameter("MosquitoTargetNum", mMosquitoTargetNum);

    /* Create picture folder */
    std::filesystem::path dir_path = "/home/avent/Desktop/MosqiBot_Pictures";
    uint16_t count = 1;
    if (!std::filesystem::is_directory(dir_path))
    {
        std::filesystem::create_directory(dir_path);
    }
    for (const auto& entry : std::filesystem::directory_iterator(dir_path))
    {
        if (entry.is_directory())
        {
            ++count;
        }
    }
    mPictureDir = dir_path.string() + "/Task_" + std::to_string(count);
    if (!std::filesystem::create_directory(mPictureDir))
    {
        RCLCPP_FATAL(mNode->get_logger(), "Failed to create a task directory!");
        std::exit(EXIT_FAILURE);
    }

    std::string pkg_path = ament_index_cpp::get_package_share_directory("mosqibot_system");
    mYoloer = std::make_unique<trt::Yolo>(pkg_path + "/config/settings/config.yaml",
                                          pkg_path + "/model/mosquito_yolov5_v3.trt",
                                          pkg_path + "/model/mosquito_classes.txt");

    mCommandSub =
        mNode->create_subscription<std_msgs::msg::Byte>("MosqiBot/command_from_GUI",
                                                        rclcpp::ParametersQoS().reliable(),
                                                        std::bind(&Task::cmdSubCallback, this, std::placeholders::_1));
}

Task::~Task()
{
    for (uint8_t i = 0; i < 2; ++i)
    {
        if (mThreads[i].joinable())
        {
            mThreads[i].join();
        }
    }
    rclcpp::shutdown();
}

void Task::task_sendMsg()
{
    while (!mStartShootFlag)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    sendAndWait(command::Mega::INIT);
    sendAndWait(command::Mega::INIT_CAMERA);
    while (rclcpp::ok())
    {
        if (mNode->img.empty())
        {
            continue;
        }

        /*** 1.Move the camera to the right middel place ***/
        sendAndWait(command::Mega::GLOB_CAMERA);
        sendAndWait(command::Mega::READY_CAMERA);               // Make camera on the top center position.
        std::this_thread::sleep_for(std::chrono::seconds(8));   // Waiting untill camera prepared
        /***************************************************/

        /*** 2.Separate the mosquitoes by shaking/vibration ***/
        vibratePlate();
        /*******************************************************/

        /*** 3.Take pictures on mosquitos one by one. ***/
        auto points = mNode->locateTarget();

        if (points.size() < mMosquitoTargetNum) continue;

        uint8_t picture_index = 0;
        std::string picture_path = mPictureDir + "/Group_" + std::to_string(++mGroupIndex);
        if (!std::filesystem::create_directory(picture_path))
        {
            RCLCPP_FATAL(mNode->get_logger(), "Failed to create a directory storing crude pictures!");
            std::exit(EXIT_FAILURE);
        }

        /*** Create a directory for crude pictures which means pictures unprocessed. ***/
        std::string crude_picture_path = picture_path + "/Crude";
        if (!std::filesystem::create_directory(crude_picture_path))
        {
            RCLCPP_FATAL(mNode->get_logger(), "Failed to create a directory storing crude pictures!");
            std::exit(EXIT_FAILURE);
        }

        sendAndWait(command::Mega::POWER_ON);
        sendAndWait(command::Mega::Z);
        std::array<command::Mega, 3> commands = {
            command::Mega::LOCAL_CAMERA_1, command::Mega::LOCAL_CAMERA_2, command::Mega::LOCAL_CAMERA_3};
        for (auto cmd : commands)
        {
            sendAndWait(cmd);
            for (const auto& coordinate : points)
            {
                sendAndWait(coordinate);
                std::this_thread::sleep_for(std::chrono::milliseconds(800));
                cv::imwrite(crude_picture_path + "/" + std::to_string(++picture_index) + ".jpg", mNode->img);
            }
        }
        sendAndWait(command::Mega::FLIP);
        sendAndWait(command::Mega::POWER_OFF);
        /**********************************************************/

        /*** 4.Init the device. ***/
        sendAndWait(command::Mega::INIT);
        sendAndWait(command::Mega::INIT_CAMERA);
        /*****************************/

        /*** Process the pictures ***/
        focusStackImgs(picture_path);
        recognizeImgs(picture_path);

        std::this_thread::sleep_for(std::chrono::seconds(600));
    }
}

void Task::cmdSubCallback(const std_msgs::msg::Byte::ConstPtr msg)
{
    switch (msg->data)
    {
        case FAN_ON:
            mNode->send_request(command::Mega::FAN_ON);
            break;
        case FAN_OFF:
            mNode->send_request(command::Mega::FAN_OFF);
            break;
        case MOSQUITO_KILLER_ON:
            mNode->send_request(command::Mega::MOSQUITO_KILLER_ON);
            break;
        case MOSQUITO_KILLER_OFF:
            mNode->send_request(command::Mega::MOSQUITO_KILLER_OFF);
            break;
        case OUTLET_OPEN:
            mNode->send_request(command::Mega::OUTLET_OPEN);
            break;
        case OUTLET_CLOSE:
            mNode->send_request(command::Mega::OUTLET_CLOSE);
            break;
        case START_SHOOT:
            mStartShootFlag = true;
            break;
        default:
            break;
    }
}

void Task::start()
{
    mThreads[0] = std::thread(&Task::task_sendMsg, this);
    mThreads[1] = std::thread(&Task::task_spinNode, this);
}

void Task::sendAndWait(command::Mega command)
{
    mNode->send_request(command);
    while (!mNode->taskflag)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    mNode->taskflag = false;
}

void Task::sendAndWait(const cv::Point2f& point)
{
    mNode->send_request(point);
    while (!mNode->taskflag)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    mNode->taskflag = false;
}

void Task::sendAndWait(uint8_t vib_motor_index)
{
    mNode->send_request(vib_motor_index);
    while (!mNode->taskflag)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    mNode->taskflag = false;
}

void Task::vibratePlate()
{
    cv::Mat tmp_img;
    static uint8_t n_vib = 6;   // The maximum number of vibrations.
    std::unordered_set<uint8_t> area_marks = mNode->locateHeap();
    if (area_marks.empty() || --n_vib == 0)
    {
        n_vib = 6;
        return;
    }
    uint8_t temp = 0;
    for (uint8_t i : area_marks)
    {
        temp |= 1 << i;
    }
    sendAndWait(temp);
    vibratePlate();
}

void Task::focusStackImgs(const std::string& file_path) const
{
    /*** Create directories ***/
    if (!std::filesystem::create_directory(file_path + "/FocusStacked"))
    {
        RCLCPP_ERROR(mNode->get_logger(), "Failed to create directory 'FocusStacked' !");
        return;
    }

    std::filesystem::path p(file_path + "/Crude");

    if (!std::filesystem::exists(p) || !std::filesystem::is_directory(p))
    {
        RCLCPP_ERROR(mNode->get_logger(), "Directory 'Crude' didn't exit!");
        return;
    }

    /***
     * Store image paths using std::map to sort in order
     * as std::filesystem::directory_iterator read file paths randomly
     ***/
    std::map<int, std::string> img_paths;
    for (const auto& entry : std::filesystem::directory_iterator(p))
    {
        if (entry.path().extension() == ".jpg" || entry.path().extension() == ".jpeg" ||
            entry.path().extension() == ".png")
        {
            img_paths[std::stoi(entry.path().stem())] = entry.path();
        }
    }
    if (img_paths.empty())
    {
        RCLCPP_ERROR(mNode->get_logger(), "There is no pictures under directory 'Crude' !");
        return;
    }
    int step = img_paths.size() / 3;
    for (int i = 1; i <= step; ++i)
    {
        std::vector<cv::Mat> imgs;
        imgs.reserve(3);
        cv::Mat tmp;
        for (int j = i; j <= img_paths.size(); j += step)
        {
            imgs.emplace_back(cv::imread(img_paths[j]));
        }
        mFocusStacker->fuse(imgs, tmp);
        cv::imwrite(file_path + "/FocusStacked/" + std::to_string(i) + ".jpg", tmp);
    }
}

void Task::recognizeImgs(const std::string& file_path) const
{
    if (!std::filesystem::create_directory(file_path + "/Recognized"))
    {
        RCLCPP_ERROR(mNode->get_logger(), "Failed to create directory 'Recognized'!");
        return;
    }
    std::filesystem::path p(file_path + "/FocusStacked");

    if (!std::filesystem::exists(p) || !std::filesystem::is_directory(p))
    {
        // std::cerr << "Error: " << p << " is not a directory" << std::endl;
        RCLCPP_ERROR_STREAM(mNode->get_logger(), "Error: " << p << " is not a directory");
        // exit(EXIT_FAILURE);
        return;
    }

    std::vector<std::string> img_paths;
    for (const auto& entry : std::filesystem::directory_iterator(p))
    {
        if (entry.path().extension() == ".jpg" || entry.path().extension() == ".jpeg" ||
            entry.path().extension() == ".png")
        {
            img_paths.push_back(entry.path().string());
        }
    }
    if (img_paths.empty())
    {
        RCLCPP_ERROR_STREAM(mNode->get_logger(),
                            "Error: There is no image file under " << file_path + "/FocusStacked !");
        // std::cerr << "Error: There is no image file under " << path + "/FocusStacked !" << std::endl;
        return;
    }

    for (int i = 0; i < img_paths.size(); ++i)
    {
        std::vector<cv::Mat> imgs;
        mYoloer->run(cv::imread(img_paths[i]), imgs);
        int j = 0;
        for (const cv::Mat& img : imgs)
        {
            cv::imwrite(file_path + "/Detected/" + std::to_string(i) + "_" + std::to_string(++j) + ".jpg", img);
        }
    }
}

void Task::task_spinNode()
{
    rclcpp::spin(mNode);
}

}   // namespace MosqiBot

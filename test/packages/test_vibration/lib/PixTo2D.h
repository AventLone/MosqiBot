/**
 * @author Avent
 * @version 0.1
 * @date 2023-05-03
 * @copyright Copyright (Avent) 2023
 **/
#pragma once
#include <opencv2/opencv.hpp>

class PixTo2D
{
public:
    PixTo2D(const float& square_width, const float& square_height);

    ~PixTo2D() = default;

    std::vector<std::array<float, 2>> detect(const cv::Mat& src);

    void detect(const cv::Mat& src, cv::Mat& dst);

    /*** Calculate corner points ***/
    static void calcuCornerPoints(const cv::Mat& src, std::vector<cv::Point>& corner_points);

    static void findRoi(const cv::Mat& src, cv::Mat& dst);

private:
    float square_width_ = 0, square_height_ = 0;   // Unit: mm

    std::vector<std::array<float, 2>> detectObject(const cv::Mat& img);

    void detectObject(const cv::Mat& src, cv::Mat& dst);
};
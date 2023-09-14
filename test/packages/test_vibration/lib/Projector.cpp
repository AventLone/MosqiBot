#include "Projector.h"


Projector::Projector(const std::string& camera_info_path, const cv::Point2f& tvec, float depth)
    : tvec_(tvec), depth_(depth)
{
    /** Read camera parameters from the yaml file **/
    cv::FileStorage fs(camera_info_path, cv::FileStorage::READ);
    fs["camera_matrix"] >> camera_matrix;
    fs["distortion_coefficients"] >> dist_coeffs;
    if (camera_matrix.empty() || dist_coeffs.empty())
    {
        throw std::runtime_error("\033[1;31mFailed to read camera parameters!\033[0m");
    }
    fs.release();
    new_camera_matrix =
        cv::getOptimalNewCameraMatrix(camera_matrix, dist_coeffs, cv::Size(1600, 1200), 1, cv::Size(1600, 1200));

    fx = new_camera_matrix.at<double>(0, 0);
    fy = new_camera_matrix.at<double>(1, 1);
    cx = new_camera_matrix.at<double>(0, 2);
    cy = new_camera_matrix.at<double>(1, 2);
}

std::vector<cv::Point2f> Projector::detect(const cv::Mat& src) const
{
    cv::Mat undistorted_img, img_gray, img_blur, img_binary;
    cv::undistort(src, undistorted_img, camera_matrix, dist_coeffs, new_camera_matrix);
    cv::cvtColor(undistorted_img, img_gray, cv::COLOR_BGR2GRAY);
    cv::medianBlur(img_gray, img_blur, 5);
    cv::threshold(img_blur, img_binary, 100, 255, cv::THRESH_BINARY_INV);

    cv::Mat out, stats, centroids;
    int number = cv::connectedComponentsWithStats(img_binary, out, stats, centroids, 8, CV_16U);

    std::vector<cv::Point2f> points;   // Target mosquitos coordinates
    cv::Point2f point;
    int area = 0;
    for (int i = 0; i < number; ++i)
    {
        area = stats.at<int>(i, cv::CC_STAT_AREA);
        /*** Remove small connected areas and oversized areas ***/
        if (area < threashold_1 || area > threashold_2)
        {
            continue;
        }

        double u = centroids.at<double>(i, 0);   // Unit: pixel
        double v = centroids.at<double>(i, 1);

        /** Calculate the real-world coordinates from the pixel **/
        point.x = (u - cx) * depth_ / fx;
        point.y = (v - cy) * depth_ / fy;

        points.push_back(point + tvec_ + error_compensation);
    }
    return points;
}

std::unordered_set<uint8_t> Projector::locateHeap(const cv::Mat& src) const
{
    cv::Mat undistorted_img, img_gray, img_blur, img_binary;
    cv::undistort(src, undistorted_img, camera_matrix, dist_coeffs, new_camera_matrix);
    cv::cvtColor(undistorted_img, img_gray, cv::COLOR_BGR2GRAY);
    cv::medianBlur(img_gray, img_blur, 5);
    cv::threshold(img_blur, img_binary, 100, 255, cv::THRESH_BINARY_INV);

    cv::Mat out, stats, centroids;
    int number = cv::connectedComponentsWithStats(img_binary, out, stats, centroids, 8, CV_16U);

    std::unordered_set<uint8_t> area_mark_set;
    int area = 0;
    for (int i = 0; i < number; ++i)
    {
        area = stats.at<int>(i, cv::CC_STAT_AREA);
        /*** Find the heaping area. ***/
        if (area <= threashold_2 || area > threashold_3)
        {
            continue;
        }
        double u = centroids.ptr<double>(i)[0];   // Unit: pixel
        double v = centroids.ptr<double>(i)[1];
        int x = static_cast<int>(u) - circle_center.x;
        int y = static_cast<int>(v) - circle_center.y;
        if (std::pow(x, 2) + std::pow(y, 2) < std::pow(circle_radius, 2))   // x^2 + y^2 < r^2
        {
            area_mark_set.insert(0);
        }
        else if (x > 0 && y < 0)
        {
            area_mark_set.insert(1);
        }
        else if (x < 0 && y < 0)
        {
            area_mark_set.insert(2);
        }
        else if (x < 0 && y > 0)
        {
            area_mark_set.insert(3);
        }
        else
        {
            area_mark_set.insert(4);
        }
    }
    return area_mark_set;
}

void Projector::detect(const cv::Mat& src, cv::Mat& dst) const
{
    cv::Mat undistorted_img, img_gray, img_blur, img_binary;
    cv::undistort(src, undistorted_img, camera_matrix, dist_coeffs, new_camera_matrix);
    cv::cvtColor(undistorted_img, img_gray, cv::COLOR_BGR2GRAY);
    cv::medianBlur(img_gray, img_blur, 5);
    cv::threshold(img_blur, img_binary, 100, 255, cv::THRESH_BINARY_INV);

    dst = undistorted_img.clone();

    cv::Mat out, stats, centroids;
    int number = cv::connectedComponentsWithStats(img_binary, out, stats, centroids, 8, CV_16U);

    // std::vector<cv::Point2f> points;   // Target mosquitos coordinates
    // cv::Point2f point;
    uint16_t index = 0;
    int area = 0;
    for (int i = 0; i < number; ++i)
    {
        area = stats.at<int>(i, cv::CC_STAT_AREA);
        /*** Remove small connected areas and oversized areas ***/
        if (area < threashold_1 || area > threashold_2)
        {
            continue;
        }

        // double u = centroids.at<double>(i, 0);   // Unit: pixel
        // double v = centroids.at<double>(i, 1);

        int x = stats.at<int>(i, cv::CC_STAT_LEFT);
        int y = stats.at<int>(i, cv::CC_STAT_TOP);
        int w = stats.at<int>(i, cv::CC_STAT_WIDTH);
        int h = stats.at<int>(i, cv::CC_STAT_HEIGHT);

        // cv::circle(dst, cv::Point(u, v), 2, cv::Scalar(0, 255, 0), 2, 8, 0);
        cv::rectangle(dst, cv::Rect(x, y, w, h), cv::Scalar(0, 255, 0), 2, 8, 0);
        int area = stats.at<int>(i, cv::CC_STAT_AREA);
        cv::putText(
            dst, std::to_string(++index), cv::Point(x, y - 6), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0, 255, 0), 2);
        // cv::putText(
        //     dst, std::to_string(area), cv::Point(x, y - 6), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0, 255, 0), 2);
    }
}

void Projector::locateHeap(const cv::Mat& src, cv::Mat& dst) const
{
    cv::Mat undistorted_img, img_gray, img_blur, img_binary;
    cv::undistort(src, undistorted_img, camera_matrix, dist_coeffs, new_camera_matrix);
    cv::cvtColor(undistorted_img, img_gray, cv::COLOR_BGR2GRAY);
    cv::medianBlur(img_gray, img_blur, 5);
    cv::threshold(img_blur, img_binary, 100, 255, cv::THRESH_BINARY_INV);

    dst = undistorted_img.clone();
    cv::circle(dst, circle_center, circle_radius, cv::Scalar(255, 0, 0), 1, 8, 0);
    cv::line(dst, line1[0], line1[1], cv::Scalar(255, 0, 0), 1, 8, 0);
    cv::line(dst, line2[0], line2[1], cv::Scalar(255, 0, 0), 1, 8, 0);
    cv::line(dst, line3[0], line3[1], cv::Scalar(255, 0, 0), 1, 8, 0);
    cv::line(dst, line4[0], line4[1], cv::Scalar(255, 0, 0), 1, 8, 0);

    cv::Mat out, stats, centroids;
    int number = cv::connectedComponentsWithStats(img_binary, out, stats, centroids, 8, CV_16U);

    int area = 0;
    for (int i = 0; i < number; ++i)
    {
        /*** Find the heaping area. ***/
        area = stats.at<int>(i, cv::CC_STAT_AREA);
        if (area <= threashold_2 || area > threashold_3)
        {
            continue;
        }
        double u = centroids.ptr<double>(i)[0];   // Unit: pixel
        double v = centroids.ptr<double>(i)[1];

        int x = stats.at<int>(i, cv::CC_STAT_LEFT);
        int y = stats.at<int>(i, cv::CC_STAT_TOP);
        int w = stats.at<int>(i, cv::CC_STAT_WIDTH);
        int h = stats.at<int>(i, cv::CC_STAT_HEIGHT);

        cv::rectangle(dst, cv::Rect(x, y, w, h), cv::Scalar(0, 0, 255), 2, 8, 0);
        cv::circle(dst, cv::Point(u, v), 2, cv::Scalar(0, 0, 255), 2, 8, 0);
        // cv::putText(
        //     dst, std::to_string(area), cv::Point(x, y - 6), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 0, 255), 2);
    }
}

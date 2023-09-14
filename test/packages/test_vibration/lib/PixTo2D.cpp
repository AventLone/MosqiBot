#include "PixTo2D.h"

PixTo2D::PixTo2D(const float& square_width, const float& square_height)
{
    square_width_  = square_width;
    square_height_ = square_height;
}

std::vector<std::array<float, 2>> PixTo2D::detect(const cv::Mat& src)
{
    cv::Mat roi;
    findRoi(src, roi);
    return detectObject(roi);
}

void PixTo2D::detect(const cv::Mat& src, cv::Mat& dst)
{
    cv::Mat roi;
    findRoi(src, roi);
    detectObject(roi, dst);
}

void PixTo2D::calcuCornerPoints(const cv::Mat& src, std::vector<cv::Point>& corner_points)
{
    /*** Convert to gray image ***/
    cv::Mat img_gray;
    cv::cvtColor(src, img_gray, cv::COLOR_BGR2GRAY);

    /*** Calculate Harris evaluation coefficient ***/
    cv::Mat harris;
    cv::cornerHarris(img_gray, harris, 2, 3, 0.04);

    /*** Normalize for numerical comparison and result display ***/
    cv::Mat harris_nomalised;
    cv::normalize(harris, harris_nomalised, 0, 255, cv::NORM_MINMAX);

    /*** Convert the data type to CV_8U ***/
    cv::convertScaleAbs(harris_nomalised, harris_nomalised);

    /*** Find Harris corner points ***/
    for (int row = 0; row < harris_nomalised.rows; ++row)
    {
        const uchar* pixel = harris_nomalised.ptr<uchar>(row);
        for (int col = 0; col < harris_nomalised.cols; ++col)
        {
            if (pixel[col] > 150)
            {
                corner_points.emplace_back(cv::Point(col, row));
            }
        }
    }
}

void PixTo2D::findRoi(const cv::Mat& src, cv::Mat& dst)
{
    std::vector<cv::Point> points;

    calcuCornerPoints(src, points);

    size_t num = ceil(points.size() * 0.3);

    /**
     * Sort points in order from smallest to largest
     * based on the y value of the coordinates
     **/
    sort(points.begin(), points.end(), [](cv::Point& a, cv::Point& b) { return a.y < b.y; });

    /*** Get the top 30% of points using iterators based on y value ***/
    std::vector<cv::Point> points_top(points.begin(), points.begin() + num);
    auto point_lefttop =
        *std::min_element(points_top.begin(), points_top.end(), [](cv::Point& a, cv::Point& b) { return a.x < b.x; });

    /*** Get the bottom 30% of points using reverse iterators based on y value ***/
    std::vector<cv::Point> points_bottom(points.rbegin(), points.rbegin() + num);
    auto point_rightbottom =
        *std::max_element(points_bottom.begin(), points_bottom.end(), [](cv::Point& a, cv::Point& b) { return a.x < b.x; });

    dst = src(cv::Rect(point_lefttop, point_rightbottom)).clone();
}

std::vector<std::array<float, 2>> PixTo2D::detectObject(const cv::Mat& img)
{
    cv::Mat img_gray, img_blur, img_binary;
    cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);
    cv::medianBlur(img_gray, img_blur, 3);
    cv::threshold(img_blur, img_binary, 120, 255, cv::THRESH_BINARY_INV);

    cv::Mat out, states, centroids;
    int number = cv::connectedComponentsWithStats(img_binary, out, states, centroids, 8, CV_16U);

    std::vector<std::array<float, 2>> points;   // Target mosquitos coordinates

    for (int i = 1; i < number; ++i)
    {
        /*** 去除小连通区域 ***/
        if (states.at<int>(i, cv::CC_STAT_AREA) < 10 || states.at<int>(i, cv::CC_STAT_AREA) > 400)
        {
            continue;
        }
        std::array<float, 2> point;
        double u = centroids.at<double>(i, 0);   // Unit: pixel
        double v = centroids.at<double>(i, 1);

        /**
         * Calculate the real-world coordinates
         * corresponding to the pixel coordinates.
         **/
        point[0] = u / img.cols * square_width_;   // mm
        point[1] = v / img.rows * square_height_;

        points.emplace_back(point);
    }
    return points;
}

void PixTo2D::detectObject(const cv::Mat& src, cv::Mat& dst)
{
    dst = src.clone();

    cv::Mat img_gray, img_blur, img_binary;
    cv::cvtColor(dst, img_gray, cv::COLOR_BGR2GRAY);
    cv::medianBlur(img_gray, img_blur, 1);
    cv::threshold(img_blur, img_binary, 120, 255, cv::THRESH_BINARY_INV);

    cv::Mat out, states, centroids;
    int number = cv::connectedComponentsWithStats(img_binary, out, states, centroids, 8, CV_16U);

    uint16_t index = 0;

    for (int i = 1; i < number; ++i)
    {
        /*** 去除比较小的连通区域 ***/
        if (states.at<int>(i, cv::CC_STAT_AREA) < 10 || states.at<int>(i, cv::CC_STAT_AREA) > 400)
        {
            continue;
        }
        ++index;
        int center_x = centroids.at<double>(i, 0);
        int center_y = centroids.at<double>(i, 1);

        auto x0 = centroids.at<double>(i, 0) / src.cols * square_width_;   // mm
        auto y0 = centroids.at<double>(i, 1) / src.rows * square_height_;

        std::cout << std::to_string(index) << ": [" << x0 << ", " << y0 << "]" << std::endl;

        int x = states.at<int>(i, cv::CC_STAT_LEFT);
        int y = states.at<int>(i, cv::CC_STAT_TOP);
        int w = states.at<int>(i, cv::CC_STAT_WIDTH);
        int h = states.at<int>(i, cv::CC_STAT_HEIGHT);

        cv::circle(dst, cv::Point(center_x, center_y), 2, cv::Scalar(0, 255, 0), 2, 8, 0);
        cv::Rect rect(x, y, w, h);
        cv::putText(dst, std::to_string(index), cv::Point(x, y), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 255, 0), 2);

        cv::rectangle(dst, rect, cv::Scalar(0, 255, 0), 1, 8, 0);
    }
}

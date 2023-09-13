#include "TrtNet.h"
namespace tensorRT
{
class Yolo : public Net
{
public:
    Yolo(const NetParams& params, std::string class_file_path);

    ~Yolo() = default;

    std::vector<cv::Mat> getIndividuals(const cv::Mat& src);

private:
    const float mConfThreshold{0.5f};   // Confidence threshold
    const float mNmsThreshold{0.4f};    // Non-maximum suppression threshold

    std::vector<std::string> classes;

    void drawPred(int class_id, float confidence, const cv::Rect& box, cv::Mat& frame);

    void postprocess(cv::Mat&) override;
};
}   // namespace tensorRT

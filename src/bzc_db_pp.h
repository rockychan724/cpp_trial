#ifndef BZC_DB_PP_H
#define BZC_DB_PP_H

#include <vector>
#include <opencv2/core.hpp>

/**
 * @author Chen Lei
 * @date 2020.12.7
 * @brief The bzc_db_pp class
 * Postprocess of DB(Differentiable Binarization)
 */
class bzc_db_pp
{
public:
    std::vector<cv::RotatedRect> parse_output(const std::vector<std::vector<float>> &, const cv::Point2f &);

private:
    float thread = 0.3f;
    float box_thresh = 0.7f;
    float scale_ratio = 0.4f;
    int max_candicates = 100;
    int min_side = 3;

    cv::Mat vector_to_Mat(const std::vector<std::vector<uint8_t>> &);
    cv::Mat partial_vertor_to_Mat(const std::vector<std::vector<float>> &, int, int, int, int);
    float get_mean_score(const std::vector<std::vector<float>> &, const cv::RotatedRect &);
    std::vector<cv::Point> unclip(const cv::RotatedRect &, float=1.5);
    inline void map_to_origin_image(const cv::Point2f &, std::vector<cv::Point> &);
};

#endif // BZC_DB_PP_H

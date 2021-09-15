#include "bzc_db_pp.h"
#include "third_part/clipper.hpp"  // thirdpart tool

#include <algorithm>
#include <opencv2/imgproc.hpp>

std::vector<cv::RotatedRect> bzc_db_pp::parse_output(const std::vector<std::vector<float>> &pred_map, const cv::Point2f &scales) {
    std::vector<cv::RotatedRect> out;
    if (pred_map.size() == 0 || pred_map[0].size() == 0) {
        return out;
    }
    int height = pred_map.size(), width = pred_map[0].size();
    std::vector<std::vector<uint8_t>> bit_map(height, std::vector<uint8_t>(width));

    // binarize pred_map
    std::transform(pred_map.begin(), pred_map.end(), bit_map.begin(), [this](std::vector<float> p) {
        std::vector<uint8_t> b(p.size());
        std::transform(p.begin(), p.end(), b.begin(), [this](float i) {
            return i > this->thread ? 255 : 0;
        });
        return b;
    });

    cv::Mat mat = this->vector_to_Mat(bit_map);
    std::vector<std::vector<cv::Point>> contours;
    // get contours of the map
    cv::findContours(mat, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
    int num_contours = std::min(int(contours.size()), this->max_candicates);
    for (int i = 0; i < num_contours; i++) {
        cv::RotatedRect box1 = cv::minAreaRect(contours[i]);
        if (std::min(box1.size.height, box1.size.width) < this->min_side)
            continue;
        float mean_score = this->get_mean_score(pred_map, box1);
        if (mean_score < this->box_thresh)
            continue;

        std::vector<cv::Point> contour = this->unclip(box1);
        this->map_to_origin_image(scales, contour);
        cv::RotatedRect box2 = cv::minAreaRect(contour);
        if (std::min(box2.size.height, box2.size.width) < this->min_side + 2)
            continue;
        out.push_back(box2);
    }
    return out;
}

cv::Mat bzc_db_pp::vector_to_Mat(const std::vector<std::vector<uint8_t>> &v) {
    cv::Mat mat(v.size(), v[0].size(), CV_8UC1);
    for (int i = 0; i < mat.rows; i++)
        for (int j = 0; j < mat.cols; j++)
            mat.at<uint8_t>(i, j) = v[i][j];
    return mat;
}

cv::Mat bzc_db_pp::partial_vertor_to_Mat(const std::vector<std::vector<float>> &v, int y_start, int y_end, int x_start, int x_end) {
    cv::Mat mat(y_end - y_start, x_end - x_start, CV_32FC1);
    for (int i = 0; i < mat.rows; i++)
        for (int j = 0; j < mat.cols; j++)
            mat.at<float>(i, j) = v[y_start + i][x_start + j];
    return mat;
}

float bzc_db_pp::get_mean_score(const std::vector<std::vector<float>> &pred_map, const cv::RotatedRect &box) {
    int height = pred_map.size(), width = pred_map[0].size();
    cv::Point2f points[4];
    box.points(points);
    float f_xmin = std::min_element(points, points + 3, [](cv::Point2f p1, cv::Point2f p2) { return p1.x < p2.x; })->x;
    float f_xmax = std::max_element(points, points + 3, [](cv::Point2f p1, cv::Point2f p2) { return p1.x < p2.x; })->x;
    float f_ymin = std::min_element(points, points + 3, [](cv::Point2f p1, cv::Point2f p2) { return p1.y < p2.y; })->y;
    float f_ymax = std::max_element(points, points + 3, [](cv::Point2f p1, cv::Point2f p2) { return p1.y < p2.y; })->y;
    int xmin = std::max(0, static_cast<int>(std::floor(f_xmin)));
    int xmax = std::min(width - 1, static_cast<int>(std::ceil(f_xmax)));
    int ymin = std::max(0, static_cast<int>(std::floor(f_ymin)));
    int ymax = std::min(height - 1, static_cast<int>(std::ceil(f_ymax)));

    cv::Mat mask(ymax - ymin + 1, xmax - xmin + 1, CV_8UC1, cv::Scalar(0));
    cv::Point root_points[1][4];
    std::transform(points, points + 4, root_points[0], [=](cv::Point2f p) {
        cv::Point res;
        res.x = p.x - xmin;
        res.y = p.y - ymin;
        return res;
    });
    const cv::Point *pts[1] = {root_points[0]};
    int npts[] = {4};
    cv::fillPoly(mask, pts, npts, 1, cv::Scalar(1));
    cv::Mat pred_mat = this->partial_vertor_to_Mat(pred_map, ymin, ymax + 1, xmin, xmax + 1);
    cv::Scalar s = cv::mean(pred_mat, mask);
    return static_cast<float>(s[0]);
}

std::vector<cv::Point> bzc_db_pp::unclip(const cv::RotatedRect &box, float unclip_ratio) {
    double distance = box.size.area() * unclip_ratio / ((box.size.height + box.size.width) * 2);
    cv::Point2f points[4];
    box.points(points);
    ClipperLib::Path path(4);
    std::transform(points, points + 4, path.begin(), [](cv::Point2f p) {
        return ClipperLib::IntPoint(static_cast<ClipperLib::cInt>(p.x), static_cast<ClipperLib::cInt>(p.y));
    });
    ClipperLib::Paths solution;
    ClipperLib::ClipperOffset offset;
    offset.AddPath(path, ClipperLib::jtRound, ClipperLib::etClosedPolygon);
    offset.Execute(solution, distance);

    std::vector<cv::Point> res(solution[0].size());
    std::transform(solution[0].begin(), solution[0].end(), res.begin(), [](ClipperLib::IntPoint p) {
        return cv::Point(static_cast<int>(p.X), static_cast<int>(p.Y));
    });
    return res;
}

// Map the coordinates back to the original image
inline void bzc_db_pp::map_to_origin_image(const cv::Point2f &scales, std::vector<cv::Point> &contour) {
    std::for_each(contour.begin(), contour.end(), [=](cv::Point &p) {
        p.x = p.x / scales.x;
        p.y = p.y / scales.y;
    });
}

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cmath>

uchar get_grayscale(uchar b, uchar g, uchar r)
{
    return static_cast<uchar>(std::round(b * 0.114 + g * 0.587 + r * 0.299));
}

cv::Mat to_grayscale(cv::Mat& image)
{
    cv::Mat img(image.rows, image.cols, CV_8UC1);
    int i, j;
    
    for (i = 0; i < img.rows; ++i) {
        for (j = 0; j < img.cols; ++j) {
            img.at<uchar>(i, j) = get_grayscale(image.at<cv::Vec3b>(i, j)[0], image.at<cv::Vec3b>(i, j)[1], image.at<cv::Vec3b>(i, j)[2]);
        }
    }
    
    return img;
}

void to_black_and_white(cv::Mat& image)
{
    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            if (image.at<uchar>(i, j) < 128) {
                image.at<uchar>(i, j) = 0;
            } else {
                image.at<uchar>(i, j) = 255;
            }
        }
    }
}

int main()
{
    cv::VideoCapture camera(0);
    cv::Mat image;
    cv::Mat grayscale_format;
    
    while (true) {
        camera >> image;
        
        cv::flip(image, image, 1);
        
        grayscale_format = to_grayscale(image);
        
        cv::imshow("pure", image);
        cv::imshow("grayscale", grayscale_format);
        
        to_black_and_white(grayscale_format);
        cv::imshow("black_and_white", grayscale_format);
        
        if (cv::waitKey(40) == ' ') {
            break;
        }
    }
}

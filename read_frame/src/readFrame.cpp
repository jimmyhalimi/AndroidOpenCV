#include <opencv2/opencv.hpp>

extern "C"
{
  int readFrameCV(unsigned char *data, int width, int height)
  {
    cv::Mat src = cv::Mat(height, width, CV_8UC1, data);

    if(src.empty())
    {
      return 0;
    }

    cv::Point center_point(width/2, height/2); 
    cv::circle(src, center_point, 100, cvScalar(255, 255, 0), -1);

    cv::imwrite("/data/misc/camera/dump_frame.jpg", src);

    return 1;
  }
}

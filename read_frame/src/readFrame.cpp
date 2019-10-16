#include <opencv2/opencv.hpp>

extern "C"
{
  // int readFrameCV(unsigned char *data, int width, int height)
  // {
  //   cv::Mat src = cv::Mat(height, width, CV_8UC1, data);

  //   if(src.empty())
  //   {
  //     return 0;
  //   }

  //   cv::Point center_point(width/2, height/2); 
  //   cv::circle(src, center_point, 100, cvScalar(255, 255, 0), -1);

  //   cv::imwrite("/data/misc/camera/dump_frame.jpg", src);

  //   return 1;
  // }

  int readFrameCV(unsigned char *data, int width, int height)
  {
    cv::CascadeClassifier face_cascade;
    if(!face_cascade.load("/vendor/lib/haarcascade_frontalface_alt2.xml"))
    {
      printf("Error loading cascade file for face");
      return -1;
    }

    std::vector<cv::Rect> faces;
    cv::Mat src = cv::Mat(height, width, CV_8UC1, data);
    cv::Mat src_image = src;

    if(src_image.empty())
    {
      return -1;
    }

    face_cascade.detectMultiScale(src_image, faces, 1.1, 3, CV_HAAR_SCALE_IMAGE | CV_HAAR_DO_CANNY_PRUNING, cvSize(0, 0), cvSize(200, 200));

    for(int i = 0; i < faces.size(); i++)
    {
      cv::Point pt1(faces[i].x + faces[i].width, faces[i].y + faces[i].height); 
      cv::Point pt2(faces[i].x, faces[i].y); 
      // cv::rectangle(src, pt1, pt2, cvScalar(0, 0, 0), 1, 8, 0); 
    }

    cv::Point pt1(50, 50);
    cv::Point pt2(100, 100);
    // cv::rectangle(src, pt1, pt2, cvScalar(0, 0, 0), 1, 8, 0); 

    cv::imwrite("/data/misc/camera/dump_frame.yuv", src);

    return faces.size();
  }
}

#pragma comment(lib, "opencv_core2411d.lib")
#pragma comment(lib, "opencv_highgui2411d.lib")
#pragma comment(lib, "opencv_imgproc2411d.lib")

#include <opencv2\core\core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main(int argc, char ** argv)
{

	Mat img = imread("C:/benchmark/image/pic3.JPG");
	Mat tmp = imread("C:/benchmark/ships/ship00.png");
	Mat img_result;
	matchTemplate(img, tmp, img_result, CV_TM_CCOEFF_NORMED);
	cv::Point max_pt;
                  double maxVal;
                  cv::minMaxLoc(img_result, NULL, &maxVal, NULL, &max_pt);
                
 
                  cv::Rect roi_rect(0, 0, tmp.cols, tmp.rows);
                  roi_rect.x = max_pt.x ;
                  roi_rect.y = max_pt.y ;
                  
                  // std::cout << i << ":(" << max_pt.x << ", " << max_pt.y << "), score=" << maxVal << std::endl;
                  // 探索結果の場所に矩形を描画
                  cv::rectangle(img, roi_rect, Scalar(0,255,255), 3);
				  resize(img, img, Size(img.cols/4, img.rows/4));


		imshow("disp",img);

	waitKey();
		return 0;
}

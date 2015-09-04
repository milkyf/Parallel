#ifdef _DEBUG
#pragma comment(lib, "opencv_core2411d.lib")
#pragma comment(lib, "opencv_highgui2411d.lib")
#pragma comment(lib, "opencv_imgproc2411d.lib")
#else
#pragma comment(lib, "opencv_core2411.lib")
#pragma comment(lib, "opencv_highgui2411.lib")
#pragma comment(lib, "opencv_imgproc2411.lib")
#endif

#include <time.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <boost/thread.hpp>

using namespace cv;
using namespace std;
using namespace boost;

mutex mtx; 
clock_t mainStart,mainEnd;

const char *pic[] = { "pic1.JPG","pic2.JPG","pic3.JPG" };
const char *ship[] = { "ship00.png","ship01.png","ship02.png","ship03.png","ship04.png","ship05.png",
				"ship06.png","ship07.png","ship08.png","ship09.png","ship10.png","ship11.png","ship12.png","ship13.png"};

void threadFuncA()
{
	for(int i = 0; i < 4; i++)
	{
		Mat color_tmp = imread(ship[i]);//カラー画像を読み込む
		resize(color_tmp, color_tmp, Size(), 0.5, 0.5);
		Mat gray_tmp;
		cvtColor(color_tmp, gray_tmp,CV_RGB2GRAY);// グレースケールに変換する

		for(int j = 0; j < 3; j++)
		{
			clock_t start,end;
			start = clock();

			Mat color_img = imread(pic[j]);
			resize(color_img, color_img, Size(), 0.5, 0.5);
			Mat gray_img, result;
			cvtColor(color_img, gray_img,CV_RGB2GRAY);
			Mat half_gray = Mat(gray_img.rows / 2, gray_img.cols, CV_8UC1);

			for(int y = 0; y < gray_img.rows / 2; y++){
				for(int x = 0; x < gray_img.cols; x++){
					half_gray.data[y *half_gray.step + x * half_gray.elemSize()] = gray_img.data[y *gray_img.step + x * gray_img.elemSize()];
				}
			}

			matchTemplate(half_gray, gray_tmp, result, CV_TM_CCOEFF_NORMED);
			Point max_pt;
            double maxVal;//閾値
            minMaxLoc(result, NULL, &maxVal, NULL, &max_pt);
		    Rect roi_rect(0, 0, gray_tmp.cols, gray_tmp.rows);
		    roi_rect.x = max_pt.x ;
		    roi_rect.y = max_pt.y ;

			end = clock();

		    cout << ship[i] << "," << pic[j] << endl;
		    cout << i << ":(" << max_pt.x << ", " << max_pt.y << "), score=" << maxVal << endl;
			cout << "検索時間:" << (double)(end - start) / CLOCKS_PER_SEC << "秒" << endl;
			cout << "" << endl;

			if(maxVal > 0.9)
			{
				cv::rectangle(color_img, roi_rect, Scalar(0,255,0), 1);// 探索結果の場所に矩形を描画
				stringstream ss;
				string str = "detect";
				ss << str << i << ".png" ;
				string filename = ss.str();
				imwrite(filename, color_img);
			}
		}
	}
}

void threadFuncB()
{
	for(int i = 4; i < 8; i++)
	{
		Mat color_tmp = imread(ship[i]);//カラー画像を読み込む
		resize(color_tmp, color_tmp, Size(), 0.5, 0.5);
		Mat gray_tmp;
		cvtColor(color_tmp, gray_tmp,CV_RGB2GRAY);// グレースケールに変換する

		for(int j = 0; j < 3; j++)
		{
			clock_t start,end;
			start = clock();

			Mat color_img = imread(pic[j]);
			resize(color_img, color_img, Size(), 0.5, 0.5);
			Mat gray_img, result;
			cvtColor(color_img, gray_img,CV_RGB2GRAY);
			Mat half_gray = Mat(gray_img.rows / 2, gray_img.cols, CV_8UC1);

			for(int y = 0; y < gray_img.rows / 2; y++){
				for(int x = 0; x < gray_img.cols; x++){
					half_gray.data[y *half_gray.step + x * half_gray.elemSize()] = gray_img.data[y *gray_img.step + x * gray_img.elemSize()];
					//gray_img.data[y *gray_img.step + x * gray_img.elemSize()] = half_gray.data[y * half_gray.step + x * half_gray.elemSize()];
				}
			}

			matchTemplate(half_gray, gray_tmp, result, CV_TM_CCOEFF_NORMED);
			Point max_pt;
            double maxVal;//閾値
            minMaxLoc(result, NULL, &maxVal, NULL, &max_pt);
		    Rect roi_rect(0, 0, gray_tmp.cols, gray_tmp.rows);
		    roi_rect.x = max_pt.x ;
		    roi_rect.y = max_pt.y ;

			end = clock();

		    cout << ship[i] << "," << pic[j] << endl;
		    cout << i << ":(" << max_pt.x << ", " << max_pt.y << "), score=" << maxVal << endl;
			cout << "検索時間:" << (double)(end - start) / CLOCKS_PER_SEC << "秒" << endl;
			cout << "" << endl;

			if(maxVal > 0.9)
			{
				mutex::scoped_lock lock(mtx); //スコープ内をロック
				cv::rectangle(color_img, roi_rect, Scalar(0,255,0), 1);// 探索結果の場所に矩形を描画
				stringstream ss;
				string str = "detect";
				ss << str << i << ".png" ;
				string filename = ss.str();
				imwrite(filename, color_img);
			}
		}
	}
}

void threadFuncC()
{
	for(int i = 8; i < 10; i++)
	{
		Mat color_tmp = imread(ship[i]);//カラー画像を読み込む
		resize(color_tmp, color_tmp, Size(), 0.5, 0.5);
		Mat gray_tmp;
		cvtColor(color_tmp, gray_tmp,CV_RGB2GRAY);// グレースケールに変換する

		for(int j = 0; j < 3; j++)
		{
			clock_t start,end;
			start = clock();

			Mat color_img = imread(pic[j]);
			resize(color_img, color_img, Size(), 0.5, 0.5);
			Mat gray_img, result;

			cvtColor(color_img, gray_img,CV_RGB2GRAY);
			Mat half_gray = Mat(gray_img.rows / 2, gray_img.cols, CV_8UC1);

			for(int y = 0; y < gray_img.rows / 2; y++){
				for(int x = 0; x < gray_img.cols; x++){
					half_gray.data[y *half_gray.step + x * half_gray.elemSize()] = gray_img.data[y *gray_img.step + x * gray_img.elemSize()];
				}
			}

			matchTemplate(half_gray, gray_tmp, result, CV_TM_CCOEFF_NORMED);
			Point max_pt;
            double maxVal;//閾値
            minMaxLoc(result, NULL, &maxVal, NULL, &max_pt);
		    Rect roi_rect(0, 0, gray_tmp.cols, gray_tmp.rows);
		    roi_rect.x = max_pt.x ;
		    roi_rect.y = max_pt.y ;

			end = clock();

		    cout << ship[i] << "," << pic[j] << endl;
		    cout << i << ":(" << max_pt.x << ", " << max_pt.y << "), score=" << maxVal << endl;
			cout << "検索時間:" << (double)(end - start) / CLOCKS_PER_SEC << "秒" << endl;
			cout << "" << endl;

			if(maxVal > 0.9)
			{
				mutex::scoped_lock lock(mtx); //スコープ内をロック
				cv::rectangle(color_img, roi_rect, Scalar(0,255,0), 1);// 探索結果の場所に矩形を描画
				stringstream ss;
				string str = "detect";
				ss << str << i << ".png" ;
				string filename = ss.str();
				imwrite(filename, color_img);					
			}
		}
	}
}

void threadFuncD()
{
	for(int i = 10; i < 14; i++)
	{
		Mat color_tmp = imread(ship[i]);//カラー画像を読み込む
		resize(color_tmp, color_tmp, Size(), 0.5, 0.5);
		Mat gray_tmp;
		cvtColor(color_tmp, gray_tmp,CV_RGB2GRAY);// グレースケールに変換する
		for(int j = 0; j < 3; j++)
		{
			clock_t start,end;
			start = clock();

			Mat color_img = imread(pic[j]);
			resize(color_img, color_img, Size(), 0.5, 0.5);
			Mat gray_img, result;

			cvtColor(color_img, gray_img,CV_RGB2GRAY);
			Mat half_gray = Mat(gray_img.rows / 2, gray_img.cols, CV_8UC1);

		for(int y = 0; y < gray_img.rows / 2; y++){
				for(int x = 0; x < gray_img.cols; x++){
					half_gray.data[y *half_gray.step + x * half_gray.elemSize()] = gray_img.data[y *gray_img.step + x * gray_img.elemSize()];
					//gray_img.data[y *gray_img.step + x * gray_img.elemSize()] = half_gray.data[y * half_gray.step + x * half_gray.elemSize()];
				}
			}

			matchTemplate(half_gray, gray_tmp, result, CV_TM_CCOEFF_NORMED);
			Point max_pt;
            double maxVal;//閾値
            minMaxLoc(result, NULL, &maxVal, NULL, &max_pt);
		    Rect roi_rect(0, 0, gray_tmp.cols, gray_tmp.rows);
		    roi_rect.x = max_pt.x ;
		    roi_rect.y = max_pt.y ;

			end = clock();

		    cout << ship[i] << "," << pic[j] << endl;
		    cout << i << ":(" << max_pt.x << ", " << max_pt.y << "), score=" << maxVal << endl;
			cout << "検索時間:" << (double)(end - start) / CLOCKS_PER_SEC << "秒" << endl;
			cout << "" << endl;

			if(maxVal > 0.9)
			{
				cv::rectangle(color_img, roi_rect, Scalar(0,255,0), 1);// 探索結果の場所に矩形を描画
				stringstream ss;
				string str = "detect";
				ss << str << i << ".png" ;
				string filename = ss.str();
				imwrite(filename, color_img);
			}
		}
	}
}

int main(int argc, char ** argv)
{
	mainStart = clock();

	thread threadA(threadFuncA);
	thread threadB(threadFuncB);
	thread threadC(threadFuncC);
	thread threadD(threadFuncD);

	threadA.join();
	threadB.join();
	threadC.join();
	threadD.join();

	mainEnd = clock();
	double time = (double)(mainEnd - mainStart) / CLOCKS_PER_SEC;
	cout << "処理にかかった合計の時間: "<< time  << "秒"<< endl;
	waitKey();
	return 0;
}

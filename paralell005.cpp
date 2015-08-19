#pragma comment(lib, "opencv_core2411.lib")
#pragma comment(lib, "opencv_highgui2411.lib")
#pragma comment(lib, "opencv_imgproc2411.lib")

#include <time.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <boost/thread.hpp>


using namespace cv;
using namespace std;
using namespace boost;
//ここまでおまじない
mutex mtx; //ロックのためのオブジェクト

clock_t mainStart,mainEnd;

const char *pic[] = { "pic1.JPG","pic2.JPG","pic3.JPG" };//でかい画像
const char *ship[] = { "ship00.png","ship01.png","ship02.png","ship03.png","ship04.png","ship05.png",
				"ship06.png","ship07.png","ship08.png","ship09.png","ship10.png","ship11.png","ship12.png","ship13.png"};//船の画像たち

//Mat Temp[] = new Mat[14];

void threadFuncA()
{
		for(int i = 0; i < 5; i++)
	{
		Mat color_tmp = imread(ship[i]);//カラー画像を読み込む
		Mat gray_tmp;
		cvtColor(color_tmp, gray_tmp,CV_RGB2GRAY);// グレースケールに変換する

		for(int j = 0; j < 3; j++)
		{
			clock_t start,end;
			start = clock();

			Mat color_img = imread(pic[j]);
			Mat gray_img, result;
			cvtColor(color_img, gray_img,CV_RGB2GRAY);

			matchTemplate(gray_img, gray_tmp, result, CV_TM_CCOEFF_NORMED);
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
				cv::rectangle(color_img, roi_rect, Scalar(0,255,255), 3);// 探索結果の場所に矩形を描画
				resize(color_img, color_img, Size(color_img.cols/4, color_img.rows/4));//出力される画像が大きいので、出力画像を4分の1に縮小
				//imshow(ship[i],color_img);//第1引数の名前のウィンドウに，第2引数のMatクラスのインスタンスの中にある画像を表示する．
				resize(color_img, color_img, Size(color_img.cols*4, color_img.rows*4));//画像をもとの大きさに戻しておく(でないとfor文で繰り返されるうちにどんどん小さくなってしまう)
				//waitKey(1);//カッコの中はミリ秒
			}
		}
	}

}
void threadFuncB()
{
		for(int i = 5; i < 10; i++)
	{
		
		Mat color_tmp = imread(ship[i]);//カラー画像を読み込む

		Mat gray_tmp;
		cvtColor(color_tmp, gray_tmp,CV_RGB2GRAY);// グレースケールに変換する

		for(int j = 0; j < 3; j++)
		{
			clock_t start,end;
			start = clock();

			Mat color_img = imread(pic[j]);
			Mat gray_img, result;
			cvtColor(color_img, gray_img,CV_RGB2GRAY);

			matchTemplate(gray_img, gray_tmp, result, CV_TM_CCOEFF_NORMED);
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
				cv::rectangle(color_img, roi_rect, Scalar(0,255,255), 3);// 探索結果の場所に矩形を描画
				resize(color_img, color_img, Size(color_img.cols/4, color_img.rows/4));//出力される画像が大きいので、出力画像を4分の1に縮小
				//imshow(ship[i],color_img);//第1引数の名前のウィンドウに，第2引数のMatクラスのインスタンスの中にある画像を表示する．
				resize(color_img, color_img, Size(color_img.cols*4, color_img.rows*4));//画像をもとの大きさに戻しておく(でないとfor文で繰り返されるうちにどんどん小さくなってしまう)
				//waitKey(1);//カッコの中はミリ秒
			}
		}
	}

}
void threadFuncC()
{
		for(int i = 10; i < 14; i++)
	{
		
		Mat color_tmp = imread(ship[i]);//カラー画像を読み込む

		Mat gray_tmp;
		cvtColor(color_tmp, gray_tmp,CV_RGB2GRAY);// グレースケールに変換する

		for(int j = 0; j < 3; j++)
		{
			clock_t start,end;
			start = clock();

			Mat color_img = imread(pic[j]);
			Mat gray_img, result;
			cvtColor(color_img, gray_img,CV_RGB2GRAY);

			matchTemplate(gray_img, gray_tmp, result, CV_TM_CCOEFF_NORMED);
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
				cv::rectangle(color_img, roi_rect, Scalar(0,255,255), 3);// 探索結果の場所に矩形を描画
				resize(color_img, color_img, Size(color_img.cols/4, color_img.rows/4));//出力される画像が大きいので、出力画像を4分の1に縮小
				imshow(ship[i],color_img);//第1引数の名前のウィンドウに，第2引数のMatクラスのインスタンスの中にある画像を表示する．
				resize(color_img, color_img, Size(color_img.cols*4, color_img.rows*4));//画像をもとの大きさに戻しておく(でないとfor文で繰り返されるうちにどんどん小さくなってしまう)
				waitKey(1);//カッコの中はミリ秒
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

	threadA.join();
	threadB.join();
	threadC.join();

	/*for(int i = 0; i < 14; i++)
	{
		imshow(ship[i],color_img);//第1引数の名前のウィンドウに，第2引数のMatクラスのインスタンスの中にある画像を表示する．
	}*/

	mainEnd = clock();
	double time = (double)(mainEnd - mainStart) / CLOCKS_PER_SEC;
	cout << "処理にかかった合計の時間: "<< time  << "秒"<< endl;
	waitKey();
	return 0;
}
/*
imshowはマルチスレッドで動かない(引用：http://blog.livedoor.jp/yhmtmt/archives/644007.html)


*/

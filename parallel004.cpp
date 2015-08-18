#pragma comment(lib, "opencv_core2411.lib")
#pragma comment(lib, "opencv_highgui2411.lib")
#pragma comment(lib, "opencv_imgproc2411.lib")

#include <time.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
//using namespace を使うと、下のほうに出てくるMatやcontやendlの前に本来つけるべきcv::やstd::を省略できる。
using namespace cv;
using namespace std;
//ここまでおまじない

int main(int argc, char ** argv)
{
	clock_t mainStart,mainEnd;
	mainStart = clock();
	
/*
//カラー画像を読み込む
Mat color_img = imread("hoge.png");  
Mat gray_img;

// グレースケールに変換する
cvtColor(color_img, gray_img,CV_RGB2GRAY);
*/
	//画像の名前を変えてるので気を付けてください。
	//画像ファイルは、どれも.cppファイルと同じ場所に保存してください。XXXXXXXXXXここ割と忘れやすいです。
	const char *pic[] = { "pic1.JPG","pic2.JPG","pic3.JPG" };//でかい画像
	const char *ship[] = { "ship00.png","ship01.png","ship02.png","ship03.png","ship04.png","ship05.png",
		"ship06.png","ship07.png","ship08.png","ship09.png","ship10.png","ship11.png","ship12.png","ship13.png"};//船の画像たち

	/*
	次のfor文の中でテンプレートマッチングします。
	まず探したい船の画像を指定して、次に大きい画像の中からその船を探します。
	大きい画像は3つあるので、1つの船舶画像につき3回テンプレートマッチングが行われています。
	計14隻の船を探すので、合計で14*3回テンプレートマッチングしてます。
	*/
	
	for(int i = 0; i < 14; i++)
	{
		
		Mat color_tmp = imread(ship[i]);//カラー画像を読み込む
		/*
		if(color_tmp.empty())
		{
			cout << "Couldnt read aimg" << endl;
		}
		*/

		Mat gray_tmp;
		cvtColor(color_tmp, gray_tmp,CV_RGB2GRAY);// グレースケールに変換する

		for(int j = 0; j < 3; j++)
		{
			clock_t start,end;
			start = clock();

			Mat color_img = imread(pic[j]);
			/*
			if(color_img.empty())
			{
				cout << "Could't read a template image." << endl;
			}
			*/
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
            
			//コンソール画面に出力
		    cout << ship[i] << "," << pic[j] << endl;
		    cout << i << ":(" << max_pt.x << ", " << max_pt.y << "), score=" << maxVal << endl;
			cout << "検索時間:" << (double)(end - start) / CLOCKS_PER_SEC << "秒" << endl;

			//閾値が高いときだけif文の中の処理をする
			if(maxVal > 0.9)
			{
				cv::rectangle(color_img, roi_rect, Scalar(0,255,255), 3);// 探索結果の場所に矩形を描画
				resize(color_img, color_img, Size(color_img.cols/4, color_img.rows/4));//出力される画像が大きいので、出力画像を4分の1に縮小
				imshow(ship[i],color_img);//第1引数の名前のウィンドウに，第2引数のMatクラスのインスタンスの中にある画像を表示する．
				resize(color_img, color_img, Size(color_img.cols*4, color_img.rows*4));//画像をもとの大きさに戻しておく(でないとfor文で繰り返されるうちにどんどん小さくなってしまう)
				waitKey(1);//カッコの中はミリ秒
			}
		}
	}
mainEnd = clock();
double time = (double)(mainEnd - mainStart) / CLOCKS_PER_SEC;
cout << "処理にかかった合計の時間: "<< time  << "秒"<< endl;
waitKey();
return 0;
}

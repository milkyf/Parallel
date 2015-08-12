#pragma comment(lib, "opencv_core2411d.lib")
#pragma comment(lib, "opencv_highgui2411d.lib")
#pragma comment(lib, "opencv_imgproc2411d.lib")

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
	//画像の名前を変えてるので気を付けてください。
	//画像ファイルは、どれも.cppファイルと同じ場所に保存してください。
	char *pic[] = { "pic1.JPG","pic2.JPG","pic3.JPG" };//でかい画像
	char *ship[] = { "ship00.png","ship01.png","ship02.png","ship03.png","ship04.png","ship05.png",
		"ship06.png","ship07.png","ship08.png","ship09.png","ship10.png","ship11.png","ship12.png","ship13.png"};//船の画像たち

	/*
	次のfor文の中でテンプレートマッチングします。
	まず探したい船の画像を指定して、次に大きい画像の中からその船を探します。
	大きい画像は3つあるので、1つの船舶画像につき3回テンプレートマッチングが行われています。
	計14隻の船を探すので、合計で14*3回テンプレートマッチングしてます。
	*/
	
	for(int i = 0; i < 14; i++)
	{
		Mat tmp = imread(ship[i]);

		for(int j = 0; j < 3; j++)
		{
			Mat img = imread(pic[j]);
			Mat img_result;
			matchTemplate(img, tmp, img_result, CV_TM_CCOEFF_NORMED);
			Point max_pt;
            double maxVal;//閾値
            minMaxLoc(img_result, NULL, &maxVal, NULL, &max_pt);
		    Rect roi_rect(0, 0, tmp.cols, tmp.rows);
		    roi_rect.x = max_pt.x ;
		    roi_rect.y = max_pt.y ;
            
			//コンソール画面に出力
		    cout << ship[i] << "," << pic[j] << endl;
		    cout << i << ":(" << max_pt.x << ", " << max_pt.y << "), score=" << maxVal << endl;

			//閾値が高いときだけif文の中の処理をする
			if(maxVal > 0.99)
			{
				cv::rectangle(img, roi_rect, Scalar(0,255,255), 3);// 探索結果の場所に矩形を描画
				resize(img, img, Size(img.cols/4, img.rows/4));//出力される画像が大きいので、出力画像を4分の1に縮小
				imshow(ship[i],img);//第1引数の名前のウィンドウに，第2引数のMatクラスのインスタンスの中にある画像を表示する．
				resize(img, img, Size(img.cols*4, img.rows*4));//画像をもとの大きさに戻しておく(でないとfor文で繰り返されるうちにどんどん小さくなってしまう)
				waitKey(1);//カッコの中はミリ秒
			}
		}
	}
waitKey();
return 0;
}

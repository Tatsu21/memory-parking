#include "pch.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace cv::xfeatures2d;
using namespace std;

class Feature {
protected:
	Mat finalImg;
	vector<Mat> des1;
	vector<Mat> des2;
	vector<Mat> img1;
	vector<Mat> img2;
	vector<vector<KeyPoint>> kp1;
	vector<vector<KeyPoint>> kp2;
public:
	void addfinalImg(Mat finalImg1)
	{
		this->finalImg = finalImg1;
	}
	Mat getFinalImg()
	{
		return this->finalImg;
	}
	void addImg1(Mat img) {
		img1.push_back(img);
	}
	void addImg2(Mat img) {
		img2.push_back(img);
	}
	void AddDes1(Mat des) {
		des1.push_back(des);
	}
	void AddDes2(Mat des) {
		des2.push_back(des);
	}
	void AddKp1(vector<KeyPoint> kps1) {
		kp1.push_back(kps1);
	}
	void AddKp2(vector<KeyPoint> kps2) {
		kp2.push_back(kps2);
	}
	vector<Mat> ReturnDes1() {
		return des1;
	}
	vector<Mat> ReturnDes2() {
		return des2;
	}
	vector<Mat> ReturnImg1() {
		return img1;
	}
	vector<Mat> ReturnImg2() {
		return img2;
	}
	vector<vector<KeyPoint>> ReturnKp1() {
		return kp1;
	}
	vector<vector<KeyPoint>> ReturnKp2() {
		return kp2;
	}
	size_t SizeKp1() {
		return kp1.size();
	}
	size_t SizeKp2() {
		return kp2.size();
	}
	size_t SizeDes1() {
		return des1.size();
	}
	size_t SizeDes2() {
		return des2.size();
	}
	size_t SizeImg1() {
		return img1.size();
	}
	size_t SizeImg2() {
		return img2.size();
	}
};
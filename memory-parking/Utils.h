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
	vector<Mat> des1;
	vector<Mat> des2;
	vector<vector<KeyPoint>> kp1;
	vector<vector<KeyPoint>> kp2;
public:
	Feature();

	void AddDes(Mat des1, Mat des2) {
		des1.push_back(des1);
		des2.push_back(des2);
	}
	void AddKp(vector<KeyPoint> kps1, vector<KeyPoint> kps2) {
		kp1.push_back(kps1);
		kp2.push_back(kps2);
	}
	vector<Mat> RetunDes1() {
		return des1;
	}
	vector<Mat> RetunDes2() {
		return des1;
	}
	vector<vector<KeyPoint>> ReturnKp1() {
		return kp1;
	}
	vector<vector<KeyPoint>> ReturnKp2() {
		return kp2;
	}
};
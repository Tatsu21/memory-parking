#include <filesystem>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <list>
#include "Utils.cpp"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QObject>
#include <QQmlContext>
//#include "Header.h"
#include <QtQuick>
#include <QtGui/qguiapplication.h>


//class interfatare : public QObject
//{
//	Q_OBJECT
//public:
//	explicit interfatare(QObject* parent = 0) : QObject(parent) {}
//	Q_INVOKABLE static void executare() {
//		int procesare();
//	}
//signals:
//public slots:
//};



#define SIZE_OF_PHOTO 200;
using namespace cv;
using namespace cv::xfeatures2d;
namespace fs = std::filesystem;
using namespace std;
string get_stem(const fs::path& p) { return (p.stem().string()); }

string* ReadFile(string dir) {
	static string photos[1200];
	int nr = 0;
	for (auto& entry : fs::directory_iterator(dir)) {
		photos[nr++] = get_stem(entry.path());
	}
	return photos;
}
string* ReadFile2(string dir) {
	static string photos[1200];
	int nr = 0;
	for (auto& entry : fs::directory_iterator(dir)) {
		photos[nr++] = get_stem(entry.path());
	}
	return photos;
}
Mat PercentOnImage(Mat img, float percent) {

	putText(img, "Percent : " + to_string(percent) + "%", Point(5, img.rows - 12), FONT_ITALIC, 0.8, CV_RGB(255, 0, 0), 2);

	return img;
}
Mat usm(Mat original, float radius, float amount, float threshold)
{

	cv::Mat input;
	original.convertTo(input, CV_32FC3);


	Mat retbuf = input.clone();

	Mat blurred;
	cv::GaussianBlur(input, blurred, cv::Size(0, 0), radius);


	Mat unsharpMask;
	cv::subtract(input, blurred, unsharpMask);


	cv::blur(unsharpMask, unsharpMask, { 3,3 });

	for (int row = 0; row < original.rows; row++)
	{
		for (int col = 0; col < original.cols; col++)
		{
			Vec3f origColor = input.at<Vec3f>(row, col);
			Vec3f difference = unsharpMask.at<Vec3f>(row, col);

			if (cv::norm(difference) >= threshold) {
				retbuf.at<Vec3f>(row, col) = origColor + amount * difference;
			}
		}
	}

	// convert back to unsigned char
	cv::Mat ret;
	retbuf.convertTo(ret, CV_8UC3);

	return ret;
}
Mat FeatureROI(string mimg, Mat img) {

	Mat mask;
	Mat imgm = imread(mimg);

	if (imgm.empty()) {
		cout << "Could not open or find the image!\n" << endl;

	}
	else {
		resize(imgm, imgm, Size(750, 750), 0.75, 0.75);
		bitwise_and(img, imgm, mask);

	}
	return mask;
}
Feature AKAZEe(Feature feature, string pimg, string mimg, int w, int h, int type, AKAZE::DescriptorType descriptor_type = AKAZE::DESCRIPTOR_KAZE, int descriptor_size = 64, int descriptor_channels = 3,
	float threshold = 0.0012f, int nOctaves = 5, int nOctaveLayers = 5, KAZE::DiffusivityType diffusivity = KAZE::DIFF_PM_G1) {
	Mat img = imread(pimg), des;
	if (img.empty()) {
		cout << "Could not open or find the image!\n" << endl;

	}
	else {
		if (type == 1) {
			img = usm(img, 2.8, 4., 1.);
			resize(img, img, Size(750, 750), 0.75, 0.75);

			Mat mask = FeatureROI(mimg, img);
			if (mask.empty()) {
				mask = img;
			}
			cvtColor(mask, mask, COLOR_BGR2GRAY);


			Ptr<AKAZE> detector = AKAZE::create(descriptor_type, descriptor_size, descriptor_channels, threshold, nOctaves, nOctaves, diffusivity);
			vector<KeyPoint> kp;
			detector->detectAndCompute(mask, noArray(), kp, des);
			feature.AddDes1(des);
			feature.AddKp1(kp);
			feature.addImg1(mask);
		}
		else if (type == 2) {
			img = usm(img, 0.8, 12., 1.);
			resize(img, img, Size(750, 750), 0.75, 0.75);
			Mat mask = FeatureROI(mimg, img);
			if (mask.empty()) {
				mask = img;
			}
			cvtColor(mask, mask, COLOR_BGR2GRAY);

			cout << pimg;
			Ptr<AKAZE> detector = AKAZE::create(descriptor_type, descriptor_size, descriptor_channels, threshold, nOctaves, nOctaves, diffusivity);
			vector<KeyPoint> kp;

			detector->detectAndCompute(mask, noArray(), kp, des);
			feature.AddDes2(des);
			feature.AddKp2(kp);
			feature.addImg2(mask);
		}
	}
	return feature;
}

Feature KAZEe(Feature feature, string pimg, int w, int h, int type, bool extended = false, bool upright = false, float threshold = 0.001f, int nOctaves = 4, int nOctaveLayers = 4, KAZE::DiffusivityType diffusivity = KAZE::DIFF_PM_G2) {
	Mat img = imread(pimg), des;

	if (img.empty()) {
		cout << "Could not open or find the image!\n" << endl;

	}
	else {
		if (type == 1) {
			resize(img, img, Size(w, h), 0.75, 0.75);
			Ptr<KAZE> detector = KAZE::create(extended, upright, threshold, nOctaveLayers, diffusivity);
			vector<KeyPoint> kp;
			detector->detectAndCompute(img, noArray(), kp, des);
			feature.AddDes1(des);
			feature.AddKp1(kp);
			feature.addImg1(img);
		}
		else if (type == 2) {
			resize(img, img, Size(w, h), 0.75, 0.75);
			Ptr<KAZE> detector = KAZE::create(extended, upright, threshold, nOctaveLayers, diffusivity);
			vector<KeyPoint> kp;

			detector->detectAndCompute(img, noArray(), kp, des);
			feature.AddDes2(des);
			feature.AddKp2(kp);
			feature.addImg2(img);
		}
	}
	return feature;
}


// tip; valoare1; valoare2; valoare3
// exemplu : float; 0.02f; 0.03f; 0.04f; etc
//			 int; 1; 2; 3; 4;
namespace FT
{
	Feature SIFT(Feature feature, string pimg, int w, int h, int type, int nFeatures = 0, int nOctaveLayers = 3, double contrastThreshold = 0.09, double edgeThreshold = 20.00,
		double sigma = 0.20) {
		Mat img = imread(pimg), des;
		if (img.empty()) {
			cout << "Could not open or find the image!\n" << endl;

		}
		else {
			if (type == 1) {
				resize(img, img, Size(w, h), 0.75, 0.75);
				Ptr<cv::SIFT> detector = SIFT::create(nFeatures, nOctaveLayers, contrastThreshold, edgeThreshold, sigma);
				vector<KeyPoint> kp;
				detector->detectAndCompute(img, noArray(), kp, des);
				feature.AddDes1(des);
				feature.AddKp1(kp);
				feature.addImg1(img);
			}
			else if (type == 2) {
				resize(img, img, Size(w, h), 0.75, 0.75);
				Ptr<cv::SIFT> detector = SIFT::create(nFeatures, nOctaveLayers, contrastThreshold, edgeThreshold, sigma);
				vector<KeyPoint> kp;

				detector->detectAndCompute(img, noArray(), kp, des);
				feature.AddDes2(des);
				feature.AddKp2(kp);
				feature.addImg2(img);
			}
		}
		return feature;
	}
}

Feature ORBb(Feature feature, string pimg, int w, int h, int type, int descriptor_size = 64, int descriptor_channels = 3,
	float threshold = 0.0012f, int nOctaves = 5, int nOctaveLayers = 5)
{
	Mat img = imread(pimg), des;
	if (img.empty()) {
		cout << "Could not open or find the image!\n" << endl;

	}
	else {
		if (type == 1) {
			resize(img, img, Size(w, h), 0.8, 0.8);
			Ptr<ORB>orbPtr = ORB::create(300, 1.1, 16, 31, 0, 2, cv::ORB::HARRIS_SCORE, 31, 70);
			vector<KeyPoint> kp;
			orbPtr->detect(img, kp, des);
			orbPtr->compute(img, kp, des);
			feature.AddDes1(des);
			feature.AddKp1(kp);
			feature.addImg1(img);

		}
		else if (type == 2) {
			resize(img, img, Size(w, h), 0.8, 0.8);
			Ptr<ORB>orbPtr = ORB::create(300, 1.1, 16, 31, 0, 2, cv::ORB::HARRIS_SCORE, 31, 70);
			vector<KeyPoint> kp;
			orbPtr->detect(img, kp, des);
			orbPtr->compute(img, kp, des);
			feature.AddDes2(des);
			feature.AddKp2(kp);
			feature.addImg2(img);
		}
	}
	return feature;
}
int procesare()
{
	cout << "started processing";
	const String path1 = "img/";
	const String spath = "save/";
	const String mspath = "blk-save/";
	const String mpath = "blk/";
	string* imgs = ReadFile(path1);
	string* train = ReadFile2(spath);

	int nr = 0;
	Feature feature;
	string nrs;
	Mat img_matches, des1, des2;
	vector<float> verifi;
	vector<int> goods;
	//train images
	for (int i = 0; i < 10; i++) {
		feature = AKAZEe(feature, spath + train[i] + ".jpg", mspath + train[i] + ".jpg", 750, 750, 1, AKAZE::DESCRIPTOR_KAZE, 64, 3, 0.0012f, 5, 5, KAZE::DIFF_PM_G1);
		//feature = FT::SIFT(feature, path1 + imgs[i] + ".jpg", 750, 750, 2, 0, 3, 0.09, 20.00, 2.00);
		//feature = KAZEe(feature, "26.jpg", 750, 750, 1);
	}

	for (int i = 0; i < 26; i++) {
		//feature = ORBb(feature, path1 + imgs[i] + ".jpg", 750, 750, 2);
		//feature = KAZEe(feature, path1 + imgs[i] + ".jpg", 750, 750, 2);
		//feature = FT::SIFT(feature, path1 + imgs[i] + ".jpg", 750, 750, 2, 0, 3, 0.09, 20.00, 2.00);
		feature = AKAZEe(feature, path1 + imgs[i] + ".jpg", mpath + imgs[i] + ".jpg", 750, 750, 2, AKAZE::DESCRIPTOR_KAZE, 64, 3, 0.0012f, 5, 5, KAZE::DIFF_PM_G1);
	}

	//Images
	for (int j = 0; j < (int)feature.RetunImg1().size(); j++) {
		for (int i = 0; i < (int)feature.RetunImg2().size(); i++) {
			try {
				Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE);
				vector<vector <DMatch>> matches;
				vector <DMatch>good_matches;
				feature.RetunDes1()[j].convertTo(des1, CV_32F);
				feature.RetunDes2()[i].convertTo(des2, CV_32F);
				matcher->knnMatch(des1, des2, matches, 2);
				//-- Filter matches using the Lowe's ratio test
				const float ratio_thresh = 0.77f;
				if (matches.size()) {
					for (size_t i = 0; i < matches.size(); i++)
					{
						if (matches[i][0].distance < ratio_thresh * matches[i][1].distance)
						{
							good_matches.push_back(matches[i][0]);
						}
					}
				}
				float percent = (((float)good_matches.size() / (float)feature.RetunDes1()[j].cols) * (float)100);
				drawMatches(feature.RetunImg1()[j], feature.ReturnKp1()[j], feature.RetunImg2()[i], feature.ReturnKp2()[i], good_matches, img_matches, Scalar::all(-1),
					Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
				img_matches = PercentOnImage(img_matches, percent);
				verifi.push_back(percent);
				imwrite("result/save_" + to_string(nr++) + ".jpg", img_matches);

			}
			catch (cv::Exception& e) {
				cerr << e.msg << endl;
			}
			//	
			//			//-- Show detected matches


			//		nr++;
			//	}
			//}
		}
		float max = verifi[0];
		int nr = 0;
		int ret = 0;
		for (int i = 0; i < verifi.size(); i++) {
			if (verifi[i] > max) max = verifi[i], ret = nr;
			nr++;
		}
		verifi.clear();
		goods.push_back(ret);
		if (j == (int)feature.RetunImg1().size() - 1) {
			nr = 0;
			Mat gooooods;
			for (int i = 0; i < goods.size(); i++) {
				Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE);
				vector<vector <DMatch>> matches;
				vector <DMatch>good_matches;
				feature.RetunDes1()[nr].convertTo(des1, CV_32F);
				cout << goods[i];
				feature.RetunDes2()[goods[i]].convertTo(des2, CV_32F);
				matcher->knnMatch(des1, des2, matches, 2);
				//-- Filter matches using the Lowe's ratio test
				const float ratio_thresh = 0.74f;
				if (matches.size()) {
					for (size_t i = 0; i < matches.size(); i++)
					{
						if (matches[i][0].distance < ratio_thresh * matches[i][1].distance)
						{
							good_matches.push_back(matches[i][0]);
						}
					}
				}
				float percent = (((float)good_matches.size() / (float)feature.RetunDes1()[nr].cols) * (float)100);
				if (percent > 100.00f) percent = 100.00f;
				drawMatches(feature.RetunImg1()[nr], feature.ReturnKp1()[nr], feature.RetunImg2()[goods[i]], feature.ReturnKp2()[goods[i]], good_matches, gooooods, Scalar::all(-1),
					Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
				gooooods = PercentOnImage(gooooods, percent);
				imwrite("result/good/save_" + to_string(nr) + ".jpg", gooooods);
				nr++;
			}
		}
	}
	//-- Draw matches
	return 0;
}


int main(int argc, char* argv[])
{
#if defined(Q_OS_WIN)
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
	//qmlRegisterType<Interfatare>("Interfatare", 1, 0, "Interfatare");
	QGuiApplication app(argc, argv);
	//QScopedPointer <Interfatare> intr(new Interfatare);
	QQmlApplicationEngine engine;
	engine.load(QUrl(QStringLiteral("qrc:/Source.qml")));
	//QQmlContext* context = engine.rootContext();
	//context->setContextProperty(QStringLiteral("interfatare"), new Interfatare(&engine));
	//engine.rootContext()->setContextProperty("intr", intr.data());
	if (engine.rootObjects().isEmpty())
		return -1;

	return app.exec();
}
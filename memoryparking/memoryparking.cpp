#include "pch.h"
#include <filesystem>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <list>
#include "MyForm.h"
#include "Utils.h"

namespace fs = std::filesystem;
using namespace System;
using namespace System::Windows::Forms;

string get_stem(const fs::path& p) { return (p.stem().string()); }

vector<string> ReadFile(string dir) {
	vector<string> photos;
	for (auto& entry : fs::directory_iterator(dir)) {
		photos.push_back(get_stem(entry.path()));
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

Feature AKAZEeMask(Feature feature, string pimg, string mimg, int w, int h, int type, AKAZE::DescriptorType descriptor_type = AKAZE::DESCRIPTOR_KAZE, int descriptor_size = 64, int descriptor_channels = 3,
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


			Ptr<AKAZE> detector = AKAZE::create(descriptor_type, descriptor_size, descriptor_channels, threshold, nOctaves, nOctaves, KAZE::DIFF_PM_G1);
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
			Ptr<AKAZE> detector = AKAZE::create(descriptor_type, descriptor_size, descriptor_channels, threshold, nOctaves, nOctaves, KAZE::DIFF_PM_G1);
			vector<KeyPoint> kp;

			detector->detectAndCompute(mask, noArray(), kp, des);
			feature.AddDes2(des);
			feature.AddKp2(kp);
			feature.addImg2(mask);
		}
	}
	return feature;
}
Feature AKAZEe(Feature feature, string pimg, int w, int h, int type, AKAZE::DescriptorType descriptor_type = AKAZE::DESCRIPTOR_KAZE, int descriptor_size = 64, int descriptor_channels = 3,
	float threshold = 0.0012f, int nOctaves = 5, int nOctaveLayers = 5, KAZE::DiffusivityType diffusivity = KAZE::DIFF_PM_G1) {
	Mat img = imread(pimg), des;
	if (img.empty()) {
		cout << "Could not open or find the image!\n" << endl;

	}
	else {
		if (type == 1) {


			Ptr<AKAZE> detector = AKAZE::create(descriptor_type, descriptor_size, descriptor_channels, threshold, nOctaves, nOctaves, KAZE::DIFF_PM_G1);
			vector<KeyPoint> kp;
			detector->detectAndCompute(img, noArray(), kp, des);
			feature.AddDes1(des);
			feature.AddKp1(kp);
			feature.addImg1(img);
		}
		else if (type == 2) {
			
			Ptr<AKAZE> detector = AKAZE::create(descriptor_type, descriptor_size, descriptor_channels, threshold, nOctaves, nOctaves, KAZE::DIFF_PM_G1);
			vector<KeyPoint> kp;

			detector->detectAndCompute(img, noArray(), kp, des);
			feature.AddDes2(des);
			feature.AddKp2(kp);
			feature.addImg2(img);
		}
	}
	return feature;
}

Feature KAZEe(Feature feature, string pimg, string mimg, int w, int h, int type, bool extended = false, bool upright = false, float threshold = 0.001f, int nOctaves = 4, int nOctaveLayers = 4, KAZE::DiffusivityType diffusivity = KAZE::DIFF_PM_G2) {
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

			resize(img, img, Size(w, h), 0.75, 0.75);
			Ptr<KAZE> detector = KAZE::create(extended, upright, threshold, nOctaveLayers, diffusivity);
			vector<KeyPoint> kp;
			detector->detectAndCompute(img, noArray(), kp, des);
			feature.AddDes1(des);
			feature.AddKp1(kp);
			feature.addImg1(img);
		}
		else if (type == 2) {
			img = usm(img, 0.8, 12., 1.);
			resize(img, img, Size(750, 750), 0.75, 0.75);
			Mat mask = FeatureROI(mimg, img);
			if (mask.empty()) {
				mask = img;
			}
			cvtColor(mask, mask, COLOR_BGR2GRAY);

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

namespace FT
{
	Feature SIFT(Feature feature, string pimg, string mimg, int w, int h, int type, int nFeatures = 0, int nOctaveLayers = 3, double contrastThreshold = 0.09, double edgeThreshold = 20.00,
		double sigma = 0.20) {
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

				resize(img, img, Size(w, h), 0.75, 0.75);
				Ptr<cv::SIFT> detector = SIFT::create(nFeatures, nOctaveLayers, contrastThreshold, edgeThreshold, sigma);
				vector<KeyPoint> kp;
				detector->detectAndCompute(img, noArray(), kp, des);
				feature.AddDes1(des);
				feature.AddKp1(kp);
				feature.addImg1(img);
			}
			else if (type == 2) {
				img = usm(img, 0.8, 12., 1.);
				resize(img, img, Size(750, 750), 0.75, 0.75);
				Mat mask = FeatureROI(mimg, img);
				if (mask.empty()) {
					mask = img;
				}
				cvtColor(mask, mask, COLOR_BGR2GRAY);

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

Feature ORBb(Feature feature, string pimg, string mimg, int w, int h, int type, int descriptor_size = 64, int descriptor_channels = 3,
	float threshold = 0.0012f, int nOctaves = 5, int nOctaveLayers = 5)
{
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

			resize(img, img, Size(w, h), 0.8, 0.8);
			Ptr<ORB> detector = ORB::create(300, 1.1, 16, 31, 0, 2, cv::ORB::HARRIS_SCORE, 31, 70);
			vector<KeyPoint> kp;

			detector->detectAndCompute(img, noArray(), kp, des);
			feature.AddDes1(des);
			feature.AddKp1(kp);
			feature.addImg1(img);

		}
		else if (type == 2) {
			img = usm(img, 0.8, 12., 1.);
			resize(img, img, Size(750, 750), 0.75, 0.75);
			Mat mask = FeatureROI(mimg, img);
			if (mask.empty()) {
				mask = img;
			}
			cvtColor(mask, mask, COLOR_BGR2GRAY);

			resize(img, img, Size(w, h), 0.8, 0.8);
			Ptr<ORB> detector = ORB::create(300, 1.1, 16, 31, 0, 2, cv::ORB::HARRIS_SCORE, 31, 70);
			vector<KeyPoint> kp;

			detector->detectAndCompute(img, noArray(), kp, des);
			feature.AddDes2(des);
			feature.AddKp2(kp);
			feature.addImg2(img);

		}
	}
	return feature;
}

auto BF(int photos, int step, Feature feature, float thresh, int matchingtyp) {
	struct BFval {
		Mat photo;
		float percent;
	};
	Mat des1, des2, photo1, photo2;
	Mat photo_matches;
	Ptr<DescriptorMatcher> matcher;
	switch (matchingtyp)
	{
	case 1: {
		matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE);
		break;
	}
	case 2: {
		matcher = DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);
		break;
	}
	}
	vector<vector <DMatch>> matches;
	vector <DMatch>good_matches;
	vector<KeyPoint> kp1, kp2;
	float percent = 0.0f;
	try {
		photo1 = feature.ReturnImg1()[photos];
		photo2 = feature.ReturnImg2()[step];
		kp1 = feature.ReturnKp1()[photos];
		kp2 = feature.ReturnKp2()[step];

		feature.ReturnDes1()[photos].convertTo(des1, CV_32F);
		feature.ReturnDes2()[step].convertTo(des2, CV_32F);

		matcher->knnMatch(des1, des2, matches, 2);
		//-- filter matches using the lowe's ratio test
		if (matches.size()) {
			for (size_t i = 0; i < matches.size(); i++) {
				if (matches[i][0].distance < thresh * matches[i][1].distance) {
					good_matches.push_back(matches[i][0]);
				}
			}
		}
		percent = (((float)good_matches.size() / (float)des1.cols) * (float)100);

		drawMatches(photo1, kp1, photo2, kp2, good_matches, photo_matches, Scalar::all(-1), Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
		photo_matches = PercentOnImage(photo_matches, percent);
	}
	catch (cv::Exception& e) {
		cerr << e.msg << endl;

	}
	return BFval{ photo_matches, percent };
}

string AKAZEMatching(string path, vector<string>imgDataSet, int descriptor_size, int descriptor_channels,
	float threshold, int nOctaves, int nOctaveLayers)
{
	cout << "akaze";
	const string path1 = "img/";
	const string spath = "save/";
	const string mspath = "blk-save/";
	const string mpath = "blk/";
	vector<string> imgs = ReadFile(path1);
	vector<string> train = ReadFile(spath);
	int nr = 0;
	Feature feature;
	string nrs;
	Mat img_matches, des1, des2;
	vector<float> verifi;
	vector<int> goods;
	//train images
	
	feature = AKAZEe(feature, path, 750, 750, 1, 
		AKAZE::DESCRIPTOR_KAZE, descriptor_size, descriptor_channels, threshold, nOctaves, nOctaveLayers, KAZE::DIFF_PM_G1);
	

	for (int i = 0; i < imgDataSet.size(); i++) {
		feature = AKAZEe(feature, imgDataSet[i], 750, 750, 2,
			AKAZE::DESCRIPTOR_KAZE, descriptor_size, descriptor_channels, threshold, nOctaves, nOctaveLayers, KAZE::DIFF_PM_G1);
	}

	////Images
	for (int j = 0; j < (int)feature.ReturnImg1().size(); j++) {
		for (int i = 0; i < (int)feature.ReturnImg2().size(); i++) {
			auto [photo_matches, percent] = BF(j, i, feature, 0.75f, 1);
			verifi.push_back(percent);
			imwrite("result/save_" + to_string(nr++) + ".jpg", photo_matches);

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
		if (j == (int)feature.ReturnImg1().size() - 1) {
			nr = 0;

			for (int i = 0; i < goods.size(); i++) {
				auto [photo_matches, percent] = BF(nr, goods[i], feature, 0.75f, 1);
				feature.addfinalImg(feature.ReturnImg2()[goods[i]]);
				imwrite("result/good2/save_0.jpg", feature.ReturnImg2()[goods[i]]);
				imwrite("result/good/save_" + to_string(nr) + ".jpg", photo_matches);
				nr++;
			}
		}
	}
	return "result/good2/save_0.jpg";
}

void ORBMatching(int descriptor_size, int descriptor_channels,
	float threshold, int nOctaves, int nOctaveLayers)
{
	cout << "orb";
	const string path1 = "img/";
	const string spath = "save/";
	const string mspath = "blk-save/";
	const string mpath = "blk/";
	vector<string> imgs = ReadFile(path1);
	vector<string> train = ReadFile(spath);
	int nr = 0;
	Feature feature;
	string nrs;
	Mat img_matches, des1, des2;
	vector<float> verifi;
	vector<int> goods;
	//train images
	for (int i = 0; i < 10; i++) {

		feature = ORBb(feature, spath + train[i] + ".jpg", mspath + train[i] + ".jpg", 750, 750, 1, descriptor_size, descriptor_channels, threshold, nOctaves, nOctaveLayers);
		cout << "img 1 size" << (int)feature.ReturnImg1().size() << "\n";
	}

	for (int i = 0; i < 26; i++) {
		cout << path1;
		cout << imgs[i];
		feature = ORBb(feature, path1 + imgs[i] + ".jpg", mpath + imgs[i] + ".jpg", 750, 750, 2, descriptor_size, descriptor_channels, threshold, nOctaves, nOctaveLayers);
		cout << "img 2 size" << (int)feature.ReturnImg2().size() << "\n";
	}
	cout << "img 1 size" << (int)feature.ReturnImg1().size() << "\n";
	cout << "img 2 size" << (int)feature.ReturnImg2().size() << "\n";

	////Images
	for (int j = 0; j < (int)feature.ReturnImg1().size(); j++) {
		cout << "j:" << j;
		for (int i = 0; i < (int)feature.ReturnImg2().size(); i++) {
			auto [photo_matches, percent] = BF(j, i, feature, 0.75f, 1);
			cout << "precent:" << percent;
			verifi.push_back(percent);
			cout << verifi[i]<< "\n";
			imwrite("result/save_" + to_string(nr++) + ".jpg", photo_matches);

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
		if (j == (int)feature.ReturnImg1().size() - 1) {
			nr = 0;

			for (int i = 0; i < goods.size(); i++) {
				auto [photo_matches, percent] = BF(nr, goods[i], feature, 0.75f, 1);

				imwrite("result/good/save_" + to_string(nr) + ".jpg", photo_matches);
				nr++;
			}
		}
	}
}

void KAZEMatching(bool extended, bool upright,
	float threshold, int nOctaves, int nOctaveLayers)
{
	cout << "kaze";
	const string path1 = "img/";
	const string spath = "save/";
	const string mspath = "blk-save/";
	const string mpath = "blk/";
	vector<string> imgs = ReadFile(path1);
	vector<string> train = ReadFile(spath);
	int nr = 0;
	Feature feature;
	string nrs;
	Mat img_matches, des1, des2;
	vector<float> verifi;
	vector<int> goods;
	//train images
	for (int i = 0; i < 10; i++) {
		feature = KAZEe(feature, spath + train[i] + ".jpg", mspath + train[i] + ".jpg", 750, 750, 1, extended, upright, threshold, nOctaves, nOctaveLayers, KAZE::DIFF_PM_G2);
	}
	for (int i = 0; i < 26; i++) {
		feature = KAZEe(feature, path1 + imgs[i] + ".jpg", mpath + imgs[i] + ".jpg", 750, 750, 2, extended, upright, threshold, nOctaves, nOctaveLayers, KAZE::DIFF_PM_G2);
	}
	////Images
	for (int j = 0; j < (int)feature.ReturnImg1().size(); j++) {
		for (int i = 0; i < (int)feature.ReturnImg2().size(); i++) {
			auto [photo_matches, percent] = BF(j, i, feature, 0.75f, 1);
			verifi.push_back(percent);
			imwrite("result/save_" + to_string(nr++) + ".jpg", photo_matches);

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
		if (j == (int)feature.ReturnImg1().size() - 1) {
			nr = 0;

			for (int i = 0; i < goods.size(); i++) {
				auto [photo_matches, percent] = BF(nr, goods[i], feature, 0.75f, 1);

				imwrite("result/good/save_" + to_string(nr) + ".jpg", photo_matches);
				nr++;
			}
		}
	}
}

void SIFTMatching(int nFeatures, int nOctaveLayers, double contrastThreshold, 
	double edgeThreshold,
	double sigma)
{
	cout << "sift";
	const string path1 = "img/";
	const string spath = "save/";
	const string mspath = "blk-save/";
	const string mpath = "blk/";
	vector<string> imgs = ReadFile(path1);
	vector<string> train = ReadFile(spath);
	int nr = 0;
	Feature feature;
	string nrs;
	Mat img_matches, des1, des2;
	vector<float> verifi;
	vector<int> goods;
	//train images
	for (int i = 0; i < 10; i++) {
		feature = FT::SIFT(feature, spath + train[i] + ".jpg", mspath + train[i] + ".jpg", 750, 750, 1, nFeatures, nOctaveLayers, contrastThreshold, edgeThreshold, sigma);
	}

	for (int i = 0; i < 26; i++) {
		feature = FT::SIFT(feature, path1 + imgs[i] + ".jpg", mpath + imgs[i] + ".jpg", 750, 750, 2, nFeatures, nOctaveLayers, contrastThreshold, edgeThreshold, sigma);
	}
	////Images
	for (int j = 0; j < (int)feature.ReturnImg1().size(); j++) {
		for (int i = 0; i < (int)feature.ReturnImg2().size(); i++) {
			auto [photo_matches, percent] = BF(j, i, feature, 0.75f, 1);
			verifi.push_back(percent);
			imwrite("result/save_" + to_string(nr++) + ".jpg", photo_matches);

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
		if (j == (int)feature.ReturnImg1().size() - 1) {
			nr = 0;

			for (int i = 0; i < goods.size(); i++) {
				auto [photo_matches, percent] = BF(nr, goods[i], feature, 0.75f, 1);

				imwrite("result/good/save_" + to_string(nr) + ".jpg", photo_matches);
				nr++;
			}
		}
	}
}


[STAThread]
int main()
{

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	memoryparking::MyForm form;
	Application::Run(% form);
	//const string path1 = "img/";
	//const string spath = "save/";
	//const string mspath = "blk-save/";
	//const string mpath = "blk/";
	//vector<string> imgs = ReadFile(path1);
	//vector<string> train = ReadFile(spath);
	//int nr = 0;
	//Feature feature;
	//string nrs;
	//Mat img_matches, des1, des2;
	//vector<float> verifi;
	//vector<int> goods;
	////train images
	//for (int i = 0; i < 10; i++) {
	//	feature = AKAZEe(feature, spath + train[i] + ".jpg", mspath + train[i] + ".jpg", 750, 750, 1, AKAZE::DESCRIPTOR_KAZE, 64, 3, 0.0012f, 5, 5, KAZE::DIFF_PM_G1);
	//	//feature = FT::SIFT(feature, path1 + imgs[i] + ".jpg", 750, 750, 2, 0, 3, 0.09, 20.00, 2.00);
	//	//feature = KAZEe(feature, "26.jpg", 750, 750, 1);
	//}

	//for (int i = 0; i < 26; i++) {
	//	//feature = ORBb(feature, path1 + imgs[i] + ".jpg", 750, 750, 2);

	////	//feature = KAZEe(feature, path1 + imgs[i] + ".jpg", 750, 750, 2);
	////	//feature = FT::SIFT(feature, path1 + imgs[i] + ".jpg", 750, 750, 2, 0, 3, 0.09, 20.00, 2.00);
	//	feature = AKAZEe(feature, path1 + imgs[i] + ".jpg", mpath + imgs[i] + ".jpg", 750, 750, 2, AKAZE::DESCRIPTOR_KAZE, 64, 3, 0.0012f, 5, 5, KAZE::DIFF_PM_G1);
	//}

	//////Images
	//for (int j = 0; j < (int)feature.ReturnImg1().size(); j++) {
	//	for (int i = 0; i < (int)feature.ReturnImg2().size(); i++) {
	//		auto [photo_matches, percent] = BF(j, i, feature, 0.75f, 1);
	//		verifi.push_back(percent);
	//		imwrite("result/save_" + to_string(nr++) + ".jpg", photo_matches);

	//	}
	//	float max = verifi[0];
	//	int nr = 0;
	//	int ret = 0;
	//	for (int i = 0; i < verifi.size(); i++) {
	//		if (verifi[i] > max) max = verifi[i], ret = nr;
	//		nr++;
	//	}
	//	verifi.clear();
	//	goods.push_back(ret);
	//	if (j == (int)feature.ReturnImg1().size() - 1) {
	//		nr = 0;

	//		for (int i = 0; i < goods.size(); i++) {
	//			auto [photo_matches, percent] = BF(nr, goods[i], feature, 0.75f, 1);

	//			imwrite("result/good/save_" + to_string(nr) + ".jpg", photo_matches);
	//			nr++;
	//		}
	//	}
	//}

    return 0;
}

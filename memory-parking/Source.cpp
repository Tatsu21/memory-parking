#include <filesystem>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <list>
#include "Utils.cpp"


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
Mat PercentOnImage(Mat img, float percent) {

	putText(img, "Percent : "+to_string(percent)+"%", Point(5, img.rows-12), FONT_ITALIC, 0.8, CV_RGB(255, 0, 0), 2);

	return img;
}
Mat FeatureROI(string mimg, Mat img) {

	Mat mask;
	Mat imgm = imread(mimg);
	resize(imgm, imgm, Size(750, 750), 0.75, 0.75);
	if (imgm.empty()) {
		cout << "Could not open or find the image!\n" << endl;

	}
	else {
		bitwise_and(img, imgm, mask);
	}
	return mask;
}
Feature AKAZEe(Feature feature, string pimg,string mimg, int w,int h, int type, AKAZE::DescriptorType descriptor_type = AKAZE::DESCRIPTOR_KAZE, int descriptor_size = 64, int descriptor_channels = 3,
								float threshold = 0.0012f, int nOctaves = 5, int nOctaveLayers = 5, KAZE::DiffusivityType diffusivity = KAZE::DIFF_PM_G1) {
	Mat img = imread(pimg), des;

	if (img.empty()) {
		cout << "Could not open or find the image!\n" << endl;
	
	}
	else {
		if (type == 1) {
			resize(img, img, Size(750, 750), 0.75, 0.75);
			Mat mask = FeatureROI(mimg, img);
			Ptr<AKAZE> detector = AKAZE::create(descriptor_type, descriptor_size, descriptor_channels, threshold, nOctaves, nOctaves, diffusivity);
			vector<KeyPoint> kp;
			detector->detectAndCompute(mask, noArray(), kp, des);
			feature.AddDes1(des);
			feature.AddKp1(kp);
			feature.addImg1(mask);
		}
		else if (type == 2) {
			resize(img, img, Size(750, 750), 0.75, 0.75);
			Mat mask = FeatureROI(mimg, img);
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

int main()
{	

	const String path1 = "img/";
	const String mpath = "blk/";
	string* imgs = ReadFile(path1);
	int nr = 0;
	Feature feature;
	string nrs;
	Mat img_matches, des1, des2;
	feature = AKAZEe(feature, "26.jpg", 750, 750, 1, AKAZE::DESCRIPTOR_KAZE, 64, 3, 0.0012f, 5, 5, KAZE::DIFF_PM_G1);
	//feature = FT::SIFT(feature, path1 + imgs[i] + ".jpg", 750, 750, 2, 0, 3, 0.09, 20.00, 2.00);

	for (int i = 0; i < 26; i++) {
		feature = AKAZEe(feature, "26.jpg", 750, 750, 1, AKAZE::DESCRIPTOR_KAZE, 64, 3, 0.0012f, 5, 5, KAZE::DIFF_PM_G1);
		//feature = FT::SIFT(feature, path1 + imgs[i] + ".jpg", 750, 750, 2, 0, 3, 0.09, 20.00, 2.00);
	}
	//Images
	for(int i= 0; i< (int)feature.RetunImg2().size(); i++){
		try{
			Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE);
			vector<vector <DMatch>> matches;
			vector <DMatch>good_matches;
			feature.RetunDes1()[0].convertTo(des1, CV_32F);
			feature.RetunDes2()[i].convertTo(des2, CV_32F);
	    	matcher->knnMatch(des1, des2, matches,2);
					//-- Filter matches using the Lowe's ratio test
			const float ratio_thresh = 0.8f;
			if (matches.size()) {
				for (size_t i = 0; i < matches.size(); i++)
				{
					if (matches[i][0].distance < ratio_thresh * matches[i][1].distance)
					{
						good_matches.push_back(matches[i][0]);
					}
				}
			}
			float percent = (((float)good_matches.size() / (float)feature.RetunDes1()[0].cols) * (float)100);
			cout << percent << endl;
			drawMatches(feature.RetunImg1()[0], feature.ReturnKp1()[0], feature.RetunImg2()[i], feature.ReturnKp2()[i], good_matches, img_matches, Scalar::all(-1),
						Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
			img_matches = PercentOnImage(img_matches, percent);
			imshow("Matches", img_matches);
			imwrite("save_" + to_string(nr++) + ".jpg", img_matches);
			waitKey(0);
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
	//-- Draw matches

	return 0;
}
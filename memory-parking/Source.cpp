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
			img = usm(img, 2.8, 4., 1.);
			resize(img, img, Size(750, 750), 0.75, 0.75);
			
			Mat mask = FeatureROI(mimg, img);
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
			cvtColor(mask, mask, COLOR_BGR2GRAY);
			

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

int main()
{	

	const String path1 = "img/";
	const String mpath = "blk/";
	string* imgs = ReadFile(path1);
	int nr = 0;
	Feature feature;
	string nrs;
	Mat img_matches, des1, des2;
	feature = AKAZEe(feature, "26.jpg", "26seg.jpg", 750, 750, 1, AKAZE::DESCRIPTOR_KAZE, 64, 3, 0.0012f, 5, 5, KAZE::DIFF_PM_G1);
	
	for (int i = 0; i < 26; i++) {
		feature = AKAZEe(feature, path1 + imgs[i] + ".jpg", mpath + imgs[i] + ".jpg", 750, 750, 2, AKAZE::DESCRIPTOR_KAZE, 64, 3, 0.0012f, 5, 5, KAZE::DIFF_PM_G1);
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
			const float ratio_thresh = 0.79f;
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
			waitKey(1000);
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
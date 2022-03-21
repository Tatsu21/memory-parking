#include <filesystem>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <list>
#include "Utils.h"


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
void AKAZEe(Feature feature, string pimg, int w,int h) {
	Mat img = imread(pimg), des;
	if (img.empty()) {
		cout << "Could not open or find the image!\n" << endl;
	
	}else{
		resize(img, img, Size(w, h), 0.75, 0.75);
		Ptr<AKAZE> detector = AKAZE::create(AKAZE::DESCRIPTOR_KAZE, 64, 3, 0.0012f, 5, 5, KAZE::DIFF_PM_G1);
		vector<KeyPoint> kp;
		detector->detectAndCompute(img, noArray(), kp, des);
	}
}

int main()
{	
	Mat imgg = imread("26.jpg");
	const String path1 = "img/";
	string* imgs = ReadFile(path1);
	int nr = 0;
	string nrs;
	if (imgg.empty()) {
		cout << "Could not open or find the image!\n" << endl;
		return -1;
	}
	resize(imgg, imgg, Size(750, 750), 0.75, 0.75);
	Ptr<AKAZE> detector = AKAZE::create(AKAZE::DESCRIPTOR_KAZE, 64, 3, 0.0012f, 5, 5, KAZE::DIFF_PM_G1);
	vector<KeyPoint> kp1, kp2;
	Mat des1, des2, img_matches;
	detector->detectAndCompute(imgg, noArray(), kp1, des1);
	//Images
	for(int i= 0; i< 26; i++){
		Mat img = imread(path1+imgs[i]+".jpg");

		resize(img, img,Size(750, 750), 0.75, 0.75);
		if (img.empty()) {
			cout << "Could not open or find the image!\n" << endl;
			cout << path1 + imgs[i] + ".jpg";
			return -1;
		}
		cout << path1 + imgs[i] + ".jpg"<<endl;
	    // VIDEOS
		//for (int i = 0; i < 13; i++) {
		//	//Mat img2 = imread(path2, IMREAD_GRAYSCALE);
		//	VideoCapture cap(path2+vid[i]+".mp4");
		//	if (!cap.isOpened()) {
		//		cout << "Could not open or find the video!\n" << endl;
		//		cout << path2 + vid[i] + ".mp4";
		//		return -1;
		//	}
		//	cout << path2 + vid[i] + ".mp4" <<endl;


		//	while (true)
		//	{
		//		Mat frame, gray,res;
		//		cap >> frame;
		//		if (frame.empty())
		//			break;
		//		//cvtColor(frame, gray, COLOR_BGR2GRAY);
		//		


		//		resize(frame, frame, cv::Size(300, 300), 0.75, 0.75);
		detector->detectAndCompute(img, noArray(), kp2, des2);
		try{
			Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE_L1);
			vector<vector <DMatch>> matches;
			vector <DMatch>good_matches;
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
			float percent = (((float)good_matches.size() / (float)des1.cols) * (float)100);
			cout << percent << endl;
			drawMatches(imgg, kp1, img, kp2, good_matches, img_matches, Scalar::all(-1),
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
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

	putText(img, "Percent : "+to_string(percent)+"%", Point(10, img.rows / 2), FONT_HERSHEY_DUPLEX, 1.0, CV_RGB(118, 185, 0), 2);

	return img;
}

int main()
{
	const String path1 = "img/";
	string* imgs = ReadFile(path1);
	const String path2 = "vid/";
	string* vid = ReadFile(path2);
	int nr = 0;
	string nrs;


	//Images
	for(int i= 0; i< 3; i++){
		Mat img = imread(path1+imgs[i]+".jpg");

		resize(img, img,Size(300, 300), 0.75, 0.75);
		if (img.empty()) {
			cout << "Could not open or find the image!\n" << endl;
			cout << path1 + imgs[i] + ".jpg";
			return -1;
		}
		cout << path1 + imgs[i] + ".jpg"<<endl;
	    // VIDEOS
		for (int i = 0; i < 13; i++) {
			//Mat img2 = imread(path2, IMREAD_GRAYSCALE);
			VideoCapture cap(path2+vid[i]+".mp4");
			if (!cap.isOpened()) {
				cout << "Could not open or find the video!\n" << endl;
				cout << path2 + vid[i] + ".mp4";
				return -1;
			}
			cout << path2 + vid[i] + ".mp4" <<endl;

			Ptr<AKAZE> detector = AKAZE::create(AKAZE::DESCRIPTOR_KAZE,64,3,0.0011f, 5, 5,KAZE::DIFF_PM_G1);
			//Ptr<AKAZE> detector = AKAZE::create();
			vector<KeyPoint> kp1, kp2;
			Mat des1, des2, img_matches;
			detector->detectAndCompute(img, noArray(), kp1, des1);
			while (true)
			{
				Mat frame, gray,res;
				cap >> frame;
				if (frame.empty())
					break;
				//cvtColor(frame, gray, COLOR_BGR2GRAY);
				


				resize(frame, frame, cv::Size(300, 300), 0.75, 0.75);
				detector->detectAndCompute(frame, noArray(), kp2, des2);
				try{
					Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE_HAMMING);
					vector<vector <DMatch>> matches;
					vector <DMatch>good_matches;
					matcher->knnMatch(des1, des2, matches,2);
					//-- Filter matches using the Lowe's ratio test
					const float ratio_thresh = 0.85f;
				    for (size_t i = 0; i < matches.size(); i++)
					{
						if (matches.size() != 0) {
							if (matches[i][0].distance < ratio_thresh * matches[i][1].distance)
							{
								good_matches.push_back(matches[i][0]);
							}
						}
					}

					float percent = (((float)good_matches.size() / (float)des1.cols) * (float)100);
					cout << percent << endl;
					drawMatches(img, kp1, frame, kp2, good_matches, img_matches, Scalar::all(-1),
						Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
				}
				catch (int e) {

				}

					//-- Show detected matches
				imshow("Matches", img_matches);
				waitKey(25);
				nr++;
			}
		}
	}
	//-- Draw matches

	return 0;
}
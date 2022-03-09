#include <filesystem>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <list>
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

int main()
{
	const String path1 = "img/";
	string* imgs = ReadFile(path1);
	const String path2 = "vid/";
	string* vid = ReadFile(path2);
	


	//Images
	for(int i= 0; i< 8; i++){
		Mat img = imread(path1+imgs[i]+".jpg", IMREAD_GRAYSCALE);

		resize(img, img, cv::Size(300, 300), 0.75, 0.75);
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
			cout << path2 + vid[i] + ".mp4";
			Ptr<AKAZE> detector = AKAZE::create();
			vector<KeyPoint> kp1, kp2;
			Mat des1, des2, img_matches;
			detector->detectAndCompute(img, noArray(), kp1, des1);
			while (true)
			{
				Mat frame, gray,res;
				cap >> frame;
				if (frame.empty())
					break;
				cvtColor(frame, gray, COLOR_BGR2GRAY);
				


				resize(gray, gray, cv::Size(300, 300), 0.75, 0.75);
				detector->detectAndCompute(gray, noArray(), kp2, des2);
				try{
					Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE_HAMMING);
					vector<vector <DMatch>> matches;
					vector <DMatch>good_matches;
					matcher->knnMatch(des1, des2, matches,2);
					//-- Filter matches using the Lowe's ratio test
					const float ratio_thresh = 0.7f;
				    for (size_t i = 0; i < matches.size(); i++)
					{
						if (matches[i][0].distance < ratio_thresh * matches[i][1].distance)
						{
							good_matches.push_back(matches[i][0]);
						}
					}

					float percent = ((int)good_matches.size() / ((int)des1.rows* (int)des1.cols))*100;
					cout << percent << endl;
					drawMatches(img, kp1, gray, kp2, good_matches, img_matches, Scalar::all(-1),
						Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
				}
				catch (int e) {

				}
					//-- Show detected matches
				imshow("Matches", img_matches);
				waitKey(25);
			}
		}
	}

	//-- Draw matches

	return 0;
}
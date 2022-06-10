#pragma once
#include <string>
#include <vector>
std::string AKAZEMatching(std::string path, std::vector<std::string>imgDataSet, int descriptor_size, int descriptor_channels,
	float threshold, int nOctaves, int nOctaveLayers);
std::string ORBMatching(std::string path, std::vector<std::string>imgDataSet, int descriptor_size, int descriptor_channels,
	float threshold, int nOctaves, int nOctaveLayers);
std::string KAZEMatching(std::string path, std::vector<std::string>imgDataSet, bool extended, bool upright,
	float threshold, int nOctaves, int nOctaveLayers);
std::string SIFTMatching(std::string path, std::vector<std::string>imgDataSet, int nFeatures, int nOctaveLayers, double contrastThreshold,
	double edgeThreshold, double sigma);
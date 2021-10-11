#pragma once

#include<vector>
#include< filesystem>
#include<string>
using namespace std;
using namespace std::filesystem;
// Declare some variables in struct

struct Options {
	bool bytes = false;
	bool validFolder = false;
	bool summary = false;
	bool clusterSize1024 = false;
	bool humanReadable = false;
	bool reverse = false;
	bool sortBySize = false;
	bool sortByName = false;
	bool boolInSwitches = false;
	bool clusterSizeReset = false;
	bool help = false;
	bool version = false;
	
	bool dublicatesS = false;
	bool dublicatesK = false;
	bool dublicatesH = false;
	bool dublicatesZ = false;
	bool dublicatesN = false;
	bool dublicatesR = false;
	bool dublicatesB = false;
	bool bh = false;
	bool nz = false;
	bool kblock = false;
	bool validValue = true;
	string switches;
	string availablSwitches = "skhznrb";
	unsigned long block_switch = 0;
	double clusterSize = 4096.0;

	path folder = ".";
};

//define all of the function in header so that it can access in all file of this project
Options parseInput(int argc, char* agrv[]);
void errorMsges(Options options);
vector<pair<string, uintmax_t>> scan(path const& f, vector<pair<string, uintmax_t>>& vec, double clusterSize);
uintmax_t rscan(path const& f, double clusterSize);
bool sort_size(std::pair<std::string, uintmax_t>& lhs, std::pair<std::string, uintmax_t>& rhs);
std::string humanReadableConversion(uintmax_t x);
void outputView(path const& folderPath, vector<pair<string, uintmax_t>> dataV, vector<pair<string, uintmax_t>> specFolderV,Options options);


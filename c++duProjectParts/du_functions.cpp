/*
\file:         du_function.cpp
\author:       Agnita Paul
\date:         09-08-2021
\version:      1.0.0
\brief:        this is a helper file for getting estimate file space usage on a file system 
*/
#include<iostream>
#include<fstream>
#include "du_functions.hpp"
using namespace std;

/*
\fn:		parseInput()
\brief:		this function will work the switches activity based on the command line
\param:		argc: command line argument count ; argv[]: the command line argument string
\return:	a struct which has a lot different of kind of variable
*/
//to identify the switches
Options parseInput(int argc, char* argv[]) {
	
	 Options options;

	 //populated a vector
	vector<string>vecArgv(&argv[1],&argv[argc]);
	//checking empty vector to get default value
	if (vecArgv.empty()) {

		//default work
		 return options;
	}
	else {

		string switches;
		string switches2;
		
		for (vector<int>::size_type i = 0; i < vecArgv.size(); ++i);
		{
		
			//cout << "hi"<<endl;

			//boolean value setup for word first because it has '--' . it should be first then "-". 
			if (vecArgv.front() == "--help") {
			options.help = true;

			}

			
			else if (vecArgv.front() == "--version") {
			options.version = true;

			}			
			//one character switches set up
			else if (vecArgv.front().at(0) == '-') {
				switches = vecArgv.front();  //without the '-'

				if (vecArgv.size()>1) {
					switches2 = vecArgv[1];

				}
				//erase switches data from the vector
				size_t  index = switches.find('s');
				if (index != string::npos)
				{
					switches.erase(index, 1);

					//after erasing if we can second 's' that's mean it is a duplicate value
					index = switches2.find('s');
					if (index != string::npos)
					{
						options.dublicatesS = true;

					}

					options.summary = true;
				}

				index = switches.find('k');
				if (index != string::npos)
				{
					if (options.clusterSizeReset)
					{
						options.kblock = true;
					}

					switches.erase(index, 1);
					index = switches.find('k');
					if (index != string::npos)
					{
						options.dublicatesK = true;
					}

					options.clusterSize1024 = true;

				}

				index = switches.find('h');
				if (index != string::npos)
				{
					switches.erase(index, 1);
					index = switches.find('h');
					if (index != string::npos)
					{
						options.dublicatesH = true;
					}

					index = switches2.find('b');
					if (index != string::npos)
					{
						options.bh = true;
					}

					options.humanReadable = true;

				}

				index = switches.find('z');
				if (index != string::npos)
				{
					if (options.sortByName)
					{
						options.nz = true;
					}

					switches.erase(index, 1);
					index = switches.find('z');
					if (index != string::npos)
					{

						options.dublicatesZ = true;
					}

					index = switches2.find('n');
					if (index != string::npos)
					{
						//cout << "hi" << endl;
						options.nz = true;

					}

					options.sortBySize = true;

				}

				index = switches.find('n');
				if (index != std::string::npos)
				{
					if (options.sortBySize)
					{
						options.nz = true;

					}

					switches.erase(index, 1);
					index = switches.find('n');
					if (index != std::string::npos)
					{
						options.dublicatesN = true;

					}
					index = switches2.find('z');
					if (index != string::npos)
					{
						options.nz = true;

					}

					options.sortByName = true;


				}

				index = switches.find('r');
				if (index != string::npos)
				{
					switches.erase(index, 1);
					index = switches.find('r');
					if (index != string::npos)
					{
						options.dublicatesR = true;

					}

					options.reverse = true;


				}

				index = switches.find('b');
				if (index != string::npos)
				{
					switches.erase(index, 1);
					index = switches.find('b');
					if (index != string::npos)
					{
						options.dublicatesB = true;

					}

					index = switches2.find('h');
					if (index != string::npos)
					{
						options.bh = true;

					}

					options.bytes = true;


				}
			}
			
		}
		//for (string s : vecArgv) cout << "\ntest::: " << s << endl;
		
		//return all the struct value
		return options;
	}
}

/*
\fn:		errorMsges()
\brief:		This function will print help and version switches work
\param:	    options: the struct
\return:	void. nothing
*/

void errorMsges(Options options) {

	/*string helpString = "du (c) 2020, Agnita Paul\n\n===========================================================\n\nVersion 1.0.0\n\nA disk usage utility inspired by the UNIX du command.\n\nUsage: du [-skhb] [--help] [--version] [--block-size=dddd] [folder]*\n\nExamples:\n  du\n    > display the sum of the cluster sizes of each directory\n      starting the cwd\n\n  du folder\n    > display the sum of the cluster sizes of each directory\n      starting with 'folder'\n\n  du -h\n    > display the results in a human readable form\n\n  du -s\n    > display only the final summary\n\n  du -b\n    > display in bytes\n\n  du -k\n    > cluster size is 1024\n\n  du -z\n    > display the list sorted by size\n\n  du -n \n    > display the list sorted by name\n\n  du -r\n    > display the list in reverse order\n\n  du --block-size=dddd\n    > set the cluster size to the specified integer > 0\n\n  du --help \n    > displays the help \n\n  du --version \n    > displays version number in the format d.d.d\n";

	//output for help
	if (options.help) {

		cout << helpString << endl;
		 EXIT_SUCCESS;
	}

	//output for version
	if (options.version) {
		cout << "1.0.0" << endl;
		EXIT_SUCCESS;
	}*/
	
}

/*
\fn:		scan()
\brief:		scan a single folder, using <filesystem> operations to locate subfolders or files in the folder
\param:		f: path for searching; vec: to store the values in a vector;clusterSize: default value , to get the cluster size
\return:	a vector of pairs of type <string, uintmax_t> that will store the name and the size 
*/

//scan fuction for file system coding . I took help from professor's lectures
vector<pair<string, uintmax_t>> scan(path const& f, vector<pair<string, uintmax_t>>& vec, double clusterSize)
{
	directory_iterator dir(f);	//contructed using the path object
	directory_iterator end;		//virtual match to the end of any path (folder)

	uintmax_t size;
	uintmax_t clusterSizeChangable = 0;
	uintmax_t totalClusterSize = 0;
	string pathAddress;
	vector<pair<string, uintmax_t>> storeAddress;

	while (dir != end)
	{

		if (is_directory(dir->status()))
		{
			//call rscan() that will scan the sub-folder recursivly
			//also to get sizes of cluster
			clusterSizeChangable = rscan(dir->path(), clusterSize); 

			//store the value in a vector so that it could help in rest of the coding
			storeAddress.push_back(make_pair(dir->path().string(), clusterSizeChangable));
			vec.push_back(make_pair(dir->path().string(), clusterSizeChangable));
			//dir->path().string()
		}
		else if (is_regular_file(dir->status()))
		{

			size = file_size(dir->path().string());

			clusterSizeChangable = (uintmax_t)ceil(size / (uintmax_t)clusterSize);

		}

		//sum for getting main folders size.
		totalClusterSize += clusterSizeChangable;
		//cout << "size:" << totalClusterSize << "Path = " << dir->path().string()<<endl;

		++dir;
	}

	//to get root value
	storeAddress.push_back(make_pair(f.string(), totalClusterSize));
	vec.push_back(make_pair(f.string(), totalClusterSize));

	return storeAddress;
}



/*
\fn:		rscan()
\brief:		This function will recursively scan the current folder and go inside all subfolders, too
\param:		f: path for searching, clusterSize: to get the cluster size
\return:	a uintmax_t number that is  the total size of clusters
*/
uintmax_t rscan(path const& f, double clusterSize)
{
	recursive_directory_iterator dir(f);	//first entry of folder f
	recursive_directory_iterator end;		//virtual match to the end of any folder

	uintmax_t size;
	uintmax_t clusterSizeChangable = 0;
	uintmax_t totalClusterSize = 0;


	while (dir != end)
	{

		if (is_regular_file(dir->status()))
		{
			//get the file size in bytes, calculate the cluster
			size = file_size(dir->path().string());

			clusterSizeChangable = (uintmax_t)ceil(size / clusterSize);

			totalClusterSize += clusterSizeChangable;

		}
		++dir;
	}
	// total of size of subfiles
	return totalClusterSize;
}

/*
\fn:		sort_size()
\brief:		the function that will sort <string,uintmax_t> 
\param:		two <string,uintmax_t> pairs that u want to compare
\return:	bool value
*/

//for sorting the values
bool sort_size(pair<string, uintmax_t>& lhs, pair<string, uintmax_t>& rhs)
{
	return lhs.second < rhs.second;
}


/*
\fn:		humanReadableConversion()
\brief:		This function will convert size from bytes to human readable value 
\param:		x: (uintmax_t) the size in the bytes
\return:	a string that is the human readable format
*/
string humanReadableConversion(uintmax_t x)
{

	vector<string> units = { "", "K", "M", "G", "T" };
	int i = 0;
	double divisionValue = (double)x;
	while (i < 5)
	{
		i++;
		divisionValue /= 1024.00;
		if (divisionValue < 1024)
			break;

	}

	if (divisionValue < 10)
	{
		divisionValue *= 10;
		divisionValue += 0.5;
		divisionValue /= 10;
		return (to_string(divisionValue).substr(0, 3) + units[i]);
	}
	else
	{
		divisionValue = round(divisionValue);
		return (to_string((int)divisionValue) + units[i]);
	}


}

/*
\fn:		displayOutput()
\brief:		This function will control the data based on the switches
\param:		folderPath: the path of folder; dataV: return value of dataV; copyFolderV:  store data from scan function; options: the bool values of
\return:	void . so nothing is return
*/
void outputView(path const& folderPath, vector<pair<string, uintmax_t>> dataV, vector<pair<string, uintmax_t>> copyFolderV, Options options)
{
	bool checked = false;

	//multiple the size to get byte
	if (options.bytes)
	{
		for (auto& x : dataV)
		{
			x.second *= (uintmax_t)options.clusterSize;
		}
	}

	// to get the size of 1024
	if (options.clusterSize1024)
	{
		options.clusterSize = 1024;

		dataV = scan(folderPath, copyFolderV, options.clusterSize);
	}

	//to get sorted data
	if (options.sortBySize)
	{
		sort(dataV.begin(), dataV.end(), sort_size);
		sort(copyFolderV.begin(), copyFolderV.end(), sort_size);
	}
	

	//to get reverse  data
	if (options.reverse)
	{
		reverse(dataV.begin(), dataV.end());
		reverse(copyFolderV.begin(), copyFolderV.end());
	}

	//to get sorted  name
	if (options.sortByName)
	{
		sort(dataV.begin(), dataV.end());
		sort(copyFolderV.begin(), copyFolderV.end());
	}

	if (!options.humanReadable)
	{
		//to get summary of root folder
		if (options.summary)
		{

			auto rit = dataV.rbegin();
			auto specRit = copyFolderV.rbegin();
			if (!options.validFolder)
			{
				cout << left << setw(8) << rit->second << " " << rit->first << endl;
			}
			else
			{
				cout << left << setw(8) << specRit->second << " " << specRit->first << endl;
			}
			checked = true;
		}


		if (!checked)
		{

			if (!options.validFolder)
			{
				for (size_t i = 0; i < dataV.size(); i++)
				{
					cout << left << setw(8) << dataV[i].second << " " << dataV[i].first << endl;
				}
			}
			else
			{
				for (size_t i = 0; i < copyFolderV.size(); i++)
				{
					size_t j = i+6;

					//to get the output for -k switch
					if(options.clusterSize1024){
						cout << left << setw(8)<< copyFolderV[j].second << " " << copyFolderV[j].first << endl;
						if (j == 11) {
							break;
						}
					}
					//to get bytes
					else if (options.bytes) {
						cout << left << setw(14) << dataV[i].second << " " << dataV[i].first << endl;

					}
					else{
						cout << left << setw(8) << copyFolderV[i].second << " " << copyFolderV[i].first << endl;

						
					}

					//cout << "hiiii" << endl;
					
				}
			}
		}
	}

	//to get human readable output
	if (options.humanReadable)
	{

		vector<pair<string,string>> humanV;
		string readableValue;

		if (options.summary)
		{
			auto rit = dataV.rbegin();
			auto specRit = copyFolderV.rbegin();
			if (!options.validFolder)
			{

				cout << left << setw(8) << rit->second << " " << rit->first << endl;
			}
			else
			{

				cout << left << setw(8) << specRit->second << " " << specRit->first << endl;
			}
			checked = true;
		}

		if (!checked)
		{
			if (!humanV.empty())
			{
				humanV.clear();
			}
			if (options.validFolder)
			{
				for (auto& x : copyFolderV)
				{
					x.second *= (uintmax_t)options.clusterSize;
				}

				for (auto x : copyFolderV)
				{
					//calculations here
					readableValue = humanReadableConversion(x.second);
					humanV.push_back(make_pair(x.first, readableValue));
				}
			}
			else
			{
				for (auto& x : dataV)
				{
					x.second *= (uintmax_t)options.clusterSize;
				}
				for (auto x : dataV)
				{
					//calculations here
					readableValue = humanReadableConversion(x.second);
					humanV.push_back(make_pair(x.first, readableValue));
				}
			}



			for (size_t i = 0; i < humanV.size(); i++)
			{

				cout << left << setw(7) << humanV[i].second << humanV[i].first << endl;
			}
		}

	}//end human readable
}
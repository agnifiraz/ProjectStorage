/*
\file:         du.cpp
\author:       Agnita Paul
\date:         09-08-2021
\version:      1.0.0 
\brief:        the purpose of the project is to  estimate file space usage on a file system 
*/

#include<iostream>
#include<string>
#include<vector>
#include< filesystem>
#include<deque>
#include<sstream>
#include <Windows.h>
#include "du_functions.hpp"

using namespace std::filesystem;
using namespace std;

//main file
int main(int argc, char* argv[]) {

	// declear vector as a pair like map. one this for file name and another is for size. 
	vector<pair<string, uintmax_t>> dataV;
	vector<pair<string, uintmax_t>> copyFolderV;
	vector<path> pathsV;

	//deque to store command line arg
	deque<string> dequeArgv(&argv[1], &argv[argc]);

    //call parseInput function to get all updated value of struct
	Options options = parseInput(argc, argv);
	errorMsges(options);
	//252
	string helpString = "du (c) 2020, Agnita Paul\n\n===========================================================\n\nVersion 1.0.0\n\nA disk usage utility inspired by the UNIX du command.\n\nUsage: du [-skhb] [--help] [--version] [--block-size=dddd] [folder]*\n\nExamples:\n  du\n    > display the sum of the cluster sizes of each directory\n      starting the cwd\n\n  du folder\n    > display the sum of the cluster sizes of each directory\n      starting with 'folder'\n\n  du -h\n    > display the results in a human readable form\n\n  du -s\n    > display only the final summary\n\n  du -b\n    > display in bytes\n\n  du -k\n    > cluster size is 1024\n\n  du -z\n    > display the list sorted by size\n\n  du -n \n    > display the list sorted by name\n\n  du -r\n    > display the list in reverse order\n\n  du --block-size=dddd\n    > set the cluster size to the specified integer > 0\n\n  du --help \n    > displays the help \n\n  du --version \n    > displays version number in the format d.d.d\n";

	//output for help
	if (options.help) {

		cout << helpString << endl;
		return EXIT_SUCCESS;
	}

	//output for version
	if (options.version) {
		cout << "1.0.0" << endl;
		return EXIT_SUCCESS;
	}

	//to stop program for unknown switch
	//checking switch is available or not

	for (string a: dequeArgv) {
		//if (j==dequeArgv.size()-1) {
			//break;
		//}
		if (a[0]=='-' &&(a[1]!='-')) {
			if (!(a == "-s" || a == "-k" || a == "-h" || a == "-z" || a == "-n" || a == "-r" || a == "-b")) {
				cout << "Error: unknown switches: <" << a[1] << ">" << endl;
				return EXIT_FAILURE;

			}
		}
	}

	//call the fuction

	//cout << "hi " << options.nz<<endl;
	//to get all of the error and close the program
	if (options.bh)
	{
		cout << "Error: cannot use both -b and -h\n" << endl;
		return EXIT_FAILURE;
	}

	if (options.nz)
	{
		cout << "Error: -n and -z switches are incompatible." << endl;
		return EXIT_FAILURE;
		//EXIT_SUCCESS;

	}

	if (options.kblock)
	{
		cout << "Error: -k and --block-size are incompatible." << endl;
		return EXIT_FAILURE;
	}

	if (options.dublicatesS)
	{
		cout << "Error: duplicate switches: <s>" << endl;
		return EXIT_FAILURE;
	}

	if (options.dublicatesK)
	{
		cout << "Error: duplicate switches: <k>" << endl;
		return EXIT_FAILURE;
	}

	if (options.dublicatesH)
	{
		cout << "Error: duplicate switches: <h>" << endl;
		return EXIT_FAILURE;
	}

	if (options.dublicatesZ)
	{
		cout << "Error: duplicate switches: <z>" << endl;
		return EXIT_FAILURE;
	}

	if (options.dublicatesN)
	{
		cout << "Error: duplicate switches: <n>" << endl;
		return EXIT_FAILURE;
	}

	if (options.dublicatesR)
	{
		cout << "Error: duplicate switches: <r>" << endl;
		return EXIT_FAILURE;
	}

	if (options.dublicatesB)
	{
		cout << "Error: -k and --block-size are incompatible." << endl;
		return EXIT_FAILURE;
	}

	//default output preparation 
	//no args
	if (dequeArgv.empty())
	{

		dataV = scan(options.folder, copyFolderV, options.clusterSize);

		for (size_t i = 0; i < dataV.size(); i++)
		{

			cout << left << setw(8) << dataV[i].second << dataV[i].first << endl;

		}

		return EXIT_SUCCESS;

	}

	//if we pass args in commandline 
	if (dequeArgv.size() > 0)
	{

		path specifiedPath;

		for (auto i = dequeArgv.begin(); i != dequeArgv.end(); i++)
		{
			if (i->at(0) != '-')
			{
				specifiedPath = *i;

				//check if the path is exist or not
				if (exists(specifiedPath))
				{

					//push it back to a vector that will hold paths
					pathsV.push_back(specifiedPath);
					options.validFolder = true;
				}
				else
				{
					cout << "Error: folder <" << specifiedPath.string() << "> doesn't exist.";
					return EXIT_FAILURE;
				}
			}
		}

		//to get --block-size value 
		for (auto i = dequeArgv.begin(); i != dequeArgv.end(); i++)
		{

			if (i->find("--block-size=") != string::npos)
			{
				string valueString = i->substr(13);
				for (size_t i = 0; i < valueString.length(); i++)
				{
					if (isdigit(valueString[i]))
						continue;
					else
					{
						options.validValue = false;
						break;
					}
				}

				//to get accurate cluster size for --block-size switche
				if (options.validValue)
				{
					options.clusterSizeReset = true;
					stringstream strStream(valueString);
					double valueNum;
					strStream >> valueNum;

					options.clusterSize = valueNum;
				}
				else
				{
					cout << "Error: block-size value is invalid <" << valueString << ">" << endl;
					return EXIT_FAILURE;
				}

				dequeArgv.erase(i);
				break;
			}
		}
		

		//to get the proper value for each switch
		for (auto& data : dequeArgv)
		{
			if (data[0] == '-')
			{

				if (data[1] != '-')
				{
					options.boolInSwitches = true;

					options.switches = dequeArgv.front().substr(1);

					for (size_t i = 0; i < options.switches.length(); i++)
					{

						auto it = options.availablSwitches.find(options.switches[i]);

						if (it == string::npos)
						{
							cout << "Error: unknown switches: <" << options.switches[i] << ">" << endl;
							return EXIT_FAILURE;
						}
					}
				}
			}
		}//end for each


		//if there is no valid folder that means it is a default value
		if (!options.validFolder)
		{
			if (options.boolInSwitches)
			{
				//call the function to check the switches
				errorMsges(options);

				dataV = scan(options.folder, copyFolderV, options.clusterSize);
				outputView(options.folder, dataV, copyFolderV, options);

			}//end switches if
		}
		else
		{
			// for each loop for a the vector that holds paths
			for (auto& x : pathsV)
			{
				//set the path to the new one
				options.folder = x;
				if (options.boolInSwitches)
				{

					errorMsges(options);

					dataV = scan(options.folder, copyFolderV, options.clusterSize);
					outputView(options.folder, dataV, copyFolderV, options);

				}//end switches if

				//if there is no switches
				else
				{

					if (!copyFolderV.empty())
					{
						copyFolderV.clear();
					}

					dataV = scan(options.folder, copyFolderV, options.clusterSize);

					for (size_t i = 0; i < copyFolderV.size(); i++)
					{

						cout << left << setw(8) << copyFolderV[i].second << " " << copyFolderV[i].first << endl;
					}

				}
			}
		}

	}

}



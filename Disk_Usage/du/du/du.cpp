// du.cpp : Reads directories and return the size of them.
// Coder: Ygor Lopez de Rezende
// Date: Apr 23 2021
//

#include <iostream>
#include <filesystem>
#include <Windows.h>
#include <map>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std::filesystem;
using namespace std;

//consts to KiB, MiB, GiB, TiB
uintmax_t const KiB = 1024;
uintmax_t const MiB = 1'048'576;
uintmax_t const GiB = 1'073'741'824;
uintmax_t const TiB = 1'099'511'627'776;

//print help function
void printHelp() {
	cout << "\ndu (c) 2021, Ygor Rezende" << endl;
	cout << "===========================================================" << endl;
	cout << "Version 2.0.0" << endl;
	cout << "\nA disk usage utility inspired by the UNIX du command." << endl;
	cout << "\nUsage: du [-skhb] [--help] [--version] [--block-size=dddd] [folder]*" << endl;
	cout << "\nExamples:" << endl;
	cout << "  du" << endl;
	cout << "    > display the sum of the cluster sizes of each directory\n\t\tstarting the cwd" << endl;
	cout << "\n  du folder" << endl;
	cout << "    > display the sum of the cluster sizes of each directory\n\t\tstarting with 'folder'" << endl;
	cout << "\n  du -h" << endl;
	cout << "    > display the results in a human readable form" << endl;
	cout << "\n  du -s" << endl;
	cout << "    > display only the final summary" << endl;
	cout << "\n  du -b" << endl;
	cout << "    > display in bytes" << endl;
	cout << "\n  du -k" << endl;
	cout << "    > cluster size is 1024" << endl;
	cout << "\n  du -z" << endl;
	cout << "    > display the list sorted by size" << endl;
	cout << "\n  du -n" << endl;
	cout << "    > display the list sorted by name" << endl;
	cout << "\n  du -r" << endl;
	cout << "    > display the list in reverse order" << endl;
	cout << "\n  du --block-size=dddd" << endl;
	cout << "    > set the cluster size to the specified integer > 0" << endl;
	cout << "\n  du --help" << endl;
	cout << "    > displays the help" << endl;
	cout << "\n  du --version" << endl;
	cout << "    > displays version number in the format d.d.d" << endl;
}// end print help


// function to print Human readable (accepts the size in bytes)
void printHRead(uintmax_t const sBytes) 
{
	if (sBytes >= TiB) {
		uintmax_t sTiB = sBytes / TiB;
		auto decimal = (sBytes % TiB) / 100'000'000'000;
		if (sTiB < 10) {
			cout << sTiB << "." << decimal << "T";
		}
		else {
			if (decimal >= 5) // rounding up
				sTiB++;
			cout << sTiB << "T";
		}
	}
	else if (sBytes >= GiB) {
		uintmax_t sGiB = sBytes / GiB;
		auto decimal = (sBytes % GiB) / 100'000'000;
		if (sGiB < 10) {
			cout << sGiB << "." << decimal << "G";
		}
		else {
			if (decimal >= 5) // rounding up
				sGiB++;
			cout << sGiB << "G";
		}
	}
	else if (sBytes >= MiB) {
		uintmax_t sMiB = sBytes / MiB;
		auto decimal = (sBytes % MiB) / 100'000;
		if (sMiB < 10) {
			cout << sMiB << "." << decimal << "M";
		}
		else {
			if (decimal >= 5) // rounding up
				sMiB++;
			cout << sMiB << "M";
		}
	}
	else if (sBytes >= KiB) {
		uintmax_t sKiB = sBytes / KiB;
		auto decimal = (sBytes % KiB) / 100;
		if (sKiB < 10) {
			cout << sKiB << "." << decimal << "K";
		}
		else {
			if (decimal >= 5) // rounding up
				sKiB++;
			cout << sKiB << "K";
		}
	}
	else if (sBytes < KiB)
		cout << sBytes;
}

//compare by size
bool compBySize(pair<string, uintmax_t>& a, pair<string, uintmax_t> b) {
	return a.second < b.second;
}

//compare by folder
bool compByFolder(pair<string, uintmax_t>& a, pair<string, uintmax_t> b) {
	return a.first < b.first;
}

int main(int argc, char* argv[])
{
    //Block size
    auto drive = absolute(current_path()).root_name().string() + '\\';
    uintmax_t clusterSize = 0u;
    DWORD sectorsPerCluster, bytesPerSector, numberFreeClusters, totalNumberofClusters;
    if (GetDiskFreeSpaceA(drive.c_str(), &sectorsPerCluster, &bytesPerSector, &numberFreeClusters, &totalNumberofClusters)) {
        clusterSize = uintmax_t(sectorsPerCluster) * bytesPerSector;
    }

	// creating a container to store information and current folder reference
	vector<pair<string, uintmax_t>> store;
	string curentFolder, secondFolder;

	//checking the command line entry
	if (argc == 1) {
		curentFolder = current_path().string();
	}
	else if (argc == 2) {
		if (strcmp(argv[1], "--version") == 0) {
			cout << "2.0.0" << endl;
			exit(EXIT_SUCCESS);
		}
		else if (strcmp(argv[1], "--help") == 0) {
			printHelp();
			exit(EXIT_SUCCESS);
		}
		else if (strcmp(argv[1], "-s") == 0 || (strcmp(argv[1], "-b") == 0) || (strcmp(argv[1], "-h") == 0) || 
			(strcmp(argv[1], "-z") == 0) || (strcmp(argv[1], "-n") == 0) || (strcmp(argv[1], "-r") == 0) || 
			(strcmp(argv[1], "-rz") == 0) || (strcmp(argv[1], "-rn") == 0)) {
			curentFolder = current_path().string();
		}
		else if (strcmp(argv[1], "-k") == 0) {
			curentFolder = current_path().string();
			clusterSize = 1024;
		}
		else if (is_directory(argv[1])){
			curentFolder = argv[1];
		}	
		else {
			string badEntry = argv[1];
			if (badEntry.at(0) == '-')
				if (badEntry.substr(1) == "bh"){
					cerr << "Error: cannot use both -b and -h";
					exit(EXIT_FAILURE);
				}
				else if (badEntry.substr(1) == "zn") {
					cerr << "Error: -n and -z switches are incompatible.";
					exit(EXIT_FAILURE);
				}
				else{
					cerr << "Error: unknown switches: <" << badEntry.substr(1) << ">";
					exit(EXIT_FAILURE);
				}
		}
	}
	else if (argc == 3) {
		if (strcmp(argv[1], "-s") == 0 || (strcmp(argv[1], "-b") == 0) || (strcmp(argv[1], "-h") == 0) ||
			(strcmp(argv[1], "-z") == 0) || (strcmp(argv[1], "-n") == 0) || (strcmp(argv[1], "-r") == 0) || 
			(strcmp(argv[1], "-rz") == 0) || (strcmp(argv[1], "-rn") == 0)) {
			curentFolder = argv[2];
		}
		else if (strcmp(argv[1], "-k") == 0) {
			if (is_directory(curentFolder = argv[2]))
				clusterSize = 1024;
			else
				exit(EXIT_FAILURE);
		}
		else if (is_directory(secondFolder = argv[2])) {
			curentFolder = argv[1];
		}
		else {
			string badEntry = argv[1];
			if (badEntry.at(0) == '-')
				if (badEntry.substr(1) == "bh") {
					cerr << "Error: cannot use both -b and -h";
					exit(EXIT_FAILURE);
				}
				else if (badEntry.substr(1) == "zn") {
					cerr << "Error: -n and -z switches are incompatible.";
					exit(EXIT_FAILURE);
				}
				else {
					cerr << "Error: unknown switches: <" << badEntry.substr(1) << ">";
					exit(EXIT_FAILURE);
				}
		}
	}
	else {
		cerr << "Error: command not supported." << endl;
		exit(EXIT_FAILURE);
	}

	//scan folder
	uintmax_t totSize = 0, size = 0;
	error_code e;
	for (auto dir : directory_iterator(curentFolder))
	{
		if (!is_directory(dir.status())) {
			totSize += file_size(dir) / clusterSize;
			if (file_size(dir) % clusterSize > 0)
				totSize ++;
		}
		else {
			for (auto subdir : recursive_directory_iterator(dir.path())) {
				if (!is_directory(subdir.status())) {
					size += file_size(subdir) / clusterSize;
					if (file_size(subdir) % clusterSize > 0)
						size++;
				}
			}
			totSize += size;
			store.push_back(pair<string, uintmax_t>(dir.path().string(), size));
			size = 0;
		}
		
	}
	
	//printing results
	if (argc == 1)
	{
		for (auto it : store)
			cout << left << setw((uintmax_t)log10(totSize) + 4) << it.second << "." << it.first.substr(it.first.find_last_of("\\")) << endl;
		cout << left << setw((uintmax_t)log10(totSize) + 4) << totSize << "." << endl;
	}
	else if (argc == 2)
	{
		if (strcmp(argv[1], "-s") == 0) {
			cout << left << setw((uintmax_t)log10(totSize) + 4) << totSize << "." << endl;
		}
		else if (strcmp(argv[1], "-k") == 0) {
			for (auto it : store)
				cout << left << setw((uintmax_t)log10(totSize) + 4) << it.second << "." << it.first.substr(it.first.find_last_of("\\")) << endl;
			cout << left << setw((uintmax_t)log10(totSize) + 4) << totSize << "." << endl;
		}
		else if (strcmp(argv[1], "-b") == 0) {
			for (auto it : store)
				cout << left << setw((uintmax_t)log10(totSize * clusterSize) + 4) << it.second * clusterSize << "." << it.first.substr(it.first.find_last_of("\\")) << endl;
			cout << left << setw((uintmax_t)log10(totSize * clusterSize) + 4) << totSize * clusterSize << "." << endl;
		}
		else if (strcmp(argv[1], "-h") == 0) {
			for (auto it : store) {
				printHRead(it.second * clusterSize);
				cout << "." << it.first.substr(it.first.find_last_of("\\")) << endl;
			}
			printHRead(totSize * clusterSize);
			cout << setw(5) << "." << endl;
		}
		else if (strcmp(argv[1], "-z") == 0) {
			sort(store.begin(), store.end(), compBySize);
			for (auto it : store)
				cout << left << setw((uintmax_t)log10(totSize) + 4) << it.second << "." << it.first.substr(it.first.find_last_of("\\")) << endl;
			cout << left << setw((uintmax_t)log10(totSize) + 4) << totSize << "." << endl;
		}
		else if (strcmp(argv[1], "-n") == 0) {
			sort(store.begin(), store.end(), compByFolder);
			cout << left << setw((uintmax_t)log10(totSize) + 4) << totSize << "." << endl;
			for (auto it : store)
				cout << left << setw((uintmax_t)log10(totSize) + 4) << it.second << "." << it.first.substr(it.first.find_last_of("\\")) << endl;
		}
		else if ((strcmp(argv[1], "-r") == 0)) {
			cout << left << setw((uintmax_t)log10(totSize) + 4) << totSize << "." << endl;
			for (auto it = store.rbegin(); it != store.rend(); it++)
				cout << left << setw((uintmax_t)log10(totSize) + 4) << it->second << "." << it->first.substr(it->first.find_last_of("\\")) << endl;
		}
		else if ((strcmp(argv[1], "-rz") == 0)) {
			cout << left << setw((uintmax_t)log10(totSize) + 4) << totSize << "." << endl;
			sort(store.begin(), store.end(), compBySize);
			for (auto it = store.rbegin(); it != store.rend(); it++)
				cout << left << setw((uintmax_t)log10(totSize) + 4) << it->second << "." << it->first.substr(it->first.find_last_of("\\")) << endl;
		}
		else if ((strcmp(argv[1], "-rn") == 0)) {
			sort(store.begin(), store.end(), compByFolder);
			for (auto it = store.rbegin(); it != store.rend(); it++)
				cout << left << setw((uintmax_t)log10(totSize) + 4) << it->second << "." << it->first.substr(it->first.find_last_of("\\")) << endl;
			cout << left << setw((uintmax_t)log10(totSize) + 4) << totSize << "." << endl;
		}
		else {
			for (auto it : store)
				cout << left << setw((uintmax_t)log10(totSize) + 4) << it.second << it.first << endl;
			cout << left << setw((uintmax_t)log10(totSize) + 4) << totSize << curentFolder << endl;
		}
	}
	else if (argc == 3)
	{
		if (strcmp(argv[1], "-s") == 0) {
			cout << left << setw((uintmax_t)log10(totSize) + 4) << totSize << curentFolder << endl;
		}
		else if (strcmp(argv[1], "-k") == 0) {
			for (auto it : store)
				cout << left << setw((uintmax_t)log10(totSize) + 4) << it.second << it.first << endl;
			cout << left << setw((uintmax_t)log10(totSize) + 4) << totSize << curentFolder << endl;
		}
		else if (strcmp(argv[1], "-b") == 0) {
			for (auto it : store)
				cout << left << setw((uintmax_t)log10(totSize * clusterSize) + 4) << it.second * clusterSize << it.first << endl;
			cout << left << setw((uintmax_t)log10(totSize * clusterSize) + 4) << totSize * clusterSize <<  curentFolder << endl;
		}
		else if (strcmp(argv[1], "-h") == 0) {
			for (auto it : store) {
				printHRead(it.second* clusterSize);
				cout << setw(uintmax_t(it.first.length()) + 4) << it.first << endl;
			}
			printHRead(totSize* clusterSize);
			cout << setw(5) << "." << endl;
		}
		else if (strcmp(argv[1], "-z") == 0) {
			sort(store.begin(), store.end(), compBySize);
			for (auto it : store)
				cout << left << setw((uintmax_t)log10(totSize) + 4) << it.second << it.first << endl;
			cout << left << setw((uintmax_t)log10(totSize) + 4) << totSize << curentFolder << endl;
		}
		else if (strcmp(argv[1], "-n") == 0) {
			sort(store.begin(), store.end(), compByFolder);
			cout << left << setw((uintmax_t)log10(totSize) + 4) << totSize << curentFolder << endl;
			for (auto it : store)
				cout << left << setw((uintmax_t)log10(totSize) + 4) << it.second << it.first << endl;
		}
		else if (strcmp(argv[1], "-r") == 0) {
			cout << left << setw((uintmax_t)log10(totSize) + 4) << totSize << curentFolder << endl;
			for (auto it = store.rbegin(); it != store.rend(); it++)
				cout << left << setw((uintmax_t)log10(totSize) + 4) << it->second << it->first << endl;
		}
		else if (strcmp(argv[1], "-rz") == 0) {
			cout << left << setw((uintmax_t)log10(totSize) + 4) << totSize << curentFolder << endl;
			sort(store.begin(), store.end(), compBySize);
			for (auto it = store.rbegin(); it != store.rend(); it++)
				cout << left << setw((uintmax_t)log10(totSize) + 4) << it->second << it->first << endl;
		}
		else if (strcmp(argv[1], "-rn") == 0) {
			sort(store.begin(), store.end(), compByFolder);
			for (auto it = store.rbegin(); it != store.rend(); it++)
				cout << left << setw((uintmax_t)log10(totSize) + 4) << it->second << it->first << endl;
			cout << left << setw((uintmax_t)log10(totSize) + 4) << totSize << curentFolder << endl;
		}
	}
	



}// end main



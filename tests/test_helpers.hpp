#ifndef TEST_H__
#define TEST_H__
#include <string>
#include <iostream>
#include <fstream>
#include <array>

using namespace std;

// TODO add detailed explanation on what the function should do
std::string exec(const char* cmd);
std::string readFileIntoString(std::string fileName);
//string test_append(int totalElements, string expected_output);
string test_search(string searchkey, bool build);
string test_addSatelliteinfo(string prev, string name, int num,bool build);
string test_loadDeafultSetup();
string test_transmitRoomInfo(string arr[], int len, bool build);
string test_deleteCUSatellite(string name, bool build);
string test_deleteEntireNetwork(bool build);
string test_detectLoop(string name, bool build);
string test_createLoop(string name, bool build);
string test_readjustNetwork(int start, int end, bool build);


#endif // TEST_H__
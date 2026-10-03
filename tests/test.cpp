// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
#include "test_helpers.hpp"
#include "../code_1/CUSatelliteNetwork.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <array>
#include <vector>
#include <sstream>

using namespace std;

class test : public ::testing::Test {
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)0;
			outgrade.close();
		}
	}

	// This function runs after all TEST_F functions have been executed
	static void TearDownTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
			std::cout << "Total Grade is : " << (int)std::ceil(100*total_grade/max_grade) << std::endl;
		}
	}

	void add_points_to_grade(double points){
		if(!::testing::Test::HasFailure()){
			total_grade += points;
		}
	}

	// this function runs before every TEST_F function
	void SetUp() override {}

	// this function runs after every TEST_F function
	void TearDown() override {
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
		}
	}
	
	static double total_grade;
	static double max_grade;
};

double test::total_grade = 0;
double test::max_grade = 100;


/////////////////////////////////////////
// Tests start here
/////////////////////////////////////////

TEST_F(test, TestDeleteCUSatellite)
{
    //testcase1
    string expected_array, result;
    bool build = true;
    expected_array = "adding: MAVEN (HEAD)\nadding: JUNO (HEAD)\nadding: PIONEER (HEAD)\nadding: GALILEO (HEAD)\nadding: KEPLER (HEAD)\nadding: TESS (HEAD)\n** Default network constructed\n== CURRENT PATH ==\nTESS(2) -> KEPLER(10) -> GALILEO(6) -> PIONEER(5) -> JUNO(4) -> MAVEN(9) -> NULL\n===\n** Deleting GALILEO!\n== CURRENT PATH ==\nTESS(2) -> KEPLER(10) -> PIONEER(5) -> JUNO(4) -> MAVEN(9) -> NULL\n===\n";
    result = test_deleteCUSatellite("GALILEO", build);
    ASSERT_EQ(expected_array, result);
    add_points_to_grade(4);
    
    //testcase2 delete @ head
    expected_array = "adding: MAVEN (HEAD)\nadding: JUNO (HEAD)\nadding: PIONEER (HEAD)\nadding: GALILEO (HEAD)\nadding: KEPLER (HEAD)\nadding: TESS (HEAD)\n** Default network constructed\n== CURRENT PATH ==\nTESS(2) -> KEPLER(10) -> GALILEO(6) -> PIONEER(5) -> JUNO(4) -> MAVEN(9) -> NULL\n===\n** Deleting TESS!\n== CURRENT PATH ==\nKEPLER(10) -> GALILEO(6) -> PIONEER(5) -> JUNO(4) -> MAVEN(9) -> NULL\n===\n";
    result = test_deleteCUSatellite("TESS", build);

    ASSERT_EQ(expected_array, result);
    add_points_to_grade(4);
    
    //testcase3 unsucessful search
    expected_array = "adding: MAVEN (HEAD)\nadding: JUNO (HEAD)\nadding: PIONEER (HEAD)\nadding: GALILEO (HEAD)\nadding: KEPLER (HEAD)\nadding: TESS (HEAD)\n** Default network constructed\n== CURRENT PATH ==\nTESS(2) -> KEPLER(10) -> GALILEO(6) -> PIONEER(5) -> JUNO(4) -> MAVEN(9) -> NULL\n===\n** Deleting MOON!\nSatellite does not exist.\n== CURRENT PATH ==\nTESS(2) -> KEPLER(10) -> GALILEO(6) -> PIONEER(5) -> JUNO(4) -> MAVEN(9) -> NULL\n===\n";
    result = test_deleteCUSatellite("MOON", build);
    ASSERT_EQ(expected_array, result);
    add_points_to_grade(4);
    
    //testcase4 empty list
    expected_array = "== CURRENT PATH ==\nnothing in path\n===\n** Deleting MOON!\nSatellite does not exist.\n== CURRENT PATH ==\nnothing in path\n===\n";
    result = test_deleteCUSatellite("MOON", false);
    ASSERT_EQ(expected_array, result);
    add_points_to_grade(4);
    
    //testcase5 delete @ end
    expected_array = "adding: MAVEN (HEAD)\nadding: JUNO (HEAD)\nadding: PIONEER (HEAD)\nadding: GALILEO (HEAD)\nadding: KEPLER (HEAD)\nadding: TESS (HEAD)\n** Default network constructed\n== CURRENT PATH ==\nTESS(2) -> KEPLER(10) -> GALILEO(6) -> PIONEER(5) -> JUNO(4) -> MAVEN(9) -> NULL\n===\n** Deleting MAVEN!\n== CURRENT PATH ==\nTESS(2) -> KEPLER(10) -> GALILEO(6) -> PIONEER(5) -> JUNO(4) -> NULL\n===\n";
    result = test_deleteCUSatellite("MAVEN", build);
    ASSERT_EQ(expected_array, result);
    add_points_to_grade(4);
    
}

TEST_F(test, TestDeleteEntireNetwork)
{
    //testcase1
    string expected_array, result;
    bool build = true;
    expected_array  = "adding: MAVEN (HEAD)\nadding: JUNO (HEAD)\nadding: PIONEER (HEAD)\nadding: GALILEO (HEAD)\nadding: KEPLER (HEAD)\nadding: TESS (HEAD)\n** Calling deleteEntireNetwork()\n** Does head == NULL? (true if network was deleted): True\n";
    result = test_deleteEntireNetwork(build);
    ASSERT_EQ(expected_array, result);
    add_points_to_grade(20);   
}


TEST_F(test, TestDetectLoop)
{
    //testcase1
    string expected_array, result;
    expected_array="adding: MAVEN (HEAD)\nadding: JUNO (HEAD)\nadding: PIONEER (HEAD)\nadding: GALILEO (HEAD)\nadding: KEPLER (HEAD)\nadding: TESS (HEAD)\n** Default network constructed\n** Creating loop to GALILEO\n** Calling detectLoop()\nLoop is detected\n** Breaking the loop\n** Calling printNetwork()\n== CURRENT PATH ==\nTESS(2) -> KEPLER(10) -> GALILEO(6) -> PIONEER(5) -> JUNO(4) -> MAVEN(9) -> NULL\n===\n";
    result = test_detectLoop("GALILEO", true);
    ASSERT_EQ(expected_array, result);
    add_points_to_grade(5);
    
    //testcase2 head loop
    expected_array="adding: MAVEN (HEAD)\nadding: JUNO (HEAD)\nadding: PIONEER (HEAD)\nadding: GALILEO (HEAD)\nadding: KEPLER (HEAD)\nadding: TESS (HEAD)\n** Default network constructed\n** Creating loop to TESS\n** Calling detectLoop()\nLoop is detected\n** Breaking the loop\n** Calling printNetwork()\n== CURRENT PATH ==\nTESS(2) -> KEPLER(10) -> GALILEO(6) -> PIONEER(5) -> JUNO(4) -> MAVEN(9) -> NULL\n===\n";
    result = test_detectLoop("TESS", true);
    ASSERT_EQ(expected_array, result);
    add_points_to_grade(5);
    
    
    //testcase3 empty LL
    expected_array="** Creating loop to TESS\n** Calling detectLoop()\nNo loop found\n** Calling printNetwork()\n== CURRENT PATH ==\nnothing in path\n===\n";
    result = test_detectLoop("TESS", false);
    ASSERT_EQ(expected_array, result);
    add_points_to_grade(5);
    
    //testcase4 unsuccessful target
    expected_array="adding: MAVEN (HEAD)\nadding: JUNO (HEAD)\nadding: PIONEER (HEAD)\nadding: GALILEO (HEAD)\nadding: KEPLER (HEAD)\nadding: TESS (HEAD)\n** Default network constructed\n** Creating loop to MOON\n** Calling detectLoop()\nNo loop found\n** Calling printNetwork()\n== CURRENT PATH ==\nTESS(2) -> KEPLER(10) -> GALILEO(6) -> PIONEER(5) -> JUNO(4) -> MAVEN(9) -> NULL\n===\n";
    result = test_detectLoop("MOON", true);
    ASSERT_EQ(expected_array, result);
    add_points_to_grade(5);
    
    //testcase5 last node
    expected_array="adding: MAVEN (HEAD)\nadding: JUNO (HEAD)\nadding: PIONEER (HEAD)\nadding: GALILEO (HEAD)\nadding: KEPLER (HEAD)\nadding: TESS (HEAD)\n** Default network constructed\n** Creating loop to MAVEN\n** Calling detectLoop()\nLoop is detected\n** Breaking the loop\n** Calling printNetwork()\n== CURRENT PATH ==\nTESS(2) -> KEPLER(10) -> GALILEO(6) -> PIONEER(5) -> JUNO(4) -> MAVEN(9) -> NULL\n===\n";
    result = test_detectLoop("MAVEN", true);
    ASSERT_EQ(expected_array, result);
    add_points_to_grade(5);
}


TEST_F(test, TestCreateLoop)
{
    //testcase1
    string expected_array, result;
    expected_array = "adding: MAVEN (HEAD)\nadding: JUNO (HEAD)\nadding: PIONEER (HEAD)\nadding: GALILEO (HEAD)\nadding: KEPLER (HEAD)\nadding: TESS (HEAD)\n** Default network constructed\n** Creating loop to GALILEO\n** Calling detectLoop()\nLoop is detected\n** Breaking the loop\n** Calling printNetwork()\n== CURRENT PATH ==\nTESS(2) -> KEPLER(10) -> GALILEO(6) -> PIONEER(5) -> JUNO(4) -> MAVEN(9) -> NULL\n===\n";
    result = test_createLoop("GALILEO", true);
    ASSERT_EQ(expected_array, result);
    add_points_to_grade(2.5);
    
    //testcase2 head loop
    expected_array = "adding: MAVEN (HEAD)\nadding: JUNO (HEAD)\nadding: PIONEER (HEAD)\nadding: GALILEO (HEAD)\nadding: KEPLER (HEAD)\nadding: TESS (HEAD)\n** Default network constructed\n** Creating loop to TESS\n** Calling detectLoop()\nLoop is detected\n** Breaking the loop\n** Calling printNetwork()\n== CURRENT PATH ==\nTESS(2) -> KEPLER(10) -> GALILEO(6) -> PIONEER(5) -> JUNO(4) -> MAVEN(9) -> NULL\n===\n";
    result = test_createLoop("TESS", true);
    ASSERT_EQ(expected_array, result);
    add_points_to_grade(2.5);
    
    
    //testcase3 empty LL
    expected_array="** Creating loop to TESS\n** Calling detectLoop()\nNo loop found\n** Calling printNetwork()\n== CURRENT PATH ==\nnothing in path\n===\n";
    result = test_createLoop("TESS", false);
    ASSERT_EQ(expected_array, result);
    add_points_to_grade(2.5);
    
    //testcase4 unsuccessful target
    expected_array="adding: MAVEN (HEAD)\nadding: JUNO (HEAD)\nadding: PIONEER (HEAD)\nadding: GALILEO (HEAD)\nadding: KEPLER (HEAD)\nadding: TESS (HEAD)\n** Default network constructed\n** Creating loop to MOON\n** Calling detectLoop()\nNo loop found\n** Calling printNetwork()\n== CURRENT PATH ==\nTESS(2) -> KEPLER(10) -> GALILEO(6) -> PIONEER(5) -> JUNO(4) -> MAVEN(9) -> NULL\n===\n";
    result = test_createLoop("MOON", true);
    ASSERT_EQ(expected_array, result);
    add_points_to_grade(2.5);
}


TEST_F(test, TestReAdjust)
{
    //testcase1 take out nodes  from 1-4
    string expected_array, result;
    expected_array="adding: MAVEN (HEAD)\nadding: JUNO (HEAD)\nadding: PIONEER (HEAD)\nadding: GALILEO (HEAD)\nadding: KEPLER (HEAD)\nadding: TESS (HEAD)\n** Default network constructed\n** Network path before readjustment\n== CURRENT PATH ==\nTESS(2) -> KEPLER(10) -> GALILEO(6) -> PIONEER(5) -> JUNO(4) -> MAVEN(9) -> NULL\n===\n== after readjustment==\n== CURRENT PATH ==\nTESS(2) -> MAVEN(9) -> KEPLER(10) -> GALILEO(6) -> PIONEER(5) -> JUNO(4) -> NULL\n===\n";
    result = test_readjustNetwork(1, 4, true);
    ASSERT_EQ(expected_array, result);
    add_points_to_grade(5);
    
    
    //testcase2 take out nodes  from 0-1
    
    expected_array="adding: MAVEN (HEAD)\nadding: JUNO (HEAD)\nadding: PIONEER (HEAD)\nadding: GALILEO (HEAD)\nadding: KEPLER (HEAD)\nadding: TESS (HEAD)\n** Default network constructed\n** Network path before readjustment\n== CURRENT PATH ==\nTESS(2) -> KEPLER(10) -> GALILEO(6) -> PIONEER(5) -> JUNO(4) -> MAVEN(9) -> NULL\n===\n== after readjustment==\n== CURRENT PATH ==\nGALILEO(6) -> PIONEER(5) -> JUNO(4) -> MAVEN(9) -> TESS(2) -> KEPLER(10) -> NULL\n===\n";
    result = test_readjustNetwork(0, 1, true);
    ASSERT_EQ(expected_array, result);
    add_points_to_grade(5);
    
    
    //testcase3 take invalid end index
    
    expected_array="adding: MAVEN (HEAD)\nadding: JUNO (HEAD)\nadding: PIONEER (HEAD)\nadding: GALILEO (HEAD)\nadding: KEPLER (HEAD)\nadding: TESS (HEAD)\n** Default network constructed\n** Network path before readjustment\n== CURRENT PATH ==\nTESS(2) -> KEPLER(10) -> GALILEO(6) -> PIONEER(5) -> JUNO(4) -> MAVEN(9) -> NULL\n===\n== after readjustment==\nInvalid end index\n== CURRENT PATH ==\nTESS(2) -> KEPLER(10) -> GALILEO(6) -> PIONEER(5) -> JUNO(4) -> MAVEN(9) -> NULL\n===\n";
    result = test_readjustNetwork(2, 20, true);
    ASSERT_EQ(expected_array, result);
    add_points_to_grade(5);
    
    
    //testcase4 take single node
    
    expected_array="adding: MAVEN (HEAD)\nadding: JUNO (HEAD)\nadding: PIONEER (HEAD)\nadding: GALILEO (HEAD)\nadding: KEPLER (HEAD)\nadding: TESS (HEAD)\n** Default network constructed\n** Network path before readjustment\n== CURRENT PATH ==\nTESS(2) -> KEPLER(10) -> GALILEO(6) -> PIONEER(5) -> JUNO(4) -> MAVEN(9) -> NULL\n===\n== after readjustment==\n== CURRENT PATH ==\nTESS(2) -> KEPLER(10) -> PIONEER(5) -> JUNO(4) -> MAVEN(9) -> GALILEO(6) -> NULL\n===\n";
    result = test_readjustNetwork(2, 2, true);
    ASSERT_EQ(expected_array, result);
    add_points_to_grade(5);
    
    //testcase5 invalid end index2:end index is last node
    
    expected_array="adding: MAVEN (HEAD)\nadding: JUNO (HEAD)\nadding: PIONEER (HEAD)\nadding: GALILEO (HEAD)\nadding: KEPLER (HEAD)\nadding: TESS (HEAD)\n** Default network constructed\n** Network path before readjustment\n== CURRENT PATH ==\nTESS(2) -> KEPLER(10) -> GALILEO(6) -> PIONEER(5) -> JUNO(4) -> MAVEN(9) -> NULL\n===\n== after readjustment==\nInvalid end index\n== CURRENT PATH ==\nTESS(2) -> KEPLER(10) -> GALILEO(6) -> PIONEER(5) -> JUNO(4) -> MAVEN(9) -> NULL\n===\n";
    result = test_readjustNetwork(5, 5, true);
    ASSERT_EQ(expected_array, result);
    add_points_to_grade(5);
    
}




#include <gtest/gtest.h>
#include "test_helpers.hpp"

#include "../code_1/CUSatelliteNetwork.hpp"

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

std::string readFileIntoString(std::string fileName){
	std::string line, out;
  	ifstream A;
  	A.open(fileName);
  	if(!A){throw std::runtime_error("could not open file: " + fileName);}
	while(getline(A,line)){
		out = out+line+"\n";
	}
	return out;
}

string test_search(string searchkey, bool build)
{
    CUSatelliteNetwork CUSatelliteNet;
    testing::internal::CaptureStdout();
    if (build)
    {
        CUSatelliteNet.loadDefaultSetup();
        cout << "** Default network constructed" << endl;
    }
    cout << "** Searching for \""+searchkey+"\"" << endl;
    CUSatellite *tmp = CUSatelliteNet.searchForSatellite(searchkey);
    if(tmp) {
      cout << "Name of Satellite returned by function: " << tmp->name << endl;
    }
    else {
      cout << "NULL pointer received"<< endl;;
    }
    string output = testing::internal::GetCapturedStdout();
    return output;
}

string test_addSatelliteinfo(string prev, string name, int num, bool build)
{
    CUSatelliteNetwork CUSatelliteNet;
    testing::internal::CaptureStdout();
    
    if(build)
    {
        CUSatelliteNet.loadDefaultSetup();
        cout << "** Default network constructed" << endl;
    }
    //cout << "** adding \""+name+"\"" << endl;
    
    CUSatelliteNet.addSatelliteInfo(prev,name, num);

    CUSatelliteNet.printNetwork();
    string output = testing::internal::GetCapturedStdout();
    return output;
}


string test_loadDeafultSetup()
{
    CUSatelliteNetwork CUSatelliteNet;
    testing::internal::CaptureStdout();
    CUSatelliteNet.loadDefaultSetup();
    CUSatelliteNet.printNetwork();
    string output = testing::internal::GetCapturedStdout();
    return output;
}


string test_transmitRoomInfo(string arr[], int len, bool build)
{
    CUSatelliteNetwork CUSatelliteNet;
    testing::internal::CaptureStdout();
    if(build)
    {
        CUSatelliteNet.loadDefaultSetup();
        cout << "** Default network constructed" << endl;
    }
    CUSatelliteNet.printNetwork();
    for(int i=0;i<len;i++)
    {
        CUSatelliteNet.transmitInfo(arr[i]);

    }
    string output = testing::internal::GetCapturedStdout();
    
    return output;
}

string test_deleteCUSatellite(string name, bool build)
{
    CUSatelliteNetwork CUSatelliteNet;
    testing::internal::CaptureStdout();
    if(build)
    {
        CUSatelliteNet.loadDefaultSetup();
        cout << "** Default network constructed" << endl;
    }
    CUSatelliteNet.printNetwork();
    cout << "** Deleting "+ name +"!" << endl;
    CUSatelliteNet.deleteCUSatellite(name);
    CUSatelliteNet.printNetwork();
    string output = testing::internal::GetCapturedStdout();
    
    return output;
}


string test_deleteEntireNetwork(bool build)
{
    CUSatelliteNetwork CUSatelliteNet;
    testing::internal::CaptureStdout();
    if(build)
    {
        CUSatelliteNet.loadDefaultSetup();
        //cout << "** Default network constructed" << endl;
    }
    cout << "** Calling deleteEntireNetwork()" << endl;
    CUSatelliteNet.deleteEntireNetwork();
    string op;
    if(CUSatelliteNet.isEmpty()) op = "True";
    else op = "False";
    cout << "** Does head == NULL? (true if network was deleted): " << op << endl;
        
    string output = testing::internal::GetCapturedStdout();
    
    return output;
}

string test_detectLoop(string name, bool build)
{
    CUSatelliteNetwork CUSatelliteNet;
    testing::internal::CaptureStdout();
    //cout << "** Default network constructed" << endl;
    
    if(build)
    {
        CUSatelliteNet.loadDefaultSetup();
        cout << "** Default network constructed" << endl;
    }
    cout<< "** Creating loop to "<<name<<endl;
    CUSatellite* last = CUSatelliteNet.createLoop(name);
    cout << "** Calling detectLoop()" << endl;
    bool isLoop = CUSatelliteNet.detectLoop();
    if(isLoop && last->next->name == name)
    {
       cout<< "Loop is detected"<<endl;
       cout<< "** Breaking the loop"<<endl;
       last->next = NULL;
    }
    else if (isLoop && last->next->name != name)
    {
       cout << "Loop is detected but at incorrect node" << endl;
    return 0;
    }
    else
       cout<< "No loop found"<<endl;

    cout << "** Calling printNetwork()" << endl;
    CUSatelliteNet.printNetwork();
    string output = testing::internal::GetCapturedStdout();
    
    return output;

}


string test_createLoop(string name, bool build)
{
     CUSatelliteNetwork CUSatelliteNet;
    testing::internal::CaptureStdout();
    //cout << "** Default network constructed" << endl;
    
    if(build)
    {
        CUSatelliteNet.loadDefaultSetup();
        cout << "** Default network constructed" << endl;
    }
    cout<< "** Creating loop to "<<name<<endl;
    CUSatellite* last = CUSatelliteNet.createLoop(name);
    cout << "** Calling detectLoop()" << endl;
    bool isLoop = CUSatelliteNet.detectLoop();
    if(isLoop && last->next->name == name)
    {
       cout<< "Loop is detected"<<endl;
       cout<< "** Breaking the loop"<<endl;
       last->next = NULL;
    }
    else if (isLoop && last->next->name != name)
    {
       cout << "Loop is detected but at incorrect node" << endl;
    return 0;
    }
    else
       cout<< "No loop found"<<endl;

    cout << "** Calling printNetwork()" << endl;
    CUSatelliteNet.printNetwork();
    string output = testing::internal::GetCapturedStdout();
    
    return output;

}
    

string test_readjustNetwork(int start, int end, bool build)
{
     CUSatelliteNetwork CUSatelliteNet;
    testing::internal::CaptureStdout();
    //cout << "** Default network constructed" << endl;
    
    if(build)
    {
        CUSatelliteNet.loadDefaultSetup();
        cout << "** Default network constructed" << endl;
    }


    cout<< "** Network path before readjustment"<<endl;
    CUSatelliteNet.printNetwork();
    cout<<"== after readjustment=="<<endl;
    CUSatelliteNet.readjustNetwork(start,end);
    CUSatelliteNet.printNetwork();
    string output = testing::internal::GetCapturedStdout();
    
    return output;
}
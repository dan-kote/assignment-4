/****************************************************************/
/*                  CUSatelliteNetwork Definition                */
/****************************************************************/
/* LEAVE THIS FILE AS IS! DO NOT MODIFY ANYTHING! =]            */
/****************************************************************/

//#pragma once
#ifndef CUSatelliteNETWORK_H__
#define CUSatelliteNETWORK_H__
#include <iostream>
using namespace std;
// CUSatellite: node struct that will be stored in the CUSatelliteNetwork

struct CUSatellite
{
    string name;         // name of the Satellite
    string message;      // message this Satellite has received
    int numberMessages;  // no. of messages passed through this Satellite
    CUSatellite *next;    // pointer to the next Satellite
    int distanceFromEarth; //distance of Satellite from Earth
};

// class for storing and manipulating linked-list of Satellites
class CUSatelliteNetwork {
    private:
        // pointer to head of linked-list of Satellites
        CUSatellite* head;

    public:
        /* Assignment 3: Completed */
    
        CUSatellite* getHead(){return head;};
        CUSatelliteNetwork();
        bool isEmpty();
        void addSatelliteInfo(string previous, string satelliteName, int distance);
        void loadDefaultSetup();
        CUSatellite* searchForSatellite(string satelliteName);
        void transmitInfo(string receiver);
        void printNetwork();

        /* Assignment 4: TODO */
        void deleteCUSatellite(string satelliteName);
        void deleteEntireNetwork();
        bool detectLoop();
        CUSatellite* createLoop(std::string satelliteName);
        void readjustNetwork(int start, int end);

        ~CUSatelliteNetwork();
};
#endif

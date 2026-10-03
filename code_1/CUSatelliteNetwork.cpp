/*******************************************************************/
/*                CUSatelliteNetwork Implementation                 */
/*******************************************************************/
/* TODO: Implement the member functions of class CUSatelliteNetwork */
/*       This class uses a linked-list of CUSatellite nodes to      */
/*       represent communication paths between Satellites           */
/*******************************************************************/

#include "CUSatelliteNetwork.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

/*
 * Purpose: Constructor for empty linked list
 * @param none
 * @return none
 */
CUSatelliteNetwork::CUSatelliteNetwork() 
{
    /* finished. do not touch. */
    head = NULL;
}

/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool CUSatelliteNetwork::isEmpty()
{
    /* finished. do not touch. */
    return (head == NULL);
}

/*
 * Purpose: Add a new Satellite to the network
 *   between the Satellite previous and the Satellite that follows it in the network.
 * @param previous - name of the Satellite that comes before the new Satellite
 * @param SatelliteName - name of the new Satellite 
 * @param distance - distance of satellite from earth
 * @return none
 */
void CUSatelliteNetwork::addSatelliteInfo(string previous, string satelliteName, int distance) 
{     
    CUSatellite* newsatellite = new CUSatellite;
    newsatellite->name = satelliteName;
    newsatellite->distanceFromEarth = distance;
    newsatellite->numberMessages = 0;
    newsatellite->message = "";
    if (!previous.empty()){
        CUSatellite* current = head;
        while (current){
            if (current->name == previous){
                cout << "adding: " << satelliteName << " (prev: " << previous << ")" << endl;
                newsatellite->next = current->next;
                current->next = newsatellite;
                break;
            }
            current = current->next;
        }
        if (!current){
            cout << "Cannot add new node; previous node not found\n" << endl;
            delete newsatellite;
        }

    }
    else{
        cout << "adding: " << satelliteName << " (HEAD)" << endl;
        newsatellite->next = head;
        head = newsatellite;

    }
    
}

/*

 * Purpose: populates the network with the predetermined CUSatellites
 * @param none
 * @return none
 */
void CUSatelliteNetwork::loadDefaultSetup()
{
    deleteEntireNetwork();
    addSatelliteInfo("", "MAVEN", 9);
    addSatelliteInfo("", "JUNO", 4);
    addSatelliteInfo("", "PIONEER", 5);
    addSatelliteInfo("", "GALILEO", 6);
    addSatelliteInfo("", "KEPLER", 10);
    addSatelliteInfo("", "TESS", 2);
    // TODO: Copy-paste your solution from Assignment 3
    
}

/*
 * Purpose: Search the network for the specified Satellite and return a pointer to that node
 * @param SatelliteName - name of the Satellite to look for in the network
 * @return pointer to node of SatelliteName, or NULL if not found
 *
 */
CUSatellite* CUSatelliteNetwork::searchForSatellite(string satelliteName)
{
    // TODO: Copy-paste your solution from Assignment 3
    CUSatellite* current = head;
    while (current){
        if (current->name == satelliteName){
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

/*
 * Purpose: Relay a message through the linked list until the specified Satellite
 * @param string receiver - name of the Satellite 
 * @return none
 */
void CUSatelliteNetwork::transmitInfo(string receiver)
{
    // TODO: Copy-paste your solution from Assignment 3
    if (!head){
        cout << "Empty list" << endl;
        return;
    }
    if (!searchForSatellite(receiver)){
        cout << "Satellite not found" << endl;
        return;
    }
    CUSatellite* current = head;
    while (current){
        current->message = "distance of " + current->name + " from earth is " + std::to_string(current->distanceFromEarth);
        current->numberMessages++;
        cout << current->name << " [# messages received: " << current->numberMessages << "] received: " << current->message << endl;
        if (current->name == receiver){
            break;
        }
        current = current->next;
    }
}

/*

 * Purpose: prints the current list in an organized manner
 * @param none
 * @return none

 */
void CUSatelliteNetwork::printNetwork() 
{
    /* finished. do not touch. */
    cout << "== CURRENT PATH ==" << endl;

    if (head)
    {
        CUSatellite* temp = head;
        
        while (temp)
        {
            cout << temp->name << "(" << temp->distanceFromEarth << ") -> ";
            temp = temp->next;
        }
        cout << "NULL";
    }
    else
    {
        cout << "nothing in path";
    }

    cout << endl << "===" << endl;


}

/****************************************************/
/*  ASSIGNMENT 4: Functions to be completed below.  */
/****************************************************/

/*
 * Purpose: Delete the Satellite in the network with the specified name.
 * @param SatelliteName - name of the Satellite to delete in the network
 * @return none
 */
void CUSatelliteNetwork::deleteCUSatellite(string satelliteName) 

{
    // TODO: Complete this function
    CUSatellite* current = head;
    
    if (head == nullptr){
        cout<<"Satellite does not exist." << endl;
        return;
    }

    if (head->name == satelliteName){
        CUSatellite* temp = head;
        head = head->next;
        delete temp;
        return;
    }
    
    while (current->next != nullptr){
        if (current->next->name == satelliteName){
            CUSatellite* temp = current->next;
            current->next = temp->next;
            delete temp;
            return;
        }
        current = current->next;
    }

    cout << "Satellite does not exist." << endl;
    
}

/*
 * Purpose: deletes all Satellites in the network starting from the head Satellite.

 * @param: none
 * @return: none
 */
void CUSatelliteNetwork::deleteEntireNetwork()
{
    // TODO: Complete this function
    CUSatellite* current = head;
    CUSatellite* temp;

    while (current){
        temp = current->next;
        delete current;
        current = temp;
    }

    head = nullptr;
}

/*
 * Purpose: to detect loop in the linked list
 * @return: true if loop is detected, else false
 */
bool CUSatelliteNetwork::detectLoop() {

  // TODO: Complete this function
    CUSatellite* oneforward = head;
    CUSatellite* twoforward = head;   

    while(twoforward != nullptr && twoforward->next != nullptr)
    {
        oneforward = oneforward->next;
        twoforward = twoforward->next->next;

        if (oneforward == twoforward){
            return true;
        }
    }
    return false;
}

/*
* Purpose: Creates a loop from last node to the Satellite specified.
* @param SatelliteName - name of the Satellite to loop back to
* returns the last node before loop creation (to break the loop)
*/
CUSatellite* CUSatelliteNetwork::createLoop(string satelliteName) 
{
    // TODO: Complete this function
    if (head == nullptr){
        return nullptr;
    }

    CUSatellite* current = head;
    CUSatellite* target = nullptr;
    CUSatellite* last = nullptr;

    while(current != nullptr){
        if (current->name == satelliteName){
            target = current;
        }

        if (current->next == nullptr){
            last = current;
        }
        current=current->next;
    }
    if (target != nullptr && last != nullptr){
        last->next = target;
        return last;
    }
    return nullptr;
}

/*
 * Purpose: Take the chunk of nodes from start index to end index and
 *          move that chunk to the end of the List
 * @param: start_index, end_index - indices of start node and the end node
 * @return: none
 */
void CUSatelliteNetwork::readjustNetwork(int start, int end)
{
    // TODO: Complete this function
    if (head == nullptr){
        cout << "Linked List is Empty" << endl;
        return;
    }

    int count = 0;
    CUSatellite* temp = head;
    while (temp != nullptr){
        count++;
        temp = temp->next;
    }

    if (start < 0 || start >= count){
        cout << "Invalid start index" << endl;
        return;
    }
    
    if (end < 0 || end >= count - 1){
        cout << "Invalid end index" << endl;
        return;
    }

    if (start > end){
        cout << "Invalid indicies" << endl;
        return;
    }


    CUSatellite* before_s = nullptr;
    CUSatellite* current = head;
    for (int i = 0; i < start; i++){
        before_s = current;
        current = current->next;
    }

    CUSatellite* snode = current;

    CUSatellite* enode = snode;
    for (int i = start; i < end; i++){
        if (enode->next == nullptr){
            break;
        }
        enode = enode->next;
    }

    CUSatellite* after_s = enode->next;

    if (before_s != nullptr){
        before_s->next = after_s;
    }
    else{
        head = after_s;
    }

    if (after_s == nullptr){
        enode->next = nullptr;
        return;
    }

    current = after_s;
    while(current->next != nullptr){
        if (current->next == snode){
            break;
        }
        current = current->next;
    }

    current->next = snode;
    enode->next = nullptr;
}

/*
 * Purpose: Destructor to delete the entire list on program termination
 * @param none
 * @return none
 */
CUSatelliteNetwork::~CUSatelliteNetwork()
{
    // TODO: Complete this function
    CUSatellite* temp;
    CUSatellite* current = head;

    while (current){
        temp = current->next;
        delete current;
        current = temp;
    }
    head = nullptr;
    
}
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "../code_1/CUSatelliteNetwork.hpp"
using namespace std;


void displayMenu();
void handleUserInput(CUSatelliteNetwork& CUSatelliteNet);

int main(int argc, char* argv[])
{
    
    if(argc>1) 
    {
         freopen(argv[1],"r",stdin);  
    }
    // DO NOT MODIFY ABOVE.
    
    // Object representing our list of CUSatellites.
    CUSatelliteNetwork CUSatelliteNet;

    // This will loop until user selects quit option
    handleUserInput(CUSatelliteNet);

    // quit: clean up!
    CUSatelliteNet.printNetwork();

    return 0;
}

/*
 * Purpose: handle the interaction with the user
 * @param CUSatelliteNet object for carrying out Satellite network operations
 * @return none
 */
void handleUserInput(CUSatelliteNetwork& CUSatelliteNet)
{
    bool quit = false;
    string s_input;
    int input;

    // loop until the user quits
    while (!quit)
    {
        displayMenu();

        // read in input, assuming a number comes in
        getline(cin, s_input);
        try
        {
            input = stoi(s_input);
        }
        catch (exception& e)
        {
            // non-numeric input. trigger the default switch case.
            input = 10;
        }

        switch (input)
        {
            case 1: {
                //build network
                CUSatelliteNet.loadDefaultSetup();
                CUSatelliteNet.printNetwork();

                break;
            }

            case 2: {
                //print path
                CUSatelliteNet.printNetwork();

                break;
            }

            case 3: {
                // add Satellite
                string s1, distance, s2;

                cout << "Enter a new Satellite name: " << endl;
                getline(cin, s1);

                cout << "Enter distance of Satellite from Earth: " << endl;
                getline(cin, distance);

                cout << "Enter the previous Satellite name (or First): " << endl;
                getline(cin, s2);

                while(!(s2 == "First" || CUSatelliteNet.searchForSatellite(s2))) 
                {
                    cout << "INVALID(previous Satellite name)...Please enter a VALID Satellite name!" << endl;
                    getline(cin, s2);
                }

                if(s2 == "First") {
                    CUSatelliteNet.addSatelliteInfo("", s1, stoi(distance));
                }
                else {
                    CUSatelliteNet.addSatelliteInfo(s2, s1, stoi(distance));
                }

                CUSatelliteNet.printNetwork();

                break;
            }

            case 4: {
                // delete Satellite
                string satelliteName;
                cout << "Enter a Satellite name: " << endl;
                getline(cin, satelliteName);

                CUSatelliteNet.deleteCUSatellite(satelliteName);

                CUSatelliteNet.printNetwork();

                break;
            }

            case 5: {
                // detect loop
                string satellite;
                cout << "Enter the Satellite name to loop back to: " <<endl;
                getline(cin, satellite);

                CUSatellite* lastnode = CUSatelliteNet.createLoop(satellite);

                bool hasLoop = CUSatelliteNet.detectLoop();

                if (hasLoop) {
                    cout << "Network contains a loop." << endl;
                    cout << "Breaking the loop."<< endl;
                    lastnode->next = NULL;
                } else {
                    cout << "Network does not contain a loop." << endl;
                }

                break;
            }

            case 6: {
                //re-adjust network
                string st, en;
                cout << "Enter the start index: " << endl;
                getline(cin, st);
                cout << "Enter the end index: " << endl;
                getline(cin, en);

                CUSatelliteNet.readjustNetwork(stoi(st), stoi(en));

                CUSatelliteNet.printNetwork();

                break;
            }

            case 7: {
                // delete entire network
                cout << "Network before deletion" << endl;
                CUSatelliteNet.printNetwork();

                CUSatelliteNet.deleteEntireNetwork();

                cout << "Network after deletion" <<endl;
                CUSatelliteNet.printNetwork();

                break;
            }
            case 8: {
                // quit
                quit = true;
                cout << "Quitting... cleaning up path: " << endl;
                break;
            }

            default:     // invalid input
                cout << "Invalid Input!" << endl;
                break;
        }
    }
}

/*
 * Purpose; displays a menu with options
 */
void displayMenu()
{
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build Network " << endl;
    cout << " 2. Print Network Path " << endl;
    cout << " 3. Add Satellite " << endl;
    cout << " 4. Delete Satellite " << endl;
    cout << " 5. Create and Detect loop in network" << endl;
    cout << " 6. Re-adjust Network" << endl;
    cout << " 7. Clear Network " << endl;
    cout << " 8. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
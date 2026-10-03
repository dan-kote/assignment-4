# CSCI 2270 – Data Structures - Assignment 4: Linked Lists

## Objectives

1. Delete, re-adjust, and detect loop in a linked list
2. Practice implementing classes in C++

**NOTE: This assignment is an extension of Assignment 3.**

## Instructions

Write code to simulate a linear communication network. To receive credit for your code, you will need to pass the necessary test cases. Use the following steps to test your code as you work on the assignment:

 1. Open up your Linux terminal, navigate to the build directory of this assignment (e.g. `cd build`).
 2. Run the `cmake ..` command.
 3. Run the `make` command.
 4. If there are no compilation errors, two executables will be generated within the build directory: `run_app_1` and `run_tests`.
 5. If you would like to run your program including your app implementation in the `main` function, execute `run_app_1` from the terminal by typing `./run_app_1`.
 6. To run the grading tests, execute `run_tests` from the terminal by typing `./run_tests`. 

 **NOTE: Make sure to run your program `./run_app_1` WITHOUT command line arguments.**

## Continuation of Previous Assignment 

This assignment builds on the previous one. You will need to reuse the `CUSatelliteNetwork` class implementation you already completed, and then add to it as described in this readme. 

**NOTE: When experimenting with your program, make sure to run your program `./run_app_1` WITHOUT command line arguments.**

The linked list itself will be implemented using the following node struct: 

```
struct CUSatellite{
    string name;         // name of the satellite
    string message;      // message this satellite has received
    int numberMessages;  // no. of messages passed through this satellite
    CUSatellite *next;   // pointer to the next satellite
    int distanceFromEarth; // distance of satellite from earth in light years
};
```

## **Class Specifications**

The **CUSatelliteNetwork** class definition is provided in the file `CUSatelliteNetwork.hpp`. Do 
not modify this file! Fill in the file `CUSatelliteNetwork.cpp` according to the following specifications. **You should be able to use your sollutions from Assignment-3 for the first part of this assignment.** 


`CUSatellite* head;` 
+ Points to the first node in the linked list 

`CUSatelliteNetwork()` 
+ Class constructor; sets the head pointer to NULL 

`bool isEmpty()`
+ Return *true* if the head is NULL, *false* otherwise 

`void addSatelliteInfo(string previous, string satelliteName, int distance)` 
+ Insert a new Satellite with name `SatelliteName` in the linked list after the Satellite pointed 
to by `​previous​`. 
+ If `​previous​` is NULL, then add the new Satellite to the beginning of the list. 
+ Print the name of the Satellite you added according to the following format: 

```
// If you are adding at the beginning use this: 
cout << "adding: " << satelliteName << " (HEAD)" << endl; 
 
// Otherwise use this: 
cout << "adding: " << satelliteName << " (prev: " << previous->name << ")" << endl;

// If the previous node cannot be found, display this message:
cout << "Cannot add new node; previous node not found\n" << endl;
```

`void loadDefaultSetup()`
+ Add the following six satellites to the network using `addSatelliteInfo`. Do so by adding each node at the head of the Linked List (i.e. start with "MAVEN", then add "JUNO" as the new head, and so on).

"TESS" -> "KEPLER" -> "GALILEO" -> "PIONEER" -> "JUNO" -> "MAVEN"

+ Add the following distances corresponding to the satellites added above, in order, to the network with `addSatelliteInfo`: 

"2", "10", "6", "5", "4", "9"


`CUSatellite* searchForSatellite(string satelliteName)`
+ Return a pointer to the node with name `satelliteName`. If `satelliteName` cannot be found, return `nullptr` 

`void transmitInfo(string receiver)`
+ Traverse the linked list from the head to the node with name receiver. For each node in this path (including the head), set the node’s message to `"distance of "+ satelliteName + " from earth is " + distanceFromEarth` and increment the node’s `numberMessages` field. If the list is empty, `print "Empty list"` and exit the function. If the node is not present, `print “Satellite not found”`. 

+ As you traverse the list, at each node report the message received and the number of messages received using the following cout: (See the end of this document for example output) 

```
cout << node->name << " [# messages received: " << node->numberMessages << "] received: " << node->message << endl;
```


`void printNetwork();`
+ Print the names of each node in the linked list. Below is an example of correct output using the default setup. (Note that you will `cout << “NULL”` at the end of the path) 

```
== CURRENT PATH == 
TESS(2) -> KEPLER(10) -> GALILEO(6) -> PIONEER(5) -> JUNO(4) -> MAVEN(9) -> NULL
=== 
```

+ If the network is empty then `print "nothing in path"`

### TODO Implementations in that order (New for Assignment-4)

**void deleteCUSatellite(string SatelliteName);** 
+ Traverse the list to find the node with name `SatelliteName`, then delete it. If there is no node with name `SatelliteName`, print ​"Satellite does not exist."

**void deleteEntireNetwork();**
+ If the list is empty, do nothing and return. Otherwise, delete every node in the linked list and set ​head ​to NULL.


**bool detectLoop();**
+ Traverse through the linked list (pointed to by *head*) to detect the presence of a loop. A loop is present in the list when the tail node points to some intermediate node (including itself) in the linked list, instead of pointing to null value. For example, the following list with ​`A`​ at the head has a loop: ​`A -> B -> C -> D -> E -> B`. Notice that all the nodes are unique, except for node ​`B` which is repeated twice. This means that the last unique node `E` is connected back to the node `B` that appears before it in the linked list. 
+ Return `​true` ​if the list contains a loop, else return `​false​`. 
+ Refer to the following links for the algorithm of loop detection: 
[Detect a loop in a linked list](https://www.youtube.com/watch?v=apIw0Opq5nk)
[Data Structures: Cycles in a Linked List](https://www.youtube.com/watch?v=MFOAbpfrJ8g)

**CUSatellite\* createLoop(string SatelliteName);**

+ As a way to test the `detectLoop()` function, develop a `createLoop()` function that adds a loop to the linked list pointed to by ​head​. 
+ You’ll achieve this by creating a link from the last node in the linked list to an intermediate node. The function takes as argument the Satellite name of that intermediate node to loop back into. 
+ The function should return the last node of the linked list before creation of the loop. This will be needed by the driver function to break the loop. 
+ For example, consider the linked list: ​`A -> B -> C -> D -> E -> NULL`. 
Suppose the function is called as -- **createLoop(“C”);**

After execution of the function the linked list should be `A -> B -> C -> D -> E -> C` ​and it will return a pointer to the node `​E​`. ​*NOTE:​ node ​E​ was the last node before creation of the loop.*
+ If the Satellite is not present in the linked list, the function should return without creating a loop. A pointer to the last node should still be returned.


**void readjustNetwork(int start, int end);**
+ Manipulate ​next ​pointers to re-adjust the linked list. Here, `start` is index of a node from starting. Similarly `​end` ​is index of a node at the end of the chunk. The function will send the chunk of the linked list from `start` index to `end` index to the end of the linked list. Consider the node at head as index 0.

For example, if you have linked list like this: ​`A -> B -> C -> D -> E-> NULL`, and `start=1` and `end=3​`, then the linked list after `readjustNetwork` should be `A -> E -> B -> C -> D->  NULL​`.

If you have linked list like this: ​`A -> B -> C -> D -> NULL`, and ​`start=0` and `end=2`​, then the linked list after readjustNetwork should be `D-> A -> B -> C -> NULL`​. Here, `D` is the new head.

+ If the linked list is empty, `print “​Linked List is Empty​”`.
+ If `end` is bigger than the number of nodes in the linked list or smaller than ​0​, then `print “​Invalid end index​”`.
+ `end` ​should be lesser than the index of the last element in the linked list. Otherwise `print “​Invalid end index​”`.
+ If `start` is bigger than the number of nodes in the linked list or smaller than ​0​, then `print “​Invalid start index​”`. 
+ If `start > end`, `print “Invalid indices”`. 

*NOTE: Change the order of the “node” (by manipulating  the next pointers of each node), not the “value of the node”.* 


**~CUSatelliteNetwork();**
+ Class destructor; delete the entire list and set the head pointer to NULL.

To test the entire implementation below, you will also need to plug-in your answers from
Assignment 3 in the provided starter file.

### Order of test cases

Order of test in `tests\test.cpp` is given below. All of these functions will use `loadDefaultSetup` and `printNetwork`
1. `deleteCUSatellite`
2. `deleteEntireNetwork`
3. `detectLoop`: This test case will require `createLoop`.
4. `createLoop`:This test case will require `detectLoop`.
5. `readjustNetwork`


## Main driver file 

***NOTE: Main driver file is provided in starter code. You do not have to code it. You can use that to test your functions​. We will walk through a brief introduction of the driver here.***

Your program will start by displaying a menu by calling the `​displayMenu​` function included in main.cpp. The user will select an option from the menu to decide what the program will do, after which, the menu will be displayed again. The specifics of each menu option are described below.

**Option 1: Build Network**

This option calls the `​loadDefaultSetup​` function, then calls the `printNetwork` ​function. You should get the following output: 

```
adding: MAVEN (HEAD)
adding: JUNO (HEAD)
adding: PIONEER (HEAD)
adding: GALILEO (HEAD)
adding: KEPLER (HEAD)
adding: TESS (HEAD)
== CURRENT PATH ==
TESS(2) -> KEPLER(10) -> GALILEO(6) -> PIONEER(5) -> JUNO(4) -> MAVEN(9) -> NULL
===
```

**Option 2: Print Network Path**

Calls the `printNetwork` function. Output should be in the format below: 

```
// Output for the default setup 
== CURRENT PATH ==
TESS(2) -> KEPLER(10) -> GALILEO(6) -> PIONEER(5) -> JUNO(4) -> MAVEN(9) -> NULL
===
 
// Output when the linked list is empty 
== CURRENT PATH == 
nothing in path 
===
```

**Option 3: Add Satellite**


Prompt the user for three inputs: the name of a new satellite to add to the network, `newSatellite`, distance of satellite from the earth, `distanceFromEarth`, and the name of a satellite already in the network, `previous`, which will precede the new satellite. Use the member functions `searchForSatellite` and `addSatelliteInfo` to insert `newSatellite` info into the linked list right after previous. 

* If the user wants to add the new satellite to the head of the network then they should enter “First” instead of a previous satellite name. 
* If the user enters an invalid previous satellite (not present in the linked list), then you need to prompt the user with the following error message and collect input again until they enter a valid previous satellite name or “First”: 

```
cout << "INVALID(previous satellite name)...Please enter a VALID satellite name!" << endl;
```

* Once a valid previous satellite name is passed and the new satellite is added, call the function `printNetwork` to demonstrate the new linked-list.
* All letters of the recipient to be added should be Uppercase (sentence case) e.g. If you want to add “sputnik, it should be stored as “SPUTNIK” in linked list.

For example, the following should be the output if the linked list contains the default setup from option (1) and the user wants to add SPUTNIK after GALILEO: 

```
Enter a new satellite name: SPUTNIK
Enter distance of satellite from earth: 13
Enter the previous satellite name (or First): GALILEO

adding: SPUTNIK (prev: GALILEO)

== CURRENT PATH ==
TESS(2) -> KEPLER(10) -> GALILEO(6) -> SPUTNIK(13) -> PIONEER(5) -> JUNO(4) -> MAVEN(9) -> NULL===
```

**Option 4: Delete Satellite**

Prompt the user for a Satellite name, then pass that name to the `deleteCUSatellite` ​function and call `printNetwork` to demonstrate the new linked list. 

For example, the following should be the output if the linked list contains the default setup from option (1) and the user wants to delete `KEPLER`:

```
Enter a Satellite name: KEPLER

== CURRENT PATH ==
TESS(2) -> GALILEO(6) -> PIONEER(5) -> JUNO(4) -> MAVEN(9) -> NULL
===
```

**Option 5: Create and Detect loop in network**

Call the `​createLoop​` and `​detectLoop` ​functions. 

User will be prompted to enter the name of the Satellite to loop back. `​createLoop` function will be called to create the loop accordingly. After that `​detectLoop` will be called. Depending on the status of loop creation `​detectLoop` will return either `true` (if the loop is created) or `false` (if the loop could not be created). After calling `​createLoop` function, If there is a loop it will be broken by the driver (*refer to the starter code for more detail*). So, in this operation, a loop is created in the linked list (if appropriate input is given) and it is removed immediately. 

```
Enter the Satellite name to loop back to: 
PIONEER
Network contains a loop. 
Breaking the loop.
```

**Option 6: Re-adjust Network**

Call the `readjustNetwork` ​function, then the `printNetwork` ​function. User should be prompted to 
input the `start` index and `end` index. 

For example, the following should be the output if the linked list contains the default setup from 
option (1): 

```
Enter the start index: 
1
Enter the end index: 
2
== CURRENT PATH == 
TESS(2) -> PIONEER(5) -> JUNO(4) -> MAVEN(9) ->  -> KEPLER(10) -> GALILEO(6) -> NULL
===
```

**Option 7: Clear Network**

Call the `deleteEntireNetwork` ​function. For example, deleting the default network should print: 

```
Network before deletion
== CURRENT PATH ==
TESS(2) -> KEPLER(10) -> GALILEO(6) -> PIONEER(5) -> JUNO(4) -> MAVEN(9) -> NULL
===

Network after deletion 
== CURRENT PATH == 
nothing in path
===
```

**Option 8: Quit**

Print the following message: 

```
cout << ​"Quitting... cleaning up path: "​ << endl;
```

Then proceed to exit the program. Prior to the exit, the destructor will be invoked automatically, and delete the network, same as `deleteEntireNetwork`.

```
Quitting... cleaning up path: 
== CURRENT PATH ==
TESS(2) -> KEPLER(10) -> GALILEO(6) -> PIONEER(5) -> JUNO(4) -> MAVEN(9) -> NULL
===
```

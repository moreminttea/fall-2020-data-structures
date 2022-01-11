// Mindy Mohr
// 917425752
// teamdata.cpp (unfinished- wrong output)

#include <iostream> //for reading file
#include <fstream> //for reading file
#include <vector> //for vector ops
#include <string> //for string ops
#include <iomanip> //for setw()
#include <set> //for set ops

#include "json.hpp"
#include "teamdata.h"
#include "priorityqueue.h"

/* goal:
 1. insert fairness |win% - 50| into min heap in priorityqueue.cpp
 2. return min (with players)
 3. pop min heap
 4. remove keys with players from removed min
 5. repeat 2-5 until left with 1 pair of players
 6. print teams
 */

TeamData::TeamData(std::string filename) //takes file as string and returns pairs of teams
{
    nlohmann::json jsonObject; //original json object
    std::ifstream file; //read in file from function argument
    file.open(filename); //open file from function argument
    file >> jsonObject; //write file to json
    nlohmann::json newjsonObject; //new json object
    
    int numPlayers_ = jsonObject["metadata"]["numPlayers"]; //access numPlayers
    int combinations = (numPlayers_ * (numPlayers_ + 1)) / 2; //max size of heap is max size of player combinations
    PriorityQueue heap(combinations); //create priority queue heap of max size
    
    for (auto pair : jsonObject["teamStats"]) //for loop to access elements of "teamStats"
    {
        //std::set<int> final_teams;
        int player1 = pair["playerOne"]; //access "playerOne"
        int player2 = pair["playerTwo"]; //access "playerTwo"
        double win_percent = pair["winPercentage"]; //access "winPercentage"
        double fairness = abs(win_percent - 50); //calculate fairness formula (deviation from 50%)
        //final_teams.insert(fairness);
        //final_teams.insert(player1);
        //final_teams.insert(player2);
        
        for (player1 = 0; player1 < numPlayers_ - 1; player1++) //player1
        {
            for (player2 = player1 + 1; player2 < numPlayers_; player2++) //player2
            {
                heap.insert(fairness); //call insert() function in priorityqueue.cpp using fairness calculation
                heap.min(); //call min() function in priorityqueue.cpp to get min
                heap.removeMin(); //call removeMin() function in priorityqueue.cpp to remove min
                //newjsonObject["teams"].push_back(player1); //write player1 to json
                //newjsonObject["teams"].push_back(player2); //write player2 to json
            }
        }
    }
    std::cout << newjsonObject["teams"] << std::endl; //print pairs of teams
}; //end TeamData

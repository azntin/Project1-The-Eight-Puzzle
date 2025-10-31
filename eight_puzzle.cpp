#include <vector>
#include <iostream>
#include "eight_puzzle.h"

using namespace std;

//global funcs for searching algorithms
void UniformCostSearch(Problem p) {
    cout << "Not yet implemented. 1" << endl;
}

void AStarSearchMT(Problem p) {
    cout << "Not yet implemented. 2" << endl;
}

void AStarSearchED(Problem p) {
    cout << "Not yet implemented. 3" << endl;
}

void printState(const vector<vector<int>>& s){
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            if(s[i][j] == 0){cout << "X";}
            else{cout << s[i][j];}
        }
        cout << endl;
    }
}

    vector<int> findBlank(vector<vector<int>> s){
        vector<int> coordinates;
        for(int i = 0; i < 3; ++i){
            for(int j = 0; j < 3; ++j){
                if(s[i][j] == 0){
                    coordinates.push_back(i);
                    coordinates.push_back(j);
                }
            }
        }
        return coordinates;
    }
    void Problem::up(){
        vector<int> position = findBlank(initial_state);
        int y = position[0];
        int x = position[1];

        if(y == 0){
            return;
        }

        //Swapping the two values:
        int backup = initial_state[y][x];
        initial_state[y][x] = initial_state[y-1][x];
        initial_state[y-1][x] = backup;
    }

    void Problem::down(){}
    void Problem::left(){}
    void Problem::right(){}

bool Problem::isSolvable(const vector<vector<int>> s){
        vector<int> vec;
        int currPos;
        int bigBeforeSmall = 0;

        for(int i = 0; i < 3; ++i){
            for(int j = 0; j < 3; ++j){
                currPos = s[i][j];
                if(currPos != 0){
                    vec.push_back(currPos);
                }
            }
        }

        for(int i = 0; i < vec.size(); ++i){
            for(int j = i+1; j < vec.size(); ++j){
                if(vec.at(i) > vec.at(j)){
                    bigBeforeSmall ++;
                }
            }
        }
        return (bigBeforeSmall % 2 == 0);
    };

/*
function Graph-Search(problem) returns a solution, or failure
    initialize frontier using the initial state of problem
    initialize the explored set to be empty
    loop do
        if the frontier is empty then return failure

        choose a leaf node and remove it from the frontier

        if the node contains a goal statae then return the corresponding solution

        add the node to the explored set

        expand the chosen node, adding the resulting nodes to the frontier
            only if not in the frontier or explored set
*/
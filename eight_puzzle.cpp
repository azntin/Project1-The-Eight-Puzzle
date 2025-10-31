#include "eight_puzzle.h"
#include <vector>
#include <iostream>

using namespace std;

void UniformCostSearch(Problem p) {
    cout << "Not yet implemented" << endl;
}

void AStarSearchMT(Problem p) {
    cout << "Not yet implemented" << endl;
}

void AStarSearchED(Problem p) {
    cout << "Not yet implemented" << endl;
}

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
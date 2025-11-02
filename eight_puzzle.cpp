#include <vector>
#include <iostream>
#include <cmath>
#include <queue>
#include "eight_puzzle.h"

using namespace std;

//global funcs for searching algorithms

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
Node UniformCostSearch(Problem p) {
    //frontier using initial state
    priority_queue<Node> frontier;
    vector<vector<vector<int>>> explored; //issue with this; prolly 3D vector since each node has 2D vector so we need one higher dimension to store each node

    //get initial state and push to frontier 
    Node startNode(p);
    frontier.push(startNode); 

    while (!frontier.empty()) {
        //choose a leaf node and remove it from the frontier
        Node curr = frontier.top();
        frontier.pop();

        //for text print out in main at end for total expanded nodes and max nodes in queue 
        p.totalExpandedNodes++;
        if (frontier.size() > p.maxNumberOfNodesInQueue) {
            p.maxNumberOfNodesInQueue = frontier.size();
        }

        //if the node contains a goal statae then return the corresponding solution
        if (curr.problem.initial_state == p.goal_state) {
            return curr;
        }
        //add the node to the explored set
        explored.push_back(curr.problem.initial_state); 

        //expand the chosen node, adding the resulting nodes to the frontier
        //only if not in the frontier or explored set
        //here call up down left right functions

        Problem child = curr.problem; //maybe issue here too? outside loop or inside loop; think about it later
        //either fix this or fix up down left right func because they modify child everytime so it does up down left right on same child
        //^^^^ IMPORTANT&&&&&
        for (int i = 0; i < 4; ++i) { //go through each up down left right func
            if (i == 0) {
                child.up(); //i believe up down left right func modifies it in function itself and doesnt return anything
            }
            else if (i == 1) {
                child.down();
            }
            else if (i == 2) {
                child.left();
            }
            else if (i == 3) {
                child.right();
            }
        }

        //only if not in the frontier or explored set
        //do for each loop 
        //fix this since it doesnt work properly
        bool inExplored = false;
        for (vector<vector<int>> x : explored) { //go through each element in explored
            if (x == child.initial_state) { //means we do not add to frontier since we already popped and explored it from vector explored
                inExplored = true;
                break;
            }
        }

        if (!inExplored) { //only runs if a child or leaf node/state is not in explored set (maybe add for frontier too?)
            //i think frontier will always add expanded node unless it is goal state to explored so i dont think so?
            Node newChild(child); 
            newChild.gCost = curr.gCost + 1; 
            newChild.depth = curr.depth + 1;
            frontier.push(newChild);
        }
    }
}

Node AStarSearchMT(Problem p) {
    cout << "Not yet implemented. 2" << endl;
}

Node AStarSearchED(Problem p) {
    cout << "Not yet implemented. 3" << endl;
}

double Problem::euclideanDist(Problem p) {
    double total = 0.0;
    int goalVal, probVal;
    vector<vector<int>> goal = this->goal_state;

    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            goalVal = goal[r][c];
            if (goalVal == 0) { continue; }
            bool found = false;

            for (int r1 = 0; r1 < 3 && !found; ++r1) {
                for (int c1 = 0; c1 < 3; ++c1) {
                    probVal = p.initial_state[r1][c1];
                    if(probVal == 0) { continue; }

                    if (goalVal == probVal) {
                        total += sqrt(pow((r1 - r),2) + pow((c1 - c),2));
                        found = true;
                        break;
                    }
                }
            }
        }
    }
    return total;
}

int Problem::misplacedTileDist(Problem p) { //maybe change this? because of how the up down left right function and instead send in curr state rather than entire problem p?
    int total = 0;
    vector<vector<int>> goal = this->goal_state;

    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (p.initial_state[r][c] == 0) { continue; }
            if (goal[r][c] != p.initial_state[r][c]) {
                ++total;
            }
        }
    }
    return total;
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
    initial_state[y][x] = initial_state[y+1][x];
    initial_state[y+1][x] = backup;
}

void Problem::down(){
    vector<int> position = findBlank(initial_state);
    int y = position[0];
    int x = position[1];

    if(y == 2){
        return;
    }

    //Swapping the two values:
    int backup = initial_state[y][x];
    initial_state[y][x] = initial_state[y+1][x];
    initial_state[y+1][x] = backup;
}

void Problem::left(){
    vector<int> position = findBlank(initial_state);
    int y = position[0];
    int x = position[1];

    if(x == 0){
        return;
    }

    //Swapping the two values:
    int backup = initial_state[y][x];
    initial_state[y][x] = initial_state[y][x+1];
    initial_state[y][x+1] = backup;
}

void Problem::right(){
            vector<int> position = findBlank(initial_state);
    int y = position[0];
    int x = position[1];

    if(x == 2){
        return;
    }

    //Swapping the two values:
    int backup = initial_state[y][x];
    initial_state[y][x] = initial_state[y][x+1];
    initial_state[y][x+1] = backup;
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
                if(vec[i] > vec[j]){
                    bigBeforeSmall ++;
                }
            }
        }
        return (bigBeforeSmall % 2 == 0);
    };


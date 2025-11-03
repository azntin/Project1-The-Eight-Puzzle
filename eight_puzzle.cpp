#include <vector>
#include <iostream>
#include <cmath>
#include <queue>
#include <unordered_set>
#include <string>
#include "eight_puzzle.h"

using namespace std;

Node* UniformCostSearch(Problem& p) {
    Node* newChild;
    //Initialize frontier 
    priority_queue<Node*, vector<Node*>, CompareByCost> frontier; //Stores pointer to node in vector; Uses custom Struct to order priority queue; smallest g(n) on top
    unordered_set<string> explored; 
    unordered_set<string> frontierSet; //Used to track states in frontier and also to check for dupes later in code

    //Add starting node to frontier
    Node* startNode = new Node(p);
    frontier.push(startNode);
    frontierSet.insert(stateToString(startNode->problem.initial_state)); //Inserts initial state into frontier set to check for dupes later

    //Checks if given puzzle is solvable
    if (!p.isSolvable(p.initial_state)) {
        cout << "This puzzle is not solvable." << endl;
        return startNode; 
    }

    //Empty = failure so loop until empty
    while (!frontier.empty()) {
        //Choose a leaf node and remove it from the frontier
        Node* curr = frontier.top();
        frontier.pop();
        frontierSet.erase(stateToString(curr->problem.initial_state)); //Remove from frontier set as well for consistency and correctness
        
        //Goal state found
        if (curr->problem.initial_state == p.goal_state) {
            vector<Node*> path; //Use to store path 
            Node* trace = curr; //Trace starting from goal node all the way back to start node via parent pointer
            while (true) {
                path.push_back(trace); //Starting node will be at end of vector; goal node at start of vector
                if (trace->parent == nullptr) { 
                    break;
                }
                trace = trace->parent;
            }
            cout << "Printing solution here: " << endl;
            for (int i = path.size() - 1; i >= 0; --i) { //From above, start at end of vector to print correctly from beginning to end
                printState(path[i]->problem.initial_state);
                cout << "-------------" << endl;
            }
            return curr;
        }

        //Add the node to the explored set
        explored.insert(stateToString(curr->problem.initial_state));

        //Expand the chosen node, adding the resulting nodes to the frontier
        //Only if not in the frontier or explored set
        for (int i = 0; i < 4; ++i) { //Go through each up down left right func
            Problem child = curr->problem;
            if (i == 0) {
                child.up(); 
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

            if (child.initial_state == curr->problem.initial_state) { //No change aka operator did not do anything so go to next iteration
                continue;
            }

            if (frontierSet.find(stateToString(child.initial_state)) != frontierSet.end()) { //Check if dupe in frontier
                continue;
            }

            if (explored.find(stateToString(child.initial_state)) != explored.end()) { //Check if dupe in explored
                continue;
            }
            p.totalExpandedNodes++; //Valid expanded node so increment count

            Node* newChild = new Node(child); //Create new child node now, set its parameters, and add to frontier
            newChild->parent = curr;
            newChild->gCost = curr->gCost + 1;
            newChild->depth = curr->depth + 1;
            frontier.push(newChild);
            frontierSet.insert(stateToString(child.initial_state));

            if (frontier.size() > p.maxNumberOfNodesInQueue) { //Update max nodes in queue if current size exceeds previous max
                p.maxNumberOfNodesInQueue = frontier.size();
            }
        }
    }
    return nullptr;
}

Node* AStarSearchMT(Problem& p) {
    Node* newChild;
    //Initialize frontier
    priority_queue<Node*, vector<Node*>, CompareByFCost> frontier; //Stores pointer to node in vector; Uses custom Struct to order priority queue; smallest f(n) on top

    unordered_set<string> explored;
    unordered_set<string> frontierSet; //Used to track states in frontier and also to check for dupes later in code

    //Add starting node to frontier
    Node* startNode = new Node(p);
    startNode->hCost = p.misplacedTileDist(p.initial_state); //Do not think we need this; here for consistency
    startNode->fCost = startNode->gCost + startNode->hCost; //Find f(n) cost with heuristic and g(n) 
    frontier.push(startNode);
    frontierSet.insert(stateToString(startNode->problem.initial_state)); //Inserts initial state into frontier set to check for dupes later

    //Checks if given puzzle is solvable 
    if (!p.isSolvable(p.initial_state)) {
        cout << "This puzzle is not solvable." << endl;
        return startNode; 
    }

    //Empty = failure so loop until empty
    while (!frontier.empty()) {
        //Choose a leaf node and remove it from the frontier
        Node* curr = frontier.top();
        frontier.pop();
        frontierSet.erase(stateToString(curr->problem.initial_state)); //Remove from frontier set as well for consistency and correctness

        //Goal state found
        if (curr->problem.initial_state == p.goal_state) {
            vector<Node*> path; //Use to store path 
            Node* trace = curr; //Trace starting from goal node all the way back to start node via parent pointer
            while (true) {
                path.push_back(trace); //Starting node will be at end of vector; goal node at start of vector
                if (trace->parent == nullptr) break;
                trace = trace->parent;
            }
            cout << "Printing solution here: " << endl;
            for (int i = path.size() - 1; i >= 0; --i) { //From above, start at end of vector to print correctly from beginning to end
                printState(path[i]->problem.initial_state);
                cout << "-------------" << endl;
            }
            return curr;
        }

        //Add the node to the explored set
        explored.insert(stateToString(curr->problem.initial_state));

        //Expand the chosen node, adding the resulting nodes to the frontier
        //Only if not in the frontier or explored set
        for (int i = 0; i < 4; ++i) { //Go through each up down left right func
            Problem child = curr->problem;
            if (i == 0) {
                child.up();
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

            if (child.initial_state == curr->problem.initial_state) { //No change aka operator did not do anything so go to next iteration
                continue;
            }

            if (frontierSet.find(stateToString(child.initial_state)) != frontierSet.end()) { //Check if dupe in frontier
                continue;
            }

            if (explored.find(stateToString(child.initial_state)) != explored.end()) { //Check if dupe in explored
                continue;
            }

            p.totalExpandedNodes++; //Valid expanded node so increment count

            Node* newChild = new Node(child); //Create new child node now, set its parameters, and add to frontier
            newChild->parent = curr;
            newChild->gCost = curr->gCost + 1;
            newChild->hCost = p.misplacedTileDist(child.initial_state); 
            newChild->fCost = newChild->gCost + newChild->hCost;
            newChild->depth = curr->depth + 1;
            frontier.push(newChild);
            frontierSet.insert(stateToString(child.initial_state));

            if (frontier.size() > p.maxNumberOfNodesInQueue) { //Update max nodes in queue if current size exceeds previous max
                p.maxNumberOfNodesInQueue = frontier.size();
            }
        }
    }
    return nullptr;
}

Node* AStarSearchED(Problem& p) {
    Node* newChild;
    //Initialize frontier
    priority_queue<Node*, vector<Node*>, CompareByFCost> frontier; //Stores pointer to node in vector; Uses custom Struct to order priority queue; smallest f(n) on top
    unordered_set<string> explored;
    unordered_set<string> frontierSet; //Used to track states in frontier and also to check for dupes later in code

    //Add starting node to frontier
    Node* startNode = new Node(p);
    startNode->hCost = p.euclideanDist(p.initial_state); //Do not think we need this; here for consistency
    startNode->fCost = startNode->gCost + startNode->hCost; //Find f(n) cost with heuristic and g(n)
    frontier.push(startNode);
    frontierSet.insert(stateToString(startNode->problem.initial_state)); //Inserts initial state into frontier set to check for dupes later

    //Checks if given puzzle is solvable
    if (!p.isSolvable(p.initial_state)) {
        cout << "This puzzle is not solvable." << endl;
        return startNode; 
    }

    //Empty = failure so loop until empty
    while (!frontier.empty()) {
        //Choose a leaf node and remove it from the frontier
        Node* curr = frontier.top();
        frontier.pop();
        frontierSet.erase(stateToString(curr->problem.initial_state)); //Remove from frontier set as well for consistency and correctness

        //Goal state found
        if (curr->problem.initial_state == p.goal_state) { 
            vector<Node*> path; //Use to store path
            Node* trace = curr; //Trace starting from goal node all the way back to start node via parent pointer
            while (true) {
                path.push_back(trace); //Starting node will be at end of vector; goal node at start of vector
                if (trace->parent == nullptr) break;
                trace = trace->parent;
            }
            cout << "Printing solution here: " << endl;
            for (int i = path.size() - 1; i >= 0; --i) { //From above, start at end of vector to print correctly from beginning to end
                printState(path[i]->problem.initial_state);
                cout << "-------------" << endl;
            }

            return curr;
        }

        //Add the node to the explored set
        explored.insert(stateToString(curr->problem.initial_state));

        //Expand the chosen node, adding the resulting nodes to the frontier
        //Only if not in the frontier or explored set
        for (int i = 0; i < 4; ++i) { //Go through each up down left right func
            Problem child = curr->problem;
            if (i == 0) {
                child.up();
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

            if (child.initial_state == curr->problem.initial_state) { //No change aka operator did not do anything so go to next iteration
                continue;
            }

            if (frontierSet.find(stateToString(child.initial_state)) != frontierSet.end()) { //Check if dupe in frontier
                continue;
            }

            if (explored.find(stateToString(child.initial_state)) != explored.end()) { //Check if dupe in explored
                continue;
            }
            p.totalExpandedNodes++; //Valid expanded node so increment count

            Node* newChild = new Node(child); //Create new child node now, set its parameters, and add to frontier
            newChild->parent = curr;
            newChild->gCost = curr->gCost + 1;
            newChild->hCost = p.euclideanDist(child.initial_state);
            newChild->fCost = newChild->gCost + newChild->hCost;
            newChild->depth = curr->depth + 1;
            frontier.push(newChild);
            frontierSet.insert(stateToString(child.initial_state));

            if (frontier.size() > p.maxNumberOfNodesInQueue) { //Update max nodes in queue if current size exceeds previous max
                p.maxNumberOfNodesInQueue = frontier.size();
            }
        }
    }
    return nullptr;
}

//Converts given state to string sp we can hash it in set and see if dupes exist
string stateToString(const vector<vector<int>>& state) {
    string s;
    for (auto& row : state) { //Goes through each row in 2D vector state
        for (int val : row) { //Goes through each value from each row and adds to string variable 
            s += to_string(val);
        }
    }
    return s;
}

double Problem::euclideanDist(vector<vector<int>> currState) {
    double total = 0.0;
    int goalVal, probVal;
    vector<vector<int>> goal = this->goal_state; //Obtaining a version of the goal state

    for (int r = 0; r < 3; ++r) { //Iterate through each tile of the goal state
        for (int c = 0; c < 3; ++c) {
            goalVal = goal[r][c];
            if (goalVal == 0) { continue; } //If coming across 0, that's the blank, skip it
            bool found = false;

            for (int r1 = 0; r1 < 3 && !found; ++r1) { //Iterate through each tile of the puzzle with respect to the goal
                for (int c1 = 0; c1 < 3; ++c1) {
                    probVal = currState[r1][c1];
                    if(probVal == 0) { continue; } //If coming across 0, that's the blank, skip it

                    if (goalVal == probVal) { //If the two tiles match, record their positions in the grid
                        total += sqrt(pow((r1 - r),2) + pow((c1 - c),2)); //Perform euclidean distance formula with both positions and sum together
                        found = true;
                        break;
                    }
                }
            }
        }
    }
    return total;
}

int Problem::misplacedTileDist(vector<vector<int>> currState) {
    int total = 0;
    vector<vector<int>> goal = this->goal_state; //Obtain a version of the goal state

    for (int r = 0; r < 3; ++r) { //Iterate through each tile of the grid
        for (int c = 0; c < 3; ++c) {
            if (currState[r][c] == 0) { continue; } //If coming across 0, that's the blank, skip it
            if (goal[r][c] != currState[r][c]) { //For every tile that isn't in the right space (misplaced), increment the total
                ++total;
            }
        }
    }
    return total;
}

//Just goes through and prints out the 8 puzzle grid visually like a 3 by 3 grid
void printState(const vector<vector<int>>& s){
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            if(s[i][j] == 0){cout << "b";}
            else{cout << s[i][j];}
        }
        cout << endl;
    }
}

//Returns coordinates of the blank space in puzzle (0)
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

//Gets position of blank space or 0 and swaps 0 tile with tile above it
void Problem::up(){
    vector<int> position = findBlank(initial_state);
    int y = position[0];
    int x = position[1];

    if(y == 0) { //No tile above and returns unchanged state
        return;
    }

    //Swapping the two values:
    int backup = initial_state[y][x];
    initial_state[y][x] = initial_state[y-1][x];
    initial_state[y-1][x] = backup;
}

//Gets position of blank space or 0 and swaps 0 tile with tile below it
void Problem::down(){
    vector<int> position = findBlank(initial_state);
    int y = position[0];
    int x = position[1];

    if(y == 2) { //No tile below and returns unchanged state
        return;
    }

    //Swapping the two values:
    int backup = initial_state[y][x];
    initial_state[y][x] = initial_state[y+1][x];
    initial_state[y+1][x] = backup;
}

//Gets position of blank space or 0 and swaps 0 tile with tile to the left of it
void Problem::left(){
    vector<int> position = findBlank(initial_state);
    int y = position[0];
    int x = position[1];

    if(x == 0) { //No tile to the left and returns unchanged state
        return;
    }

    //Swapping the two values:
    int backup = initial_state[y][x];
    initial_state[y][x] = initial_state[y][x-1];
    initial_state[y][x-1] = backup;
}

//Gets position of blank space or 0 and swaps 0 tile with tile to the right of it
void Problem::right(){
            vector<int> position = findBlank(initial_state);
    int y = position[0];
    int x = position[1];

    if(x == 2) { //No tile to the right and returns unchanged state
        return;
    }

    //Swapping the two values:
    int backup = initial_state[y][x];
    initial_state[y][x] = initial_state[y][x+1];
    initial_state[y][x+1] = backup;
}

//Checks if given puzzle is solvable or not
//Logic: let x = an instance where a big number comes before a small number.
//If x is even, the puzzle is solvable. Otherwise not.
bool Problem::isSolvable(const vector<vector<int>> s){
    vector<int> vec;
    int currPos;
    int bigBeforeSmall = 0;

    //Basically just goes through given initial state and appends every value except 0 to 1D vector to check later for Logic
    for(int i = 0; i < 3; ++i){ 
        for(int j = 0; j < 3; ++j){
            currPos = s[i][j];
            if(currPos != 0){
                vec.push_back(currPos);
            }
        }
    }

    //Now goes through 1D vector and counts every instance where a big number comes before a small number
    for(int i = 0; i < vec.size(); ++i){
        for(int j = i+1; j < vec.size(); ++j){
            if(vec[i] > vec[j]){
                bigBeforeSmall++;
            }
        }
    }
    return (bigBeforeSmall % 2 == 0); //If even, solvable; else, not
};
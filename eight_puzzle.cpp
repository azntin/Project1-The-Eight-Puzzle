#include <vector>
#include <iostream>
#include <cmath>
#include <queue>
#include <unordered_set>
#include <string>
#include "eight_puzzle.h"

using namespace std;

Node* UniformCostSearch(Problem& p) {
    //frontier using initial state
    Node newChild;
    priority_queue<Node*, vector<Node*>, CompareByCost> frontier;

    unordered_set<string> explored;
    unordered_set<string> frontierSet;
    //get initial state and push to frontier 
    Node* startNode = new Node(p);

    frontier.push(startNode);
    frontierSet.insert(stateToString(startNode->problem.initial_state));

    if (!p.isSolvable(p.initial_state)) {
        cout << "This puzzle is not solvable." << endl;
        return startNode; 
    }

    while (!frontier.empty()) {
        //choose a leaf node and remove it from the frontier
        Node* curr = frontier.top();
        frontier.pop();
        frontierSet.erase(stateToString(curr->problem.initial_state));

        //for text print out in main at end for total expanded nodes and max nodes in queue 
        
        if (curr->problem.initial_state == p.goal_state) {
            vector<Node*> path; //Use to store path 
            Node* trace = curr;
            while (true) {
                path.push_back(trace);
                if (trace->parent == nullptr) break;
                trace = trace->parent;
            }
            cout << "Printing solution here: " << endl;
            for (int i = path.size() - 1; i >= 0; --i) {
                printState(path[i]->problem.initial_state);
                cout << "-------------" << endl;
            }
            return curr;
        }

        //if the node contains a goal statae then return the corresponding solution
        //add the node to the explored set
        //explored.push_back(curr.problem.initial_state); 
        explored.insert(stateToString(curr->problem.initial_state));

        //expand the chosen node, adding the resulting nodes to the frontier
        //only if not in the frontier or explored set
        //here call up down left right functions

        //Problem child = curr.problem; //maybe issue here too? outside loop or inside loop; think about it later
        //either fix this or fix up down left right func because they modify child everytime so it does up down left right on same child
        //^^^^ IMPORTANT&&&&&
        for (int i = 0; i < 4; ++i) { //go through each up down left right func
            Problem child = curr->problem;
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

            if (child.initial_state == curr->problem.initial_state) {
                continue;
            }

            string childKey = stateToString(child.initial_state);

            if (frontierSet.find(childKey) != frontierSet.end()) {
                continue;
            }

            if (explored.find(childKey) != explored.end()) {
                continue;
            }

            p.totalExpandedNodes++;

            Node* newChild = new Node(child);
            newChild->parent = curr;
            newChild->gCost = curr->gCost + 1;
            newChild->depth = curr->depth + 1;
            frontier.push(newChild);
            frontierSet.insert(childKey);

            if (frontier.size() > p.maxNumberOfNodesInQueue) {
                p.maxNumberOfNodesInQueue = frontier.size();
            }

                    //only if not in the frontier or explored set
        //do for each loop 
        //fix this since it doesnt work properly
        // bool inExplored = false;
        // for (vector<vector<int>> x : explored) { //go through each element in explored
        //     if (x == child.initial_state) { //means we do not add to frontier since we already popped and explored it from vector explored
        //         inExplored = true;
        //         break;
        //     }
        // }
        //     if (!inExplored) { //only runs if a child or leaf node/state is not in explored set (maybe add for frontier too?)
        //     //i think frontier will always add expanded node unless it is goal state to explored so i dont think so?
        //     Node newChild(child); 
        //     newChild.gCost = curr.gCost + 1; 
        //     newChild.depth = curr.depth + 1;
        //     frontier.push(newChild);
        // }
        }
    }
    return nullptr;
}

Node* AStarSearchMT(Problem& p) {
    //frontier using initial state
    Node* newChild;
    priority_queue<Node*, vector<Node*>, CompareByFCost> frontier;

    unordered_set<string> explored;
    unordered_set<string> frontierSet;
    //unordered_set<string> explored;
    //get initial state and push to frontier 
    Node* startNode = new Node(p);
    startNode->gCost = 0;
    startNode->hCost = p.misplacedTileDist(p.initial_state);
    startNode->fCost = startNode->gCost + startNode->hCost;

    frontier.push(startNode);
    frontierSet.insert(stateToString(startNode->problem.initial_state));

    if (!p.isSolvable(p.initial_state)) {
        cout << "This puzzle is not solvable." << endl;
        return startNode; //returning startNode since we have to return something; think about it later
    }

    while (!frontier.empty()) {
        //choose a leaf node and remove it from the frontier
        Node* curr = frontier.top();
        frontier.pop();
        frontierSet.erase(stateToString(curr->problem.initial_state));

        //for text print out in main at end for total expanded nodes and max nodes in queue    

        if (curr->problem.initial_state == p.goal_state) {
            vector<Node*> path; //Use to store path 
            Node* trace = curr;
            while (true) {
                path.push_back(trace);
                if (trace->parent == nullptr) break;
                trace = trace->parent;
            }
            cout << "Printing solution here: " << endl;
            for (int i = path.size() - 1; i >= 0; --i) {
                printState(path[i]->problem.initial_state);
                cout << "-------------" << endl;
            }
            return curr;
        }

        //if the node contains a goal statae then return the corresponding solution
        //add the node to the explored set
        explored.insert(stateToString(curr->problem.initial_state));

        for (int i = 0; i < 4; ++i) { //go through each up down left right func
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

            if (child.initial_state == curr->problem.initial_state) {
                continue;
            }

            string childKey = stateToString(child.initial_state);

            if (frontierSet.find(childKey) != frontierSet.end()) {
                continue;
            }

            if (explored.find(childKey) != explored.end()) {
                continue;
            }

            p.totalExpandedNodes++;

            Node* newChild = new Node(child);
            newChild->parent = curr;
            newChild->gCost = curr->gCost + 1;
            newChild->hCost = p.misplacedTileDist(child.initial_state);
            newChild->fCost = newChild->gCost + newChild->hCost;
            newChild->depth = curr->depth + 1;
            frontier.push(newChild);
            frontierSet.insert(childKey);

            if (frontier.size() > p.maxNumberOfNodesInQueue) {
                p.maxNumberOfNodesInQueue = frontier.size();
            }
        }
    }
    return nullptr;
}

Node* AStarSearchED(Problem& p) {
    //frontier using initial state
    Node* newChild;
    priority_queue<Node*, vector<Node*>, CompareByFCost> frontier;

    unordered_set<string> explored;
    unordered_set<string> frontierSet;
    //unordered_set<string> explored;
    //get initial state and push to frontier 
    Node* startNode = new Node(p);
    startNode->gCost = 0;
    startNode->hCost = p.euclideanDist(p.initial_state);
    startNode->fCost = startNode->gCost + startNode->hCost;

    frontier.push(startNode);
    frontierSet.insert(stateToString(startNode->problem.initial_state));

    if (!p.isSolvable(p.initial_state)) {
        cout << "This puzzle is not solvable." << endl;
        return startNode; //returning startNode since we have to return something; think about it later
    }

    while (!frontier.empty()) {
        //choose a leaf node and remove it from the frontier
        Node* curr = frontier.top();
        frontier.pop();
        frontierSet.erase(stateToString(curr->problem.initial_state));

        //for text print out in main at end for total expanded nodes and max nodes in queue    

        if (curr->problem.initial_state == p.goal_state) { //Current state/node matches goal state, thus return that state/node
            vector<Node*> path; //Use to store path 
            Node* trace = curr;
            while (true) {
                path.push_back(trace);
                if (trace->parent == nullptr) break;
                trace = trace->parent;
            }
            cout << "Printing solution here: " << endl;
            for (int i = path.size() - 1; i >= 0; --i) {
                printState(path[i]->problem.initial_state);
                cout << "-------------" << endl;
            }

            return curr;
        }

        //if the node contains a goal statae then return the corresponding solution
        //add the node to the explored set
        explored.insert(stateToString(curr->problem.initial_state));

        for (int i = 0; i < 4; ++i) { //go through each up down left right func
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

            if (child.initial_state == curr->problem.initial_state) {
                continue;
            }

            string childKey = stateToString(child.initial_state);

            if (frontierSet.find(childKey) != frontierSet.end()) {
                continue;
            }

            if (explored.find(childKey) != explored.end()) {
                continue;
            }

            p.totalExpandedNodes++;

            Node* newChild = new Node(child);
            newChild->parent = curr;
            newChild->gCost = curr->gCost + 1;
            newChild->hCost = p.euclideanDist(child.initial_state);
            newChild->fCost = newChild->gCost + newChild->hCost;
            newChild->depth = curr->depth + 1;
            frontier.push(newChild);
            frontierSet.insert(childKey);

            if (frontier.size() > p.maxNumberOfNodesInQueue) {
                p.maxNumberOfNodesInQueue = frontier.size();
            }
        }
    }
    return nullptr;
}

string stateToString(const vector<vector<int>>& state) {
    string s;
    for (auto& row : state)
        for (int val : row)
            s += to_string(val);
    return s;
}

double Problem::euclideanDist(vector<vector<int>> currState) {
    double total = 0.0;
    int goalVal, probVal;
    vector<vector<int>> goal = this->goal_state; // obtaining a version of the goal state

    for (int r = 0; r < 3; ++r) { // iterate through each tile of the goal state
        for (int c = 0; c < 3; ++c) {
            goalVal = goal[r][c];
            if (goalVal == 0) { continue; } // if coming across 0, that's the blank, skip it
            bool found = false;

            for (int r1 = 0; r1 < 3 && !found; ++r1) { // iterate through each tile of the puzzle with respect to the goal
                for (int c1 = 0; c1 < 3; ++c1) {
                    probVal = currState[r1][c1];
                    if(probVal == 0) { continue; } // if coming across 0, that's the blank, skip it

                    if (goalVal == probVal) { // if the two tiles match, record their positions in the grid
                        total += sqrt(pow((r1 - r),2) + pow((c1 - c),2)); //perform euclidean distance formula with both positions and sum together
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
    vector<vector<int>> goal = this->goal_state; //obtain a version of the goal state

    for (int r = 0; r < 3; ++r) { // iterate through each tile of the grid
        for (int c = 0; c < 3; ++c) {
            if (currState[r][c] == 0) { continue; } // if coming across 0, that's the blank, skip it
            if (goal[r][c] != currState[r][c]) { // for every tile that isn't in the right space (misplaced), increment the total
                ++total;
            }
        }
    }
    return total;
}

// prints out the 8 puzzle grid for visual
void printState(const vector<vector<int>>& s){
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            if(s[i][j] == 0){cout << "b";}
            else{cout << s[i][j];}
        }
        cout << endl;
    }
}

// returns coordinates of the blank space in puzzle (0)
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
    initial_state[y][x] = initial_state[y][x-1];
    initial_state[y][x-1] = backup;
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
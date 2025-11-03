#include <iostream>
#include <vector>
#include "eight_puzzle.h"

using namespace std;

int main() {
    int puzzleChoice;
    int algoChoice;
    int userPuzzleInput;
    Problem p;
    Node* goalNode;

    cout << "Welcome to 8 puzzle solver." << endl; 
    cout << "Student IDs: Brian Byun - 862346988, ..." << endl;
    cout << "Type '1' to use a default puzzle, or '2' to enter your own puzzle." << endl;
    cin >> puzzleChoice;

    if (puzzleChoice == 1) {
        p = Problem(); //Default hardcoded puzzle
    }
    if (puzzleChoice == 2) { 
        cout << "Enter your puzzle, use a zero to represent the blank." << endl;
        cout << "The puzzle will be filled in row-major order, meaning it fills each column of every row. Enter each number separately." << endl;
        vector<vector<int>> userPuzzle(3, vector<int>(3, 0));

        for (int i = 0; i < 3; ++i) { //Just fills puzzle row by row
            for (int j = 0; j < 3; ++j) {
                cin >> userPuzzleInput;
                userPuzzle[i][j] = userPuzzleInput;
            }
        }
        p = Problem(userPuzzle); //Set initial state to custom puzzle
    }
    cout << "Enter your choice of algorithm" << endl;
    cout << "Uniform Cost Search " << endl;
    cout << "A* with the Misplaced Tile heuristic" << endl;
    cout << "A* with the Euclidean distance heuristic" << endl;
    cin >> algoChoice;

    //Call corresponding algo 
    if (algoChoice == 1) {
        goalNode = UniformCostSearch(p);
        if (!(p.isSolvable(p.initial_state))) { return 1; }
    }
    else if (algoChoice == 2) {
        goalNode = AStarSearchMT(p);
        if (!(p.isSolvable(p.initial_state))) { return 1; }
    }
    else if (algoChoice == 3) {
        goalNode = AStarSearchED(p);
        if (!(p.isSolvable(p.initial_state))) { return 1; }
    }
    cout << "Goal!!!" << endl; 
    cout << "To solve this problem the search algorithm expanded a total of " << p.totalExpandedNodes << " nodes." << endl;
    cout << "The maximum number of nodes in the queue at any one time: " << p.maxNumberOfNodesInQueue << "." << endl;
    cout << "The depth of the goal node was " << goalNode->depth << '.' << endl;  

    return 0;
}

#include <iostream>
using namespace std;

int main() {
    int puzzleChoice;
    int algoChoice;

    cout << "Welcome to 8 puzzle solver." << endl; // add student ID here ?
    cout << "Type '1' to use a default puzzle, or '2' to enter your own puzzle." << endl;
    cin >> puzzleChoice;

    if (puzzleChoice == 1) {
        //call function to solve default puzzle which is hardcoded ?
    }
    if (puzzleChoice == 2) { 
        cout << "Enter your puzzle, use a zero to represent the blank" << endl;
        int input;
        for(int i = 0; i < 3; ++i) {
            for(int j = 0; j < 3; ++j) {
                cin >> input;
                // vector<vector>[i][j] = input.
            }
        }
    }


        cout << "Enter the first row, use space or tabs between numbers" << endl;
        //take input here and send to corresponding function or add to vector and then send 
        //entire vector altogether 

        cout << "Enter the second row, use space or tabs between numbers" << endl;
        cout << "Enter the third row, use space or tabs between numbers" << endl;

        cout << "Enter your choice of algorithm" << endl;
        cout << "Uniform Cost Search " << endl;
        cout << "A* with the Misplaced Tile heuristic" << endl;
        cout << "A* with the Euclidean distance heuristic" << endl;
        cin >> algoChoice;

        //call correspodning function based on algochoice and that fnction can call 
        //func drawPath to show expanding the node and best choice... stuff from project


        cout << "Goal!!!" << endl; //maybe remove this because there are some cases where 
        //8 puzzle cant be solved?

        //for these three statements, maybe do it in the function itself and not here?
        cout << "To solve this problem the search algorithm expanded a total of XXX (correct numbers should appear here) nodes." << endl;
        cout << "The maximum number of nodes in the queue at any one time: YYY." << endl;
        cout << "The depth of the goal node was ZZZ." << endl;  

        return 0;
}

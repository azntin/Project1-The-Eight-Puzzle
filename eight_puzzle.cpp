#include "eight_puzzle.h"
#include <vector>
#include <iostream>

using namespace std;

void UniformCostSearch(Problem p) {
    cout << "Not yet implemented"
}

void AStarSearchMT(Problem p) {
    cout << "Not yet implemented" << endl;
}

void AStarSearchED(Problem p) {
    cout << "Not yet implemented" << endl;
}

/*
function Graph-Search(problem) returns a solution, or failure
    initialize frontier using the initial state of problem
    initialize the explored set to be empty
    loop do
        if the frontier is empty then return failure

        choose a leaf noed and remove it from the frontier

        if the node contains a goal statae then return the corresponding solution

        add the node to the explored set

        expand the chosen node, adding the resulting nodes to the frontier
            only if not in the frontier or explored set
*/
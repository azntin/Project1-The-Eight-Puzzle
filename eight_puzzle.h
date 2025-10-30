#pragma once
#include <array>
#include <string>
#include <vector>
#include <set>
#include <utility>
#include <cstddef>

using namespace std;

struct Node {
    array<int,9> state;
    Node* parent;
    string move;
    int g;
    int h;
    int f;

    Node(array<int,9> s, Node* p = nullptr, string mv = "", int g_n = 0, int h_n = 0)
        : state(s), parent(p), move(mv), g(g_), h(h_), f(g_ + h_) {}
};

struct Problem {
    array<int,9> initial{1,2,3,4,8,0,7,6,5};   // default puzzle
    array<int,9> goal   {1,2,3,4,5,6,7,8,0};   // goal puzzle

    static bool isSolvable(const array<int,9>& s);
    static vector<pair<array<int,9>,string>> neighbors(const array<int,9>& s);
};

struct SearchStats {
    int nodesExpanded = 0;
    size_t maxQueue = 0;
};

// Search prototypes
Node* uniform_cost_search(const Problem&, SearchStats&, bool trace = true);
Node* a_star_misplaced(const Problem&, SearchStats&, bool trace = true);
Node* a_star_euclidean(const Problem&, SearchStats&, bool trace = true);
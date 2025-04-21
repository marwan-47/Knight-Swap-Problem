#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include "mainwindow.h"

using namespace std;
int ROWS = 4;
int COLS = 3;


struct State {
    std::vector<int> positions; // [W1, W2, W3, B1, B2, B3]
    bool whiteTurn;     // true = White's move, false = Black's move

    bool operator<(const State& other) const {
        return std::tie(positions, whiteTurn) < std::tie(other.positions, other.whiteTurn);
    }

    bool operator==(const State& other) const {
        return positions == other.positions && whiteTurn == other.whiteTurn;
    }
};


// Moves a knight can make
const vector<pair<int, int>> moves = {
    {1, 2}, {2, 1}, {-1, 2}, {-2, 1},
    {1, -2}, {2, -1}, {-1, -2}, {-2, -1}
};

// Converts cell index to board coordinates
pair<int, int> idxToCoord(int idx) {
    int r = 3 - ((idx - 1) / 3);       
    int c = (idx - 1) % 3;
    return {r, c};
}

// Converts board coordinates to cell index
int coordToIdx(int r, int c) {
    int flipped_r = 3 - r;             
    return flipped_r * 3 + c + 1;
}

// Check if cell is within 3x3 board
bool isValid(int r, int c) {
    return r >= 0 && r < 4 && c >= 0 && c < 3 ;
}

// Generate all reachable states from a given state
vector<State> generateNextStates(const State& s, bool turnBased) {
    vector<State> result;
    int start = turnBased ? (s.whiteTurn ? 0 : 3) : 0;
    int end   = turnBased ? (s.whiteTurn ? 3 : 6) : 6;

    for (int i = start; i < end; ++i) {
        auto coord = idxToCoord(s.positions[i]);
        for (auto [dr, dc] : moves) {
            int nr = coord.first + dr;
            int nc = coord.second + dc;
            if (isValid(nr, nc)) {
                int dest = coordToIdx(nr, nc);
                if (find(s.positions.begin(), s.positions.end(), dest) == s.positions.end()) {
                    State ns = s;
                    ns.positions[i] = dest;
                    sort(ns.positions.begin(), ns.positions.begin() + 3); // white
                    sort(ns.positions.begin() + 3, ns.positions.end());   // black
                    if (turnBased) ns.whiteTurn = !s.whiteTurn; // Switch turn
                    result.push_back(ns);
                }
            }
        }
    }
    return result;
}

void printBoard(const std::vector<int>& s) {
    // Create a 4x3 board initialized with '.'
    vector<vector<char>> board(4, vector<char>(3, '.'));

    // Map knight positions to the board
    for (int i = 0; i < 3; ++i) {
        int pos = s[i]; // White knight
        auto cordW = idxToCoord(pos);
        board[cordW.first][cordW.second] = 'W' ; 
    }
    for (int i = 3; i < 6; ++i) {
        int pos = s[i]; // Black knight
        auto cordB = idxToCoord(pos);
        board[cordB.first][cordB.second] = 'B' ;  
    }

    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 3; ++c) {
            cout << board[r][c] << ' ';
        }
        cout << '\n';
    }
    cout << "------------\n";
}


// Find minimum number of moves using BFS
int solveMCNF(const State& start, const State& goal, bool turnBased,MainWindow* mainwindow) {
    map<State, int> dist;
    map<State, State> parent; // For path reconstruction
    queue<State> q;

    dist[start] = 0;
    q.push(start);

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        if (cur.positions == goal.positions) {
            State final = cur;
            // Print full path:
            vector<State> path;
            while (cur.positions != start.positions || cur.whiteTurn != start.whiteTurn) {
                path.push_back(cur);
                cur = parent[cur];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            for (const auto& step : path) {
                printBoard(step.positions);
                mainwindow->updateBoard(step.positions);

            }
            return dist[final];
        }

        for (const State& next : generateNextStates(cur, turnBased)) {
            if (!dist.count(next)) {
                dist[next] = dist[cur] + 1;
                parent[next] = cur;
                q.push(next);
            }
        }
    }
    return -1; // Not reachable
}



/*int main() {
    RawState startPos = {1,2,3,10,11,12};
    RawState goalPos  = {10,11,12,1,2,3};

    sort(startPos.begin(), startPos.begin() + 3);
    sort(startPos.begin() + 3, startPos.end());
    sort(goalPos.begin(), goalPos.begin() + 3);
    sort(goalPos.begin() + 3, goalPos.end());

    State start = {startPos, true};  // White starts
    State goal  = {goalPos, false};  // Turn is ignored in goal check

    bool turnBased = false;
    int minMoves = solveMCNF(start, goal, turnBased);
    cout << "Minimum number of moves: " << minMoves << endl;
}*/

#ifndef CHESS_H
#define CHESS_H

#include <vector>
#include <utility>

extern int ROWS;
extern int COLS;

using namespace std;


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

// Coordinate conversions
std::pair<int, int> idxToCoord(int idx);
int coordToIdx(int r, int c);
bool isValid(int r, int c);

// Knight logic
std::vector<State> generateNextStates(const State& s, bool turnBased);

// Board utility
void printBoard(const std::vector<int>& s);

// Path solver
class MainWindow;  // Forward declaration so we can pass pointer

int solveMCNF(const State& start, const State& goal, bool turnBased, MainWindow* mainwindow = nullptr);

#endif // CHESS_H

#ifndef ALGORITHMS_DOT_H
#define ALGORITHMS_DOT_H

#include "Graph.h"

// this exception is thrown when all possible paths have been traversed, and none of them is a solution
struct NoSolutionPathException : public exception {
    NoSolutionPathException();
    NoSolutionPathException(const string& message);
};

// this exception is thrown when the number of visited paths so far has exceeded the path visit limit
struct StuckInCycleException : public exception {
    StuckInCycleException();
    StuckInCycleException(const string& message);
};

struct Algorithms {

    string inputFile;
    string outputFile;
    int pathVisitLimit;

    Algorithms(const string& in, const string& out, int limit);

    PathWithInfo depthFirstSearch(bool reverseNeighbourInsertionOrder = false) const;
    PathWithInfo breadthFirstSearch(bool reverseNeighbourInsertionOrder = false) const;
    PathWithInfo lowestCostFirstSearch(bool reverseNeighbourInsertionOrder = false) const;
    PathWithInfo bestFirstSearch(bool reverseNeighbourInsertionOrder = false) const;
    PathWithInfo aStarSearch(bool reverseNeighbourInsertionOrder = false) const;
    PathWithInfo iterativeDeepeningSearch(bool reverseNeighbourInsertionOrder) const;

};

#endif
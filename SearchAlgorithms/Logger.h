#ifndef LOGGER_DOT_H
#define LOGGER_DOT_H

#include "Graph.h"

#include <climits>

struct Logger {

    static string getInsertionMode(bool reversed);

    vector<string> graphLog, algorithmLog, nodeVisitLog, frontierLog, resultLog;
    int pathsInserted = 0, pathsExamined = 0, currentDepth = 0;
    double currentBestSolutionLength = (double) INT_MAX;
    vector<string> nodesVisited;
    bool cycleDetected = false, noSolution = true;
    PathWithInfo solution;
    Graph graph;

    Logger(const Graph& graph, const string& algorithm, const string& insertionMode);
    Logger(const Graph& graph, const string& algorithm, bool reversed);

    void insertIntoFrontier(const Path& path);
    Node removeFromFrontier(const Path& path);
    void findSolution(const Path& path);
    void writeToFile(const string& filename);

    void deepenDepth();
    void findBetterSolution(const Path& path);
    void ignoreCurrentPath();

};

#endif
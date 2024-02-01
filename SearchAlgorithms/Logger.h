#ifndef LOGGER_DOT_H
#define LOGGER_DOT_H

#include "Graph.h"

struct Logger {

    vector<string> graphLog, nodeVisitLog, frontierLog, resultLog;
    int pathsInserted = 0, pathsExamined = 0;
    vector<string> nodesVisited;
    bool cycleDetected = false, noSolution = true;
    PathWithInfo solution;
    Graph graph;

    Logger(const Graph& graph);

    void insertIntoFrontier(const Path& path);
    Node removeFromFrontier(const Path& path);
    void findSolution(const Path& path);
    void writeToFile(const string& filename);

};

#endif
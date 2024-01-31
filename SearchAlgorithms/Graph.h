#ifndef GRAPH_DOT_H
#define GRAPH_DOT_H

#include "general/vectorUtility.h"
#include "general/stringUtility.h"

struct Node {

    string name;
    double heuristic;
    bool isStart = false;
    bool isGoal = false;
    vector<pair<string, double>> neighbours;

    Node(const string& name, double heuristic, bool isStart, bool isGoal, const vector<pair<string, double>>& neighbours);
    Node(const string& line);

    string toString() const;

};

struct Graph {

    vector<Node> nodes;

    Graph(const vector<Node>& nodes);
    Graph(const string& filename);

    void writeToFile(const string& filename) const;

};

#endif
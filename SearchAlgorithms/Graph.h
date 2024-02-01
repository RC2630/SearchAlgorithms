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

struct Path {

    vector<string> nodes;

    Path(const string& path);
    Path(const vector<string>& nodes);

    string getCompactedRepresentation() const;
    Path appendNode(const string& newNode) const;
    int numArcs() const;

};

struct PathWithInfo {

    Path path;
    double totalLength;
    int numArcs;
    double heuristic;

    PathWithInfo(const Path& path, double length, int arcs, double heuristic);
    PathWithInfo(const Path& path, double length, double heuristic);
    PathWithInfo();

    string toString() const;

};

struct Graph {

    vector<Node> nodes;

    Graph(const vector<Node>& nodes);
    Graph(const string& filename);
    Graph();

    vector<string> toStringVector() const;
    void writeToFile(const string& filename) const;
    Node getNodeByName(const string& name) const;
    Node getStartingNode() const;

    double getArcLength(const string& fromNode, const string& toNode) const;
    double getPathLength(const Path& path) const;
    double getPathHeuristic(const Path& path) const;
    PathWithInfo buildPathWithInfo(const Path& path) const;

};

#endif
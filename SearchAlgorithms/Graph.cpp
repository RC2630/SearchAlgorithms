#include "Graph.h"

#include "general/file.h"
#include "general/parseArguments.h"

Node::Node(const string& name, double heuristic, bool isStart, bool isGoal, const vector<pair<string, double>>& neighbours)
: name(name), heuristic(heuristic), isStart(isStart), isGoal(isGoal), neighbours(neighbours)
{ }

Node::Node(const string& line) {
    
    vector<string> portions = strUtil::split(line, " : ");
    string nodePortion = portions.front();
    string neighboursPortion = portions.back();

    this->name = parse::parseArgument(nodePortion, 0);
    this->heuristic = parse::parseNumericalArgument(nodePortion, 1);
    if (parse::numArguments(nodePortion) == 2) {
        if (parse::parseArgument(nodePortion, 2) == "S") {
            this->isStart = true;
        } else if (parse::parseArgument(nodePortion, 2) == "G") {
            this->isGoal = true;
        }
    }

    if (neighboursPortion == "none") {
        return;
    }

    vector<string> neighboursInfo = strUtil::split(neighboursPortion, " ");
    for (int i = 0; i < neighboursInfo.size(); i += 2) {
        string neighbourName = neighboursInfo.at(i);
        double distanceToNeighbour = stod(neighboursInfo.at(i + 1));
        this->neighbours.push_back({neighbourName, distanceToNeighbour});
    }

}

Graph::Graph(const vector<Node>& nodes)
: nodes(nodes)
{ }

Graph::Graph(const string& filename) {
    vector<string> nodeLines;
    file::inputStrVecFrom(nodeLines, filename);
    for (const string& line : nodeLines) {
        this->nodes.push_back(Node(line));
    }
}
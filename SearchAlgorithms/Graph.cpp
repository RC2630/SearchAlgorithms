#include "Graph.h"

#include "general/file.h"
#include "general/parseArguments.h"
#include "general/abstractFunctions.h"
#include "general/numberUtility.h"

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

string Node::toString() const {

    vector<string> parts = {this->name, numUtil::simplify(to_string(this->heuristic))};
    if (this->isGoal) {
        parts.push_back("G");
    } else if (this->isStart) {
        parts.push_back("S");
    }
    parts.push_back(":");

    if (this->neighbours.empty()) {
        parts.push_back("none");
        return strUtil::join(parts, " ");
    }

    for (const auto& [neighbourName, distanceToNeighbour] : this->neighbours) {
        parts.push_back(neighbourName);
        parts.push_back(numUtil::simplify(to_string(distanceToNeighbour)));
    }

    return strUtil::join(parts, " ");
    
}

Path::Path(const string& path)
: nodes(strUtil::split(path, ", "))
{ }

Path::Path(const vector<string>& nodes)
: nodes(nodes)
{ }

string Path::getCompactedRepresentation() const {
    return strUtil::join(nodes, ", ");
}

Path Path::appendNode(const string& newNode) const {
    return Path(this->getCompactedRepresentation() + ", " + newNode);
}

PathWithInfo::PathWithInfo(const Path& path, double length, int arcs, double heuristic)
: path(path), totalLength(length), numArcs(arcs), heuristic(heuristic)
{ }

PathWithInfo::PathWithInfo(const Path& path, double length, double heuristic)
: path(path), totalLength(length), numArcs(path.nodes.size() - 1), heuristic(heuristic)
{ }

PathWithInfo::PathWithInfo()
: path(Path(vector<string>())), totalLength(0), numArcs(0), heuristic(0)
{ }

string PathWithInfo::toString() const {
    return this->path.getCompactedRepresentation() + " (length " + numUtil::simplify(to_string(this->totalLength)) +
           ", arcs " + to_string(this->numArcs) + ", heuristic " + numUtil::simplify(to_string(this->heuristic)) +
           ", f " + numUtil::simplify(to_string(this->totalLength + this->heuristic)) + ")";
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

Graph::Graph()
: nodes({})
{ }

vector<string> Graph::toStringVector() const {
    return absFunc::map<Node, string>(this->nodes, [] (const Node& node) {
        return node.toString();
    });
}

void Graph::writeToFile(const string& filename) const {
    vector<string> lines = this->toStringVector();
    file::outputVecTo(lines, filename);
}

Node Graph::getNodeByName(const string& name) const {
    for (const Node& node : this->nodes) {
        if (node.name == name) {
            return node;
        }
    }
}

Node Graph::getStartingNode() const {
    for (const Node& node : this->nodes) {
        if (node.isStart) {
            return node;
        }
    }
}

double Graph::getArcLength(const string& fromNode, const string& toNode) const {
    Node from = this->getNodeByName(fromNode);
    for (const auto& [name, dist] : from.neighbours) {
        if (name == toNode) {
            return dist;
        }
    }
    throw runtime_error("there is no arc from " + fromNode + " to " + toNode);
}

double Graph::getPathLength(const Path& path) const {
    int length = 0;
    for (int i = 0; i < path.nodes.size() - 1; i++) {
        length += this->getArcLength(path.nodes.at(i), path.nodes.at(i + 1));
    }
    return length;
}

double Graph::getPathHeuristic(const Path& path) const {
    return this->getNodeByName(path.nodes.back()).heuristic;
}

PathWithInfo Graph::buildPathWithInfo(const Path& path) const {
    return PathWithInfo(path, this->getPathLength(path), this->getPathHeuristic(path));
}
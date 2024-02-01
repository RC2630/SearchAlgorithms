#include "Algorithms.h"

#include "general/file.h"
#include "general/numberUtility.h"

#include <stack>

NoSolutionPathException::NoSolutionPathException()
: exception()
{ }

NoSolutionPathException::NoSolutionPathException(const string& message)
: exception(message.c_str())
{ }

StuckInCycleException::StuckInCycleException()
: exception()
{ }

StuckInCycleException::StuckInCycleException(const string& message)
: exception(message.c_str())
{ }

Algorithms::Algorithms(const string& in, const string& out, int limit)
: inputFile(in), outputFile(out), pathVisitLimit(limit)
{ }

PathWithInfo Algorithms::depthFirstSearch(bool reverseNeighbourInsertionOrder) const {
    
    // setting up
    Graph graph(this->inputFile);
    vector<string> graphLog, nodeVisitLog, frontierLog, resultLog;
    int pathsInserted = 0, pathsExamined = 0;
    vector<string> nodesVisited;
    bool cycleDetected = false, noSolution = true;
    PathWithInfo solution;

    // initializing log headers
    vector<string> logHeaders = {"GRAPH:", "NODES VISITED:", "FRONTIER:", "RESULT:"};
    int logHeaderIndex = 0;
    auto makeLogHeader = [&logHeaders] (int index) -> vector<string> {
        return {logHeaders.at(index), string(logHeaders.at(index).size(), '-')};
    };

    // creating logs
    graphLog = vecUtil::concatenate<string>({makeLogHeader(logHeaderIndex++), graph.toStringVector()});
    nodeVisitLog = {makeLogHeader(logHeaderIndex++)};
    frontierLog = {makeLogHeader(logHeaderIndex++)};
    resultLog = {makeLogHeader(logHeaderIndex++)};

    // initializing frontier
    stack<Path> frontier;
    Path currPathToInsert(graph.getStartingNode().name);
    frontier.push(currPathToInsert);
    frontierLog.push_back(
        "+   insert " + to_string(++pathsInserted) + ": " + graph.buildPathWithInfo(currPathToInsert).toString()
    );

    // looping until solution found, frontier empty, or stuck in cycle
    while (!frontier.empty()) {
        
        // stuck in a cycle
        if (pathsExamined == this->pathVisitLimit) {
            cycleDetected = true;
            break;
        }

        // remove path from top of stack
        Path currPathRemoved = frontier.top();
        frontier.pop();
        frontierLog.push_back(
            "  - remove " + to_string(++pathsExamined) + ": " + graph.buildPathWithInfo(currPathRemoved).toString()
        );
        
        // get the node to examine from the end of the current path
        Node currNodeToExamine = graph.getNodeByName(currPathRemoved.nodes.back());
        nodesVisited.push_back(currNodeToExamine.name);

        // check if current node is a goal (i.e. current path is a solution)
        if (currNodeToExamine.isGoal) {
            solution = graph.buildPathWithInfo(currPathRemoved);
            noSolution = false;
            break;
        }

        // add all neighbours of current node to frontier
        auto neighbours =
            reverseNeighbourInsertionOrder ? vecUtil::reverse(currNodeToExamine.neighbours) : currNodeToExamine.neighbours;
        for (const auto& [neighbourName, distToNeighbour] : neighbours) {
            currPathToInsert = currPathRemoved.appendNode(neighbourName);
            frontier.push(currPathToInsert);
            frontierLog.push_back(
                "+   insert " + to_string(++pathsInserted) + ": " + graph.buildPathWithInfo(currPathToInsert).toString()
            );
        }

    }

    // finalize the log for tracking visited nodes
    nodeVisitLog.push_back(strUtil::join(nodesVisited, ", "));

    // finalizing the log for the algorithm's result
    if (cycleDetected) {
        resultLog.push_back(
            "Algorithm appears to be stuck in a cycle after " + to_string(pathsExamined) + " paths have been examined."
        );
    } else if (noSolution) {
        resultLog.push_back(
            "No solution path has been found after " + to_string(pathsExamined) + " paths have been examined."
        );
    } else {
        resultLog = vecUtil::concatenate<string>({resultLog, {
            "Solution path: " + solution.path.getCompactedRepresentation(),
            "Total length of solution path: " + numUtil::simplify(to_string(solution.totalLength)),
            "# of arcs in solution path: " + to_string(solution.numArcs),
            "# of paths inserted to frontier: " + to_string(pathsInserted),
            "# of paths removed from frontier and examined: " + to_string(pathsExamined),
            "# of paths remaining on frontier after solution is found: " + to_string(frontier.size())
        }});
    }

    // putting all the individual logs together to form the final complete log
    vector<string> outputLog = vecUtil::concatenate<string>({
        graphLog, {""}, nodeVisitLog, {""}, frontierLog, {""}, resultLog
    });
    
    // write the final complete log to the output file
    file::outputVecTo(outputLog, this->outputFile);

    // throw exceptions if algorithm was stuck in a cycle or there is no solution path
    if (cycleDetected) {
        throw StuckInCycleException();
    } else if (noSolution) {
        throw NoSolutionPathException();
    }

    // return the solution path if one exists and has been found
    return solution;

}
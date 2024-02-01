#include "Logger.h"

#include "general/numberUtility.h"
#include "general/file.h"

Logger::Logger(const Graph& graph) {

    // setting the logger's graph to the input graph
    this->graph = graph;
    
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

}

void Logger::insertIntoFrontier(const Path& path) {
    frontierLog.push_back(
        "+   insert " + to_string(++pathsInserted) + ": " + graph.buildPathWithInfo(path).toString()
    );
}

Node Logger::removeFromFrontier(const Path& path) {

    // updating the frontier log to include info on the removal from frontier
    frontierLog.push_back(
        "  - remove " + to_string(++pathsExamined) + ": " + graph.buildPathWithInfo(path).toString()
    );

    // updating the nodes visited log and returning the current node to examine
    Node currNodeToExamine = graph.getNodeByName(path.nodes.back());
    nodesVisited.push_back(currNodeToExamine.name);
    return currNodeToExamine;

}

void Logger::findSolution(const Path& path) {
    solution = graph.buildPathWithInfo(path);
    noSolution = false;
}

void Logger::writeToFile(const string& filename) {

    // finalizing the log for tracking visited nodes
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
            "# of paths remaining on frontier after solution is found: " + to_string(pathsInserted - pathsExamined)
        }});
    }

    // putting all the individual logs together to form the final complete log
    vector<string> outputLog = vecUtil::concatenate<string>({
        graphLog, {""}, nodeVisitLog, {""}, frontierLog, {""}, resultLog
    });

    // writing the final complete log to the output file
    file::outputVecTo(outputLog, filename);

}
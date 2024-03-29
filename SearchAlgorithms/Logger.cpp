#include "Logger.h"

#include "general/numberUtility.h"
#include "general/file.h"

string Logger::getInsertionMode(bool reversed) {
    return reversed ? "reversed" : "ordinary";
}

Logger::Logger(const Graph& graph, const string& algorithm, const string& insertionMode) {

    // setting the logger's graph to the input graph
    this->graph = graph;
    
    // initializing log headers
    vector<string> logHeaders = {"GRAPH:", "ALGORITHM:", "NODES VISITED:", "FRONTIER:", "RESULT:"};
    int logHeaderIndex = 0;
    auto makeLogHeader = [&logHeaders] (int index) -> vector<string> {
        return {logHeaders.at(index), string(logHeaders.at(index).size(), '-')};
    };

    // creating logs
    graphLog = vecUtil::concatenate<string>({makeLogHeader(logHeaderIndex++), graph.toStringVector()});
    algorithmLog = vecUtil::concatenate<string>({makeLogHeader(logHeaderIndex++), {
        "Algorithm name: " + algorithm,
        "Order of insertion for neighbours: " + insertionMode
    }});
    nodeVisitLog = {makeLogHeader(logHeaderIndex++)};
    frontierLog = {makeLogHeader(logHeaderIndex++)};
    resultLog = {makeLogHeader(logHeaderIndex++)};

}

Logger::Logger(const Graph& graph, const string& algorithm, bool reversed)
: Logger(graph, algorithm, Logger::getInsertionMode(reversed))
{ }

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
        graphLog, {""}, algorithmLog, {""}, nodeVisitLog, {""}, frontierLog, {""}, resultLog
    });

    // writing the final complete log to the output file
    file::outputVecTo(outputLog, filename);

}

void Logger::deepenDepth() {
    frontierLog.push_back("THE MAXIMUM DEPTH HAS BEEN UPDATED TO " + to_string(++currentDepth));
}

void Logger::findBetterSolution(const Path& path) {
    this->findSolution(path);
    this->currentBestSolutionLength = solution.totalLength;
    frontierLog.push_back(
        "THE CURRENT BEST SOLUTION LENGTH HAS BEEN UPDATED TO " + numUtil::simplify(to_string(solution.totalLength))
    );
}

void Logger::ignoreCurrentPath() {
    this->frontierLog.back() += " [IGNORED]";
    this->nodesVisited.back() = "(" + this->nodesVisited.back() + ")";
}
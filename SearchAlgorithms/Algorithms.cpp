#include "Algorithms.h"
#include "Logger.h"

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
    Logger logger(graph);

    // initializing frontier
    stack<Path> frontier;
    Path currPathToInsert(graph.getStartingNode().name);
    frontier.push(currPathToInsert);
    logger.insertIntoFrontier(currPathToInsert);

    // looping until solution found, frontier empty, or stuck in cycle
    while (!frontier.empty()) {
        
        // stuck in a cycle
        if (logger.pathsExamined == this->pathVisitLimit) {
            logger.cycleDetected = true;
            break;
        }

        // remove path from top of stack and get the node to examine from the end of the current path
        Path currPathRemoved = frontier.top();
        frontier.pop();
        Node currNodeToExamine = logger.removeFromFrontier(currPathRemoved);

        // check if current node is a goal (i.e. current path is a solution)
        if (currNodeToExamine.isGoal) {
            logger.findSolution(currPathRemoved);
            break;
        }

        // add all neighbours of current node to frontier
        auto neighbours =
            reverseNeighbourInsertionOrder ? vecUtil::reverse(currNodeToExamine.neighbours) : currNodeToExamine.neighbours;
        for (const auto& [neighbourName, distToNeighbour] : neighbours) {
            currPathToInsert = currPathRemoved.appendNode(neighbourName);
            frontier.push(currPathToInsert);
            logger.insertIntoFrontier(currPathToInsert);
        }

    }

    // finalizing the logs and writing them to the output file
    logger.writeToFile(this->outputFile);

    // throw exceptions if algorithm was stuck in a cycle or there is no solution path
    if (logger.cycleDetected) {
        throw StuckInCycleException();
    } else if (logger.noSolution) {
        throw NoSolutionPathException();
    }

    // return the solution path if one exists and has been found
    return logger.solution;

}
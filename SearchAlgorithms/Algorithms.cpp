#include "Algorithms.h"
#include "Logger.h"

#include "general/file.h"
#include "general/numberUtility.h"

#include <stack>
#include <queue>

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
    Logger logger(graph, "depth-first search (DFS)", reverseNeighbourInsertionOrder);

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

PathWithInfo Algorithms::breadthFirstSearch(bool reverseNeighbourInsertionOrder) const {

    // setting up
    Graph graph(this->inputFile);
    Logger logger(graph, "breadth-first search (BFS)", reverseNeighbourInsertionOrder);

    // initializing frontier
    queue<Path> frontier;
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

        // remove path from front of queue and get the node to examine from the end of the current path
        Path currPathRemoved = frontier.front();
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

PathWithInfo Algorithms::lowestCostFirstSearch(bool reverseNeighbourInsertionOrder) const {

    // setting up
    Graph graph(this->inputFile);
    Logger logger(graph, "lowest-cost-first search (LCFS)", reverseNeighbourInsertionOrder);

    // creating lambda for priority queue
    auto lowestCostComparator = [] (const PathWithInfo& path1, const PathWithInfo& path2) {
        return path1.totalLength > path2.totalLength;
    };

    // initializing frontier
    priority_queue<PathWithInfo, vector<PathWithInfo>, decltype(lowestCostComparator)> frontier(lowestCostComparator);
    PathWithInfo currPathToInsert = graph.buildPathWithInfo(Path(graph.getStartingNode().name));
    frontier.push(currPathToInsert);
    logger.insertIntoFrontier(currPathToInsert.path);

    // looping until solution found, frontier empty, or stuck in cycle
    while (!frontier.empty()) {

        // stuck in a cycle
        if (logger.pathsExamined == this->pathVisitLimit) {
            logger.cycleDetected = true;
            break;
        }

        // remove path from front of priority queue and get the node to examine from the end of the current path
        PathWithInfo currPathRemoved = frontier.top();
        frontier.pop();
        Node currNodeToExamine = logger.removeFromFrontier(currPathRemoved.path);

        // check if current node is a goal (i.e. current path is a solution)
        if (currNodeToExamine.isGoal) {
            logger.findSolution(currPathRemoved.path);
            break;
        }

        // add all neighbours of current node to frontier
        auto neighbours =
            reverseNeighbourInsertionOrder ? vecUtil::reverse(currNodeToExamine.neighbours) : currNodeToExamine.neighbours;
        for (const auto& [neighbourName, distToNeighbour] : neighbours) {
            currPathToInsert = graph.buildPathWithInfo(currPathRemoved.path.appendNode(neighbourName));
            frontier.push(currPathToInsert);
            logger.insertIntoFrontier(currPathToInsert.path);
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

PathWithInfo Algorithms::bestFirstSearch(bool reverseNeighbourInsertionOrder) const {

    // setting up
    Graph graph(this->inputFile);
    Logger logger(graph, "best-first search (BestFS)", reverseNeighbourInsertionOrder);

    // creating lambda for priority queue
    auto lowestHeuristicComparator = [] (const PathWithInfo& path1, const PathWithInfo& path2) {
        return path1.heuristic > path2.heuristic;
    };

    // initializing frontier
    priority_queue<PathWithInfo, vector<PathWithInfo>, decltype(lowestHeuristicComparator)> frontier(lowestHeuristicComparator);
    PathWithInfo currPathToInsert = graph.buildPathWithInfo(Path(graph.getStartingNode().name));
    frontier.push(currPathToInsert);
    logger.insertIntoFrontier(currPathToInsert.path);

    // looping until solution found, frontier empty, or stuck in cycle
    while (!frontier.empty()) {

        // stuck in a cycle
        if (logger.pathsExamined == this->pathVisitLimit) {
            logger.cycleDetected = true;
            break;
        }

        // remove path from front of priority queue and get the node to examine from the end of the current path
        PathWithInfo currPathRemoved = frontier.top();
        frontier.pop();
        Node currNodeToExamine = logger.removeFromFrontier(currPathRemoved.path);

        // check if current node is a goal (i.e. current path is a solution)
        if (currNodeToExamine.isGoal) {
            logger.findSolution(currPathRemoved.path);
            break;
        }

        // add all neighbours of current node to frontier
        auto neighbours =
            reverseNeighbourInsertionOrder ? vecUtil::reverse(currNodeToExamine.neighbours) : currNodeToExamine.neighbours;
        for (const auto& [neighbourName, distToNeighbour] : neighbours) {
            currPathToInsert = graph.buildPathWithInfo(currPathRemoved.path.appendNode(neighbourName));
            frontier.push(currPathToInsert);
            logger.insertIntoFrontier(currPathToInsert.path);
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

PathWithInfo Algorithms::aStarSearch(bool reverseNeighbourInsertionOrder) const {

    // setting up
    Graph graph(this->inputFile);
    Logger logger(graph, "A* search (A*)", reverseNeighbourInsertionOrder);

    // creating lambda for priority queue
    auto lowestFvalueComparator = [] (const PathWithInfo& path1, const PathWithInfo& path2) {
        return path1.totalLength + path1.heuristic > path2.totalLength + path2.heuristic;
    };

    // initializing frontier
    priority_queue<PathWithInfo, vector<PathWithInfo>, decltype(lowestFvalueComparator)> frontier(lowestFvalueComparator);
    PathWithInfo currPathToInsert = graph.buildPathWithInfo(Path(graph.getStartingNode().name));
    frontier.push(currPathToInsert);
    logger.insertIntoFrontier(currPathToInsert.path);

    // looping until solution found, frontier empty, or stuck in cycle
    while (!frontier.empty()) {

        // stuck in a cycle
        if (logger.pathsExamined == this->pathVisitLimit) {
            logger.cycleDetected = true;
            break;
        }

        // remove path from front of priority queue and get the node to examine from the end of the current path
        PathWithInfo currPathRemoved = frontier.top();
        frontier.pop();
        Node currNodeToExamine = logger.removeFromFrontier(currPathRemoved.path);

        // check if current node is a goal (i.e. current path is a solution)
        if (currNodeToExamine.isGoal) {
            logger.findSolution(currPathRemoved.path);
            break;
        }

        // add all neighbours of current node to frontier
        auto neighbours =
            reverseNeighbourInsertionOrder ? vecUtil::reverse(currNodeToExamine.neighbours) : currNodeToExamine.neighbours;
        for (const auto& [neighbourName, distToNeighbour] : neighbours) {
            currPathToInsert = graph.buildPathWithInfo(currPathRemoved.path.appendNode(neighbourName));
            frontier.push(currPathToInsert);
            logger.insertIntoFrontier(currPathToInsert.path);
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

PathWithInfo Algorithms::iterativeDeepeningSearch(bool reverseNeighbourInsertionOrder) const {

    // setting up
    Graph graph(this->inputFile);
    Logger logger(graph, "iterative deepening search (IDS)", reverseNeighbourInsertionOrder);

    // looping through various maximum depths, incrementing each time
    while (true) {

        // raising the current max depth by 1
        logger.deepenDepth();

        // this flag is set to true if at some point we want to add a path to the frontier but cannot due to max depth
        bool triggerTooDeepCannotAdd = false;

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
                goto postOuterLoop;
            }

            // remove path from top of stack and get the node to examine from the end of the current path
            Path currPathRemoved = frontier.top();
            frontier.pop();
            Node currNodeToExamine = logger.removeFromFrontier(currPathRemoved);

            // check if current node is a goal (i.e. current path is a solution)
            if (currNodeToExamine.isGoal) {
                logger.findSolution(currPathRemoved);
                goto postOuterLoop;
            }

            // add all neighbours of current node to frontier if max depth has not been exceeded
            if (currPathRemoved.numArcs() < logger.currentDepth) {
                auto neighbours =
                    reverseNeighbourInsertionOrder ? vecUtil::reverse(currNodeToExamine.neighbours) : currNodeToExamine.neighbours;
                for (const auto& [neighbourName, distToNeighbour] : neighbours) {
                    currPathToInsert = currPathRemoved.appendNode(neighbourName);
                    frontier.push(currPathToInsert);
                    logger.insertIntoFrontier(currPathToInsert);
                }
            } else {
                triggerTooDeepCannotAdd = triggerTooDeepCannotAdd || !currNodeToExamine.neighbours.empty();
            }

        }

        // if the trigger never happened, then incrementing the max depth is useless as the next iteration will be the same
        if (!triggerTooDeepCannotAdd) {
            break;
        }

    }

    // this label marks the end of the outer loop, used for GOTO statements
    postOuterLoop:

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
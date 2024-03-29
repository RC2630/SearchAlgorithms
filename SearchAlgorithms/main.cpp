#include "Graph.h"
#include "Algorithms.h"

#include "general/ansi_codes.h"
#include "general/parseArguments.h"

const string INPUT_FILE = "file/input.txt";
const string OUTPUT_FILE = "file/output.txt";
const int DEFAULT_PATH_VISIT_LIMIT = 1000;

const string HELP =

    "OVERVIEW:\n\n"
    
    "This program will perform search algorithms on graphs.\n"
    "The input graph should be placed in the file \"file/input.txt\", and the output is stored in \"file/output.txt\".\n"
    "Select the type of search algorithm to use as well as other options in the program's console when it is running,\n"
    "by using a variety of commands, which will be explained below.\n\n"
    
    "INPUT GRAPH SYNTAX:\n\n"
    
    "Each node of the graph is on its own line.\n"
    "The general structure of a node line is:\n"
    "<node_name> <heuristic> <S|G|nothing> : <neighbour_1> <dist_to_neighbour_1> ... <neighbour_b> <dist_to_neighbour_b>\n\n"
    
    "If a node has no neighbours, type \"none\" after the colon.\n"
    "The starting node (there should only be 1) should be marked with \"S\" after its heuristic,\n"
    "while goal nodes (there could be many) should be marked with \"G\" after its heuristic.\n"
    "Note that <b> in the syntax description above refers to the total number of neighbours that the node has.\n\n"
    
    "Here is an example node line:\n"
    "S 24 S : A 3 B 9 C 4\n\n"
    
    "In the example, the node's name is S, its heuristic is 24, and it is the starting node.\n"
    "It has an arc to node A with length 3, an arc to node B with length 9, and an arc to node C with length 4.\n\n"
    
    "COMMANDS:\n\n"
    
    "/help = display this help message\n"
    "/exit = terminate the program\n"
    "/limit = display the current path visit limit (# of paths visited before timeout)\n"
    "/limit <new_limit> = set the path visit limit (# of paths visited before timeout) to new_limit\n"
    "/search <algorithm> <rev?> = perform search using the given algorithm (see section below for details)\n\n"

    "SEARCH COMMAND DETAILS:\n\n"

    "The \"/search\" command is the primary purpose of this program, since it performs search algorithms.\n"
    "To use it, specify a search algorithm as well as an optional argument called \"rev\".\n"
    "The name of the search algorithm is case-insensitive, so feel free to use upper or lower case as you please.\n"
    "The inclusion of the \"rev\" argument will reverse the order in which neighbours are inserted into the frontier.\n\n"

    "Specifically for branch-and-bound search, there is an additional option.\n"
    "The order in which neighbours are added to the frontier can be ordinary, reversed, or by descending F-value.\n"
    "The ordinary and reversed orders are specified the same way as for all the other search algorithms;\n"
    "in other words, they are specified as \"/search b&b\" and \"/search b&b rev\", respectively.\n"
    "The order by descending F-value is specified as \"/search b&b f\";\n"
    "note that this is the only time that the 2nd argument of \"/search\" is allowed to take a value other than \"rev\".\n\n"

    "Currently, the available search algorithms to use are:\n"
    "1. \"dfs\" (depth-first search)\n"
    "2. \"bfs\" (breadth-first search)\n"
    "3. \"lcfs\" (lowest-cost-first search)\n"
    "4. \"bestfs\" (best-first search)\n"
    "5. \"A*\" (classic A* search)\n"
    "6. \"ids\" (iterative deepening search)\n"
    "7. \"b&b\" (branch-and-bound search)\n\n"
    
    "Here are some examples of using the \"/search\" command:\n"
    "/search dfs rev = perform depth-first search with the insertion order of neighbours being reversed\n"
    "/search bfs = perform breadth-first search with the insertion order of neighbours being ordinary\n"
    "/search b&b f = perform branch-and-bound search with the insertion order of neighbours being by descending F-value";

void performSearchAlgorithm(const Algorithms& algorithms, const string& algorithmName, const string& mode) {
    
    PathWithInfo solution;
    bool reversed = (mode == "rev");

    try {

        if (strUtil::equalsIgnoreCase(algorithmName, "dfs")) {
            solution = algorithms.depthFirstSearch(reversed);
        } else if (strUtil::equalsIgnoreCase(algorithmName, "bfs")) {
            solution = algorithms.breadthFirstSearch(reversed);
        } else if (strUtil::equalsIgnoreCase(algorithmName, "lcfs")) {
            solution = algorithms.lowestCostFirstSearch(reversed);
        } else if (strUtil::equalsIgnoreCase(algorithmName, "bestfs")) {
            solution = algorithms.bestFirstSearch(reversed);
        } else if (strUtil::equalsIgnoreCase(algorithmName, "A*")) {
            solution = algorithms.aStarSearch(reversed);
        } else if (strUtil::equalsIgnoreCase(algorithmName, "ids")) {
            solution = algorithms.iterativeDeepeningSearch(reversed);
        } else if (strUtil::equalsIgnoreCase(algorithmName, "b&b")) {
            solution = algorithms.branchAndBoundSearch(mode);
        } else {
            throw runtime_error("algorithm name does not correspond to any valid search algorithm");
        }

        cout << "\nA solution has been found!\n"
             << "\nSolution path: " << ANSI_BLUE << solution.path.getCompactedRepresentation() << ANSI_NORMAL
             << "\nTotal length of solution path: " << ANSI_BLUE << solution.totalLength << ANSI_NORMAL
             << "\n# of arcs in solution path: " << ANSI_BLUE << solution.numArcs << ANSI_NORMAL << "\n";

    } catch (const NoSolutionPathException& e) {
        cout << ANSI_RED << "\nNo solution path has been found.\n" << ANSI_NORMAL;
    } catch (const StuckInCycleException& e) {
        cout << ANSI_RED << "\nThe algorithm appears to be stuck in a cycle. Please update the path visit limit if necessary.\n"
             << ANSI_NORMAL;
    }

}

void run() {
    
    Algorithms algorithms(INPUT_FILE, OUTPUT_FILE, DEFAULT_PATH_VISIT_LIMIT);
    cout << "\nWelcome to the search algorithms program! Please type " << ANSI_YELLOW << "/help" << ANSI_NORMAL
         << " to learn how to use this program.\n";

    while (true) {
        
        cout << "\n" << ANSI_YELLOW << ">>> " << ANSI_GREEN;
        string command;
        getline(cin >> ws, command);
        cout << ANSI_NORMAL;

        if (parse::commandIs(command, "/help")) {
            cout << "\n" << ANSI_BLUE << HELP << ANSI_NORMAL << "\n";
        } else if (parse::commandIs(command, "/exit")) {
            cout << ANSI_BLUE << "\nThank you for using the search algorithms program. See you later!\n" << ANSI_NORMAL;
            break;
        } else if (parse::commandIs(command, "/limit") && parse::numArguments(command) == 0) {
            cout << "\nThe current path visit limit is " << algorithms.pathVisitLimit << ".\n";
        } else if (parse::commandIs(command, "/limit") && parse::numArguments(command) == 1) {
            algorithms.pathVisitLimit = parse::parseNumericalArgument(command);
            cout << "\nThe path visit limit has been updated to " << algorithms.pathVisitLimit << ".\n";
        } else if (parse::commandIs(command, "/search")) {
            string mode = (parse::numArguments(command) == 2) ? parse::parseArgument(command, 2) : "ord";
            performSearchAlgorithm(algorithms, parse::parseArgument(command, 1), mode);
        } else {
            cout << ANSI_RED << "\nSorry, but your command either does not exist or has the wrong number of arguments. "
                 << "Please try again!\n" << ANSI_NORMAL;
        }

    }

}

int main() {
    try {
        run();
    } catch (...) {
        cout << ANSI_RED << "\nOops, an unexpected error occurred. Sorry!\n" << ANSI_NORMAL;
    }
}
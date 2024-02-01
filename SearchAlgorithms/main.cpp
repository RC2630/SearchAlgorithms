#include "Graph.h"

#include "general/ansi_codes.h"

const string INPUT_FILE = "file/input.txt";
const string OUTPUT_FILE = "file/output.txt";

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
    "/exit = terminate the program";

void run() {
    
    cout << "\nWelcome to the search algorithms program! Please type " << ANSI_YELLOW << "/help" << ANSI_NORMAL
         << " to learn how to use this program.\n";

    while (true) {
        
        cout << "\n" << ANSI_YELLOW << ">>> " << ANSI_GREEN;
        string command;
        getline(cin >> ws, command);
        cout << ANSI_NORMAL;

        if (command == "/help") {
            cout << "\n" << ANSI_BLUE << HELP << ANSI_NORMAL << "\n";
        } else if (command == "/exit") {
            cout << ANSI_BLUE << "\nThank you for using the search algorithms program. See you later!\n" << ANSI_NORMAL;
            break;
        } else {
            cout << ANSI_RED << "\nSorry, but that is not a valid command. Please try again!\n" << ANSI_NORMAL;
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
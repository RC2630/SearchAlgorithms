#include "Graph.h"

const string INPUT_FILE = "file/input.txt";
const string OUTPUT_FILE = "file/output.txt";

int main() {
    Graph g(INPUT_FILE);
    g.writeToFile(OUTPUT_FILE);
    cout << "done!\n";
}
#include "Algorithms.h"

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

PathWithInfo Algorithms::depthFirstSearch() const {
    // TODO
    return PathWithInfo(Path({"A", "B", "C"}), 20, 0);
}
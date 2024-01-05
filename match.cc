#include <iostream>
#include <string>
#include "match.hh"

using namespace std;

map<int, match> createMatches()
{
    map<int, match> matches;

    // Example of creating match instances and adding them to the map
    match match1("Heat", "Lakers", 100, 98, "2020-10-11");
    match match2("Lakers", "Heat", 106, 93, "2020-10-09");

    match match3("Lakers", "Heat", 0, 0, "2023-10-06");

    matches[1] = match1;
    matches[2] = match2;
    matches[3] = match3;

    return matches;
}
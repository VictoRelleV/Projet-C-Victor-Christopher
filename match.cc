#include <iostream>
#include <string>
#include "match.hh"

using namespace std;

map<int, match*> createMatches()
{
    map<int, match*> matches;

    // Example of creating match instances and adding them to the map
    match* match1 = new match("Lakers", "Heat", 116, 98, "2020-10-06");
    match* match2 = new match("Lakers", "Heat", 124, 114, "2021-10-06");

    match* match3 = new match("Lakers", "Heat", 0, 0, "2020-10-06");

    matches[1] = match1;
    matches[2] = match2;
    matches[3] = match3;

    return matches;
}
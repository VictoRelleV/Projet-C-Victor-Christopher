#include <iostream>
#include <string>
#include "../include/Match.hh"

using namespace std;

map<int, Match*> createMatches()
{
    map<int, Match*> matches;

    // Example of creating Match instances and adding them to the map
    Match* match1 = new Match("Lakers", "Heat", 116, 98, "2020-10-06");
    Match* match2 = new Match("Lakers", "Heat", 124, 114, "2021-10-06");

    Match* match3 = new Match("Lakers", "Heat", 0, 0, "2020-10-06");

    matches[1] = match1;
    matches[2] = match2;
    matches[3] = match3;

    return matches;
}
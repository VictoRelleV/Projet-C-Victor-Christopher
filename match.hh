#ifndef MATCH_HH
#define MATCH_HH

#include <iostream>
#include <string>
#include <map>

using namespace std;

class match
{
protected:
    string _equipe1;
    string _equipe2;
    int _score1;
    int _score2;
    string _date;

public:
    match()
    {
    }

    match(string equipe1, string equipe2, int score1, int score2, string date)
        : _equipe1(equipe1), _equipe2(equipe2), _score1(score1), _score2(score2), _date(date)
    {
    }

    // Other getter methods
    const string& getEquipe1() const {
        return _equipe1;
    }

    const string& getEquipe2() const {
        return _equipe2;
    }

    int getScore1() const {
        return _score1;
    }

    void setScore1(int score1) {
        _score1 = score1;
    }

    int getScore2() const {
        return _score2;
    }

    void setScore2(int score2) {
        _score2 = score2;
    }

    const string& getDate() const {
        return _date;
    }

    void setDate(string date) {
        _date = date;
    }
};

map<int, match*> createMatches();

#endif
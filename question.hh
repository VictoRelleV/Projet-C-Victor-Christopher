#ifndef QUESTION_HH
#define QUESTION_HH

#include <string>
#include <vector>

using namespace std;

// Structure pour représenter une question
struct Question {
    string questionText;
    vector<string> options;
    int correctOptionIndex;
};

vector<Question> createQuestions();

#endif
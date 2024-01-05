#include <map>
#include <string>
#include <vector>
#include <random>

#include "question.hh"

using namespace std;

vector<Question> questions = {
    {"Quel joueur a marqué le plus de points lors des JO 2016 ?", {"Kevin Durant", "LeBron James", "Stephen Curry"}, 0},
    {"Qui est le meilleur marqueur de tous les temps en NBA ?", {"Kareem Abdul-Jabbar", "LeBron James", "Michael Jordan"}, 0},
    {"Quelle équipe a remporté le plus de championnats NBA ?", {"Los Angeles Lakers", "Boston Celtics", "Golden State Warriors"}, 1},
    {"Quelle équipe a remporté les Jeux Olympiques de 2004 ?", {"Argentine", "Etats-Unis", "Espagne"}, 0},
    {"Quelle équipe a remporté les Jeux Olympiques de 2008 ?", {"Argentine", "Etats-Unis", "Espagne"}, 1},
    {"Quelle équipe a remporté les Jeux Olympiques de 2012 ?", {"Argentine", "Etats-Unis", "Espagne"}, 1},
    {"Quelle équipe a remporté les Jeux Olympiques de 2016 ?", {"Argentine", "Etats-Unis", "Espagne"}, 1},
    {"Quelle équipe a remporté les Jeux Olympiques de 2020 ?", {"Argentine", "Etats-Unis", "Espagne"}, 1},
    {"Quelle équipe a remporté les Jeux Olympiques de 2024 ?", {"Argentine", "Etats-Unis", "Espagne"}, 1},
    {"Quelle équipe a remporté les Jeux Olympiques de 2028 ?", {"Argentine", "Etats-Unis", "Espagne"}, 1},
    {"Quelle équipe a remporté les Jeux Olympiques de 2032 ?", {"Argentine", "Etats-Unis", "Espagne"}, 1},
    {"Quelle équipe a remporté les Jeux Olympiques de 2036 ?", {"Argentine", "Etats-Unis", "Espagne"}, 1},
    {"Quelle équipe a remporté les Jeux Olympiques de 2040 ?", {"Argentine", "Etats-Unis", "Espagne"}, 1},
    {"Quelle équipe a remporté les Jeux Olympiques de 2044 ?", {"Argentine", "Etats-Unis", "Espagne"}, 1},
    {"Quelle équipe a remporté les Jeux Olympiques de 2048 ?", {"Argentine", "Etats-Unis", "Espagne"}, 1},
    {"Quelle équipe a remporté les Jeux Olympiques de 2052 ?", {"Argentine", "Etats-Unis", "Espagne"}, 1},
    {"Quelle équipe a remporté les Jeux Olympiques de 2056 ?", {"Argentine", "Etats-Unis", "Espagne"}, 1}
};

vector<Question> createQuestions() {
    return questions;
}

#ifndef FONCTIONS_HH
#define FONCTIONS_HH

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>

#include <vector>
#include <map>
#include <mutex>
#include "joueur.hh"
#include "match.hh"
#include "question.hh"

void updatePlayerLabel(QLabel *label, joueur* player, int x, int y);
void updateMatchLabel(QLabel *label, const match &currentMatch, int x, int y, int horloge);
void updatePlayerImageLabel(QLabel *label, joueur* player, int x, int y, int size);
bool compareOvr(const pair<int, joueur*> &a, const pair<int, joueur*> &b);
void updatePlayerImageLabelAll(QLabel* PointGuard1, QLabel* ShootingGuard1, QLabel* SmallForward1, QLabel* PowardForward1, QLabel* Center1, 
                                QLabel* PointGuard2, QLabel* ShootingGuard2, QLabel* SmallForward2, QLabel* PowardForward2, QLabel* Center2, 
                                map<int, joueur*> team1, map<int, joueur*> team2);
void updateTeams(map<int, joueur*>& team1, map<int, joueur*>& team2);
joueur* getMVP(map<int, joueur*> players);
int endGame(QLabel* Info, map<int, joueur*> team1, map<int, joueur*> team2, map<int, match> matches, int horloge, int start, joueur* mvp);
void hideAfterDelay(QLabel *label);
int Quizz(vector<Question> questions);
void RandomUpdateTeams(map<int, joueur*>& team1, map<int, joueur*>& team2);
int ClickTheBall(map<int, joueur*> team1, map<int, match> matches);
void hideAfterDelay2(QWidget *window);
#endif
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
class joueur; // Déclaration anticipée de joueur
#include "match.hh"
#include "question.hh"
#include "clickablelabel.hh"

void updateMatchLabel(QLabel &label, match* currentMatch, int x, int y, int horloge);

void updatePlayerImageLabel(QLabel &label, joueur* player, int x, int y, int size);
void updatePlayerImageLabelAll(QLabel& PointGuard1, QLabel& ShootingGuard1, QLabel& SmallForward1, QLabel& PowardForward1, QLabel& Center1,
                                QLabel& PointGuard2, QLabel& ShootingGuard2, QLabel& SmallForward2, QLabel& PowardForward2, QLabel& Center2,
                                map<int, joueur*> team1, map<int, joueur*> team2);

QString getPositionLabel(joueur* player);
void updatePlayerTextLabel(QLabel& label, joueur* player, int posX, int posY);
void updatePlayerTextLabel2(QLabel& label, joueur* player, int posX, int posY, int reveal);

void updatePlayerTextLabelAll(QLabel& PointGuard1Text, QLabel& ShootingGuard1Text, QLabel& SmallForwardText, QLabel& PowardForward1Text, QLabel& Center1Text,
                              QLabel& PointGuard2Text, QLabel& ShootingGuard2Text, QLabel& SmallForward2Text, QLabel& PowardForward2Text, QLabel& Center2Text,
                              map<int, joueur*> team1, map<int, joueur*> team2, vector<int> indicePick);

int endGame(QLabel& Info, map<int, joueur*> team1, map<int, joueur*> team2, map<int, match*> matches, int horloge, int start, joueur* mvp);
void hideAfterDelay(QLabel& label);
void askQuestion(QLabel& Info1, joueur* player, map<int, match*> matches, vector<Question> questions);

#endif
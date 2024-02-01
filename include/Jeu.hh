#ifndef JEU_HH
#define JEU_HH

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>
#include <QBoxLayout>
#include <QLineEdit>
#include <QTableWidget>
#include <QHeaderView>
#include <QMouseEvent>

#include <random>
#include <thread>
#include <chrono>

#include "Match.hh"
#include "HeadCoach.hh"
#include "Joueur.hh"
#include "fonctions.hh"
#include "question.hh"
#include "ClickableLabel.hh"
#include "Center.hh"
#include "PowerForward.hh"
#include "SmallForward.hh"
#include "ShootingGuard.hh"
#include "PointGuard.hh"
#include "../lib/basketball/include/Game.h"

using namespace std;

int horloge = 0;
int start = 0;
int poste = 0;
int action1 = 0;
int score = 0;
int coachboost = 0;
vector<int> indicePick(5, 0);
Joueur* mvp;
Joueur* joueurChoisi;

class Jeu {
private:
    QApplication app;
    QWidget window;
    QLabel Court;
    QPixmap pixmap_court;
    QLabel Judges;
    QPixmap pixmap_judges;
    QLabel Logo;
    QPixmap pixmap_logo;
    QLabel Coach1;
    QPixmap pixmap_coach1;
    QLabel Coach2;
    QPixmap pixmap_coach2;
    QLabel textScore;
    QLabel textInfo1;
    QLabel textInfo2;
    QLabel Info1;
    QLabel Info2;
    QLabel Info3;
    QLabel PointGuard1Text;
    QLabel ShootingGuard1Text;
    QLabel SmallForwardText;
    QLabel PowardForward1Text;
    QLabel Center1Text;
    QLabel PointGuard2;
    QLabel PointGuard2Text;
    QLabel ShootingGuard2;
    QLabel ShootingGuard2Text;
    QLabel SmallForward2;
    QLabel SmallForward2Text;
    QLabel PowardForward2;
    QLabel PowardForward2Text;
    QLabel Center2;
    QLabel Center2Text;
    QPushButton Start;
    QPushButton Play;
    QPushButton Reset;
    QPushButton CoachBoost;

public:
    Jeu(int argc, char *argv[]):
        app(argc, argv),
        Court(&window),
        pixmap_court("./Image/sunscourt.png"),
        Judges(&window),
        pixmap_judges("./Image/judges.jpg"),
        Logo(&window),
        pixmap_logo("./Image/logo.png"),
        Coach1(&window),
        pixmap_coach1("./Image/kerr.png"),
        Coach2(&window),
        pixmap_coach2("./Image/popo.png"),
        textScore(&window),
        textInfo1(&window),
        textInfo2(&window),
        Info1(&window),
        Info2(&window),
        Info3(&window),
        PointGuard1Text(&window),
        ShootingGuard1Text(&window),
        SmallForwardText(&window),
        PowardForward1Text(&window),
        Center1Text(&window),
        PointGuard2(&window),
        PointGuard2Text(&window),
        ShootingGuard2(&window),
        ShootingGuard2Text(&window),
        SmallForward2(&window),
        SmallForward2Text(&window),
        PowardForward2(&window),
        PowardForward2Text(&window),
        Center2(&window),
        Center2Text(&window),
        Start("Start", &window),
        Play("Play", &window),
        Reset("Reset", &window),
        CoachBoost("Coach Boost", &window)
    {}

    void lancer() {
        // Create Joueur instance
        std::map<int, Joueur*> players = createPlayers();

        // Create team
        pair<map<int, Joueur*>, map<int, Joueur*>> result = createTeams(players);
        map<int, Joueur*> team1 = result.first;
        map<int, Joueur*> team2 = result.second;

        HeadCoach coach("Kerr", "Steve", "Warriors", "./Image/steve_kerr.jpg");

        // Create Match instance
        map<int, Match*> matches = createMatches();

        // Create question
        vector<Question> questions = createQuestions();
        shuffle(questions.begin(), questions.end(), std::mt19937(std::random_device()()));


        window.setWindowTitle("Olympic Basketball");
        window.setFixedSize(1500, 980);

        // Set background image using a style sheet
        window.setStyleSheet("background-image: url('./Image/fond.jpg');");

        pixmap_court = pixmap_court.scaled(1460, 1460, Qt::KeepAspectRatio);
        Court.setPixmap(pixmap_court);
        Court.move(20, 20);
        Court.show();

        pixmap_judges = pixmap_judges.scaled(450, 200, Qt::KeepAspectRatio);
        Judges.setStyleSheet("border: 2px solid black;");
        Judges.setPixmap(pixmap_judges);
        Judges.move(525, 757);
        Judges.show();

        pixmap_logo = pixmap_logo.scaled(100, 100, Qt::KeepAspectRatio);
        Logo.setPixmap(pixmap_logo);
        Logo.move(609, 150);
        Logo.show();

        pixmap_coach1 = pixmap_coach1.scaled(200, 200, Qt::KeepAspectRatio);
        Coach1.setStyleSheet("border: 2px solid black;");
        Coach1.setPixmap(pixmap_coach1);
        Coach1.move(20, 757);
        Coach1.show();

        pixmap_coach2 = pixmap_coach2.scaled(200, 200, Qt::KeepAspectRatio);
        Coach2.setStyleSheet("border: 2px solid black;");
        Coach2.setPixmap(pixmap_coach2);
        Coach2.move(1276, 757);
        Coach2.show();

        updateMatchLabel(textScore, matches[3], 650, 150, horloge);

        textInfo1.setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
        textInfo1.setText(QString("Lakers"));
        textInfo1.setFixedSize(265, 20);
        textInfo1.move(240, 790);
        textInfo1.setAlignment(Qt::AlignCenter); // Centrer le texte dans le label
        textInfo1.show();

        textInfo2.setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
        textInfo2.setText(QString("Heat"));
        textInfo2.setFixedSize(265, 20);
        textInfo2.move(995, 790);
        textInfo2.setAlignment(Qt::AlignCenter); // Centrer le texte dans le label
        textInfo2.show();

        Info1.setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
        Info1.setText(QString("Click Start to start the Match\nClick Reset to reset the Match\nClick Play to simulate a Match"));
        Info1.setFixedSize(265, 100);
        Info1.move(240, 820);
        Info1.setAlignment(Qt::AlignCenter); // Centrer le texte dans le label
        Info1.show();

        Info2.setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
        Info2.setText(QString("Click Start to start the Match\nClick Reset to reset the Match\nClick Play to simulate a Match"));
        Info2.setFixedSize(265, 100);
        Info2.move(995, 820);
        Info2.setAlignment(Qt::AlignCenter); // Centrer le texte dans le label
        Info2.show();

        Info3.setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
        Info3.setText(QString("Click Start to start the Match\nClick Reset to reset the Match\nClick Play to simulate a Match"));
        Info3.setFixedSize(390, 104);
        Info3.move(555, 857);
        Info3.setAlignment(Qt::AlignCenter); // Centrer le texte dans le label
        Info3.show();

        ClickableLabel PointGuard1(QString(team1[1]->getFullName().c_str()), team1[1]->getStatAttaque(),
                                   team1[1]->getStatDefense(), team1[1]->getStatVitesse(), 1, window, Info1, &action1, &poste);
        updatePlayerImageLabel(PointGuard1, team1[1], 550, 309, 226);

        updatePlayerTextLabel(PointGuard1Text, team1[1], 540, 535);

        ClickableLabel ShootingGuard1(QString(team1[2]->getFullName().c_str()), team1[2]->getStatAttaque(),
                                      team1[2]->getStatDefense(), team1[2]->getStatVitesse(), 2, window, Info1, &action1, &poste);
        updatePlayerImageLabel(ShootingGuard1, team1[2], 350, 410, 226);

        updatePlayerTextLabel(ShootingGuard1Text, team1[2], 340, 636);

        ClickableLabel SmallForward1(QString(team1[3]->getFullName().c_str()), team1[3]->getStatAttaque(),
                                     team1[3]->getStatDefense(), team1[3]->getStatVitesse(), 3, window, Info1, &action1, &poste);
        updatePlayerImageLabel(SmallForward1, team1[3], 350, 120, 226);

        updatePlayerTextLabel(SmallForwardText, team1[3], 340, 346);

        ClickableLabel PowardForward1(QString(team1[4]->getFullName().c_str()), team1[4]->getStatAttaque(),
                                      team1[4]->getStatDefense(), team1[4]->getStatVitesse(), 4, window, Info1, &action1, &poste);
        updatePlayerImageLabel(PowardForward1, team1[4], 150, 450, 226);

        updatePlayerTextLabel(PowardForward1Text, team1[4], 140, 676);

        ClickableLabel Center1(QString(team1[5]->getFullName().c_str()), team1[5]->getStatAttaque(),
                               team1[5]->getStatDefense(), team1[5]->getStatVitesse(), 5, window, Info1, &action1, &poste);
        updatePlayerImageLabel(Center1, team1[5], 150, 160, 226);

        updatePlayerTextLabel(Center1Text, team1[5], 140, 386);

        updatePlayerImageLabel(PointGuard2, team2[1], 790, 309, 226);

        updatePlayerTextLabel2(PointGuard2Text, team2[1], 780, 535, indicePick[0]);

        updatePlayerImageLabel(ShootingGuard2, team2[2], 990, 410, 226);

        updatePlayerTextLabel2(ShootingGuard2Text, team2[2], 980, 636, indicePick[1]);

        updatePlayerImageLabel(SmallForward2, team2[3], 990, 120, 226);

        updatePlayerTextLabel2(SmallForward2Text, team2[3], 980, 346, indicePick[2]);

        updatePlayerImageLabel(PowardForward2, team2[4], 1190, 450, 226);

        updatePlayerTextLabel2(PowardForward2Text, team2[4], 1180, 676, indicePick[3]);

        updatePlayerImageLabel(Center2, team2[5], 1190, 160, 226);

        updatePlayerTextLabel2(Center2Text, team2[5], 1180, 386, indicePick[4]);

        Start.setFixedSize(50, 20);
        Start.setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
        Start.move(665, 727);
        QObject::connect(&Start, &QPushButton::clicked, [&]() {
            if (start == 0 && horloge == 0) {
                start = 1;
                Info1.clear();
                Info3.setText(QString("Match commence"));
                joueurChoisi = choisirJoueurAuHasard(team2);
                Info2.setText(QString("%1 %2 is picked")
                                       .arg(joueurChoisi->getPrenom().c_str())
                                       .arg(joueurChoisi->getNom().c_str()));
            }
        });

        Play.setFixedSize(50, 20);
        Play.setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
        Play.move(725, 727);
        QObject::connect(&Play, &QPushButton::clicked, [&]() {
            if(start == 1 && action1 != 0){

                if(action1==1){
                    team1[poste]->atq(joueurChoisi, Info3, questions, matches);
                } else if (action1==2) {
                    team1[poste]->def(joueurChoisi, Info3, questions, matches);
                } else if (action1==3) {
                    team1[poste]->vit(joueurChoisi, Info3, questions, matches);
                }

                if(horloge==11){
                    Game game(30);
                    score = game.run();
                    matches[3]->setScore1(matches[3]->getScore1() + score);
                }

                joueurChoisi = choisirJoueurAuHasard(team2);
                Info2.setText(QString("%1 %2 is picked")
                                       .arg(joueurChoisi->getPrenom().c_str())
                                       .arg(joueurChoisi->getNom().c_str()));

                Info1.clear();
                action1 = 0;
                horloge++;
                recreateLabels(PointGuard1, ShootingGuard1, SmallForward1, PowardForward1, Center1, team1);
                updatePlayerImageLabelAll(PointGuard1, ShootingGuard1, SmallForward1, PowardForward1, Center1,
                                          PointGuard2, ShootingGuard2, SmallForward2, PowardForward2, Center2,
                                          team1, team2);
                updatePlayerTextLabelAll(PointGuard1Text, ShootingGuard1Text, SmallForwardText, PowardForward1Text, Center1Text,
                                         PointGuard2Text, ShootingGuard2Text, SmallForward2Text, PowardForward2Text, Center2Text,
                                         team1, team2, indicePick);
                updateMatchLabel(textScore, matches[3], 650, 150, horloge);
            }
            start = endGame(Info3, team1, team2, matches, horloge, start, mvp);
        });

        Reset.setFixedSize(50, 20);
        Reset.setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
        Reset.move(785, 727);
        QObject::connect(&Reset, &QPushButton::clicked, [&]() {
            horloge = 0;
            start = 0;
            action1 = 0;
            coachboost = 0;
            indicePick = vector<int>(5, 0);
            matches[3]->setScore1(0);
            matches[3]->setScore2(0);
            players = createPlayers();
            result = createTeams(players);
            team1 = result.first;
            team2 = result.second;
            recreateLabels(PointGuard1, ShootingGuard1, SmallForward1, PowardForward1, Center1, team1);
            updatePlayerImageLabelAll(PointGuard1, ShootingGuard1, SmallForward1, PowardForward1, Center1,
                                      PointGuard2, ShootingGuard2, SmallForward2, PowardForward2, Center2,
                                      team1, team2);
            updatePlayerTextLabelAll(PointGuard1Text, ShootingGuard1Text, SmallForwardText, PowardForward1Text, Center1Text,
                                     PointGuard2Text, ShootingGuard2Text, SmallForward2Text, PowardForward2Text, Center2Text,
                                     team1, team2, indicePick);
            updateMatchLabel(textScore, matches[3], 650, 150, horloge);
            Info1.setText(QString("Click Start to start the Match\nClick Reset to reset the Match\nClick Play to simulate a Match"));
            Info2.setText(QString("Click Start to start the Match\nClick Reset to reset the Match\nClick Play to simulate a Match"));
            Info3.setText(QString("Click Start to start the Match\nClick Reset to reset the Match\nClick Play to simulate a Match"));
        });

        CoachBoost.setFixedSize(100, 20);
        CoachBoost.setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
        CoachBoost.move(23, 727);
        QObject::connect(&CoachBoost, &QPushButton::clicked, [&]() {
            if(start==1 && coachboost==0){
                coachboost = 1;
                int nbrPick = Draft();
                indicePick = coach.scoutingReport(horloge, nbrPick, matches, team2, Info3);
                updateMatchLabel(textScore, matches[3], 650, 150, horloge);
                updatePlayerTextLabelAll(PointGuard1Text, ShootingGuard1Text, SmallForwardText, PowardForward1Text, Center1Text,
                                         PointGuard2Text, ShootingGuard2Text, SmallForward2Text, PowardForward2Text, Center2Text,
                                         team1, team2, indicePick);
            }
        });

        window.show();

        QApplication::exec();
    }
};

#endif

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

#include <thread>
#include <chrono>

#include "match.hh"
#include "joueur.hh"
#include "fonctions.hh"
#include "question.hh"
#include "clickablelabel.hh"
#include "center.hh"
#include "powerforward.hh"
#include "smallforward.hh"
#include "shootingguard.hh"
#include "pointguard.hh"
#include "lib/basketball/include/Game.h"

using namespace std;

int horloge = 0;
int start = 0;
int timeouts = 0;
int poste = 0;
int action1 = 0;
int score = 0; 
joueur* mvp;
joueur* joueurChoisi;
string reponse;

// Utilise l'horloge pour initialiser le générateur de nombres aléatoires
std::random_device rd;
std::mt19937 gen(rd());
// Génère un nombre aléatoire entre 1 et 2
uniform_int_distribution<> distribution2(1, 2);
uniform_int_distribution<> distribution100(1, 100);

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Create joueur instance
    std::map<int, joueur*> players = createPlayers();

    // Create team
    pair<map<int, joueur*>, map<int, joueur*>> result = createTeams(players);
    map<int, joueur*> team1 = result.first;
    map<int, joueur*> team2 = result.second;

    // Create match instance
    map<int, match*> matches = createMatches();

    // Create question
    vector<Question> questions = createQuestions();
    random_shuffle(questions.begin(), questions.end());

    QWidget window;
    window.setWindowTitle("Image Display Example");
    window.setFixedSize(1500, 1000);

    // Set background image using a style sheet
    window.setStyleSheet("background-image: url('/home/vivi_z/C++/Projet/Image/fond.jpg');");

    Game game(20);
    score = game.run();
    cout << "Score: " << score << endl;

    QLabel *Court = new QLabel(&window);
    QPixmap pixmap_court("/home/vivi_z/C++/Projet/Image/sunscourt.png");
    pixmap_court = pixmap_court.scaled(1460, 1460, Qt::KeepAspectRatio);
    Court->setPixmap(pixmap_court);
    Court->move(20, 20);
    Court->show();

    QLabel *textScore = new QLabel(&window);
    textScore->setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
    textScore->setFixedSize(200, 100);
    updateMatchLabel(textScore, matches[3], 650, 150, horloge);

    QLabel *Info1 = new QLabel(&window);
    Info1->setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
    Info1->setText(QString("Click Start to start the match\nClick Reset to reset the match\nClick Play to simulate a match"));
    Info1->setFixedSize(300, 150);
    Info1->move(430, 800);
    Info1->setAlignment(Qt::AlignCenter); // Centrer le texte dans le label
    Info1->show();

    QLabel *Info2 = new QLabel(&window);
    Info2->setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
    Info2->setText(QString("Click Start to start the match\nClick Reset to reset the match\nClick Play to simulate a match"));
    Info2->setFixedSize(300, 150);
    Info2->move(770, 800);
    Info2->setAlignment(Qt::AlignCenter); // Centrer le texte dans le label
    Info2->show();
    
    ClickableLabel *PointGuard1 = new ClickableLabel(QString(team1[1]->getName().c_str()), team1[1]->getATQ(), team1[1]->getDEF(), team1[1]->getVIT(), 1, &window, Info1);
    updatePlayerImageLabel(PointGuard1, team1[1], 550, 309, 226);

    QLabel *PointGuard1Text = new QLabel(&window);
    updatePlayerTextLabel(PointGuard1Text, team1[1], 540, 535);

    ClickableLabel *ShootingGuard1 = new ClickableLabel(QString(team1[2]->getName().c_str()), team1[2]->getATQ(), team1[2]->getDEF(), team1[2]->getVIT(), 2, &window, Info1);
    updatePlayerImageLabel(ShootingGuard1, team1[2], 350, 410, 226);

    QLabel *ShootingGuard1Text = new QLabel(&window);
    updatePlayerTextLabel(ShootingGuard1Text, team1[2], 340, 636);

    ClickableLabel *SmallForward1 = new ClickableLabel(QString(team1[3]->getName().c_str()), team1[3]->getATQ(), team1[3]->getDEF(), team1[3]->getVIT(), 3, &window, Info1);
    updatePlayerImageLabel(SmallForward1, team1[3], 350, 120, 226);

    QLabel *SmallForwardText = new QLabel(&window);
    updatePlayerTextLabel(SmallForwardText, team1[3], 340, 346);

    ClickableLabel *PowardForward1 = new ClickableLabel(QString(team1[4]->getName().c_str()), team1[4]->getATQ(), team1[4]->getDEF(), team1[4]->getVIT(), 4, &window, Info1);
    updatePlayerImageLabel(PowardForward1, team1[4], 150, 450, 226);

    QLabel *PowardForward1Text = new QLabel(&window);
    updatePlayerTextLabel(PowardForward1Text, team1[4], 140, 676);

    ClickableLabel *Center1 = new ClickableLabel(QString(team1[5]->getName().c_str()), team1[5]->getATQ(), team1[5]->getDEF(), team1[5]->getVIT(), 5, &window, Info1);
    updatePlayerImageLabel(Center1, team1[5], 150, 160, 226);

    QLabel *Center1Text = new QLabel(&window);
    updatePlayerTextLabel(Center1Text, team1[5], 140, 386);

    QLabel *PointGuard2 = new QLabel(&window);
    updatePlayerImageLabel(PointGuard2, team2[1], 790, 309, 226);

    QLabel *ShootingGuard2 = new QLabel(&window);
    updatePlayerImageLabel(ShootingGuard2, team2[2], 990, 410, 226);

    QLabel *SmallForward2 = new QLabel(&window);
    updatePlayerImageLabel(SmallForward2, team2[3], 990, 120, 226);

    QLabel *PowardForward2 = new QLabel(&window);
    updatePlayerImageLabel(PowardForward2, team2[4], 1190, 450, 226);

    QLabel *Center2 = new QLabel(&window);
    updatePlayerImageLabel(Center2, team2[5], 1190, 160, 226);

    QPushButton *Start = new QPushButton("Start", &window);
    Start->setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
    Start->move(10, 700);
    QObject::connect(Start, &QPushButton::clicked, [&]() {
        if (start == 0) {
            start = 1;
            Info1->setText(QString("Match commence"));
            joueurChoisi = choisirJoueurAuHasard(team2);
            Info2->setText(QString("%1 %2 est choisi")
                            .arg(joueurChoisi->getPrenom().c_str())
                            .arg(joueurChoisi->getNom().c_str()));
        }
    });

    QPushButton *Play = new QPushButton("Play", &window);
    Play->setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
    Play->move(10, 760);
    QObject::connect(Play, &QPushButton::clicked, [&]() {
        start = endGame(Info1, team1, team2, matches, horloge, start, mvp);
        if(start == 1 && action1 != 0){
            
            if(horloge==12 || horloge==24 || horloge==36 || horloge==48){
                Game game(20);
                score = game.run();
                matches[3]->setScore1(matches[3]->getScore1() + score);
                Info1->setText(QString("Score: %1").arg(score));
            }

            if(action1==1){
                team1[poste]->atq(joueurChoisi, Info1, questions, matches);
            } else if (action1==2) {
                team1[poste]->def(joueurChoisi, Info1, questions, matches);
            } else if (action1==3) {
                team1[poste]->vit(joueurChoisi, Info1, questions, matches);
            }
            
            joueurChoisi = choisirJoueurAuHasard(team2);
            Info2->setText(QString("%1 %2 est choisi")
                .arg(joueurChoisi->getPrenom().c_str())
                .arg(joueurChoisi->getNom().c_str()));

            action1 = 0;
            horloge++;
            updatePlayerImageLabelAll(PointGuard1, ShootingGuard1, SmallForward1, PowardForward1, Center1, 
                                    PointGuard2, ShootingGuard2, SmallForward2, PowardForward2, Center2, 
                                    team1, team2);
            updatePlayerTextLabelAll(PointGuard1Text, ShootingGuard1Text, SmallForwardText, PowardForward1Text, Center1Text, team1);
            updateMatchLabel(textScore, matches[3], 650, 150, horloge);
        }
    });

    QPushButton *Reset = new QPushButton("Reset", &window);
    Reset->setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
    Reset->move(10, 730);
    QObject::connect(Reset, &QPushButton::clicked, [&]() {
        horloge = 0;
        start = 0;
        timeouts = 0;
        action1 = 0;
        matches[3]->setScore1(0);
        matches[3]->setScore2(0);
        players = createPlayers();
        result = createTeams(players);
        team1 = result.first;
        team2 = result.second;
        updatePlayerImageLabelAll(PointGuard1, ShootingGuard1, SmallForward1, PowardForward1, Center1, 
                                PointGuard2, ShootingGuard2, SmallForward2, PowardForward2, Center2, 
                                team1, team2);
        updatePlayerTextLabelAll(PointGuard1Text, ShootingGuard1Text, SmallForwardText, PowardForward1Text, Center1Text, team1);                                    
        updateMatchLabel(textScore, matches[3], 650, 150, horloge);
        Info1->setText(QString("Click Start to start the match\nClick Reset to reset the match\nClick Play to simulate a match"));
        Info2->setText(QString("Click Start to start the match\nClick Reset to reset the match\nClick Play to simulate a match"));
    });

    QLabel *Shaq1 = new QLabel(&window);
    QPixmap pixmap_shaq1("/home/vivi_z/C++/Projet/Image/Shaq1.jpeg");
    pixmap_shaq1 = pixmap_shaq1.scaled(100, 100, Qt::KeepAspectRatio);
    Shaq1->setPixmap(pixmap_shaq1);
    Shaq1->move(450, 600);
    Shaq1->hide();

    QLabel *Shaq2 = new QLabel(&window);
    QPixmap pixmap_shaq2("/home/vivi_z/C++/Projet/Image/Shaq2.jpeg");
    pixmap_shaq2 = pixmap_shaq2.scaled(100, 100, Qt::KeepAspectRatio);
    Shaq2->setPixmap(pixmap_shaq2);
    Shaq2->move(450, 600);
    Shaq2->hide();

    QLabel *Logo = new QLabel(&window);
    QPixmap pixmap_logo("/home/vivi_z/C++/Projet/Image/logo.png");
    pixmap_logo = pixmap_logo.scaled(100, 100, Qt::KeepAspectRatio);
    Logo->setPixmap(pixmap_logo);
    Logo->move(609, 150);
    Logo->show();

    window.show();

    return app.exec();
}

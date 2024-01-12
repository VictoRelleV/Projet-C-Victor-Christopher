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
#include "lib/basketball/include/Game.h"

using namespace std;

int horloge = 0;
int start = 0;
int timeouts = 0;
int switchs = 0;
joueur* mvp;
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
    map<int, match> matches = createMatches();

    // Create question
    vector<Question> questions = createQuestions();

    QWidget window;
    window.setWindowTitle("Image Display Example");
    window.setFixedSize(1500, 1000);

    // Set background image using a style sheet
    window.setStyleSheet("background-image: url('/home/vivi_z/C++/Projet/Image/fond.jpg');");

    //Game game(20);
    //game.run();

    QLabel *Court = new QLabel(&window);
    QPixmap pixmap_court("/home/vivi_z/C++/Projet/Image/sunscourt.png");
    pixmap_court = pixmap_court.scaled(1460, 1460, Qt::KeepAspectRatio);
    Court->setPixmap(pixmap_court);
    Court->move(20, 20);
    Court->show();
    
    QLabel *PointGuard1 = new QLabel(&window);
    updatePlayerImageLabel(PointGuard1, team1[1], 550, 309, 226);

    QLabel *PointGuard1Text = new QLabel(&window);
    PointGuard1Text->setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
    PointGuard1Text->setFixedSize(180, 40);
    PointGuard1Text->setText(QString("%1 %2\nATQ: %3 DEF: %4 VIT: %5")
                            .arg(team1[1]->getPrenom().c_str())
                            .arg(team1[1]->getNom().c_str())
                            .arg(team1[1]->getATQ())
                            .arg(team1[1]->getDEF())
                            .arg(team1[1]->getVIT()));
    PointGuard1Text->setAlignment(Qt::AlignCenter); // Centrer le texte
    PointGuard1Text->move(540, 535);
    PointGuard1Text->show();

    QLabel *ShootingGuard1 = new QLabel(&window);
    updatePlayerImageLabel(ShootingGuard1, team1[2], 350, 410, 226);

    QLabel *ShootingGuard1Text = new QLabel(&window);
    ShootingGuard1Text->setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
    ShootingGuard1Text->setFixedSize(180, 40);
    ShootingGuard1Text->setText(QString("%1 %2\nATQ: %3 DEF: %4 VIT: %5")
                            .arg(team1[2]->getPrenom().c_str())
                            .arg(team1[2]->getNom().c_str())
                            .arg(team1[2]->getATQ())
                            .arg(team1[2]->getDEF())
                            .arg(team1[2]->getVIT()));
    ShootingGuard1Text->setAlignment(Qt::AlignCenter); // Centrer le texte
    ShootingGuard1Text->move(340, 636);
    ShootingGuard1Text->show();

    QLabel *SmallForward1 = new QLabel(&window);
    updatePlayerImageLabel(SmallForward1, team1[3], 350, 120, 226);

    QLabel *SmallForwardText = new QLabel(&window);
    SmallForwardText->setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
    SmallForwardText->setFixedSize(180, 40);
    SmallForwardText->setText(QString("%1 %2\nATQ: %3 DEF: %4 VIT: %5")
                            .arg(team1[3]->getPrenom().c_str())
                            .arg(team1[3]->getNom().c_str())
                            .arg(team1[3]->getATQ())
                            .arg(team1[3]->getDEF())
                            .arg(team1[3]->getVIT()));
    SmallForwardText->setAlignment(Qt::AlignCenter); // Centrer le texte
    SmallForwardText->move(340, 346);
    SmallForwardText->show();

    QLabel *PowardForward1 = new QLabel(&window);
    updatePlayerImageLabel(PowardForward1, team1[4], 150, 450, 226);

    QLabel *PowardForward1Text = new QLabel(&window);
    PowardForward1Text->setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
    PowardForward1Text->setFixedSize(180, 40);
    PowardForward1Text->setText(QString("%1 %2\nATQ: %3 DEF: %4 VIT: %5")
                            .arg(team1[4]->getPrenom().c_str())
                            .arg(team1[4]->getNom().c_str())
                            .arg(team1[4]->getATQ())
                            .arg(team1[4]->getDEF())
                            .arg(team1[4]->getVIT()));
    PowardForward1Text->setAlignment(Qt::AlignCenter); // Centrer le texte
    PowardForward1Text->move(140, 676);
    PowardForward1Text->show();

    QLabel *Center1 = new QLabel(&window);
    updatePlayerImageLabel(Center1, team1[5], 150, 160, 226);

    QLabel *Center1Text = new QLabel(&window);
    Center1Text->setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
    Center1Text->setFixedSize(180, 40);
    Center1Text->setText(QString("%1 %2\nATQ: %3 DEF: %4 VIT: %5")
                            .arg(team1[5]->getPrenom().c_str())
                            .arg(team1[5]->getNom().c_str())
                            .arg(team1[5]->getATQ())
                            .arg(team1[5]->getDEF())
                            .arg(team1[5]->getVIT()));
    Center1Text->setAlignment(Qt::AlignCenter); // Centrer le texte
    Center1Text->move(140, 386);
    Center1Text->show();

    QLabel *textLabel1 = new QLabel(&window);
    //textLabel1->setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
    //textLabel1->setFixedSize(230, 150);
    //updatePlayerLabel(textLabel1, team1[1], 10, 540);

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

    QLabel *textLabel2 = new QLabel(&window);
    textLabel2->setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
    textLabel2->setFixedSize(230, 150);
    updatePlayerLabel(textLabel2, team2[1], 1260, 540);

    QLabel *textScore = new QLabel(&window);
    textScore->setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
    textScore->setFixedSize(200, 100);
    updateMatchLabel(textScore, matches[3], 650, 470, horloge);

    QLabel *Info = new QLabel(&window);
    Info->setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
    Info->setText(QString("Click Start to start the match\nClick Reset to reset the match\nClick Play to simulate a match"));
    Info->setFixedSize(600, 200);
    Info->move(450, 600);
    Info->setAlignment(Qt::AlignCenter); // Centrer le texte dans le label
    Info->show();

    QPushButton *Play = new QPushButton("Play", &window);
    Play->setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
    Play->move(10, 760);
    QObject::connect(Play, &QPushButton::clicked, [&]() {
        start = endGame(Info, team1, team2, matches, horloge, start, mvp);
        if(start == 1){
            int randomValue100 = distribution100(gen);
            int pointsScored = 0;
            int pointsScoredAgainst = 0;

            if(team1[1]->getATQ() > team2[1]->getDEF()){
                pointsScored = 2;
            } else {
                pointsScored = 0;
            }
            if(team1[1]->getDEF() > team2[1]->getATQ()){
                pointsScoredAgainst = 0;
            } else {
                pointsScoredAgainst = 2;
            }
            if(team1[1]->getVIT() > team2[1]->getVIT()){
                pointsScored += 1;
            } else {
                pointsScoredAgainst += 1;
            }
            team1[1]->setPoint(team1[1]->getPoint() + pointsScored);  
            team2[1]->setPoint(team2[1]->getPoint() + pointsScoredAgainst);
            matches[3].setScore1(matches[3].getScore1() + pointsScored);
            matches[3].setScore2(matches[3].getScore2() + pointsScoredAgainst);
            
            Info->setText(QString("%1 %2 marque %3 point%4\n%5 %6 marque %7 point%8")
                            .arg(team1[1]->getPrenom().c_str())
                            .arg(team1[1]->getNom().c_str())
                            .arg(pointsScored)
                            .arg(pointsScored > 1 ? "s" : "")
                            .arg(team2[1]->getPrenom().c_str())
                            .arg(team2[1]->getNom().c_str())
                            .arg(pointsScoredAgainst)
                            .arg(pointsScoredAgainst > 1 ? "s" : ""));

            switchs = 0;
            horloge++;
            RandomUpdateTeams(team1, team2);
            updatePlayerImageLabelAll(PointGuard1, ShootingGuard1, SmallForward1, PowardForward1, Center1, 
                                    PointGuard2, ShootingGuard2, SmallForward2, PowardForward2, Center2, 
                                    team1, team2);
            updatePlayerLabel(textLabel1, team1[1], 10, 540);
            updatePlayerLabel(textLabel2, team2[1], 1260, 540);
            updateMatchLabel(textScore, matches[3], 650, 470, horloge);
        }
    });

    QPushButton *Start = new QPushButton("Start", &window);
    Start->setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
    Start->move(10, 700);
    QObject::connect(Start, &QPushButton::clicked, [&]() {
        if (start == 0) {
            start = 1;
            Info->setText(QString("Match commence"));
        }
    });

    QPushButton *Reset = new QPushButton("Reset", &window);
    Reset->setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
    Reset->move(10, 730);
    QObject::connect(Reset, &QPushButton::clicked, [&]() {
        horloge = 0;
        start = 0;
        timeouts = 0;
        switchs = 0;
        matches[3].setScore1(0);
        matches[3].setScore2(0);
        players = createPlayers();
        result = createTeams(players);
        team1 = result.first;
        team2 = result.second;
        updatePlayerImageLabelAll(PointGuard1, ShootingGuard1, SmallForward1, PowardForward1, Center1, 
                                PointGuard2, ShootingGuard2, SmallForward2, PowardForward2, Center2, 
                                team1, team2);
        updateMatchLabel(textScore, matches[3], 650, 470, horloge);
        updatePlayerLabel(textLabel1, team1[1], 10, 540);
        updatePlayerLabel(textLabel2, team2[1], 1200, 540);
        Info->setText(QString("Click Start to start the match\nClick Reset to reset the match\nClick Play to simulate a match"));
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

    QPushButton *QuizzJO = new QPushButton("QuizzJO", &window);
    QuizzJO->setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
    QuizzJO->move(10, 790);
    QObject::connect(QuizzJO, &QPushButton::clicked, [&]() {
        if (start == 1) {
            bool ok;
            QString reponse = QInputDialog::getText(&window, "Quizz JO", "Quel joueur a marqué le plus de points lors des JO 2016 ?", QLineEdit::Normal, QString(), &ok);

            if (ok) {
                if (reponse == "Kevin Durant") {
                    Shaq1->show();
                    matches[3].setScore1(matches[3].getScore1() + 3);
                    team1[1]->setPoint(team1[1]->getPoint() + 3);
                    team1[1]->setOVR(team1[1]->getOVR() + 1);
                    Info->setText(QString("Bonne réponse\n%1 %2 marque 3 points")
                                    .arg(team1[1]->getPrenom().c_str())
                                    .arg(team1[1]->getNom().c_str()));
                    thread(hideAfterDelay, Shaq1).detach();
                    
                } else {
                    Shaq2->show();
                    matches[3].setScore2(matches[3].getScore2() + 3);
                    team2[1]->setPoint(team2[1]->getPoint() + 3);
                    team2[1]->setOVR(team2[1]->getOVR() + 1);
                    Info->setText(QString("Mauvaise réponse\n%1 %2 marque 3 points")
                                    .arg(team2[1]->getPrenom().c_str())
                                    .arg(team2[1]->getNom().c_str()));
                    thread(hideAfterDelay, Shaq2).detach();
                }
            }
            updateMatchLabel(textScore, matches[3], 650, 470, horloge);
            updatePlayerLabel(textLabel1, team1[1], 10, 540);
            updatePlayerLabel(textLabel2, team2[1], 1260, 540);
        }
    });

    QPushButton *Timeout = new QPushButton("Timeout", &window);
    Timeout->setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
    Timeout->move(10, 820);
    QObject::connect(Timeout, &QPushButton::clicked, [&]() {
        int streak = 0;
        int bank = 0;
        start = endGame(Info, team1, team2, matches, horloge, start, mvp);
        if (start == 1 && timeouts < 7) {
            while(streak >= 0 && streak < 5){
                random_shuffle(questions.begin(), questions.end());
                int userAnswerIndex = Quizz(questions);

                // Traiter la réponse en fonction du bouton cliqué
                if (userAnswerIndex != -1) {
                    if (userAnswerIndex == questions[0].correctOptionIndex) {
                        streak++;
                        Shaq1->show();
                        bank += 3;
                        Info->setText(QString("Bonne réponse\n%1 bucks in the bank")
                                        .arg(bank));
                        thread(hideAfterDelay, Shaq1).detach();
                    } else {
                        streak = -1;
                        Shaq2->show();
                        matches[3].setScore2(matches[3].getScore2() + bank);
                        team2[1]->setPoint(team2[1]->getPoint() + bank);
                        team2[1]->setOVR(team2[1]->getOVR() + bank);
                        Info->setText(QString("Mauvaise réponse\n%1 %2 marque %3 points")
                                        .arg(team2[1]->getPrenom().c_str())
                                        .arg(team2[1]->getNom().c_str())
                                        .arg(bank));
                        thread(hideAfterDelay, Shaq2).detach();
                    }
                }
            }
            if (streak == 5) {
            matches[3].setScore1(matches[3].getScore1() + bank);
            team1[1]->setPoint(team1[1]->getPoint() + bank);
            team1[1]->setOVR(team1[1]->getOVR() + bank);
            Info->setText(QString("Bonne réponse\n%1 %2 marque %3 points")
                            .arg(team1[1]->getPrenom().c_str())
                            .arg(team1[1]->getNom().c_str())
                            .arg(bank));
            }
            horloge++;
            timeouts++;
            updateMatchLabel(textScore, matches[3], 650, 470, horloge);
            updatePlayerLabel(textLabel1, team1[1], 10, 540);
            updatePlayerLabel(textLabel2, team2[1], 1260, 540);
        }
    });

    QPushButton *Switch = new QPushButton("Switch", &window);
    Switch->setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
    Switch->move(10, 850);
    QObject::connect(Switch, &QPushButton::clicked, [&]() {
        start = endGame(Info, team1, team2, matches, horloge, start, mvp);
        if (start == 1 && switchs < 3) {
            RandomUpdateTeams(team1, team2);
            updatePlayerImageLabelAll(PointGuard1, ShootingGuard1, SmallForward1, PowardForward1, Center1, 
                                    PointGuard2, ShootingGuard2, SmallForward2, PowardForward2, Center2, 
                                    team1, team2);

            switchs++;
            Info->setText(QString("Switch"));
            updateMatchLabel(textScore, matches[3], 650, 470, horloge);
            updatePlayerLabel(textLabel1, team1[1], 10, 540);
            updatePlayerLabel(textLabel2, team2[1], 1260, 540);
        }
    });

    QLabel *Logo = new QLabel(&window);
    QPixmap pixmap_logo("/home/vivi_z/C++/Projet/Image/logo.png");
    pixmap_logo = pixmap_logo.scaled(100, 100, Qt::KeepAspectRatio);
    Logo->setPixmap(pixmap_logo);
    Logo->move(609, 470);
    Logo->show();

    // Créer une nouvelle fenêtre de jeu
    QWidget *gameWindow = new QWidget();
    gameWindow->setWindowTitle("Click The Ball");
    gameWindow->setFixedSize(500, 500);
    gameWindow->setStyleSheet("background-image: url('/home/vivi_z/C++/Projet/Image/fond.jpg');");

    ClickableLabel *Ball = new ClickableLabel(gameWindow);
    QPixmap pixmap_ball("/home/vivi_z/C++/Projet/Image/ball.png");
    pixmap_ball = pixmap_ball.scaled(100, 100, Qt::KeepAspectRatio);
    Ball->setPixmap(pixmap_ball);
    Ball->move(0, 0);
    Ball->show();

    QPushButton *Click = new QPushButton("Click", &window);
    Click->setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
    Click->move(10, 880);
    QObject::connect(Click, &QPushButton::clicked, [&]() {
        start = endGame(Info, team1, team2, matches, horloge, start, mvp);
        if (start == 1) {
            thread(hideAfterDelay2, gameWindow).detach();
            gameWindow->show();
        }
    });
    
    // Connectez le signal de fermeture de la fenêtre à la fonction de mise à jour (utilisation d'une fonction lambda)
    QObject::connect(gameWindow, &QWidget::destroyed, [&]() {
        // Mettez à jour les points et les étiquettes ici
        team1[1]->setPoint(team1[1]->getPoint() + Ball->getScore());
        matches[3].setScore1(matches[3].getScore1() + Ball->getScore());
        updateMatchLabel(textScore, matches[3], 650, 470, horloge);
        updatePlayerLabel(textLabel1, team1[1], 10, 540);
    });
    window.show();

    return app.exec();
}

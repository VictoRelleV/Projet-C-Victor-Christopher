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
int poste = 0;
int action1 = 0;
int action2 = 0;
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
    
    ClickableLabel *PointGuard1 = new ClickableLabel("Lebron James", team1[1]->getATQ(), team1[1]->getDEF(), team1[1]->getVIT(), 1, &window, Info1);
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

    ClickableLabel *ShootingGuard1 = new ClickableLabel("Lebron James", team1[2]->getATQ(), team1[2]->getDEF(), team1[2]->getVIT(), 2, &window, Info1);
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

    ClickableLabel *SmallForward1 = new ClickableLabel("Lebron James", team1[3]->getATQ(), team1[3]->getDEF(), team1[3]->getVIT(), 3, &window, Info1);
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

    ClickableLabel *PowardForward1 = new ClickableLabel("Lebron James", team1[4]->getATQ(), team1[4]->getDEF(), team1[4]->getVIT(), 4, &window, Info1);
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

    ClickableLabel *Center1 = new ClickableLabel("Lebron James", team1[5]->getATQ(), team1[5]->getDEF(), team1[5]->getVIT(), 5, &window, Info1);
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
            if (joueurChoisi) {
                action2 = Action(joueurChoisi, Info2);
            }
        }
    });

    QPushButton *Play = new QPushButton("Play", &window);
    Play->setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
    Play->move(10, 760);
    QObject::connect(Play, &QPushButton::clicked, [&]() {
        start = endGame(Info1, team1, team2, matches, horloge, start, mvp);
        if(start == 1 && action1 != 0){
            
            if(action2==1){
                if(action1==1){
                    if(team1[poste]->getATQ() > joueurChoisi->getATQ()){
                        matches[3].setScore1(matches[3].getScore1() + team1[poste]->getATQ()-joueurChoisi->getATQ());
                        Info1->setText(QString("%1 %2 marque %3 points")
                                        .arg(team1[poste]->getPrenom().c_str())
                                        .arg(team1[poste]->getNom().c_str())
                                        .arg(team1[poste]->getATQ()-joueurChoisi->getATQ()));
                    } else {
                        matches[3].setScore2(matches[3].getScore2() + joueurChoisi->getATQ()-team1[poste]->getATQ());
                        Info1->setText(QString("%1 %2 marque %3 points")
                                        .arg(joueurChoisi->getPrenom().c_str())
                                        .arg(joueurChoisi->getNom().c_str())
                                        .arg(joueurChoisi->getATQ()-team1[poste]->getATQ()));
                    }
                }
            }

            else if(action2==2){
                if(action1==1){
                    if(team1[poste]->getATQ() > joueurChoisi->getDEF()){
                        matches[3].setScore1(matches[3].getScore1() + team1[poste]->getATQ()-joueurChoisi->getDEF());
                        Info1->setText(QString("%1 %2 marque %3 points")
                                        .arg(team1[poste]->getPrenom().c_str())
                                        .arg(team1[poste]->getNom().c_str())
                                        .arg(team1[poste]->getATQ()-joueurChoisi->getDEF()));
                    } else {
                        matches[3].setScore2(matches[3].getScore2() + joueurChoisi->getDEF()-team1[poste]->getATQ());
                        Info1->setText(QString("%1 %2 marque %3 points")
                                        .arg(joueurChoisi->getPrenom().c_str())
                                        .arg(joueurChoisi->getNom().c_str())
                                        .arg(joueurChoisi->getDEF()-team1[poste]->getATQ()));
                    }
                }
            }
            
            horloge++;
            updatePlayerImageLabelAll(PointGuard1, ShootingGuard1, SmallForward1, PowardForward1, Center1, 
                                    PointGuard2, ShootingGuard2, SmallForward2, PowardForward2, Center2, 
                                    team1, team2);
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
                    Info1->setText(QString("Bonne réponse\n%1 %2 marque 3 points")
                                    .arg(team1[1]->getPrenom().c_str())
                                    .arg(team1[1]->getNom().c_str()));
                    thread(hideAfterDelay, Shaq1).detach();
                    
                } else {
                    Shaq2->show();
                    matches[3].setScore2(matches[3].getScore2() + 3);
                    Info1->setText(QString("Mauvaise réponse\n%1 %2 marque 3 points")
                                    .arg(team2[1]->getPrenom().c_str())
                                    .arg(team2[1]->getNom().c_str()));
                    thread(hideAfterDelay, Shaq2).detach();
                }
            }
            updateMatchLabel(textScore, matches[3], 650, 470, horloge);
        }
    });

    QPushButton *Timeout = new QPushButton("Timeout", &window);
    Timeout->setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
    Timeout->move(10, 820);
    QObject::connect(Timeout, &QPushButton::clicked, [&]() {
        int streak = 0;
        int bank = 0;
        start = endGame(Info1, team1, team2, matches, horloge, start, mvp);
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
                        Info1->setText(QString("Bonne réponse\n%1 bucks in the bank")
                                        .arg(bank));
                        thread(hideAfterDelay, Shaq1).detach();
                    } else {
                        streak = -1;
                        Shaq2->show();
                        matches[3].setScore2(matches[3].getScore2() + bank);
                        Info1->setText(QString("Mauvaise réponse\n%1 %2 marque %3 points")
                                        .arg(team2[1]->getPrenom().c_str())
                                        .arg(team2[1]->getNom().c_str())
                                        .arg(bank));
                        thread(hideAfterDelay, Shaq2).detach();
                    }
                }
            }
            if (streak == 5) {
            matches[3].setScore1(matches[3].getScore1() + bank);
            Info1->setText(QString("Bonne réponse\n%1 %2 marque %3 points")
                            .arg(team1[1]->getPrenom().c_str())
                            .arg(team1[1]->getNom().c_str())
                            .arg(bank));
            }
            horloge++;
            timeouts++;
            updateMatchLabel(textScore, matches[3], 650, 470, horloge);
        }
    });

    QPushButton *Switch = new QPushButton("Switch", &window);
    Switch->setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
    Switch->move(10, 850);
    QObject::connect(Switch, &QPushButton::clicked, [&]() {
        start = endGame(Info1, team1, team2, matches, horloge, start, mvp);
        if (start == 1 && switchs < 3) {
            RandomUpdateTeams(team1, team2);
            updatePlayerImageLabelAll(PointGuard1, ShootingGuard1, SmallForward1, PowardForward1, Center1, 
                                    PointGuard2, ShootingGuard2, SmallForward2, PowardForward2, Center2, 
                                    team1, team2);

            switchs++;
            Info1->setText(QString("Switch"));
            updateMatchLabel(textScore, matches[3], 650, 470, horloge);
        }
    });

    QLabel *Logo = new QLabel(&window);
    QPixmap pixmap_logo("/home/vivi_z/C++/Projet/Image/logo.png");
    pixmap_logo = pixmap_logo.scaled(100, 100, Qt::KeepAspectRatio);
    Logo->setPixmap(pixmap_logo);
    Logo->move(609, 150);
    Logo->show();

    window.show();

    return app.exec();
}

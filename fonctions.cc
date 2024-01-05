#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QInputDialog>
#include <QLineEdit>
#include <QTableWidget>
#include <QBoxLayout>
#include <QHeaderView>
#include <QMouseEvent>

#include <map>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>

#include "fonctions.hh"
#include "match.hh"
#include "joueur.hh"
#include "clickablelabel.hh"

using namespace std;

// Fonction pour mettre à jour le texte d'un QLabel avec les données d'un joueur
void updatePlayerLabel(QLabel *label, joueur* player, int x, int y)
{
    label->setText(QString("Name: %1 %2\nOVR: %3\nPosition: %4\nTeam: %5\nATQ: %6\nDEF: %7\nVIT: %8\nPoint: %9")
                       .arg(player->getPrenom().c_str())
                       .arg(player->getNom().c_str())
                       .arg(player->getOVR())
                       .arg(player->getPosition().c_str())
                       .arg(player->getTeam().c_str())
                       .arg(player->getATQ())
                       .arg(player->getDEF())
                       .arg(player->getVIT())
                       .arg(player->getPoint()));
    label->move(x, y);
    label->show();
}

// Fonction pour mettre à jour le texte d'un QLabel avec les données d'un match
void updateMatchLabel(QLabel *label, const match &currentMatch, int x, int y, int horloge)
{
    QString quarter;
    int adjustedHorloge = horloge;
    if(horloge >=0 && horloge < 13){
        quarter = "1st";
    } else if (horloge >= 13 && horloge < 25) {
        quarter = "2nd";
        adjustedHorloge -= 12;
    } else if (horloge >= 25 && horloge < 37) {
        quarter = "3rd";
        adjustedHorloge -= 24;
    } else if (horloge >= 37 && horloge < 49) {
        quarter = "4th";
        adjustedHorloge -= 36;
    } 
    label->setText(QString("%1 %2:00\n%3 %4 - %5 %6")
                .arg(quarter)
                .arg(adjustedHorloge)
                .arg(currentMatch.getEquipe1().c_str())
                .arg(currentMatch.getScore1())
                .arg(currentMatch.getEquipe2().c_str())
                .arg(currentMatch.getScore2()));
    label->move(x, y);
    label->setAlignment(Qt::AlignCenter); // Centrer le texte dans le label
    label->show();
}

// Fonction pour mettre à jour l'image d'un QLabel avec l'image d'un joueur
void updatePlayerImageLabel(QLabel* label, joueur* player, int posX, int posY, int size) {
    QPixmap pixmap(player->getImagePath().c_str());
    pixmap = pixmap.scaled(size, size, Qt::KeepAspectRatio);
    label->setPixmap(pixmap);
    label->move(posX, posY);
    label->show();
}

// Fonction qui retourne le joueur avec le plus de points marqués
joueur* getMVP(map<int, joueur*> players){
    joueur* mvp = players[1];
    for (int i = 1; i <= players.size(); ++i) {
        if(players[i]->getPoint() > mvp->getPoint()){
            mvp = players[i];
        }
    }
    return mvp;
}

// Fonction pour trier les joueurs par OVR de manière décroissante
bool compareOvr(const std::pair<int, joueur*>& a, const std::pair<int, joueur*>& b) {
    return a.second->getOVR() > b.second->getOVR();
}

// Fonction pour mettre à jour les images des joueurs de chaque équipe
void updatePlayerImageLabelAll(QLabel* PointGuard1, QLabel* ShootingGuard1, QLabel* SmallForward1, QLabel* PowardForward1, QLabel* Center1, 
                                QLabel* PointGuard2, QLabel* ShootingGuard2, QLabel* SmallForward2, QLabel* PowardForward2, QLabel* Center2, 
                                map<int, joueur*> team1, map<int, joueur*> team2) {

    updatePlayerImageLabel(PointGuard1, team1[1], 10, 10, 400);
    updatePlayerImageLabel(ShootingGuard1, team1[2], 10, 410, 120);
    updatePlayerImageLabel(SmallForward1, team1[3], 95, 410, 120);
    updatePlayerImageLabel(PowardForward1, team1[4], 180, 410, 120);
    updatePlayerImageLabel(Center1, team1[5], 265, 410, 120);

    updatePlayerImageLabel(PointGuard2, team2[1], 1206, 10, 400);
    updatePlayerImageLabel(ShootingGuard2, team2[2], 1150, 410, 120);
    updatePlayerImageLabel(SmallForward2, team2[3], 1235, 410, 120);
    updatePlayerImageLabel(PowardForward2, team2[4], 1320, 410, 120);
    updatePlayerImageLabel(Center2, team2[5], 1405, 410, 120);
}

// Fonction pour mettre à jour les équipes en fonction de l'OVR des joueurs
void updateTeams(map<int, joueur*>& team1, map<int, joueur*>& team2) {
    // Transfert des paires clé-valeur dans un vector
    vector<pair<int, joueur*>> joueurVector1(team1.begin(), team1.end());
    vector<pair<int, joueur*>> joueurVector2(team2.begin(), team2.end());
    
    // Tri du vector en utilisant la fonction de comparaison compareOvr
    sort(joueurVector1.begin(), joueurVector1.end(), compareOvr);
    sort(joueurVector2.begin(), joueurVector2.end(), compareOvr);

    // Mise à jour de la map à partir du vector trié
    team1.clear(); // Effacer la map d'origine
    team2.clear();

    for (int i = 0; i < joueurVector1.size(); ++i) {
        team1[i + 1] = joueurVector1[i].second; // Ajouter les joueurs triés à la map
    }
    for(int i = 0; i < joueurVector2.size(); ++i) {
        team2[i + 1] = joueurVector2[i].second;
    }
}

int endGame(QLabel* Info, map<int, joueur*> team1, map<int, joueur*> team2, map<int, match> matches, int horloge, int start, joueur* mvp){
    if(horloge>=48){
        if(matches[3].getScore1() > matches[3].getScore2()){
            for (int i = 1; i <= 5; ++i) {
                cout << team1[i]->getPrenom() << " " << team1[i]->getNom() << " a marqué " << team1[i]->getPoint() << " points" << endl;
            }
            mvp = getMVP(team1);
            Info->setText(QString("Match terminé\n%1 gagne\n%2 %3 est le MVP du match avec %4 points")
                            .arg(matches[3].getEquipe1().c_str())
                            .arg(mvp->getPrenom().c_str())
                            .arg(mvp->getNom().c_str())
                            .arg(mvp->getPoint()));
        } else if(matches[3].getScore1() < matches[3].getScore2()){
            for (int i = 1; i <= 5; ++i) {
                cout << team2[i]->getPrenom() << " " << team2[i]->getNom() << " a marqué " << team2[i]->getPoint() << " points" << endl;
            }
            mvp = getMVP(team2);
            Info->setText(QString("Match terminé\n%1 gagne\n%2 %3 est le MVP du match avec %4 points")
                            .arg(matches[3].getEquipe2().c_str())
                            .arg(mvp->getPrenom().c_str())
                            .arg(mvp->getNom().c_str())
                            .arg(mvp->getPoint()));
        } else {
            Info->setText(QString("Match terminé\nMatch nul"));
        }
    start = 0;
    }
    return start;
}

void hideAfterDelay(QLabel *label) {
    // Attendre pendant 10 secondes
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Cacher le QLabel
    label->hide();
}

int Quizz(vector<Question> questions){
    QMessageBox msgBox;
    msgBox.setText(questions[0].questionText.c_str());
    msgBox.setWindowTitle("Money In The Bank");
    
    // Ajouter des boutons personnalisés
    QPushButton *buttonYes = msgBox.addButton(QString(questions[0].options[0].c_str()), QMessageBox::YesRole);
    QPushButton *buttonNo = msgBox.addButton(QString(questions[0].options[1].c_str()), QMessageBox::NoRole);
    QPushButton *buttonMaybe = msgBox.addButton(QString(questions[0].options[2].c_str()), QMessageBox::NoRole);
    
    msgBox.exec();

    // Récupérer l'index du bouton cliqué
    QAbstractButton *clickedButton = msgBox.clickedButton();
    int userAnswerIndex = -1;
    if (clickedButton == buttonYes) {
        userAnswerIndex = 0;
    } else if (clickedButton == buttonNo) {
        userAnswerIndex = 1;
    } else if (clickedButton == buttonMaybe) {
        userAnswerIndex = 2;
    }
    return userAnswerIndex;
}

void RandomUpdateTeams(map<int, joueur*>& team1, map<int, joueur*>& team2) {
    // Transfert des paires clé-valeur dans un vector
    vector<pair<int, joueur*>> joueurVector1(team1.begin(), team1.end());
    vector<pair<int, joueur*>> joueurVector2(team2.begin(), team2.end());
    
    random_shuffle(joueurVector1.begin(), joueurVector1.end());
    random_shuffle(joueurVector2.begin(), joueurVector2.end());

    // Mise à jour de la map à partir du vector trié
    team1.clear(); // Effacer la map d'origine
    team2.clear();

    for (int i = 0; i < joueurVector1.size(); ++i) {
        team1[i + 1] = joueurVector1[i].second; // Ajouter les joueurs triés à la map
    }
    for(int i = 0; i < joueurVector2.size(); ++i) {
        team2[i + 1] = joueurVector2[i].second;
    }
}

void hideAfterDelay2(QWidget *window) {
    this_thread::sleep_for(chrono::seconds(5));
    window->close();
}

int ClickTheBall(map<int, joueur*> team1, map<int, match> matches){
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

    thread(hideAfterDelay2, gameWindow).detach();

    // Afficher la fenêtre
    gameWindow->show();
    return Ball->score;
}
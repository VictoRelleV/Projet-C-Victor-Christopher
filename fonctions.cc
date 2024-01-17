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

// Fonction pour mettre à jour le texte d'un QLabel avec les données d'un joueur
void updatePlayerTextLabel(QLabel* label, joueur* player, int posX, int posY) {
    label->setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
    label->setFixedSize(180, 40);
    label->setText(QString("%1 %2\nATQ: %3 DEF: %4 VIT: %5")
                            .arg(player->getPrenom().c_str())
                            .arg(player->getNom().c_str())
                            .arg(player->getATQ())
                            .arg(player->getDEF())
                            .arg(player->getVIT()));
    label->setAlignment(Qt::AlignCenter); // Centrer le texte
    label->move(posX, posY);
    label->show();
}

// Fonction pour mettre à jour le texte des QLabel avec les données d'un joueur
void updatePlayerTextLabelAll(QLabel* PointGuard1Text, QLabel* ShootingGuard1Text, QLabel* SmallForwardText, QLabel* PowardForward1Text, QLabel* Center1Text,
                                map<int, joueur*> team1) {

    updatePlayerTextLabel(PointGuard1Text, team1[1], 540, 535);
    updatePlayerTextLabel(ShootingGuard1Text, team1[2], 340, 636);
    updatePlayerTextLabel(SmallForwardText, team1[3], 340, 346);
    updatePlayerTextLabel(PowardForward1Text, team1[4], 140, 676);
    updatePlayerTextLabel(Center1Text, team1[5], 140, 386);
}

// Fonction pour mettre à jour les images des joueurs de chaque équipe
void updatePlayerImageLabelAll(QLabel* PointGuard1, QLabel* ShootingGuard1, QLabel* SmallForward1, QLabel* PowardForward1, QLabel* Center1, 
                                QLabel* PointGuard2, QLabel* ShootingGuard2, QLabel* SmallForward2, QLabel* PowardForward2, QLabel* Center2, 
                                map<int, joueur*> team1, map<int, joueur*> team2) {

    updatePlayerImageLabel(PointGuard1, team1[1], 550, 309, 226);
    updatePlayerImageLabel(ShootingGuard1, team1[2], 350, 410, 226);
    updatePlayerImageLabel(SmallForward1, team1[3], 350, 120, 226);
    updatePlayerImageLabel(PowardForward1, team1[4], 150, 450, 226);
    updatePlayerImageLabel(Center1, team1[5], 150, 160, 226);

    updatePlayerImageLabel(PointGuard2, team2[1], 790, 309, 226);
    updatePlayerImageLabel(ShootingGuard2, team2[2], 990, 410, 226);
    updatePlayerImageLabel(SmallForward2, team2[3], 990, 120, 226);
    updatePlayerImageLabel(PowardForward2, team2[4], 1190, 450, 226);
    updatePlayerImageLabel(Center2, team2[5], 1190, 160, 226);
}


// Fonction pour mettre à jour les équipes en fonction de l'OVR des joueurs
void updateTeams(map<int, joueur*>& team1, map<int, joueur*>& team2) {
    // Transfert des paires clé-valeur dans un vector
    vector<pair<int, joueur*>> joueurVector1(team1.begin(), team1.end());
    vector<pair<int, joueur*>> joueurVector2(team2.begin(), team2.end());
    
    // Tri du vector en utilisant la fonction de comparaison compareOvr
    //sort(joueurVector1.begin(), joueurVector1.end(), compareOvr);
    //sort(joueurVector2.begin(), joueurVector2.end(), compareOvr);

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
                cout << team1[i]->getPrenom() << " " << team1[i]->getNom() << " a marqué " << endl;
            }
            //mvp = getMVP(team1);
            mvp = team1[1];
            Info->setText(QString("Match terminé\n%1 gagne\n%2 %3 est le MVP du match avec points")
                            .arg(matches[3].getEquipe1().c_str())
                            .arg(mvp->getPrenom().c_str())
                            .arg(mvp->getNom().c_str()));
        } else if(matches[3].getScore1() < matches[3].getScore2()){
            for (int i = 1; i <= 5; ++i) {
                cout << team2[i]->getPrenom() << " " << team2[i]->getNom() << " a marqué " << endl;
            }
            //mvp = getMVP(team2);
            mvp = team2[1];
            Info->setText(QString("Match terminé\n%1 gagne\n%2 %3 est le MVP du match avec points")
                            .arg(matches[3].getEquipe2().c_str())
                            .arg(mvp->getPrenom().c_str())
                            .arg(mvp->getNom().c_str()));
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
    msgBox.setWindowTitle("Quizz");
    
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

int askQuestion(QLabel* Info1, joueur* player, map<int, match> matches, vector<Question> questions){
    random_shuffle(questions.begin(), questions.end());
    int userAnswerIndex = Quizz(questions);
    int answer = 0;

    // Traiter la réponse en fonction du bouton cliqué
    if (userAnswerIndex != -1) {
        if (userAnswerIndex == questions[0].correctOptionIndex) {
            //Shaq1->show();
            Info1->setText(QString("Bonne réponse\n%1 %2 marque 3 points")
                            .arg(player->getPrenom().c_str())
                            .arg(player->getNom().c_str()));
            //thread(hideAfterDelay, Shaq1).detach();
            answer = 1;
        } else {
            //Shaq2->show();
            Info1->setText(QString("Mauvaise réponse"));
            //thread(hideAfterDelay, Shaq2).detach();
        }
    }
    return answer;
}
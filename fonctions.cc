#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QBoxLayout>
#include <QHeaderView>

#include <map>
#include <random>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>

#include "fonctions.hh"
#include "match.hh"
#include "joueur.hh"

using namespace std;

// Fonction pour mettre à jour le texte d'un QLabel avec les données d'un match
void updateMatchLabel(QLabel &label, match* currentMatch, int x, int y, int horloge)
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
    label.setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
    label.setFixedSize(200, 100);
    label.setText(QString("%1 %2:00\n%3 %4 - %5 %6")
                .arg(quarter)
                .arg(adjustedHorloge)
                .arg(currentMatch->getEquipe1().c_str())
                .arg(currentMatch->getScore1())
                .arg(currentMatch->getEquipe2().c_str())
                .arg(currentMatch->getScore2()));
    label.move(x, y);
    label.setAlignment(Qt::AlignCenter); // Centrer le texte dans le label
    label.show();
}

// Fonction pour mettre à jour l'image d'un QLabel avec l'image d'un joueur
void updatePlayerImageLabel(QLabel& label, joueur* player, int posX, int posY, int size) {
    QPixmap pixmap(player->getImagePath().c_str());
    pixmap = pixmap.scaled(size, size, Qt::KeepAspectRatio);
    label.setPixmap(pixmap);
    label.move(posX, posY);
    label.show();
}

QString getPositionLabel(joueur* player) {
    QString positionLabel;
    if (player->getPosition() == "Point Guard") {
        positionLabel = "[PG]";
    } else if (player->getPosition() == "Shooting Guard") {
        positionLabel = "[SG]";
    } else if (player->getPosition() == "Small Forward") {
        positionLabel = "[SF]";
    } else if (player->getPosition() == "Power Forward") {
        positionLabel = "[PF]";
    } else if (player->getPosition() == "Center") {
        positionLabel = "[C]";
    } else {
        positionLabel = "[N/A]";  // Une valeur par défaut si la position n'est pas reconnue
    }
    return positionLabel;
}

// Fonction pour mettre à jour le texte d'un QLabel avec les données d'un joueur
void updatePlayerTextLabel(QLabel& label, joueur* player, int posX, int posY) {
    QString positionLabel = getPositionLabel(player);

    label.setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
    label.setFixedSize(180, 40);
    label.setText(QString("%1 %2 %3\nATQ: %4 DEF: %5 VIT: %6")
                            .arg(player->getPrenom().c_str())
                            .arg(player->getNom().c_str())
                            .arg(positionLabel)
                            .arg(player->getATQ())
                            .arg(player->getDEF())
                            .arg(player->getVIT()));
    label.setAlignment(Qt::AlignCenter); // Centrer le texte
    label.move(posX, posY);
    label.show();
}

// Fonction pour mettre à jour le texte d'un QLabel avec les données d'un joueur
void updatePlayerTextLabel2(QLabel& label, joueur* player, int posX, int posY, int reveal) {
    QString positionLabel = getPositionLabel(player);
    label.setStyleSheet("border: 2px solid black;"); // You can adjust the border size and color
    label.setFixedSize(180, 40);
    if(reveal==0){
        label.setText(QString("%1 %2 %3\nATQ: XX DEF: XX VIT: XX")
                                .arg(player->getPrenom().c_str())
                                .arg(player->getNom().c_str())
                                .arg(positionLabel));
    } else {
        label.setText(QString("%1 %2 %3\nATQ: %4 DEF: %5 VIT: %6")
                                .arg(player->getPrenom().c_str())
                                .arg(player->getNom().c_str())
                                .arg(positionLabel)
                                .arg(player->getATQ())
                                .arg(player->getDEF())
                                .arg(player->getVIT()));
    }
    label.setAlignment(Qt::AlignCenter); // Centrer le texte
    label.move(posX, posY);
    label.show();
}

// Fonction pour mettre à jour le texte des QLabel avec les données d'un joueur
void updatePlayerTextLabelAll(QLabel& PointGuard1Text, QLabel& ShootingGuard1Text, QLabel& SmallForwardText, QLabel& PowardForward1Text, QLabel& Center1Text,
                              QLabel& PointGuard2Text, QLabel& ShootingGuard2Text, QLabel& SmallForward2Text, QLabel& PowardForward2Text, QLabel& Center2Text,
                              map<int, joueur*> team1, map<int, joueur*> team2, vector<int> indicePick) {

    updatePlayerTextLabel(PointGuard1Text, team1[1], 540, 535);
    updatePlayerTextLabel(ShootingGuard1Text, team1[2], 340, 636);
    updatePlayerTextLabel(SmallForwardText, team1[3], 340, 346);
    updatePlayerTextLabel(PowardForward1Text, team1[4], 140, 676);
    updatePlayerTextLabel(Center1Text, team1[5], 140, 386);

    updatePlayerTextLabel2(PointGuard2Text, team2[1], 780, 535, indicePick[0]);
    updatePlayerTextLabel2(ShootingGuard2Text, team2[2], 980, 636, indicePick[1]);
    updatePlayerTextLabel2(SmallForward2Text, team2[3], 980, 346, indicePick[2]);
    updatePlayerTextLabel2(PowardForward2Text, team2[4], 1180, 676, indicePick[3]);
    updatePlayerTextLabel2(Center2Text, team2[5], 1180, 386, indicePick[4]);
}

// Fonction pour mettre à jour les images des joueurs de chaque équipe
void updatePlayerImageLabelAll(QLabel& PointGuard1, QLabel& ShootingGuard1, QLabel& SmallForward1, QLabel& PowardForward1, QLabel& Center1,
                                QLabel& PointGuard2, QLabel& ShootingGuard2, QLabel& SmallForward2, QLabel& PowardForward2, QLabel& Center2,
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

int endGame(QLabel& Info, map<int, joueur*> team1, map<int, joueur*> team2, map<int, match*> matches, int horloge, int start, joueur* mvp){
    if(start == 1 && horloge >= 12) {
        if(matches[3]->getScore1() > matches[3]->getScore2()) {
            for (int i = 1; i <= 5; ++i) {
                cout << *team1[i] << endl;
            }
            mvp = getMVP(team1);
            Info.setText(QString("%1 wins\n%2 %3 is the MVP with %4 points")
                            .arg(matches[3]->getEquipe1().c_str())
                            .arg(mvp->getPrenom().c_str())
                            .arg(mvp->getNom().c_str())
                            .arg(mvp->getPoints()));
        } else if(matches[3]->getScore1() < matches[3]->getScore2()) {
            for (int i = 1; i <= 5; ++i) {
                cout << *team2[i] << endl;
            }
            mvp = getMVP(team2);
            Info.setText(QString("%1 wins\n%2 %3 is the MVP with %4 points")
                            .arg(matches[3]->getEquipe2().c_str())
                            .arg(mvp->getPrenom().c_str())
                            .arg(mvp->getNom().c_str())
                            .arg(mvp->getPoints()));
        } else {
            Info.setText(QString("Draw"));
        }
    start = 0;
    }
    return start;
}

void hideAfterDelay(QLabel& label) {
    // Attendre pendant 10 secondes
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Cacher le QLabel
    label.hide();
}

void askQuestion(QLabel& Info1, joueur* player, map<int, match*> matches, vector<Question> questions){
    shuffle(questions.begin(), questions.end(), std::mt19937(std::random_device()()));
    int userAnswerIndex = Quizz(questions);

    // Traiter la réponse en fonction du bouton cliqué
    if (userAnswerIndex != -1) {
        if (userAnswerIndex == questions[0].correctOptionIndex) {
            Info1.setText(QString("Good answer\n%1 %2 scores 3 points")
                            .arg(player->getPrenom().c_str())
                            .arg(player->getNom().c_str()));
            player->setPoints(player->getPoints() + 3);
            matches[3]->setScore1(matches[3]->getScore1() + 3);
            player->addSTAT(-3);

        } else {
            Info1.setText(QString("Wrong answer"));
            player->addSTAT(-10);
        }
    }
}

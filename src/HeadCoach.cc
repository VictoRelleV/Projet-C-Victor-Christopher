#include <QPushButton>
#include <QMessageBox>

#include "../include/HeadCoach.hh"

vector<int> HeadCoach::scoutingReport(int horloge, int nbrChoix, map<int, Match *> matches, map<int, Joueur *> team2, QLabel &Info) {
    // Utilise l'horloge pour initialiser le générateur de nombres aléatoires
    std::random_device rd;
    std::mt19937 gen(rd());
    // Génère un nombre aléatoire entre 0 et 4
    uniform_int_distribution<> distribution5(0, 4);

    vector<int> indices(5, 0);
    int cout = nbrChoix * (12-horloge);
    team2[1]->setPoints(team2[1]->getPoints() + cout);
    matches[3]->setScore2(matches[3]->getScore2() + cout);
    Info.setText(QString::fromStdString(team2[1]->getPrenom() + " " + team2[1]->getNom() + " scored " + to_string(cout) + " points!"));
    for (int i = 0; i < nbrChoix; ++i) {
        int nouvelIndice;
        do {
            nouvelIndice = distribution5(gen);
        } while (indices[nouvelIndice] == 1); {
            indices[nouvelIndice] = 1;
        }
    }
    return indices;
}

int Draft(){
    QMessageBox msgBox;
    msgBox.setText("Draft");
    msgBox.setWindowTitle("Draft");
    
    // Ajouter des boutons personnalisés
    QPushButton *buttonYes = msgBox.addButton(QString("1"), QMessageBox::YesRole);
    QPushButton *buttonNo = msgBox.addButton(QString("2"), QMessageBox::NoRole);
    QPushButton *buttonMaybe = msgBox.addButton(QString("3"), QMessageBox::NoRole);
    QPushButton *buttonMaybe2 = msgBox.addButton(QString("4"), QMessageBox::NoRole);
    QPushButton *buttonMaybe3 = msgBox.addButton(QString("5"), QMessageBox::NoRole);
    
    msgBox.exec();

    // Récupérer l'index du bouton cliqué
    QAbstractButton *clickedButton = msgBox.clickedButton();
    int nbrChoix = -1;
    if (clickedButton == buttonYes) {
        nbrChoix = 1;
    } else if (clickedButton == buttonNo) {
        nbrChoix = 2;
    } else if (clickedButton == buttonMaybe) {
        nbrChoix = 3;
    } else if (clickedButton == buttonMaybe2) {
        nbrChoix = 4;
    } else if (clickedButton == buttonMaybe3) {
        nbrChoix = 5;
    }
    return nbrChoix;
}
#include <QPushButton>
#include <QMessageBox>

#include "headcoach.hh"

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





#include <QPushButton>
#include <QMessageBox>

#include <map>
#include <string>
#include <vector>
#include <random>

#include "../include/question.hh"

using namespace std;

vector<Question> questions = {
    {"Quel pays a accueilli les Jeux Olympiques d'hiver en 2018 ?", {"Canada", "Corée du Sud", "Norvège"}, 1},
    {"Dans quel sport les Jeux Olympiques de la jeunesse comprennent-ils l'épreuve de trampoline ?", {"Gymnastique artistique", "Athlétisme", "Natation synchronisée"}, 0},
    {"Quel athlète a allumé la flamme olympique lors des Jeux de 1996 à Atlanta ?", {"Muhammad Ali", "Michael Jordan", "Carl Lewis"}, 0},
    {"Quelle est la devise olympique ?", {"Faster, Higher, Stronger", "Unity in Diversity", "Peace and Friendship"}, 0},
    {"En quelle année les premiers Jeux Olympiques modernes ont-ils eu lieu ?", {"1896", "1900", "1920"}, 0},
    {"Quelle ville a accueilli les Jeux Olympiques d'été en 2016 ?", {"Rio de Janeiro", "Londres", "Tokyo"}, 0},
    {"Dans quelle discipline les concurrents portent-ils des masques et utilisent-ils des armes ?", {"Tir à l'arc", "Escrime", "Boxe"}, 1},
    {"Quel pays a remporté le plus grand nombre de médailles d'or aux Jeux Olympiques de 2012 ?", {"Chine", "Etats-Unis", "Russie"}, 1},
    {"Combien de fois Usain Bolt a-t-il remporté la médaille d'or olympique sur 100 mètres ?", {"Trois fois", "Quatre fois", "Cinq fois"}, 1},
    {"Quelle nation a remporté le plus grand nombre de médailles aux Jeux Olympiques d'hiver de 2018 ?", {"Norvège", "Allemagne", "Canada"}, 1},
    {"En quelle année les Jeux Olympiques d'été ont-ils été annulés en raison de la Seconde Guerre mondiale ?", {"1940", "1944", "1948"}, 0},
    {"Quel est le plus grand stade utilisé pour les Jeux Olympiques de 2008 ?", {"Stade olympique national de Pékin", "Stade de Wembley à Londres", "Stade olympique de Berlin"}, 0},
    {"Quelle est la durée standard des Jeux Olympiques, en jours ?", {"12 jours", "16 jours", "20 jours"}, 1},
    {"Quelle discipline a été ajoutée aux Jeux Olympiques d'été pour la première fois en 2020 ?", {"Skateboard", "Curling", "Surf"}, 0},
    {"Quel athlète détient le record du monde du saut en hauteur aux Jeux Olympiques ?", {"Javier Sotomayor", "Stefan Holm", "Mutaz Essa Barshim"}, 0},
    {"Combien de médailles d'or Michael Phelps a-t-il remportées aux Jeux Olympiques de 2008 ?", {"Huit", "Dix", "Douze"}, 0},
    {"Quel pays a remporté le plus grand nombre de médailles d'or aux Jeux Olympiques de 2016 ?", {"Etats-Unis", "Chine", "Russie"}, 1},
    {"Quelle est la couleur du drapeau olympique ?", {"Bleu, jaune, noir", "Bleu, jaune, rouge", "Bleu, jaune, vert"}, 0},
    {"En quelle année les Jeux Olympiques d'hiver ont-ils été organisés pour la première fois ?", {"1924", "1932", "1940"}, 0},
    {"Quel est le symbole des Jeux Paralympiques ?", {"Les anneaux paralympiques", "Le flambeau", "La flamme"}, 0},
    {"Quel est le seul pays à avoir participé à tous les Jeux Olympiques d'été depuis leur création ?", {"Grèce", "Royaume-Uni", "France"}, 0},
    {"Dans quelle ville se sont déroulés les premiers Jeux Olympiques de la jeunesse en 2010 ?", {"Singapour", "Nanjing", "Innsbruck"}, 0},
    {"Quelle discipline a été ajoutée aux Jeux Olympiques d'hiver en 1998 ?", {"Curling", "Snowboard", "Patinage artistique synchronisé"}, 1},
    {"Qui est le seul athlète à avoir remporté des médailles d'or aux Jeux Olympiques d'hiver et d'été ?", {"Eddie Eagan", "Michael Phelps", "Usain Bolt"}, 0},
    {"En quelle année les premiers Jeux Olympiques spéciaux ont-ils eu lieu ?", {"1968", "1976", "1988"}, 2},
    {"Quel pays a accueilli les Jeux Olympiques d'été en 2000 ?", {"Australie", "Grèce", "Chine"}, 0},
    {"Combien de fois le Japon a-t-il accueilli les Jeux Olympiques d'été ?", {"Deux fois", "Trois fois", "Quatre fois"}, 1},
    {"Quelle est la plus grande île du Japon, où se sont déroulés les Jeux Olympiques d'hiver de 1972 ?", {"Hokkaido", "Honshu", "Kyushu"}, 0},
    {"Quelle nation a remporté le plus grand nombre de médailles aux Jeux Olympiques d'été de 1900 ?", {"France", "Etats-Unis", "Royaume-Uni"}, 0}
};

vector<Question> createQuestions() {
    return questions;
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

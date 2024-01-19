#include <QLabel>

#include <map>
#include <string>
#include <vector>
#include <random>

#include "joueur.hh"
#include "center.hh"
#include "powerforward.hh"
#include "smallforward.hh"
#include "shootingguard.hh"
#include "pointguard.hh"

using namespace std;

// List of player details (nom, prenom, position, imagePath)
vector<tuple<string, string, string, string, int, int , int>> playerDetails = {
    {"Butler", "Jimmy", "Small Forward", "/home/vivi_z/C++/Projet/Image/jimmy-butler.png", 93, 99, 92},
    {"Bryant", "Kobe", "Shooting Guard", "/home/vivi_z/C++/Projet/Image/kobe-bryant.png", 99, 97, 85},
    {"James", "Lebron", "Small Forward", "/home/vivi_z/C++/Projet/Image/lebron-james.png", 97, 97, 96},
    {"Jordan", "Michael", "Shooting Guard", "/home/vivi_z/C++/Projet/Image/michael-jordan.png", 97, 94, 95},
    {"O'Neal", "Shaquille", "Center", "/home/vivi_z/C++/Projet/Image/shaquille-o-neal.png", 94, 99, 87},
    {"Durant", "Kevin", "Small Forward", "/home/vivi_z/C++/Projet/Image/kevin-durant.png", 98, 89, 90},
    {"Irving", "Kyrie", "Point Guard", "/home/vivi_z/C++/Projet/Image/kyrie-irving.png", 97, 85, 93},
    {"Thompson", "Klay", "Shooting Guard", "/home/vivi_z/C++/Projet/Image/klay-thompson.png", 92, 89, 78},
    {"Curry", "Stephen", "Point Guard", "/home/vivi_z/C++/Projet/Image/stephen-curry.png", 99, 99, 99},
    {"Iverson", "Allen", "Point Guard", "/home/vivi_z/C++/Projet/Image/allen-iverson.png", 96, 93, 98}
    };

map<int, joueur*> createPlayers()
{
    map<int, joueur*> players;

    for (int i = 1; i <= playerDetails.size(); ++i)
    {
        const auto& [nom, prenom, position, imagePath, ATQ, DEF, VIT] = playerDetails[i - 1];
        std::string positionValue = std::get<2>(playerDetails[i - 1]);

        if(positionValue == "Center"){
            players[i] = new center(nom, prenom, position, imagePath, ATQ, DEF, VIT);
        } else if(positionValue == "Small Forward"){
            players[i] = new smallforward(nom, prenom, position, imagePath, ATQ, DEF, VIT);
        } else if(positionValue == "Shooting Guard"){
            players[i] = new shootingguard(nom, prenom, position, imagePath, ATQ, DEF, VIT);
        } else if(positionValue == "Power Forward"){
            players[i] = new powerforward(nom, prenom, position, imagePath, ATQ, DEF, VIT);
        } else if(positionValue == "Point Guard"){
            players[i] = new pointguard(nom, prenom, position, imagePath, ATQ, DEF, VIT);
        } else {
            players[i] = new joueur(nom, prenom, position, imagePath, ATQ, DEF, VIT);
            cout << "Erreur: position invalide" << endl;
        }
    }
    return players;
}

pair<map<int, joueur*>, map<int, joueur*>> createTeams(map<int, joueur*> players) {
    map<int, joueur*> team1;
    map<int, joueur*> team2;
    int nextkey1 = 1;
    int nextkey2 = 1;

    for(int i = 1; i <= players.size(); ++i) {

        // Utilise l'horloge pour initialiser le générateur de nombres aléatoires
        std::random_device rd;
        std::mt19937 gen(rd());

        // Génère un nombre aléatoire entre 1 et 100
        std::uniform_int_distribution<> distribution(1, 100);
        int randomValue = distribution(gen);

        if ((randomValue % 2 == 0) && (nextkey1 < 5)) {
            team1[nextkey1] = players[i];
            nextkey1++;
        } else if ((randomValue % 2 != 0) && (nextkey2 < 5)){
            team2[nextkey2] = players[i];
            nextkey2++;
        } else if (nextkey1 <= 5) {
            team1[nextkey1] = players[i];
            nextkey1++;
        } else if (nextkey2 <= 5){
            team2[nextkey2] = players[i];
            nextkey2++;
        }
    }
    return make_pair(team1, team2);
}

joueur* choisirJoueurAuHasard(map<int, joueur*>& equipe) {
    // Vérifier si l'équipe n'est pas vide
    if (equipe.empty()) {
        std::cerr << "L'équipe est vide." << std::endl;
        return nullptr;
    }

    // Initialiser un générateur de nombres aléatoires
    std::random_device rd;
    std::mt19937 gen(rd());

    // Générer une position aléatoire dans la map
    std::uniform_int_distribution<> distrib(0, equipe.size() - 1);
    auto it = std::next(equipe.begin(), distrib(gen));

    // Récupérer le joueur à la position aléatoire
    return it->second;
}
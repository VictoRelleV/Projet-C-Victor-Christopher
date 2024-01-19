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
    {"Butler", "Jimmy", "Small Forward", "./Image/jimmy-butler.png", 93, 99, 92},
    {"Bryant", "Kobe", "Shooting Guard", "./Image/kobe-bryant.png", 99, 97, 85},
    {"James", "Lebron", "Small Forward", "./Image/lebron-james.png", 97, 97, 96},
    {"Jordan", "Michael", "Shooting Guard", "./Image/michael-jordan.png", 97, 94, 95},
    {"O'Neal", "Shaquille", "Center", "./Image/shaquille-o-neal.png", 94, 99, 87},
    {"Durant", "Kevin", "Small Forward", "./Image/kevin-durant.png", 98, 89, 90},
    {"Irving", "Kyrie", "Point Guard", "./Image/kyrie-irving.png", 97, 85, 93},
    {"Thompson", "Klay", "Shooting Guard", "./Image/klay-thompson.png", 92, 89, 78},
    {"Curry", "Stephen", "Point Guard", "./Image/stephen-curry.png", 99, 99, 99},
    {"Iverson", "Allen", "Point Guard", "./Image/allen-iverson.png", 96, 93, 98},
    {"Rose", "Derrick", "Point Guard", "./Image/derrick_rose.png", 99, 96, 98},
    {"Pippen", "Scottie", "Small Forward", "./Image/scottie_pippen.png", 90, 99, 95},
    {"Gobert", "Rudy", "Center", "./Image/rudy_gobert.png", 88, 99, 81},
    {"Dončić", "Luka", "Point Guard", "./Image/luka_doncic.png", 99, 87, 90},
    {"Malone", "Karl", "Power Forward", "./Image/karl_malone.png", 94, 99, 95},
    {"Stockton", "John", "Point Guard", "./Image/john_stockton.png", 92, 99, 95},
    {"Brown", "Jaylen", "Shooting Guard", "./Image/jaylen_brown.png", 94, 94, 92},
    {"Russell", "D'Angelo", "Point Guard", "./Image/d_angelo_russell.png", 99, 85, 91},
    {"Adebayo", "Bam", "Center", "./Image/bam_adebayo.png", 91, 99, 92}
    };

map<int, joueur*> createPlayers()
{
    map<int, joueur*> players;
    random_shuffle(playerDetails.begin(), playerDetails.end());

    for (int i = 1; i <= 10; ++i)
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

    for(int i = 1; i <= 10; ++i) {

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
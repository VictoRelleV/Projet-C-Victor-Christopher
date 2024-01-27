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
    {"Irving", "Kyrie", "Point Guard", "./Image/kyrie-irving.png", 97, 85, 93},
    {"Curry", "Stephen", "Point Guard", "./Image/stephen-curry.png", 99, 99, 99},
    {"Iverson", "Allen", "Point Guard", "./Image/allen-iverson.png", 96, 93, 98},
    {"Rose", "Derrick", "Point Guard", "./Image/derrick_rose.png", 99, 96, 98},
    {"Dončić", "Luka", "Point Guard", "./Image/luka_doncic.png", 99, 87, 90},
    {"Stockton", "John", "Point Guard", "./Image/john_stockton.png", 92, 99, 95},
    {"Russell", "D'Angelo", "Point Guard", "./Image/d_angelo_russell.png", 99, 85, 91},
    {"Parker", "Tony", "Point Guard", "./Image/tony_parker.png", 98, 95, 98},
    {"Gilgeous-Alexander", "Shai", "Point Guard", "./Image/shai_gilgeous-alexander.png", 96, 88, 86},
    {"Murray", "Jamal", "Point Guard", "./Image/jamal_murray.png", 98, 93, 94},

    {"Bryant", "Kobe", "Shooting Guard", "./Image/kobe-bryant.png", 99, 97, 85},
    {"Jordan", "Michael", "Shooting Guard", "./Image/michael-jordan.png", 97, 94, 95},
    {"Thompson", "Klay", "Shooting Guard", "./Image/klay-thompson.png", 92, 89, 78},
    {"Brown", "Jaylen", "Shooting Guard", "./Image/jaylen_brown.png", 94, 94, 92},
    {"Harden", "James", "Shooting Guard", "./Image/james_harden.png", 97, 89, 92},
    {"Allen", "Ray", "Shooting Guard", "./Image/ray_allen.png", 97, 93, 90},
    //{"Edwards", "Anthony", "Shooting Guard", "./Image/ray_allen.png", 97, 93, 93},
    //{"Booker", "Devin", "Shooting Guard", "./Image/ray_allen.png", 99, 89, 93},
    //{"Mitchell", "Donovan", "Shooting Guard", "./Image/ray_allen.png", 94, 89, 96},
    //{"Drexler", "Clyde", "Shooting Guard", "./Image/ray_allen.png", 98, 94, 94},
    
    {"Butler", "Jimmy", "Small Forward", "./Image/jimmy-butler.png", 93, 99, 92},
    {"James", "Lebron", "Small Forward", "./Image/lebron-james.png", 97, 97, 96},
    {"Pippen", "Scottie", "Small Forward", "./Image/scottie_pippen.png", 90, 99, 95},
    {"Durant", "Kevin", "Small Forward", "./Image/kevin-durant.png", 98, 89, 90},
    
    {"Duncan", "Tim", "Power Forward", "./Image/tim_duncan.png", 96, 99, 87},
    {"Malone", "Karl", "Power Forward", "./Image/karl_malone.png", 94, 99, 95},
    {"Williamson", "Zion", "Power Forward", "./Image/zion_williamson.png", 93, 85, 85},
    {"Antetokounmpo", "Giannis", "Power Forward", "./Image/giannis_antetokounmpo.png", 97, 99, 95},
    {"Nowitzki", "Dirk", "Power Forward", "./Image/dirk_nowitzki.png", 98, 89, 74},
    {"Bosh", "Chris", "Power Forward", "./Image/chris_bosh.png", 92, 93, 80},
    {"Holmgren", "Chet", "Power Forward", "./Image/chet_holmgren.png", 91, 93, 77},
    {"Towns", "Karl-Anthony", "Power Forward", "./Image/karl-anthony_towns.png", 99, 98, 87},
    {"Garnett", "Kevin", "Power Forward", "./Image/kevin_garnett.png", 93, 99, 90},
    {"Bird", "Larry", "Power Forward", "./Image/larry_bird.png", 99, 99, 90},

    {"Gobert", "Rudy", "Center", "./Image/rudy_gobert.png", 88, 99, 81},
    {"O'Neal", "Shaquille", "Center", "./Image/shaquille-o-neal.png", 94, 99, 87},
    {"Adebayo", "Bam", "Center", "./Image/bam_adebayo.png", 91, 99, 92},
    {"Wembanyama", "Victor", "Center", "./Image/victor_wembanyama.png", 92, 99, 79}
    
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

// Fonction qui retourne le joueur avec le plus de points marqués
joueur* getMVP(map<int, joueur*> players){
    joueur* mvp = players[1];
    for (int i = 1; i <= players.size(); ++i) {
        if(players[i]->getPoints() > mvp->getPoints()){
            mvp = players[i];
        }
    }
    return mvp;
}

std::ostream& operator<<(std::ostream& os, const joueur& joueur) {
    os << joueur._prenom << " " << joueur._nom << " scored " << joueur._points << " points";
    return os;
}
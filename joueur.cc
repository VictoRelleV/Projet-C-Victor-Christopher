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

// List of player details (nom, prenom, OVR, position, team, imagePath)
vector<tuple<string, string, int, string, string, string>> playerDetails = {
    {"Butler", "Jimmy", 95, "Small Forward", "Heat", "/home/vivi_z/C++/Projet/Image/jimmy-butler.png"},
    {"Bryant", "Kobe", 99, "Shooting Guard", "Lakers", "/home/vivi_z/C++/Projet/Image/kobe-bryant.png"},
    {"James", "Lebron", 94, "Small Forward", "Lakers", "/home/vivi_z/C++/Projet/Image/lebron-james.png"},
    {"Jordan", "Michael", 94, "Shooting Guard", "Bulls", "/home/vivi_z/C++/Projet/Image/michael-jordan.png"},
    {"O'Neal", "Shaquille", 94, "Center", "Lakers", "/home/vivi_z/C++/Projet/Image/shaquille-o-neal.png"},
    {"Durant", "Kevin", 94, "Small Forward", "Warriors", "/home/vivi_z/C++/Projet/Image/kevin-durant.png"},
    {"Irving", "Kyrie", 94, "Point Guard", "Cavaliers", "/home/vivi_z/C++/Projet/Image/kyrie-irving.png"},
    {"Thompson", "Klay", 91, "Shooting Guard", "Warriors", "/home/vivi_z/C++/Projet/Image/klay-thompson.png"},
    {"Curry", "Stephen", 99, "Point Guard", "Warriors", "/home/vivi_z/C++/Projet/Image/stephen-curry.png"},
    {"Iverson", "Allen", 94, "Point Guard", "Sixers", "/home/vivi_z/C++/Projet/Image/allen-iverson.png"}
    };

map<int, joueur*> createPlayers()
{
    map<int, joueur*> players;

    for (int i = 1; i <= playerDetails.size(); ++i)
    {
        const auto& [nom, prenom, OVR, position, team, imagePath] = playerDetails[i - 1];
        std::string positionValue = std::get<3>(playerDetails[i - 1]);

        if(positionValue == "Center"){
            players[i] = new center(nom, prenom, OVR, position, team, imagePath);
        } else if(positionValue == "Small Forward"){
            players[i] = new smallforward(nom, prenom, OVR, position, team, imagePath);
        } else if(positionValue == "Shooting Guard"){
            players[i] = new shootingguard(nom, prenom, OVR, position, team, imagePath);
        } else if(positionValue == "Power Forward"){
            players[i] = new powerforward(nom, prenom, OVR, position, team, imagePath);
        } else if(positionValue == "Point Guard"){
            players[i] = new pointguard(nom, prenom, OVR, position, team, imagePath);
        } else {
            players[i] = new joueur(nom, prenom, OVR, position, team, imagePath);
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
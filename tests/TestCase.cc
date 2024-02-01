// Let DocTest provide main():
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../include/HeadCoach.hh"
#include "../include/Center.hh"
#include "../include/PointGuard.hh"
#include "../include/PowerForward.hh"
#include "../include/ShootingGuard.hh"
#include "../include/SmallForward.hh"

TEST_SUITE("Construct classes") {
    TEST_CASE("Construct HeadCoach") {
        HeadCoach hc("Popovich", "Gregg", "Spurs", "images/Popovich.png");
        CHECK((hc.getNom() == "Popovich"));
        CHECK((hc.getPrenom() == "Gregg"));
        CHECK((hc.getFullName() == "Gregg Popovich"));
        CHECK((hc.getEquipe() == "Spurs"));
        CHECK((hc.getImagePath() == "images/Popovich.png"));
    }

    TEST_CASE("Construct Center") {
        Center c("Duncan", "Tim", "Center", "images/Duncan.png", 10, 11, 12);
        CHECK((c.getNom() == "Duncan"));
        CHECK((c.getPrenom() == "Tim"));
        CHECK((c.getPosition() == "Center"));
        CHECK((c.getImagePath() == "images/Duncan.png"));
        CHECK((c.getStatAttaque() == 10));
        CHECK((c.getStatDefense() == 11));
        CHECK((c.getStatVitesse() == 12));
    }

    TEST_CASE("Construct PointGuard") {
        PointGuard pg("Parker", "Tony", "Point Guard", "images/Parker.png", 10, 11, 12);
        CHECK((pg.getNom() == "Parker"));
        CHECK((pg.getPrenom() == "Tony"));
        CHECK((pg.getPosition() == "Point Guard"));
        CHECK((pg.getImagePath() == "images/Parker.png"));
        CHECK((pg.getStatAttaque() == 10));
        CHECK((pg.getStatDefense() == 11));
        CHECK((pg.getStatVitesse() == 12));
    }

    TEST_CASE("Construct PowerForward") {
        PowerForward pf("Garnett", "Kevin", "Power Forward", "images/Garnett.png", 10, 11, 12);
        CHECK((pf.getNom() == "Garnett"));
        CHECK((pf.getPrenom() == "Kevin"));
        CHECK((pf.getPosition() == "Power Forward"));
        CHECK((pf.getImagePath() == "images/Garnett.png"));
        CHECK((pf.getStatAttaque() == 10));
        CHECK((pf.getStatDefense() == 11));
        CHECK((pf.getStatVitesse() == 12));
    }

    TEST_CASE("Construct ShootingGuard") {
        ShootingGuard sg("Ginobili", "Manu", "Shooting Guard", "images/Ginobili.png", 10, 11, 12);
        CHECK((sg.getNom() == "Ginobili"));
        CHECK((sg.getPrenom() == "Manu"));
        CHECK((sg.getPosition() == "Shooting Guard"));
        CHECK((sg.getImagePath() == "images/Ginobili.png"));
        CHECK((sg.getStatAttaque() == 10));
        CHECK((sg.getStatDefense() == 11));
        CHECK((sg.getStatVitesse() == 12));
    }

    TEST_CASE("Construct SmallForward") {
        SmallForward sf("Leonard", "Kawhi", "Small Forward", "images/Leonard.png", 10, 11, 12);
        CHECK((sf.getNom() == "Leonard"));
        CHECK((sf.getPrenom() == "Kawhi"));
        CHECK((sf.getPosition() == "Small Forward"));
        CHECK((sf.getImagePath() == "images/Leonard.png"));
        CHECK((sf.getStatAttaque() == 10));
        CHECK((sf.getStatDefense() == 11));
        CHECK((sf.getStatVitesse() == 12));
    }
}

TEST_SUITE("Joueur abstract class") {
    TEST_CASE("Add stats") {
        Center c("Duncan", "Tim", "Center", "images/Duncan.png", 10, 11, 12);
        c.addStat(11);
        CHECK((c.getStatAttaque() == 21));
        CHECK((c.getStatDefense() == 22));
        CHECK((c.getStatVitesse() == 23));
    }

    TEST_CASE("Set attaque stats") {
        Center c("Duncan", "Tim", "Center", "images/Duncan.png", 10, 11, 12);
        c.setStatAttaque(55);
        CHECK((c.getStatAttaque() == 55));
    }

    TEST_CASE("Set defense stats") {
        Center c("Duncan", "Tim", "Center", "images/Duncan.png", 10, 11, 12);
        c.setStatDefense(60);
        CHECK((c.getStatDefense() == 60));
    }

    TEST_CASE("Set vitesse stats") {
        Center c("Duncan", "Tim", "Center", "images/Duncan.png", 10, 11, 12);
        c.setStatVitesse(65);
        CHECK((c.getStatVitesse() == 65));
    }

    TEST_CASE("Set points") {
        Center c("Duncan", "Tim", "Center", "images/Duncan.png", 10, 11, 12);
        c.setPoints(67);
        CHECK((c.getPoints() == 67));
    }
}

TEST_SUITE("Operator overloads") {
    TEST_CASE("Joueur operator++") {
        Center c("Duncan", "Tim", "Center", "images/Duncan.png", 10, 11, 12);
        CHECK((c.getPoints() == 0));
        c++;
        CHECK((c.getPoints() == 1));
    }

    TEST_CASE("Joueur operator+=") {
        Center c("Duncan", "Tim", "Center", "images/Duncan.png", 10, 11, 12);
        CHECK((c.getPoints() == 0));
        c += 15;
        CHECK((c.getPoints() == 15));
    }

    TEST_CASE("Joueur operator<<") {
        Center c("Duncan", "Tim", "Center", "images/Duncan.png", 10, 11, 12);
        std::stringstream ss;
        ss << c;
        CHECK((ss.str() == "Tim Duncan scored 0 points"));
        ss.str("");
        c++;
        ss << c;
        CHECK((ss.str() == "Tim Duncan scored 1 points"));
    }
}
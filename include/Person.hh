#ifndef PERSON_HH
#define PERSON_HH

#include <string>
#include <utility>

using namespace std;

class Person
{
protected:
    string _nom;
    string _prenom;
    string _imagePath; // New attribute for image path

public:
    Person(string nom, string prenom, string imagePath)
        : _nom(std::move(nom)), _prenom(std::move(prenom)), _imagePath(std::move(imagePath)) {}

    // Getter and setter for the image path
    const string& getImagePath() const {
        return _imagePath;
    }

    void setImagePath(const string& imagePath) {
        _imagePath = imagePath;
    }

    // Other getter methods
    const string& getNom() const {
        return _nom;
    }

    const string& getPrenom() const {
        return _prenom;
    }

    const string getFullName() const {
        return _prenom + " " + _nom;
    }

    friend std::ostream& operator<<(std::ostream& os, const Person& personne) {
        os << "Nom: " << personne._nom << ", Prenom: " << personne._prenom;
        return os;
    }
};

#endif // PERSON_HH
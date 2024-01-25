#ifndef PERSON_HH
#define PERSON_HH

#include <string>

using namespace std;

class person
{
protected:
    string _nom;
    string _prenom;
    string _imagePath; // New attribute for image path

public:

    person()
    {
    }

    person(string nom, string prenom, string imagePath)
        : _nom(nom), _prenom(prenom), _imagePath(imagePath)
    {
    }

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

    const string getName() const {
        return _prenom+" "+_nom;
    }
};

#endif // PERSON_HH
//
// Created by Nolan Donaldson on 11/16/2018.
//

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "StarDesc.h"
using namespace std;

//Default Constructor; initializes values to be equal to that of the sun
//source: https://en.wikipedia.org/wiki/Sun
StarDesc::StarDesc() {
    _starType = 'G';
    _mass = 1;
    _luminosity = 1;
    _lifetime = 1e10; //10 billion years
    _radius = 1;
    _temperature = 5800;
    _surfaceGravity = 28.02; //sun has 28 times the surface gravity of Earth
    _superNovaYesOrNo = false;
    _blackHoleYesOrNo = false;
    introduction();
}

//parameterized constructor that allows the user to specify aspects of the star
StarDesc::StarDesc(double& mass, double& luminosity, double& lifetime, double& radius, double& temperature) {
    _mass = mass;
    _luminosity = luminosity;
    _lifetime = lifetime;
    _radius = radius;
    _temperature = temperature;
    introduction();
}

//Prints aspects of the star
void StarDesc::PrintStarStats() const {
    cout << endl;
    cout << "-------------------------------------" << endl;
    cout << " #How Your Star Compares to the Sun#" << endl;
    cout << "-------------------------------------" << endl;
    cout << "Your star's spectral class is type " << _starType << "." << endl;
    cout << "Your star is " << _mass << " times as massive as the sun." << endl;
    cout << "Your star's radius is " << _radius << " times the sun's radius." << endl;
    cout << "Your star's surface temperature is " << _temperature << " degrees K." << endl;
    cout << "Your star is " << _luminosity << " times as luminous as the sun." << endl;
    cout << "Your star's surface gravity is " << _surfaceGravity <<  " times what it is on Earth." << endl;
    cout << "Your star will be expected to last approximately " << _lifetime << " years." << endl;
    if (_superNovaYesOrNo) {
        cout << "Your star will go out in a blaze of glory known as a supernova!" << endl;
        if (_blackHoleYesOrNo) {
            cout << "Then your star will become a black hole once it's done blowing up. Pretty neat!" << endl;
        }
        //source on neutron stars: http://astronomy.swin.edu.au/cosmos/N/Neutron+Star
        else {
            cout << "Then your star will become a neutron star at the end of its life." << endl;
            cout << "It'll probably spin super fast and (as the name may suggest) be almost completely made of neutrons." << endl;
        }
    }
    else {
        if (_mass > _lowerMassLimit) {
            cout << "Your star will slowly burn out as a white dwarf, just like the Sun." << endl;
        }
        else {
            cout << "As a brown dwarf, your object isn't really a star, since no nuclear fusion is happening." << endl;
            cout << "Your star will probably just cool until it's basically just a large planet. Who knows?" << endl;
        }
    }
}

/* calculates the traits of the user's star object depending on what the user specifies about their star.
 * can sorta work for basically any star, but works best with main-sequence stars, aka "dwarf" stars
 */
void StarDesc::CalculateTraits(){
    double mass, radius, temperature, luminosity;
    char yesNo;
    int tally = 0;
    bool radiusNo, tempNo, luminNo;
    calcIntro();

    cout << "The mass you enter is relative to the sun's mass." << endl;
    cout << "The absolute upper limit is about 150 times the sun's mass. The lower limit is about 0.08 suns." << endl;
    cout << "Below this, your star isn't really a star anymore!" << endl;
    //checks if the user's mass is in range and makes the user enter it in again if it isn't
    do {
        cout << "Enter the star's mass: ";
        cin >> mass;
        if (mass > _upperMassLimit) {
            cout << "There's no such thing as a star that massive! Try again." << endl;
            continue;
        }
        else if (mass < _lowerMassLimit) {
            _starType = _spectralClasses[8]; //star is a brown dwarf, which technically isn't a star
            _mass = mass;
            break;
        }
        else {
            _mass = mass;
            break;
        }
        cout << endl;
    } while (true);

    //asking for the user's radius of the star and then checking it
    cout << "Would you like to specify the radius of the star? (Y/N) ";
    cin >> yesNo;
    if (yesNo == 'Y' || yesNo == 'y') {
        cout << "The radius of your star is relative to the sun." << endl;
        cout << "It can be pretty much as small as you want, but it caps out at around 1000." << endl;
        //source: https://en.wikipedia.org/wiki/Stellar_classification
        cout << "Enter the radius of the star: ";
        do {
            cin >> radius;
            if (radius < 1000 && radius > 0) {
                _radius = radius;
                break;
            }
            else {
                cout << "Out of bounds! Try again." << endl;
                continue;
            }
        } while (true);
    }
    //increments a tally upon "n" or "N" that makes sure the user enters in at least 2 values
    else if (yesNo == 'N' || yesNo == 'n') {
        tally += 1;
        radiusNo = true;
    }
    else {
        cout << "?" << endl;
    }

    //asking for the user's temperature of the star and then checking it
    cout << "Would you like to specify the surface temperature of the star? (Y/N) ";
    cin >> yesNo;
    if (yesNo == 'Y' || yesNo == 'y') {
        cout << "The surface temperature of your star is in degrees K. For reference, the sun is 5800K." << endl;
        cout << "It typically ranges between 30000K on the upper end and 2400K on the lower end." << endl;
        //source: https://en.wikipedia.org/wiki/Stellar_classification
        cout << "Enter the temperature of the star: ";
        do {
            cin >> temperature;
            if (temperature > 0) {
                _temperature = temperature;
                break;
            }
            else {
                cout << "Out of bounds! Try again." << endl;
                continue;
            }
        } while (true);
    }
    else if (yesNo == 'N' || yesNo == 'n') {
        tally += 1;
        tempNo = true;
    }
    else {
        cout << "?" << endl;
    }

    //asking for the user's luminosity of the star and then checking it
    cout << "Would you like to specify the luminosity of your star? (Y/N) ";
    cin >> yesNo;
    if (yesNo == 'Y' || yesNo == 'y') {
        cout << "The luminosity of your star is basically its energy output relative to the sun." << endl;
        cout << "It typically ranges between 30000 on the upper end and 0.08 on the lower end." << endl;
        cout << "However, stars can go much higher and lower than this." << endl;
        //source: https://en.wikipedia.org/wiki/Stellar_classification
        cout << "Enter the luminosity of the star: ";
        do {
            cin >> luminosity;
            if (luminosity > 0) {
                _luminosity = luminosity;
                break;
            }
            else {
                cout << "Out of bounds! Try again." << endl;
                continue;
            }
        } while (true);
    }
    else if (yesNo == 'N' || yesNo == 'n') {
        tally += 1;
        luminNo = true;
    }
    else {
        cout << "?" << endl;
    }

    //stops the program if the user doesn't specify 2 or more values
    if (tally >= 2) {
        cout << "Sorry, but the program requires that you enter in at least 2 of the above values." << endl;
    }
    else {
        //calculating the unknowns (when needed)
        if (radiusNo) {
            _radius = calculateRadius();
        }
        else if (tempNo) {
            _temperature = calculateTemperature();
        }
        else if (luminNo) {
            _luminosity = calculateLuminosity();
        }
    }
    //lifetime is based on the amount of fuel(mass) and the energy output(luminosity) of the star
    _lifetime = calculateLifetime();

    //calculates the star's surface gravity in relation to the Earth
    _surfaceGravity = calculateSurfaceGravity();

    //supernova comparison
    _superNovaYesOrNo = calculateSuperNova();

    //black hole comparison
    _blackHoleYesOrNo = calculateBlackHole();
}

/*
 * public function that determines the star's spectral class
 * uses the harvard classification, which is only based off of temperature (for simplicity's sake) and works for
 * main-sequence stars (stars do deviate from the main sequence, but only extremely massive or dense stars usually do)
 * source: http://astronomy.swin.edu.au/cosmos/h/harvard+spectral+classification
 * RGB values: http://www.tayloredmktg.com/rgb/#PI
 */
void StarDesc::DetermineStarType() {
    //O-type star, by far the hottest and brightest stars. Usually blue-violet in color
    if (_temperature >= 2.8e4) {
        _starType = _spectralClasses[0];
        _starColor.r = 132;
        _starColor.g = 112;
        _starColor.b = 255;
    }
    //B-Type star, still pretty dang hot and bright, usually blue in color
    else if (_temperature < 2.8e4 && _temperature >= 10e4) {
        _starType = _spectralClasses[1];
        _starColor.r = 0;
        _starColor.g = 0;
        _starColor.b = 205;
    }
    //A-type star, very hot and bright but nothing ridiculous. Blue color
    else if (_temperature < 10e4 && _temperature >= 7.5e3) {
        _starType = _spectralClasses[2];
        _starColor.r = 0;
        _starColor.g = 0;
        _starColor.b = 255;
    }
    //F-type star, still hotter and brighter than most stars. blue-white color
    else if (_temperature < 7.5e3 && _temperature >= 6e3) {
        _starType = _spectralClasses[3];
        _starColor.r = 0;
        _starColor.g = 191;
        _starColor.b = 255;
    }
    //G-type star, same as the sun. Yellow-white in color
    else if (_temperature < 6e3 && _temperature >= 5e3) {
        _starType = _spectralClasses[4];
        _starColor.r = 255;
        _starColor.g = 255;
        _starColor.b = 215;
    }
    //H-type star, a little smaller than the sun. A lot more common than the sun, too. Orange-red in color
    else if (_temperature < 5e3 && _temperature >= 3.5e3) {
        _starType = _spectralClasses[5];
        _starColor.r = 255;
        _starColor.g = 69;
        _starColor.b = 0;
    }
    //M-type star, a red dwarf. SUPER common. Also pretty dim, but can live trillions of years. Red in color
    else if (_temperature < 3.5e3) {
        //brown dwarfs, aka "failed stars". Happens when the star doesn't have enough mass for nuclear fusion to happen
        if (_mass < _lowerMassLimit) {
            _starType = _spectralClasses[7];
            _starColor.r = 139;
            _starColor.g = 69;
            _starColor.b = 19;
            _lifetime = 0;
        }
        else {
            //if mass is big enough, is a red dwarf instead
            _starType = _spectralClasses[6];
            _starColor.r = 255;
            _starColor.g = 0;
            _starColor.b = 0;
        }
    }
}

//public member function that defines the star's shape(always a circle) and color
sf::CircleShape StarDesc::DefineStarObject() {
    sf::CircleShape starObject;
    starObject.setRadius(100 * _radius);
    starObject.setOrigin(sf::Vector2f(_radius * 100, _radius * 100 ));
    starObject.setPosition(_radius * 100 + 50, 450);
    starObject.setFillColor(_starColor);
    return starObject;
}

//public member function that defines a star's lifetime bar corresponding to its lifetime compared to the sun's
sf::RectangleShape StarDesc::LifetimeBar() {
    //1e10, or 10 billion, is the sun's lifetime. This will ensure that the comparison makes visual sense
    double visualLifetime;
    if (_lifetime < 1e10) {
        visualLifetime = (_lifetime / 1e10) * 640;
    }
    else {
        visualLifetime = 640;
    }

    //drawing the lifetime bar
    sf::RectangleShape lifetimeBar;
    lifetimeBar.setPosition(0, 320);
    lifetimeBar.setRotation(0);
    lifetimeBar.setFillColor(sf::Color::White);
    lifetimeBar.setSize(sf::Vector2f(visualLifetime, 20));
    return lifetimeBar;
}

//sun's lifetime, which will visually change if it's smaller than the user's star
sf::RectangleShape StarDesc::SunLifetimeBar() {
    double visualLifetime = 640;
    if (_lifetime > 1e10) {
        visualLifetime = visualLifetime / (_lifetime / 1e10);
    }

    //drawing the lifetime bar
    sf::RectangleShape sunLifetime;
    sunLifetime.setPosition(0, 275);
    sunLifetime.setRotation(0);
    sunLifetime.setFillColor(sf::Color::White);
    sunLifetime.setSize(sf::Vector2f(visualLifetime, 20));
    return sunLifetime;
}

//getter functions
char StarDesc::GetStarType() const {
    return _starType;
}

double StarDesc::GetRadius() const {
    return _radius;
}

double StarDesc::GetMass() const {
    return _mass;
}

double StarDesc::GetLuminosity() const {
    return _luminosity;
}

double StarDesc::GetLifetime() const {
    return _lifetime;
}

double StarDesc::GetTemperature() const {
    return _temperature;
}

bool StarDesc::GetSuperNova() const {
    return _superNovaYesOrNo;
}

bool StarDesc::GetBlackHole() const {
    return _blackHoleYesOrNo;
}

//setter functions
void StarDesc::SetStarType(char starType) {
    int i;

    //only allows the user to specify a Star's spectral class within the vector
    for (i=0; i<_spectralClasses.size(); i++) {
        if (starType == _spectralClasses[i]) {
            _starType = starType;
        }
        else if (starType + 32 == _spectralClasses[i]) {
            _starType = char(starType + 32);
        }
        else {
            cout << "No such spectral class exists." << endl;
        }
    }
}

void StarDesc::SetStarRadius(double radius) {
    _radius = radius;
}

//prevents user from specifying a mass that exists outside of realm of possibility
void StarDesc::SetMass(double mass) {
    if (mass > _upperMassLimit) {
        cout << "No star that massive exists!" << endl;
    }
    else if (mass < _lowerMassLimit) {
        _starType = _spectralClasses[7]; //star is a brown dwarf
        _mass = mass;
    }
    else {
        _mass = mass;
    }
}

void StarDesc::SetLuminosity(double luminosity) {
    _luminosity = luminosity;
}

void StarDesc::SetLifetime(double lifetime) {
    _lifetime = lifetime;
}

//private helper function that calculates a star's (approximate) lifetime, requires star's mass and luminosity
double StarDesc::calculateLifetime() {
    const double sunLifetime = 1e10; //sun lives about 10 billion years
    double starLifeTime;

    //star lifetime is directly related to its mass and luminosity
    //equation from http://astronomy.swin.edu.au/cosmos/m/main+sequence+lifetime
    starLifeTime = (_mass / _luminosity) * sunLifetime;

    return starLifeTime;
}

//private helper that solves for the star object's luminosity (aka energy output)
double StarDesc::calculateLuminosity() {
    double luminosity;
    double relativeTemp = _temperature / _sunTemperature;

    //solves for ratio of the sun's luminosity and the star object's luminosity
    //source: http://cas.sdss.org/dr4/en/proj/advanced/hr/radius1.asp
    luminosity = pow(_radius, 2.0) * pow(relativeTemp, 4.0);

    return luminosity;
}

//private helper that calculates a star's approx. surface temperature in degrees K; requires star radius and luminosity
double StarDesc::calculateTemperature() {
    double starTemp;

    //equation from http://cas.sdss.org/dr4/en/proj/advanced/hr/radius1.asp
    //solves for ratio between sun's surface temperature and the user's star object
    //converts to degrees K by multiplying by the sun's surface temp
    starTemp = pow(_luminosity, 0.25) / pow(_radius, 0.50) * _sunTemperature;

    return starTemp;
}

//private helper that calculates the radius of the star; requires star's surface temperature and luminosity
double StarDesc::calculateRadius() {
    double radius;

    //equation from http://cas.sdss.org/dr4/en/proj/advanced/hr/radius1.asp
    //solves for ratio of sun's radius to star object's radius
    radius = pow((_sunTemperature / _temperature), 2.0) * sqrt(_luminosity);

    return radius;
}

//private helper that calculates the surface gravity of the star. Requires its mass and radius
//source: https://www.physicsclassroom.com/class/circles/Lesson-3/The-Value-of-g
double StarDesc::calculateSurfaceGravity() {
    double starGravity, starMassKg, starRadiusMeters;
    const double G = 6.674e-11; //gravitational constant
    const double sunMass = 1.9885e30; //sun's mass in kg
    const double sunRadius = 6.957e8; //sun's radius in m

    //values must be converted to SI units
    starMassKg = _mass * sunMass;
    starRadiusMeters = _radius * sunRadius;

    //calculation using newton's universal law of gravitation, returns value in m/s/s or m/s^2
    starGravity = (G * starMassKg) / pow(starRadiusMeters, 2.0);

    //converting to g's, or earth's gravity
    starGravity = starGravity / 9.8;

    return starGravity;
}

//private helper that determines whether the star will blow up or not
bool StarDesc::calculateSuperNova() {
    bool superNova = false;

    //source: http://astronomy.swin.edu.au/cosmos/C/Chandrasekhar+Limit
    if (_mass > 1.4) {
        superNova = true;
    }

    return superNova;
}

//private helper that determines if a star will collapse into a black hole or not
bool StarDesc::calculateBlackHole() {
    bool blackHole = false;

    //source: http://astronomy.swin.edu.au/cosmos/N/Neutron+Star
    //mass required to become a black hole isn't completely agreed upon. However, it still works ok for this program
    if (_mass > 3) {
        blackHole = true;
    }

    return blackHole;
}

//introduction that makes the user read a lot; private helper
void StarDesc::introduction() {
    cout << "----------------------" << endl;
    cout << " Welcome to Starseer!" << endl;
    cout << "----------------------" << endl;
    cout << endl;
    cout << "This program will allow a user to create their own star with its own traits which will then be visually";
    cout << " compared to the sun. " << endl;
    cout << "The traits the user will specify are the star's mass, temperature, radius, and luminosity." << endl;
    cout << "The mass will always be user-specified, but out of the other 3 traits, the user need only enter in two.";
    cout << endl;
    cout << "Starseer will then inform the user of the other calculable traits of the star, such as its predicted";
    cout << " lifespan, if it" << endl;
    cout << "will explode into a supernova, and if it will collapse into a black hole or neutron star.";
    cout << endl;
    cout << "A visual representation of the star will also appear, showing the user a scale model of the star";
    cout << ", a bar showing its" << endl;
    cout << "predicted lifespan, the star's color, and how these compare to the sun." << endl;
    cout << "The program will also tell the user how strong the gravity on the surface is compared to the Earth's!";
    cout << endl;
    cout << endl;
}

//Information for the user to use when creating their star object; private helper
//source on Sirius stats: https://www.britannica.com/place/Sirius-star
void StarDesc::calcIntro() {
    cout << "------------------------------------------------------" << endl;
    cout << "   #Here is where you enter in your star's traits#" << endl;
    cout << "------------------------------------------------------" << endl;
    cout << endl;
    cout << "With the exception of your star's temperature, the values of your star are always relative to the sun's.";
    cout << endl;
    cout << "Things get weird as stars get super big and super small, so the program won't always be accurate." << endl;
    cout << endl;
    cout << "As an example, try entering in the values of Sirius, the brightest star in the night sky." << endl;
    cout << "Sirius is twice as massive as the sun, so mass = 2." << endl;
    cout << "Its radius is 1.71 times that of the sun, so radius = 1.71." << endl;
    cout << "Its surface temperature is 9940K, so temperature = 9940." << endl;
    cout << "And it is 25.4 times as luminous as the sun, so luminosity = 25.4." << endl;
    cout << "Try fiddling around with the values and see what kind of star you get! Have fun!" << endl;
    cout << endl;
}

//
// Created by Nolan Donaldson on 11/16/2018.
//

/*Sources for the the mass limits and star types/spectral classes are from the following:
 * https://www.space.com/858-study-stars-size-limit.html
 * https://www.space.com/840-newfound-star-smaller-planets.html
 * http://www.ucolick.org/~bolte/AY4_04/class4_04bwd.pdf
 * https://www.enchantedlearning.com/subjects/astronomy/stars/startypes.shtml
 * https://en.wikipedia.org/wiki/Stellar_classification
 * Other sources are listed in the StarDesc.cpp file close to where they are used.
 */

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
using namespace std;

#ifndef SFML_TEMPLATE_STARDESC_H
#define SFML_TEMPLATE_STARDESC_H

class StarDesc {
public:
    //default and parameterized constructors
    StarDesc();
    StarDesc(double& mass, double& luminosity, double& lifetime, double& radius, double& temperature);
    //public member functions
    void CalculateTraits();
    void PrintStarStats() const;
    void DetermineStarType();
    sf::CircleShape DefineStarObject();
    sf::RectangleShape LifetimeBar();
    sf::RectangleShape SunLifetimeBar();
    //getter functions
    char GetStarType() const;
    double GetRadius() const;
    double GetMass() const;
    double GetLuminosity() const;
    double GetLifetime() const;
    double GetTemperature() const;
    bool GetSuperNova() const;
    bool GetBlackHole() const;
    //setter functions
    void SetStarType(char starType);
    void SetStarRadius(double radius);
    void SetMass(double mass);
    void SetLuminosity(double luminosity);
    void SetLifetime(double lifetime);

private:
    char _starType; //spectral classes. From hottest to coolest: O, B, A, F, G, K, M, T. The sun is type G
    //stars can be only any one of these spectral classes; therefore the vector cannot be altered
    //stars go from hottest to coldest, O -> T
    //source: https://en.wikipedia.org/wiki/Main_sequence
    const vector<char> _spectralClasses = {'O', 'B', 'A', 'F', 'G', 'K', 'M', 'T'};
    sf::Color _starColor; //color of the star as determined by its spectral class;
    double _mass; //measured in solar masses
    double _radius; //measured in solar radii (sun = 1)
    double _temperature; //measured in Kelvin, surface temperature of the star
    double _luminosity; //measured in terms of solar luminosity (sun = 1 L), how much energy a star outputs
    double _surfaceGravity; //measured in Earth units; the earth is equal to 1, or 9.8 m/s/s
    double _lifetime; //Measured in years
    const double _sunTemperature = 5800; //surface temperature of the sun. Helps with proper conversions
    const double _lowerMassLimit = 0.08; //lowest mass possible for nuclear fusion to happen; measured in solar masses
    const double _upperMassLimit = 150.0; //highest observed mass of a star; measured in solar masses
    bool _superNovaYesOrNo; //whether or not a star object will collapse into a supernova based on its mass
    bool _blackHoleYesOrNo; //whether or not a star object will become a black hole (only after a supernova)
    //lifetimes and temperature helper functions
    double calculateLifetime();
    double calculateLuminosity();
    double calculateTemperature();
    double calculateRadius();
    double calculateSurfaceGravity();
    bool calculateSuperNova();
    bool calculateBlackHole();
    //Lots of words for the user to read so they know what's happening
    void introduction();
    void calcIntro();
};

#endif //SFML_TEMPLATE_STARDESC_H

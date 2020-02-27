#include <iostream>                             // for standard input/output
#include "StarDesc.h"
using namespace std;                            // using the standard namespace

#include <SFML/Graphics.hpp>                    // include the SFML Graphics Library
using namespace sf;                             // using the sf namespace

//Author: Nolan Donaldson
//CSCI-261-B, 12/06/18
//Final Project: Starseer

int main() {
    StarDesc star;
    star.CalculateTraits();
    star.DetermineStarType();
    star.PrintStarStats();

    // create a RenderWindow object
    // specify the size to be 640x640
    // set the title to be "SFML Example Window"
    RenderWindow window( VideoMode(640, 640), "Star Comparison" );

    //********************************************
    //  PLACE ANY FILE INPUT PROCESSING BELOW HERE
    //********************************************
    Font starFont;
    if(!starFont.loadFromFile("data/arial.ttf"))
        return -1;
    //********************************************
    //  PLACE ANY FILE INPUT PROCESSING ABOVE HERE
    //********************************************

    // while our window is open, keep it open
    // this is our draw loop
    while( window.isOpen() ) {
        window.clear( Color::Black );           // clear the contents of the old frame
                                                // by setting the window to black

        //****************************************
        //  ADD ALL OF OUR DRAWING BELOW HERE
        //****************************************

        //drawing the user's star. This is done before the sun in case it's super huge
        window.draw(star.DefineStarObject());

        //drawing star object's lifetime bar
        window.draw(star.LifetimeBar());

        //label for the star's lifetime bar
        Text starLifeLabel;
        starLifeLabel.setFont(starFont);
        starLifeLabel.setString("Your Star's Lifetime");
        starLifeLabel.setPosition(0, 300);
        starLifeLabel.setCharacterSize(20);
        starLifeLabel.setFillColor(Color::White);
        window.draw(starLifeLabel);

        //star object's label
        Text starLabel;
        starLabel.setFont(starFont);
        starLabel.setString("Your Star");
        starLabel.setPosition(50, 350);
        starLabel.setFillColor(Color::White);
        window.draw(starLabel);

        CircleShape sun;
        //yellow-white color used for the sun
        sun.setFillColor(Color(255, 255, 215));
        sun.setPosition(50, 50);
        sun.setRadius(100);
        window.draw(sun);

        //sun's lifetime bar. Its length changes depending on the length of the other star's lifetime
        window.draw(star.SunLifetimeBar());

        //sun's lifetime bar label
        Text sunLifetimeLabel;
        sunLifetimeLabel.setFont(starFont);
        sunLifetimeLabel.setString("Sun's Lifetime");
        sunLifetimeLabel.setPosition(0, 255);
        sunLifetimeLabel.setCharacterSize(20);
        sunLifetimeLabel.setFillColor(Color::White);
        window.draw(sunLifetimeLabel);

        //sun label
        Text sunLabel;
        sunLabel.setFont(starFont);
        sunLabel.setString("Sun");
        sunLabel.setPosition(50, 25);
        sunLabel.setFillColor(Color::White);
        window.draw(sunLabel);

        //****************************************
        //  ADD ALL OF OUR DRAWING ABOVE HERE
        //****************************************

        window.display();                       // display the window

        //****************************************
        // HANDLE EVENTS BELOW HERE
        //****************************************
        Event event;
        while( window.pollEvent(event) ) {      // ask the window if any events occurred
            if( event.type == Event::Closed ) { // if event type is a closed event
                                                // i.e. they clicked the X on the window
                window.close();                 // then close our window
            }
        }
    }

    return EXIT_SUCCESS;                        // report our program exited successfully
}
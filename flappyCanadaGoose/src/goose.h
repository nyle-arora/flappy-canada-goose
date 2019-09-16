#pragma once
//
// Created by Nyle Arora on 2019-03-13.
//

#include <ge211.h>


struct Goose {

    /// CONSTRUCTOR

    explicit Goose();

    /// MEMBER FUNCTIONS

    //Tells us whether the goose's velocity is positive or negative.
    bool goose_falling_();

    //Returns the goose at a new position based off the forces acting on the original goose
    //(i.e. gravity & flap acceleration
    Goose goose_next_();

    /// MEMBER VARIABLES


    //Describes whether the user wants to flap the bird (this is true when the user presses
    //the space bar
    bool userflap;

    //Describes the center position of the goose sprite
    ge211::Position center_;

    //Describes the radius of the goose sprite
    int radius_;

    //Provides the velocity of the goose sprite's y-coordinate
    int velocity_;

    //Acceleration in the upwards direction on the y-coordinate of the goose sprite
    int flap_acceleration_;

    //This is the effect of gravity on the goose
    int gravity;

};

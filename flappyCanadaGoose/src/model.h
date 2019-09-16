#pragma once

#include <ge211.h>
#include "goose.h"
#include <vector>
#include <string>

using Pipe = ge211::Rectangle;

class Model {

    /// CONSTRUCTOR
public:
    explicit Model();

    /// MEMBER FUNCTIONS

    //This function will update the state of the game for one frame
    //(1/60 s). Does nothing if the game is in the dead state. Otherwise,
    //if the next position of the bird is at the bottom of the screen or
    //intersecting with one of the pipes, it sets the game to the game over
    //state and calls the game over function defined below. Otherwise, the
    //bird will remain in the live state and will have its position
    //updated.
    void update(int);

    //This returns whether the game is dead or not for a given bottom pipe
    bool game_over_bottom_(Pipe p);

    //This returns whether the game is dead or not for a given top pipe
    bool game_over_top_(Pipe p);

    //This tells the game what to do in the Game over score (i.e display
    //the final score, decide which medal the player has earned.)
    void final_display(int score_);

    //This function switches the game from the dead state to the live state. In
    //the UI, this function will be run when the space bar is activated.
    void start_();

    /// MEMBER VARIABLES

    //This variable tells us whether the game is in dead state or if it's live
    bool live_;

    //This defines the dimensions of the window
    ge211::Dimensions scene_dims;

    //This keeps track of how many pipes the bird has cleared.
    int score_;

    //initial x position of every new pipe
    int initial_pipe_x;

    //default initial y position of every new pipe (this is randomized later with the UI)
    int initial_pipe_y;

    //This variable is used by the UI to check if the game is over
    bool gameovervariable;

    //The message displayed in the game over state (fed into text sprite in UI)
    std::string finalmessage;

    //This is the horizontal distance between pipe sets
    int pipe_spacing;

    //This is the vertical distance between top and bottom pipes
    int gap_distance;

    //This is the vector for bottom pipes
    std::vector<Pipe> bottom_pipes_;

    //This is the vector for top pipes
    std::vector<Pipe> top_pipes_;

    //Stores the random height of the top pipe to be called by the UI to create the sprites
    int top_height;

    //Stores the random height of the bottom pipe to be called by the UI to create the sprites
    int bottom_height;

    //State of the goose
    Goose goose_;

private:

    //How fast the pipes move towards the left side of the screen
    int pipe_velocity;

};
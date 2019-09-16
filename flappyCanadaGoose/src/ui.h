#ifndef FINAL_PROJECT_UI_H
#define FINAL_PROJECT_UI_H

#endif //FINAL_PROJECT_UI_H

#pragma once

#include "model.h"
#include <ge211.h>
#include <cstdlib>
#include <vector>

//these constants are defined here
//extern ge211::Color goose_color const ;
//extern ge211::Color pipe_color const;

//ge211::Color const goose_color {255, 255, 0};
ge211::Color const pipe_color {27, 229, 9};

struct Ui : ge211::Abstract_game {

    //Constructor
    explicit Ui(Model&);

    //Returns the size of the window, as given by model_.scene_dims
    ge211::Dimensions initial_window_dimensions() const override;

    //Returns the randomly generated height of each bottom pipe
    //int bottom_pipe_random_y();

    //Renders all game entities on the screen.
    void draw(ge211::Sprite_set& sprites) override;

    //Controller functions for space bar and mouse clicks (both of which launch
    //the bird upwards)
    //WE ACTUALLY ONLY DID SPACE BAR
    void on_key(ge211::Key) override;
    //void on_mouse_up(ge211::Mouse_button, ge211::Position) override;

    //Updates the model of the game to reflect the passage of time by calling
    //Model::update
    void on_frame(double dt) override;

    //Model reference
    Model& model_;

    std::vector<Pipe> pipez_;

    //Sprites
    //ge211::Circle_sprite const
    //        goose_sprite {model_.goose_.radius_,
    //                      goose_color};

    ge211::Image_sprite const bg_pic {"background3.png"};
    //Image sprite for Canada Goose logo
    ge211::Image_sprite const logo_sprite {"gooselogo.png"};

    //ge211::Rectangle_sprite bottom_sprite{{86, 300}, pipe_color};

    //ge211::Rectangle_sprite top_sprite{{86, 268}, pipe_color};

    //text sprite
    ge211::Text_sprite const text_sprite {model_.finalmessage, ge211::Font("COMIC.TTF", 20)};

    ge211::Rectangle_sprite rect = ge211::Rectangle_sprite({10, 10}, pipe_color);

    std::vector <ge211::Rectangle_sprite> rectz_;

};
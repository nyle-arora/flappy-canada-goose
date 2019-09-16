#include "model.h"
#include "goose.h"
#include <stdlib.h>

Model::Model()
        : live_ (false)
        , scene_dims {1024, 768}
        , score_ {0}
        , initial_pipe_x {1024}
        , initial_pipe_y {500}
        , gameovervariable (false)
        , finalmessage ("You're garbage and should go live with the snails ")
        , pipe_spacing {170} //256 - 86
        , gap_distance {230}
        , pipe_velocity {-4}
{
    //adding the first bottom pipe to the vector
    Pipe bottom;
    //Pipe* bottom_ref = &bottom;
    bottom.width = 86;
    bottom.x = initial_pipe_x;
    bottom.y = initial_pipe_y;
    bottom.height = 3000;
    //bottom_height = bottom.height;
    bottom_pipes_.push_back(bottom);
    //adding the first top pipe to the vector
    Pipe top;
    //Pipe* top_ref = &top;
    top.width = 86;
    top.x = initial_pipe_x;
    top.y = 0;
    top.height = bottom.y - gap_distance;
    //top_height = top.height;
    top_pipes_.push_back(top);
}

void Model::start_() {
    live_ = true;
    goose_.userflap = true;
}

bool Model::game_over_bottom_(Pipe p) {
    Goose gooseboi = goose_;
    if (gooseboi.center_.y + gooseboi.radius_ >= 768) { //if the goose hits the bottom
        live_ = false;
        gameovervariable = true;
        return gameovervariable;
    }
    if (gooseboi.center_.x + gooseboi.radius_ >= p.x && gooseboi.center_.x - gooseboi.radius_ <= p.x + p.width) {
        if (gooseboi.center_.y + gooseboi.radius_ >= p.y) {
            live_ = false;
            gameovervariable = true;
            return gameovervariable;
        }
    }
    return false;
}

bool Model::game_over_top_(Pipe p) {
    Goose gooseboi = goose_;
    if (gooseboi.center_.y + gooseboi.radius_ >= 768) { //if the goose hits the bottom
        live_ = false;
        gameovervariable = true;
        return gameovervariable;
    }
    if (gooseboi.center_.x + gooseboi.radius_ >= p.x && gooseboi.center_.x - gooseboi.radius_ <= p.x + p.width) {
        if (gooseboi.center_.y - gooseboi.radius_ <= p.height) { //found and corrected mistake here
            live_ = false;
            gameovervariable = true;
            return gameovervariable;
        }
    }
    return false;
}

void Model::final_display(int score_) {
    if (score_ >= 10 && score_ < 20)
        finalmessage = "You got a bronze medal! Score: " + std::to_string(score_);
    else if (score_ >= 20 && score_ < 30)
        finalmessage = "You got a silver medal! Score: " + std::to_string(score_);
    else if (score_ >= 30)
        finalmessage = "You got a gold medal! Score: " + std::to_string(score_);
    else
        finalmessage = "You get no medal :( Score: " + std::to_string(score_);
}

void Model::update(int rand){
    //move the bird
    //Goose g = goose_.goose_next_();
    if (!live_) return;
    else {
        //constructing a potential new pipe
        Pipe new_bottom;
        //Pipe* new_bottom_ref = &new_bottom;
        new_bottom.width = 86;
        new_bottom.x = initial_pipe_x;
        new_bottom.y = rand + 230;
        new_bottom.height = 3000;

        Pipe new_top;
        new_top.width = 86;
        new_top.x = initial_pipe_x;
        new_top.y = 0;
        new_top.height = rand;
        //incrementing through the pipes
        for (Pipe& p : top_pipes_) {
            p.x += pipe_velocity;
            if (game_over_top_(p)) {
                final_display(score_);
                return;
            }
        }
        for (Pipe& p : bottom_pipes_) {
            //moving each pipe closer to the left
            p.x += pipe_velocity;
            //if the bird hits pipe, display game over model
            if (game_over_bottom_(p)) {
                final_display(score_);
                return;
            }
            else {
                //If a pipe is approximately a quarter way down the screen, create a new pipe
                //at back of vector. This number determines pipe_spacing
                if (p.x == 468) {
                    bottom_pipes_.push_back(new_bottom);
                    top_pipes_.push_back(new_top);
                }
                if (p.x == -86) {
                    bottom_pipes_.erase(bottom_pipes_.begin());
                    top_pipes_.erase(top_pipes_.begin());
                }
                //if goose passes thru center position of pipes, update score
                if (goose_.center_.x >= (p.x + p.width / 2) - 2 && goose_.center_.x <= (p.x + p.width / 2) + 1) //CHANGED
                    ++score_;

            }
        }
    }
    goose_ = goose_.goose_next_();
}

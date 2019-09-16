#include "model.h"
#include <catch.h>


TEST_CASE("play the game") {
    Model m;
    CHECK(!m.live_);
    m.start_();
    CHECK(m.live_);
    CHECK(m.goose_.goose_falling_());
    CHECK(m.goose_.userflap);
    Goose old_goose = m.goose_;

    m.update(300);
    CHECK(m.goose_.center_.x == old_goose.center_.x);
    CHECK(m.goose_.velocity_ == old_goose.flap_acceleration_);
    CHECK(m.goose_.center_.y == old_goose.center_.y + m.goose_.velocity_); //velocity is updated before position in goose_next_
    CHECK(!m.goose_.userflap);

    Goose old_goose2 = m.goose_;
    m.update(400);
    CHECK(m.goose_.center_.x == old_goose.center_.x);
    CHECK(m.goose_.velocity_ == old_goose2.velocity_ + old_goose2.gravity);
    CHECK(m.goose_.center_.y == old_goose2.center_.y + m.goose_.velocity_);

}

TEST_CASE("ground_collision") {
    Model m;
    Goose goose;
    goose.center_.y = m.scene_dims.height - goose.radius_;
    goose.velocity_ = 10;
    CHECK(goose.goose_falling_());
    m.goose_ = goose;
    m.live_ = true;
    m.update(300);
    CHECK(!m.live_);
}

TEST_CASE("bottom_pipe_collision") {
    Model m;
    Goose goose;
    goose.center_.y = 484;
    goose.velocity_ = 10;
    m.goose_ = goose;
    m.live_ = true;

    Pipe pipe;
    pipe.x = goose.center_.x;
    pipe.y = 505;
    pipe.width = 86;
    pipe.height = m.scene_dims.height - pipe.y;
    //m.bottom_pipes_[0] = pipe;

    CHECK(!m.game_over_bottom_(pipe));
    m.update(300);
    CHECK(m.game_over_bottom_(pipe));
}

TEST_CASE("top_pipe_collision") {
    Model m;
    Goose goose;
    goose.center_.y = 484;
    goose.velocity_ = -10;
    m.goose_ = goose;
    m.live_ = true;

    Pipe pipe;
    pipe.x = goose.center_.x;
    pipe.y = 0;
    pipe.width = 86;
    pipe.height = 463;

    CHECK(!m.game_over_top_(pipe));
    m.update(300);
    CHECK(m.game_over_top_(pipe));
}

TEST_CASE("moving_pipes") {
    Model m;
    m.live_ = true;
    m.update(500);
    CHECK(m.bottom_pipes_[0].x == 1020);
    CHECK(m.bottom_pipes_[0].y == 500);
    CHECK(m.top_pipes_[0].x == 1020);
    CHECK(m.top_pipes_[0].y == 0);

    m.update(600);
    CHECK(m.bottom_pipes_.size() == 1);
    CHECK(m.bottom_pipes_[0].x == 1016);
    CHECK(m.bottom_pipes_[0].y == 500);
    CHECK(m.bottom_pipes_[0].height == 268);
    CHECK(m.top_pipes_[0].x == 1016);
    CHECK(m.top_pipes_[0].y == 0);
    CHECK(m.top_pipes_[0].height == 300);
}

TEST_CASE("creating_new_pipe") {
    Model m;
    m.live_ = true;
    Pipe bottom;
    bottom.x = 772;
    bottom.y = 500;
    bottom.height = 268;
    bottom.width = 86;
    m.bottom_pipes_.clear();
    m.bottom_pipes_.push_back(bottom);
    Pipe top;
    top.x = 772;
    top.y = 0;
    top.height = 300;
    top.width = 86;
    m.top_pipes_.clear();
    m.top_pipes_.push_back(top);

    m.update(400);
    CHECK(m.bottom_pipes_[0].x == 768);
    CHECK(m.top_pipes_[0].x == 768);
    CHECK(m.gap_distance == m.bottom_pipes_[0].top_left().y - m.top_pipes_[0].bottom_left().y);
    CHECK(m.bottom_pipes_[1].x == 1024);
    CHECK(m.top_pipes_[1].x == 1024);
    CHECK(m.bottom_pipes_[1].y == 400);
    CHECK(m.top_pipes_[1].y == 0);
    CHECK(m.bottom_pipes_[1].top_left().x - m.bottom_pipes_[0].top_right().x == m.pipe_spacing);

}

TEST_CASE("increment_score") {
    Model m;
    m.live_ = true;
    Goose goose;
    Pipe bottom;
    bottom.width = 86;
    bottom.x = goose.center_.x - (bottom.width / 2) + 4; // goose is 4 left of center of bottom pipe
    bottom.y = 500;                                      // goose.center_.x = 256
    bottom.height = 268;                                 // bottom.x = 217
    m.bottom_pipes_.clear();                             // width / 2 = 43, so bottom.center.x would be 260
    m.bottom_pipes_.push_back(bottom);
    goose.center_.y = bottom.y - m.gap_distance / 2;
    goose.velocity_ = 0;
    m.goose_ = goose;

    Pipe top;
    top.x = bottom.x;
    top.y = 0;
    top.height = 300;
    top.width = 86;
    m.top_pipes_.clear();
    m.top_pipes_.push_back(top);

    int score = m.score_;
    CHECK(m.score_ == 0);
    m.update(450);
    CHECK(m.score_ == score + 1);
}

TEST_CASE("bird_not_live") {
    Model m;
    Goose goose;
    Goose old_goose = goose;
    m.update(458);
    CHECK(!m.live_);
    CHECK(m.goose_.center_.x == old_goose.center_.x);
    CHECK(m.goose_.center_.y == old_goose.center_.y);
    CHECK(m.goose_.velocity_ == old_goose.velocity_);

}

TEST_CASE ("medal earned") {
    Model m;

    int score = 5;
    m.final_display(score);
    CHECK(m.finalmessage == "You get no medal :( Score: 5");

    score = 10;
    m.final_display(score);
    CHECK(m.finalmessage == "You got a bronze medal! Score: 10");

    score = 20;
    m.final_display(score);
    CHECK(m.finalmessage == "You got a silver medal! Score: 20");

    score = 30;
    m.final_display(score);
    CHECK(m.finalmessage == "You got a gold medal! Score: 30");

}
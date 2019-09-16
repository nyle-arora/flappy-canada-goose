#include "ui.h"

//View constants

Ui::Ui(Model& model)
        : model_(model)
{}


ge211::Dimensions Ui::initial_window_dimensions() const {
    return model_.scene_dims;
}

void Ui::draw(ge211::Sprite_set& sprites) {
    if (model_.gameovervariable) {
        sprites.add_sprite(text_sprite, {360, 384}, 1);
        sprites.add_sprite(bg_pic, {0, 0}, 0);
    }
    else {
        sprites.add_sprite(logo_sprite, {model_.goose_.center_.x - model_.goose_.radius_,
                                         model_.goose_.center_.y - model_.goose_.radius_},
                           1);
        sprites.add_sprite(bg_pic, {0, 0}, 0);
        pipez_.clear();
        pipez_.shrink_to_fit();
        rectz_.clear();
        rectz_.shrink_to_fit();
        for (Pipe p : model_.bottom_pipes_) {
            pipez_.push_back(p);
            rect = ge211::Rectangle_sprite({p.width, p.height}, pipe_color);
            rectz_.push_back(rect);
        }
        for (Pipe p : model_.top_pipes_) {
            pipez_.push_back(p);
            rect = ge211::Rectangle_sprite({p.width, p.height}, pipe_color);
            rectz_.push_back(rect);
        }

        for (unsigned int i = 0; i < pipez_.size(); ++i) {
            sprites.add_sprite(rectz_[i], {pipez_[i].x, pipez_[i].y}, 1);

        }
    }
}

//Controller functions

void Ui::on_key(ge211::Key key) {
    if (key == ge211::Key::code(' '))
        model_.start_();
}

void Ui::on_frame(double) {
    int rand = get_random().between(100, 468);
    model_.update(rand);
}

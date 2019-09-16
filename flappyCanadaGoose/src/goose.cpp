#include "goose.h"

Goose::Goose()
        : userflap (false)
        , center_ {256, 384}
        , radius_ {20}
        , velocity_ {1}
        , flap_acceleration_ {-15}
        , gravity {1}
{}

bool Goose::goose_falling_()
{
    return Goose::velocity_ >= 1;
}

Goose Goose::goose_next_()
{
    Goose result(*this);
    if (result.goose_falling_() && result.userflap)
        result.velocity_ = flap_acceleration_;
    else
        result.velocity_ += gravity;
    result.center_.y += result.velocity_;
    result.userflap = false;
    return result;
}

#pragma once

#include "model.hxx"

#include <string>

class View
{
public:
    explicit View(Model const&);

    void draw(ge211::Sprite_set& set, ge211::Position position);

    ge211::Dimensions initial_window_dimensions() const;

    std::string initial_window_title() const;
    
    ge211::Position board_to_screen(ge211::Position position) const;

    ge211::Position screen_to_board(ge211::Position position) const;

    void reset_view();

private:
    Model const& model_;

    ge211::Image_sprite instructions_{"instructions.png"};
    
    ge211::Circle_sprite light_sprite_;

    ge211::Circle_sprite dark_sprite_;

    ge211::Rectangle_sprite const turns_sprite_;

    ge211::Rectangle_sprite const default_brick_;
    
    int square_width() const;

    int circle_radius() const;
};


#pragma once

#include "model.hxx"

#include <string>

extern ge211::Color const light_color, dark_color, brick_color, end_color,
                          move_color;

extern int const grid_size;

class View
{
public:
    explicit View(Model const&);

    // You will probably want to add arguments here so that the
    // controller can communicate UI state (such as a mouse or
    // cursor position):
    void draw(ge211::Sprite_set& set, ge211::Position);

    ge211::Dimensions initial_window_dimensions() const;

    std::string initial_window_title() const;

    ge211::Position board_to_screen_(ge211::Position) const;
    ge211::Position screen_to_board(ge211 :: Position) const;
    void add_player_(ge211::Sprite_set&, Player, ge211::Position, int) const;

private:
    Model const& model_;


    // TODO: Add any private members you need, such as helper functions
    // or sprites.
    ge211::Circle_sprite const dark_token_{grid_size/2 - 6, dark_color};
    ge211::Circle_sprite const light_token_{grid_size/2 - 6, light_color};
    ge211::Rectangle_sprite const square_{{grid_size - 2, grid_size - 2}, brick_color};
    ge211::Rectangle_sprite const end_square_{{grid_size - 2, grid_size - 2},
                                              end_color};
    ge211::Rectangle_sprite const move_square_{{grid_size - 2, grid_size -2 },
                                             move_color};
    ge211::Circle_sprite const star_ {grid_size/4, {255,255,0}};
};

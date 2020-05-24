#pragma once

#include "model.hxx"

#include <string>

class View
{
public:
    explicit View(Model const&);

    // You will probably want to add arguments here so that the
    // controller can communicate UI state (such as a mouse or
    // cursor position):
    void draw(ge211::Sprite_set& set);

    ge211::Dimensions initial_window_dimensions() const;

    std::string initial_window_title() const;

private:
    Model const& model_;

    // TODO: Add any private members you need, such as helper functions
    // or sprites.
        ge211::Circle_sprite const dark_token_{token_radius, dark_color};
    ge211::Circle_sprite const light_token_{token_radius, light_color};
    ge211::Circle_sprite const dark_shadow_{token_radius, dark_shaded};
    ge211::Circle_sprite const light_shadow_{token_radius, light_shaded};
};

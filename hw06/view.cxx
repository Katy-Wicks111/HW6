#include "view.hxx"

// Convenient type aliases:
using Dimensions = ge211::Dimensions;
using Position   = ge211::Position;
using Color      = ge211::Color;
using Sprite_set = ge211::Sprite_set;

Color const dark_color {0,0,0};
Color const light_color {255,255,255};
Color const brick_color {0,153,51};
Color const move_color {208,0,0};
Color const end_color {169,169,169};

// You can change this or even determine it some other way:
int const grid_size = 36;

View::View(Model const& model)
        : model_(model)
        // You may want to add sprite initialization here
{ }

void View::draw(Sprite_set& set, ge211::Position mouse)
{
    for (int col_no = 0; col_no < model_.board().dimensions().width; ++col_no) {
        for (int row_no = 0; row_no < model_.board().dimensions().height;
        ++row_no) {
            ge211::Position screen_pos = board_to_screen_({col_no, row_no});
            set.add_sprite(square_, screen_pos, 0);

            if (model_.operator[]({col_no, row_no}) == Player::dark) {
                add_player_(set, Player::dark, screen_pos, 10);
            } else if (model_.operator[]({col_no, row_no}) == Player::light) {
                add_player_(set, Player::light, screen_pos, 10);
            }
        }
    }

    if(!model_.is_game_over()) {
        if (model_.turn() == Player::dark){
            set.add_sprite(dark_token_, mouse, 10);
        } else if (model_.turn() == Player::light){
            set.add_sprite(light_token_, mouse, 10);
        }
    }

    if(model_.find_move(mouse) != NULL){
        for(ge211::Position pos : model_.find_move(mouse)->second) {
            set.add_sprite(star_, pos);
        }
    }
}

Dimensions View::initial_window_dimensions() const
{
    // You can change this if you want:
    return grid_size * model_.board().dimensions();
}

std::string View::initial_window_title() const
{
    // You can change this if you want:
    return "Reversi";
}

ge211::Position View::board_to_screen_(ge211::Position board_pos) const
{
    int x = grid_size * board_pos.x;
    int y = grid_size * board_pos.y;
    return ge211::Position{x, y};
}

ge211::Position View::screen_to_board(ge211 :: Position screen_pos) const
{
    int col_no  = screen_pos.x / grid_size;
    int row_no  = screen_pos.y / grid_size;
    return {col_no, row_no};
}

void View::add_player_(ge211::Sprite_set& set, Player player, ge211::Position
                        pos, int z ) const
{
    if (model_.turn() == Player::dark) {
        set.add_sprite(dark_token_, pos, z);
    }
    else if (model_.turn() == Player::light) {
        set.add_sprite(light_token_, pos, z);
    }
    else {
        return;
    }
}

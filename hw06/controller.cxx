#include "controller.hxx"

Controller::Controller(int size)
        : Controller(size, size)
{ }

Controller::Controller(int width, int height)
        : model_(width, height)
        , view_(model_)
{ }

void Controller::draw(ge211::Sprite_set& sprites)
{
    view_.draw(sprites, mouse_);

}

ge211::Dimensions Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

std::string Controller::initial_window_title() const
{
    return view_.initial_window_title();
}

void Controller::on_mouse_down(ge211::Mouse_button btn, ge211::Position
screen_posn)
{
    if (model_.turn() == Player::neither) return;
    if (btn != ge211::Mouse_button::left) return;

    if (model_.find_move(screen_posn) != NULL)
        model_.play_move(screen_posn);
}

void Controller::on_mouse_move(ge211::Position screen_pos)
{
    mouse_ = screen_pos;
}
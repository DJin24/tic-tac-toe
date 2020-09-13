#include "controller.hxx"

using namespace ge211;

Controller::Controller()
        : Controller(3, 3)
{ }

Controller::Controller(int size)
        : Controller(size, size)
{ }

Controller::Controller(int width, int height)
        : model_(width, height)
        , view_(model_)
{ }

void Controller::draw(Sprite_set& sprites)
{
    view_.draw(sprites, mouse_position);
}

Dimensions Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

std::string Controller::initial_window_title() const
{
    return view_.initial_window_title();
}

void Controller::on_key(ge211::Key key)
{
    if (key == ge211::Key::code('q'))
        quit();

    model_ = Model();
    view_.reset_view();

    if (key == ge211::Key::left())
        model_.set_ai_player(1);
    else if (key == ge211::Key::right())
        model_.set_ai_player(2);

    model_.launch();

    if (model_.turn() == model_.ai())
        model_.ai_play_move();
}

void Controller::on_mouse_up(ge211::Mouse_button, ge211::Position position)
{
    if (!model_.live()) {
        model_.launch();
        return;
    }

    if (model_.is_game_over()) {
        model_ = Model();
        view_.reset_view();
        return;
    }

    if (model_.valid_move(view_.screen_to_board(position)) && !model_.is_game_over()
    && model_.turn() != model_.ai()) {
        model_.play_move(view_.screen_to_board(position));
    }

    if (!model_.is_game_over() && model_.turn() == model_.ai())
        model_.ai_play_move();
}

void Controller::on_mouse_move(ge211::Position position){
    mouse_position = position;
}

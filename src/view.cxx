#include "view.hxx"

using namespace ge211;

static int const grid_size = 100;

View::View(Model const& model)
        : model_(model)
        , light_sprite_(circle_radius(), Color(44, 97, 203))
        , dark_sprite_(circle_radius(), Color(0, 0, 0))
        , turns_sprite_({square_width(), square_width()}, Color(174, 197, 243))
        , default_brick_({square_width(), square_width()}, Color::white())
{ }

void View::draw(Sprite_set& set, ge211::Position position)
{
    if (model_.live()) {
        for (int i = 0; i < model_.board().dimensions().width; i++) {
            for (int j = 0; j < model_.board().dimensions().height; j++) {
                set.add_sprite(default_brick_, {i * square_width() + i, j * square_width() + j}, 0);
            }
        }

        //CIRCLE FOLLOWING MOUSE
        if (model_.turn() == Player::light && model_.ai() != Player::light) {
            set.add_sprite(light_sprite_, position, 3);
        } else if (model_.turn() == Player::dark && model_.ai() != Player::dark) {
            set.add_sprite(dark_sprite_, position, 3);
        }

        //ADDING EXISTING PLAYERS WHERE THEY SHOULD BE
        if (!model_.is_game_over()) {
            for (ge211::Position pos : model_.board()) {
                if (model_[pos] == Player::light) {
                    set.add_sprite(light_sprite_, board_to_screen(pos), 2);
                } else if (model_[pos] == Player::dark) {
                    set.add_sprite(dark_sprite_, board_to_screen(pos), 2);
                }
            }
        } else {
            for (ge211::Position pos : model_.board()) {
                if (model_[pos] == Player::light && model_.winner() == Player::light) {
                    set.add_sprite(light_sprite_, board_to_screen(pos), 2);
                } else if (model_[pos] == Player::dark && model_.winner() == Player::light) {
                    dark_sprite_.recolor(Color(64, 64, 64));
                    set.add_sprite(dark_sprite_, board_to_screen(pos), 2);
                } else if (model_[pos] == Player::light && model_.winner() == Player::dark) {
                    light_sprite_.recolor(Color(64, 64, 64));
                    set.add_sprite(light_sprite_, board_to_screen(pos), 2);
                } else if (model_[pos] == Player::dark && model_.winner() == Player::dark) {
                    set.add_sprite(dark_sprite_, board_to_screen(pos), 2);
                } else if (model_[pos] == Player::dark && model_.winner() == Player::neither) {
                    dark_sprite_.recolor(Color(0, 153, 153));
                    set.add_sprite(dark_sprite_, board_to_screen(pos), 2);
                } else if (model_[pos] == Player::light && model_.winner() == Player::neither) {
                    light_sprite_.recolor(Color(0, 153, 153));
                    set.add_sprite(light_sprite_, board_to_screen(pos), 2);
                }
            }
        }
    } else {
        set.add_sprite(instructions_, {0,0});
    }
}

Dimensions View::initial_window_dimensions() const
{
    return grid_size * model_.board().dimensions();
}

std::string View::initial_window_title() const
{
    return "Tic Tac Toe";
}

int View::square_width() const
{
    int number = grid_size * model_.board().dimensions().width;
    number = number - model_.board().dimensions().width;
    number = number / model_.board().dimensions().width;
    return number;
}

int View::circle_radius() const
{
    return square_width() / 2 - 2;
}

ge211::Position View::board_to_screen(ge211::Position position) const {
    int x = position.x;
    int y = position.y;
    return {x * square_width() + x, y * square_width() + y};
}

ge211::Position View::screen_to_board(ge211::Position position) const {
    double x = position.x;
    x = x / square_width();
    double y = position.y;
    y = y / square_width();
    return {(int) x, (int) y};
}

void View::reset_view() {
    light_sprite_.recolor(Color(44, 97, 203));
    dark_sprite_.recolor(Color(0, 0, 0));
}
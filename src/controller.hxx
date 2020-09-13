#pragma once

#include "model.hxx"
#include "view.hxx"

// The main game class for Tic Tac Toe.
class Controller : public ge211::Abstract_game
{
public:
    // Constructs a game with 3 as both its width and height.
    Controller();

    // Constructs a game with `size` as both its width and height.
    explicit Controller(int size);

    // Constructs a game with the given width and height.
    Controller(int width, int height);

// `protected` means that GE211 (via base class `ge211::Abstract_game`)
// can access these members, but arbitrary other code cannot:
protected:
    //
    // Controller operations called by GE211
    //
    void on_key(ge211::Key key) override;
    void on_mouse_up(ge211::Mouse_button, ge211::Position) override;
    void on_mouse_move(ge211::Position) override;

    // These three delegate to the view:
    void draw(ge211::Sprite_set&) override;
    ge211::Dimensions initial_window_dimensions() const override;
    std::string initial_window_title() const override;

private:
    Model            model_;
    View             view_;
    ge211::Position  mouse_position = {0, 0};
};

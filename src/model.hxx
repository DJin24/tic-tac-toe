#pragma once

#include "player.hxx"
#include "board.hxx"

#include <ge211.hxx>

#include <iostream>
#include <vector>

// Represents the state of the Tic Tac Toe game.
class Model
{
public:
    // Constructs a model with 3 as both its width and height.
    Model();

    // Constructs a model with `size` as both its width and height.
    explicit Model(int size);

    // Constructs a model with the given width and height.
    Model(int width, int height);

    // Returns a rectangle containing all the positions of the board.
    // This can be used to iterate over the positions.
    ge211::Rectangle board() const;

    // Returns whether the game is live. This is true after proceeding
    // through the initial instructions.
    bool live() const
    { return live_; }

    // Returns whether the game is finished.
    bool is_game_over() const
    { return winner_ != Player::neither || next_moves_.empty(); }

    // Returns the current turn, or `Player::neither` if the game is
    // over.
    Player turn() const
    { return turn_; }

    // Returns the ai player, or `Player::neither` if there is no ai
    // player.
    Player ai() const
    { return ai_; }

    // Returns the winner, or `Player::neither` if there is no winner
    // (either because the game isn't over, or because it's a draw).
    Player winner() const
    { return winner_; }

    // Returns the player at the given position, or `Player::neither` if
    // the position is unoccupied.
    //
    // ERRORS:
    //  - Throws `ge211::Client_logic_error` if the position is out of
    //    bounds.
    Player operator[](ge211::Position) const;

    // Launches the game by setting live_ to true.
    void launch();

    // Returns whether the move is valid. This is true when the player
    // selects a position that is unoccupied.
    bool valid_move(ge211::Position) const;

    // Attempts to play a move at the given position for the current
    // player. If successful, advances the state of the game to the
    // correct player or game over.
    //
    // ERRORS:
    //  - Throws `ge211::Client_logic_error` if the game is over.
    //  - Throws `ge211::Client_logic_error` if the move is not currently
    //    allowed for the current player.
    //
    void play_move(ge211::Position);

    // Set the corresponding player number to be controlled by the minimax
    // AI. 1 corresponds to Player 1 and 2 corresponds to Player 2.
    void set_ai_player(int);

    // Attempts to have the AI Player play a move at the calculated
    // optimal position. If successful, advances the state of the game to the
    // correct player or game over.
    void ai_play_move();

    friend struct Test_access;

private:
    ///
    /// PRIVATE MEMBER VARIABLES
    ///

    bool live_ = false;
    Player turn_   = Player::dark;
    Player ai_ = Player::neither;
    Player winner_ = Player::neither;
    Board board_;

    std::unordered_set<ge211::Position> next_moves_;
    // INVARIANT:
    //  - `next_moves_` is always current for the state of the game.

    ///
    /// PRIVATE HELPER FUNCTIONS
    ///

    // Advances to the next turn by flipping `turn_` and updating
    // `next_moves_`. Checks for game over. Returns whether any moves
    // are now available (meaning game not over).
    //
    // (Helper for `really_play_move_`.)
    bool advance_turn_();

    // Given a board and 3 positions, check if the positions are of the
    // same type, which would represent the game winner. It is the job of
    // the parent function to make sure the positions passed in form a line.
    // Returns the winning player or Player::neither if no winner.
    //
    // (Helper for `check_winner`.)
    Player line_winner(Board, ge211::Position, ge211::Position, ge211::Position);

    // Given a board, checks all potential position combinations to check if
    // there is a winner. Returns the winning player or Player::neither
    // if no winner.
    //
    // (Helper for `is_game_over`.)
    Player check_winner(Board);

    // Returns whether the game is finished.
    bool game_over();

    // Assuming `move` has been validated, actually executes it by setting
    // the relevant board positions and then advancing the turn and checking
    // for the game to be over.
    //
    // (Helper for `play_move`.)
    //
    // PRECONDITION (UNCHECKED):
    //
    //  - `move` is a valid move right now, meaning it is present in
    //    `next_moves_`
    void really_play_move_(ge211::Position);

    // Given the board, set of available moves, and AI player, calculates
    // the optimal move for the AI player using the minimax algorithm.
    // Returns the position of the optimal move or {-1, -1} if no such move
    // is found.
    //
    // (Helper for `ai_play_move`.)
    ge211::Position minimax(Board, std::unordered_set<ge211::Position>, Player);

    // Given the board, set of available moves, and AI player, calculates
    // the minimax value of the game state using the minimax algorithm.
    // Returns a value of 1 for a win, 0 for a draw, and -1 for a loss.
    //
    // (Helper for `minimax`.)
    int minimax_helper(Board, std::unordered_set<ge211::Position>, Player);
};


#include "model.hxx"

using namespace ge211;

Model::Model()
        : Model(3, 3)
{ }

Model::Model(int size)
        : Model(size, size)
{ }

Model::Model(int width, int height)
        : board_({width, height})
{
    for (ge211::Position pos : board_.all_positions()) {
        next_moves_.insert(pos);
    }
}

Rectangle Model::board() const
{
    return board_.all_positions();
}

Player Model::operator[](Position pos) const
{
    return board_[pos];
}

void Model::launch()
{
    live_ = true;
}

bool Model::valid_move(ge211::Position pos) const
{
    return next_moves_.find(pos) != next_moves_.end();
}

void Model::play_move(Position pos)
{
    if (is_game_over())
        throw Client_logic_error("Model::play_move: game over");

    if (!valid_move(pos))
        throw Client_logic_error("Model::play_move: no such move");

    next_moves_.erase(pos);
    really_play_move_(pos);
}

bool Model::advance_turn_()
{
    turn_ = other_player(turn_);
    return !next_moves_.empty();
}

Player Model::line_winner(Board board, Position a, Position b, Position c)
{
    if (board[a] == board[b] && board[b] == board[c])
        return board[a];
    return Player::neither;
}

Player Model::check_winner(Board board)
{
    // Rows
    if (line_winner(board, {0,0}, {0,1}, {0,2}) != Player::neither)
        return board[{0,0}];
    if (line_winner(board, {1,0}, {1,1}, {1,2}) != Player::neither)
        return board[{1,0}];
    if (line_winner(board, {2,0}, {2,1}, {2,2}) != Player::neither)
        return board[{2,0}];

    // Columns
    if (line_winner(board, {0,0}, {1,0}, {2,0}) != Player::neither)
        return board[{0,0}];
    if (line_winner(board, {0,1}, {1,1}, {2,1}) != Player::neither)
        return board[{0,1}];
    if (line_winner(board, {0,2}, {1,2}, {2,2}) != Player::neither)
        return board[{0,2}];

    // Diagonals
    if (line_winner(board, {0,0}, {1,1}, {2,2}) != Player::neither)
        return board[{0,0}];
    if (line_winner(board, {0,2}, {1,1}, {2,0}) != Player::neither)
        return board[{0,2}];

    return Player::neither;
}

bool Model::game_over()
{
    Player winner;
    if (((winner = check_winner(board_)) != Player::neither) || next_moves_.empty()) {
        winner_ = winner;
        return true;
    }
    return false;
}

void Model::really_play_move_(Position move)
{
    board_.set_(move, turn_);
    if (game_over())
        turn_ = Player::neither;
    advance_turn_();
}

void Model::set_ai_player(int i)
{
    if (i == 1)
        ai_ = Player::dark;
    else if (i == 2)
        ai_ = Player::light;
}

void Model::ai_play_move()
{
    play_move(minimax(board_, next_moves_, turn_));
}

Position Model::minimax(Board board, std::unordered_set<ge211::Position> next_moves, Player player)
{
    Position move = {-1, -1};
    int score = -2;

    for (Position position : next_moves) {
        Board new_board = board;
        new_board.set_(position, player);
        std::unordered_set<ge211::Position> new_next_moves = next_moves;
        new_next_moves.erase(position);
        int move_score = -minimax_helper(new_board, new_next_moves, other_player(player));
        if (move_score > score) {
            score = move_score;
            move = position;
        }
    }

    return move;
}

int Model::minimax_helper(Board board, std::unordered_set<ge211::Position> next_moves, Player player)
{
    Player winner;
    if ((winner = check_winner(board)) != Player::neither) {
        if (winner == player)
            return 1;
        else
            return -1;
    }

    Position move = {-1, -1};
    int score = -2;

    for (Position position : next_moves) {
        Board new_board = board;
        new_board.set_(position, player);
        std::unordered_set<ge211::Position> new_next_moves = next_moves;
        new_next_moves.erase(position);
        int move_score = -minimax_helper(new_board, new_next_moves, other_player(player));
        if (move_score > score) {
            score = move_score;
            move = position;
        }
    }

    if (move.x == -1 && move.y == -1)
        return 0;

    return score;
}
#include "model.hxx"
#include <catch.hxx>

using namespace ge211;

// Test initial model state
TEST_CASE("Initial model state")
{
    Model m(3, 3);
    CHECK( m.board() == Rectangle{0, 0, 3, 3} );
    CHECK_FALSE( m.is_game_over() );
    CHECK( m.turn() == Player::dark );
    CHECK( m.winner() == Player::neither );
    CHECK( m[{0, 0}] == Player::neither );
}
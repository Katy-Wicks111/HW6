#include "model.hxx"
#include <catch.hxx>

using namespace ge211;

// These pass with the starter code and should continue
// to pass.
TEST_CASE("Passes with starter code")
{
    Model m(8, 8);
    CHECK( m.board() == Rectangle{0, 0, 8, 8} );
    CHECK_FALSE( m.is_game_over() );
    CHECK( m.turn() == Player::dark );
    CHECK( m.winner() == Player::neither );
    CHECK( m[{0, 0}] == Player::neither );
    CHECK( m.find_move({0, 0}) == nullptr );
    CHECK_THROWS_AS( m.play_move({0, 0}), Client_logic_error );
}

// This fails with the starter code, but should pass.
TEST_CASE("Fails with starter code")
{
    Model m(6);
    CHECK( m.find_move({2, 2}) );
}

// This fails with the starter code, but should pass.
TEST_CASE("Throws with starter code")
{
    Model m(4);
    m.play_move({1, 1});
}

// YOU NEED MANY MORE TESTS!
//  TESTS FOR PRIVATE HELPER FUNCTIONS
//it's not recognizing test access tho:(
TEST_CASE("test find flips")
{
Model model;
Test_access t{model};

t.board()[{2,2}] = Player::dark;
t.board[{2,3.}] = Player::light;

Position_set f;

f = t.find_flips({2,4},{0,1});
CHECK(f.empty());

f = t.find_flips({2,4},{0,-1}); //how do I know which player it is checking for?
CHECK(f == Position_set{{2,3}}); //ig its dark player idk why

f = t.evaluate_position({2,4});
CHECK(f == Position_set{{2,3}, {2,4}}); //not sure if I should include
// position itself or just the other players positions that changed

f = t.evaluate_position({2,2});
CHECK(f.empty());

f = t.evaluate_position({3,2});
CHECK(f == Position_set(){3,2}); //again, do i include position?

}

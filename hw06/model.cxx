#include "model.hxx"

using namespace ge211;

Model::Model(int size)
        : Model(size, size)
{ }

Model::Model(int width, int height)
        : board_({width, height})
{
    compute_next_moves_();
}

Rectangle Model::board() const
{
    return board_.all_positions();
}

Player Model::operator[](Position pos) const
{
    return board_[pos];
}

Move const* Model::find_move(Position pos) const
{
    auto i = next_moves_.find(pos);

    if (i == next_moves_.end())
        return nullptr;
    else
        return &*i;
}

void Model::play_move(Position pos)
{
    if (is_game_over())
        throw Client_logic_error("Model::play_move: game over");

    Move const* movep = find_move(pos);
    if (!movep)
        throw Client_logic_error("Model::play_move: no such move");

    next_moves_.clear();
    for (int col_no = 0; col_no < board_.center_positions().dimensions().width;
         ++col_no) {
        for (int row_no = 0; row_no < board_.center_positions().dimensions().height;
             ++row_no) {
            if (board_[{col_no, row_no}] == Player::neither) {
                ge211::Position posi = {col_no, row_no};
                next_moves_[posi] = {posi};
            }
        }
    }

    if(!next_moves_.empty())
        return;

    really_play_move_(*movep);
}

//
// BELOW ARE *OPTIONAL* HELPER FUNCTIONS
//

Position_set Model::find_flips_(Position current, Dimensions dir) const
{
    Position_set result = Position_set();
    for (int i = 0; i < board_.dimensions().width - current.x &&
    i < board_.dimensions().height - current.y; i = i + 1){
        Position pos = current + i * dir;
        if (!board_.good_position(pos) || board_[pos] == Player::neither){
            result.clear();
            return result;
        }
        else if (board_[pos] == other_player(turn_)){
            Position_set pos_set = {pos};
            result = result|pos_set;
        }
        else if (board_[pos] == turn_){
            return result;
        }
    }
}

Position_set Model::evaluate_position_(Position pos) const
{
    Position_set result = Position_set();
    if(board_[pos] == Player::neither) {
        for (int i = 0; i < board_.all_directions().size(); i = i + 1) {
            Position_set temp = find_flips_(pos, board_.all_directions()[i]);
            result = result | temp;
        }
        if (!result.empty()) {
            Position_set set = Position_set({pos});
            result = result | set;
        }
    }
    return result;
}

void Model::compute_next_moves_()
{
    next_moves_.clear();
    for(Position pos : board_.all_positions()) {
        next_moves_[pos] = evaluate_position_(pos);
    }
}

bool Model::advance_turn_()
{
    turn_ = other_player(turn_);
    compute_next_moves_();
    if(next_moves_.empty())
        return false;
    else
        return true;
}

void Model::set_game_over_()
{
    turn_ = Player::neither;
    winner_ = winner();
}

void Model::really_play_move_(Move move)
{
    board_.set_all(evaluate_position_(move.first),turn_);
    if (!advance_turn_()){
       if (!advance_turn_()){
           set_game_over_();
       }
    }
}

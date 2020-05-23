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

    Position top1 = board_.center_positions().top_left();
    Position top2 = board_.center_positions().top_right();
    Position bottom1 = board_.center_positions().bottom_left();
    Position bottom2 = board_.center_positions().bottom_right();
    if(board_[top1] == Player:: neither)
        next_moves_[top1] = {top1};
    if(board_[top2] == Player:: neither)
        next_moves_[top2] = {top2};
    if(board_[bottom1] == Player:: neither)
        next_moves_[bottom1] = {bottom1};
    if(board_[bottom2] == Player:: neither)
        next_moves_[bottom2] = {bottom2};

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
    for (int i = 1; i < 8; i = i + 1){
        Position pos = current + i * dir;
        if (!board_.good_position(pos) || board_[pos] == Player::neither){
            result.clear();
            return result;
        }
        else if (board_[pos] == other_player(turn_)){
            result[pos] = true;
        }
        else if (board_[pos] == turn_){
            return result;
        }
    }
}

/////katys
    Position_set find_flips_(ge211::Position start,
                             ge211::Dimensions dir) const{
        Position_set pset= Position_set();
        //Position temp= start;
        size_t n=1;
        while(board_.good_position(start+n*dir) &&
        board_[start+n*dir]==other_player(turn_))
        {
            pset[(start+n*dir)]= true;
            n++;
        }
        return pset;
    }

///

Position_set Model::evaluate_position_(Position pos) const
{
    Position_set result = Position_set();
   if(board_[pos] == Player::neither){
    for(int i = 0; i < board_.all_directions().size(); i = i + 1){
        Position_set temp = find_flips_(pos, board_.all_directions()[i]);
        result = result|temp;
    }
    if (!result.empty()){
        result[pos] = true;
    }
        return result;
   } else{
       return result;
   }
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

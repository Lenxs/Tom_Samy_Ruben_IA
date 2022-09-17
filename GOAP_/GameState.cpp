#include "GameState.h"

goap::GameState::GameState(const std::string name) : priority_(0), name_(name) {
    
}

void goap::GameState::setVariable(const int var_id, const bool value) {
    vars_[var_id] = value;
}

bool goap::GameState::getVariable(const int var_id) const {
    return vars_.at(var_id);
}


bool goap::GameState::operator==(const GameState& other) const {
    return (vars_ == other.vars_);
}

bool goap::GameState::meetsGoal(const GameState& goal_state) const {
    for (const auto& kv : goal_state.vars_) {
        try {
            if (vars_.at(kv.first) != kv.second) {
                return false;
            }
        }
        catch (const std::out_of_range&) {
            return false;
        }
    }
    return true;
}

int goap::GameState::distanceTo(const GameState& goal_state) const {
    int result = 0;

    for (const auto& kv : goal_state.vars_) {
        auto itr = vars_.find(kv.first);
        if (itr == end(vars_) || itr->second != kv.second) {
            ++result;
        }
    }

    return result;
}
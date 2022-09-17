#pragma once
#pragma once
#include <vector>
#include <iostream>
#include <unordered_map>


#pragma once

#include <ostream>
#include <string>
#include <map>

namespace UtilityAI {
    struct GameState {
        float priority_; // useful if this is a goal state, to distinguish from other possible goals
        std::string name_; // the human-readable name of the state
        std::map<int, bool> vars_; // the variables that in aggregate describe a worldstate

        GameState(const std::string name = "");
        void setVariable(const int var_id, const bool value);
        bool getVariable(const int var_id) const;
        bool meetsGoal(const GameState& goal_state) const;
        int distanceTo(const GameState& goal_state) const;
        bool operator==(const GameState& other) const;
        friend std::ostream& operator<<(std::ostream& out, const GameState& n);
    };

}


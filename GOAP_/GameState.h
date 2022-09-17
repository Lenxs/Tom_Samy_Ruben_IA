#pragma once

#include <ostream>
#include <string>
#include <map>

namespace goap {
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

    inline std::ostream& operator<<(std::ostream& out, const GameState& n) {
        out << "GameState { ";
        for (const auto& kv : n.vars_) {
            out << kv.second << " ";
        }
        out << "}";
        return out;
    }

}
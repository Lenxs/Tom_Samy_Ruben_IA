#include "Action.h"
#include "GameState.h"

goap::Action::Action() : cost_(0) {
}

goap::Action::Action(std::string name, int cost) : Action() {
    // Because delegating constructors cannot initialize & delegate at the same time...
    name_ = name;
    cost_ = cost;
}

bool goap::Action::operableOn(const GameState& gs) const {
    for (const auto& precond : preconditions_) {
        try {
            if (gs.vars_.at(precond.first) != precond.second) {
                return false;
            }
        }
        catch (const std::out_of_range&) {
            return false;
        }
    }
    return true;
}

goap::GameState goap::Action::actOn(const GameState& gs) const {
    goap::GameState tmp(gs);
    for (const auto& effect : effects_) {
        tmp.setVariable(effect.first, effect.second);
    }
    return tmp;
}
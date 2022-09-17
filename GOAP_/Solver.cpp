#include "Solver.h"
#include <iostream>
#include <cassert>
#include <algorithm>

int goap::Node::last_id_ = 0;

goap::Node::Node() : g_(0), h_(0) {
    id_ = ++last_id_;
}
goap::Node::Node(const GameState state, int g, int h, int parent_id, const Action* action) :
    ws_(state), g_(g), h_(h), parent_id_(parent_id), action_(action) {
    id_ = ++last_id_;
}

bool goap::operator<(const goap::Node& lhs, const goap::Node& rhs) {
    return lhs.f() < rhs.f();
}

goap::Planner::Planner() {
}

int goap::Planner::calculateHeuristic(const GameState& now, const GameState& goal) const {
    return now.distanceTo(goal);
}

void goap::Planner::addToOpenList(Node&& n) {
    auto it = std::lower_bound(begin(open_),
        end(open_),
        n);
    open_.emplace(it, std::move(n));
}

goap::Node& goap::Planner::popAndClose() {
    assert(!open_.empty());
    closed_.push_back(std::move(open_.front()));
    open_.erase(open_.begin());

    return closed_.back();
}

bool goap::Planner::memberOfClosed(const GameState& ws) const {
    if (std::find_if(begin(closed_), end(closed_), [&](const Node& n) { return n.ws_ == ws; }) == end(closed_)) {
        return false;
    }
    return true;
}

std::vector<goap::Node>::iterator goap::Planner::memberOfOpen(const GameState& ws) {
    return std::find_if(begin(open_), end(open_), [&](const Node& n) { return n.ws_ == ws; });
}

void goap::Planner::printOpenList() const {
    for (const auto& n : open_) {
        std::cout << n << std::endl;
    }
}

void goap::Planner::printClosedList() const {
    for (const auto& n : closed_) {
        std::cout << n << std::endl;
    }
}

std::vector<goap::Action> goap::Planner::plan(const GameState& start, const GameState& goal, const std::vector<Action>& actions) {
    if (start.meetsGoal(goal)) {
        //throw std::runtime_error("Planner cannot plan when the start state and the goal state are the same!");
        return std::vector<goap::Action>();
    }

    open_.clear();
    closed_.clear();

    Node starting_node(start, 0, calculateHeuristic(start, goal), 0, nullptr);

    open_.push_back(std::move(starting_node));

    while (open_.size() > 0) {
        Node& current(popAndClose());

        if (current.ws_.meetsGoal(goal)) {
            std::vector<Action> the_plan;
            do {
                the_plan.push_back(*current.action_);
                auto itr = std::find_if(begin(open_), end(open_), [&](const Node& n) { return n.id_ == current.parent_id_; });
                if (itr == end(open_)) {
                    itr = std::find_if(begin(closed_), end(closed_), [&](const Node& n) { return n.id_ == current.parent_id_; });
                }
                current = *itr;
            } while (current.parent_id_ != 0);
            return the_plan;
        }

        for (const auto& potential_action : actions) {
            if (potential_action.operableOn(current.ws_)) {
                GameState outcome = potential_action.actOn(current.ws_);

                if (memberOfClosed(outcome)) {
                    continue;
                }

                auto p_outcome_node = memberOfOpen(outcome);
                if (p_outcome_node == end(open_)) {
                    Node found(outcome, current.g_ + potential_action.cost(), calculateHeuristic(outcome, goal), current.id_, &potential_action);
                
                    addToOpenList(std::move(found));
                }
                else { 
                    if (current.g_ + potential_action.cost() < p_outcome_node->g_) {
                        p_outcome_node->parent_id_ = current.id_;                 
                        p_outcome_node->g_ = current.g_ + potential_action.cost();
                        p_outcome_node->h_ = calculateHeuristic(outcome, goal);
                        p_outcome_node->action_ = &potential_action;
                        std::sort(begin(open_), end(open_));
                    }
                }
            }
        }
    }

    throw std::runtime_error("A* planner could not find a path from start to goal");
}

#pragma once
#include "Action.h"
#include "GameState.h"
#include <ostream>
#include <unordered_map>
#include <vector>

namespace goap {

    struct Node {
        static int last_id_; // a static that lets us assign incrementing, unique IDs to nodes

        GameState ws_;      // The state of the world at this node.
        int id_;             // the unique ID of this node
        int parent_id_;      // the ID of this node's immediate predecessor
        int g_;              // The A* cost from 'start' to 'here'
        int h_;              // The estimated remaining cost to 'goal' form 'here'
        const Action* action_;     // The action that got us here (for replay purposes)

        Node();
        Node(const GameState state, int g, int h, int parent_id, const Action* action);

        // F -- which is simply G+H -- is autocalculated
        int f() const {
            return g_ + h_;
        }
        friend std::ostream& operator<<(std::ostream& out, const Node& n);
    };

    bool operator<(const Node& lhs, const Node& rhs);

    inline std::ostream& operator<<(std::ostream& out, const Node& n) {
        out << "Node { id:" << n.id_ << " parent:" << n.parent_id_ << " F:" << n.f() << " G:" << n.g_ << " H:" << n.h_;
        out << ", " << n.ws_ << "}";
        return out;
    }



	class Planner {
    private:
        std::vector<Node> open_;   // The A* open list
        std::vector<Node> closed_; // The A* closed list

        bool memberOfClosed(const GameState& ws) const;

        std::vector<goap::Node>::iterator memberOfOpen(const GameState& ws);

        Node& popAndClose();

        void addToOpenList(Node&&);

        int calculateHeuristic(const GameState& now, const GameState& goal) const;

    public:
        Planner();

        void printOpenList() const;

        void printClosedList() const;

        
        std::vector<Action> plan(const GameState& start, const GameState& goal, const std::vector<Action>& actions);

    };
}
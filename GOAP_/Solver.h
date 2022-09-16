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

        //        /**
        //         Less-than operator, needed for keeping Nodes sorted.
        //         @param other the other node to compare against
        //         @return true if this node is less than the other (using F)
        //         */
        //        bool operator<(const Node& other);

                // A friend function of a class is defined outside that class' scope but it has the
                // right to access all private and protected members of the class. Even though the
                // prototypes for friend functions appear in the class definition, friends are not
                // member functions.
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

        /**
         Is the given GameState a member of the closed list? (And by that we mean,
         does any node on the closed list contain an equal GameState.)
         @param ws the GameState in question
         @return true if it's been closed, false if not
         */
        bool memberOfClosed(const GameState& ws) const;

        /**
         Is the given GameState a member of the open list? (And by that we mean,
         does any node on the open list contain an equal GameState.)
         @param ws the GameState in question
         @return a pointer to the note if found, end(open_) if not
         */
        std::vector<goap::Node>::iterator memberOfOpen(const GameState& ws);

        /**
         Pops the first Node from the 'open' list, moves it to the 'closed' list, and
         returns a reference to this newly-closed Node. Its behavior is undefined if
         you call on an empty list.
         @return a reference to the newly closed Node
         */
        Node& popAndClose();

        /**
         Moves the given Node (an rvalue reference) into the 'open' list.
         @param an rvalue reference to a Node that will be moved to the open list
         */
        void addToOpenList(Node&&);

        /**
         Given two GameStates, calculates an estimated distance (the A* 'heuristic')
         between the two.
         @param now the present GameState
         @param goal the desired GameState
         @return an estimated distance between them
         */
        int calculateHeuristic(const GameState& now, const GameState& goal) const;

    public:
        Planner();

        /**
         Useful when you're debugging a GOAP plan: simply dumps the open list to stdout.
        */
        void printOpenList() const;

        /**
         Useful when you're debugging a GOAP plan: simply dumps the closed list to stdout.
        */
        void printClosedList() const;

        /**
         Actually attempt to formulate a plan to get from start to goal, given a pool of
         available actions.
         @param start the starting GameState
         @param goal the goal GameState
         @param actions the available action pool
         @return a vector of Actions in REVERSE ORDER - use a reverse_iterator on this to get stepwise-order
         @exception std::runtime_error if no plan could be made with the available actions and states
         */
        std::vector<Action> plan(const GameState& start, const GameState& goal, const std::vector<Action>& actions);

    };
}
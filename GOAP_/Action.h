#pragma once
#include <vector>
#include <iostream>
#include <unordered_map>

//
//
//
//struct Effect 
//{
//	std::string Name;
//	int EnumValue;
//};
//	
//enum Precondition 
//{
//	HasAmmo,
//	HasWeapon,
//	PlayerInRange,
//	HasEnoughHealthToMove,
//	Length
//};

namespace goap {
    struct GameState;

    class Action {
    private:
        std::string name_; 
        int cost_;         
        // Preconditions are things that must be satisfied before this
        // action can be taken. Only preconditions that "matter" are here.
        std::unordered_map<int, bool> preconditions_;

        // Effects are things that happen when this action takes place.
        std::unordered_map<int, bool> effects_;


    public:
        Action();
        Action(std::string name, int cost);

        bool operableOn(const goap::GameState& gs) const;

        GameState actOn(const GameState& ws) const;

        /**
         Set the given precondition variable and value.
         @param key the name of the precondition
         @param value the value the precondition must hold
         */
        void setPrecondition(const int key, const bool value) {
            preconditions_[key] = value;
        }

        /**
         Set the given effect of this action, in terms of variable and new value.
         @param key the name of the effect
         @param value the value that will result
         */
        void setEffect(const int key, const bool value) {
            effects_[key] = value;
        }

        int cost() const { return cost_; }

        std::string name() const { return name_; }

        
    };

}
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
        std::unordered_map<int, bool> preconditions_;
        std::unordered_map<int, bool> effects_;


    public:
        Action();
        Action(std::string name, int cost);

        bool operableOn(const goap::GameState& gs) const;

        GameState actOn(const GameState& ws) const;
        void setPrecondition(const int key, const bool value) {
            preconditions_[key] = value;
        }
        void setEffect(const int key, const bool value) {
            effects_[key] = value;
        }

        int cost() const { return cost_; }

        std::string name() const { return name_; }

        
    };

}
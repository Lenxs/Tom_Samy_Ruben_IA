#pragma once
#include <vector>
#include <iostream>

struct Effect 
{
	std::string Name;
	int EnumValue;
};
	
enum Precondition 
{
	HasAmmo,
	HasWeapon,
	PlayerInRange,
	HasEnoughHealthToMove,
	Length
};

class Action
{
public:
	std::string Name;
	std::vector<Effect> Effet;
	int cost;
 
private:
};
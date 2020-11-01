#pragma once

#include "GameLogic/MoveableGameUnit.h"
#include "GameLogic/MoveableUnitBehaviourAI.h"

class Halton : public MoveableGameUnit{
public:
private:
protected:
	float m_range;
	float m_damage;
};

class HaltonAI : public AbstractMoveableUnitBehaviorAI {

};
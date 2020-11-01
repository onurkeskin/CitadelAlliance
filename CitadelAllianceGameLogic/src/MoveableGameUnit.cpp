#include "GameLogic/MoveableGameUnit.h"

MoveableGameUnit::MoveableGameUnit(float radius, float height, float maxAcceleration, float maxSpeed) :
	m_radius(radius),
	m_height(height),
	m_maxAcceleration(maxAcceleration),
	m_maxSpeed(maxSpeed)
{
}


MoveableGameUnit::~MoveableGameUnit()
{
}

void MoveableGameUnit::update(const float dt)
{
	GameUnit::update(dt);
	m_unitAI->Tick(dt);
}

void MoveableGameUnit::onSpawn() {
	m_unitAI->onSpawn();
}

UnitState* MoveableGameUnit::getUnitState() {
	auto unitState = GameUnit::getUnitState();
	MoveableGameUnitState* state = new
		MoveableGameUnitState(
			*GameUnit::getUnitState(),
			m_curSpeed
	);
	free(unitState);
	return state;
}

MoveableGameUnitState::MoveableGameUnitState(UnitState basicState, float m_curSpeed[3]) : 
	UnitState(basicState),
	m_curSpeed{ m_curSpeed[0], m_curSpeed[1], m_curSpeed[2] } {
}

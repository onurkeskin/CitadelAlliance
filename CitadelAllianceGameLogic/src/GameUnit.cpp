#include "GameLogic/GameUnit.h"


GameUnit::GameUnit()
{
}


GameUnit::~GameUnit()
{
}

void GameUnit::update(const float dt)
{
}

UnitState* GameUnit::getUnitState() {
	return new UnitState(
		m_playerID,
		m_gameUnitID,
		m_navigationMapID,
		m_position,
		m_orientation,
		m_obj,
		m_isFlying,
		m_isCurFlying,
		m_isTargetable,
		m_isCurTargetable,
		m_maxHealth,
		m_health,
		m_defence,
		m_curDefence
		);
}
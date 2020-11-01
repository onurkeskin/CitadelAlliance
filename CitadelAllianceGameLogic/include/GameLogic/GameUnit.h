#pragma once

#ifndef GAMEUNIT_H
#define GAMEUNIT_H

#include "json\json.h"

#include "GameLogic/IJsonSerializable.h"
#include "GameLogic/UnitState.h"
#include "GameLogic/MoveableUnitBehaviourAI.h"
#include "GameLogic/IObjective.h"

class GameUnit
{
public:
	GameUnit();
	inline GameUnit(int playerID, int gameUnitID,int navigationMapID) :
		m_playerID(playerID), 
		m_gameUnitID(gameUnitID), 
		m_navigationMapID(navigationMapID){}
	virtual ~GameUnit();

	inline virtual void setUnitParams(float maxHealth, float health, float defence, float curDefence,
		bool isFlying, bool isCurFlying, bool isTargetable, bool isCurTargetable) {
		m_maxHealth = maxHealth;
		m_health = health;  
		m_defence = defence; 
		m_curDefence = curDefence;

		m_isFlying = isFlying;  
		m_isCurFlying = isCurFlying;
		m_isTargetable = isTargetable;
		m_isCurTargetable = isCurTargetable;
	}

	virtual UnitState* getUnitState();

	virtual inline int getUnitMapId() { return m_navigationMapID; }
	virtual void setUnitMapId(int idx) { this->m_navigationMapID = idx; }
	virtual void setUnitPlayerId(int idx){ this->m_gameUnitID = idx; }
	virtual void setGameUnitId(int idx) { this->m_gameUnitID = idx; }

	virtual void onSpawn() = 0;
	virtual void update(const float dt);

	virtual inline float* getUnitPosition() { return m_position; }
	virtual inline void setPosition(const float newPos[3]) { m_position[0] = newPos[0]; m_position[1] = newPos[1]; m_position[2] = newPos[2]; }
	
	virtual inline void setUnitAI(UnitBehaviourAI* unitAI) { m_unitAI = unitAI; }
	virtual void inline setUnitObjective(IUnitObjective* obj) { m_obj = obj; if (m_unitAI) m_unitAI->setObjective(obj); }
protected:
	int m_playerID;
	int m_gameUnitID;
	int m_navigationMapID;

	float m_position[3];
	float m_orientation;

	bool m_isFlying;
	bool m_isCurFlying;

	bool m_isTargetable;
	bool m_isCurTargetable;

	// For game purposes
	float m_maxHealth,m_health, m_defence, m_curDefence;

	IUnitObjective* m_obj;
	UnitBehaviourAI* m_unitAI;
};

#endif
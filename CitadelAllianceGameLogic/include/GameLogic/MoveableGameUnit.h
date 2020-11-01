#pragma once

#ifndef MOVEABLEGAMEUNIT_H
#define MOVEABLEGAMEUNIT_H

#include "json\json.h"

#include "GameLogic/GameUnit.h"
#include "GameLogic/MoveableUnitBehaviourAI.h"
#include "GameLogic/IJsonSerializable.h"
#include "GameLogic/UnitMoveObjective.h"

class MoveableGameUnitState : public UnitState {
public:
	MoveableGameUnitState(UnitState basicState, float m_curSpeed[3]);

	inline virtual void Serialize(Json::Value& serializeRoot) {
		UnitState::Serialize(serializeRoot);

		Json::Value serializeVelocity;
		serializeVelocity["x_vel"] = m_curSpeed[0];
		serializeVelocity["y_vel"] = m_curSpeed[1];
		serializeVelocity["z_vel"] = m_curSpeed[2];

		serializeRoot["velocity"] = serializeVelocity;
	}

	inline virtual void Deserialize(Json::Value& serializeRoot) {
		UnitState::Deserialize(serializeRoot);

		Json::Value velocityRoot = serializeRoot["position"];
		m_curSpeed[0] = velocityRoot.get("x_vel", 0.f).asFloat();
		m_curSpeed[1] = velocityRoot.get("y_vel", 0.f).asFloat();
		m_curSpeed[2] = velocityRoot.get("z_vel", 0.f).asFloat();

	}

protected:
	float m_curSpeed[3];

};

class MoveableGameUnit :
	public GameUnit
{
public:
	MoveableGameUnit(float radius, float height, float maxAcceleration, float maxSpeed);
	virtual ~MoveableGameUnit();

	virtual UnitState* getUnitState();

	virtual void onSpawn();
	virtual void update(const float dt);


	virtual float getUnitRadius() { return m_radius; }
	virtual float getUnitHeight() { return m_height; }
	virtual float getUnitMaxAcceleration() { return m_maxAcceleration; }
	virtual float getUnitMaxSpeed() { return m_maxSpeed; }

	virtual inline void setNavMapBinder(MapBindingClass* moveControl) { m_moveControl = moveControl; m_unitAI->setNavMapBinder(moveControl); }
	//virtual inline void setUnitAI(AbstractMoveableUnitBehaviorAI* unitAI) { m_unitAI = unitAI; }
	virtual inline void setCurrentUnitSpeed(const float speed[3]) { m_curSpeed[0] = speed[0]; m_curSpeed[1] = speed[1]; m_curSpeed[2] = speed[2]; }

protected:
	// For navigation purposes
	float m_radius,
		m_height,
		m_maxAcceleration,
		m_maxSpeed;

	float m_curSpeed[3];

	MapBindingClass* m_moveControl;
	//AbstractMoveableUnitBehaviorAI* m_unitAI;
};

#endif
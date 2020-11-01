#pragma once

#ifndef UNITDESTROYOBJECTIVE_H
#define UNITDESTROYOBJECTIVE_H

#include "GameLogic/IObjective.h"
//#include "camathfuncs.h"

#define UNITDESTROYOBJECTIVE 2

class GameUnit;
class UnitDestroyObjective : public IUnitObjective {
public:
	UnitDestroyObjective(float* dest, IUnitObjective* next) : m_dest(dest), IUnitObjective(next) {}

	virtual long getObjectiveType() { return UNITDESTROYOBJECTIVE; }

	virtual void Serialize(Json::Value& serializeRoot);
	virtual void Deserialize(Json::Value& serializeRoot);

	virtual IUnitObjective* doObjective(GameUnit& unit);
	inline float* getObjectivePosition() { return m_dest; }
protected:
	float* m_dest;
};

#endif
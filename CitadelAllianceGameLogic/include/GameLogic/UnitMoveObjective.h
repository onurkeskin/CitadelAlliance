#pragma once

#ifndef UNITMOVEOBJECTIVE_H
#define UNITMOVEOBJECTIVE_H

#include "GameLogic/IObjective.h"
//#include "camathfuncs.h"

#define UNITMOVEOBJECTIVE 1

class GameUnit;
class UnitMoveObjective : public IUnitObjective {
public:
	UnitMoveObjective(float* dest, IUnitObjective* next) : m_dest(dest), IUnitObjective(next){}
	
	virtual long getObjectiveType() { return UNITMOVEOBJECTIVE; }

	virtual void Serialize(Json::Value& serializeRoot);
	virtual void Deserialize(Json::Value& serializeRoot);

	virtual IUnitObjective* doObjective(GameUnit& unit);
	inline float* getObjectivePosition() { return m_dest; }
protected:
	float* m_dest;
};

#endif
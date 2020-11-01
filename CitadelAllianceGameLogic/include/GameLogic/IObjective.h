#pragma once

#include "json\json.h"
#include "GameLogic/IJsonSerializable.h"

#define BASICUNITOBJECTIVE 0

class GameUnit;
class IUnitObjective : public IJsonSerializable {
public:
	IUnitObjective(IUnitObjective* nextObjective) { m_nextObjective = nextObjective; }
	virtual ~IUnitObjective() {}
	
	virtual IUnitObjective* doObjective(GameUnit& unit)/* = 0;*/ { return NULL; }

	virtual long getObjectiveType() {return BASICUNITOBJECTIVE;}

	virtual void Serialize(Json::Value& serializeRoot)/* = 0;*/{}
	virtual void Deserialize(Json::Value& serializeRoot)/* = 0;*/{}

	inline virtual void setNextObjective(IUnitObjective* nextObjective) { m_nextObjective = nextObjective; }
	inline virtual IUnitObjective* getNextObjective() { return m_nextObjective; }
protected:
	IUnitObjective* m_nextObjective;
};


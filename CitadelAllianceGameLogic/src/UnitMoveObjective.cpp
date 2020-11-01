#include "GameLogic/UnitMoveObjective.h"
#include "GameLogic/GameUnit.h"

#include "UtilLibrary/camathfuncs.h"

void UnitMoveObjective::Serialize(Json::Value& serializeRoot) {
	Json::Value serializeObjective;
	serializeObjective["x_obj"] = m_dest[0];
	serializeObjective["y_obj"] = m_dest[1];
	serializeObjective["z_obj"] = m_dest[2];

	serializeObjective["objectivetype"] = getObjectiveType();
	serializeRoot["objective"] = serializeObjective;
}

void UnitMoveObjective::Deserialize(Json::Value& serializeRoot) {
	Json::Value serializeObjective;
	serializeObjective = serializeRoot["objective"];

	m_dest[0] = serializeObjective.get("x_obj", 0).asFloat();
	m_dest[1] = serializeObjective.get("y_obj", 0).asFloat();
	m_dest[2] = serializeObjective.get("z_obj", 0).asFloat();
}


IUnitObjective* UnitMoveObjective::doObjective(GameUnit& unit)
{
	
	if (PointsDistance(unit.getUnitPosition(), m_dest) < 2) {
		return m_nextObjective;
	}
	return this;
}
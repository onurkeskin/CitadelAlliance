#include "GameLogic/UnitState.h"

void UnitState::Serialize(Json::Value& serializeRoot) {
	serializeRoot["p_id"] = m_playerID;
	serializeRoot["u_id"] = m_gameUnitID;
	serializeRoot["u_nav_id"] = m_navigationMapID;

	Json::Value serializePosition;
	serializePosition["x_pos"] = m_position[0];
	serializePosition["y_pos"] = m_position[1];
	serializePosition["z_pos"] = m_position[2];

	serializeRoot["position"] = serializePosition;

	//Json::Value serializeObjective;
	//serializeObjective["x_obj"] = m_objective[0];
	//serializeObjective["y_obj"] = m_objective[1];
	//serializeObjective["z_obj"] = m_objective[2];
	m_objective->Serialize(serializeRoot);

	serializeRoot["orientation"] = m_orientation;

	serializeRoot["isFlying"] = m_isFlying;
	serializeRoot["isCurFlying"] = m_isCurFlying;
	serializeRoot["isTargetable"] = m_isTargetable;
	serializeRoot["isCurTargetable"] = m_isCurTargetable;
	serializeRoot["maxHealth"] = m_maxHealth;
	serializeRoot["health"] = m_health;

	serializeRoot["defence"] = m_defence;
	serializeRoot["curDefence"] = m_curDefence;
}

void UnitState::Deserialize(Json::Value& serializeRoot)
{
	// deserialize primitives
	m_gameUnitID = serializeRoot.get("u_id", 0).asInt();
	m_navigationMapID = serializeRoot.get("u_nav_id", 0).asInt();

	Json::Value positionRoot = serializeRoot["position"];
	m_position[0] = positionRoot.get("x_pos", 0).asFloat();
	m_position[1] = positionRoot.get("y_pos", 0).asFloat();
	m_position[2] = positionRoot.get("z_pos", 0).asFloat();

	m_orientation = serializeRoot.get("orientation", 0.f).asFloat();
}
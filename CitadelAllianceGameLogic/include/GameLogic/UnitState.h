#include "json\json.h"

#include "GameLogic/IObjective.h"
#include "GameLogic/IJsonSerializable.h"

class UnitState : public IJsonSerializable {
public:
	inline UnitState(int playerid, int uid, int nid, float* pos, float orient, IUnitObjective* objective,
		bool isFlying,
		bool isCurFlying,
		bool isTargetable,
		bool isCurTargetable,
		float maxHealth,
		float health,
		float defence,
		float curDefence 
		) :
		m_playerID(playerid),
		m_gameUnitID(uid),
		m_navigationMapID(nid),
		m_orientation(orient),
		m_objective(objective),
		m_isFlying(isFlying),
		m_isCurFlying(isCurFlying),
		m_isTargetable(isTargetable),
		m_isCurTargetable(isCurTargetable),
		m_health(health),
		m_maxHealth(maxHealth),
		m_curDefence(curDefence),
		m_defence(defence) 
	{
		m_position[0] = pos[0];
		m_position[1] = pos[1];
		m_position[2] = pos[2];

	}

	inline UnitState() {}
	inline  ~UnitState() {}

	virtual void Serialize(Json::Value& serializeRoot);
	virtual void Deserialize(Json::Value& serializeRoot);
protected:
	int m_playerID;
	int m_gameUnitID;
	int m_navigationMapID;

	float m_position[3];
	float m_orientation;

	IUnitObjective* m_objective;

	bool m_isFlying, m_isCurFlying, m_isTargetable, m_isCurTargetable;
	float m_maxHealth, m_health, m_defence, m_curDefence;
};
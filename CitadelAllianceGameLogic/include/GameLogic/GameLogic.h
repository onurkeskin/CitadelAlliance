#pragma once

#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <map>
#include "GameLogic/SpawnPoint.h"
#include "GameLogic/IJsonSerializable.h"

#include "json\json.h"

class GameState : public IJsonSerializable {
public:
	inline virtual void Serialize(Json::Value& serializeRoot) {
		serializeRoot["timestamp"] = timestamp;

		std::string units;
		serializeRoot["units"] = Json::Value(Json::arrayValue);

		//Json::Value& unitArray = serializeRoot["units"];/*Json::Value(Json::arrayValue); = Json::Value(Json::arrayValue);*/
		size_t unitArraySize = unitStates.size();
		serializeRoot["units"].resize(unitArraySize);
		int i = 0;
		for (auto it = unitStates.begin(); it != unitStates.end(); it++) {
			(*it)->Serialize(serializeRoot["units"][i]);
			i++;
		}
	}
	inline virtual void Deserialize(Json::Value& serializeRoot) {

	}
	time_t timestamp;
	std::vector<UnitState*> unitStates;
protected:


};

class GameLogic {
public:
	GameLogic();
	virtual ~GameLogic();

	bool Initialize(GameMapBindContainer& navMapBinder);

	bool CreateSpawn(int id, float* s_coor, float* d_coor);
	bool CreateSpawn(int id, float * s_coor, float * d_coor, UnitMoveObjective * obj);
	bool AddExistingSpawn(int id, SpawnPoint* spawn);

	bool AddUnitToSpawn(int SpawnPointID, MoveableGameUnit* unit);
	bool SpawnWaves();

	bool IterateGameDeltaTime(float dt);
	virtual GameState* getGameState();

protected:
	GameMapBindContainer* m_navMapBinder;

	std::map<int, SpawnPoint*> m_spawns;
	std::list<MoveableGameUnit*> m_creaturesOnMap;
};



#endif
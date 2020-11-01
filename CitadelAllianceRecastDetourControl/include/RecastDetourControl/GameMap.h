#ifndef GENERATOR_H
#define GENERATOR_H

#include <map>
#include <string>

#include "Detour/DetourNavMesh.h"
#include "DetourCrowd/DetourCrowd.h"

#include "RecastDetourControl/NavMapController.h"
#include "GameMapBind/GameMapBind.h"
/*
	GameMap handles all related to map,
	Adding unit and structure
	Add new spawn points
	Ticking the game

*/

class GameMap : public MapBindingClass {
public:
	GameMap();
	virtual ~GameMap();

	bool InitializeGameMap(std::string loc);
	bool InitializeCrowd();

	NavMapController* GetNavMapController();

	virtual int addUnit(float* pos, UnitNavigationParams params);
	virtual bool requestMove(int idx, float* pos);
	virtual bool addObstacle(float* size, float* pos);
	virtual NavMapResult IterateNavigationDeltaTime(float dt);

	//GameMapState GetGameMapState;
protected:
	dtNavMeshQuery* m_navquery;
	dtCrowd* m_crowd;
	NavMapController* m_gameMap;
	dtCrowdAgentDebugInfo m_agentDebug;
	dtObstacleAvoidanceDebugData* m_vod;
};

//class GameMapState {
//public:
//	char* WriteToJson();
//protected:
//	std::list<MoveableGameUnit*> m_creaturesOnMap;
//};

#endif
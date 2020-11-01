#pragma once
#ifndef GAMEMAPBIND_H
#define GAMEMAPBIND_H

#include <map>

struct UnitNavigationParams {
	float radius;						///< Agent radius. [Limit: >= 0]
	float height;						///< Agent height. [Limit: > 0]
	float maxAcceleration;				///< Maximum allowed acceleration. [Limit: >= 0]
	float maxSpeed;						///< Maximum allowed speed. [Limit: >= 0]
};

struct UnitParams {
	UnitParams()
	{
	}
	UnitParams(const float i_npos[3], const float i_vel[3])
	{
		npos[0] = i_npos[0]; npos[1] = i_npos[1]; npos[2] = i_npos[2];
		vel[0] = i_vel[0]; vel[1] = i_vel[1]; vel[2] = i_vel[2];
	}
	UnitParams(const UnitParams& cur) 
	{
		npos[0] = cur.npos[0]; npos[1] = cur.npos[1]; npos[2] = cur.npos[2];
		vel[0] = cur.vel[0]; vel[1] = cur.vel[1]; vel[2] = cur.vel[2];
	}

	float npos[3];		///< The current agent position. [(x, y, z)]
	float vel[3];		///< The actual velocity of the agent. The change from nvel -> vel is constrained by max acceleration. [(x, y, z)]
};

struct NavMapResult {
	NavMapResult() : unitResults(unitResults) {
	}
	NavMapResult(const NavMapResult& cur)  {
		auto cpyUnitResults = cur.unitResults;
		for (auto it = cpyUnitResults.begin(); it != cpyUnitResults.end(); it++) {
			unitResults.insert(std::make_pair(it->first, it->second));
		}
	}
	std::map<int, UnitParams> unitResults;
};

class MapBindingClass {
public:
	virtual NavMapResult IterateNavigationDeltaTime(float dt) = 0;

	virtual int addUnit(float* pos, UnitNavigationParams params) = 0;
	virtual bool requestMove(int idx, float* pos);
	virtual bool addObstacle(float* size, float* pos);
protected:
private:
};

class GameMapBindContainer {
public:
	GameMapBindContainer(MapBindingClass* gameMap);

	inline MapBindingClass* getMapBinder() { return m_gameMap; }
protected:
	MapBindingClass* m_gameMap;
private:
};


#endif
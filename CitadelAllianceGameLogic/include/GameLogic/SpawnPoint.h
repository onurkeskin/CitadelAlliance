#pragma once
#ifndef SPAWNPOINT_H
#define SPAWNPOINT_H


#include <list>
#include <queue>

#include "GameMapBind/GameMapBind.h"

#include "GameLogic/IObjectiveGranter.h"
#include "GameLogic/MoveableGameUnit.h"
/*
Contains Spawn Location
Spawn Requires a Destination
*/
class SpawnPoint : public IUnitObjectiveGranter
{
public:
	SpawnPoint(MapBindingClass* con);
	virtual ~SpawnPoint();

	virtual IUnitObjective* GetObjective(MoveableGameUnit& unit);
	inline void setSpawnPointObjective(UnitMoveObjective* obj) { m_obj = obj; }

	void SetSpawnPoint(float x, float y, float z);
	void SetDestinationPoint(float x, float y, float z);

	void AddWave();
	void AddUnitToWave(MoveableGameUnit*);
	void AddUnitToWaveNum(unsigned int, MoveableGameUnit*);

	virtual void SpawnNextWave(std::list<MoveableGameUnit*> *spawnedUnits);
protected:
	MapBindingClass* m_navMapBinder;

	float m_spawnLocation[3];
	float m_destinationLocation[3];

	float m_targetPos[3];

	std::list<std::queue<MoveableGameUnit*>> m_waveQueue;

	UnitMoveObjective* m_obj;
	unsigned int m_curWave;

};

#endif
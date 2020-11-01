#include "GameLogic/SpawnPoint.h"

SpawnPoint::SpawnPoint(MapBindingClass* con) :
	m_navMapBinder(con),
	m_curWave(0)
{
}


SpawnPoint::~SpawnPoint()
{
}

void SpawnPoint::SetSpawnPoint(float x, float y, float z)
{
	m_spawnLocation[0] = x;
	m_spawnLocation[1] = y;
	m_spawnLocation[2] = z;
}

void SpawnPoint::SetDestinationPoint(float x, float y, float z)
{
	m_destinationLocation[0] = x;
	m_destinationLocation[1] = y;
	m_destinationLocation[2] = z;

	return;
}

void SpawnPoint::AddUnitToWave(MoveableGameUnit* unit)
{
	if (m_waveQueue.size() == 0) {
		m_waveQueue.push_back(std::queue<MoveableGameUnit*>());
	}

	AddUnitToWaveNum(m_waveQueue.size() - 1, unit);
}

void SpawnPoint::AddUnitToWaveNum(unsigned int waveNum, MoveableGameUnit *unit)
{
	if (m_waveQueue.size() < waveNum) {
		for (unsigned int i = 0; i <= waveNum; i++) {
			m_waveQueue.push_back(std::queue<MoveableGameUnit*>());
		}
	}

	std::list<std::queue<MoveableGameUnit*>>::iterator it = m_waveQueue.begin();
	for (unsigned int i = 0; i <= waveNum; i++)
	{
		if (it == m_waveQueue.end())
			return;

		if (i == waveNum) {
			it->push(unit);
			//unit->setUnitObjective(m_obj);
		}

		it++;
	}
}

IUnitObjective* SpawnPoint::GetObjective(MoveableGameUnit& unit) {
	//TO DO: This
	return NULL;
}

void SpawnPoint::SpawnNextWave(std::list<MoveableGameUnit*> *spawnedUnits) {
	if (m_waveQueue.size() < m_curWave)
		return;

	auto waveQueue_front = m_waveQueue.front();

	std::queue<MoveableGameUnit*> curWave = waveQueue_front;

	while (!curWave.empty())
	{
		MoveableGameUnit* curUnit = curWave.front();

		UnitNavigationParams params;
		params.height = curUnit->getUnitHeight();
		params.maxAcceleration = curUnit->getUnitMaxAcceleration();
		params.maxSpeed = curUnit->getUnitMaxSpeed();
		params.radius = curUnit->getUnitRadius();

		int idx = m_navMapBinder->addUnit(m_spawnLocation, params);

		if (idx != -1) {
			//m_navMapBinder->requestMove(idx, m_destinationLocation);
			curUnit->setNavMapBinder(m_navMapBinder);
			curUnit->setPosition(m_spawnLocation);
			curUnit->setUnitMapId(idx);

			curUnit->setUnitObjective(m_obj);
			spawnedUnits->insert(spawnedUnits->begin(), curUnit);
			curUnit->onSpawn();
		}

		curWave.pop();
	}

	m_waveQueue.pop_front();
}
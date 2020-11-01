#include "GameLogic/GameLogic.h"
#include <iostream>

using namespace std;

GameLogic::GameLogic() {

}

bool GameLogic::Initialize(GameMapBindContainer& navMapBinder) {
	m_navMapBinder = &navMapBinder;
	return true;
}

GameLogic::~GameLogic() {
	for (auto spawnIterator = m_spawns.begin(); spawnIterator != m_spawns.end(); spawnIterator++) {
		delete spawnIterator->second;
	}

	for (auto creaturesIterator = m_creaturesOnMap.begin(); creaturesIterator != m_creaturesOnMap.end(); creaturesIterator++) {
		delete *creaturesIterator;
	}

	delete m_navMapBinder;

	return;
}

bool GameLogic::CreateSpawn(int id, float* s_coor, float* d_coor) {
	SpawnPoint* spawn = new SpawnPoint(m_navMapBinder->getMapBinder());
	spawn->SetSpawnPoint(s_coor[0], s_coor[1], s_coor[2]);
	spawn->SetDestinationPoint(d_coor[0], d_coor[1], d_coor[2]);

	return AddExistingSpawn(id, spawn);
}

bool GameLogic::CreateSpawn(int id, float* s_coor, float* d_coor, UnitMoveObjective* obj) {
	SpawnPoint* spawn = new SpawnPoint(m_navMapBinder->getMapBinder());
	spawn->SetSpawnPoint(s_coor[0], s_coor[1], s_coor[2]);
	spawn->SetDestinationPoint(d_coor[0], d_coor[1], d_coor[2]);
	spawn->setSpawnPointObjective(obj);
	return AddExistingSpawn(id, spawn);
}

bool GameLogic::AddExistingSpawn(int id, SpawnPoint* spawn)
{
	if (spawn == NULL) return false;
	if (m_spawns.find(id) != m_spawns.end()) return false;

	std::pair<std::map<int, SpawnPoint*>::iterator, bool> ret;

	ret = m_spawns.insert(std::make_pair(id, spawn));
	if (ret.second == false) {
		cout << "element " << id << " already existed";
		cout << " with a value of " << ret.first->second << '\n';
	}

	return true;
}

bool GameLogic::AddUnitToSpawn(int SpawnPointID, MoveableGameUnit* unit) {
	if (m_spawns.find(SpawnPointID) == m_spawns.end()) {
		return false;
	}
	m_spawns[SpawnPointID]->AddUnitToWave(unit);

	return true;
}


bool GameLogic::SpawnWaves() {
	for (std::map<int, SpawnPoint*>::iterator it = m_spawns.begin(); it != m_spawns.end(); ++it)
	{
		//std::list<MoveableGameUnit*> addedUnits;
		it->second->SpawnNextWave(&m_creaturesOnMap);
	}
	return false;
}

bool GameLogic::IterateGameDeltaTime(float dt) {
	auto mapBinder = m_navMapBinder->getMapBinder();
	NavMapResult updatedParams = mapBinder->IterateNavigationDeltaTime(dt);

	for (auto it = m_creaturesOnMap.begin(); it != m_creaturesOnMap.end(); it++) {
		auto uParams = updatedParams.unitResults[(*it)->getUnitMapId()];
		(*it)->setPosition(uParams.npos);
		(*it)->setCurrentUnitSpeed(uParams.vel);
		(*it)->update(dt);
	}

	return true;
}

GameState* GameLogic::getGameState() {
	GameState* gameState = new GameState();
	
	size_t size = m_creaturesOnMap.size();
	std::vector<UnitState*> unitStates(size);
	gameState->unitStates = unitStates;

	int i = 0;
	for (auto it = m_creaturesOnMap.begin(); it != m_creaturesOnMap.end(); it++) {
		UnitState* st = ((*it)->getUnitState());
		gameState->unitStates[i] = st;
		i++;
	}

	return gameState;
}
#include <string>
#include <iostream>
#include <vector>


#include "Recast/Recast.h"

#include "Detour/DetourNavMeshQuery.h"
#include "Detour/DetourNavMesh.h"
#include "Detour/DetourMath.h"

#include "DetourCrowd/DetourCrowd.h"

#include "RecastDetourControl/GameMap.h"
#include "RecastDetourControl/MeshLoaderObj.h"
#include "RecastDetourControl/Interfaces.h"
#include "RecastDetourControl/Sample.h"
#include "RecastDetourControl/NavMapController.h"
#include "RecastDetourControl/MeshPreparer.h"

#ifdef _WIN32
#include <Windows.h>
#else
//#	include <dirent.h>
#	include <cstring>
#endif

using std::string;

string ExePath() {
#ifdef _WIN32
	char buffer[MAX_PATH];
	::GetSystemDirectoryA(buffer, _countof(buffer));
	//GetModuleFileName(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	return std::string(buffer).substr(0, pos);
#endif
	return "";
}

GameMap::GameMap()
{
}

GameMap::~GameMap() {

}

bool GameMap::InitializeGameMap(std::string loc) {
	NavMapController* sample = 0;
	BuildContext ctx;
	MeshPreparer* geom = new MeshPreparer;

	//std::string meshName = "/TestMeshes/testmesh.obj";
	std::string meshName = loc;
	std::cout << meshName.c_str() << std::endl;
	if (!geom->load(&ctx, /*ExePath() +*/meshName))
	{
		std::cout << " Couldn't Load File" << std::endl;
		return false;
	}

	if (!geom || !geom->getMesh())
	{
		ctx.log(RC_LOG_ERROR, "buildTiledNavigation: No vertices and triangles.");
		return false;
	}

	sample = new NavMapController();
	sample->setContext(&ctx);

	BuildSettings settings;
	memset(&settings, 0, sizeof(settings));

	rcVcopy(settings.navMeshBMin, geom->getNavMeshBoundsMin());
	rcVcopy(settings.navMeshBMax, geom->getNavMeshBoundsMax());
	sample->collectSettings(settings);
	geom->saveGeomSet(&settings);

	sample->handleMeshChanged(geom);
	sample->handleSettings();
	if (!sample->handleBuild())
	{
		std::cout << "Couldn't Build" << std::endl;
	}
	ctx.dumpLog("Build log %s:", meshName.c_str());

	m_gameMap = sample;

	m_crowd = sample->getCrowd();
	m_navquery = sample->getNavMeshQuery();

	return true;
}

bool GameMap::InitializeCrowd() {
	bool ok = m_crowd->init(1000, m_gameMap->getAgentRadius(), m_gameMap->getNavMesh());
	if (!ok) return ok;

	m_crowd->getEditableFilter(0)->setExcludeFlags(SAMPLE_POLYFLAGS_DISABLED);
	// Setup local avoidance params to different qualities.
	dtObstacleAvoidanceParams params;
	// Use mostly default settings, copy from dtCrowd.
	memcpy(&params, m_crowd->getObstacleAvoidanceParams(0), sizeof(dtObstacleAvoidanceParams));

	// Low (11)
	params.velBias = 0.5f;
	params.adaptiveDivs = 5;
	params.adaptiveRings = 2;
	params.adaptiveDepth = 1;
	m_crowd->setObstacleAvoidanceParams(0, &params);

	// Medium (22)
	params.velBias = 0.5f;
	params.adaptiveDivs = 5;
	params.adaptiveRings = 2;
	params.adaptiveDepth = 2;
	m_crowd->setObstacleAvoidanceParams(1, &params);

	// Good (45)
	params.velBias = 0.5f;
	params.adaptiveDivs = 7;
	params.adaptiveRings = 2;
	params.adaptiveDepth = 3;
	m_crowd->setObstacleAvoidanceParams(2, &params);

	// High (66)
	params.velBias = 0.5f;
	params.adaptiveDivs = 7;
	params.adaptiveRings = 3;
	params.adaptiveDepth = 3;
	m_crowd->setObstacleAvoidanceParams(3, &params);

	m_vod = dtAllocObstacleAvoidanceDebugData();
	m_vod->init(2048);

	memset(&m_agentDebug, 0, sizeof(m_agentDebug));
	m_agentDebug.idx = -1;
	m_agentDebug.vod = m_vod;

	return ok;
}

NavMapController* GameMap::GetNavMapController() {
	return m_gameMap;
}

int GameMap::addUnit(float* pos, UnitNavigationParams params) {
	
	dtCrowdAgentParams ap;
	memset(&ap, 0, sizeof(ap));
	ap.radius = params.radius;
	ap.height = params.height;
	ap.maxAcceleration = params.maxAcceleration;
	ap.maxSpeed = params.maxSpeed;
	ap.collisionQueryRange = ap.radius * 12.0f;
	ap.pathOptimizationRange = ap.radius * 30.0f;
	ap.updateFlags = 0;
	ap.updateFlags |= DT_CROWD_ANTICIPATE_TURNS;
	ap.updateFlags |= DT_CROWD_OPTIMIZE_VIS;
	ap.updateFlags |= DT_CROWD_OPTIMIZE_TOPO;
	ap.updateFlags |= DT_CROWD_OBSTACLE_AVOIDANCE;
	ap.obstacleAvoidanceType = (unsigned char)3.0f;
	ap.separationWeight = 2.0f;

	int idx = m_crowd->addAgent(pos, &ap);

	return idx;
}

bool GameMap::requestMove(int idx, float* pos) {
	bool toReturn = false;

	const dtQueryFilter* filter = m_crowd->getFilter(0);
	const float* halfExtents = m_crowd->getQueryExtents();

	dtPolyRef m_targetRef;
	float m_targetPos[3];

	bool ok = dtStatusSucceed(m_navquery->findNearestPoly(pos, halfExtents, filter, &m_targetRef, m_targetPos));

	if (ok && m_targetRef && m_crowd->getAgent(idx) != NULL) {
		toReturn = m_crowd->requestMoveTarget(idx, m_targetRef, m_targetPos);
	}

	return toReturn;
}

bool GameMap::addObstacle(float* size, float* pos) {
	return false;
}

NavMapResult GameMap::IterateNavigationDeltaTime(float dt)
{
	TimeVal startTime = getPerfTime();
	/*
		First move all the units in crowd
	*/

	m_crowd->update(dt, &m_agentDebug);
	m_gameMap->handleUpdate(dt);

	TimeVal endTime = getPerfTime();

	NavMapResult result;
	for (int i = 0; i < m_crowd->getAgentCount(); ++i)
	{
		auto curAgent = m_crowd->getAgent(i);
		if (!curAgent->active) continue;

		struct UnitParams unitParams = {
			curAgent->npos,
			curAgent->vel
			//{curAgent->npos[0],curAgent->npos[1],curAgent->npos[2]},
			//{curAgent->vel[0],curAgent->vel[1],curAgent->vel[2]}
		};
		result.unitResults.insert(std::make_pair(i, unitParams));
	}

	//auto cur = result.unitResults[0].npos[0];
	//auto cur1 = result.unitResults[0].npos[1];
	//auto cur2 = result.unitResults[0].npos[2];
	return result;
}


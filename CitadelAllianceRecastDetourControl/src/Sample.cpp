//
// Copyright (c) 2009-2010 Mikko Mononen memon@inside.org
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>

#include "RecastDetourControl/Sample.h"
#include "RecastDetourControl/MeshPreparer.h"


#include "DebugUtils/RecastDebugDraw.h"
#include "DebugUtils/DetourDebugDraw.h"

#include "Recast/Recast.h"

#include "Detour/DetourNavMesh.h"
#include "Detour/DetourNavMeshQuery.h"

#include "DetourCrowd/DetourCrowd.h"

#ifdef _WIN32
#	define snprintf _snprintf
#endif


Sample::Sample() :
	m_geom(0),
	m_navMesh(0),
	m_navQuery(0),
	m_crowd(0),
	m_navMeshDrawFlags(DU_DRAWNAVMESH_OFFMESHCONS | DU_DRAWNAVMESH_CLOSEDLIST),
	m_filterLowHangingObstacles(true),
	m_filterLedgeSpans(true),
	m_filterWalkableLowHeightSpans(true),
	m_ctx(0)
{
	resetCommonSettings();
	m_navQuery = dtAllocNavMeshQuery();
	m_crowd = dtAllocCrowd();
}

Sample::~Sample()
{
	dtFreeNavMeshQuery(m_navQuery);
	dtFreeNavMesh(m_navMesh);
	dtFreeCrowd(m_crowd);
}

void Sample::handleSettings()
{
}

bool Sample::handleBuild()
{
	return true;
}

void Sample::handleUpdate(const float dt)
{
	return;
}

void Sample::handleMeshChanged(MeshPreparer* geom)
{
	m_geom = geom;

	const BuildSettings* buildSettings = geom->getBuildSettings();
	if (buildSettings)
	{
		m_cellSize = buildSettings->cellSize;
		m_cellHeight = buildSettings->cellHeight;
		m_agentHeight = buildSettings->agentHeight;
		m_agentRadius = buildSettings->agentRadius;
		m_agentMaxClimb = buildSettings->agentMaxClimb;
		m_agentMaxSlope = buildSettings->agentMaxSlope;
		m_regionMinSize = buildSettings->regionMinSize;
		m_regionMergeSize = buildSettings->regionMergeSize;
		m_edgeMaxLen = buildSettings->edgeMaxLen;
		m_edgeMaxError = buildSettings->edgeMaxError;
		m_vertsPerPoly = buildSettings->vertsPerPoly;
		m_detailSampleDist = buildSettings->detailSampleDist;
		m_detailSampleMaxError = buildSettings->detailSampleMaxError;
		m_partitionType = buildSettings->partitionType;
	}
}

void Sample::collectSettings(BuildSettings& settings)
{
	settings.cellSize = m_cellSize;
	settings.cellHeight = m_cellHeight;
	settings.agentHeight = m_agentHeight;
	settings.agentRadius = m_agentRadius;
	settings.agentMaxClimb = m_agentMaxClimb;
	settings.agentMaxSlope = m_agentMaxSlope;
	settings.regionMinSize = m_regionMinSize;
	settings.regionMergeSize = m_regionMergeSize;
	settings.edgeMaxLen = m_edgeMaxLen;
	settings.edgeMaxError = m_edgeMaxError;
	settings.vertsPerPoly = m_vertsPerPoly;
	settings.detailSampleDist = m_detailSampleDist;
	settings.detailSampleMaxError = m_detailSampleMaxError;
	settings.partitionType = m_partitionType;
}

void Sample::resetCommonSettings()
{
	m_cellSize = 0.3f;
	m_cellHeight = 0.2f;
	m_agentHeight = 2.0f;
	m_agentRadius = 0.6f;
	m_agentMaxClimb = 0.9f;
	m_agentMaxSlope = 45.0f;
	m_regionMinSize = 8;
	m_regionMergeSize = 20;
	m_edgeMaxLen = 12.0f;
	m_edgeMaxError = 1.3f;
	m_vertsPerPoly = 6.0f;
	m_detailSampleDist = 6.0f;
	m_detailSampleMaxError = 1.0f;
	m_partitionType = SAMPLE_PARTITION_WATERSHED;
}

static const int NAVMESHSET_MAGIC = 'M' << 24 | 'S' << 16 | 'E' << 8 | 'T'; //'MSET';
static const int NAVMESHSET_VERSION = 1;

struct NavMeshSetHeader
{
	int magic;
	int version;
	int numTiles;
	dtNavMeshParams params;
};

struct NavMeshTileHeader
{
	dtTileRef tileRef;
	int dataSize;
};

dtNavMesh* Sample::loadAll(const char* path)
{
	FILE *fp;
	errno_t err = fopen_s(&fp, path, "rb");
	if (fp == NULL)
		return false;

	// Read header.
	NavMeshSetHeader header;
	size_t readLen = fread(&header, sizeof(NavMeshSetHeader), 1, fp);
	if (readLen != 1)
	{
		fclose(fp);
		return 0;
	}
	if (header.magic != NAVMESHSET_MAGIC)
	{
		fclose(fp);
		return 0;
	}
	if (header.version != NAVMESHSET_VERSION)
	{
		fclose(fp);
		return 0;
	}

	dtNavMesh* mesh = dtAllocNavMesh();
	if (!mesh)
	{
		fclose(fp);
		return 0;
	}
	dtStatus status = mesh->init(&header.params);
	if (dtStatusFailed(status))
	{
		fclose(fp);
		return 0;
	}

	// Read tiles.
	for (int i = 0; i < header.numTiles; ++i)
	{
		NavMeshTileHeader tileHeader;
		readLen = fread(&tileHeader, sizeof(tileHeader), 1, fp);
		if (readLen != 1)
		{
			fclose(fp);
			return 0;
		}

		if (!tileHeader.tileRef || !tileHeader.dataSize)
			break;

		unsigned char* data = (unsigned char*)dtAlloc(tileHeader.dataSize, DT_ALLOC_PERM);
		if (!data) break;
		memset(data, 0, tileHeader.dataSize);
		readLen = fread(data, tileHeader.dataSize, 1, fp);
		if (readLen != 1)
		{
			dtFree(data);
			fclose(fp);
			return 0;
		}

		mesh->addTile(data, tileHeader.dataSize, DT_TILE_FREE_DATA, tileHeader.tileRef, 0);
	}

	fclose(fp);

	return mesh;
}

void Sample::saveAll(const char* path, const dtNavMesh* mesh)
{
	if (!mesh) return;

	FILE *fp;
	errno_t err = fopen_s(&fp, path, "rb");
	if (fp == NULL)
		return;

	// Store header.
	NavMeshSetHeader header;
	header.magic = NAVMESHSET_MAGIC;
	header.version = NAVMESHSET_VERSION;
	header.numTiles = 0;
	for (int i = 0; i < mesh->getMaxTiles(); ++i)
	{
		const dtMeshTile* tile = mesh->getTile(i);
		if (!tile || !tile->header || !tile->dataSize) continue;
		header.numTiles++;
	}
	memcpy(&header.params, mesh->getParams(), sizeof(dtNavMeshParams));
	fwrite(&header, sizeof(NavMeshSetHeader), 1, fp);

	// Store tiles.
	for (int i = 0; i < mesh->getMaxTiles(); ++i)
	{
		const dtMeshTile* tile = mesh->getTile(i);
		if (!tile || !tile->header || !tile->dataSize) continue;

		NavMeshTileHeader tileHeader;
		tileHeader.tileRef = mesh->getTileRef(tile);
		tileHeader.dataSize = tile->dataSize;
		fwrite(&tileHeader, sizeof(tileHeader), 1, fp);

		fwrite(tile->data, tile->dataSize, 1, fp);
	}

	fclose(fp);
}

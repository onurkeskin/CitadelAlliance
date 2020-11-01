#ifndef SAMPLE_H
#define SAMPLE_H

#include "RecastDetourControl/Interfaces.h"
/// Tool types.
enum SampleToolType
{
	TOOL_NONE = 0,
	TOOL_TILE_EDIT,
	TOOL_TILE_HIGHLIGHT,
	TOOL_TEMP_OBSTACLE,
	TOOL_NAVMESH_TESTER,
	TOOL_NAVMESH_PRUNE,
	TOOL_OFFMESH_CONNECTION,
	TOOL_CONVEX_VOLUME,
	TOOL_CROWD,
	MAX_TOOLS
};
enum SamplePolyAreas
{
	SAMPLE_POLYAREA_GROUND,
	SAMPLE_POLYAREA_WATER,
	SAMPLE_POLYAREA_ROAD,
	SAMPLE_POLYAREA_DOOR,
	SAMPLE_POLYAREA_GRASS,
	SAMPLE_POLYAREA_JUMP,
};
enum SamplePolyFlags
{
	SAMPLE_POLYFLAGS_WALK = 0x01,		// Ability to walk (ground, grass, road)
	SAMPLE_POLYFLAGS_SWIM = 0x02,		// Ability to swim (water).
	SAMPLE_POLYFLAGS_DOOR = 0x04,		// Ability to move through doors.
	SAMPLE_POLYFLAGS_JUMP = 0x08,		// Ability to jump.
	SAMPLE_POLYFLAGS_DISABLED = 0x10,		// Disabled polygon
	SAMPLE_POLYFLAGS_ALL = 0xffff	// All abilities.
};

enum SamplePartitionType
{
	SAMPLE_PARTITION_WATERSHED,
	SAMPLE_PARTITION_MONOTONE,
	SAMPLE_PARTITION_LAYERS,
};

class Sample
{
protected:
	class MeshPreparer* m_geom;
	class dtNavMesh* m_navMesh;
	class dtNavMeshQuery* m_navQuery;
	class dtCrowd* m_crowd;

	unsigned char m_navMeshDrawFlags;

	float m_cellSize;
	float m_cellHeight;
	float m_agentHeight;
	float m_agentRadius;
	float m_agentMaxClimb;
	float m_agentMaxSlope;
	float m_regionMinSize;
	float m_regionMergeSize;
	float m_edgeMaxLen;
	float m_edgeMaxError;
	float m_vertsPerPoly;
	float m_detailSampleDist;
	float m_detailSampleMaxError;
	int m_partitionType;

	bool m_filterLowHangingObstacles;
	bool m_filterLedgeSpans;
	bool m_filterWalkableLowHeightSpans;

	BuildContext* m_ctx;

	dtNavMesh* loadAll(const char* path);
	void saveAll(const char* path, const dtNavMesh* mesh);

public:
	Sample();
	virtual ~Sample();

	void setContext(BuildContext* ctx) { m_ctx = ctx; }

	virtual void handleSettings();
	virtual void handleMeshChanged(class MeshPreparer* geom);
	virtual bool handleBuild();
	virtual void handleUpdate(const float dt);
	virtual void collectSettings(struct BuildSettings& settings);

	virtual class MeshPreparer* getInputGeom() { return m_geom; }
	virtual class dtNavMesh* getNavMesh() { return m_navMesh; }
	virtual class dtNavMeshQuery* getNavMeshQuery() { return m_navQuery; }
	virtual class dtCrowd* getCrowd() { return m_crowd; }
	virtual float getAgentRadius() { return m_agentRadius; }
	virtual float getAgentHeight() { return m_agentHeight; }
	virtual float getAgentClimb() { return m_agentMaxClimb; }

	unsigned char getNavMeshDrawFlags() const { return m_navMeshDrawFlags; }
	void setNavMeshDrawFlags(unsigned char flags) { m_navMeshDrawFlags = flags; }

	void resetCommonSettings();

private:
	// Explicitly disabled copy constructor and copy assignment operator.
	Sample(const Sample&);
	Sample& operator=(const Sample&);
};
#endif
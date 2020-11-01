#include <algorithm>

#include "GameLogic/GameUnit.h"
#include "GameLogic/MoveableUnitBehaviourAI.h"
#include "UtilLibrary/camathfuncs.h"

BasicRunTargetUnitBehaviourAI::BasicRunTargetUnitBehaviourAI(GameUnit& unit) {
	m_unit = &unit;
}

BasicRunTargetUnitBehaviourAI::BasicRunTargetUnitBehaviourAI() {

}

void BasicRunTargetUnitBehaviourAI::onSpawn() {
	float* pos = m_unit->getUnitPosition();
	m_start[0] = pos[0];
	m_start[1] = pos[1];
	m_start[2] = pos[2];

	m_moveControl->requestMove(m_unit->getUnitMapId(), m_target);
}

void BasicRunTargetUnitBehaviourAI::setObjective(IUnitObjective* obj) {
	auto isUnitMoveObjective = dynamic_cast<UnitMoveObjective*>(obj);
	if (isUnitMoveObjective) {
		objectiveChanged(isUnitMoveObjective);
	}

	auto isUnitDestroyObjective = dynamic_cast<UnitDestroyObjective*>(obj);
	if (isUnitDestroyObjective) {
		objectiveChanged(isUnitDestroyObjective);
	}
}

void BasicRunTargetUnitBehaviourAI::objectiveChanged(UnitMoveObjective* obj) {
	objectiveChange = true;
	m_obj = obj;

	float* objPos = obj->getObjectivePosition();
	m_target[0] = objPos[0];
	m_target[1] = objPos[1];
	m_target[2] = objPos[2];

	if (m_moveControl)
		m_moveControl->requestMove(m_unit->getUnitMapId(), m_target);
}

void BasicRunTargetUnitBehaviourAI::objectiveChanged(UnitDestroyObjective* obj) {
	objectiveChange = true;
	m_obj = obj;
}

void BasicRunTargetUnitBehaviourAI::objectiveChanged(IUnitObjective* obj) {
	objectiveChange = true;
	m_obj = obj;
}

void BasicRunTargetUnitBehaviourAI::Tick(float dt) {
	if (objectiveChange)
		objectiveChange != objectiveChange;

	float* pos = m_unit->getUnitPosition();

	bool objCompForMe = PointsDistance(pos, m_target) < 2;
	if (objCompForMe) {
		auto ok = m_obj->doObjective(*m_unit);
		if (ok != m_obj) {
			m_unit->setUnitObjective(ok);
		}
	}
}
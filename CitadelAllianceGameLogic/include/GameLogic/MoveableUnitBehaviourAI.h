#pragma once

#ifndef MOVEABLEUNITBEHAVIORAI_H
#define MOVEABLEUNITBEHAVIORAI_H

#include "GameMapBind/GameMapBind.h"

#include "GameLogic/UnitMoveObjective.h"
#include "GameLogic/UnitDestroyObjective.h"
#include "GameLogic/UnitBehaviourAI.h"


class AbstractMoveableUnitBehaviorAI : public UnitBehaviourAI /*abstract*/
{
public :
	virtual inline void setNavMapBinder(MapBindingClass* moveControl) { m_moveControl = moveControl; }
	
	virtual void Tick(float dt) = 0;
	
	virtual void onSpawn() = 0;

//	virtual void objectiveChanged(IUnitObjective* node) override = 0;
//
//#define PROCESS(_derived_, _base_)            \
//    virtual void objectiveChanged(_derived_* objective) { \
//      objectiveChanged(static_cast<_base_*>(objective));  \
//    }    
//
//		PROCESS(UnitMoveObjective, IUnitObjective)
//		PROCESS(UnitDestroyObjective, IUnitObjective)
//#undef PROCESS

	//virtual void setDestination(float* pos) = 0;
	virtual void setObjective(IUnitObjective* obj) = 0;

protected:
	MapBindingClass* m_moveControl;
};


class BasicRunTargetUnitBehaviourAI : public AbstractMoveableUnitBehaviorAI
{
public:
	BasicRunTargetUnitBehaviourAI(GameUnit& unit);
	BasicRunTargetUnitBehaviourAI();

	virtual void Tick(float dt);

	virtual void onSpawn();
	//virtual void onDestroy();
	virtual void setObjective(IUnitObjective* obj) override;

	virtual void objectiveChanged(IUnitObjective*);
	virtual void objectiveChanged(UnitMoveObjective*);
	virtual void objectiveChanged(UnitDestroyObjective*);
protected:
	GameUnit* m_unit;
	IUnitObjective* m_obj;

	float m_target[3];
	float m_start[3];

	bool objectiveChange;
private:

};

#endif
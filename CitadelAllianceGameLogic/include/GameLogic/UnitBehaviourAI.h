#pragma once

class UnitBehaviourAI
{
public:
	virtual void Tick(float dt) = 0;

	virtual void onSpawn() = 0;

	virtual void setObjective(IUnitObjective* obj) = 0;

	//virtual void objectiveChanged(IUnitObjective* node) = 0;

//#define PROCESS(_derived_, _base_)            \
//    virtual void objectiveChanged(_derived_* objective) { \
//      objectiveChanged(static_cast<_base_*>(objective));  \
//    }    
//
//		PROCESS(UnitMoveObjective, IUnitObjective)
//		PROCESS(UnitDestroyObjective, IUnitObjective)
//#undef PROCESS

	virtual inline void setNavMapBinder(MapBindingClass* moveControl) { m_moveControl = moveControl; }

protected:
	MapBindingClass* m_moveControl;
};
#pragma once

#include "GameLogic/IObjective.h"

class IUnitObjectiveGranter {
public:
	virtual ~IUnitObjectiveGranter() {}
	virtual IUnitObjective* GetObjective(MoveableGameUnit& unit) = 0;
};
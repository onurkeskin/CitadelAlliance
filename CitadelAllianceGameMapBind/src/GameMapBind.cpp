#include "GameMapBind/GameMapBind.h"


bool MapBindingClass::requestMove(int idx, float* pos) {
	return false;
}

bool MapBindingClass::addObstacle(float* size, float* pos) {
	return false;
}

GameMapBindContainer::GameMapBindContainer(MapBindingClass* gameMap) : m_gameMap(gameMap) {

}
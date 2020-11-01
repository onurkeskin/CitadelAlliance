#include <ctime>

#include "GameLogic/GameMap.h"
#include "GameLogic/SpawnPoint.h"
#include "GameLogic/GameUnit.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/CJsonSerializer.h"

#include <iostream>

#include "GameServer/Server.h"

// BOT LANE
const float teamSouthSpawnBot[3] = /*int[3]*/{ 16.8815f, 0.0f, -215.132f };
const float teamSouthSpawnBotObjective1[3] = { 34.6101f, 0.0f, -100.418f };
const float teamSouthSpawnBotObjective2[3] = { 51.3658f, 0.0f, 0.0f };

const float teamSouthSpawnMid[3] = /*int[3]*/{ -19.871f,-0.286108971f, -14.5999f };
const float teamSouthSpawnTop[3] = /*int[3]*/{ -168.248f,-0.286108971f, 22.6847f };
const float teamNorthSpawnBot[3] = /*int[3]*/{ 148.29f,-0.286108971f, -26.0135f };
const float teamNorthSpawnMid[3] = /*int[3]*/{ -0.087368f,-0.286108971f, 11.271f };
const float teamNorthSpawnTop[3] = /*int[3]*/{ -168.248f,-0.286108971f, -26.0135f };

const float teamSouthCamp[3] = { 0.0f, 0.0f, 203.643f };

const float dest[3] = { -9.97913f, -0.286108971f, 127.69f };

int main() {
	//Json::Value& serializeRoot = Json::Value();
	//GameUnit& unit2 = MoveableGameUnit(0.6f, 2.0f, 8.0f, 3.5f);
	//UnitState* debug = unit2.getUnitState();
	//std::string outputtest;
	//CJsonSerializer::Serialize(debug, outputtest);

	GameMap* gmap = new GameMap();
	gmap->InitializeGameMap("TestMeshes/testmesh.obj");

	NavMapController* navMapCont = gmap->GetNavMapController();
	gmap->InitializeCrowd();

	GameMapBindContainer& binder = GameMapBindContainer(gmap);

	GameLogic* gameLogic = new GameLogic();
	gameLogic->Initialize(binder);

	float _teamSouthSpawnBot[3];
	float _teamSouthCamp[3];
	float _teamSouthSpawnBotObjective1[3];
	float _teamSouthSpawnBotObjective2[3];
	//float _teamSouthSpawnBotObjective3[3];

	memcpy(_teamSouthSpawnBot, teamSouthSpawnBot, 3 * sizeof(float));
	memcpy(_teamSouthCamp, teamSouthCamp, 3 * sizeof(float));
	memcpy(_teamSouthSpawnBotObjective1, teamSouthSpawnBotObjective1, 3 * sizeof(float));
	memcpy(_teamSouthSpawnBotObjective2, teamSouthSpawnBotObjective2, 3 * sizeof(float));
	//memcpy(_teamSouthSpawnBotObjective3, teamSouthSpawnBotObjective3, 3 * sizeof(float));

	UnitMoveObjective* obj4 = new UnitMoveObjective(_teamSouthSpawnBot, NULL);
	UnitMoveObjective* obj3 = new UnitMoveObjective(_teamSouthCamp, obj4);
	UnitMoveObjective* obj2 = new UnitMoveObjective(_teamSouthSpawnBotObjective2, obj3);
	UnitMoveObjective* obj1 = new UnitMoveObjective(_teamSouthSpawnBotObjective1, obj2);
	obj4->setNextObjective(obj1);

	gameLogic->CreateSpawn(1, _teamSouthSpawnBot, _teamSouthCamp, obj1);

	// END OF MAP CREATION
	auto server = new NetworkLib::Server(34890);


	MoveableGameUnit basicUnit = MoveableGameUnit(1.0f, 2.0f, 8.0f, 3.5f);
	basicUnit.setUnitParams(100, 75, 10, 10, 0, 0, 1, 1);
	BasicRunTargetUnitBehaviourAI basicAI = BasicRunTargetUnitBehaviourAI(basicUnit);
	basicUnit.setUnitAI(&basicAI);
	
	MoveableGameUnit basicUnit2 = MoveableGameUnit(1.0f, 2.0f, 8.0f, 3.5f);
	basicUnit2.setUnitParams(100, 75, 10, 10, 0, 0, 1, 1);
	BasicRunTargetUnitBehaviourAI basicAI2 = BasicRunTargetUnitBehaviourAI(basicUnit2);
	basicUnit2.setUnitAI(&basicAI2);

	gameLogic->AddUnitToSpawn(1, &basicUnit);
	gameLogic->AddUnitToSpawn(1, &basicUnit2);

	gameLogic->SpawnWaves();

	float t = 0.0f;

	//const float dt = 1.0f / 20.0f;
	std::time_t time = std::time(0);
	std::time_t startingTime = time;
	time_t prevFrameTime = time;

	while (true) {
		time = std::time(0);
		float dt = (time - prevFrameTime)/* / 1000.0f*/;
		prevFrameTime = time;

		gameLogic->IterateGameDeltaTime(dt);


		std::string output;
		GameState* curGameState = gameLogic->getGameState();
		curGameState->timestamp = time - startingTime;
		CJsonSerializer::Serialize(curGameState, output);
		free(curGameState);
		//std::cout << "testClass Serialized Output\n" << output << "\n\n\n";

		server->SendToAll(output);
		t += dt;
		navMapCont->handleUpdate(dt);
		Sleep(60l);
	}
	return 1;
}
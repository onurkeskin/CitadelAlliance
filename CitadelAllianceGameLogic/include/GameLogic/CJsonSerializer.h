#pragma once

#ifndef CJSONSERIALIZER_H
#define CJSONSERIALIZER_H

#include "GameLogic/IJsonSerializable.h"

class CJsonSerializer
{
public:
	static bool Serialize(IJsonSerializable* pObj, std::string& output);
	static bool Deserialize(IJsonSerializable* pObj, std::string& input);

private:
	CJsonSerializer(void) {};
};

#endif
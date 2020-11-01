#pragma once

#include "json\json.h"

class IJsonSerializable
{
public:
	virtual ~IJsonSerializable(void) {};
	virtual void Serialize(Json::Value& root) = 0;
	virtual void Deserialize(Json::Value& root) = 0;
};

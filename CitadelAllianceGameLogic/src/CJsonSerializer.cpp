#include "GameLogic/CJsonSerializer.h"

#include <iostream>
#include <memory>
#include <sstream>

bool CJsonSerializer::Serialize(IJsonSerializable* pObj, std::string& output)
{
	Json::StreamWriterBuilder builder;
	builder.settings_["indentation"] = "";
	std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

	Json::Value serializeRoot;
	pObj->Serialize(serializeRoot);

	std::stringstream ss;
	writer->write(serializeRoot, &ss);
	ss >> output;

	return true;
}

bool CJsonSerializer::Deserialize(IJsonSerializable* pObj, std::string& input)
{
	if (pObj == NULL)
		return false;

	Json::Value deserializeRoot;
	Json::Reader reader;

	if (!reader.parse(input, deserializeRoot))
		return false;

	pObj->Deserialize(deserializeRoot);

	return true;
}
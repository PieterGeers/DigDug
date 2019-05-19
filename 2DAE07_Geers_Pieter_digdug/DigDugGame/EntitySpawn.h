#pragma once
#include "GameObject.h"
#include "Structs.h"

class EntitySpawn
{
public:
	EntitySpawn() = default;
	~EntitySpawn() = default;

	static std::shared_ptr<GameObject> SpawnPlayer(MVector2_INT pos, const std::string& textPath, int index, bool healthRight = false, MVector2_INT healthPos = { 0, 576 });

	static std::shared_ptr<GameObject> SpawnPlayableFygar(MVector2_INT pos, const std::string& tag, int index, bool healthRight, MVector2_INT healthPos);

	static std::shared_ptr<GameObject> SpawnPooka(MVector2_INT pos, const std::string& tag);
	static std::shared_ptr<GameObject> SpawnFygar(MVector2_INT pos, const std::string& tag);

};


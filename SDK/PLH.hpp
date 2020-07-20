#pragma once

class PlayerData {
public:
	std::byte pad0[16];
	std::int32_t idx;
	std::int32_t team;
	SystemString* name;
	SystemString* formatname;
	std::int32_t clanid;
	SystemString* clanname;
	std::int32_t health;
	std::byte pad00[8];
	Vector3 previous_pos;
	std::byte pad01[4];
	Vector3 current_pos;
	Vector3 pos;
	std::byte pad02[16];
	float next_frame;
	std::byte pad03[60];
	UnityEngine::GameObject* head_bone;
	UnityEngine::GameObject* chest_bone;
	std::byte pad04[228];
	bool spawnprotect;
};

struct PlayerData_Array {
	std::byte pad[12];
	std::uintptr_t MaxLength;
	PlayerData* Items[IL2CPP_ARRAY_MAX_SIZE];
};

class PLH_StaticFields {
public:
	std::byte pad[12];
	PlayerData_Array* players;
};

class PLHKlass {
public:
	std::byte pad[92];
	PLH_StaticFields* static_fields;
};
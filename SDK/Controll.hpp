#pragma once

class PlayerData;

class Controll_StaticFields {
public:
	std::byte pad00[60];
	Vector2 view_angle;
	std::byte pad01[56];
	UnityEngine::Transform* transform_cam;
	std::byte pad02[8];
	UnityEngine::Camera* camera;
	std::byte pad03[172];
	PlayerData* local_player;
	std::byte pad04[200];
	std::int32_t gamemode;
};

class ControllKlass {
public:
	std::byte pad[92];
	Controll_StaticFields* static_fields;
};

class Controll {
public:
	ControllKlass* klass;
};
#pragma once

class Manager {
public:
	inline Controll_StaticFields* GetGameControll() {
		ControllKlass* Controll_Klass = GameMemory->Controll;
		if (!Controll_Klass) return nullptr;

		Controll_StaticFields* Controll_StaticFields = Controll_Klass->static_fields;
		if (!Controll_StaticFields) return nullptr;

		return Controll_StaticFields;
	}

	inline std::vector<PlayerData*> GetPlayers() {
		Manager::Player_List.clear();

		PLHKlass* PLH_Klass = GameMemory->PLH;
		if (!PLH_Klass) return Manager::Player_List;

		PLH_StaticFields* PLH_StaticFields = PLH_Klass->static_fields;
		if (!PLH_StaticFields) return Manager::Player_List;

		PlayerData_Array* Player_Array = PLH_StaticFields->players;
		if (!Player_Array) return Manager::Player_List;

		std::uintptr_t Player_Array_MaxLength = Player_Array->MaxLength;
		if (!Player_Array_MaxLength) return Manager::Player_List;

		for (size_t i = 0; i < Player_Array_MaxLength; i++)
		{
			PlayerData* Player = Player_Array->Items[i];
			if (!Player) continue;

			Manager::Player_List.push_back(Player);
		}

		return Manager::Player_List;
	}

	inline void ChangeTextureColor(UnityEngine::Texture* texture, UnityEngine::Color color) {
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				UnityEngine::Texture::SetPixel(texture, i, j, color);

		UnityEngine::Texture::Apply(texture, true);
	}

	inline std::vector<Vector3> EdgesOfAnObject(UnityEngine::GameObject* Object) {
		if (!Object) return std::vector<Vector3>();

		UnityEngine::Transform* Transform = UnityEngine::GameObject::GetTransform(Object);
		if (!Transform) return std::vector<Vector3>();

		Vector3 ObjectPosition = UnityEngine::Transform::GetPosition(Transform);
		Vector3 ObjectLocalScale = UnityEngine::Transform::GetLocalScale(Transform);

		Vector3 ObjectLeft = ObjectPosition + UnityEngine::Transform::GetRight(Transform) * (ObjectLocalScale / 2.f);
		Vector3 ObjectRight = ObjectPosition - UnityEngine::Transform::GetRight(Transform) * (ObjectLocalScale / 2.f);

		Vector3 ObjectUp = ObjectPosition + UnityEngine::Transform::GetUp(Transform) * (ObjectLocalScale / 2.f);
		Vector3 ObjectDown = ObjectPosition - UnityEngine::Transform::GetUp(Transform) * (ObjectLocalScale / 2.f);

		return std::vector<Vector3>{
			ObjectPosition, ObjectRight, ObjectLeft, ObjectUp, ObjectDown
		};
	}

	inline bool MultipleLineOfSight(std::vector<Vector3> positions, Vector3 src) {
		static UnityEngine::RaycastHit RaycastHit;

		for (Vector3 position : positions)
			if (!UnityEngine::Physics::Linecast(position, src, RaycastHit))
				return true;

		return false;
	}

	inline bool LineOfSight(Vector3 position, Vector3 src) {
		static UnityEngine::RaycastHit RaycastHit;
		return !UnityEngine::Physics::Linecast(position, src, RaycastHit);
	}

	inline void DisableInput(bool value) {
		static bool restore = false;

		if (UnityEngine::Client::IsConnected())
			if (value) {
				UnityEngine::Crosshair::SetCursor(value);
				UnityEngine::Controll::SetLockAngle(value);
				UnityEngine::Controll::SetLockAttack(value);

				restore = true;
			}
			else
				if (restore) {
					UnityEngine::Crosshair::SetCursor(value);
					UnityEngine::Controll::SetLockAngle(value);
					UnityEngine::Controll::SetLockAttack(value);

					restore = false;
				}
	}

	inline bool TeamCheck(PlayerData* player) {
		Controll_StaticFields* GameControll = this->GetGameControll();
		if (!GameControll) return false;
		if (!GameControll->local_player) return false;

		switch (GameControll->gamemode)
		{
		case Enums::GameModes::FREE_FOR_ALL: return true; break;
		case Enums::GameModes::GUN_GAME: return true; break;
		default: return player->team != GameControll->local_player->team; break;
		}
	}
private:
	std::vector<PlayerData*> Player_List = std::vector<PlayerData*>();
	std::vector<UnityEngine::Texture*> Texture_List = std::vector<UnityEngine::Texture*>();
};

inline std::unique_ptr<Manager> GameManager;
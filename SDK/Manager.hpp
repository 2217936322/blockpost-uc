#pragma once

class Manager {
public:
	inline Controll_StaticFields* GetGameControll() {
		ControllKlass* ClassControll_Klass = GameMemory->Controll;
		if (!ClassControll_Klass) return nullptr;

		Controll_StaticFields* ClassControll_StaticFields = ClassControll_Klass->static_fields;
		if (!ClassControll_StaticFields) return nullptr;

		return ClassControll_StaticFields;
	}

	inline std::vector<PlayerData*> GetPlayers() {
		this->Player_List.clear();

		PLHKlass* ClassPLH_Klass = GameMemory->PLH;
		if (!ClassPLH_Klass) return this->Player_List;

		PLH_StaticFields* ClassPLH_StaticFields = ClassPLH_Klass->static_fields;
		if (!ClassPLH_StaticFields) return this->Player_List;

		PlayerData_Array* Player_Array = ClassPLH_StaticFields->players;
		if (!Player_Array) return this->Player_List;

		std::uintptr_t Player_Array_MaxLength = Player_Array->MaxLength;
		if (!Player_Array_MaxLength) return this->Player_List;

		for (size_t i = 0; i < Player_Array_MaxLength; i++)
		{
			PlayerData* Player = Player_Array->Items[i];
			if (!Player) continue;

			this->Player_List.push_back(Player);
		}

		return this->Player_List;
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

		return (GameControll->gamemode != GameModes::FREE_FOR_ALL && GameControll->gamemode != GameModes::GUN_GAME) ? player->team != GameControll->local_player->team : true;
	}

	enum KeyCode {
		Insert = 277
	};
private:
	std::vector<PlayerData*> Player_List;

	enum GameModes {
		FREE_FOR_ALL = 2,
		GUN_GAME = 8
	};
};

inline std::unique_ptr<Manager> GameManager;
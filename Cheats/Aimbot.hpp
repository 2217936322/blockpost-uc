#pragma once

class Aimbot {
public:
	static void Run() {
		Aimbot::InitializeStaticVariables();

		if (!Config::Aimbot::Enabled) return;
		if (!UnityEngine::Input::GetKey(Config::Aimbot::Key)) return;

		Controll_StaticFields* GameControll = GameManager->GetGameControll();
		if (!GameControll) return;
		if (!GameControll->local_player || !GameControll->camera || !GameControll->transform_cam) return;

		Aimbot::Players = GameManager->GetPlayers();

		for (const auto& Player : Aimbot::Players)
		{
			if (!GameManager->TeamCheck(Player) || Player->idx == GameControll->local_player->idx || Player->health <= 10) continue;

			if (Config::Aimbot::SpawnProtect && Player->spawnprotect) continue;

			UnityEngine::GameObject* GameObject = nullptr;

			switch (Config::Aimbot::Bone)
			{
			case Enums::Bones::HEAD: GameObject = Player->head_bone; break;
			case Enums::Bones::CHEST: GameObject = Player->chest_bone; break;
			default: GameObject = Player->head_bone; break;
			}

			std::vector<Vector3> EdgesOfBone = GameManager->EdgesOfAnObject(GameObject);
			if (EdgesOfBone.empty()) continue;

			Vector3 BonePosition = EdgesOfBone[0];

			Vector3 CameraPosition = UnityEngine::Transform::GetPosition(GameControll->transform_cam);
			Vector3 CameraForward = UnityEngine::Transform::GetForward(GameControll->transform_cam);

			if (Config::Aimbot::Visible && !GameManager->MultipleLineOfSight(EdgesOfBone, CameraPosition)) continue;

			CameraPosition += CameraForward;

			Vector3 BoneW2S = UnityEngine::Camera::WorldToScreen(GameControll->camera, BonePosition);
			if (BoneW2S.z < 1.f) continue;

			Vector3 CameraW2S = UnityEngine::Camera::WorldToScreen(GameControll->camera, CameraPosition);
			CameraW2S.y = UnityEngine::Screen::GetResolution().height - CameraW2S.y;

			Vector2 Camera2D{ CameraW2S.x - BoneW2S.x, CameraW2S.y - BoneW2S.y };

			if (Camera2D.length() < Aimbot::BestFov) {
				Aimbot::BestFov = Camera2D.length();
				Aimbot::Target = BonePosition;
			}
		}

		if (Aimbot::Target && !Config::Aimbot::Silent) {
			Vector2 CalculateAngle = Aimbot::CalculateAngle(UnityEngine::Transform::GetPosition(GameControll->transform_cam), Aimbot::Target);
			if (!CalculateAngle) return;

			GameControll->view_angle = CalculateAngle;
		}
	}

	STATIC_INLINE Vector3 Target = { 0.f, 0.f, 0.f };
private:
	STATIC_INLINE float BestFov = Config::Aimbot::Fov;
	STATIC_INLINE std::vector<PlayerData*> Players{};

	static void InitializeStaticVariables() {
		Aimbot::BestFov = Config::Aimbot::Fov;
		Aimbot::Target = { 0.f, 0.f, 0.f };
	}

	static Vector2 CalculateAngle(Vector3 src, Vector3 dst) {
		Vector3 delta = dst - src;

		float x = static_cast<float>(RAD2DEG(atan2(delta.z, delta.x)) - 90.f);
		float y = static_cast<float>((0.f - RAD2DEG(atan2(delta.y, std::sqrtf(delta.x * delta.x + delta.z * delta.z)))));

		return Vector2{ -x, y };
	};
};